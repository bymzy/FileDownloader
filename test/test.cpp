

#include <iostream>
#include <curl/curl.h>

size_t writeData(char *ptr, size_t size, size_t nmemb, void *arg)
{
    int *flag = (int*)arg;
    std::cout << *flag << std::endl;
    
    std::cout << size << ", " << nmemb << std::endl;
    std::cout << ptr << std::endl;

    return size * nmemb;
}

int  main()
{
    CURL *curl = curl_easy_init();
    CURLcode res;
    int flag = 1;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&flag);
        res = curl_easy_perform(curl);

        if (!res) {
            double cl;
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &cl);
            if (!res) {
                //printf("Size: " CURL_FORMAT_CURL_OFF_T "\n", cl);
                std::cout << cl << std::endl;
            }
        }
    }

    curl_easy_cleanup(curl);

    return 0;
}

