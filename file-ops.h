#pragma once

#include <fstream>
#include <iostream>

// stream string operations derived from:
// Optimized C++ by Kurt Guntheroth (O’Reilly).
// Copyright 2016 Kurt Guntheroth, 978-1-491-92206-4

namespace fileops
{

inline std::streamoff stream_size(std::istream& file)
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
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        return false;
    }

    const bool success = stream_read_string(file, fileContents);

    file.close();

    return success;
}

} // namespace fileops
