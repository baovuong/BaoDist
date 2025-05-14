# JUCE Distortion

A simple plugin demonstrating different distortion algorithms.

## Prerequisites

* JUCE 8.x (https://github.com/juce-framework/JUCE)

*from JUCE project link*:

* C++ Standard: 17
* **macOS/iOS**: Xcode 12.4 (Intel macOS 10.15.4, Apple Silicon macOS 11.0)
* **Windows**: Visual Studio 2019/2022 (Windows 10)
* **Linux**: g++ 7.0 or Clang 6.0 (for a full list of dependencies, see here).

## How To Build

### Windows

#### via Visual Studio 2022 (IDE)

1. Launch Visual Studio 2022
2. Open .sln file
3. Switch to `Release`
4. Run `Build Solution` (Ctrl+Shift+B)

#### via Visual Studio 2022 (Powershell)

```
> . "C:\Program Files\Microsoft Visual Studio\2022\{Community|Professional}\Common7\Tools\Launch-VsDevShell.ps1" 
> msbuild {juce project directory}\BevyDistortion.sln
```

### Mac OS X

#### via XCode (IDE)

1. Launch XCode
2. Open  `{juce project directory}/Builds/MacOSX/BevyDistortion.xcodeproj`
3. Build

#### via XCode (CLI)

```
> cd {juce project directory}/Builds/MacOSX/
> xcodebuild -list -project BevyDistortion.xcodeproj
```

### Linux

```
> cd {juce project directory}/Builds/LinuxMakefile
> make
```