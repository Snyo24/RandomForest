/*
 * main.cpp
 *
 * @author: Snyo Kang
 * @date: 2016-01-14 ~ 
 * main
 */

#include "RandomForest.h"

#include <string.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace rf;

int input(const char* fileName, vector<Pair>& data) {
	ifstream ifs(fileName);

	if(!ifs.good()) {
		cerr << "Cannot open file \"" << fileName << "\"" << endl;
		return -1;
	}

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

	return 0;
}

int main(int argc, char** argv) {
	const char* fileName = "./train/training.data";
	if(argc > 1) {
		if(!strcmp(argv[1], "-r") && argc>2)
			fileName = argv[2];
		else {
			cerr << "<Usage>" << endl
			     << "./rf" << endl
			     << "./rf -r [filename]" << endl;
			return -1;
		}
	}

	vector<Pair> data;
	if(!input(fileName, data)) {
		Forest f(10, 5);

		f.train(data);

		// Test 1: Red and Blue
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

		// Test 2: Finger Tip
		// float x[] = {9.913528,  4.020704,  3.449625,  2.207823,  1.592659,  1.602922,  1.612980,  1.337000,  0.296113, -1.484193, -1.664025, -2.610483, -3.562976, -3.342586, -3.138854};
		// vector<float> v(x, x+15);
		// cout << f.test(v) << endl;
		// float x2[] = {7.579501, 6.289897, 7.253836, 4.165284, 3.288854, 5.550620, 6.149657, 3.988874, 3.766049, 5.380942, 5.381154, 3.771944, 2.834219, 2.216844, 4.107403};
		// vector<float> v2(x2, x+15);
		// cout << f.test(v2) << endl;
	}
	return 0;
}