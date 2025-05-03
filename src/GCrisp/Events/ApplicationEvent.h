#pragma once

#include "Event.h"
#include <GCrisp/Core/Core.h>

namespace GCrisp
{
class WindowCloseEvent : public Event
{
  public:
	WindowCloseEvent() {}

	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowMinimizeEvent : public Event
{
  public:
	WindowMinimizeEvent(bool minimized) : m_Minimized(minimized) {}

	inline bool IsMinimized() const { return m_Minimized; }

	EVENT_CLASS_TYPE(WindowMinimize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

  private:
	bool m_Minimized;
};

class WindowFocusEvent : public Event
{
  public:
	WindowFocusEvent(bool focused) : m_Focused(focused) {}

	inline bool IsFocused() const { return m_Focused; }

	EVENT_CLASS_TYPE(WindowFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

  private:
	bool m_Focused;
};

class WindowResizeEvent : public Event
{
  public:
	WindowResizeEvent(unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height)
	{
	}

	inline int GetNewWidth() const { return m_Width; }
	inline int GetNewHeight() const { return m_Height; }

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
} // namespace GCrisp
