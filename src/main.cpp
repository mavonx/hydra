#include <iostream>

#include "hydra/validate.hpp"
#include "hydra/renderer.hpp"
#include "hydra/inspect.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: hydra <file.csv>\n";
        return 1;
    }

    const std::string_view csv_path = argv[1];

    if (!hydra::has_csv_extension(csv_path)) {
        std::cerr << "Error: file must be a .csv file\n";
        return 1;
    }

    if (!hydra::file_exists(csv_path)) {
        std::cerr << "Error: file does not exist: " << csv_path << "\n";
        return 1;
    }

    if (!hydra::is_readable_file(csv_path)) {
        std::cerr << "Could not open file: " << csv_path << "\n";
        return 1;
    }

    hydra::render(
        csv_path,
        hydra::get_file_size_gb(csv_path),
        hydra::count_csv_rows(csv_path)
    );

    return 0;
}
