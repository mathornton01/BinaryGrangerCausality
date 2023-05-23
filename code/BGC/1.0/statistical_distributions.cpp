#include "statistical_distributions.h"
#include <cmath>

// Constants for normal distribution
const double SQRT2PI = std::sqrt(2.0 * M_PI);

// Error function approximation
double erf_approx(double x) {
    const double a1 =  0.254829592;
    const double a2 = -0.284496736;
    const double a3 =  1.421413741;
    const double a4 = -1.453152027;
    const double a5 =  1.061405429;
    const double p  =  0.3275911;

    int sign = (x < 0) ? -1 : 1;
    x = std::fabs(x);

    double t = 1.0 / (1.0 + p * x);
    double y = ((((a5 * t + a4) * t + a3) * t + a2) * t + a1) * t;

    return sign * (1 - y * std::exp(-x * x));
}

double normal_distribution_cdf(double x, double mu, double sigma) {
    return 0.5 * (1 + erf_approx((x - mu) / (sigma * std::sqrt(2.0))));
}

// Constants for chi squared distribution
const int ITERATIONS = 10000;

// Gamma function approximation
double gamma_function(double x) {
    if (x <= 0) return 0;
    if (x < 12.0) {
        double y = x;
        int i, n = 0;
        bool arg_is_integer = x == std::floor(x);
        if (arg_is_integer) {
            --y;
            n = static_cast<int>(x) - 1;
            x = 1.0;
        }
        for (i = 0; i < n; ++i) {
            x *= y--;
        }
        return x;
    }
    double tmp = x + 5.2421875;
    tmp = (x + 0.5) * std::log(tmp) - tmp;
    return std::sqrt(2.0 * M_PI) * std::pow(x, x - 0.5) * std::exp(-x) * (1.0 + 1.0 / (12.0 * x));
}

double chi_squared_distribution_cdf(int k, double x) {
    double sum = 0.0;
    for (int i = 0; i < ITERATIONS; ++i) {
        double xi = i / static_cast<double>(ITERATIONS);
        double dxi = 1.0 / static_cast<double>(ITERATIONS);
        sum += std::pow(xi, k / 2.0 - 1) * std::exp(-xi / 2.0) * dxi;
    }
    return sum / gamma_function(k / 2.0);
}
