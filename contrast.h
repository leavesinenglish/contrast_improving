#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <string>
#include <map>

class AbstractContrast{
public:
	virtual void SourceImage(const cv::Mat& src);
	virtual void ThresholdMap(const cv::Mat& thresholdMap);
	virtual cv::Mat ContrastImage() = 0;
	virtual std::map<std::string, std::pair<int, int&>>& factorMap() = 0;

protected:
	cv::Mat src;
	cv::Mat thresholdMap;
};