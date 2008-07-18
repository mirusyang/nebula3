#pragma once
#ifndef DEBUG_MESHPAGEHANDLER_H
#define DEBUG_MESHPAGEHANDLER_H
//------------------------------------------------------------------------------
/**
    @class Debug::MeshPageHandler
    
    Provide an HTML debug page with information about shared mesh resources.

    Usage:    
    http://host/mesh                    - provide a list of all meshes with their properties
    http://host/mesh?meshinfo=[resId]   - display information about specific mesh    
    
    (C) 2007 Radon Labs GmbH
*/
#include "http/httprequesthandler.h"
#include "resources/resourceid.h"

//------------------------------------------------------------------------------
namespace Debug
{
class MeshPageHandler : public Http::HttpRequestHandler
{
    DeclareClass(MeshPageHandler);
public:
    /// constructor
    MeshPageHandler();
    /// return true if the http request is accepted by the request handler
    virtual bool AcceptsRequest(const Ptr<Http::HttpRequest>& request);
    /// handle a http request, the handler is expected to fill the content stream with response data
    virtual void HandleRequest(const Ptr<Http::HttpRequest>& request);

private:
    /// display information about specific mesh
    Http::HttpStatus::Code HandleMeshInfoRequest(const Resources::ResourceId& resId, const Ptr<IO::Stream>& responseContentStream);
};

} // namespace Debug
//------------------------------------------------------------------------------
#endif

    