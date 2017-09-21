#!/bin/sh

if [ -n "$1" ]; then
    branch="$1"
else
    branch=master
fi

if [ -n "$2" ]; then
    repo="$2"
else
    repo=origin
fi
if [ -d mathreverb_source ];then
  srcdir=mathreverb_source
elif [ -d vst3sdk/public.sdk/samples/vst/mathreverb ]; then
  srcdir=vst3sdk/public.sdk/samples/vst/mathreverb
fi

if [ "$srcdir" ]; then
  echo "Entering mathreverb source directory $srcdir"
  cd "$srcdir"
  echo "Setting branch $branch"
  git checkout "$branch"
  echo "Updating..."
  git pull $repo $branch
else
  echo "Source directory does not exists"
fi
