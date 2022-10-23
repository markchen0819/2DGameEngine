#include "EventSystem.h"

EventSystem* EventSystem::instance = nullptr;
EventSystem& EventSystem::GetInstance()
{
	static EventSystem instance; // Guaranteed to be destroyed,  Instantiated on first use.
	return instance;
}
EventSystem::EventSystem() 
{
	listOfEventListenerLists = new std::vector<std::vector<EventListener*>>();
	// Add in a list for each event type
	for (int i = 0; i != static_cast<int>(EventType::Default); ++i)
	{
		std::vector<EventListener*> listenerListByType;
		listOfEventListenerLists->push_back(listenerListByType);
	}
};
EventSystem::~EventSystem() 
{
	for (int i = 0; i != static_cast<int>(EventType::Default); ++i)
	{
		listOfEventListenerLists->at(i).clear();
	}
	listOfEventListenerLists->clear();
	delete listOfEventListenerLists;
}

void EventSystem::AddListener(EventType Type, EventListener* eventlistener)
{
	int index = static_cast<int>(Type);

	// Get list with that type
	std::vector<EventListener*>* list = &listOfEventListenerLists->at(index);
	list->push_back(eventlistener);
}

void EventSystem::BroadcastEvent(EventType Type, void* eventData)
{
	int index = static_cast<int>(Type);
	std::vector<EventListener*>* list = &listOfEventListenerLists->at(index);
	for(auto el : *list)
	{
		(*el).HandleEvent(eventData);
	}
}
