#pragma once
#include "Debug/Debug.h"
#include <functional>

enum EventName {
    WindowResize = 0, WindowClose, WindowCreated,
    MousePressed = 10, MouseDown, MouseRelease,
    KeyPressed = 20, KeyHold, KeyDown
};

enum EventType {
    None = 0,
    WindowEvent = 1, MouseEvent = 2, KeyboardEvent = 3
};

class Event {
public:
    virtual ~Event() = default;

    virtual EventName GetEventName() const = 0;
    virtual EventType GetEventType() const = 0;
    virtual int GetEventCode() const { return 0; }

    bool Handled = false;
};

class EventDispacher {
public:
    using EventCallback = std::function<bool(Event& event)>;

    explicit EventDispacher(Event& event) : m_Event(event){}

    bool Dispatch(EventName targetName, const EventCallback& func)
    {
        if(!m_Event.Handled && m_Event.GetEventName() == targetName)
        {
            m_Event.Handled = func(m_Event);
            return true;
        }
        return false;
    }
    // void Detach();
private:
    Event& m_Event;

};