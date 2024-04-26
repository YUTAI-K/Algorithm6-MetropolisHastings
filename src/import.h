#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>  // Include for standard exceptions

struct Reader
{
    std::vector<double> read_csv_as_vector(const std::string& filename) {
        std::vector<double> data;
        std::ifstream file(filename);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return data; // Return empty vector if file could not be opened
        }

        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string cell;

            while (getline(ss, cell, ',')) {
                try {
                    double value = std::stod(cell); // Convert string to double
                    data.push_back(value);
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error: Invalid number encountered (" << e.what() << ")." << std::endl;
                }
            }
        }

        file.close();
        return data;
    }
};