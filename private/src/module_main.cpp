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
            X11WindowManager x11_window_manager;

            DllLoader()
            {
                x11_window_manager.initialize();
                Core::ModuleManager::registerInterface<Interface::Window::IWindowManager>(
                    "x11_window_manager", 
                    &x11_window_manager
                );
            }

            ~DllLoader()
            {
                Core::ModuleManager::unregisterInterface<Interface::Window::IWindowManager>(
                    &x11_window_manager
                );
                x11_window_manager.finalize();
            }
        } dll_loader;
    }
}