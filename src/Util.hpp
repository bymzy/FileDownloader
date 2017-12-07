


#ifndef __UTIL_HPP__
#define __UTIL_HPP__

void Usage()
{
    std::string usage = "\nUsage: FileDownload -t <PROTOTYPE> -u <URL>\n"\
                        "\t-t proto to use to download the target file\n"\
                        "\t\tcurrent supports HTTP\n"\
                        "\t-u url of the target file\n";

    std::cout << usage << std::endl;
}

int ParseArgs(int argc, char *argv[], std::string& protoType, std::string& url)
{
    int err = 0;
    int opt;
    while ((opt = getopt(argc, argv, "t:u:")) != -1) {
        switch(opt) {
            case 't':
                protoType = std::string(optarg);
                break;
            case 'u':
                url = std::string(optarg);
                break;
            default:
                std::cerr << "invalid arg: " << opt << std::endl;
                err = EINVAL;
                break;
        }

        if (0 != err) {
            break;
        }
    }

    if (protoType.empty()) {
        std::cerr << "-t <PROTOTYPE> is requested" << std::endl;
        err = EINVAL;
    }

    if (url.empty()) {
        std::cerr << "-u <URL> is requested" << std::endl;
        err = EINVAL;
    }

    return err;
}

#endif


