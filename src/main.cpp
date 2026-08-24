#include <iostream>

#include "hydra/app.hpp"
#include "hydra/validate.hpp"

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

    hydra::run(csv_path);

    return 0;
}
