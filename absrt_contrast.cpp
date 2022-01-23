#include "abstr_contrast.hpp"

void Abstract_contrast::source_image(const cv::Mat& src){
	source = src.clone();
}

void Abstract_contrast::threshold_map(const cv::Mat& map){
	threshold = map.clone();
}