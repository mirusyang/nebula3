//------------------------------------------------------------------------------
//  remotecontrolproxy.cc
//  (C) 2008 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "remote/remotecontrolproxy.h"
#include "remote/remoteprotocol.h"
#include "remote/remoteinterface.h"

namespace Remote
{
__ImplementClass(Remote::RemoteControlProxy, 'RECP', Core::RefCounted);
__ImplementSingleton(Remote::RemoteControlProxy);

//------------------------------------------------------------------------------
/**
*/
RemoteControlProxy::RemoteControlProxy() :
    isOpen(false)
{
    __ConstructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
RemoteControlProxy::~RemoteControlProxy()
{
    n_assert(!this->isOpen);
    __DestructSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void
RemoteControlProxy::Open()
{
    n_assert(!this->isOpen);
    n_assert(this->requestHandlers.IsEmpty());
    this->isOpen = true;
}

//------------------------------------------------------------------------------
/**
*/
void
RemoteControlProxy::Close()
{
    n_assert(this->isOpen);
    
    // cleanup request handlers
    while (this->requestHandlers.Size() > 0)
    {
        this->RemoveRequestHandler(this->requestHandlers.Back());
    }
    this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
*/
void
RemoteControlProxy::AttachRequestHandler(const Ptr<RemoteRequestHandler>& requestHandler)
{
    n_assert(this->isOpen);
    this->requestHandlers.Append(requestHandler);

    // register request handler with RemoteControl thread 
    Ptr<Remote::AttachRequestHandler> msg = Remote::AttachRequestHandler::Create();
    msg->SetRequestHandler(requestHandler);
    RemoteInterface::Instance()->Send(msg.cast<Messaging::Message>());
}

//------------------------------------------------------------------------------
/**
*/
void
RemoteControlProxy::RemoveRequestHandler(const Ptr<RemoteRequestHandler>& requestHandler)
{
    n_assert(this->isOpen);    
    IndexT index = this->requestHandlers.FindIndex(requestHandler);
    n_assert(InvalidIndex != index);
    
    // unregister request handler from RemoteControl thread
    Ptr<Remote::RemoveRequestHandler> msg = Remote::RemoveRequestHandler::Create();
    msg->SetRequestHandler(requestHandler);
    RemoteInterface::Instance()->Send(msg.cast<Messaging::Message>());

    // delete from local array
    this->requestHandlers.EraseIndex(index);
}

//------------------------------------------------------------------------------
/**
*/
void
RemoteControlProxy::HandlePendingRequests()
{
    n_assert(this->isOpen);

    IndexT i;
    for (i = 0; i < this->requestHandlers.Size(); i++)
    {
        this->requestHandlers[i]->HandlePendingRequests();
    }
}

} // namespace Remote