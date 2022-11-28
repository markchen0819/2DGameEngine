#pragma once

class WaveEvent : public Event
{
public:
	WaveEvent(std::string name) : WaveSideName(name) {};
	~WaveEvent() {};

	std::string WaveSideName;
	// WaveR, WaveL, WaveU, WaveD
};