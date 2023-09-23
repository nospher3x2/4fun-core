#include "EventHandler.hpp"

void EventHandler::Add(EventType type, void* callback)
{
	if (callback == nullptr)
		return;

	if (!EventHandler::Callbacks.contains(type))
		EventHandler::Callbacks.insert({ type, {} });

	std::vector<void*> callbacks = EventHandler::Callbacks[type];
	callbacks.push_back(callback);
	EventHandler::Callbacks[type] = callbacks;
}

void EventHandler::Remove(const EventType type, const void* callback)
{
	if (callback == nullptr)
		return;

	if (!EventHandler::Callbacks.contains(type))
		return;

	std::vector<void*> callbacks = EventHandler::Callbacks[type];
	for (auto it = callbacks.begin(); it != callbacks.end(); ++it)
	{
		if (*it == callback)
		{
			callbacks.erase(it);
			break;
		}
	}
	EventHandler::Callbacks[type] = callbacks;
}