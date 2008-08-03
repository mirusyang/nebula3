#pragma once
#ifndef WIN32_WIN32INPUTSERVER_H
#define WIN32_WIN32INPUTSERVER_H
//------------------------------------------------------------------------------
/**
    @class Win32::Win32InputServer
    
    Win32-specific InputServer (provides a default Keyboard and Mouse).
    
    (C) 2007 Radon Labs GmbH
*/
#include "core/singleton.h"
#include "input/base/inputserverbase.h"
#include "input/win32/win32inputdisplayeventhandler.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

//------------------------------------------------------------------------------
namespace Win32
{
class Win32InputServer : public Base::InputServerBase
{
    DeclareClass(Win32InputServer);
    DeclareSingleton(Win32InputServer);
public:
    /// constructor
    Win32InputServer();
    /// destructor
    virtual ~Win32InputServer();

    /// open the input server
    void Open();
    /// close the input server
    void Close();
    /// call after processing window events (reads DInput raw mouse events)
    void OnFrame();
    /// call after window gains/loses input focus
    void SetFocus(bool);

    /// set the parent window HWND
    void SetParentHwnd(HWND hWnd);

protected:
    friend class Win32Mouse;

    /// setup the DirectInput mouse device for tracking mouse movement 
    bool OpenDInputMouse();
    /// shutdown the DirectInput mouse device
    void CloseDInputMouse();
    /// get mouse readings
    void ReadDInputMouse();
    /// get the current mouse movement
    const Math::float2& GetMouseMovement() const;

    Ptr<Win32InputDisplayEventHandler> eventHandler;
    IDirectInput8* di8;
    IDirectInputDevice8* di8Mouse;
    Math::float2 mouseMovement;
    bool wndHasFocus; // ignored unless hWndParent is set
    HWND hWndParent;
    static const int DInputMouseBufferSize = 16;
};

//------------------------------------------------------------------------------
/**
*/
inline const Math::float2&
Win32InputServer::GetMouseMovement() const
{
    return this->mouseMovement;
}

} // namespace Win32
//------------------------------------------------------------------------------
#endif
    