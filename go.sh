#!/bin/bash
elf=$(find ./debug -name "*.elf" -type f)

if [ -z "$elf" ]; then
    echo "No elf executable found on debug directory"
    exit
fi

 openocd \
  -f interface/cmsis-dap.cfg \
  -c "cmsis_dap_backend hid" \
  -c "transport select swd" \
  -f target/lpc84x.cfg \
  -c "adapter speed 1000" \
  -c "program ${elf} verify reset exit"
