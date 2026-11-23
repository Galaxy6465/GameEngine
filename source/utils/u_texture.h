#pragma once

#include <glad/glad.h>

#include <cctype>
#include <cstddef>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Utils {

class Texture2D {
public:
    Texture2D() = default;
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    ~Texture2D()
    {
        Release();
    }

    void Create(int width, int height, int channels, const unsigned char* pixels)
    {
        if (width <= 0 || height <= 0 || (channels != 3 && channels != 4) || pixels == nullptr) {
            throw std::invalid_argument("Texture requires positive dimensions, RGB/RGBA pixels, and data");
        }

        const GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
        GLuint texture = 0;
        glGenTextures(1, &texture);
        if (texture == 0) {
            throw std::runtime_error("Failed to create OpenGL texture");
        }

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format),
                     width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
        glBindTexture(GL_TEXTURE_2D, 0);

        Release();
        m_Texture = texture;
    }

    void LoadPPM(const std::string& path)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Unable to open PPM texture: " + path);
        }

        const std::string magic = ReadToken(file);
        if (magic != "P3" && magic != "P6") {
            throw std::runtime_error("Unsupported PPM format in " + path + " (expected P3 or P6)");
        }

        const int width = ParsePositiveInteger(ReadToken(file), "width", path);
        const int height = ParsePositiveInteger(ReadToken(file), "height", path);
        const int maxValue = ParsePositiveInteger(ReadToken(file), "maximum color value", path);
        if (maxValue > 255) {
            throw std::runtime_error("PPM values above 255 are not supported: " + path);
        }

        const std::size_t maxSize = std::numeric_limits<std::size_t>::max();
        if (static_cast<std::size_t>(width) > maxSize / static_cast<std::size_t>(height)) {
            throw std::runtime_error("PPM dimensions are too large: " + path);
        }
        const std::size_t pixelCount = static_cast<std::size_t>(width) *
                                       static_cast<std::size_t>(height);
        if (pixelCount > maxSize / 3) {
            throw std::runtime_error("PPM dimensions are too large: " + path);
        }
        std::vector<unsigned char> pixels(pixelCount * 3);

        if (magic == "P3") {
            for (unsigned char& pixel : pixels) {
                const int value = ParseNonNegativeInteger(ReadToken(file), "pixel value", path);
                if (value > maxValue) {
                    throw std::runtime_error("PPM pixel value exceeds maximum in: " + path);
                }
                pixel = static_cast<unsigned char>((value * 255 + maxValue / 2) / maxValue);
            }
        } else {
            file.read(reinterpret_cast<char*>(pixels.data()),
                      static_cast<std::streamsize>(pixels.size()));
            if (file.gcount() != static_cast<std::streamsize>(pixels.size())) {
                throw std::runtime_error("PPM pixel data is incomplete: " + path);
            }
            for (const unsigned char pixel : pixels) {
                if (pixel > maxValue) {
                    throw std::runtime_error("PPM pixel value exceeds maximum in: " + path);
                }
            }
            if (maxValue != 255) {
                for (unsigned char& pixel : pixels) {
                    pixel = static_cast<unsigned char>(
                        (static_cast<unsigned int>(pixel) * 255u +
                         static_cast<unsigned int>(maxValue) / 2u) /
                        static_cast<unsigned int>(maxValue));
                }
            }
        }

        Create(width, height, 3, pixels.data());
    }

    void Bind(unsigned int textureUnit = 0) const
    {
        EnsureLoaded();
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_Texture);
    }

    static void Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLuint GetId() const { return m_Texture; }

    void Release()
    {
        if (m_Texture != 0) {
            glDeleteTextures(1, &m_Texture);
            m_Texture = 0;
        }
    }

private:
    static std::string ReadToken(std::istream& input)
    {
        std::string token;
        char character = 0;

        while (input.get(character)) {
            if (std::isspace(static_cast<unsigned char>(character))) {
                continue;
            }
            if (character == '#') {
                input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            token.push_back(character);
            break;
        }

        while (input.get(character)) {
            if (std::isspace(static_cast<unsigned char>(character))) {
                if (character == '\r' && input.peek() == '\n') {
                    input.get();
                }
                break;
            }
            if (character == '#') {
                input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            token.push_back(character);
        }

        if (token.empty()) {
            throw std::runtime_error("Unexpected end of PPM file");
        }
        return token;
    }

    static int ParsePositiveInteger(const std::string& token, const char* field,
                                    const std::string& path)
    {
        const int value = ParseNonNegativeInteger(token, field, path);
        if (value == 0) {
            throw std::runtime_error("Invalid PPM " + std::string(field) + " in: " + path);
        }
        return value;
    }

    static int ParseNonNegativeInteger(const std::string& token, const char* field,
                                       const std::string& path)
    {
        std::istringstream parser(token);
        int value = 0;
        char trailing = 0;
        if (!(parser >> value) || (parser >> trailing) || value < 0) {
            throw std::runtime_error("Invalid PPM " + std::string(field) + " in: " + path);
        }
        return value;
    }

    void EnsureLoaded() const
    {
        if (m_Texture == 0) {
            throw std::logic_error("Texture has not been created or loaded");
        }
    }

    GLuint m_Texture = 0;
};

} // namespace Utils
