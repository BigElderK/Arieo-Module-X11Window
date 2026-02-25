#pragma once
#include "interface/window/window.h"
#include "base/interface/interface.h"

#include <x11/xlib.h>

namespace Arieo
{
    class X11WindowManager;
    class X11Window final
        : public Interface::Window::IWindow
    {
    public:
        X11Window(Interface::Window::IWindowManager* window_manager, Window&& x11_window)
            : m_window_manager(window_manager), m_x11_window(std::move(x11_window))
        {

        }

        std::uint64_t getWindowHandle() override
        {
            return reinterpret_cast<std::uint64_t>(m_x11_window);
        }

        Base::Math::Rect<std::uint32_t> getWindowRect() override
        {
            XWindowAttributes w_attributes;
            XGetWindowAttributes(
                (Display*)m_window_manager->getDisplay(),
                m_x11_window,
                &w_attributes
            );

            return Base::Math::Rect<std::uint32_t>(
                w_attributes.x,
                w_attributes.y,
                w_attributes.width,
                w_attributes.height
            );
        }
        
        Base::Math::Vector<std::uint32_t, 2> getFramebufferSize() override
        {
            XWindowAttributes w_attributes;
            XGetWindowAttributes(
                (Display*)m_window_manager->getDisplay(),
                m_x11_window,
                &w_attributes
            );
            
            return Base::Math::Vector<std::uint32_t, 2>(w_attributes.width, w_attributes.height);
        }        

        bool isClosed() override
        {
            XWindowAttributes attrs;
            if (::XGetWindowAttributes(reinterpret_cast<Display*>(m_window_manager->getDisplay()), m_x11_window, &attrs) == false) 
            {
                // Failed to get attributes - window likely closed
                return true;
            }
            return false;
        }

        Base::Interface<Interface::Window::IWindowManager> getWindowManager() override
        {
            return m_window_manager.get();
        }

        Base::StringID getWindowPlatform() override
        {
            return Base::MakeStringID("x11");
        } 
    private:
        friend class X11WindowManager;
        Window m_x11_window;
        Base::Interface<Interface::Window::IWindowManager> m_window_manager;
    };

    class X11WindowManager final
        : public Interface::Window::IWindowManager
    {
    private:
        Display* m_display = nullptr;
        std::unordered_set<X11Window*> m_window_set;
    public:
        void initialize();
        void finalize();

        void* getDisplay() override;

        Base::Interface<Interface::Window::IWindow> createWindow(std::uint16_t pos_x, std::uint16_t pos_y, std::uint16_t width, std::uint16_t height) override;
        void destroyWindow(Base::Interface<Interface::Window::IWindow>) override;

        Base::Interface<Interface::Window::IWindow> getMainWindow() override;
    public:
        void onInitialize() override;
        void onTick() override;
        void onDeinitialize() override;
    };
}