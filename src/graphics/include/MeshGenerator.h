#pragma once
#include "EngineContext.h"
#include <cmath>
#include <vector>
#include <glad/glad.h>
#include <iostream>

// Only the declaration (no function body here!)
void GenerateSphereData(ObjectData& sphereData, float radius, unsigned int sectorCount, unsigned int stackCount, bool normals, bool textures);

void GenerateCubeData(ObjectData& cubeData, bool normals, bool textures);

void GenerateCubeDataEBO(ObjectData& cubeData, bool normals, bool textures);

void GenerateSquareData(ObjectData& squareData, bool normals, bool textures);

void GenerateTriangleData(ObjectData& triangleData, bool normals, bool textures);

void GenerateObject(ObjectData& object, std::vector<float> Vertices, bool normals, bool textures);

void GenerateObjectEBO(ObjectData& object, std::vector<float> Vertices, std::vector<unsigned int> Indices, bool normals, bool textures);