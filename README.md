# Lily Engine

<div align="center">
  <img src="./docs/lily.png" align="center" />
</div>

A simple template boilerplate for Raylib game library that I always (mostly) use and keep repeating same thing over and over again, 
this template focus only on 2D.

Why I name it lily? idk.

## Features

- [X] Scene System (no transition yet)
- [X] Centralized Memory Management
- [X] Packaging Assets (as zip file for now)
- [X] Dynamic Array
- [X] Configuration file with .ini
- [X] Timer
- [X] Tween System
- [X] 2D Rendering Pipeline
- [X] Assets Manager
- [ ] UI Helper
- [ ] Camera Helper

## Build

To build make sure you have:
- meson build system
- 7z (packaging)
- raylib (with meson.build in it, the one I use is self-hosted, i will publish it later)
- bash
- makefile (if you lazy like me)

```
# Make the desktop build
make desktop

# Build the thing and put it into dist folder
make build
```

## License

This project is currently licensed as MIT
