/*************************************************************************************************************
@! Copyright(c) 2023
@Time    :  2023-11-12 10:38:40
@File    :  promise.hpp
@Author  :  hui
@Version :  V0.1
@Desc    :  说明
**************************************************************************************************************/


#ifndef _SIMX_PROMISE_H_
#define _SIMX_PROMISE_H_

#include <coroutine>        // std::coroutine_handle, std::suspend_never
#include <utility>          // std::exchange 


namespace simx {

    struct Promise {
        struct promise_type {
            Promise get_return_object() {
                return  Promise{ std::coroutine_handle<promise_type>::from_promise(*this) };
            }
            std::suspend_never initial_suspend() noexcept { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }  // std::suspend_always  std::suspend_never 
            void return_void() { }
            void unhandled_exception() { throw; }
        };

        std::coroutine_handle<promise_type> handle_;
        explicit Promise(std::coroutine_handle<promise_type> handle) noexcept
        : handle_(handle) {}

        Promise(Promise &&generator) noexcept
            : handle_(std::exchange(generator.handle_, {})) {}

        Promise(Promise &p) : handle_(p.handle_) {p.handle_=nullptr;}  

        Promise &operator=(Promise &) = delete;

        ~Promise() { if(handle_) handle_.destroy(); }

    }; // end of struct Promise


};  // end of namespace simx



#endif // _SIMX_PROMISE_H_