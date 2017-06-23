#!/bin/sh
port=$1
if [ -z "$port" ]; then
  echo "Usage: $0 PORT"
  exit 1
fi

../../tools/px_uploader.py --port "$port" --baud-bootloader 115200 --baud-flightstack 115200 firmware.hex
