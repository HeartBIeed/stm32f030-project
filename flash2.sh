#!/bin/bash

interfaceCfg="interface/stlink.cfg"
targetCfg="target/stm32f0x.cfg"
firmware="build/main.hex"

openocd -f "$interfaceCfg" -f "$targetCfg" \
  -c "program $firmware verify reset exit"

echo -e "\e[32mПрошивка загружена!\e[0m"