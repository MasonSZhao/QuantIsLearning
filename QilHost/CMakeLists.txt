# Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

# CMakeList.txt : CMake project for QilHost, include source and define project specific logic here.

# Set the C++ standard.
set(CMAKE_CXX_STANDARD 20)

# Add source to this project's executable.
add_executable (
	QilHostExecute
	"apps/QilHost.cpp" 
	"apps/QilHost.h"
)

