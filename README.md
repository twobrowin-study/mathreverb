# MathReverb
  This repository contains few Bash scripts for building MathReverb VST3 plugin under Windows.

## Clonning
  Run `git clone --recursive https://github.com/twobrowin-study/mathreverb.git`

## Requires
  * Microsoft Windows x64 (7-10 will do)
  * [Cygwin](https://cygwin.com/) Bash for Windows realization
  * Microsoft Visual Studio 2015 - 2017
  * [CMake](https://cmake.org/) for Windows

## Release script
  This script makes all need work to create VST3 sdk environment, Cmake and build plugin into .vst3 file.
  Plugin will be build in x64 and x32 bit.

  Usage: `./release.sh [keys]`

### Release keys
  * `-m` - Move plugin into standart VST folder (your DAW will find it with no problem)
  * `-u [remote branch]` - Update mathreverb_source repository (if not set - will be used origin master)
  * `-f filename` - Start FL Studio 64 with given filename (if there is no given filename ignoring)
  * `--vst2` - Compile as VST2 plugin
  * `--win64` - Compile in 64 bit mode

## Build project
  You can manualy build project via `./build.sh generation build_dir move_dir [--vst2]`, where generation can be Win32 or Win64.

## Create and Destroy environment
  Environment creates automatically when Release script is ran, if key -d is set it will be destroyed.
  But you can create or destroy environment by using `./create_env.sh [--vst2]` or `./destroy_env.sh [--vst2]`

## Update MathReverb Source code
  As base of plugin mathreverb_source (or mathreverb) can be pulled at any environment condition.
  To update origin/master just run `./update_src.sh [remote branch]`

## Output
  Plugin files is `mathreverb.vst3` in VST3 mode or `mathreverb.dll` in VST2 mode.
