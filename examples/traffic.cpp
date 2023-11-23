/*************************************************************************************************************
@! Copyright(c) 2023
@Time    :  2023-11-22 21:28:10
@File    :  traffic.cpp
@Author  :  hui
@Version :  V0.1
@Desc    :  说明
**************************************************************************************************************/

#include <iostream>
#include <string>
#include <random>
#include <list>
#include <memory>

#include "../core/simx.hpp"

using TimeType = long;
using Sim = simx::SimX<TimeType>;
using Promise = simx::Promise;

struct Passenger
{
    int id;
    bool wait;
    std::string place;
    Passenger(int i): id(i) {};
};

struct Car
{
    int id, passenger_id;
    bool empty;
    std::string place;
    Car(int i): id(i) {};
};


Promise PassengerWalkEvent(Sim &sim, std::shared_ptr<Passenger> p, std::mt19937 &rng) {
    p->place = 'A';
    p->wait = false;
    printf("Time: %4ld, passenger %d at %s\n", sim.Now(), p->id, p->place.c_str());
    std::uniform_int_distribution<int> dist(30, 120);
    auto delay = dist(rng);
    co_await sim.Timeout(delay);
    p->place = 'B';
    p->wait = true;
    printf("Time: %4ld, passenger %d at %s\n", sim.Now(), p->id, p->place.c_str());
}

Promise CarEvent(Sim &sim, std::shared_ptr<Car> car, std::list<std::shared_ptr<Passenger>> &passengers, std::mt19937 &rng) {
    car->place = 'C';
    car->empty = true;
    printf("Time: %4ld, car %d at %s\n", sim.Now(), car->id, car->place.c_str());
    std::uniform_int_distribution<int> dist(30, 120);
    auto delay = dist(rng);
    co_await sim.Timeout(delay);
    car->place = 'B';
    printf("Time: %4ld, car %d at %s\n", sim.Now(), car->id, car->place.c_str());
    while (car->empty){
        for(auto &p : passengers) {
            if (p->place == "B" && p->wait) {
                p->wait = false;
                car->empty = false;
                car->passenger_id = p->id;
                break;
            }
        }
        co_await sim.Timeout(1);
    }
    printf("Time: %4ld, car %d at %s with passenger %d\n", sim.Now(), car->id, car->place.c_str(), car->passenger_id);
    delay = dist(rng);
    co_await sim.Timeout(delay);
    car->place = 'D';
    printf("Time: %4ld, car %d at %s with passenger %d\n", sim.Now(), car->id, car->place.c_str(), car->passenger_id);
}


int main(){
    Sim sim;
    std::mt19937 rng;
    std::list<std::shared_ptr<Passenger>> passengers;  //  乘客
    std::list<std::shared_ptr<Promise>> promises;
    for(int i=0; i<10; i++) {
        auto passenger = std::make_shared<Passenger>(i);
        auto p =PassengerWalkEvent(sim, passenger, rng);
        passengers.push_back(passenger);
        promises.push_back(std::make_shared<Promise>(p));

    }

    for(int i=0; i<10; i++) {
        auto car = std::make_shared<Car>(i);
        auto p = CarEvent(sim, car, passengers, rng);
        promises.push_back(std::make_shared<Promise>(p));

    }

    sim.Run();
    return 0;
}