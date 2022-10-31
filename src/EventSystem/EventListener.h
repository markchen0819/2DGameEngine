#pragma once

class EventListener
{
public:

	EventListener();
	EventListener(std::function<void(void*)> c, EventType t);
	~EventListener();

	void HandleEvent(void* eventData);
	void SetCallback(std::function<void(void*)> c);
	std::function<void(void*)> GetCallback();

	EventType Type = EventType::Default;

private:
	std::function<void(void*)> callback; // pointer to a function (called when event triggered)

};

