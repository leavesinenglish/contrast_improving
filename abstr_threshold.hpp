#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <string>
#include <map>

class Abstract_threshold_map{
public:
	virtual ~Abstract_threshold_map() = default;
	virtual void source_image(const cv::Mat& src);
	virtual cv::Mat threshold_map() = 0;
	virtual std::map<std::string, std::pair<int, int&>>& factor_map() = 0;
protected:
	cv::Mat source;
};