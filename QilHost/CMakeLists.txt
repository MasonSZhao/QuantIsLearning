# Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

# CMakeList.txt : CMake project for QilHost, include source and define project specific logic here.

# Set the C++ standard.
set(CMAKE_CXX_STANDARD 20)

# Glob all files ended with .h and .cpp in the folders.
file (GLOB QILHOST_SRCS CONFIGURE_DEPENDS "src/QilHost*.cpp")
file (GLOB QILHOST_HEADERS CONFIGURE_DEPENDS "include/QilHost*.h")

# Add source to this project's executable.
add_executable (
	QilHostExecute
	"apps/QilHost.cpp" 
	"apps/QilHost.h"
 		${QILHOST_SRCS}
	${QILHOST_HEADERS}
)

# Add source to the project's static library.
add_library(
	QilHostStatic
	STATIC
		${QILHOST_SRCS}
	${QILHOST_HEADERS}
)

target_include_directories(
	QilHostStatic 
	PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"	
)

# Test option
set(QILHOST_BUILD_TESTS ON)

if (QILHOST_BUILD_TESTS)

	# Enable testing for current directory and below.
	enable_testing()

	# Add a subdirectory to the build.
	add_subdirectory("tests")

endif()
