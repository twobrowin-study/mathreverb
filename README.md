# MathReverb
  This repository contains few Bash scripts for building MathReverb VST3 plugin under Windows

## Clonning
  Run `git clone --recursive https://github.com/TwoBroWin/mathreverb.git`

## Requires
  * Microsoft Windows (7-10 will do)
  * [Cygwin](https://cygwin.com/) or any other Bash for Windows realization (MSys or Cmder)
  * Microsoft Visual Studio 2015 - 2017
  * [CMake](https://cmake.org/) for Windows

## Release script
  This script makes all need work to create VST3 sdk environment, Cmake and build plugin into .vst3 file

  Usage `./release.sh [keys]`

### Release keys
  * `-r` - Clear build directory and run CMake again (build all libs again)
  * `-d` - Clean environment after building (only plugin .vst3 will be after)
  * `-m` - Move plugin into standart VST3 folder (C:\Program Files\Common Files\VST3)

## Output
  Plugin file is `mathreverb.vst3`. **Project works only in 64 bit mode!**
