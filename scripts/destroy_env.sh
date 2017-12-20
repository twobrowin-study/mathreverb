#!/bin/bash

if [ $1 == '--vst2' ]; then
    echo "Returning VST2_SDK directory from vst3sdk"
    mkdir VST2_SDK
    mkdir VST2_SDK/pluginterfaces
    mkdir VST2_SDK/public.sdk
    mkdir VST2_SDK/public.sdk/source
    mv vst3sdk/pluginterfaces/vst2.x VST2_SDK/pluginterfaces/vst2.x
    mv vst3sdk/public.sdk/source/vst2.x VST2_SDK/public.sdk/source/vst2.x
    
    echo "Changing vst3sdk/CMakeLists.txt to compile VST3"
    sed -i '\%option(SMTG_CREATE_VST2_VERSION "Use VST2" ON)%coption(SMTG_CREATE_VST2_VERSION "Use VST2" OFF)' vst3sdk/CMakeLists.txt
fi

echo "Moving vst3sdk/public.sdk/samples/vst/mathreverb folder into ./ as mathreverb_source"
mv vst3sdk/public.sdk/samples/vst/mathreverb mathreverb_source

echo "Changing mathreverb_source/.git repository binding"
sed -i '\%gitdir: ../../../../../.git/modules/mathreverb_source%c\gitdir: ../.git/modules/mathreverb_source' mathreverb_source/.git

echo "Changing .git/modules/mathreverb_source/config repository binding"
sed -i '\%worktree = ../../../vst3sdk/public.sdk/samples/vst/mathreverb%c\worktree = ../../../mathreverb_source' .git/modules/mathreverb_source/config

echo "Removing vst3sdk/build directory"
rm -rf vst3sdk/build
