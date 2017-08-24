#!/bin/bash

# Varables and keys section
mvdir="../../"
while [ -n "$1" ]; do
  case "$1" in
    -r) build_clean="rm -r vst3sdk/build/*; cmake.exe -G'Visual Studio 14 2015 Win64' ../";;
    -m) mvdir="/c/'Program Files'/'Common Files'/VST3";;
    -d) dstr="./destroy_env.sh";;
  esac
  shift
done

# Clean up build directory if need to
"$build_clean"

# Create environment if need to
if [ ! -d vst3sdk/public.sdk/samples/vst/mathreverb ]; then
  ./build_env.sh
fi

# Build project
cd vst3sdk/build
powershell "msbuild.exe public.sdk\samples\vst\mathreverb\mathreverb.vcxproj /t:Build /p:Configuration=Release"

# Move result to destanation
mv VST3/Release/mathreverb.vst3 mathreverb.vst3

# Destroy environment if need to
"$dstr"
