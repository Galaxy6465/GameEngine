#pragma once

class Layer {
public:
    Layer(const char* name = "Layer") : m_LayerName(name) {}
    virtual ~Layer() = default;

    virtual void OnAttach(){}
    virtual void OnDetach(){}
    virtual void OnUpdate(){}
    virtual void OnRender(){}
    virtual void Clean(){}

     const char* GetName() const { return m_LayerName; }
protected:
    const char* m_LayerName;
};