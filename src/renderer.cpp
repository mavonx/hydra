#include <ftxui/ftxui.hpp>
#include <iomanip>
#include <sstream>
#include <string>

#include "hydra/renderer.hpp"

using namespace ftxui;

namespace hydra {
    void render(
        std::string_view csv_path,
        double file_size_gb,
        std::size_t total_rows
    ) {
        auto screen = ScreenInteractive::FullscreenAlternateScreen();

        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << file_size_gb;
        std::string formatted_size = stream.str();

        const std::string file_info =
            std::string(csv_path) +
            " - " +
            std::to_string(total_rows) +
            " rows " +
            "(file: " +
            formatted_size +
            " GB)";

        auto renderer = Renderer([&] {
            auto top = hbox({
                text(file_info),
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
