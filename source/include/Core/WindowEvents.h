#pragma once

#include "Core/Event.h"

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(int width, int height)
        : m_Width(width), m_Height(height) {}

    EventName GetEventName() const override { return EventName::WindowResize; }
    EventType GetEventType() const override { return EventType::WindowEvent; }
    int GetEventCode() const override { return static_cast<int>(EventName::WindowResize); }

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }

private:
    int m_Width;
    int m_Height;
};