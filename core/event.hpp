/*************************************************************************************************************
@! Copyright(c) 2023
@Time    :  2023-11-11 18:02:49
@File    :  event.hpp
@Author  :  hui
@Version :  V0.1
@Desc    :  说明
**************************************************************************************************************/

#ifndef _SIMX_EVENT_H_
#define _SIMX_EVENT_H_

#include <cassert>          // assert
#include <cstddef>          // std::size_t
#include <cstdint>          // std::uint64_t
#include <coroutine>        // std::coroutine_handle

namespace simx {

    enum EventState {
        pending,  /// Event is not yet triggered or aborted.
        triggered,      /// Event is triggered and will be processed at the current simulation time.
        processed,  /// Event is processed.
        aborted  /// Event is aborted.
    };

    template<typename TimeType = double> class Event {
        private:
            std::coroutine_handle<> handle_;
            TimeType time_ = 0;
            std::uint64_t id_;
            EventState state_ = EventState::pending;
        public:
            Event(TimeType time, std::uint64_t id, std::coroutine_handle<> &handle) : time_{time} , id_{id}, handle_(handle){}

        public:
            TimeType Time() const { return time_; }
            void Process() {
                state_ = EventState::triggered;
                // do something
                state_ = EventState::processed;
                handle_.resume();
            }

            // 重载<运算符
            bool operator<(const Event<TimeType> &b) const { return this->time_ < b.time_; }

            // 重载<运算符
            bool operator>(const Event<TimeType> &b) const { return this->time_ > b.time_; }

    }; // end of class Event
};  // end of namespace simx


#endif // _SIMX_EVENT_H_