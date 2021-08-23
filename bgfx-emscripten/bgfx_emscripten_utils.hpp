#pragma once

#include <emscripten/emscripten.h>
#include <emscripten/fetch.h>

#include <string>

namespace emscriptenutils
{

inline bool fetch_file(const std::string& filename, std::string& file_contents)
{
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes =
        EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_SYNCHRONOUS;
    emscripten_fetch_t* fetch = emscripten_fetch(&attr, filename.c_str());
    if (fetch->status == 200) {
        file_contents = fetch->data;
        return true;
    } else {
        return false;
    }
}

} // namespace emscriptenutils
