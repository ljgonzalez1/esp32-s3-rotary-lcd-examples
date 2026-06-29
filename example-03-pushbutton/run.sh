pio run -t clean && \
pio run -t upload && \
{ pio device monitor -b 115200 -p /dev/ttyACM0 || \
  pio device monitor -b 115200 -p /dev/ttyACM1 || \
  pio device monitor -b 115200 -p /dev/ttyACM2; }
