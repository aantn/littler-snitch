#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    int written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

int main(void)
{
    CURL *curl_handle;
    static const char *headerfilename = "/little_snitch_example.txt";
    FILE *headerfile;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_URL, "http://google.com");
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

    /* output file */
    headerfile = fopen(headerfilename,"w");
    if (headerfile == NULL) {
        curl_easy_cleanup(curl_handle);
        return -1;
    }

    curl_easy_setopt(curl_handle,   CURLOPT_WRITEHEADER, headerfile);
    curl_easy_perform(curl_handle);

    /* cleanup */
    fclose(headerfile);
    curl_easy_cleanup(curl_handle);

    return 0;
}
