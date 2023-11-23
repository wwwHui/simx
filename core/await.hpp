/*************************************************************************************************************
@! Copyright(c) 2023
@Time    :  2023-11-12 18:16:33
@File    :  await.hpp
@Author  :  hui
@Version :  V0.1
@Desc    :  说明
**************************************************************************************************************/

#ifndef __SIMX_AWAIT_H__
#define __SIMX_AWAIT_H__


#include <coroutine>  // std::coroutine_handle


namespace simx {

    template<typename SimX, typename TimeType = double> struct EventAwait {
        SimX *sim_;
        TimeType time_;

        bool await_ready() { return false;};
        void await_suspend(std::coroutine_handle<> &handle) { 
            sim_->AddEvent(time_, handle);
            };
        void await_resume() {  };

        EventAwait(SimX *sim, TimeType t): sim_(sim), time_(t) {}

    };  // end of EventAwait


};  // end of namespace simx

#endif  // end of __SIMX_AWAIT_H__