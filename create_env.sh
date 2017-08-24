#!/bin/bash
git clone --recursive https://github.com/steinbergmedia/vst3sdk.git
if [ "$(ls -A vst3sdk/base)" ] && [ "$(ls -A vst3sdk/cmake)" ] && [ "$(ls -A vst3sdk/pluginterfaces)" ] && [ "$(ls -A vst3sdk/public.sdk)" ] && [ "$(ls -A vst3sdk/vstgui4)" ]; then
  mv mathreverb_source vst3sdk/public.sdk/samples/vst/mathreverb
  echo >> vst3sdk/CMakeLists.txt
  echo "# MathReverb plugin" >> vst3sdk/CMakeLists.txt
  echo "add_subdirectory(public.sdk/samples/vst/mathreverb)" >> vst3sdk/CMakeLists.txt
  mkdir vst3sdk/build
  cd vst3sdk/build
  cmake.exe -G"Visual Studio 14 2015 Win64" ../
  cd ../../
else
  echo "https://github.com/steinbergmedia/vst3sdk.git is not responding"
fi
