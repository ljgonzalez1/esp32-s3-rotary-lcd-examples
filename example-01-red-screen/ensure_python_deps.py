# ensure_python_deps.py
from pathlib import Path
Import("env")

REQUIRED = "intelhex>=2.3.0"

# Vendor dir (queda dentro de .pio del proyecto)
vendor_dir = Path(env["PROJECT_DIR"]) / ".pio" / "pythonlibs"
vendor_dir.mkdir(parents=True, exist_ok=True)

print(">>> Ensuring intelhex for PlatformIO build...")
# Instala/actualiza SI ES NECESARIO dentro del mismo Python que usa PIO
env.Execute(
    '$PYTHONEXE -m pip install --disable-pip-version-check --no-input --upgrade '
    f'--target "{vendor_dir}" {REQUIRED}'
)

# Ponemos ese path AL INICIO para que tenga prioridad al importar
env.PrependENVPath("PYTHONPATH", str(vendor_dir))
print("PYTHONPATH now begins with:", vendor_dir)
