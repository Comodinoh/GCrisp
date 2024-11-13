#pragma once

#include <GCrisp/Core.h>
#include "Event.h"

namespace gcrisp{

class WindowCloseEvent : public Event
{
public:
  WindowCloseEvent() {}

  EVENT_CLASS_TYPE(WindowClose)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowResizeEvent : public Event
{
public:

  WindowResizeEvent(unsigned int width, unsigned int height) : 
    m_Width(width), m_Height(height) {}

  std::string ToString() const override
  {
    std::stringstream stream;
    stream << "WindowResizeEvent: " << m_Width << ", " << m_Height;
    return stream.str();
  }
  
  EVENT_CLASS_TYPE(WindowResize)
  EVENT_CLASS_CATEGORY(EventCategoryApplication)
  
private:
  unsigned int m_Width, m_Height;
};

}
