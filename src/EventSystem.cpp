#include "EventSystem.h"

Event::Event() { Type = EventType::Default; }
Event::~Event() {}

EventSystem* EventSystem::instance = nullptr;
EventSystem& EventSystem::GetInstance()
{
	static EventSystem instance; // Guaranteed to be destroyed,  Instantiated on first use.
	return instance;
}
EventSystem::~EventSystem() { observers.clear(); }



void EventSystem::RegisterEvent(EventType Type, MyDelegate&& d)
{
	observers[Type].push_back(d);
}

void EventSystem::BroadcastEvent(Event* event) const
{
	auto type = (*event).Type;

	if (observers.find(type) == observers.end()) // No registered
	{
		return;
	}

	auto&& filteredObservers = observers.at(type);
	for (auto&& observer : filteredObservers)
	{
		observer((*event));
	}

}
