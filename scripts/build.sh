#!/bin/bash

builddir=$2
currdir=$(pwd)

# If set 64bit else - empty string
if [ "$1" == "Win64" ]; then
    generation=" $1"
fi

mvdir=$3
if [ "$mvdir" == "none" ]; then
    mvdir='.'
fi

ext='vst3'
if [ "$4" == "--vst2" ]; then
    ext='dll'
fi

echo "Entering $builddir"
cd $builddir

echo "Cleaning directory"
rm -rf *

echo "Compiling MS VC 2015 project files"
cmake.exe -G"Visual Studio 14 2015$generation" ../

echo "Leaving $builddir"
cd $currdir

echo "Building project mathreverb.vcxproj"
powershell "msbuild.exe vst3sdk\build\public.sdk\samples\vst\mathreverb\mathreverb.vcxproj /t:Build /p:Configuration=Release"

# Move result to destination
echo "Moving mathreverb.vst3 into $mvdir"
mv vst3sdk/build/VST3/Release/mathreverb.vst3 "$mvdir/mathreverb.$ext"
