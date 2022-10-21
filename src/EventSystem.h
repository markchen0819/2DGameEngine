#pragma once
#include <functional>
#include <map>
#include <vector>
#include <iostream>

enum class EventType
{
	Collision,
	Default
};

class Event
{
public:
	Event();
	virtual ~Event();
	EventType Type = EventType::Default;
};

class EventListener
{
public:
	virtual void HandleEvent(const Event& e){}
	EventType Type = EventType::Default;
};

class EventSystem
{
public:
	~EventSystem();
	static EventSystem& GetInstance();

	using MyDelegate = std::function< void(const Event&)>; 

	void RegisterEvent(EventType Type, MyDelegate&& d); // C++ 11
	void BroadcastEvent(Event* event) const;

private:
	EventSystem() {}; // Private constructor so that no objects can be created.
	static EventSystem* instance;
	std::map<EventType, std::vector<MyDelegate>> observers;
};


/////////////////// Testing to check if the EventSystem works ///////////////////

//using namespace std::placeholders;
//TestEventListener tel;
//eventSystem.RegisterEvent(EventType::Default, std::bind(&TestEventListener::HandleEvent, tel, _1));
//eventSystem.BroadcastEvent(TestEvent());

class TestEvent : public Event
{
public:
	TestEvent(){ Type = EventType::Default; };
	~TestEvent() {};

	void print() const
	{
		std::cout << "TestEvent!" << std::endl;
	}
};

class TestEventListener : public EventListener
{
public:
	virtual void HandleEvent(const Event& e)
	{
		if (e.Type == Type) // Default
		{
			const TestEvent& testEvent = static_cast<const TestEvent&>(e);
			testEvent.print();
		}
	}
};
