/*************************************************************************************************************
@! Copyright(c) 2023
@Time    :  2023-11-11 18:41:41
@File    :  test.cpp
@Author  :  hui
@Version :  V0.1
@Desc    :  说明
**************************************************************************************************************/
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

/*

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

*/