# MathReverb
  This repository contains few Bash scripts for building MathReverb VST3 plugin under Windows.

## Clonning
  Run `git clone --recursive https://github.com/TwoBroWin/mathreverb.git`

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
  * `-d` - Destroy environment after building (only plugins .vst3 will be after in x64 and x86 directories)
  * `-m` - Move plugin into standart VST3 folder (C:\Program Files\Common Files\VST3 and C:\Program Files (x86)\Common Files\VST3)
  * `-u [remote branch]` - Update mathreverb_source repository (if not set - will be used origin master)
  * `-f filename` - Start FL Studio 64 with given filename (if there is no given filename ignoring)

## Build project
  You can manualy build project via `./build.sh generation build_dir move_dir`, where generation can be Win32 or Win64.

## Create and Destroy environment
  Environment creates automatically when Release script is ran, if key -d is set it will be destroyed.
  But you can create or destroy environment by using `./create_env.sh` or `./destroy_env.sh`

## Update MathReverb Source code
  As base of plugin mathreverb_source (or mathreverb) can be pulled at any environment condition.
  To update origin/master just run `./update_src.sh [remote branch]`

## Output
  Plugin files is `mathreverb.vst3`, located in x64 and x86 directories.

## Docs
  Some semi-documentation on Russian language is [here](https://github.com/TwoBroWin/cookbook/tree/master/VST3) and [here](https://drive.google.com/open?id=1aXpuvaWZaVSo70sdoA_K74pKW21VSRPT).
