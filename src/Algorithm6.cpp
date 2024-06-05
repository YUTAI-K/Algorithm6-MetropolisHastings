#include "Algorithm6.h"
#include <algorithm>
#include <numeric>
#include <iterator>

// Constructor to initialize data members
Algorithm6::Algorithm6(const std::vector<double>& data, double alpha, int len_data, int num_iter, int R, double mu, double sigma, double individual_sigma)
    : data(data), alpha(alpha), len_data(len_data), num_iter(num_iter), R(R), mu(mu), sigma(sigma), individual_sigma(individual_sigma)
{
}

// Generate a random number from a normal distribution representing the prior
double Algorithm6::G0()
{
    static std::mt19937 generator(4643); // Random number generator with a fixed seed
    static std::normal_distribution<double> distribution(mu, sigma); // Normal distribution configured with mean and std

    return distribution(generator); // Return a random number generated from the distribution
}

// Compute the acceptance probability of the proposed theta
double Algorithm6::acceptance_probability(const double& yi, const double& theta_current, const double& theta_proposed, const double& stddev)
{
    return std::min(1.0, pdf_normal(yi, theta_proposed, stddev) / pdf_normal(yi, theta_current, stddev));
}

// Compute the probability density function of a normal distribution (unnormalized)
double Algorithm6::pdf_normal(const double& yi, const double& mean, const double& stddev)
{
    return std::exp(-0.5 * std::pow((yi - mean) / stddev, 2)) / stddev;
}

// Initialize the theta vector with values from the prior distribution
void Algorithm6::initialize(std::vector<double>& vec)
{
    for (int i = 0; i < len_data; ++i)
    {
        vec[i] = G0();
    }
}

// Execute the algorithm, performing iterative updates to theta based on acceptance probability
std::vector<std::vector<double>> Algorithm6::run()
{
    std::vector<std::vector<double>> history(num_iter); // Stores the history of updates for analysis

    std::vector<double> theta(len_data); // Stores the current values of theta
    initialize(theta);

    std::vector<double> theta_minus_i(theta); // Used for updates, holding all theta except the current one

    double theta_proposed; // Variable to store proposed updates to theta

    std::vector<double> weights(len_data - 1, 1.0 / (len_data - 1 + alpha));
    weights.push_back(alpha / (len_data - 1 + alpha)); // Weights for choosing updates

    std::mt19937 gen(34413); // Random generator for selecting updates
    std::discrete_distribution<> weight_dist(weights.begin(), weights.end()); // Distribution based on weights
    std::normal_distribution<double> delta(0, individual_sigma); // Normal distribution for generating updates
    std::uniform_real_distribution<double> dist_uniform(0.0, 1.0); // Uniform distribution for calculating acceptance

    for (int it = 0; it < num_iter; ++it)
    {
        history.push_back(theta); // Save the current state of theta

        for (int i = 0; i < len_data; ++i)
        {
            theta_minus_i.erase(theta_minus_i.begin() + i); // Remove the current theta for update calculation

            for (int r = 0; r < R; ++r)
            {
                int index = weight_dist(gen); // Select an index for theta update

                // Propose a new theta based on the selected index or from the prior
                theta_proposed = (index == len_data - 1) ? G0() : delta(gen) + theta_minus_i[index];

                double probability_of_accept = acceptance_probability(data[i], theta[i], theta_proposed, individual_sigma);

                if (dist_uniform(gen) < probability_of_accept)
                {
                    theta[i] = theta_proposed; // Accept the new theta
                    break;
                }
            }

            theta_minus_i.insert(theta_minus_i.begin() + i, theta[i]); // Reinsert the updated theta for the next iteration
        }

        if (it % 10 == 0) // Print diagnostic information every 10 iterations
        {
            std::cout << "\nIteration: " << it << '\n';
            for (int i = 0; i < 10; ++i)
            {
                std::cout << std::fixed << std::setprecision(2) << theta[i] << ' ';
            }
        }
    }

    return history; // Return the history for further analysis
}
