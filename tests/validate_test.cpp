#include <filesystem>
#include <fstream>
#include <string>

#include <unistd.h>

#include <gtest/gtest.h>

#include "hydra/validate.hpp"

namespace {
    // Scratch fixture directory, unique per test run and removed on exit.
    class ValidateCsvPathTest : public ::testing::Test {
    protected:
        void SetUp() override {
            fixture_dir_ = std::filesystem::temp_directory_path() /
                           ("hydra_validate_test_" + std::to_string(::getpid()));
            std::filesystem::create_directories(fixture_dir_);

            small_csv_ = fixture_dir_ / "small.csv";
            std::ofstream{small_csv_} << "a,b\n1,2\n";

            not_csv_ = fixture_dir_ / "data.txt";
            std::ofstream{not_csv_} << "a,b\n1,2\n";
        }

        void TearDown() override {
            std::filesystem::remove_all(fixture_dir_);
        }

        std::filesystem::path fixture_dir_;
        std::filesystem::path small_csv_;
        std::filesystem::path not_csv_;
    };

    TEST_F(ValidateCsvPathTest, AcceptsExistingReadableCsv) {
        EXPECT_EQ(hydra::validate_csv_path(small_csv_.string()),
                  hydra::CsvPathStatus::Ok);
    }

    TEST_F(ValidateCsvPathTest, AcceptsCsvExtensionCaseInsensitively) {
        const auto upper = fixture_dir_ / "ORDERS.CSV";
        std::ofstream{upper} << "a,b\n";
        EXPECT_EQ(hydra::validate_csv_path(upper.string()),
                  hydra::CsvPathStatus::Ok);
    }

    TEST_F(ValidateCsvPathTest, RejectsMissingFile) {
        EXPECT_EQ(hydra::validate_csv_path((fixture_dir_ / "missing.csv").string()),
                  hydra::CsvPathStatus::NotOpenable);
    }

    TEST_F(ValidateCsvPathTest, RejectsDirectory) {
        // A directory with a .csv name still must not pass: it is not a
        // regular file even though the extension matches.
        const auto csv_dir = fixture_dir_ / "data.csv";
        std::filesystem::create_directories(csv_dir);
        EXPECT_EQ(hydra::validate_csv_path(csv_dir.string()),
                  hydra::CsvPathStatus::NotOpenable);
    }

    TEST_F(ValidateCsvPathTest, RejectsNonCsvExtension) {
        EXPECT_EQ(hydra::validate_csv_path(not_csv_.string()),
                  hydra::CsvPathStatus::NotCsv);
    }

    TEST_F(ValidateCsvPathTest, RejectsEmptyPath) {
        EXPECT_EQ(hydra::validate_csv_path(""), hydra::CsvPathStatus::NotCsv);
    }

    TEST_F(ValidateCsvPathTest, RejectsCsvSuffixInsideLongerExtension) {
        const auto csvx = fixture_dir_ / "data.csvx";
        std::ofstream{csvx} << "a,b\n";
        EXPECT_EQ(hydra::validate_csv_path(csvx.string()),
                  hydra::CsvPathStatus::NotCsv);
    }
}
