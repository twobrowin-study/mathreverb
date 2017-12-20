#!/bin/bash

cd ../

if [ $1 == '--vst2' ]; then
    echo "Moving VST2_SDK directory into vst3sdk"
    cp -r VST2_SDK/. vst3sdk/.
    rm -r VST2_SDK
    
    echo "Changing vst3sdk/CMakeLists.txt to compile VST2"
    sed -i '\%option(SMTG_CREATE_VST2_VERSION "Use VST2" OFF)%coption(SMTG_CREATE_VST2_VERSION "Use VST2" ON)' vst3sdk/CMakeLists.txt
fi

echo "Moving mathreverb_source directory into vst3sdk/public.sdk/samples/vst/ as mathreverb"
mv mathreverb_source vst3sdk/public.sdk/samples/vst/mathreverb

echo "Changing vst3sdk/public.sdk/samples/vst/mathreverb/.git repository binding"
sed -i '\%gitdir: ../.git/modules/mathreverb_source%c\gitdir: ../../../../../.git/modules/mathreverb_source' vst3sdk/public.sdk/samples/vst/mathreverb/.git

echo "Changing .git/modules/mathreverb_source/config repository binding"
sed -i '\%worktree = ../../../mathreverb_source%c\worktree = ../../../vst3sdk/public.sdk/samples/vst/mathreverb' .git/modules/mathreverb_source/config

echo "Makind vst3sdk/build directory"
mkdir vst3sdk/build
