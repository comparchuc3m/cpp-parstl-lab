# C++ Parallel STL Lab

This repository contains educational examples demonstrating the use of C++23 parallel algorithms from the Standard Template Library (STL). The project includes three different programs that compare sequential and parallel execution strategies using `std::execution` policies.

## Overview

The project showcases practical applications of parallel programming in C++ using:
- C++23 standard parallel execution policies (`std::execution::seq` and `std::execution::par`)
- Intel Threading Building Blocks (TBB) as the parallel backend
- Modern C++ features including `std::print`, `std::println`, and structured bindings

## Prerequisites

- **CMake** version 3.30 or higher
- **C++23** compliant compiler (GCC or Clang)
- **Intel TBB** (Threading Building Blocks)
- **Ninja** build system
- **Microsoft GSL** (Guidelines Support Library) - fetched automatically by CMake

## Project Contents

The repository contains three demonstration programs:

### 1. `squares` - In-place Vector Squaring with `for_each`

**Location:** `squares/`

Demonstrates in-place transformation of vector elements using `std::for_each`:
- Generates a large vector of random doubles (100 million elements)
- Squares each element in place using both sequential and parallel execution
- Compares execution times between sequential (`std::execution::seq`) and parallel (`std::execution::par`) policies
- Uses lambda with reference parameter to modify elements in place

**Key Algorithm:** `std::for_each` with in-place modification

### 2. `sqtransform` - Vector Transformation with `transform`

**Location:** `sqtransform/`

Demonstrates vector transformation using `std::transform`:
- Generates a large vector of random doubles (100 million elements)
- Squares each element and stores results in a separate output vector
- Compares execution times between sequential and parallel execution policies
- Uses `std::transform` to create a new result vector without modifying the original

**Key Algorithm:** `std::transform` for element-wise transformation

### 3. `wordfreq` - Word Frequency Counter

**Location:** `wordfreq/`

Demonstrates parallel text processing using `std::transform_reduce`:
- Contains two implementations: sequential (`wordseq`) and parallel (`wordpar`)
- Reads words from a text file (e.g., `quijote.txt` - Don Quixote in Spanish)
- Counts word frequencies using a map-reduce pattern
- Converts words to lowercase for case-insensitive counting
- Sorts results by frequency and displays the top 50 most common words
- Compares execution times between sequential and parallel implementations

**Key Algorithms:** 
- `std::transform_reduce` for parallel word counting
- `std::sort` for sorting by frequency

**Input File:** The repository includes `quijote.txt` (2.2 MB), the Spanish text of Don Quixote, as sample input data.

## Building the Project

The project uses CMake with presets for configuration:

```bash
# Configure with default preset
cmake --preset default

# Build all programs in Release mode
cmake --build out/build/default --config Release

# Or build specific programs
cmake --build out/build/default --config Release --target squares
cmake --build out/build/default --config Release --target sqtransform
cmake --build out/build/default --config Release --target wordseq
cmake --build out/build/default --config Release --target wordpar
```

### Build Configurations

- **gcc-debug**: Debug build with GCC
- **gcc-release**: Optimized release build with GCC
- **clang-tidy-debug**: Debug build with clang-tidy static analysis enabled
- **clang-tidy-release**: Release build with clang-tidy static analysis enabled

## Running the Programs

### Squares and Sqtransform

```bash
# Run from the build directory
./out/build/default/Release/squares
./out/build/default/Release/sqtransform
```

Both programs will output:
- Execution time for sequential version
- Number of squared values exceeding 2500.0
- Execution time for parallel version
- Performance comparison

### Word Frequency Counter

```bash
# Sequential version
./out/build/default/Release/wordseq quijote.txt

# Parallel version
./out/build/default/Release/wordpar quijote.txt
```

Output includes:
- Total word count
- Execution time for word frequency counting
- Execution time for sorting
- Top 50 most frequent words with their counts

## Learning Objectives

This lab helps understand:
1. **Parallel Execution Policies**: How `std::execution::seq` and `std::execution::par` affect performance
2. **Algorithm Selection**: When to use `for_each`, `transform`, or `transform_reduce`
3. **Performance Comparison**: Measuring and comparing sequential vs. parallel execution times
4. **Real-world Applications**: Text processing, numerical computations, and data transformations
5. **Modern C++ Features**: Using C++23 standard library features for parallel programming

## Code Quality

The project is configured with:
- Strict compiler warnings (`-Wall -Wextra -Werror -pedantic`)
- C++23 standard compliance
- Optional clang-tidy static analysis
- clang-format for code formatting

## License

Apache License Version 2.0 - See [LICENSE](LICENSE) file for details.
