# Stupid Pong

## What?
*Stupid Pong* is a poor implementation of a *Pong* style game, written in C++ using the SDL2 library.

## Why?
I wanted to learn more about game development in general, and SDL2 in particular. I've never written a game before, and I found the 
execution semantics (e.g. game loop, display refresh, input management, etc.) to be a refreshing break from the sort of development
work I typically do.

I also challenged myself to build this project using CMake and vim.

## How?
To compile, you'll need a working C++ compiler (clang ?? / gcc ?? / MSVC 19) and vcpkg. Using vcpkg install the SDL2 library and then define 
CMAKE_TOOLCHAIN_FILE when invoking cmake. For example, let's assume that you are going to build in a folder called 'build' positions as a peer,
to the 'src' folder, and let's further assume that you've install vcpkg to a peer folder of your project folder. Your directory tree would look
something like:

```
Root
   |-- vcpkg
   |-- spong
           |-- build
           |-- src
```

In this case, while in the `build` folder, execute the following command:

`cmake ../src -DCMAKE_TOOLCHAIN_FILE=../../vcpkg/scripts/buildsystems/vcpkg.cmake`

Flip the direction of the slashes around on Windows.