#!/bin/bash
echo "Moving mathreverb_source folder into vst3sdk/public.sdk/samples/vst/ as mathreverb"
mv mathreverb_source vst3sdk/public.sdk/samples/vst/mathreverb

echo "Adding empty line into vst3sdk/CMakeLists.txt"
echo >> vst3sdk/CMakeLists.txt

echo "Adding line '# MathReverb plugin' into vst3sdk/CMakeLists.txt"
echo "# MathReverb plugin" >> vst3sdk/CMakeLists.txt

echo "Adding line 'add_subdirectory(public.sdk/samples/vst/mathreverb)' into vst3sdk/CMakeLists.txt"
echo "add_subdirectory(public.sdk/samples/vst/mathreverb)" >> vst3sdk/CMakeLists.txt

echo "Makind vst3sdk/build directory"
mkdir vst3sdk/build
