#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <utility>

#define _IS_SAME(T, U) std::is_same<T, U>::value

namespace az {

    class Timer
    {
    public:

        using ll = long long;

        using ns = std::chrono::nanoseconds;
        using mcs = std::chrono::microseconds;
        using ms = std::chrono::milliseconds;
        using s = std::chrono::seconds;
        using m = std::chrono::minutes;

        Timer() = delete;
        Timer(Timer&) = delete;
        Timer(Timer&&) = delete;

        template<class scale, class T, class... Args>
        static ll timer(T&& caller, Args&&... args)
        {

            constexpr bool _SA = _IS_SAME(scale, ns) || _IS_SAME(scale, mcs) ||
                                 _IS_SAME(scale, ms) || _IS_SAME(scale, s) ||
                                 _IS_SAME(scale, m);

            static_assert (_SA, "Scale is not Timer::<duration>.");

            _TP _start = _HRC::now();
            caller(std::forward<Args>(args)...);
            return std::chrono::duration_cast<scale>(_HRC::now() - _start).count();
        }

    protected:

        using _HRC = std::chrono::high_resolution_clock;
        using _TP  = std::chrono::high_resolution_clock::time_point;

    };

}

#endif // TIMER_HPP
