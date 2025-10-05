# Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

# CMakeList.txt : Top-level CMake project file, do global configuration and include sub-projects here.

cmake_minimum_required (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("QuantIsLearning")

# Include sub-projects.
add_subdirectory ("QilHost")

# Include sub-projects.
add_subdirectory ("QilHttp")

# Include sub-projects.
add_subdirectory ("QilD2d")
