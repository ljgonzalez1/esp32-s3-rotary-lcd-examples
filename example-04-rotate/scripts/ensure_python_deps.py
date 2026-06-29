# scripts/ensure_python_deps.py
from pathlib import Path
Import("env")
import os, sys

VENDOR_DIR = Path(env["PROJECT_DIR"]) / ".pio" / "pythonlibs"
VENDOR_DIR.mkdir(parents=True, exist_ok=True)

def pip(py, *pkgs):
    cmd = f'"{py}" -m pip install --disable-pip-version-check --no-input --upgrade ' + " ".join(pkgs)
    print(">>>", cmd); env.Execute(cmd)

# 1) Vendor por si acaso (intelhex visible vía PYTHONPATH)
pip(env["PYTHONEXE"], f'--target "{VENDOR_DIR}"', "intelhex>=2.3.0")
env.PrependENVPath("PYTHONPATH", str(VENDOR_DIR))

# 2) PIO venv (donde a veces corre esptool.py)
pio_py = sys.executable  # python actual del proceso de build
pip(pio_py, "intelhex>=2.3.0")

# 3) Venv de ESP-IDF (ldgen.py corre aquí) → pin pyparsing 3.0.x
idf_py = env["ENV"].get("IDF_PYTHON_ENV_PATH")
if not idf_py:
    penv = Path.home()/".platformio"/"penv"
    cands = sorted(penv.glob(".espidf-*"), reverse=True)
    if cands:
        idf_py = str(cands[0]/("Scripts/python.exe" if os.name=="nt" else "bin/python"))

if idf_py:
    pip(idf_py, "intelhex>=2.3.0", "pyparsing==3.0.9")
else:
    print("WARN: ESP-IDF venv not found; skipped.")

# Sanitizar locale para objdump/ldgen
env['ENV']['LC_ALL'] = 'C'
env['ENV']['LANG']   = 'C'
print("PYTHONPATH ->", VENDOR_DIR)
