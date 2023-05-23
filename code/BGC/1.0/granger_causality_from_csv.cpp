#include <fstream>
#include <sstream>
#include "granger_causality_from_csv.h"
#include "granger_causality.h"

// Helper function to split string into a vector of integers
vec string_to_vec(const std::string& binary_string) {
    vec v(binary_string.size());
    for (size_t i = 0; i < binary_string.size(); ++i) {
        v(i) = binary_string[i] - '0';
    }
    return v;
}

// Function to split a vector into subsequences
std::vector<vec> split_into_subsequences(const vec& v, int subsequence_size) {
    int n = v.n_elem / subsequence_size;
    std::vector<vec> subsequences(n);
    for (int i = 0; i < n; ++i) {
        subsequences[i] = v.subvec(i * subsequence_size, (i + 1) * subsequence_size - 1);
    }
    return subsequences;
}

// Function to perform Granger causality tests
mat granger_tests_from_csv(const std::string& file_path, int subsequence_size, int p) {
    // Read binary string from CSV file
    std::ifstream file(file_path);
    std::string line;
    std::getline(file, line);
    vec binary_sequence = string_to_vec(line);

    // Split binary sequence into subsequences
    std::vector<vec> subsequences = split_into_subsequences(binary_sequence, subsequence_size);
    std::cout << "Here1" << std::endl;
    // Perform Granger causality tests
    int n = subsequences.size();
    std::cout << n <<std::endl;
    mat p_values(n, n, fill::zeros);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::cout << subsequences[i] << std::endl;
            std::cout << subsequences[j] << std::endl;
            p_values(i, j) = granger_causality_test(subsequences[i], subsequences[j], p).second;
            p_values(j, i) = p_values(i,j);
        }
    }
    
    return p_values;
}
