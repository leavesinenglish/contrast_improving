#pragma once
#include "abstr_threshold.hpp"

class Gauss_threshold_map final : public Abstract_threshold_map{
public:
	cv::Mat threshold_map() override;
	std::map<std::string, std::pair<int, int&>>& factor_map() override;
private:
	int gauss_coef = 8;
	std::map<std::string, std::pair<int, int&>> fact_map = {{"gauss_coef",{120,gauss_coef}}};
};