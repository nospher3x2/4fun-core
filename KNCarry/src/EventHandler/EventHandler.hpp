#pragma once
#include <map>
#include <vector>

enum struct EventType
{
	OnTick,
	OnPresentDraw,
	OnWndProc,
	Size
};

class EventHandler
{
private:
	static inline std::map<EventType, std::vector<void*>> Callbacks = {};
public:
	template <typename... Args>
	static void Trigger(const EventType type, Args... args)
	{
		for (const auto& callback : EventHandler::Callbacks[type])
		{
			if (callback == nullptr)
				continue;

			static_cast<void(*)(Args...)>(callback)(args...);
		}
	}

	static void Add(EventType type, void* callback);
	static void Remove(EventType type, const void* callback);
};

