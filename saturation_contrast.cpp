#include "saturation_contrast.hpp"

void Saturation_contrast::source_image(const cv::Mat& src){
	source = src.clone();
	cv::cvtColor(src, YCrCb, cv::COLOR_BGR2YCrCb);
	cv::cvtColor(src, HSV, cv::COLOR_BGR2HSV);
}

void Saturation_contrast::threshold_map(const cv::Mat& map){
	threshold = map.clone();
	if (map.channels() != 1){
		cv::cvtColor(threshold, threshold, cv::COLOR_BGR2GRAY);
	}
}

cv::Mat Saturation_contrast::contrast_image() {
	cv::Mat result = YCrCb.clone();
	cv::Mat res_BGR;
	for (int i = 0; i < YCrCb.rows; i++) {
		for (int j = 0; j < YCrCb.cols; j++) {
			const double c = HSV.at<cv::Vec3b>(i, j)[1];
			double coef;
			if (c < 1) {
				coef = static_cast<double>(crit_coef) / 100;
			}
			else {
				coef = (static_cast<double>(contrast_coef)) / c;
				if (coef > static_cast<double>(crit_coef) / 100) {
					coef = static_cast<double>(crit_coef) / 100;
				}
			}
			const double l = -YCrCb.at<cv::Vec3b>(i, j)[0] + static_cast<double>(threshold.at<uchar>(i, j));
			const double r = coef * l;
			result.at<cv::Vec3b>(i, j)[0] = r;
		}
	}
	cv::cvtColor(result, res_BGR, cv::COLOR_YCrCb2BGR);
	return res_BGR;
}

std::map<std::string, std::pair<int, int&>>& Saturation_contrast::factor_map(){
	return fact_map;
}

void Saturation_contrast::make_HVS() {
	cv::cvtColor(source, HSV, cv::COLOR_BGR2HLS);
}

void Saturation_contrast::make_YCrCb() {
	cv::cvtColor(source, YCrCb, cv::COLOR_BGR2YCrCb);
}