#include <iostream>
#include "Core/Engine.h"
#include "Debug/Debug.h"

int main() {

    Engine GalaxyEngine("GalaxyEngine");
    ENGINE_TRACE("Engine Initialized : ", GalaxyEngine.ctx.Title);

    GalaxyEngine.Init("OpenGL");

    GalaxyEngine.Run();


    ENGINE_TRACE("ENGINE TERMINATED");
    
    return 0;
}