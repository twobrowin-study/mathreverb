#!/bin/bash
echo "Moving mathreverb_source folder into vst3sdk/public.sdk/samples/vst/ as mathreverb"
mv mathreverb_source vst3sdk/public.sdk/samples/vst/mathreverb

echo "Changing vst3sdk/public.sdk/samples/vst/mathreverb/.git repository binding"
sed -i '\%gitdir: ../.git/modules/mathreverb_source%c\gitdir: ../../../../../.git/modules/mathreverb_source' vst3sdk/public.sdk/samples/vst/mathreverb/.git

echo "Changing .git/modules/mathreverb_source/config repository binding"
sed -i '\%worktree = ../../../mathreverb_source%c\worktree = ../../../vst3sdk/public.sdk/samples/vst/mathreverb' .git/modules/mathreverb_source/config

echo "Makind vst3sdk/build directory"
mkdir vst3sdk/build
