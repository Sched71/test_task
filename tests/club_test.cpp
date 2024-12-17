#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

#include "computer_club.h"

void AssertOutputEqualExpected(std::string expected_file) {
    std::ifstream ifs_output("tests/output");
    std::ifstream ifs_expected(expected_file);
    std::string output_line;
    std::string expected_line;
    while (!ifs_output.eof() && !ifs_expected.eof()) {
        std::getline(ifs_output, output_line);
        std::getline(ifs_expected, expected_line);
        ASSERT_EQ(output_line, expected_line);
    }
    ASSERT_EQ(ifs_output.eof(), ifs_expected.eof());
}

TEST(Base, ExampleTest) {
    std::fstream fs("tests/output", std::ios::out | std::ios::trunc);
    {
        ComputerClub c("tests/test_data/example_in", fs);
        c.ProcessInput();
    }
    fs.close();
    AssertOutputEqualExpected("tests/test_data/example_out");
}

TEST(Base, ErrorTest) {
    std::fstream fs("tests/output", std::ios::out | std::ios::trunc);
    {
        ComputerClub c("tests/test_data/errors_in", fs);
        c.ProcessInput();
    }
    fs.close();
    AssertOutputEqualExpected("tests/test_data/errors_out");
}


TEST(Format, FormatCheckTest1) {
    EXPECT_ANY_THROW({
        try {
            ComputerClub c("tests/test_data/format1", std::cout);
        } catch(std::exception const& e) {
            std::cerr << e.what() << '\n';
            throw;
        }
    });
}

TEST(Format, FormatCheckTest2) {
    EXPECT_ANY_THROW({
        try {
            ComputerClub c("tests/test_data/format2", std::cout);
        } catch(std::exception const& e) {
            std::cerr << e.what() << '\n';
            throw;
        }
    });
}

TEST(Format, FormatCheckTest3) {
    EXPECT_ANY_THROW({
        try {
            ComputerClub c("tests/test_data/format3", std::cout);
        } catch(std::exception const& e) {
            std::cerr << e.what() << '\n';
            throw;
        }
    });
}

TEST(Format, FormatCheckTest4) {
    EXPECT_ANY_THROW({
        try {
            ComputerClub c("tests/test_data/format4", std::cout);
        } catch(std::exception const& e) {
            std::cerr << e.what() << '\n';
            throw;
        }
    });
}
