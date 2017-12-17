#!/bin/bash

builddir=$2
currdir=$(pwd)

# If set 64bit else - empty string
if [ "$1" == "Win64" ]; then
    generation="$1"
fi

echo "Entering $builddir"
cd $builddir

echo "Cleaning directory"
rm -rf *

echo "Compiling MS VC 2015 project files"
cmake.exe -G"Visual Studio 14 2015 $generation" ../

echo "Leaving $builddir"
cd $currdir

echo "Building project mathreverb.vcxproj"
powershell "msbuild.exe vst3sdk\build\public.sdk\samples\vst\mathreverb\mathreverb.vcxproj /t:Build /p:Configuration=Release"

# Move result to destanation
echo "Moving mathreverb.vst3 into $3"
mv vst3sdk/build/VST3/Release/mathreverb.vst3 $3
