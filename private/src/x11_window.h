#pragma once
#include "interface/window/window.h"
#include "base/interop/interface.h"

#include <x11/xlib.h>

namespace Arieo
{
    class X11WindowManager;
    class X11Window final
        : public Interface::Window::IWindow
    {
    public:
        X11Window(Display* display, Window&& x11_window)
            : m_display(display), m_x11_window(std::move(x11_window))
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
                m_display,
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
                m_display,
                m_x11_window,
                &w_attributes
            );
            
            return Base::Math::Vector<std::uint32_t, 2>(w_attributes.width, w_attributes.height);
        }        

        bool isClosed() override
        {
            XWindowAttributes attrs;
            if (::XGetWindowAttributes(m_display, m_x11_window, &attrs) == false) 
            {
                // Failed to get attributes - window likely closed
                return true;
            }
            return false;
        }

        Base::StringID getWindowPlatform() override
        {
            return Base::MakeStringID("x11");
        } 
    private:
        friend class X11WindowManager;
        Window m_x11_window;
        Display* m_display = nullptr;
    };

    class X11WindowManager final
        : public Interface::Window::IWindowManager
    {
    private:
        Display* m_display = nullptr;
        std::unordered_set<Base::Interop<Interface::Window::IWindow>> m_window_set;
    public:
        void initialize();
        void finalize();

        void* getDisplay() override;

        Base::Interop<Interface::Window::IWindow> createWindow(std::uint16_t pos_x, std::uint16_t pos_y, std::uint16_t width, std::uint16_t height) override;
        void destroyWindow(Base::Interop<Interface::Window::IWindow>) override;

        Base::Interop<Interface::Window::IWindow> getMainWindow() override;
    public:
        void onInitialize() override;
        void onTick() override;
        void onDeinitialize() override;
    };
}