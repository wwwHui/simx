
# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.14)  

add_definitions(-DDEV)  # 宏定义 DEV
# add_definitions(-DDEV_PASSENGER_ID=7)



# 设置 C++ 标准
# set(CMAKE_CXX_STANDARD 20)
# SET(CMAKE_C_COMPILER "/usr/bin/gcc-10")
# SET(CMAKE_CXX_COMPILER "/usr/bin/g++-10")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")


set(PROJECT_NAME simx)
message(STATUS "Project name: ${PROJECT_NAME}")
project(${PROJECT_NAME}
    VERSION      0.1.0 
    DESCRIPTION  "simx: Discrete Event Simulation System"
    LANGUAGES    CXX)

# 添加核心源文件
message(STATUS "add file core")
# file(GLOB_RECURSE CORE_SOURCES "core/*.cpp")
add_subdirectory(core)

# 添加测试源文件
# file(GLOB TEST_SOURCES "tests/*.cpp")
add_subdirectory(tests)
add_subdirectory(examples)


# # 添加可执行文件
# add_executable(Tests ${CORE_SOURCES} ${TEST_SOURCES})


# # 添加测试
# enable_testing()
# add_test(NAME Tests COMMAND build/Tests)


# FetchContent_Declare(fmt
#         URL https://github.com/fmtlib/fmt
#         GIT_TAG        f5e54359df4c26b6230fc61d38aa294581393084)
# FetchContent_MakeAvailable(fmt)
