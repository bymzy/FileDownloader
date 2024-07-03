

#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <string>

void Usage();

int ParseArgs(int argc, char *argv[], std::string& protoType, std::string& url, bool& quiet_output, std::string& output_file_name);

size_t GetHeader(char *ptr, size_t blockCount, size_t memBlockSize, void *arg);

#endif



