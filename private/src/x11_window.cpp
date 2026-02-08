
#include "base/prerequisites.h"
#include "core/core.h"

#include "x11_window.h"

namespace Arieo
{
    void X11WindowManager::initialize()
    {
        m_display = XOpenDisplay(nullptr);
        if(m_display == nullptr)
        {
            Core::Logger::fatal("Cannot open display for X11");
        }
    }

    void X11WindowManager::finalize()
    {
        for(X11Window* window : std::unordered_set(m_window_set))
        {
            destroyWindow(window);
        }
        m_window_set.clear();

        if(m_display != nullptr)
        {
            XCloseDisplay(m_display);
            m_display = nullptr;
        }
    }

    void* X11WindowManager::getDisplay()
    {
        return m_display;
    }
    
    Interface::Window::IWindow* X11WindowManager::createWindow(std::uint16_t pos_x, std::uint16_t pos_y, std::uint16_t width, std::uint16_t height)
    {
        Window window = XCreateSimpleWindow(
            m_display, 
            XDefaultRootWindow(m_display),
            pos_x, 
            pos_y,
            width, 
            height, 
            4, 0, 0);
        
        if(window == 0)
        {
            Core::Logger::fatal("Create X11 window failed");
            return nullptr;
        }
        
        XMapWindow(m_display, window);
        XSelectInput(m_display, window, KeyPressMask | ButtonPressMask | ExposureMask);

        X11Window* ret_win = Base::newT<X11Window>(this, std::move(window));
        m_window_set.insert(ret_win);
        return ret_win;
    }

    Interface::Window::IWindow* X11WindowManager::getMainWindow()
    {
        Core::Logger::error("X11WindowManager::getMainWindow() not implemented, using createWindow instead");
        return nullptr;
    }

    void X11WindowManager::destroyWindow(Interface::Window::IWindow* window)
    {
        X11Window* x11_win = Base::castInterfaceToInstance<X11Window>(window);
        if(x11_win == nullptr)
        {
            Core::Logger::fatal("Cannot get x11 window instances");
        }

        XDestroyWindow(m_display, x11_win->m_x11_window);
        m_window_set.erase(x11_win);

        Base::deleteT(x11_win);
    }

    void X11WindowManager::onInitialize()
    {

    }

    void X11WindowManager::onTick()
    {
        XEvent event;
        for(X11Window* window : m_window_set)
        {
            if(XCheckWindowEvent(
                m_display, 
                window->m_x11_window, 
                KeyPressMask | ButtonPressMask | ExposureMask, &event))
            {
                switch(event.type)
                {
                case Expose:
                case ButtonPress:
                    Core::Logger::trace("Button {} Pressed", event.xbutton.button);
                default: break;
                }
            }
        }
    }

    void X11WindowManager::onDeinitialize()
    {

    }
}