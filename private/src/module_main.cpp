#include "base/prerequisites.h"
#include "core/core.h"
#include "x11_window.h"
namespace Arieo
{
    GENERATOR_MODULE_ENTRY_FUN()
    ARIEO_DLLEXPORT void ModuleMain()
    {
        Core::Logger::setDefaultLogger("x11_window");

        static struct DllLoader
        {
            Base::Instance<X11WindowManager> x11_window_manager;

            DllLoader()
            {
                x11_window_manager->setSelf(x11_window_manager.queryInterface<Interface::Window::IWindowManager>());
                x11_window_manager->initialize();
                
                Core::ModuleManager::registerInstance<Interface::Window::IWindowManager, X11WindowManager>(
                    "x11_window_manager", 
                    x11_window_manager
                );
            }

            ~DllLoader()
            {
                Core::ModuleManager::unregisterInstance<Interface::Window::IWindowManager, X11WindowManager>(
                    x11_window_manager
                );
                x11_window_manager->finalize();
            }
        } dll_loader;
    }
}