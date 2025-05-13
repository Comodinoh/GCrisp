#pragma once

#include "Event.h"
#include <GCrisp/Core/Core.h>

namespace GCrisp {
class MouseMovedEvent : public Event {
  public:
    MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

    inline float GetX() const { return m_MouseX; }
    inline float GetY() const { return m_MouseY; }

    virtual std::string ToString() const override {
        std::stringstream stream;
        stream << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return stream.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event {
  public:
    MouseScrolledEvent(float xOffset, float yOffset)
        : m_XOffset(xOffset), m_YOffset(yOffset) {}

    inline float GetXOffset() const { return m_XOffset; }
    inline float GetYOffset() const { return m_YOffset; }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event {
  public:
    inline int GetMouseButton() const { return m_Button; }
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  protected:
    MouseButtonEvent(int button) : m_Button(button) {}

    int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
  public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

    virtual std::string ToString() const override{
        std::stringstream stream;
        stream << "MouseButtonPressedEvent: " << m_Button;
        return stream.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
  public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

    virtual std::string ToString() const override{
        std::stringstream stream;
        stream << "MouseButtonReleasedEvent: " << m_Button;
        return stream.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};
} // namespace GCrisp
