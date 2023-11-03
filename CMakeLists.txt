cmake_minimum_required(VERSION 3.26)
project(auto_dalle C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(auto_dalle
        main.c
        scripts/sendRequest.h
        scripts/parseJson.h
        util/logger.h
        scripts/downloadImage.h
        util/readAllFiles.h
)

find_package(CURL REQUIRED)
target_link_libraries(auto_dalle PRIVATE CURL::libcurl)

find_package(json-c CONFIG REQUIRED)
target_link_libraries(auto_dalle PRIVATE json-c::json-c json-c::json-c-static)