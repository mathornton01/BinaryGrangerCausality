#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

#include <armadillo>

using namespace arma;

vec OLS(const mat& X, const vec& y);
vec WLS(const mat& X, const vec& y, const vec& w);
vec IRLS(const mat& X, const vec& y);
vec logistic_regression(const mat& X, const vec& y);

#endif //LOGISTIC_REGRESSION_H
