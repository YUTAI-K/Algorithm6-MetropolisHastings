#pragma once

#include <vector>
#include <random>
#include <map>
#include <iostream>
#include <algorithm>

// Sample_generator: A struct to generate samples from a Gaussian mixture model and print histograms of the data
struct Sample_generator
{
    // Generates a vector of doubles sampled from a Gaussian mixture model defined by means and probabilities
    template<typename T>
    std::vector<double> gaussian_mixture(const T& means, const T& probs, const int& n, const double& stddev)
    {
        std::mt19937 generator(4563); // Random number generator
        std::discrete_distribution<> assignment_dist(probs.begin(), probs.end()); // Distribution for choosing mixture components
        std::normal_distribution<double> delta(0, stddev); // Normal distribution for generating deviations

        std::vector<double> data(n);
        for (int i = 0; i < n; ++i)
        {
            int cluster_index = assignment_dist(generator); // Select cluster index based on probabilities
            data[i] = delta(generator) + means[cluster_index]; // Generate sample by adding deviation to mean
        }

        return data;
    }

    // Prints a histogram of the provided data
    void print_histogram(const std::vector<double>& data);
};