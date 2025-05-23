#pragma once

#include "Event.h"
#include <GCrisp/Core/Base.h>

namespace GCrisp {
class KeyEvent : public Event {
  public:
    inline int GetKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

  protected:
    KeyEvent(int keycode) : m_KeyCode(keycode) {}

    int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent {
  public:
    KeyPressedEvent(int keycode, int repeatCount)
        : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

    inline int GetRepeatCount() const { return m_RepeatCount; }

    std::string ToString() const override {
        std::stringstream stream;
        stream << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount
               << " repeats)";
        return stream.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)

  private:
    int m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent {
  public:
    KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

    std::string ToString() const override {
        std::stringstream stream;
        stream << "KeyReleasedEvent: " << m_KeyCode;
        return stream.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};
} // namespace GCrisp
