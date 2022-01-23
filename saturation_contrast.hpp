#pragma once

#include "abstr_contrast.hpp"

class Saturation_contrast final : public Abstract_contrast{
public:
	void source_image(const cv::Mat& src) override;
	void threshold_map(const cv::Mat& map) override;
	cv::Mat contrast_image() override;
	std::map<std::string, std::pair<int, int&>>& factor_map() override;
private:
	cv::Mat HSV;
	cv::Mat YCrCb;
	void make_HVS();
	void make_YCrCb();
	int contrast_coef = 0;
	int crit_coef = 200;
	std::map<std::string, std::pair<int, int&>> fact_map = { {"crit_coef",{500,crit_coef}},{"contrast_coef",{1000,contrast_coef}} };
};