#include <iostream>
#include <fstream>
#include <armadillo>
#include <random>


using namespace std;
using namespace arma;
void GenerateBinaryDataAndResponses(const vec& coeffs, size_t numSamples, const string& dataFile, const string& responsesFile) {
  size_t numFeatures = coeffs.n_elem - 1;
  mat data = randu<mat>(numSamples, numFeatures); // Generate uniform random data in the range [0, 1]

  // Convert random data to binary data with probability 0.5
  data.transform([](double val) { return (val >= 0.5) ? 1.0 : 0.0; });

  vec intercepts = ones<vec>(numSamples);
  mat X = join_horiz(intercepts, data); // Add the intercept column

  vec linearCombination = X * coeffs;
  vec probabilities = 1 / (1 + exp(-linearCombination)); // Apply logistic function

  // Generate binary responses based on probabilities
  vec responses = zeros<vec>(numSamples);
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  for (size_t i = 0; i < numSamples; ++i) {
    if (distribution(generator) < probabilities(i)) {
      responses(i) = 1;
    }
  }

  // Save data and responses to CSV files
  data.save(dataFile, csv_ascii);
  responses.save(responsesFile, csv_ascii);
}

int main() {
  // Set the desired coefficients (including the intercept), number of samples, and output file names
  vec coeffs = {1.5, -2.0, 3.0, 3.2, 3, -3, -2, 3, 0, 0, 0};
  size_t numSamples = 10000;
  string dataFile = "binary_data.csv";
  string responsesFile = "binary_responses.csv";

  // Generate and save binary data and responses
  GenerateBinaryDataAndResponses(coeffs, numSamples, dataFile, responsesFile);

  return 0;
}