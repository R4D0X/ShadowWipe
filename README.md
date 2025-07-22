# ShadowWipe

![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows%2010%2F11-blue)
![Language](https://img.shields.io/badge/language-C++17-red)

ShadowWipe is a high-precision anti-forensics tool designed to systematically eliminate traces of user activity and system metadata from Windows environments. By targeting a wide range of forensic artifacts—including volume shadow copies, shellbags, registry entries, browser caches, temporary files, and alternate data streams (ADS)—ShadowWipe ensures that post-incident investigations yield minimal usable evidence.
Built for researchers, privacy advocates, and advanced users, ShadowWipe automates the process of evidence elimination and artifact removal, providing a reliable method for forensic evasion in test or controlled environments.

- Shadow copies and restore points
- Shellbags and recent documents
- Browser history, cookies, and cache (Chrome, Firefox, Edge, Brave, Opera, Vivaldi)
- Alternate Data Streams (ADS)
- Registry traces (RunMRU, Typed URLs, MUICache, UserAssist, etc.)
- Event logs, prefetch files, temp folders, and clipboard data
- USN journal and recycle bin contents

## Features

- Full system trace wiping
- Shadow copy and backup deletion
- Browser-specific cleanup
- Registry cleaning (for commonly used forensic keys)
- Optionally clears pagefile on shutdown
- Minimal and fast – no external dependencies

## Requirements

- Windows 10/11 (x64)
- Administrator privileges



## Build Instructions

Compile using Visual Studio or `g++` with C++17 support:

```bash
g++ -std=c++17 -o ShadowWipe.exe ShadowWipe.cpp
```
**Anti-Forensics Tool**
> ⚠️ **Disclaimer:** This tool is intended for ethical research, educational purposes, and authorized security testing only. Misuse may be illegal and unethical.
