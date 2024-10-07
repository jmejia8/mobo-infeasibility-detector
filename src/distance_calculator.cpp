#include "distance_calculator.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <omp.h>

using namespace Eigen;

MatrixXd DistanceCalculator::load_data(const std::string& file_path) {
    std::ifstream file(file_path);
    std::string line;
    std::vector<std::vector<double>> data;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<double> row;
        std::string value;
        while (std::getline(ss, value, ',')) {
            row.push_back(std::stod(value));
        }
        data.push_back(row);
    }

    MatrixXd matrix(data.size(), data[0].size());
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            matrix(i, j) = data[i][j];
        }
    }

    return matrix;
}

MatrixXd DistanceCalculator::compute_distances(const MatrixXd& data) {
    int rows = data.rows();
    MatrixXd dist_matrix = MatrixXd::Zero(rows, rows);

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < rows; ++i) {
        for (int j = i; j < rows; ++j) {
            double dist = std::sqrt((data.row(i) - data.row(j)).squaredNorm());
            dist_matrix(i, j) = dist;
            dist_matrix(j, i) = dist;
        }
    }

    return dist_matrix;
}
