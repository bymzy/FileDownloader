

#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <iostream>

#define DEBUG_LOG(data) do {\
        std::cout << "DEBUG: " << data << __PRETTY_FUNCTION__ << ":" << __LINE__ << std::endl;\
    } while(0);\

#define ERROR_LOG(data) do {\
        std::cerr << "ERROR: " << data << __PRETTY_FUNCTION__ << ":" << __LINE__ << std::endl;\
    } while(0);\

#endif


