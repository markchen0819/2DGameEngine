#pragma once
#include <functional>
#include <vector>
#include <iostream>
#include "EventType.h"
#include "EventListener.h"

class EventSystem
{
public:
	~EventSystem();
	static EventSystem* GetInstance();

	void AddListener(EventType Type, EventListener* eventlistener);
	void BroadcastEvent(EventType Type, void* eventData);

	//void RemoveListener(EventType Type, EventListener* eventlistener);

private:
	EventSystem(); // Private constructor so that no objects can be created.
	static EventSystem* instance;

	// List of Listeners registed sorted by EventType
	std::vector<std::vector<EventListener*>> listOfEventListenerLists;
};
