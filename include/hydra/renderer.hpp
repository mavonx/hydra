#pragma once

#include <string_view>

namespace hydra {
    void render(
        std::string_view csv_path,
        double file_size_gb,
        std::size_t total_rows
    );
}
