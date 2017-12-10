

#include <getopt.h>
#include <errno.h>
#include <assert.h>
#include <iostream>
#include <string>

#include "Util.hpp"
#include "ControlCenter.hpp"

int main(int argc, char *argv[])
{
    int err = 0;
    std::string url;
    std::string protoType;
    ControlCenter *cc = NULL;

    do {
        err = ParseArgs(argc, argv, protoType, url);
        if (0 != err) {
            Usage();
            break;
        }

        cc = ControlCenter::Instance();
        assert(NULL != cc);

        err = cc->Init(url, protoType, url);
        if (0 != err) {
            break;
        }

        err = cc->StartWork();
        if (0 != err) {
            break;
        }

    } while(0);

    return err;
}




