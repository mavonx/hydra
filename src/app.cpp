#include <ftxui/ftxui.hpp>

#include "hydra/app.hpp"

using namespace ftxui;

namespace hydra {
    void run(std::string_view csv_path) {
        auto screen = ScreenInteractive::FullscreenAlternateScreen();
        const std::string file_name(csv_path);

        auto renderer = Renderer([&] {
            auto top = hbox({
                text("hydra❤️"),
                filler(),
                text(file_name)
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
