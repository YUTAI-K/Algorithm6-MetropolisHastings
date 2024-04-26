### This program is implementing a Metropolis-Hastings algorithm described by RM Neal in his paper Markov chain sampling methods for Dirichlet process mixture models(2000)

For a detailed description please consult algorithm 6 in the paper mentioned.

For the model setup in my code plese check the model.pdf file.

Useage: Compile and run my code, it will automatically samples a gaussian mixture model with
cluster means -6.0, 0, 6, 12.0, standard deviation all set to 0.1, and probability of sample 
from each cluster:0.1, 0.25, 0.35, 0.3. Then, it will run a metropolis hasting algorithm to 
estimate the distribution of the model(the algorithm will run 500 iterations by default), and export 
the result to a file called "history.csv". In the "cmake-build-debug" folder there is a python
notebook named "plot", which can be used to generate illustrations. You can also check the plots
directly from the folder "SamplePlots". The parameters of the data generating process and the algorithm 
can be changed, please check the code.
