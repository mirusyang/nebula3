#pragma once
#ifndef WIN32_WIN32CPU_H
#define WIN32_WIN32CPU_H
//------------------------------------------------------------------------------
/**
    @class Win32::Win32Cpu
    
    CPU related definitions for the Win32 platform.  
    
    (C) 2008 Radon Labs GmbH
*/
#include "core/types.h"

//------------------------------------------------------------------------------
namespace Win32
{
class Win32Cpu
{
public:
    typedef DWORD CoreId;
    
    /// core identifiers, under Win32, we basically don't care...
    static const CoreId InvalidCoreId    = 0xffffffff;
    static const CoreId MainThreadCore   = 0;
    static const CoreId IoThreadCore     = 2;
    static const CoreId RenderThreadCore = 1;
    static const CoreId AudioThreadCore  = 3;
    static const CoreId MiscThreadCore   = 4;
};

} // namespace Win32    
//------------------------------------------------------------------------------
#endif
