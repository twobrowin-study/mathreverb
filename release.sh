#!/bin/bash

# Keys and varibles section
mvdir="./"
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
  cd vst3sdk/build
  cmake.exe -G'Visual Studio 14 2015 Win64' ../
  cd ../../
fi

# Create environment if need to
if [ ! -d vst3sdk/public.sdk/samples/vst/mathreverb ]; then
  ./create_env.sh
fi

# Build project
powershell "msbuild.exe vst3sdk\build\public.sdk\samples\vst\mathreverb\mathreverb.vcxproj /t:Build /p:Configuration=Release"

# Move result to destanation
mv vst3sdk/build/VST3/Release/mathreverb.vst3 "$mvdir"

# Destroy environment if need to
if [ "$destroy" ]; then
  ./destroy_env.sh
fi
