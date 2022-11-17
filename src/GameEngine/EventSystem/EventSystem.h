#pragma once

class EventSystem
{
public:
	~EventSystem();
	static EventSystem* GetInstance();

	void AddListener(EventType Type, EventListener* eventlistener);
	void BroadcastEvent(EventType Type, void* eventData);
	void RemoveAllListeners();
	void RemoveListener(EventType Type, EventListener* eventlistener);

private:
	EventSystem(); // Private constructor so that no objects can be created.
	static EventSystem* instance;

	// List of Listeners registed sorted by EventType
	std::vector<std::vector<EventListener*>> listOfEventListenerLists;
};


// This Event System Approach:
// Register "Listeners" that want to receive this event
// When event triggered, do callbacks
// Faster but need to manage register/ unregister and manage callbacks

// Another Event System Approach:
// Register "Events" -> Broadcast all events to all gobjs in the loop
// -> gobj filter the events they want then do logic on it -> Events are done, unregister
// Needs traversal so slower, but don't need to care about managing register/ unregister and callbacks
// In Components.h & Node.h we comment out virtual void HandleEvent(void* eventData)
// which is a placeholder for this approach