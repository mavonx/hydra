#include <iostream>

#include "hydra/app.hpp"
#include "hydra/validate.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: hydra <file.csv>\n";
        return 1;
    }

    const std::string_view csv_path = argv[1];

    switch (hydra::validate_csv_path(csv_path)) {
        case hydra::CsvPathStatus::NotCsv:
            std::cerr << "Error: file must be a .csv file\n";
            return 1;
        case hydra::CsvPathStatus::NotOpenable:
            std::cerr << "Could not open file: " << csv_path << "\n";
            return 1;
        case hydra::CsvPathStatus::Ok:
            break;
    }

    hydra::run(csv_path);

    return 0;
}
