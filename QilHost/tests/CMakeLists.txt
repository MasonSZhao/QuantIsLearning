# Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

# Set the C++ standard.
set(CMAKE_CXX_STANDARD 20)

## github: https://github.com/catchorg/Catch2
#find_package(Catch2 REQUIRED)

include(FetchContent)

FetchContent_Declare(
	Catch2	
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v3.10.0
)

FetchContent_MakeAvailable(Catch2)

# Load and run CMake code from a file or module.
include(CTest)
include(Catch)

# Define the target
add_executable(TestQilHostSecurity "TestQilHostSecurity.cpp")

# Specify that the target uses the Catch2 library and needs this library to provide a main function for running test cases.
target_link_libraries(TestQilHostSecurity PRIVATE Catch2::Catch2WithMain)
target_link_libraries(TestQilHostSecurity PUBLIC QilHostStatic)

# Catch2 helper function that registers each Catch2 TEST_CASE as a single CTest test, which is then run in a separate process. 
catch_discover_tests(TestQilHostSecurity)
