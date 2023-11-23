file(GLOB_RECURSE TARGETS "./*.cpp")

# 添加测试
enable_testing()

foreach(FILE ${TARGETS})
    message(STATUS "TESTS FILE: ${FILE}.")
    get_filename_component(TARGET ${FILE} NAME_WE)
    message(STATUS "TESTS TARGET: ${TARGET}.")
    add_executable(${TARGET} ${TARGET}.cpp)
    target_link_libraries(${TARGET} PRIVATE simx)

    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        # 在 MSVC 编译器下启用协程选项
        target_compile_options(${TARGET} PRIVATE "/await")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # 在 Clang 编译器下启用协程选项
        target_compile_options(${TARGET} PRIVATE "-fcoroutines")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # 在 Clang 编译器下启用协程选项
        target_compile_options(${TARGET} PRIVATE "-fcoroutines")
    else()
        message(WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}. Unable to enable coroutines.")
    endif()

    add_test(NAME ${TARGET} COMMAND build/tests/${TARGET})

endforeach()
