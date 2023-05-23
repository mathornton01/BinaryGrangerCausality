#ifndef GRANGER_CAUSALITY_FROM_CSV_H
#define GRANGER_CAUSALITY_FROM_CSV_H

#include <string>
#include <armadillo>

using namespace arma;

mat granger_tests_from_csv(const std::string& file_path, int subsequence_size, int p);

#endif //GRANGER_CAUSALITY_FROM_CSV_H
