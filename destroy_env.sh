#!/bin/bash
echo "Moving vst3sdk/public.sdk/samples/vst/mathreverb folder into ./ as mathreverb_source"
mv vst3sdk/public.sdk/samples/vst/mathreverb mathreverb_source

echo "Removing '# MathReverb plugin' line from vst3sdk/CMakeLists.txt"
sed -i '\%# MathReverb plugin%d' vst3sdk/CMakeLists.txt

echo "Removing 'add_subdirectory(public.sdk/samples/vst/mathreverb)' line from vst3sdk/CMakeLists.txt"
sed -i '\%add_subdirectory(public.sdk/samples/vst/mathreverb)%d' vst3sdk/CMakeLists.txt

echo "Removing vst3sdk/build directory"
rm -rf vst3sdk/build
