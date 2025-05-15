# PopWork
[![Build Status](https://github.com/Electr0Gunner/PopWork/actions/workflows/build.yml/badge.svg)](https://github.com/Electr0Gunner/PopWork/actions/workflows/build.yml) ![Repo size](https://img.shields.io/github/repo-size/Electr0Gunner/PopWork) ![Last commit](https://img.shields.io/github/last-commit/Electr0Gunner/PopWork)

> An updated version of PopCap's SexyAppFramework, which aims to add more features than usual.

## Features
- **SDL3** rendering instead of plain old DirectDraw
- **x64** support
- **OpenAL** sound system, replacing the old DirectSound
- Replaced **zlib, libpng, libjpeg, ~~JPEG2000~~** with **stb_image**

## Third-party libraries
> see THIRD_PARTY_NOTICES.txt

## Building
The building process is the same as every single CMake project, just run:
```
cmake -S . -B build -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release -A x64
cmake --build build --config Release
```
, assuming you want to build for **x64, Release**.