#pragma once

#include <GCrisp/Events/Event.h>
#include <GCrisp/Core/Timing.h>

namespace GCrisp
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach()
        {
        }

        virtual void OnDetach()
        {
        }

        virtual void OnUpdate(const ProcessedTime& elapsed)
        {
        }

        virtual void OnEvent(Event& e)
        {
        }

        inline const std::string& GetName() const { return m_DebugName; }

    private:
        std::string m_DebugName;
        float m_Time;
    };
}
