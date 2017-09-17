# MathReverb
  This repository contains few Bash scripts for building MathReverb VST3 plugin under Windows.

## Clonning
  Run `git clone --recursive https://github.com/TwoBroWin/mathreverb.git`

## Requires
  * Microsoft Windows (7-10 will do)
  * [Cygwin](https://cygwin.com/) Bash for Windows realization
  * Microsoft Visual Studio 2015 - 2017
  * [CMake](https://cmake.org/) for Windows

## Release script
  This script makes all need work to create VST3 sdk environment, Cmake and build plugin into .vst3 file.

  Usage: `./release.sh [keys]`

### Release keys
  * `-r` - Clear build directory and run CMake again (build all libs again)
  * `-d` - Destroy environment after building (only plugin .vst3 will be after)
  * `-m` - Move plugin into standart VST3 folder (C:\Program Files\Common Files\VST3)
  * `-u [branch]` - Update mathreverb_source repository (if branch is not set, update will be on master brach)
  * `-f filename` - Start FL Studio 64 with given filename (if there is no given filename ignoring)

## Create and Destroy environment
  Environment creates automatically when Release script is ran, if key -d is set it will be destroyed.
  But you can create or destroy environment by using `./create_env.sh` or `./destroy_env.sh`

## Update MathReverb Source code
  As base of plugin mathreverb_source (or mathreverb) can be pulled at any environment condition.
  Just run `./update_src.sh master`

## Output
  Plugin file is `mathreverb.vst3`. **Project works only in 64 bit mode!**.

## Docs
  Some semi-documentation in Russian language is [here](https://github.com/TwoBroWin/cookbook/tree/master/VST3).
