#!/bin/bash

# Keys and varibles section
while [ -n "$1" ]; do
  case "$1" in
    -r) cmake_clean=true;;
    -d) destroy=true;;
    -m) mvdir=/cygdrive/c/"Program Files"/"Common Files"/VST3/;;
  esac
  shift
done

# Create environment if need to
if [ ! -d vst3sdk/public.sdk/samples/vst/mathreverb ]; then
  ./create_env.sh
fi

# Clean up build directory if need to
if [ "$cmake_clean" ] && [ "$(ls -A vst3sdk/build)" ]; then
  rm -r vst3sdk/build/*
fi

# CMake project if need to
if [ ! "$(ls -A vst3sdk/build)" ]; then
  cd vst3sdk/build
  cmake.exe -G'Visual Studio 14 2015 Win64' ../
  cd ../../
fi

# Build project
powershell "msbuild.exe vst3sdk\build\public.sdk\samples\vst\mathreverb\mathreverb.vcxproj /t:Build /p:Configuration=Release"

# Move result to destanation
mv vst3sdk/build/VST3/Release/mathreverb.vst3 "$mvdir"./

# Destroy environment if need to
if [ "$destroy" ]; then
  ./destroy_env.sh
fi
