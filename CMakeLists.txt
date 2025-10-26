cmake_minimum_required(VERSION 4.0)
project(cppreuse LANGUAGES CXX)

# Enable Fetch content
include(FetchContent)

# Fetch GSL library
FetchContent_Declare(
  GSL
  GIT_REPOSITORY https://github.com/microsoft/GSL.git
  GIT_TAG        v4.1.0  
  GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(GSL)

find_package(TBB REQUIRED)

if(ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_EXE NAMES clang-tidy-20 clang-tidy)
  if(CLANG_TIDY_EXE)
    message(STATUS "Found clang-tidy: ${CLANG_TIDY_EXE}")
    # Use the wrapper form so clang-tidy reads compilation database
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--header-filter=.*")
  else()
    message(STATUS "clang-tidy not found; skipping CMAKE_CXX_CLANG_TIDY")
  endif()
endif()

# For every program add the corresponding subdirectory here
add_subdirectory(squares)
add_subdirectory(sqtransform)
add_subdirectory(wordfreq)
