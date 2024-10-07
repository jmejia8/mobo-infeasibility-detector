#ifndef DISTANCE_CALCULATOR_HPP
#define DISTANCE_CALCULATOR_HPP

#include <Eigen/Dense>
#include <string>

class DistanceCalculator {
public:
    Eigen::MatrixXd load_data(const std::string& file_path);
    Eigen::MatrixXd compute_distances(const Eigen::MatrixXd& data);
};

#endif // DISTANCE_CALCULATOR_HPP
