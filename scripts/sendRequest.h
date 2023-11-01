#ifndef SENDREQUEST_H
#define SENDREQUEST_H

#include <curl/curl.h>
#include <string.h>

#define URL "http://localhost:8080/generate/images"

struct ResponseString {
    char *ptr;
    size_t len;
};

void init_string(struct ResponseString *s) {
    s->len = 0;
    s->ptr = malloc(s->len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct ResponseString *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size*nmemb;
}


char* sendReq(const char* prompt) {

    CURL *curl;
    CURLcode result;
    char post_fields[600] = "{\"prompt\": \"";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl == NULL){
        fprintf(stderr, "Error occurred!\n");
        return "err";
    }

    struct curl_slist *list = curl_slist_append(NULL, "Content-Type: application/json");

    strcat(post_fields, prompt);
    strcat(post_fields, "\"}");

    printf("%s\n", post_fields);

    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields);

    struct ResponseString s;
    init_string(&s);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

    result = curl_easy_perform(curl);

    if(result != CURLE_OK) {
        fprintf(stderr, "Error occurred!: %s\n", curl_easy_strerror(result));
        return "err";
    }
    else {
        printf("Generated request successfully.\n");
    }

    curl_slist_free_all(list);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return s.ptr;
}

#endif
