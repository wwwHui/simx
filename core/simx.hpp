/*************************************************************************************************************
@! Copyright(c) 2023
@Time    :  2023-11-11 17:50:33
@File    :  simx.hpp
@Author  :  hui
@Version :  V0.1
@Desc    :  说明
**************************************************************************************************************/

#ifndef _SIMX_H_
#define _SIMX_H_

#include <cassert>          // assert
#include <cstddef>          // std::size_t
#include <cstdint>          // std::uint64_t
#include <queue>            // std::priority_queue

#include "event.hpp"
#include "promise.hpp"
#include "await.hpp"

namespace simx {

    template<typename TimeType = double> class SimX {
        private:
            TimeType now_ = 0;  // time 
            std::uint64_t next_id_= 0 ;  // for event id 
            std::priority_queue<Event<TimeType>, std::vector<Event<TimeType>>, std::greater<Event<TimeType>>> events_;  // Scheduled events.
        public:
            TimeType Now() const {return now_;}
            EventAwait<SimX, TimeType> Timeout(TimeType delay){
                assert(delay >= TimeType{0});
                auto await = EventAwait<SimX, TimeType>(this, now_+delay);
                return await;
            }

            void Step() {
                auto event = events_.top();
                events_.pop();
                now_ = event.Time();
                event.Process();
            }

            /// Run the simulation until no more events are scheduled.
            void Run() {
                while (!events_.empty()) {
                    Step();
                }
            }
            void Run(TimeType target) {
                assert(target >= now_);
                while (!events_.empty() && events_.top().Time() < target) {
                    Step();
                }

                now_ = target;
            }
            void AddEvent(TimeType time, std::coroutine_handle<> &handle){
                events_.emplace(Event<TimeType>(time, next_id_++, handle));
            }

            void Reset(){
                while(!events_.empty()){
                    events_.pop();
                }
                now_ = 0;  // time 
                next_id_=0;  // for event id 
            }

    };  // end of class SimX
};  // end of namespace simx


#endif // _SIMX_H_