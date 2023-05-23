#include "granger_causality.h"
#include "logistic_regression.h"
#include "statistical_distributions.h"

// Helper function to create lagged matrix
mat create_lagged_matrix(const vec& v, int p) {
    int n = v.n_elem;
    mat X(n - p, p);
    for (int i = 0; i < p; ++i) {
        X.col(i) = v.subvec(p - i - 1, n - i - 2);
    }
    return X;
}

std::pair<double, double> granger_causality_test(const vec& x, const vec& y, int p) {
    mat X = join_horiz(create_lagged_matrix(y, p), create_lagged_matrix(x, p));
    vec Y = y.subvec(p, y.n_elem - 1);
    std::cout << "Here1" << std::endl;
    std::cout << X << std::endl;
    std::cout << Y << std::endl;
    vec unrestricted_model = logistic_regression(X, Y);
    std::cout << unrestricted_model << std::endl;
    std::cout << "Here 6.5" << std::endl;
     
    std::cout << Y % (X * unrestricted_model) - log(1+exp(X * unrestricted_model))
    double unrestricted_ll = sum(Y % (X * unrestricted_model) - log(1 + exp(X * unrestricted_model)));

    X.shed_cols(p, 2 * p - 1);
    std::cout << "Here7" << std::endl;
    std::cout << X << std::endl;
    std::cout << Y << std::endl;
    vec restricted_model = logistic_regression(X, Y);
    std::cout << "Here8" << std::endl;
    double restricted_ll = sum(Y % (X * restricted_model) - log(1 + exp(X * restricted_model)));

    double test_statistic = 2 * (unrestricted_ll - restricted_ll);
    double p_value = 1 - chi_squared_distribution_cdf(p, test_statistic);

    return {test_statistic, p_value};
}
