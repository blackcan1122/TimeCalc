#pragma once
#include <memory>
//#include "Tickable.h"
#include "Event.hpp"
#include "EventDispatcher.hpp"

class DispatcherEvent : public Event
{
public:
	DispatcherEvent() = default;

	std::string GetName() const override;
	EventDispatcher* GetDispatcher();

	EventDispatcher* CurrentDispatcher;


};