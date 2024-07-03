

#ifndef __LOG_HPP__
#define __LOG_HPP__

extern bool g_quiet_output;

#include <iostream>

#define DEBUG_LOG(data)\
    {\
        if (!g_quiet_output) std::cout << "[DEBUG] " << std::boolalpha << data << "\n";\
}\

           /* << __FILE__ << ":"<< __LINE__<< ":" << __FUNCTION__ << "]\n" */

#define ERROR_LOG(data)\
    {\
        std::cerr << std::boolalpha << data << " [ERROR] ["\
           << __FILE__ << ":"<< __LINE__<< ":" << __FUNCTION__ << "]\n";\
}\

#endif
