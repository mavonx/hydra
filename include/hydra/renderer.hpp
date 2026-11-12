#pragma once

#include <string_view>
#include <string>
#include <vector>

namespace hydra {
    void render(
        std::string_view csv_path,
        std::pair<double, std::string_view> file_size,
        std::size_t total_rows,
        const std::vector<std::string>& headers
    );
}
