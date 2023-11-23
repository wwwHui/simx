
add_library(simx INTERFACE)

target_include_directories(simx INTERFACE ${PROJECT_SOURCE_DIR}/core)

# 判断编译器类型
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # 在 MSVC 编译器下启用协程选项
    target_compile_options(simx INTERFACE "/await")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # 在 Clang 编译器下启用协程选项
    target_compile_options(simx INTERFACE "-fcoroutines")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "10")
      message(WARNING "GCC Version is ${CMAKE_CXX_COMPILER_VERSION}, simx requires GCC 10 or later ")
    endif()
    # 在 GNU 编译器下启用协程选项
    target_compile_options(simx INTERFACE "-fcoroutines")
else()
    message(WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}. Unable to enable coroutines.")
endif()
