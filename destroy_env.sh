#!/bin/bash
mv vst3sdk/public.sdk/samples/vst/mathreverb mathreverb_source
sed -i '\%# MathReverb plugin%d' vst3sdk/CMakeLists.txt
sed -i '\%add_subdirectory(public.sdk/samples/vst/mathreverb)%d' vst3sdk/CMakeLists.txt
rm -rf vst3sdk/build
