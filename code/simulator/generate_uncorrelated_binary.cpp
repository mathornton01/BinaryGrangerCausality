#include <iostream>
#include <fstream>
#include <random>

int main(int argc, char* argv[]) {
    // Check if command line argument is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " number_of_elements" << std::endl;
        return 1;
    }

    int num_elements = std::stoi(argv[1]); // convert command line argument to integer

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 1); // define the range

    std::ofstream file;
    file.open("random_binary.csv");

    for(int n=0; n<num_elements; ++n) {
        file << distr(eng) << std::endl;
    }

    file.close();
    return 0;
}
