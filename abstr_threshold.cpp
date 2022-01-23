#include "abstr_threshold.hpp"

void Abstract_threshold_map::source_image(const cv::Mat& src){
	source = src.clone();
}