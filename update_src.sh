#!/bin/sh

if [ -d mathreverb_source ];then
  srcdir=mathreverb_source
elif [ -d vst3sdk/public.sdk/samples/vst/mathreverb ]; then
  srcdir=vst3sdk/public.sdk/samples/vst/mathreverb
fi

if [ "$srcdir" ]; then
  echo "Entering mathreverb source directory $srcdir"
  cd "$srcdir"
  git checkout master
  git pull
else
  echo "Source directory does not exists"
fi
