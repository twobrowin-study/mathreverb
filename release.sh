#!/bin/bash

# Varables section
cmake_clean="./"
mvdir="./"
destroy="./"

# Keys section
while [ -n "$1" ]; do
  case "$1" in
    -r) cmake_clean="rm -r vst3sdk/build/*; cmake.exe -G'Visual Studio 14 2015 Win64' ../";;
    -m) mvdir="/c/'Program Files'/'Common Files'/VST3/";;
    -d) destroy="./destroy_env.sh";;
  esac
  shift
done

# Clean up build directory if need to
"$cmake_clean"

# Create environment if need to
if [ ! -d vst3sdk/public.sdk/samples/vst/mathreverb ]; then
  ./build_env.sh
fi

# Build project
powershell "msbuild.exe vst3sdk\build\public.sdk\samples\vst\mathreverb\mathreverb.vcxproj /t:Build /p:Configuration=Release"

# Move result to destanation
mv VST3/Release/mathreverb.vst3 "$mvdir"mathreverb.vst3

# Destroy environment if need to
"$destroy"
