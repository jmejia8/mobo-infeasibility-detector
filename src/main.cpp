#include "distance_calculator.hpp"
#include <iostream>
#include <Eigen/Dense>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::string file_path = argv[1];

    // Check if the file exists
    if (!fs::exists(file_path)) {
        std::cerr << "Error: File " << file_path << " does not exist." << std::endl;
        return 1;
    }

    DistanceCalculator calculator;

    // Load data from the provided file path
    Eigen::MatrixXd data = calculator.load_data(file_path);

    std::cout << "Data loaded from " << file_path << ". Computing distance matrix..." << std::endl;

    // Compute the distance matrix
    Eigen::MatrixXd distance_matrix = calculator.compute_distances(data);

    std::cout << "Distance matrix computed!" << std::endl;
    // std::cout <<  distance_matrix << std::endl;

    return 0;
}
