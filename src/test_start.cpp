#include "test_init.h"

#include <iostream>
#include <chrono>

//#include <pthread.h>
//#include <stdarg.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int opt;

    dsm_log_info("Parameter Check");
    while ((opt = getopt(argc, argv, "a:")) != -1) 
    {
        switch (opt) {
            case 'a':
                std::string temp(optarg);
                if(temp.compare("aocs"))
                {
                    dsm_log_info("! AOCS");
                }
                break;
        }
    }
    
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