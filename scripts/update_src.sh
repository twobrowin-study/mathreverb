#!/bin/sh

arg_remote=$1
arg_branch=$2
if [ -n "$arg_remote" ] &&
   [ "${arg_remote::1}" != "-" ] &&
   [ -n "$arg_branch" ] &&
   [ "${arg_branch::1}" != "-" ]; then
    remote="$arg_remote"
    branch="$arg_branch"
else
    remote=origin
    branch=master
fi

if [ -d mathreverb_source ];then
  srcdir=mathreverb_source
elif [ -d vst3sdk/public.sdk/samples/vst/mathreverb ]; then
  srcdir=vst3sdk/public.sdk/samples/vst/mathreverb
fi

if [ "$srcdir" ]; then
  echo "Entering mathreverb source directory $srcdir"
  cd "$srcdir"
  echo "Updating..."
  git pull $remote $branch
else
  echo "Source directory does not exists"
fi
