#include "generate_samples.h"


// Print a histogram of the data
void Sample_generator::print_histogram(const std::vector<double>& data)
{
    const size_t num_bins = 300; // Number of bins for the histogram
    double min = *std::min_element(data.begin(), data.end()); // Minimum data value
    double max = *std::max_element(data.begin(), data.end()); // Maximum data value
    double bin_size = (max - min) / num_bins; // Size of each bin

    std::map<int, int> histogram; // Map to store bin counts
    for (double d : data) {
        int bin = static_cast<int>((d - min) / bin_size); // Determine the appropriate bin for each data point
        if (bin == num_bins) { // Handle edge case where d equals max
            bin--;
        }
        histogram[bin]++; // Increment bin count
    }

    std::cout << "Histogram:" << std::endl;
    for (const auto& bin : histogram) {
        std::cout << "[" << min + bin.first * bin_size << " - " << min + (bin.first + 1) * bin_size << "): ";
        std::cout << std::string(bin.second, '*') << std::endl; // Print bin and its count as asterisks
    }
}

