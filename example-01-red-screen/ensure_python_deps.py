"""
PlatformIO pre-script: ensure required Python packages are available for the build.

- Installs/updates packages into a *project-local* vendor directory (".pio/pythonlibs").
- Uses the exact same Python interpreter PlatformIO uses during the build ($PYTHONEXE).
- Prepends the vendor directory to PYTHONPATH so child tools (e.g., esptool.py) can import them.

Extendable:
- Add more packages to REQUIRED_PKGS below (key = import name, value = pip spec).
- Optionally add a plain-text file `python-vendor-requirements.txt` at the project root
  (one pip requirement per line, comments allowed with '#'). These specs will be merged.
"""

from pathlib import Path
Import("env")  # SCons environment provided by PlatformIO

# -------------------------
# Configuration
# -------------------------
# Map of import_name -> pip requirement spec
REQUIRED_PKGS = {
    # Example: "intelhex" module, installed from the PyPI package "intelhex"
    "intelhex": "intelhex>=2.3.0",
}

# Optional extra requirements file at the project root
REQ_FILE = "python-vendor-requirements.txt"

# Vendor directory inside the project (kept under .pio/ so it's ephemeral and per-build)
VENDOR_DIR = Path(env["PROJECT_DIR"]) / ".pio" / "pythonlibs"
VENDOR_DIR.mkdir(parents=True, exist_ok=True)

# -------------------------
# Helpers
# -------------------------

def _read_extra_requirements(req_path: Path):
    """Parse a minimal requirements file (ignoring comments and blank lines)."""
    specs = []
    if not req_path.is_file():
        return specs
    for line in req_path.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        specs.append(line)
    return specs


def _pip_install(spec: str):
    """Run pip install/upgrade *into* the vendor dir using PlatformIO's Python.
    We use --upgrade so existing installs can be bumped to the requested version if needed.
    """
    cmd = (
        "$PYTHONEXE -m pip install "
        "--disable-pip-version-check --no-input --upgrade "
        f"--target \"{VENDOR_DIR}\" {spec}"
    )
    print(f">>> pip: {spec}")
    # Execute via SCons env so it inherits PlatformIO's environment
    env.Execute(cmd)


# -------------------------
# Main
# -------------------------
print("=== Ensuring Python vendor packages for PlatformIO build ===")
print("Python executable:")
env.Execute('$PYTHONEXE -c "import sys; print(sys.executable)"')

# 1) Merge REQUIRED_PKGS with optional file specs
extra_specs = _read_extra_requirements(Path(env["PROJECT_DIR"]) / REQ_FILE)
if extra_specs:
    print(f"Found {REQ_FILE} with {len(extra_specs)} entries")

# 2) Install/upgrade pinned packages
for import_name, spec in REQUIRED_PKGS.items():
    # Try importing first (for a friendly log), but still run pip --upgrade to ensure version
    try:
        __import__(import_name)
        print(f"Module '{import_name}' is already importable; ensuring version via pip...")
    except Exception:
        print(f"Module '{import_name}' missing; installing via pip...")
    _pip_install(spec)

# 3) Install any extra specs from the optional requirements file
for spec in extra_specs:
    _pip_install(spec)

# 4) Prepend vendor dir to PYTHONPATH so child tools (esptool.py, etc.) can import modules
env.PrependENVPath("PYTHONPATH", str(VENDOR_DIR))
print("PYTHONPATH begins with:", VENDOR_DIR)
print("=== Python vendor packages ready ===")
