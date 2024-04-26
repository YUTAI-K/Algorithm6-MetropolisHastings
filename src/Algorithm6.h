#pragma once


#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iostream>
#include <iomanip>

struct Algorithm6
{
    const std::vector<double> data{}; // vector holding the data to be clustered
    const double alpha{}; // concentration parameter.
    const int len_data{}; // length of data
    const int num_iter{}; // number of iterations to run
    const int R{}; // See the paper. Is the number of updates we will try for each i in each iteration.

    const double mu{}; // mean of prior
    const double sigma{}; // standard deviation of the prior
    const double individual_sigma{}; // standard deviations of each individual



    double G0()
    //Both the engine and the distribution will be initialized only once, since, this is the prior.
    {
        static std::mt19937 generator(4643);
        static std::normal_distribution<double> distribution(mu, sigma);

        return distribution(generator); // Return a rand number generated
    }


    double acceptance_probability(const double& yi, const double& theta_current, const double& theta_proposed, const double& stddev)
    {
        return std::min(1.0, pdf_normal(yi, theta_proposed, stddev) / pdf_normal(yi, theta_current, stddev));
    }


    double pdf_normal(const double& yi, const double& mean, const double& stddev) // Here is computing the pdf of normal, but with out the scaler part
    // We don't care about the scaler part since they are going to cancel. see above function.
    {
        return   std::exp(-0.5 * ((yi - mean) / stddev) * ((yi - mean) / stddev)) / stddev;
    }

    void initialize(std::vector<double>& vec)
    {
        for (int i = 0; i < len_data; ++i)
        {
            vec[i] = G0();
        }
    }

    std::vector<std::vector<double>> run()
    {
        std::vector<std::vector<double>> history(num_iter); // matrix to store the history of the algorithm;

        std::vector<double> theta(len_data); // vector of length n
        initialize(theta);

        std::vector<double> theta_minus_i(theta); // copy the vector theta to hold all values of vector theta except theta[i]

        double theta_proposed{};

        // Create weights
        std::vector<double> weights(len_data - 1, 1.0 / (len_data - 1 + alpha));
        weights.push_back(alpha / (len_data - 1 + alpha));

        // Setup random number generators
        std::mt19937 gen(34413);
        std::discrete_distribution<> weight_dist(weights.begin(), weights.end());// This distriubtion will be used for the CRP selection
        std::normal_distribution<double> delta(0, individual_sigma); // This one used for individual distributions
        // Uniform distribution between 0 and 1
        std::uniform_real_distribution<double> dist_uniform(0.0, 1.0); // This one used for judge the acceptance probablity

        for (int it = 0; it < num_iter; ++it)
        {
            history.push_back(theta); // Update the history

            for (int i = 0; i < len_data; ++i)
            {
                theta_minus_i.erase(theta_minus_i.begin() + i);

                for (int r = 0; r < R; ++r)
                {
                    int index = weight_dist(gen); // the distribution selects from 0 to len_data-1

                    // Debug: Print the chosen index
                    // std::cout << "Chosen index: " << index << std::endl;

                    // propose new theta
                    if (index == len_data - 1)
                    {
                        theta_proposed = G0();
                    }
                    else
                    {
                        theta_proposed = delta(gen) + theta_minus_i[index]; // We don't create a new distribution, instead we adjust the old one
                    }

                    double probility_of_accept{ acceptance_probability(data[i], theta[i], theta_proposed, individual_sigma) };

                    if (dist_uniform(gen) < probility_of_accept)
                    {
                        theta[i] = theta_proposed;
                        break;
                    }

                }

                theta_minus_i.insert(theta_minus_i.begin() + i, theta[i]);  // add back the ith element, prepare for next iteration;
            }

            // Print something every 10 iterations
            if (it % 10 == 0)
            {
                std::cout << "\nIteration: " << it << '\n';
                for (int i = 0; i < 10; ++i)
                {
                    std::cout << std::fixed << std::setprecision(2) << theta[i] << ' ';
                }
            }
        }

        return history;
    }
};
