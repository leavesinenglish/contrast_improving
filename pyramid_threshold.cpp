#include "pyramid_threshold.hpp"
#include "image_utils.hpp"

cv::Mat Comp_mat::get_comp_mat(){
	return mat;
}

cv::Mat Comp_mat::get_uncomp_mat(int interpolation) const{
	cv::Mat uncmat;
	cv::resize(mat, uncmat, source_size, 0, 0, interpolation);
	return uncmat;
}

int Comp_mat::get_lvl() const{
	return comp_lvl;
}

void Pyramid_threshold_map::source_image(const cv::Mat& src){
	source = src.clone();
	if (src.channels() != 1){
		source = convert_color::YfromBGR(src);
	}
	minimum_pyramid();
	average_pyramid();
	maximum_pyramid();
}

cv::Mat Pyramid_threshold_map::threshold_map(){
	cv::Mat threshold_map = average.back().get_comp_mat().clone();
	const int lvl = average.back().get_lvl() - 1;
	for (int i = lvl; i >= pyr_lvl; i--){
		cv::Mat min = minimum[i].get_comp_mat();
		cv::Mat max = maximum[i].get_comp_mat();
		cv::Mat aver = average[i].get_comp_mat();
		cv::GaussianBlur(threshold_map, threshold_map, cv::Size(gauss_coef * 2 + 1, gauss_coef * 2 + 1), 0, 0);
		cv::resize(threshold_map, threshold_map, min.size(), 0, 0, 1);
		for (int y = 0; y < threshold_map.rows; y++){
			for (int x = 0; x < threshold_map.cols; x++){
				if ((max.at<uchar>(y, x) - min.at<uchar>(y, x)) >= noise_lvl){
					threshold_map.at<uchar>(y, x) = aver.at<uchar>(y, x) + 7;
				}
			}
		}
	}
	cv::resize(threshold_map, threshold_map, source.size(), 0, 0, 1);
	return threshold_map;
}

std::map<std::string, std::pair<int, int&>>& Pyramid_threshold_map::factor_map(){
	return map;
}

void Pyramid_threshold_map::make_pyramid(std::vector<Comp_mat>& vec, cv::Mat func(const cv::Mat& mat)) const{
	cv::Mat nMat = source.clone();
	int compLvl = 1;
	while (nMat.rows > 1 && nMat.cols > 1){
		cv::Size srcSize = nMat.size();
		nMat = func(nMat);
		vec.emplace_back(nMat, compLvl, srcSize);
		compLvl++;
	}
}

void Pyramid_threshold_map::minimum_pyramid(){
	make_pyramid(minimum, compress_image::min_mat);
}

void Pyramid_threshold_map::average_pyramid(){
	make_pyramid(average, compress_image::mid_mat);
}

void Pyramid_threshold_map::maximum_pyramid(){
	make_pyramid(maximum, compress_image::max_mat);
}