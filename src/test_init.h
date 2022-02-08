#ifndef __test_init__
#define __test_init__

#include <iostream>
#include <functional>
#include <chrono>
#include <future>
#include <iomanip>
#include <stdarg.h>

inline std::string timestamp()
{
    using namespace std::chrono;
    using clock = system_clock;
    
    const auto current_time_point {clock::now()};
    const auto current_time {clock::to_time_t (current_time_point)};
    const auto current_localtime {*std::localtime (&current_time)};
    const auto current_time_since_epoch {current_time_point.time_since_epoch()};
    const auto current_milliseconds {duration_cast<milliseconds> (current_time_since_epoch).count() % 1000};
    
    std::ostringstream stream;
    stream << std::put_time (&current_localtime, "%Y-%m-%d %T") << "." << std::setw (3) << std::setfill ('0') << current_milliseconds;
    return stream.str();
}

inline void dsm_log_info(char const *fmt, ...)
{
    char dest[1024 * 16];

    va_list argptr;
    va_start(argptr, fmt);
    //vfprintf(stderr, fmt, argptr);
    vsprintf(dest, fmt, argptr);
    va_end(argptr);

    printf("[%s] [\033[1;32minfo\033[0m] %s\n", timestamp().c_str(), dest);
}

inline void disp_cpp_version()
{
    if (__cplusplus == 201703L) std::cout << "CPP VERSION : C++17\n";
    else if (__cplusplus == 201402L) std::cout << "CPP VERSION : C++14\n";
    else if (__cplusplus == 201103L) std::cout << "CPP VERSION : C++11\n";
    else if (__cplusplus == 199711L) std::cout << "CPP VERSION : C++98\n";
    else std::cout << "CPP VERSION : pre-standard C++\n";
}

// https://www.tutorialspoint.com/how-to-create-timer-using-cplusplus11
class later 
{
public:
    template <class callable, class... arguments>
    later(int after, bool async, callable&& f, arguments&&... args)
    {
        std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
        if (async) 
        {
            std::thread([after, task]() 
            {
                std::this_thread::sleep_for(std::chrono::microseconds(after));
                task();
            }).detach();
        } 
        else 
        {
            std::this_thread::sleep_for(std::chrono::microseconds(after));
            task();
        }
   }
};

class DSM_Timer
{
public:
    template <class callable, class... arguments>
    DSM_Timer(int after, bool async, callable&& f, arguments&&... args)
    {
        bool* running = &m_running;
        if (async) 
        {
            std::thread([running, after, async, f, args...]() 
            {
                while(*running)
                {
                    //dsm_log_info("timer bool : %d", (*running)? 1 : 0);
                    later later_test1(after, false, f, args...);
                }
            }).detach();
        }
        else
        {
            while(*running)
            {
                //dsm_log_info("timer bool : %d", (*running)? 1 : 0);
                later later_test1(after, false, f, args...);
            }
        }
        
    }

    void Stop()
    {
        //dsm_log_info("timer stop");
        m_running = false;
    }

private:
    bool m_running = true;
};

/*
usage)

    // 할당 및 타이머 시작
    DSM_Timer temp(1000000, true, &test2, 10, tempStr);

    // 중지
    temp.Stop();

*/

#endif