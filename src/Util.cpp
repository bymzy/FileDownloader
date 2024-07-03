

#include <getopt.h>
#include <errno.h>
#include <iostream>

#include "Log.hpp"
#include "Util.hpp"

void Usage()
{
    std::string usage = "\nUsage: fget [-t <PROTOTYPE>] [-u <URL>] [-o <file>] [-v] [URL] \n"\
                        "\t-t proto to use to download the target file\n"\
                        "\t\tcurrent supports HTTP\n"\
                        "\t-u url of the target file\n"\
                        "\t-o output file name \n"\
                        "\t-v verbose output \n";

    std::cout << usage << std::endl;
}

int ParseArgs(int argc, char *argv[], std::string& protoType, std::string& url, bool& quite_output, std::string& output_file_name)
{
    int err = 0;
    int opt;
    while ((opt = getopt(argc, argv, "t:u:vo:")) != -1) {
        switch(opt) {
            case 't':
                protoType = std::string(optarg);
                break;
            case 'u':
                url = std::string(optarg);
                break;
            case 'v':
                quite_output = false;
                break;
            case 'o':
                output_file_name = std::string(optarg);
                break;
            default:
                ERROR_LOG("invalid arg: " << opt); 
                err = EINVAL;
                break;
        }

        if (0 != err) {
            break;
        }
    }

    if (optind < argc) {
        url = std::string(argv[optind]);
    }


    if (protoType.empty()) {
        //ERROR_LOG("-t <PROTOTYPE> is requested");
        //err = EINVAL;
        protoType = "HTTP";
    }

    if (protoType != "HTTP") {
        ERROR_LOG("invalid protoType, current support HTTP only");
        err = EINVAL;
    }

    if (url.empty()) {
        ERROR_LOG("-u <URL> is requested");
        err = EINVAL;
    }

    return err;
}

size_t GetHeader(char *ptr, size_t blockCount, size_t memBlockSize, void *arg)
{
    std::string *str = (std::string*)arg;
    (*str) += std::string(ptr);

    return blockCount * memBlockSize;
}


