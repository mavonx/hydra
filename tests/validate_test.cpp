#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "hydra/validate.hpp"

// ---------------------------------------------------------------------------
// Extension Validation Tests
// ---------------------------------------------------------------------------

TEST(ValidateExtensionTest, ValidCsvExtensions) {
    EXPECT_TRUE(hydra::has_csv_extension("data.csv"));
    EXPECT_TRUE(hydra::has_csv_extension("DATA.CSV"));
    EXPECT_TRUE(hydra::has_csv_extension("report.Csv"));
    EXPECT_TRUE(hydra::has_csv_extension("archive.CsV"));
    EXPECT_TRUE(hydra::has_csv_extension("my.dataset.2026.csv"));
    EXPECT_TRUE(hydra::has_csv_extension(".csv"));
    EXPECT_TRUE(hydra::has_csv_extension("path/to/nested/file.csv"));
    EXPECT_TRUE(hydra::has_csv_extension("folder.csv/actual_file.csv"));
    EXPECT_TRUE(hydra::has_csv_extension("file with spaces.csv"));
}

TEST(ValidateExtensionTest, InvalidCsvExtensions) {
    EXPECT_FALSE(hydra::has_csv_extension("data.tsv"));
    EXPECT_FALSE(hydra::has_csv_extension("data.txt"));
    EXPECT_FALSE(hydra::has_csv_extension("data.json"));
    EXPECT_FALSE(hydra::has_csv_extension("data.cs"));
    EXPECT_FALSE(hydra::has_csv_extension("data.csvx"));
    EXPECT_FALSE(hydra::has_csv_extension("data.csv_backup"));
    EXPECT_FALSE(hydra::has_csv_extension("data.csv "));
    EXPECT_FALSE(hydra::has_csv_extension("data.csv.gz"));
}

TEST(ValidateExtensionTest, MissingExtensionsAndEdgeCases) {
    EXPECT_FALSE(hydra::has_csv_extension(""));
    EXPECT_FALSE(hydra::has_csv_extension("."));
    EXPECT_FALSE(hydra::has_csv_extension(".."));
    EXPECT_FALSE(hydra::has_csv_extension("..."));
    EXPECT_FALSE(hydra::has_csv_extension(".cs"));
    EXPECT_FALSE(hydra::has_csv_extension("csv"));
    EXPECT_FALSE(hydra::has_csv_extension("csv."));
    EXPECT_FALSE(hydra::has_csv_extension("data_file"));
    EXPECT_FALSE(hydra::has_csv_extension("path/to/folder/"));
}

TEST(ValidateExtensionTest, StressLongAndExtremeStrings) {
    const std::string long_prefix(100'000, 'a');
    EXPECT_TRUE(hydra::has_csv_extension(long_prefix + ".csv"));
    EXPECT_TRUE(hydra::has_csv_extension(long_prefix + ".CSV"));
    EXPECT_FALSE(hydra::has_csv_extension(long_prefix + ".tsv"));
    EXPECT_FALSE(hydra::has_csv_extension(long_prefix));
}

// ---------------------------------------------------------------------------
// Filesystem Validation Tests (Isolated with Temporary Directory)
// ---------------------------------------------------------------------------

class ValidateFileSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        const auto timestamp = std::chrono::steady_clock::now().time_since_epoch().count();
        test_dir_ = std::filesystem::temp_directory_path() / ("hydra_test_" + std::to_string(timestamp));
        std::filesystem::create_directories(test_dir_);
    }

    void TearDown() override {
        std::error_code ec;
        std::filesystem::remove_all(test_dir_, ec);
    }

    std::filesystem::path create_test_file(const std::string& filename, const std::string& content = "") {
        const auto path = test_dir_ / filename;
        std::ofstream file(path);
        if (!content.empty()) {
            file << content;
        }
        file.close();
        return path;
    }

    std::filesystem::path test_dir_;
};

TEST_F(ValidateFileSystemTest, ExistsReturnsTrueForExistingEntries) {
    const auto file = create_test_file("test.csv");
    EXPECT_TRUE(hydra::exists(file.string()));
    EXPECT_TRUE(hydra::exists(test_dir_.string()));
}

TEST_F(ValidateFileSystemTest, ExistsReturnsFalseForNonExistentPaths) {
    const auto non_existent = test_dir_ / "non_existent_file.csv";
    EXPECT_FALSE(hydra::exists(non_existent.string()));
    EXPECT_FALSE(hydra::exists(""));
}

TEST_F(ValidateFileSystemTest, IsDirectoryValidatesCorrectly) {
    const auto file = create_test_file("regular_file.csv");
    const auto sub_dir = test_dir_ / "sub_directory.csv";
    std::filesystem::create_directories(sub_dir);

    EXPECT_TRUE(hydra::is_directory(test_dir_.string()));
    EXPECT_TRUE(hydra::is_directory(sub_dir.string()));
    EXPECT_FALSE(hydra::is_directory(file.string()));
    EXPECT_FALSE(hydra::is_directory((test_dir_ / "missing_dir").string()));
    EXPECT_FALSE(hydra::is_directory(""));
}

TEST_F(ValidateFileSystemTest, IsReadableFileReturnsTrueForRegularReadableFiles) {
    const auto empty_file = create_test_file("empty.csv");
    const auto content_file = create_test_file("data.csv", "id,name\n1,alpha\n");

    EXPECT_TRUE(hydra::is_readable_file(empty_file.string()));
    EXPECT_TRUE(hydra::is_readable_file(content_file.string()));
}

TEST_F(ValidateFileSystemTest, IsReadableFileReturnsFalseForDirectoriesAndNonExistentFiles) {
    const auto file_like_dir = test_dir_ / "fake_file.csv";
    std::filesystem::create_directories(file_like_dir);

    EXPECT_FALSE(hydra::is_readable_file(test_dir_.string()));
    EXPECT_FALSE(hydra::is_readable_file(file_like_dir.string()));
    EXPECT_FALSE(hydra::is_readable_file((test_dir_ / "does_not_exist.csv").string()));
    EXPECT_FALSE(hydra::is_readable_file(""));
}

TEST_F(ValidateFileSystemTest, IsReadableFileReturnsFalseForUnreadableFiles) {
    const auto file = create_test_file("no_read_perm.csv", "secret");

    std::error_code ec;
    std::filesystem::permissions(file, std::filesystem::perms::none, std::filesystem::perm_options::replace, ec);
    if (!ec) {
        EXPECT_FALSE(hydra::is_readable_file(file.string()));
        // Restore permissions for teardown cleanup
        std::filesystem::permissions(file, std::filesystem::perms::all, ec);
    }
}

TEST_F(ValidateFileSystemTest, HandlesSpecialCharactersAndUnicodePaths) {
    const auto unicode_file = create_test_file("данные_тест_📊.csv", "col1,col2\n1,2\n");
    EXPECT_TRUE(hydra::has_csv_extension(unicode_file.string()));
    EXPECT_TRUE(hydra::exists(unicode_file.string()));
    EXPECT_TRUE(hydra::is_readable_file(unicode_file.string()));
    EXPECT_FALSE(hydra::is_directory(unicode_file.string()));
}

TEST_F(ValidateFileSystemTest, HandlesSymlinksCorrectly) {
    const auto target_file = create_test_file("target.csv", "hello,world\n");
    const auto symlink_file = test_dir_ / "symlink.csv";
    std::error_code ec;
    std::filesystem::create_symlink(target_file, symlink_file, ec);
    if (!ec) {
        EXPECT_TRUE(hydra::exists(symlink_file.string()));
        EXPECT_TRUE(hydra::is_readable_file(symlink_file.string()));
        EXPECT_FALSE(hydra::is_directory(symlink_file.string()));
    }

    const auto broken_symlink = test_dir_ / "broken.csv";
    std::filesystem::create_symlink(test_dir_ / "does_not_exist.csv", broken_symlink, ec);
    if (!ec) {
        EXPECT_FALSE(hydra::exists(broken_symlink.string()));
        EXPECT_FALSE(hydra::is_readable_file(broken_symlink.string()));
        EXPECT_FALSE(hydra::is_directory(broken_symlink.string()));
    }
}

TEST_F(ValidateFileSystemTest, StressRapidFileCreationAndValidation) {
    for (int i = 0; i < 500; ++i) {
        const std::string name = "stress_" + std::to_string(i) + ".csv";
        const auto file = create_test_file(name, "x,y\n10,20\n");
        EXPECT_TRUE(hydra::has_csv_extension(file.string()));
        EXPECT_TRUE(hydra::exists(file.string()));
        EXPECT_TRUE(hydra::is_readable_file(file.string()));
        EXPECT_FALSE(hydra::is_directory(file.string()));
    }
}
