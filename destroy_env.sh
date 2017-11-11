#!/bin/bash
echo "Moving vst3sdk/public.sdk/samples/vst/mathreverb folder into ./ as mathreverb_source"
mv vst3sdk/public.sdk/samples/vst/mathreverb mathreverb_source

echo "Changing mathreverb_source/.git repository binding"
sed -i '\%gitdir: ../../../../../.git/modules/mathreverb_source%c\gitdir: ../.git/modules/mathreverb_source' mathreverb_source/.git

echo "Changing .git/modules/mathreverb_source/config repository binding"
sed -i '\%worktree = ../../../vst3sdk/public.sdk/samples/vst/mathreverb%c\worktree = ../../../mathreverb_source' .git/modules/mathreverb_source/config

echo "Removing vst3sdk/build directory"
rm -rf vst3sdk/build
