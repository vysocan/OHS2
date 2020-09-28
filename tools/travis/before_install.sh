#!/bin/sh

set -ex

cd /tmp

sudo apt-get install lib32z1
wget https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases/download/v9.2.1-1.1/xpack-arm-none-eabi-gcc-9.2.1-1.1-linux-x64.tar.gz
tar xjf xpack-arm-none-eabi-gcc-9.2.1-1.1-linux-x64.tar.gz
#export PATH=/tmp/gcc-arm-none-eabi-4_9-2015q3/bin:$PATH
export PATH=/tmp/xpack-arm-none-eabi-gcc-9.2.1-1.1/bin:$PATH
arm-none-eabi-gcc --version

cd -
cd ..

#mkdir ChibiOS-RT
#cd ChibiOS-RT
#git clone https://github.com/ChibiOS/ChibiOS.git .