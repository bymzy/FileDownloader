

#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <iostream>

#define DEBUG_LOG(data)\
    {\
        std::cout << std::boolalpha << data << " [DEBUG] ["\
           << __FILE__ << ":"<< __LINE__<< ":" << __FUNCTION__ << "]\n";\
}\


#define ERROR_LOG(data)\
    {\
        std::cout << std::boolalpha << data << " [ERROR] ["\
           << __FILE__ << ":"<< __LINE__<< ":" << __FUNCTION__ << "]\n";\
}\

#endif
