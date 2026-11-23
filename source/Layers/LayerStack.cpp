#include "LayerStack.h"
#include <algorithm>

LayerStack::~LayerStack() {
    Clear();
}

void LayerStack::Clear() {
    for (auto layer = m_Layers.rbegin(); layer != m_Layers.rend(); ++layer) {
        (*layer)->OnDetach();
    }
    m_Layers.clear();
    m_LayerInsertIndex = 0;
}

void LayerStack::PushLayer(std::unique_ptr<Layer> layer) {
    layer->OnAttach();
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
    m_LayerInsertIndex++;
}

void LayerStack::PushOverlay(std::unique_ptr<Layer> overlay) {
    overlay->OnAttach();
    m_Layers.emplace_back(std::move(overlay));
}

void LayerStack::PopLayer(Layer* layer) {
    auto it = std::find_if(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex,
        [layer](const std::unique_ptr<Layer>& ptr) { return ptr.get() == layer; });

    if (it != m_Layers.begin() + m_LayerInsertIndex) {
        (*it)->OnDetach();
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
}

void LayerStack::PopOverlay(Layer* overlay) {
    auto it = std::find_if(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(),
        [overlay](const std::unique_ptr<Layer>& ptr) { return ptr.get() == overlay; });

    if (it != m_Layers.end()) {
        (*it)->OnDetach();
        m_Layers.erase(it);
    }
}
