// Where the main function is

#include <iostream>
#include <random>
#include "export.h"
#include "Algorithm6.h"
#include "generate_samples.h"
#include "import.h"
#include <chrono> // For timing


int main() {

    ////////////////////////////////////////////////////////////////////////////
    // This block will generate a gaussian mixture dataset with different means

    Sample_generator sampler{};
    std::vector<double> means{-6.0, 0, 6, 12.0}; // Setting the cluster means.
    std::vector<double> probs{0.1, 0.25, 0.35, 0.3}; // Probability of drawing from each cluster.
    int n = 3000; // setting the number of data points to draw.
    double stddev = 0.1; // This will be the standard deviation of all clusters.
    std::vector<double> data = sampler.gaussian_mixture(means, probs, n, stddev);
    sampler.print_histogram(data); // Print a histogram for the data simulated


    /////////////////////////////////////////////////////////////////////////
    // Uncomment this block and comment out the block above if you want to import data from outside.

    // Import csv data
    /*
    Reader reader{};
    std::vector<double> data = reader.read_csv_as_vector("data.csv");
    int n = static_cast<int>(data.size()); // setting the value of n
    double stddev = 0.1; // Change to what ever you want
    */
    //////////////////////////////////////////////
    // Now run the algorithm. Change things here if you want to.
    constexpr double alpha = 1; // concentration parameter, higher <=> less concentrated
    const int len_data = n;
    constexpr int num_iter = 500; // Number of iterations to run.
    constexpr int R = 20; // Number of updated for each data point within each iteration

    constexpr double mu = 0; // mean for the prior
    constexpr double sigma = 10; // standard deviation for the prior
    constexpr double individual_sigma = 0.5; // standard deviation for each datapoint. Changing this changes the behaviour

    Algorithm6 algo6
            (
                    data, // vector holding the data to be clustered
                    alpha, // concentration parameter.
                    len_data, // length of data
                    num_iter, // number of iterations to run
                    R, // See the paper. Is the number of updates we will try for each i in each iteration.

                    mu, // mean of prior
                    sigma, // standard deviation of the prior
                    individual_sigma
            );

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    auto history = algo6.run();

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    std::cout << "\n\n\nExecution time: " << duration.count() << " seconds" << '\n'
        << "Iterations run: " << num_iter <<'\n'
        << "Number of data points: " << n << '\n';

    exportToCSV(history, "history.csv");





    return 0;
}
