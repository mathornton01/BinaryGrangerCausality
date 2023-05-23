#include <iostream>
#include "granger_causality_from_csv.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: ./program <csv_file_path> <subsequence_size> <lag>\n";
        return 1;
    }

    std::string file_path = argv[1];
    int subsequence_size = std::stoi(argv[2]);
    int p = std::stoi(argv[3]);

    mat p_values = granger_tests_from_csv(file_path, subsequence_size, p);
    p_values.print("P-values:");

    return 0;
}
