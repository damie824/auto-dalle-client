#ifndef PARSEJSON_H
#define PARSEJSON_H

#include <json-c/json.h>
#include <util/logger.h>

typedef struct imgres {
	char *prompt;
	char *url;
} imgres;

imgres parseJSON(char *data) {
	struct json_object *parsed_json;
	struct json_object *prompt;
	struct json_object *url;
	
	parsed_json = json_tokener_parse(data);

	json_object_object_get_ex(parsed_json, "message", &prompt);
	json_object_object_get_ex(parsed_json, "url", &url);

	logger.verbose("Parsing requested data type:json.");

	imgres result;

	result.prompt = json_object_get_string(prompt);
	result.url = json_object_get_string(url);

	return result;
}

#endif
