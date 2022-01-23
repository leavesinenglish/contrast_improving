#pragma once

namespace compress_image{

	static uchar average(std::initializer_list<uchar> list){
		int sum = 0;
		for (auto &elem : list){
			sum = sum + elem;
		}
		return sum / 4;
	}

	static cv::Mat compression(const cv::Mat& mat, uchar func(std::initializer_list<uchar>)){
		const int new_rows = mat.rows / 2;
		const int new_cols = mat.cols / 2;
		if (new_rows < 1 && new_cols < 1){
			return mat;
		}
		cv::Mat new_mat = cv::Mat(new_rows, new_cols, mat.type());
		for (int y = 0; y < new_mat.rows; y++){
			for (int x = 0; x < new_mat.cols; x++){
				new_mat.at<uchar>(y, x) = func({mat.at<uchar>(y * 2, x * 2),
														mat.at<uchar>(y * 2 + 1, x * 2 + 1),
														mat.at<uchar>(y * 2 + 1, x * 2),
														mat.at<uchar>(y * 2, x * 2 + 1) });
			}
		}
		return new_mat;
	}

	static cv::Mat max_mat(const cv::Mat& mat){
		return compression(mat, std::max);
	}

	static cv::Mat mid_mat(const cv::Mat& mat){
		return compression(mat, average);
	}

	static cv::Mat min_mat(const cv::Mat& mat){
		return compression(mat, std::min);
	}
}

namespace convert_color{

	static cv::Mat YfromYCrCb(const cv::Mat& src){
		cv::Mat ch[3];
		cv::split(src, ch);
		return ch[0].clone();
	}

	static cv::Mat YfromBGR(const cv::Mat& src){
		cv::Mat yCrCb;
		cv::cvtColor(src, yCrCb, cv::COLOR_BGR2YCrCb);
		return YfromYCrCb(yCrCb);
	}
}

namespace image_modification{

	static void make_same_channels_amount(cv::Mat& first, cv::Mat& sec){
		if (first.channels() != sec.channels()){
			if (first.channels() != 1){
				cv::cvtColor(first, first, cv::COLOR_BGR2GRAY);
			}
			if (sec.channels() != 1){
				cv::cvtColor(sec, sec, cv::COLOR_BGR2GRAY);
			}
		}
	}
}