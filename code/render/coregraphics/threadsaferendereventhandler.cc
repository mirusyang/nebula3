//------------------------------------------------------------------------------
//  threadsaferendereventhandler.cc
//  (C) 2007 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "coregraphics/threadsaferendereventhandler.h"

namespace CoreGraphics
{
ImplementClass(CoreGraphics::ThreadSafeRenderEventHandler, 'TREH', CoreGraphics::RenderEventHandler);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
ThreadSafeRenderEventHandler::ThreadSafeRenderEventHandler()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
ThreadSafeRenderEventHandler::~ThreadSafeRenderEventHandler()
{
    // empty
}    

//------------------------------------------------------------------------------
/**
    Put an event into the event handler. This method is called by the
    render thread's RenderDevice. Events are queued until the consumer
    thread processes them by calling HandlePendingEvents().
*/
bool
ThreadSafeRenderEventHandler::PutEvent(const RenderEvent& e)
{
    this->eventQueue.Enqueue(e);
    // return "event unhandled" because we can't know better at this time
    return false;
}

//------------------------------------------------------------------------------
/**
    Process pending events. This method should be called frequently by
    the consumer thread. Pending events will be deqeued from the 
    internel event queue and the HandleEvent() method will be called
    once per event.
*/
void
ThreadSafeRenderEventHandler::HandlePendingEvents()
{
    Array<RenderEvent> pendingEvents = this->eventQueue.DequeueAll();
    IndexT i;
    for (i = 0; i < pendingEvents.Size(); i++)
    {
        this->HandleEvent(pendingEvents[i]);
    }
}

//------------------------------------------------------------------------------
/**
    Handle an event. This method is called in the consumer thread
    context from the HandlePendingEvents() method for each
    pending event. Override this method in your subclass to process
    the event.
*/
bool
ThreadSafeRenderEventHandler::HandleEvent(const RenderEvent& e)
{
    // override in subclass!
    return false;
}

} // namespace CoreGraphics