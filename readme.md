# simx


simx is a discrete-event simulation framework for C++20.


Processes are defined as functions receiving `simx::SimX<> &` as their first argument and returning `simx::Promise`.
Each process is executed as a coroutine.
Thus, this framework requires C++20.
A short example simulating two clocks ticking in different time intervals looks like this:

```c++
#include <iostream>
#include <string>

#include "../core/simx.hpp"

using TimeType = long;
using Sim = simx::SimX<TimeType>;
using Promise = simx::Promise;


Promise ClockProc(Sim &sim, const std::string &name, long delay) {
    while (true) {
        std::cout<<"time: "<<sim.Now()<<", "<<name<<std::endl;
        co_await sim.Timeout(delay);
    }
}


int main(){
    Sim sim;
    auto p0 = ClockProc(sim, "slow", 5);
    auto p1 = ClockProc(sim, "fast", 3);
    sim.Run(20);
    return 0;
}

```

When run, the following output is generated:

```text
time: 0, slow
time: 0, fast
time: 3, fast
time: 5, fast
time: 6, fast
time: 9, fast
time: 10, fast
time: 12, fast
time: 15, fast
time: 15, fast
time: 18, fast
```


This project uses CMake.
To build and execute the clocks example, run the following commands:

```shell
cmake -B build
cmake --build build
build/examples/clocks
```

The CMake configuration has been tested with GCC (version 10 or later), Clang (version 14 or later) and MSVC.
If such a version is available under a different name (for example `g++-10`), you can try `CXX=g++-10 cmake ..` instead of just `cmake ..` to set the C++ compiler command.
When using an MSVC compiler, it must be of version 19.28 or later (Visual Studio 2019 version 16.8 or later).
Contributions to improve compiler support are welcome!

If you want to use simx in your project, the easiest option is to use CMake with FetchContent.
A simple configuration looks like this:

```cmake
cmake_minimum_required(VERSION 3.14)

project(my_app)

include(FetchContent)

FetchContent_Declare(simx
    GIT_REPOSITORY https://github.com/wwwHui/simx
    GIT_TAG        50dc6ed5e75f2942f534c55fdcbd688d6fcff6e8) # replace with latest revision

FetchContent_MakeAvailable(simx)

add_executable(app app.cpp)
target_link_libraries(app PRIVATE simx)
```

Replace the commit hash with the latest commit hash of simx accordingly.


## Reference

[SimCpp20](https://github.com/fschuetz04/simcpp20) is a discrete-event simulation framework for C++20. Actually, I developed Simx because I encountered a memory leak in a traffic project based on SimCpp20, and I didn't have the capability to solve that issue.

[CppCoroutines](https://github.com/bennyhuo/CppCoroutines)

## Copyright and License

Copyright © 2023 hui.

Licensed under the MIT License.
See the `LICENSE` file for details.