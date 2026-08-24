#include <ftxui/ftxui.hpp>

#include "hydra/renderer.hpp"

using namespace ftxui;

namespace hydra {
    void render(std::string_view csv_path) {
        auto screen = ScreenInteractive::FullscreenAlternateScreen();
        const std::string file_name(csv_path);

        auto renderer = Renderer([&] {
            auto top = hbox({
                text(file_name),
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
