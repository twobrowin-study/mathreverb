#!/bin/bash
git clone --recursive https://github.com/steinbergmedia/vst3sdk.git
mv mathreverb/ vst3sdk/public.sdk/samples/vst/
cd vst3sdk
echo >> CMakeLists.txt
echo "# MathReverb plugin" >> CMakeLists.txt
echo "add_subdirectory(public.sdk/samples/vst/mathreverb)" >> CMakeLists.txt
mkdir build
cd build
cmake.exe -G"Visual Studio 14 2015 Win64" ../
