#pragma once
#include "abstr_threshold.hpp"

class Comp_mat{
private:
	cv::Size source_size;
	int comp_lvl = 0;
	cv::Mat mat;
public:
	Comp_mat() = delete;
	Comp_mat(const cv::Mat& mat, int lvl, cv::Size src_size) :mat(mat), comp_lvl(lvl), source_size(src_size) {}
	cv::Mat get_uncomp_mat(int interpolation = 1) const;
	cv::Mat get_comp_mat();
	int get_lvl() const;
};

class Pyramid_threshold_map final : public Abstract_threshold_map{
public:
	void source_image(const cv::Mat& src) override;
	cv::Mat threshold_map() override;
	std::map<std::string, std::pair<int, int&>>& factor_map()override;
private:
	std::map<std::string, std::pair<int, int&>> map = {{"pyr_lvl",{5,pyr_lvl}},{"noise_lvl",{200,noise_lvl}},{"gauss_coef",{40,gauss_coef}}};
	int pyr_lvl = 1;
	int noise_lvl = 20;
	int gauss_coef = 0;
	void make_pyramid(std::vector<Comp_mat>& vec, cv::Mat func(const cv::Mat& mat)) const;
	void minimum_pyramid();
	void average_pyramid();
	void maximum_pyramid();
	std::vector<Comp_mat> minimum;
	std::vector<Comp_mat> average;
	std::vector<Comp_mat> maximum;
};