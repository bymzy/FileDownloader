

#include <getopt.h>
#include <errno.h>
#include <assert.h>
#include <iostream>
#include <string>

#include "Util.hpp"
#include "ControlCenter.hpp"

bool g_quiet_output = true;
std::string g_output_file_name;

int main(int argc, char *argv[])
{
    int err = 0;
    std::string url;
    std::string protoType;
    ControlCenter *cc = NULL;

    do {
        err = ParseArgs(argc, argv, protoType, url, g_quiet_output, g_output_file_name);
        if (0 != err) {
            Usage();
            break;
        }

        cc = new ControlCenter();
        assert(NULL != cc);

        err = cc->Init(url, protoType);
        if (0 != err) {
            break;
        }

        err = cc->StartWork();
        if (0 != err) {
            break;
        }

    } while(0);

    if (NULL != cc) {
        cc->Finit();

        delete cc;
        cc = NULL;
    }

    return err;
}


