#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <string>
#include <map>
#include <memory>

#include "abstr_threshold.hpp"
#include "abstr_contrast.hpp"

#include "alpha_contrast.hpp"
#include "border_contrast.hpp"
#include "saturation_contrast.hpp"

#include "gauss_threshold.hpp"
#include "pyramid_threshold.hpp"

namespace types{

	static int count_threshold_types = 2;
	enum threshold_types{
		Gaussian,
		Pyramid
	};

	static int count_contrast_types = 3;
	enum contrast_types{
		Border,
		Alpha,
		Saturation
	};

}

class Contrast_maker{
public:
	Contrast_maker(std::unique_ptr<Abstract_threshold_map>&& threshold_map, std::unique_ptr<Abstract_contrast>&& contrast) :
	threshold(std::move(threshold_map)), contrast(std::move(contrast)) {}
	static void init(int, void* user);
	static void make(int, void* user);
	void new_source(const cv::Mat& src);
	void new_threshold_map(std::unique_ptr<Abstract_threshold_map>&& map);
	void new_contrast_map(std::unique_ptr<Abstract_contrast>&& map);
	cv::Mat result_image();
	void UI();
private:
	cv::Mat source;
	cv::Mat resized_src;
	cv::Mat res;
	int image_size = 30;
	std::unique_ptr<Abstract_threshold_map> threshold;
	std::unique_ptr<Abstract_contrast> contrast;
	std::map<std::string, std::pair<int, int&>> factors_threshold;
	std::map<std::string, std::pair<int, int&>> factors_contrast;
};

class Contrast{
public:
	Contrast();
	void main_loop();
private:
	cv::Mat source;
	cv::Mat result;
	int contrast_type = types::Border;
	int threshold_type = types::Gaussian;
	Contrast_maker contrast_maker;
	void print_result() const;
	bool source_image();
	void contrast_image();
	void save_image();
	static void change_types(int, void* user);
};