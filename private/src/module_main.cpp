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
            X11WindowManager x11_window_manager_instance;
            Base::Interop::SharedRef<Interface::Window::IWindowManager> window_manager = Base::Interop::makePersistentShared<Interface::Window::IWindowManager>(x11_window_manager_instance);

            DllLoader()
            {
                x11_window_manager_instance.initialize();

                Base::Interop::SharedRef<Interface::Main::IMainModule> main_module = Core::ModuleManager::getInterface<Interface::Main::IMainModule>();
                main_module->registerTickable(window_manager);

                Core::ModuleManager::registerInterface<Interface::Window::IWindowManager>(
                    "x11_window_manager",
                    window_manager
                );
            }

            ~DllLoader()
            {
                Core::ModuleManager::unregisterInterface<Interface::Window::IWindowManager>(
                    window_manager
                );
                x11_window_manager_instance.finalize();
            }
        } dll_loader;
    }
}




