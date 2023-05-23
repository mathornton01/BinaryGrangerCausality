#ifndef GRANGER_CAUSALITY_H
#define GRANGER_CAUSALITY_H

#include <armadillo>

using namespace arma;

std::pair<double, double> granger_causality_test(const vec& x, const vec& y, int p);

#endif //GRANGER_CAUSALITY_H
