#pragma once
#include <queue>
#include <optional>
#include <map>

class EventSystem
{
public:
	enum class Events
	{
		LUA_EVENT,
		ON_UPDATE,
		CUSTOM_EVENT,
		WINDOW_CREATED
	};
public:
	~EventSystem() = default;
	void FilterEvents();
	void Push_Event(EventSystem::Events event);
	std::optional<EventSystem::Events> Read();
	void Flush() noexcept;
	void TrimBuffer();
private:
	std::queue<Events> eventBuffer;
	static constexpr unsigned int bufferSize = 16u;
	std::vector<Events> customEvents;
};