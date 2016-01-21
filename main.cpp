/*
 * main.cpp
 *
 * @author: Snyo Kang
 * @date: 2016-01-14 ~ 
 * main
 */

#include "RandomForest.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace rf;

using namespace cv;

void input(vector<Pair>& data) {
	ifstream ifs("./train/training.data");

	int c = 1;
	while(!ifs.eof()) {
		string STRING;
		getline(ifs, STRING);
		stringstream ss(STRING);

		string token;
		bool y = false;
		Pair x;
		while(getline(ss, token, ',')) {
			if(!y)
				x.second = atoi(token.c_str());
			else
				x.first.push_back(atof(token.c_str()));
			y = true;
		}
		data.push_back(x);
	}
}

int main(int argc, char** argv) {
	vector<Pair> data;
	input(data);

	Forest f(10, 5);

	f.train(data);

	Mat img;
	img = imread("./train/test_image.png");
	Mat res = img.clone();
	for (int i=0; i<img.size().height; ++i) {
		for (int j=0; j<img.size().width; ++j) {
			Vec3f pix(img.at<Vec3b>(i, j));
			vector<float> t;
			t.push_back(pix[0]);
			t.push_back(pix[0]);
			t.push_back(pix[0]);
			t.push_back(pix[0]);
			t.push_back(pix[0]);
			t.push_back(pix[1]);
			t.push_back(pix[1]);
			t.push_back(pix[1]);
			t.push_back(pix[1]);
			t.push_back(pix[1]);
			t.push_back(pix[2]);
			t.push_back(pix[2]);
			t.push_back(pix[2]);
			t.push_back(pix[2]);
			t.push_back(pix[2]);
			float cc = f.test(t);
			res.at<Vec3b>(i,j)[0] = 255*cc;
			res.at<Vec3b>(i,j)[1] = 255*cc;
			res.at<Vec3b>(i,j)[2] = 255*cc;
		}
	}
	imshow("f", img);
	imshow("fff", res);
	waitKey(0);
	return 0;
}