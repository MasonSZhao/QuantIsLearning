# Copyright (c) 2025-present Mason Zhao MasonSZhao@qq.com

# Set the C++ standard.
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(Catch2	URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.11.0.tar.gz) # GIT_REPOSITORY is painful to fetch when network is indirect, change as you wish.
FetchContent_MakeAvailable(Catch2)

# Load and run CMake code from a file or module.
include(CTest)
include(Catch)

# Define the target
add_executable(TestQilHostFileTd "TestQilHostFileTd.cpp")

# Specify that the target uses the Catch2 library and needs this library to provide a main function for running test cases.
target_link_libraries(TestQilHostFileTd PRIVATE Catch2::Catch2WithMain)
target_link_libraries(TestQilHostFileTd PUBLIC QilHostStatic)

# Catch2 helper function that registers each Catch2 TEST_CASE as a single CTest test, which is then run in a separate process. 
catch_discover_tests(TestQilHostFileTd)

# Define the target
add_executable(TestQilHostSecurity "TestQilHostSecurity.cpp")

# Specify that the target uses the Catch2 library and needs this library to provide a main function for running test cases.
target_link_libraries(TestQilHostSecurity PRIVATE Catch2::Catch2WithMain)
target_link_libraries(TestQilHostSecurity PUBLIC QilHostStatic)

# Catch2 helper function that registers each Catch2 TEST_CASE as a single CTest test, which is then run in a separate process. 
catch_discover_tests(TestQilHostSecurity)

# Define the target
add_executable(TestQilHostTech "TestQilHostTech.cpp")

# Specify that the target uses the Catch2 library and needs this library to provide a main function for running test cases.
target_link_libraries(TestQilHostTech PRIVATE Catch2::Catch2WithMain)
target_link_libraries(TestQilHostTech PUBLIC QilHostStatic)

# Catch2 helper function that registers each Catch2 TEST_CASE as a single CTest test, which is then run in a separate process. 
catch_discover_tests(TestQilHostTech)
