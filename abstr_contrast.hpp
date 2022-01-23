#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <string>
#include <map>

class Abstract_contrast{
public:
	virtual ~Abstract_contrast() = default;
	virtual void source_image(const cv::Mat& src);
	virtual void threshold_map(const cv::Mat& map);
	virtual cv::Mat contrast_image() = 0;
	virtual std::map<std::string, std::pair<int, int&>>& factor_map() = 0;

protected:
	cv::Mat source;
	cv::Mat threshold;
}; 