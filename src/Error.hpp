

#ifndef __ERROR_HPP__
#define __ERROR_HPP__

enum _ERROR {
    E_CURL_GLOBAL_INIT = 1000, /* curl global init failed */
    E_CURL_EASY_INIT, /* curl global init failed */
    E_CURL_GET_FILE_SIZE, /* filed when get file size */
    E_CURL_DOWNLOAD_FAILED, /* easy perform failed */
};

#endif


