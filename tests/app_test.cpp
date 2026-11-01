#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "hydra/inspect.hpp"

namespace {

std::filesystem::path write_temp_file(const std::string& name, std::size_t byte_count) {
    const auto path = std::filesystem::temp_directory_path() / name;
    std::ofstream out(path, std::ios::binary);
    std::vector<char> payload(byte_count, 'a');
    out.write(payload.data(), static_cast<std::streamsize>(payload.size()));
    out.close();
    return path;
}

}  // namespace

TEST(AppTest, StringComparison) {
    EXPECT_EQ("hydra", "hydra");
}

TEST(InspectTest, FileSizeUsesBytesForTinyFiles) {
    const auto path = write_temp_file("hydra_size_bytes.csv", 482);
    const auto [value, unit] = hydra::get_file_size(path.string());
    EXPECT_EQ(unit, "B");
    EXPECT_DOUBLE_EQ(value, 482.0);
    std::filesystem::remove(path);
}

TEST(InspectTest, FileSizeUsesMegabytesForMediumFiles) {
    const auto path = write_temp_file("hydra_size_mb.csv", 3 * 1024 * 1024 + 512 * 1024);
    const auto [value, unit] = hydra::get_file_size(path.string());
    EXPECT_EQ(unit, "MB");
    EXPECT_NEAR(value, 3.50, 0.01);
    std::filesystem::remove(path);
}

TEST(InspectTest, FileSizeUsesKilobytesNearBoundary) {
    const auto path = write_temp_file("hydra_size_kb.csv", 2048);
    const auto [value, unit] = hydra::get_file_size(path.string());
    EXPECT_EQ(unit, "KB");
    EXPECT_NEAR(value, 2.0, 0.01);
    std::filesystem::remove(path);
}
