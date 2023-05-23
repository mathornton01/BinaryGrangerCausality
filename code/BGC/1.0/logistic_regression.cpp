#include "logistic_regression.h"
#include <armadillo>
#include "statistical_distributions.h"

using namespace arma;

vec OLS(const mat& X, const vec& y) {
    return solve(X, y);
}

vec WLS(const mat& X, const vec& y, const vec& w) {
    mat X_tilde = diagmat(sqrt(w)) * X;
    vec y_tilde = sqrt(w) % y;
    return OLS(X_tilde, y_tilde);
}

vec IRLS(const mat& X, const vec& y) {
    std::cout << "Here" << std::endl;
    int n = X.n_rows;
    vec beta = zeros<vec>(X.n_cols);
    vec beta_prev;
    do {
        beta_prev = beta;
        vec p = 1.0 / (1.0 + exp(-X * beta));
        vec w = p % (1 - p);
        beta = WLS(X, y, w);
    } while (norm(beta - beta_prev, 2) > 1e-6);
    return beta;
}

vec logistic_regression(const mat& X, const vec& y) {
        std::cout << "Here2" << std::endl;
    vec beta = IRLS(X, y);
        std::cout << "Here3" << std::endl;
    mat V = pinv(X.t() * diagmat(1.0 / (1.0 + exp(-X * beta)) % (1 - 1.0 / (1.0 + exp(-X * beta)))) * X);
    std::cout << "Here4" << std::endl;
    vec se = sqrt(V.diag());
    vec z = beta / se;
    vec abs_z = abs(z);
    vec p(abs_z.n_elem);
    std::cout << "Here5" << std::endl;
    for (size_t i = 0; i < abs_z.n_elem; ++i) {
        p(i) = 2 * (1 - normal_distribution_cdf(abs_z(i), 0, 1));
    }
    std::cout << "Here6" << std::endl;
    return join_cols(join_cols(join_cols(beta, se), z), p);
}

