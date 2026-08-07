#include <ftxui/ftxui.hpp>

#include "hydra/app.hpp"

using namespace ftxui;

namespace hydra {
    void run() {
        auto screen = ScreenInteractive::FullscreenAlternateScreen();

        auto renderer = Renderer([&] {
            auto top = hbox({
                text("hydra❤️"),
                filler()
            });

            auto bottom = hbox({
                filler(),
                text("Press 'Esc' to exit")
            });

            return vbox({
                top,
                filler(),
                bottom
            });
        });

        auto component = CatchEvent(renderer, [&] (Event event) {
            if(event == Event::Escape) {
                screen.Exit();
                return true;
            }

            return false;
        });

        screen.Loop(component);
    }
}
