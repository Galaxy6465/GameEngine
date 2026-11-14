#include "graphics/MeshGenerator.hpp"


void GenerateSphereData(ObjectData& sphereData, float radius, unsigned int sectorCount, unsigned int stackCount, bool normals, bool textures) {
    sphereData.vertices.clear();
    sphereData.indices.clear();

    float PI = 3.14159265359f;

    // 1. Generate Vertices (Position, Normals, and TexCoords dynamically)
    for (unsigned int i = 0; i <= stackCount; ++i) {
        float stackAngle = PI / 2.0f - i * (PI / stackCount); // from pi/2 to -pi/2
        float xy = radius * cosf(stackAngle);                 
        float z = radius * sinf(stackAngle);                  

        for (unsigned int j = 0; j <= sectorCount; ++j) {
            float sectorAngle = j * (2.0f * PI / sectorCount); // from 0 to 2pi

            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            // Position (3 floats)
            sphereData.vertices.push_back(x);
            sphereData.vertices.push_back(y);
            sphereData.vertices.push_back(z);

            // Normals (3 floats) - normalized position vector from origin
            if (normals) {
                sphereData.vertices.push_back(x / radius);
                sphereData.vertices.push_back(y / radius);
                sphereData.vertices.push_back(z / radius);
            }

            // Texture Coordinates (2 floats)
            if (textures) {
                float s = (float)j / sectorCount;
                float t = (float)i / stackCount;
                sphereData.vertices.push_back(s);
                sphereData.vertices.push_back(t);
            }
        }
    }

    // 2. Generate Indices for Triangles (EBO)
    unsigned int k1, k2;
    for (unsigned int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);     
        k2 = k1 + sectorCount + 1;      

        for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                sphereData.indices.push_back(k1);
                sphereData.indices.push_back(k2);
                sphereData.indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1)) {
                sphereData.indices.push_back(k1 + 1);
                sphereData.indices.push_back(k2);
                sphereData.indices.push_back(k2 + 1);
            }
        }
    }

    // 3. Calculate Stride & Setup Buffers
    GLsizei stride = 3; // Position
    if (normals) stride += 3;
    if (textures) stride += 2;

    GLuint VBO, EBO;
    glGenVertexArrays(1, &sphereData.VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(sphereData.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sphereData.vertices.size() * sizeof(float), sphereData.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereData.indices.size() * sizeof(unsigned int), sphereData.indices.data(), GL_STATIC_DRAW);

    size_t byteOffset = 0;

    // Layout 0: Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
    glEnableVertexAttribArray(0);
    byteOffset += 3 * sizeof(float);

    // Layout 1: Normals (if enabled)
    if (normals) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(1);
        byteOffset += 3 * sizeof(float);
    }

    // Layout 2: Texture Coords (if enabled)
    if (textures) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(2);
        byteOffset += 2 * sizeof(float);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


// --- 1. Standard Cube (36 vertices, glDrawArrays) with dynamic attributes ---
void GenerateCubeData(ObjectData& cubeData, bool normals, bool textures) {
    cubeData.vertices.clear();
    cubeData.indices.clear();

    // Base 36 positions for non-indexed cube faces
    std::vector<float> rawPositions = {
        -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,   0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,  -0.5f,  0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,   0.5f,  0.5f, -0.5f,   0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,  -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,   0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,  -0.5f,  0.5f, -0.5f
    };

    // Corresponding normals (per face)
    std::vector<float> rawNormals = {
         0.0f,  0.0f, -1.0f,    0.0f,  0.0f,  1.0f,
        -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,
         0.0f, -1.0f,  0.0f,    0.0f,  1.0f,  0.0f
    };

    // Texture coords repeating per face
    std::vector<float> rawTexCoords = {
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f
    };

    // Interleave data based on flags
    for (size_t i = 0; i < 36; ++i) {
        // 1. Position (Always included: 3 floats)
        cubeData.vertices.push_back(rawPositions[i * 3 + 0]);
        cubeData.vertices.push_back(rawPositions[i * 3 + 1]);
        cubeData.vertices.push_back(rawPositions[i * 3 + 2]);

        // 2. Normal (Optional: 3 floats)
        if (normals) {
            size_t faceIndex = (i / 6) * 3;
            cubeData.vertices.push_back(rawNormals[faceIndex + 0]);
            cubeData.vertices.push_back(rawNormals[faceIndex + 1]);
            cubeData.vertices.push_back(rawNormals[faceIndex + 2]);
        }

        // 3. Texture Coords (Optional: 2 floats)
        if (textures) {
            size_t texIndex = (i % 6) * 2;
            cubeData.vertices.push_back(rawTexCoords[texIndex + 0]);
            cubeData.vertices.push_back(rawTexCoords[texIndex + 1]);
        }
    }

    // Calculate stride in floats
    GLsizei stride = 3; // Position
    if (normals) stride += 3;
    if (textures) stride += 2;

    // OpenGL Buffers Setup
    GLuint VBO;
    glGenVertexArrays(1, &cubeData.VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(cubeData.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, cubeData.vertices.size() * sizeof(float), cubeData.vertices.data(), GL_STATIC_DRAW);

    size_t byteOffset = 0;

    // Layout 0: Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
    glEnableVertexAttribArray(0);
    byteOffset += 3 * sizeof(float);

    // Layout 1: Normals (if enabled)
    if (normals) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(1);
        byteOffset += 3 * sizeof(float);
    }

    // Layout 2: Texture Coords (if enabled)
    if (textures) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(2);
        byteOffset += 2 * sizeof(float);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


// --- 2. Indexed Cube (EBO) with dynamic attributes ---
void GenerateCubeDataEBO(ObjectData& cubeData, bool normals, bool textures) {
    cubeData.vertices.clear();
    cubeData.indices.clear();

    // 24 unique vertices for clean face mapping with EBO
    std::vector<float> basePositions = {
        // Front
        -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,
        // Back
        -0.5f, -0.5f,  0.5f,   0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,
        // Left
        -0.5f,  0.5f,  0.5f,  -0.5f,  0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f,  0.5f,
        // Right
         0.5f,  0.5f,  0.5f,   0.5f,  0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,
        // Bottom
        -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,
        // Top
        -0.5f,  0.5f, -0.5f,   0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f
    };

    std::vector<float> baseNormals = {
         0.0f,  0.0f, -1.0f,   0.0f,  0.0f, -1.0f,   0.0f,  0.0f, -1.0f,   0.0f,  0.0f, -1.0f,
         0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  1.0f,
        -1.0f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,
         0.0f, -1.0f,  0.0f,   0.0f, -1.0f,  0.0f,   0.0f, -1.0f,  0.0f,   0.0f, -1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  0.0f
    };

    std::vector<float> baseTexCoords = {
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
        1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f,
        1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f,
        0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f,
        0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f
    };

    for (size_t i = 0; i < 24; ++i) {
        // Position
        cubeData.vertices.push_back(basePositions[i * 3 + 0]);
        cubeData.vertices.push_back(basePositions[i * 3 + 1]);
        cubeData.vertices.push_back(basePositions[i * 3 + 2]);

        // Normal
        if (normals) {
            cubeData.vertices.push_back(baseNormals[i * 3 + 0]);
            cubeData.vertices.push_back(baseNormals[i * 3 + 1]);
            cubeData.vertices.push_back(baseNormals[i * 3 + 2]);
        }

        // Texture Coords
        if (textures) {
            cubeData.vertices.push_back(baseTexCoords[i * 2 + 0]);
            cubeData.vertices.push_back(baseTexCoords[i * 2 + 1]);
        }
    }

    cubeData.indices = {
        0, 1, 2,  2, 3, 0,       
        4, 5, 6,  6, 7, 4,       
        8, 9, 10, 10, 11, 8,   
        12, 13, 14, 14, 15, 12, 
        16, 17, 18, 18, 19, 16, 
        20, 21, 22, 22, 23, 20  
    };

    GLsizei stride = 3;
    if (normals) stride += 3;
    if (textures) stride += 2;

    GLuint VBO, EBO;
    glGenVertexArrays(1, &cubeData.VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(cubeData.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, cubeData.vertices.size() * sizeof(float), cubeData.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeData.indices.size() * sizeof(unsigned int), cubeData.indices.data(), GL_STATIC_DRAW);

    size_t byteOffset = 0;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
    glEnableVertexAttribArray(0);
    byteOffset += 3 * sizeof(float);

    if (normals) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(1);
        byteOffset += 3 * sizeof(float);
    }

    if (textures) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(2);
        byteOffset += 2 * sizeof(float);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// --- 3. Square / Quad Data (Indexed EBO, 4 vertices) ---
void GenerateSquareData(ObjectData& squareData, bool normals, bool textures) {
    squareData.vertices.clear();
    squareData.indices.clear();

    // 4 corners of a 1x1 quad centered at origin on the XY plane
    std::vector<float> basePositions = {
        -0.5f,  0.5f,  0.0f, // Top-Left (0)
        -0.5f, -0.5f,  0.0f, // Bottom-Left (1)
         0.5f, -0.5f,  0.0f, // Bottom-Right (2)
         0.5f,  0.5f,  0.0f  // Top-Right (3)
    };

    std::vector<float> baseNormals = {
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f
    };

    std::vector<float> baseTexCoords = {
        0.0f,  1.0f, // Top-Left
        0.0f,  0.0f, // Bottom-Left
        1.0f,  0.0f, // Bottom-Right
        1.0f,  1.0f  // Top-Right
    };

    for (size_t i = 0; i < 4; ++i) {
        // Position
        squareData.vertices.push_back(basePositions[i * 3 + 0]);
        squareData.vertices.push_back(basePositions[i * 3 + 1]);
        squareData.vertices.push_back(basePositions[i * 3 + 2]);

        // Normals
        if (normals) {
            squareData.vertices.push_back(baseNormals[i * 3 + 0]);
            squareData.vertices.push_back(baseNormals[i * 3 + 1]);
            squareData.vertices.push_back(baseNormals[i * 3 + 2]);
        }

        // Texture Coords
        if (textures) {
            squareData.vertices.push_back(baseTexCoords[i * 2 + 0]);
            squareData.vertices.push_back(baseTexCoords[i * 2 + 1]);
        }
    }

    // Two triangles making up the square (Counter-clockwise winding)
    squareData.indices = {
        0, 1, 2,
        2, 3, 0
    };

    GLsizei stride = 3;
    if (normals) stride += 3;
    if (textures) stride += 2;

    GLuint VBO, EBO;
    glGenVertexArrays(1, &squareData.VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(squareData.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, squareData.vertices.size() * sizeof(float), squareData.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, squareData.indices.size() * sizeof(unsigned int), squareData.indices.data(), GL_STATIC_DRAW);

    size_t byteOffset = 0;

    // Layout 0: Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
    glEnableVertexAttribArray(0);
    byteOffset += 3 * sizeof(float);

    // Layout 1: Normals
    if (normals) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(1);
        byteOffset += 3 * sizeof(float);
    }

    // Layout 2: Texture Coords
    if (textures) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(2);
        byteOffset += 2 * sizeof(float);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


// --- 4. Triangle Data (3 vertices, glDrawArrays) ---
void GenerateTriangleData(ObjectData& triangleData, bool normals, bool textures) {
    triangleData.vertices.clear();
    triangleData.indices.clear(); // Not strictly needed for a single triangle, can use glDrawArrays

    std::vector<float> basePositions = {
        -0.5f, -0.5f,  0.0f, // Bottom-Left
         0.5f, -0.5f,  0.0f, // Bottom-Right
         0.0f,  0.5f,  0.0f  // Top-Center
    };

    std::vector<float> baseNormals = {
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f
    };

    std::vector<float> baseTexCoords = {
        0.0f,  0.0f,
        1.0f,  0.0f,
        0.5f,  1.0f
    };

    for (size_t i = 0; i < 3; ++i) {
        // Position
        triangleData.vertices.push_back(basePositions[i * 3 + 0]);
        triangleData.vertices.push_back(basePositions[i * 3 + 1]);
        triangleData.vertices.push_back(basePositions[i * 3 + 2]);

        // Normals
        if (normals) {
            triangleData.vertices.push_back(baseNormals[i * 3 + 0]);
            triangleData.vertices.push_back(baseNormals[i * 3 + 1]);
            triangleData.vertices.push_back(baseNormals[i * 3 + 2]);
        }

        // Texture Coords
        if (textures) {
            triangleData.vertices.push_back(baseTexCoords[i * 2 + 0]);
            triangleData.vertices.push_back(baseTexCoords[i * 2 + 1]);
        }
    }

    GLsizei stride = 3;
    if (normals) stride += 3;
    if (textures) stride += 2;

    GLuint VBO;
    glGenVertexArrays(1, &triangleData.VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(triangleData.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, triangleData.vertices.size() * sizeof(float), triangleData.vertices.data(), GL_STATIC_DRAW);

    size_t byteOffset = 0;

    // Layout 0: Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
    glEnableVertexAttribArray(0);
    byteOffset += 3 * sizeof(float);

    // Layout 1: Normals
    if (normals) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(1);
        byteOffset += 3 * sizeof(float);
    }

    // Layout 2: Texture Coords
    if (textures) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(2);
        byteOffset += 2 * sizeof(float);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



// --- 5. Generate Object with Given Vertex ---
void GenerateObject(ObjectData& object, std::vector<float> Vertices, bool normals, bool textures) {
    object.vertices.clear();

    //std::vector<float> Vertices;
    // { VerticesCoord, normalsCoord, texturesCoord }

    object.vertices = Vertices;

    // Calculate stride in floats
    GLsizei stride = 3; // Position
    if (normals) stride += 3;
    if (textures) stride += 2;

    // OpenGL Buffers Setup
    GLuint VBO;
    glGenVertexArrays(1, &object.VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(object.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, object.vertices.size() * sizeof(float), object.vertices.data(), GL_STATIC_DRAW);

    size_t byteOffset = 0;

    // Layout 0: Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
    glEnableVertexAttribArray(0);
    byteOffset += 3 * sizeof(float);

    // Layout 1: Normals (if enabled)
    if (normals) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(1);
        byteOffset += 3 * sizeof(float);
    }

    // Layout 2: Texture Coords (if enabled)
    if (textures) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(2);
        byteOffset += 2 * sizeof(float);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// --- 6. Generate Object with Vertices and Indices (EBO Version) ---
void GenerateObjectEBO(ObjectData& object, std::vector<float> Vertices, std::vector<unsigned int> Indices, bool normals, bool textures) {
    object.vertices.clear();
    object.indices.clear();

    object.vertices = Vertices;
    object.indices = Indices;

    // Calculate stride in floats
    GLsizei stride = 3; // Position
    if (normals) stride += 3;
    if (textures) stride += 2;

    // OpenGL Buffers Setup
    GLuint VBO, EBO;
    glGenVertexArrays(1, &object.VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(object.VAO);

    // 1. Upload Vertex Data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, object.vertices.size() * sizeof(float), object.vertices.data(), GL_STATIC_DRAW);

    // 2. Upload Index Data (EBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, object.indices.size() * sizeof(unsigned int), object.indices.data(), GL_STATIC_DRAW);

    size_t byteOffset = 0;

    // Layout 0: Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
    glEnableVertexAttribArray(0);
    byteOffset += 3 * sizeof(float);

    // Layout 1: Normals (if enabled)
    if (normals) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(1);
        byteOffset += 3 * sizeof(float);
    }

    // Layout 2: Texture Coords (if enabled)
    if (textures) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)byteOffset);
        glEnableVertexAttribArray(2);
        byteOffset += 2 * sizeof(float);
    }

    // IMPORTANT: Unbind the VAO *before* unbinding the EBO! 
    // The VAO stores the active GL_ELEMENT_ARRAY_BUFFER binding state.
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Safe to unbind only after VAO is unbound
}