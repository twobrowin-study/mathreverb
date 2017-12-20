#!/bin/bash

# Keys and varibles section
while [ -n "$1" ]; do
  case "$1" in
    -m) move=$1;;
    -u) remote=$2
        branch=$3;;
    -f) arg="$2"
        if [ -n "$arg" ] &&
           [ "${arg::1}" != "-" ]; then
            frutyfile="$arg"
        else
            echo "Didn't find filename for FL Studio - ignoring"
        fi;;
    --vst2) vst2_flag=$1;;
    --win64) win64=$1;;
  esac
  shift
done

# Update mathreverb_source if need to
if [ "$remote" ] && [ "$branch" ]; then
    echo "Updating mathreverb_source on $remote/$branch"
    ./scripts/update_src.sh "$remote" "$branch"
fi

# if VST2 set
if [ "$vst2_flag" ]; then
    echo "Selected VST2 mode"
fi

# Create environment
echo "Creating environment"
./scripts/create_env.sh $vst2_flag

# Setting Win32 params
arc='Win32'
mvdir="none"
if [ "$move" ]; then
    mvdir='/cygdrive/c/Program Files (x86)/Common Files/VST3'
    if [ "$vst2_flag" ]; then
        mvdir='/cygdrive/c/Program Files (x86)/VstPlugins'
    fi
fi

# Setting Win64 params if need to
if [ "$win64" ]; then
    echo "Selected 64 bit mode"
    arc='Win64'
    mvdir="none"
    if [ "$move" ]; then
        mvdir='/cygdrive/c/Program Files/Common Files/VST3'
        if [ "$vst2_flag" ]; then
            mvdir='/cygdrive/c/Program Files/Common Files/VST2'
        fi
    fi
fi

# Building project
echo "Building"
./scripts/build.sh $arc ./vst3sdk/build "$mvdir" $vst2_flag

# Destroy environment
echo "Destroy environment"
./scripts/destroy_env.sh $vst2_flag

# Start FL Studio with given filename
if [ "$frutyfile" ]; then
  echo "Starting FL Studio"
  fl64.exe "$frutyfile"
fi
