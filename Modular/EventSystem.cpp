#include "EventSystem.h"
#include "CustomMessages.h"
#include "Win.h"

void EventSystem::FilterEvents()
{

}

void EventSystem::Push_Event(EventSystem::Events event)
{
	HWND handle;
	handle = FindWindowA(NULL, "Modular Engine");
	eventBuffer.push(event);
	switch (event)
	{
	case EventSystem::Events::LUA_EVENT:
		SendMessage(handle,	LUA_EVENTX, (WPARAM)0, (LPARAM)0);
		break;
	case EventSystem::Events::CUSTOM_EVENT:
		SendMessage(handle, CUSTOM_EVENTX, (WPARAM)0, (LPARAM)0);
		break;
	case EventSystem::Events::ON_UPDATE:
		SendMessage(handle, ON_UPDATEX, (WPARAM)0, (LPARAM) 0);
		break;
	case EventSystem::Events::WINDOW_CREATED:
		SendMessage(handle, WINDOW_CREATEDX, (WPARAM) 0, (LPARAM) 0);
		break;
	}
	TrimBuffer();
}

std::optional<EventSystem::Events> EventSystem::Read()
{
	if (eventBuffer.size() > 0u)
	{
		EventSystem::Events e = eventBuffer.front();
		eventBuffer.pop();
		return e;
	}
	return {};
}

void EventSystem::Flush() noexcept
{
	eventBuffer = std::queue<Events>();
}

void EventSystem::TrimBuffer()
{
	if (eventBuffer.size() > bufferSize)
	{
		eventBuffer.pop();
	}
}