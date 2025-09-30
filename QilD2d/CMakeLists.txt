# Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

# CMakeList.txt : CMake project for QilHost, include source and define project specific logic here.

# Set the C++ standard.
set(CMAKE_CXX_STANDARD 20)

# https://cmake.org/cmake/help/v2.8.8/cmake.html Build an executable with a WinMain entry point on windows.
set(CMAKE_WIN32_EXECUTABLE TRUE) # When this property is set to true the executable when linked on Windows will be created with a WinMain() entry point instead of of just main().This makes it a GUI executable instead of a console application.

# Copy font files to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/AlibabaPuHuiTi-3-55-Regular.ttf DESTINATION ${CMAKE_BINARY_DIR})

# Glob all files ended with .h and .cpp in the folders.
file (GLOB QILD2D_SRCS CONFIGURE_DEPENDS "src/QilD2d*.cpp")
file (GLOB QILD2D_HEADERS CONFIGURE_DEPENDS "include/QilD2d*.h")

# Add source to this project's executable.
add_executable (
	QilD2dExecute
	"apps/QilD2d.cpp" 
	"apps/QilD2d.h"
	${QILD2D_SRCS}
	${QILD2D_HEADERS}
)

target_link_libraries(QilD2dExecute PUBLIC QilHostStatic)
