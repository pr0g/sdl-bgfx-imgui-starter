#pragma once

#include <fstream>
#include <iostream>

#include "bgfx/platform.h"
#if BX_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#endif

// stream string operations derived from:
// Optimized C++ by Kurt Guntheroth (O’Reilly).
// Copyright 2016 Kurt Guntheroth, 978-1-491-92206-4

namespace fileops
{

inline static std::streamoff stream_size(std::istream& file)
{
    std::istream::pos_type current_pos = file.tellg();
    if (current_pos == std::istream::pos_type(-1)) {
        return -1;
    }
    file.seekg(0, std::istream::end);
    std::istream::pos_type end_pos = file.tellg();
    file.seekg(current_pos);
    return end_pos - current_pos;
}

inline bool stream_read_string(std::istream& file, std::string& fileContents)
{
    std::streamoff len = stream_size(file);
    if (len == -1) {
        return false;
    }

    fileContents.resize(static_cast<std::string::size_type>(len));

    file.read(&fileContents[0], fileContents.length());
    return true;
}

inline bool read_file(const std::string& filename, std::string& fileContents)
{
#if !BX_PLATFORM_EMSCRIPTEN
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        return false;
    }

    const bool success = stream_read_string(file, fileContents);

    file.close();

    return success;
#else
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_ATTR_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_SYNCHRONOUS;
    emscripten_fetch_t *fetch = emscripten_fetch(&attr, filename.c_str());
    if (fetch->status == 200) {
        *fileContents = fetch->data;
        return true;
    } else
        return false;
#endif
}

} // namespace fileops
