#!/bin/bash

####### Настройки ###########
interfaceCfg="interface/stlink.cfg"
targetCfg="target/stm32f0x.cfg"
firmware="build/main.hex"
#############################

openocd -f "$interfaceCfg" -f "$targetCfg" &
sleep 3

# telnet
telnet 127.0.0.1 4444 << EOF
reset halt
flash write_image erase $firmware
reset run
exit
EOF

# Сообщение о завершении
echo -e "\e[32m Прошивка загружена! \e[0m"
sleep 3
