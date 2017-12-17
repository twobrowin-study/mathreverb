#!/bin/bash

# Keys and varibles section
while [ -n "$1" ]; do
  case "$1" in
    -d) destroy=true;;
    -m) mvdir64=/cygdrive/c/"Program Files"/"Common Files"/VST3/
        mvdir32=/cygdrive/c/"Program Files (x86)"/"Common Files"/VST3/;;
    -u) remote=$2
        branch=$3;;
    -f) arg="$2"
        if [ -n "$arg" ] &&
           [ "${arg::1}" != "-" ]; then
            frutyfile="$arg"
        else
            echo "Didn't find filename for FL Studio - ignoring"
        fi;;
  esac
  shift
done

# Create environment if need to
if [ ! -d vst3sdk/public.sdk/samples/vst/mathreverb ]; then
  echo "Creating environment"
  ./create_env.sh
fi

# Update mathreverb_source if need to
if [ "$remote" ] && [ "$branch" ]; then
    echo "Updating mathreverb_source on $remote/$branch"
    ./update_src.sh "$remote" "$branch"
fi

# Setting base directories if need to
if [ -z "$mvdir64" ] && [ -z "$mvdir32" ]; then
    mvdir64="x64"
    mvdir32="x32"
fi

# Build project in 64bit
echo "Build in 64 bit mode"
./build.sh Win64 ./vst3sdk/build $mvdir64

# Build project in 32bit
echo "Build in 32 bit mode"
./build.sh Win32 ./vst3sdk/build $mvdir32

# Destroy environment if need to
if [ "$destroy" ]; then
  echo "Destroy environment"
  ./destroy_env.sh
fi

# Start FL Studio with given filename
if [ "$frutyfile" ]; then
  echo "Starting FL Studio"
  fl64.exe "$frutyfile"
fi
