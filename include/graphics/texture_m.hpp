#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>

class Texture {
public:
    unsigned int ID;
    int width, height, nrChannels;

    Texture(const char* path) {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        
        // Texture wrapping options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Texture filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Flip loaded textures on the Y-axis (OpenGL expects 0.0 at bottom)
        stbi_set_flip_vertically_on_load(true); 

        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format = GL_RGB;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture at path: " << path << std::endl;
        }
        
        stbi_image_free(data);
    }

    ~Texture() {
        glDeleteTextures(1, &ID);
    }

    void Bind(unsigned int slot = 0) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, ID);
    }
};

#endif