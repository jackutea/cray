# Intro
raylib project template

# Env
0. vscode & gcc & cmake & vcpkg
1. vcpkg install raylib:x64-windows
2. install vscode CMake extension

# Configure
0. according to /.vscode txts to configure .json
1. according to CMakelists_sample.txt to create CMakelists.txt
2. manual build once
```
>> cd build
>> cmake .. 
vscode: ctrl + shift + p, cmake configure
```

# Build & Run
1. build every times
```
vscode: ctrl + shift + p, cmake build
```
2. run
```
vscode: F5
```

# FAQ
1. Q:路径有非法字符
- A:cmake --build d:/cray/build 应改为 cmake --build d:\cray\build