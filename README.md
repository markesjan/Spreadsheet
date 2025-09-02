# Spreadsheet

A lightweight spreadsheet backend implemented in modern C++20, built with CMake.
The project provides the core functionality for managing and evaluating spreadsheet data.

## Requirements

- **C++20** compatible compiler
- **CMake** ≥ 3.28

## Build and run

```
# Create and enter the build directory
mkdir build && cd build

# Configure the project (choose Debug or Release)
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build using multiple threads (adjust -j to match your CPU threads)
cmake --build . -j12

# Run the executable
./Spreadsheet
```