#pragma once
#include <iostream>
#include <fstream>
#include <vector>

void exportToCSV(const std::vector<std::vector<double>>& history, const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "\nFailed to open file for writing." << std::endl;
        return;
    }

    for (const auto& row : history) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }

    file.close();
    std::cout << "Data exported successfully to " << filename << '\n';
}
