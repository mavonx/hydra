#include <ftxui/ftxui.hpp>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>

#include "hydra/renderer.hpp"

using namespace ftxui;

namespace hydra {
    void render(
        std::string_view csv_path,
        double file_size,
        std::string_view file_size_unit,
        std::size_t total_rows,
        std::vector<std::string> headers
    ) {
        auto screen = ScreenInteractive::FullscreenAlternateScreen();

        std::ostringstream stream;
        if (file_size_unit == "B") {
            stream << static_cast<long long>(file_size);
        } else {
            stream << std::fixed << std::setprecision(2) << file_size;
        }
        std::string formatted_size = stream.str();

        const std::string file_info =
            std::string(csv_path) +
            " - " +
            std::to_string(total_rows) +
            " rows " +
            "(file: " +
            formatted_size +
            " " +
            std::string(file_size_unit) +
            ")";

        std::vector<std::vector<std::string>> table_data;
        table_data.push_back({" # ", "Column"});

        for (size_t i = 0; i < headers.size(); ++i) {
            table_data.push_back({" " + std::to_string(i + 1) + " ", headers[i]});
        }

        auto table = Table(table_data);

        table.SelectAll().Separator(LIGHT);
        table.SelectAll().DecorateCells(center);
        table.SelectAll().Decorate(color(Color::White));

        auto table_element = table.Render();

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
                separatorEmpty(),
                hbox({
                    table_element,
                    filler()
                }),
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
