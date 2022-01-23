#include "gauss_threshold.hpp"

cv::Mat Gauss_threshold_map::threshold_map(){
	cv::Mat threshold_map;
	cv::GaussianBlur(source, threshold_map, cv::Size(gauss_coef * 2 + 1, gauss_coef * 2 + 1), 0, 0);
	return threshold_map;
}

std::map<std::string, std::pair<int, int&>>& Gauss_threshold_map::factor_map(){
	return fact_map;
}