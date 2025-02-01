#!/bin/bash
export ARMGCC_DIR=/home/naii/rt1064/toolchain/gcc-arm-none-eabi-10.3-2021.10/
export SDK_DIR=/home/naii/rt1064/sdk
cd build/
if [ -d "CMakeFiles" ];then rm -rf CMakeFiles; fi
if [ -f "Makefile" ];then rm -f Makefile; fi
if [ -f "cmake_install.cmake" ];then rm -f cmake_install.cmake; fi
if [ -f "CMakeCache.txt" ];then rm -f CMakeCache.txt; fi
cmake -DSdkRootDirPath=${SDK_DIR} -DCMAKE_TOOLCHAIN_FILE=${SDK_DIR}"/tools/cmake_toolchain_files/armgcc.cmake" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=flexspi_nor_debug  ..
make -j 2>&1 | tee build_log.txt
