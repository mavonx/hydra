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
        double file_size_gb,
        std::size_t total_rows,
        const std::vector<std::string>& headers
    ) {
        auto screen = ScreenInteractive::FullscreenAlternateScreen();

        std::string formatted_size = get_file_size_formatted(file_size_gb);

        const std::string file_info =
            std::string(csv_path) +
            " - " +
            std::to_string(total_rows) +
            " rows " +
            "(file: " +
            formatted_size +
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

    std::string get_file_size_formatted(double file_size) {
        std::vector<std::string> size_types{
            "GB", "MB", "KB", "B"
        };

        std::size_t type_index = 0;
        while (file_size < 1.0 && type_index < size_types.size() - 1) {
            file_size *= 1024;
            ++type_index;
        }

        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << file_size;

        return stream.str() + " " + size_types[type_index];
    }
}
