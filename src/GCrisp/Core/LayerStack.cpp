#include "LayerStack.h"
#include <gcpch.h>

namespace GCrisp {
LayerStack::LayerStack() : m_LayerInsertIndex(0) {}

LayerStack::~LayerStack() {
    for (Layer* layer : m_Layers) {
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* layer) {
    GC_PROFILE_FUNC();
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    m_LayerInsertIndex++;
    layer->OnAttach();
}

void LayerStack::PushOverlay(Layer* overlay) {
    GC_PROFILE_FUNC();
    m_Layers.emplace_back(overlay);
    overlay->OnAttach();
}

void LayerStack::PopLayer(Layer* layer) {
    GC_PROFILE_FUNC();
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
        m_LayerInsertIndex--;
        layer->OnDetach();
    }
}

void LayerStack::PopOverlay(Layer* overlay) {
    GC_PROFILE_FUNC();
    auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
        overlay->OnDetach();
    }
}
} // namespace GCrisp
