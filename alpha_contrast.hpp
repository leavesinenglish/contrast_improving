#pragma once
#include "abstr_contrast.hpp"

class Alpha_contrast final : public Abstract_contrast{
public:
	cv::Mat contrast_image() override;
	std::map<std::string, std::pair<int, int&>>& factor_map() override;
private:
	int contrast_coef = 2;
	int src_coef = 50;
	int threshold_coef = 100;
	std::map<std::string, std::pair<int, int&>> fact_map = {{"contrast_coef",{20,contrast_coef}},{"src_coef",{100,src_coef}},{"threshold_coef",{100,threshold_coef}}};
};