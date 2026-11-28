#pragma once
#include "Layer.h"
#include <vector>
#include <memory>

class LayerStack {
public:
    LayerStack() = default;
    ~LayerStack();

    // Prevent copying (m_Layers holds unique_ptr<Layer>)
    LayerStack(const LayerStack&) = delete;
    LayerStack& operator=(const LayerStack&) = delete;

    // Allow moving
    LayerStack(LayerStack&&) = default;
    LayerStack& operator=(LayerStack&&) = default;

    void PushLayer(std::unique_ptr<Layer> layer);
    void PushOverlay(std::unique_ptr<Layer> overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlay);
    void Clear();

    auto begin() { return m_Layers.begin(); }
    auto end() { return m_Layers.end(); }
    auto rbegin() { return m_Layers.rbegin(); }
    auto rend() { return m_Layers.rend(); }

private:
    std::vector<std::unique_ptr<Layer>> m_Layers;
    unsigned int m_LayerInsertIndex = 0;
};