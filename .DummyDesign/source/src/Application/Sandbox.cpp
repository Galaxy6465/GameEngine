#include "Application/Sandbox.h"
#include "Layers/Layer.h"


class ExampleLayer : public GalaxyEngine::Layer {
public:
    ExampleLayer() : Layer("Example Layer")
    {

    }  

    void OnUpdate() override
    {
        // std::cout << GetName() << " : Layer Update. " << std::endl;
    }

    void OnEvent(GalaxyEngine::Event& event) override
    {
        std::cout << event.ToString() << std::endl;
    }
};

Sandbox::Sandbox()
{
    PushLayer(new ExampleLayer());
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