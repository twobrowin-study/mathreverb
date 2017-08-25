#!/bin/bash
mv mathreverb_source vst3sdk/public.sdk/samples/vst/mathreverb
echo >> vst3sdk/CMakeLists.txt
echo "# MathReverb plugin" >> vst3sdk/CMakeLists.txt
echo "add_subdirectory(public.sdk/samples/vst/mathreverb)" >> vst3sdk/CMakeLists.txt
mkdir vst3sdk/build
