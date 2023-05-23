#include <iostream>
#include <armadillo>
#include <random>

using namespace std;
using namespace arma;

vec GenerateAutocorrelatedBinarySequence(const vec& coeffs, size_t numSamples) {
  size_t lag = coeffs.n_elem - 1;
  vec binarySeries(numSamples, fill::zeros);

  // Generate initial random binary values
  for (size_t i = 0; i < lag; ++i) {
    binarySeries(i) = (rand() % 2 == 1) ? 1.0 : 0.0;
  }

  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  for (size_t i = lag; i < numSamples; ++i) {
    vec laggedValues = binarySeries.subvec(i - lag, i - 1);
    double linearCombination = dot(coeffs.subvec(1, lag), laggedValues) + coeffs(0);
    double probability = 1 / (1 + exp(-linearCombination));

    if (distribution(generator) < probability) {
      binarySeries(i) = 1;
    }
  }

  return binarySeries;
}

void WriteBinarySequenceToFile(const vec& binarySeries, const string& fileName) {
  binarySeries.save(fileName, csv_ascii);
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    cerr << "Usage: " << argv[0] << " <coefficients> <number of samples> <output file>" << endl;
    cerr << "Example: " << argv[0] << " \"1.5 -2.0 3.0\" 1000 autocorrelated_binary_series.csv" << endl;
    return 1;
  }

  // Parse coefficients from the command line
  stringstream ss(argv[1]);
  vector<double> tempCoeffs;
  double temp;
  while (ss >> temp) {
    tempCoeffs.push_back(temp);
    if (ss.peek() == ' ') {
      ss.ignore();
    }
  }
  vec coeffs(tempCoeffs);

  // Parse the number of samples and output file name from the command line
  size_t numSamples = stoi(argv[2]);
  string fileName = argv[3];

  // Generate the autocorrelated binary sequence
  vec binarySeries = GenerateAutocorrelatedBinarySequence(coeffs, numSamples);

  // Write the binary sequence to a CSV file
  WriteBinarySequenceToFile(binarySeries, fileName);

  return 0;
}
