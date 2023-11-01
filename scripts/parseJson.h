#ifndef PARSEJSON_H
#define PARSEJSON_H

#include <json-c/json.h>

char parseJSON(char* data) {
    struct json_object *parsed_json;
    struct json_object *prompt;
    struct json_object *url;

    parsed_json = json_tokener_parse(data);

    json_object_object_get_ex(parsed_json, "message", &prompt);
    json_object_object_get_ex(parsed_json, "url", &url);

    printf("Used Prompt: %s\n", json_object_get_string(prompt));
    printf("Url: %s\n", json_object_get_string(url));
}

#endif
