# #!/bin/bash

PIO_PATH=${HOME}/.local/bin/pio
BAUD_RATE=115200
PORT=/dev/ttyACM0

main() {
  ${PIO_PATH} run -t clean
  ${PIO_PATH} run -t upload

  ${PIO_PATH} device monitor -b ${BAUD_RATE} -p ${PORT}

  return 0
}

main || (echo "Failed to upload and run" && exit 1)
exit 0

