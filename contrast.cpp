#include "contrast.hpp"
#include "image_utils.hpp"
#include <iostream>

void Contrast_maker::init(int, void* user){
	const auto self = static_cast<Contrast_maker*>(user);
	cv::resize(self->source, self->resized_src, cv::Size(), static_cast<double>(self->image_size) / 100 + 0.1, static_cast<double>(self->image_size) / 100 + 0.1);
	self->threshold->source_image(self->resized_src);
	self->contrast->source_image(self->resized_src);
	self->factors_threshold = self->threshold->factor_map();
	self->factors_contrast = self->contrast->factor_map();
	make(1, self);
}

void Contrast_maker::make(int, void* user){
	const auto self = static_cast<Contrast_maker*>(user);
	const cv::Mat th = self->threshold->threshold_map();
	self->contrast->threshold_map(th);
	self->res = self->contrast->contrast_image();
	cv::Mat doubleImage;
	image_modification::make_same_channels_amount(self->resized_src, self->res);
	cv::hconcat(self->resized_src, self->res, doubleImage);
	cv::imshow("Res", doubleImage);
}

void Contrast_maker::UI(){
	init(1, this);
	//cv::destroyWindow("Regulate");
	cv::namedWindow("Regulate", cv::WINDOW_NORMAL);
	cv::createTrackbar("ImageSize", "Regulate", &image_size, 100, init, this);
	for (auto it = factors_threshold.begin(); it != factors_threshold.end(); ++it){
		cv::createTrackbar(it->first, "Regulate", &(it->second.second), it->second.first, make, this);
	}
	for (auto it = factors_contrast.begin(); it != factors_contrast.end(); ++it){
		cv::createTrackbar(it->first, "Regulate", &(it->second.second), it->second.first, make, this);
	}
}

cv::Mat Contrast_maker::result_image(){
	const int image_size_back = image_size;
	image_size = 90;
	init(1, this);
	cv::Mat fullSizeResult = res.clone();
	image_size = image_size_back;
	init(1, this);
	return fullSizeResult;
}

void Contrast_maker::new_threshold_map(std::unique_ptr<Abstract_threshold_map>&& thrMap){
	threshold = std::move(thrMap);
	init(1, this);
}

void Contrast_maker::new_contrast_map(std::unique_ptr<Abstract_contrast>&& contrast_map){
	contrast = std::move(contrast_map);
	init(1, this);
}

void Contrast_maker::new_source(const cv::Mat& src){
	this->source = src.clone();
}

Contrast::Contrast() : contrast_maker(std::make_unique<Gauss_threshold_map>(), std::make_unique<Border_contrast>()) {}

void Contrast::main_loop(){
	if (!source_image()){
		return;
	}
	cv::namedWindow("Type", cv::WINDOW_NORMAL);
	bool repeat = true;
	while (repeat){
		std::cout << "Menu:" << std::endl << "SAVE IMAGE - 1" << std::endl << "NEW IMAGE - 2" << std::endl << "EXIT - 0" << std::endl;
		contrast_image();
		cv::createTrackbar("contrast_type", "Type", &contrast_type, types::count_contrast_types - 1, change_types, this);
		cv::createTrackbar("threshold_type", "Type", &threshold_type, types::count_threshold_types - 1, change_types, this);
		const int key = cv::waitKey();
		if (key == '1'){
			save_image();
		} else if (key == '2'){
			if (!source_image()){
				return;
			}
		} else if (key == '0'){
			repeat = false;
		}
	}
}

void Contrast::print_result() const{
	cv::imshow("Result", result);
}

bool Contrast::source_image(){
	bool repeat = true;
	bool error = false;
	while (repeat){
		if (error){
			std::cout << "CAN'T OPEN IMAGE, TRY AGAIN. ENTER 0 TO EXIT" << std::endl;
		}
		std::cout << "NAME OF THE IMAGE: ";
		std::string fileName;
		std::getline(std::cin, fileName);
		if (fileName == "0"){
			return false;
		}
		source = cv::imread(fileName);
		if (source.data != nullptr){
			repeat = false;
		} else{
			error = true;
		}
	}
	contrast_maker.new_source(source);
	return true;
}

void Contrast::contrast_image(){
	contrast_maker.UI();
}

void Contrast::save_image(){
	result = contrast_maker.result_image();
	std::string fileName;
	std::cout << "NAME OF THE NEW IMAGE: ";
	std::getline(std::cin, fileName);
	const bool check = cv::imwrite(fileName, result);
	if (check == false){
		std::cout << "SAVING THE IMAGE - FAILED" << std::endl;
	} else{
		std::cout << "SAVING THE IMAGE - SUCCESS" << std::endl;
	}
}

void Contrast::change_types(int, void* user){
	const auto self = static_cast<Contrast*>(user);
	std::unique_ptr<Abstract_contrast> ctr;
	std::unique_ptr<Abstract_threshold_map> thr;
	switch (self->contrast_type){
	case types::Border:
		self->contrast_maker.new_contrast_map(std::make_unique<Border_contrast>());
		break;
	case types::Alpha:
		self->contrast_maker.new_contrast_map(std::make_unique<Alpha_contrast>());
		break;
	case types::Saturation:
		self->contrast_maker.new_contrast_map(std::make_unique<Saturation_contrast>());
		break;
	default: 
		break;
	}

	switch (self->threshold_type){
	case types::Gaussian:
		self->contrast_maker.new_threshold_map(std::make_unique<Gauss_threshold_map>());
		break;
	case types::Pyramid:
		self->contrast_maker.new_threshold_map(std::make_unique<Pyramid_threshold_map>());
		break;
	default:
		break;
	}

	(*self).contrast_image();
}