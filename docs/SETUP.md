# Setup Guide

This guide will help you set up the development environment for working with this repository.

## Prerequisites

### C++ Development Environment
1. **Install C++ Compiler**
   - For macOS:
     ```bash
     xcode-select --install
     ```
   - For Ubuntu/Debian:
     ```bash
     sudo apt-get update
     sudo apt-get install build-essential
     ```
   - For Windows:
     - Install MinGW or Visual Studio Community Edition

2. **Install Required Libraries**
   - SDL2 (Required for Assignment 3)
     ```bash
     # macOS
     brew install sdl2
     
     # Ubuntu/Debian
     sudo apt-get install libsdl2-dev
     
     # Windows
     # Download from https://www.libsdl.org/download-2.0.php
     ```

### Python Environment (Required for Assignment 8)
1. **Install Python**
   - Download from [python.org](https://www.python.org/downloads/)
   - Minimum version: Python 3.8

2. **Install pip**
   ```bash
   # Verify pip installation
   python -m pip --version
   ```

## IDE Setup

### VSCode Configuration
1. **Install Required Extensions**
   - C/C++ Extension Pack
   - Python Extension Pack
   - Code Runner

2. **Configure VSCode Settings**
   - Copy settings from `tools/vscode/` to your VSCode settings
   - Ensure the C++ compiler path is correctly set

## Building and Running

### C++ Projects
1. **Compile a C++ Program**
   ```bash
   g++ -std=c++17 source.cpp -o output
   ```

2. **Run the Program**
   ```bash
   ./output
   ```

### Python Projects
1. **Run a Python Script**
   ```bash
   python script.py
   ```

## Common Issues and Solutions

### C++ Related
1. **Compiler Not Found**
   - Ensure the compiler is in your system PATH
   - Verify installation with `g++ --version`

2. **SDL2 Not Found**
   - Check if SDL2 is properly installed
   - Verify library path in your build configuration

### Python Related
1. **Module Not Found**
   - Ensure you're using the correct Python environment
   - Install required packages using pip

## Additional Resources
- [C++ Reference](https://en.cppreference.com/)
- [Python Documentation](https://docs.python.org/3/)
- [SDL2 Documentation](https://wiki.libsdl.org/) 
