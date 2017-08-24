#!/bin/bash

# Keys and varibles section
while [ -n "$1" ]; do
  case "$1" in
    -r) cmake_clean=true;;
    -d) destroy=true;;
    -m) mvdir="/c/'Program Files'/'Common Files'/VST3/";;
  esac
  shift
done

# Clean up build directory if need to
if [ "$cmake_clean" ]; then
  rm -r vst3sdk/build/*
  cmake.exe -G'Visual Studio 14 2015 Win64' ../
fi

# Create environment if need to
if [ ! -d vst3sdk/public.sdk/samples/vst/mathreverb ]; then
  ./build_env.sh
fi

# Build project
powershell "msbuild.exe vst3sdk\build\public.sdk\samples\vst\mathreverb\mathreverb.vcxproj /t:Build /p:Configuration=Release"

# Move result to destanation
mv VST3/Release/mathreverb.vst3 "$mvdir"mathreverb.vst3

# Destroy environment if need to
if [ "$destroy" ]; then
  ./destroy_env.sh
fi
