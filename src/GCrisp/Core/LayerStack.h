#pragma once

#include <GCrisp/Core/Layer.h>
#include <vector>

namespace GCrisp {
class LayerStack {
  public:
    LayerStack();
    ~LayerStack();

    // TODO: Test with more layers
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* layer);

    std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_Layers.end(); }

  private:
    std::vector<Layer*> m_Layers;
    uint32_t m_LayerInsertIndex;
};
} // namespace GCrisp
