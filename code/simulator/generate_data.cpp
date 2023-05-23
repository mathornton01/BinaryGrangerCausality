#include <iostream>
#include <fstream>
#include <armadillo>
#include <random>


using namespace std;
using namespace arma;
void GenerateDataAndResponses(const vec& coeffs, size_t numSamples, const string& dataFile, const string& responsesFile) {
  size_t numFeatures = coeffs.n_elem - 1;
  mat data = randn<mat>(numSamples, numFeatures); // Generate random data
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

int main(int argc, char** argv) {
  if (argc != 5) {
    cout << "Usage: " << argv[0] << " <numSamples> <coefficients (comma-separated)> <data.csv> <responses.csv>" << endl;
    return 1;
  }

  size_t numSamples = stoi(argv[1]);
  string coeffsString = argv[2];
  string dataFile = argv[3];
  string responsesFile = argv[4];

  // Parse coefficients
  vec coeffs;
  stringstream ss(coeffsString);
  double value;
  while (ss >> value) {
    coeffs.insert_rows(coeffs.n_elem, 1);
    coeffs(coeffs.n_elem - 1) = value;
    if (ss.peek() == ',') {
      ss.ignore();
    }
  }

  // Generate and save data and responses
  GenerateDataAndResponses(coeffs, numSamples, dataFile, responsesFile);

  return 0;
}
