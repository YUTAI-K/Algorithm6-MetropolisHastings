#pragma once

#include <random>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

// Algorithm6: A struct designed to model a Bayesian updating process with prior distributions
struct Algorithm6
{
    const std::vector<double> data; // Holds the data to be clustered
    const double alpha; // Concentration parameter for the distribution
    const int len_data; // Number of data points
    const int num_iter; // Number of iterations to run the algorithm
    const int R; // Number of updates attempted for each element in each iteration

    const double mu; // Mean of the prior distribution
    const double sigma; // Standard deviation of the prior distribution
    const double individual_sigma; // Standard deviation for individual updates

    // Constructor
    Algorithm6(const std::vector<double>& data, double alpha, int len_data, int num_iter, int R, double mu, double sigma, double individual_sigma);

    // Generate a random number from the prior distribution
    double G0();

    // Calculate the acceptance probability for a proposed change
    double acceptance_probability(const double& yi, const double& theta_current, const double& theta_proposed, const double& stddev);

    // Calculate the probability density function of a normal distribution, without scaling
    double pdf_normal(const double& yi, const double& mean, const double& stddev);

    // Initialize the vector with random values drawn from the prior distribution
    void initialize(std::vector<double>& vec);

    // Run the Bayesian updating process over multiple iterations
    std::vector<std::vector<double>> run();
};
