#include "border_contrast.hpp"
#include "image_utils.hpp"

cv::Mat Border_contrast::contrast_image(){
	image_modification::make_same_channels_amount(source,threshold);
	cv::Mat contrast_mat;
	cv::addWeighted(source,-static_cast<double>(src_coef)/100,threshold,static_cast<double>(threshold_coef)/100,0,contrast_mat);
	contrast_mat.convertTo(contrast_mat,-1,static_cast<double>(contrast_coef),0);
	cv::bitwise_not(contrast_mat,contrast_mat);
	return contrast_mat;
}

std::map<std::string, std::pair<int, int&>>& Border_contrast::factor_map(){
	return fact_map;
}