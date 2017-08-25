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
  echo "Creating environment"
  ./create_env.sh
fi

# Clean up build directory if need to
if [ "$cmake_clean" ] && [ "$(ls -A vst3sdk/build)" ]; then
  echo "Cleaning vst3sdk/build directory"
  rm -r vst3sdk/build/*
fi

# CMake project if need to
if [ ! "$(ls -A vst3sdk/build)" ]; then
  echo "Compiling MS VC 2015 project files"

  echo "Entering vst3sdk/build"
  cd vst3sdk/build

  echo "Compiling... Executing CMake"
  cmake.exe -G'Visual Studio 14 2015 Win64' ../

  echo "Leaving vst3sdk/build"
  cd ../../
fi

# Build project
echo "Building project mathreverb.vcxproj"
powershell "msbuild.exe vst3sdk\build\public.sdk\samples\vst\mathreverb\mathreverb.vcxproj /t:Build /p:Configuration=Release"

# Move result to destanation
echo "Moving mathreverb.vst3 into $( [ $mvdir ] && echo $mvdir || pwd )"
mv vst3sdk/build/VST3/Release/mathreverb.vst3 "$mvdir"./

# Destroy environment if need to
if [ "$destroy" ]; then
  echo "Destroy environment"
  ./destroy_env.sh
fi
