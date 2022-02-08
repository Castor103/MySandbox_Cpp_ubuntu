#include "test_init.h"

#include <iostream>
#include <chrono>

//#include <pthread.h>
//#include <stdarg.h>
#include <unistd.h>

constexpr unsigned int HashCode(const char* str)
{
    return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
}

int main(int argc, char *argv[])
{
    int opt;

    dsm_log_info("Parameter Check");

    while ((opt = getopt(argc, argv, "a:")) != -1) 
    {
        switch (opt) {
            case 'a':
                std::string temp(optarg);

                /* 
                    방법 1 : if, else if 조건문으로 비교문을 추가 
                    문제점 : 이럴 경우 중첩 제한 문제 때문에 조건문을 최대 124개 정도만 작성 가능
                */
                if(false)
                {
                    if(string_compare(temp, "aocs", -1))
                    {
                        dsm_log_info("2! AOCS");
                    }
                    else if (string_compare(temp, "eps", -1))
                    {
                        dsm_log_info("2! EPS");
                    }
                    else
                    {
                        dsm_log_info("2! ????");
                    }
                    
                } 

                /*
                    ref : https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=devmachine&logNo=220952781191
                    방법 2 : HashCode 함수를 이용해서 Switch 문
                    문제점 : case 문에 작성하는 비교 문자열의 길이 제한이 있다고함, 늘리는 방법이 있다고 는 하나 컴파일 시간과 소모 자원이 증가
                */
                if(false)
                {
                    switch (HashCode(&temp[0]))
                    {
                    case HashCode("aocs"):
                        dsm_log_info("2! AOCS");
                        break;
                    case HashCode("eps"):
                        dsm_log_info("2! EPS");
                        break;
                    default:
                        dsm_log_info("2! ????");
                        break;
                    }
                }
                
                break;
        }
    }
    
    /* 내부 콘솔 입력 부 */

    dsm_log_info("Start");

    while(true)
    {
        std::string input;
        std::cin >> input;

        if(input.compare("exit") == 0)
        {
            dsm_log_info("exit command");
            break;
        }
        else if(input.compare("stop") == 0)
        {
            dsm_log_info("stop command");
        }
        else
        {
            int num = atoi(&input[0]);

            if(num == 0)
            {
                
            }
            else
            {
                
            }
           

        }
    }

    dsm_log_info("Finish");
   
    return 0;
}