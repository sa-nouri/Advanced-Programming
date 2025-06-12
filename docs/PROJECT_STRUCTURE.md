# Project Structure

This document provides a detailed explanation of the repository's structure and organization.

## Directory Structure

```
Advanced-Programming/
├── assignments/           # Course assignments
│   ├── assignment-1/     # Fundamental C++ Concepts
│   ├── assignment-2/     # Recursion Implementation
│   ├── assignment-3/     # RSDL Library Development
│   ├── assignment-4/     # Restaurant Ordering Service
│   ├── assignment-5/     # C++ Operators
│   ├── assignment-6/     # Process Scheduling
│   ├── assignment-7/     # Taxi Service
│   └── assignment-8/     # Python Stack Implementation
│
├── exercises/            # Practice exercises
│   └── learncpp/        # LearnC++ exercises
│       ├── chapter_0/   # Introduction
│       ├── chapter_1/   # Basic Concepts
│       └── ...         # Additional chapters
│
├── docs/                # Documentation
│   ├── templates/      # JSON templates
│   ├── resources/      # Learning resources
│   ├── SETUP.md       # Setup guide
│   ├── CODING_STANDARDS.md  # Coding standards
│   └── PROJECT_STRUCTURE.md # This file
│
├── tools/              # Development tools
│   └── vscode/        # VSCode configuration
│
├── .gitignore         # Git ignore rules
├── LICENSE           # MIT License
├── README.md         # Main documentation
├── CONTRIBUTING.md   # Contribution guidelines
└── CHANGELOG.md      # Version history
```

## Assignment Structure

Each assignment directory follows this structure:
```
assignment-X/
├── src/              # Source files
├── include/          # Header files
├── tests/            # Test files
├── docs/             # Assignment-specific documentation
├── Makefile         # Build configuration
└── README.md        # Assignment description
```

## Exercise Structure

Each LearnC++ chapter follows this structure:
```
chapter_X/
├── exercises/        # Practice exercises
├── solutions/        # Exercise solutions
└── README.md        # Chapter overview
```

## Documentation Structure

The `docs/` directory contains:
- `templates/`: JSON templates and other template files
- `resources/`: Additional learning resources
- `SETUP.md`: Detailed setup instructions
- `CODING_STANDARDS.md`: Coding standards and best practices
- `PROJECT_STRUCTURE.md`: This file

## Development Tools

The `tools/` directory contains:
- `vscode/`: VSCode configuration files
  - `settings.json`: Editor settings
  - `launch.json`: Debug configurations
  - `tasks.json`: Build tasks

## Version Control

The repository uses Git for version control with the following conventions:
- `main` branch: Stable, production-ready code
- Feature branches: For new features and improvements
- Tags: For version releases

## Build System

- C++ projects use Make for building
- Python projects use standard Python packaging
- Each assignment includes its own build configuration

## Testing

- C++ tests use a testing framework (specified in each assignment)
- Python tests use pytest
- Test files are located in the `tests/` directory of each project 
