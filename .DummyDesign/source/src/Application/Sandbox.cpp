#include "Application/Sandbox.h"

Sandbox::Sandbox()
{

}

Sandbox::~Sandbox()
{

}

/*Create a Sandbox
//? (
//? can also use only sandbox class in main.cpp
//? or just directly declare without extern in main
//? )
*/
GalaxyEngine::Application* GalaxyEngine::CreateApplication()  
{
    return new Sandbox();
}