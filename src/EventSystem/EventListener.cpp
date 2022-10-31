#include "pch.h"

EventListener::EventListener() { }
EventListener::EventListener(std::function<void(void*)> c, EventType t): callback(c), Type(t) { }
EventListener::~EventListener() { }

void EventListener::HandleEvent(void* eventData)
{
	if (callback)
	{
		callback(eventData);
	}
}

void EventListener::SetCallback(std::function<void(void*)> c)
{
	callback = c;
}

std::function<void(void*)> EventListener::GetCallback()
{
	return callback;
}
