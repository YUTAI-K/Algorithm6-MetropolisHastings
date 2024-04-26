#pragma once

#include<vector>
#include<iostream>
#include<random>
#include <map>

struct Sample_generator
{
    template<typename T>
    std::vector<double> gaussian_mixture(const T& means, const T& probs, const int& n, const double& stddev)
    // first two inputs should be two double vectors with same length.
    {
        std::mt19937 generator(4563);
        std::discrete_distribution<> assignment_dist(probs.begin(), probs.end());
        std::normal_distribution<double> delta(0, stddev);


        std::vector<double> data(n);
        for (int i = 0; i < n; ++i)
        {
            int cluster_index = assignment_dist(generator);
            data[i] = delta(generator) + means[cluster_index];
        }

        return data;
    }


    void print_histogram(const std::vector<double>& data)
    {
        const size_t num_bins = 300;
        double min = *std::min_element(data.begin(), data.end());
        double max = *std::max_element(data.begin(), data.end());
        double bin_size = (max - min) / num_bins;

        std::map<int, int> histogram;
        for (double d : data) {
            int bin = static_cast<int>((d - min) / bin_size);
            if (bin == num_bins) { // This handles the edge case where d == max
                bin--;
            }
            histogram[bin]++;
        }

        std::cout << "Histogram:" << std::endl;
        for (const auto& bin : histogram) {
            std::cout << "[" << min + bin.first * bin_size << " - " << min + (bin.first + 1) * bin_size << "): ";
            std::cout << std::string(bin.second, '*') << std::endl;
        }
    }

};