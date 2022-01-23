#include "alpha_contrast.hpp"
#include "image_utils.hpp"

cv::Mat Alpha_contrast::contrast_image(){
	image_modification::make_same_channels_amount(source,threshold);
	cv::Mat contrast_mat;
	cv::addWeighted(source,-static_cast<double>(src_coef)/100,threshold,static_cast<double>(threshold_coef)/100,0,contrast_mat);
	contrast_mat.convertTo(contrast_mat,-1,1,0);////// maybe unused
	contrast_mat = source - contrast_mat;
	contrast_mat.convertTo(contrast_mat,-1,contrast_coef,0);
	return contrast_mat;
}

std::map<std::string, std::pair<int, int&>>& Alpha_contrast::factor_map(){
	return fact_map;
}