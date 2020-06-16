#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <SDL_image.h>

#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>

namespace aur::file_utilities
{
    typedef std::tuple<std::vector<uint8_t>, unsigned int, unsigned int, unsigned int> image_data_type;

    static std::string read_text_file(const std::string &path)
    {
        std::ifstream file_stream{path};
        if (!file_stream.is_open()) {
            std::cerr << "Failed to open the file: '" << path << "'" << std::endl;
            exit(-1);
        }

        std::stringstream string_stream;
        string_stream << file_stream.rdbuf();

        return string_stream.str();
    }

    static image_data_type read_image_file(const std::string &path)
    {
        SDL_Surface *surface = IMG_Load(path.c_str());
        if (!surface) {
            std::cerr << "Failed to open the file: '" << path << "'" << std::endl;
            exit(-1);
        }

        auto bytes_per_pixel = surface->format->BytesPerPixel;
        if (!(bytes_per_pixel == 3 || bytes_per_pixel == 4))
        {
            std::cerr << "Invalid image file format (only RGB and RGBA files are supported): '" << path << "'" << std::endl;
            exit(-1);
        }

        auto *data = static_cast<uint8_t *>(surface->pixels);
        int image_pitch = surface->pitch;
        int image_width = surface->w;
        int image_height = surface->h;
        std::vector<uint8_t> image_data{data, data + image_height * image_pitch};

        SDL_FreeSurface(surface);

        return std::make_tuple(image_data, image_width, image_height, bytes_per_pixel);
    }
}

#endif
