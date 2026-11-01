#pragma once

#include <string_view>
#include <string>
#include <vector>

namespace hydra {
    void render(
        std::string_view csv_path,
        double file_size,
        std::string_view file_size_unit,
        std::size_t total_rows,
        std::vector<std::string> headers
    );
}
