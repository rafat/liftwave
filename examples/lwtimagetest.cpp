//============================================================================
// Name        : imagedemo_sym.cpp
// Author      : Rafat Hussain
// Version     :
// Copyright   :
// Description : DWT of arbitrary size image using symmetric extension
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include "lwave.h"
#include "..\..\..\..\OpenCV2.0\include\opencv\cv.h"
#include "..\..\..\..\OpenCV2.0\include\opencv\highgui.h"
#include "..\..\..\..\OpenCV2.0\include\opencv\cxcore.h"

using namespace std;
using namespace cv;

void* maxval(vector<vector<double> > &arr, double &max){
	max = 0;
	for (unsigned int i =0; i < arr.size(); i++) {
		for (unsigned int j =0; j < arr[0].size(); j++) {
			if (max <= arr[i][j]){
				max = arr[i][j];
			}
		}
	}
	return 0;
}

void* maxval1(vector<double> &arr, double &max){
	max = 0;
	for (unsigned int i =0; i < arr.size(); i++) {
		if (max <= arr[i]){
			max = arr[i];
		}

	}
	return 0;
}


int main() {
	IplImage* img = cvLoadImage("lena512.bmp");
	if (!img){
		cout << " Can't read Image. Try Different Format." << endl;
		exit(1);
	}
	int height, width;
	height = img->height;
	width = img->width;
	int nc = img->nChannels;
	//   uchar* ptr2 =(uchar*) img->imageData;
	int pix_depth = img->depth;
	CvSize size;
	size.width =width;
	size.height=height;
	cout << "depth" << pix_depth <<  "Channels" << nc << endl;


	cvNamedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Original Image", img);
	cvWaitKey();
	cvDestroyWindow("Original Image");
	cvSaveImage("orig.bmp",img);


	int rows =(int) height;
	int cols =(int) width;
	Mat matimg(img);

	vector<double> vec1,copy;


	int k =1;
	for (int i=0; i < rows; i++) {
		for (int j =0; j < cols; j++){
			unsigned char temp;
			temp = ((uchar*) matimg.data + i * matimg.step)[j  * matimg.elemSize() + k ];
			vec1.push_back((double) temp);
		}

	}

	copy=vec1;

    int J=4;
	string nm = "db3";
	liftscheme lift(nm);
	lwt2<double> wt(vec1,rows,cols,lift,J);

	ilwt2<double> iwt(wt,lift);
	vector<double> oup;
	iwt.getSignal(oup);
	vector<int> oup_dim;
	iwt.getDim(oup_dim);

	vector<double> ll,lh,hl,hh;
	wt.getCoef(ll,lh,hl,hh);
	vector<int> vec;
	wt.getDim(vec);
	for (int i=0; i < (int)vec.size(); i++) {
        cout << vec[i] << endl;
	}
//	filtcoef(nm,l1,h1,l2,h2);
	cout << vec1.size() << endl;

	IplImage *cvImg; // image used for output
	CvSize imgSize; // size of output image

	imgSize.width = oup_dim[1];
	imgSize.height = oup_dim[0];

	cout << vec[1] << " : " << vec[0] << endl;

	cvImg = cvCreateImage( imgSize, 8, 1 );
	double max;
	maxval1(ll,max);
	vector<double> diff;
	cout << rows << " " << cols << " " << vec1.size();

	/*for (int i=0; i < rows*cols; i++) {
        //diff.push_back(oup[i]-vec1[i]);

	    ((uchar*)(cvImg->imageData ))[i] =
						(char) (vec1[i]);
	}*/

	for (int i = 0; i < imgSize.height; i++ ) {
		for (int j = 0; j < imgSize.width; j++ ){

       // diff.push_back(oup[i*imgSize.width + j]-vec1[i*imgSize.width + j]);
				((uchar*)(cvImg->imageData + cvImg->widthStep*i))[j] =
						(char) (oup[i*imgSize.width + j]);

		}
	}

    for(int i=0 ; i < copy.size(); i++) {
    diff.push_back(copy[i]-oup[i]);
    }



    maxval1(diff,max);
    cout << " Max Error : " << max << endl;
    cout << diff[0] << endl;
    cvNamedWindow( "DWT Image", 1 ); // creation of a visualisation window
	cvShowImage( "DWT Image", cvImg ); // image visualisation
	cvWaitKey();
	cvDestroyWindow("DWT Image");
	cvSaveImage("dwt.bmp",cvImg);

	// unsigned int lf=l1.size();
	//  int rows_n =(int) (rows+ J*(lf-1));
	//  int cols_n =(int)  (cols + J * ( lf -1));

	// Finding 2D DWT Transform of the image using symetric extension algorithm
	// Extension is set to 3 (eg., int e = 3)
/*
	vector<int> length;
	vector<double> output,flag;
	int J =2;
	time_t start,end;
    time (&start);
	dwt_2d_sym(vec1,J,nm,output,flag,length);
	time (&end);

	double max;
	vector<int> length2;
	// This algorithm computes DWT of image of any given size. Together with convolution and
	// subsampling operations it is clear that subsampled images are of different length than
	// dyadic length images. In order to compute the "effective" size of DWT we do additional
	// calculations.
	dwt_output_dim_sym(length,length2,J);
	// length2 is gives the integer vector that contains the size of subimages that will
	// combine to form the displayed output image. The last two entries of length2 gives the
	// size of DWT ( rows_n by cols_n)

	int siz = length2.size();
	int rows_n=length2[siz-2];
	int cols_n = length2[siz-1];

	vector<vector< double> > dwtdisp(rows_n, vector<double>(cols_n));
	dispDWT(output,dwtdisp, length ,length2, J);

	// dispDWT returns the 2D object dwtdisp which will be displayed using OPENCV's image
	// handling functions

	//Extracting Individual Images at the Jth level

	int jrow = length[0];
	int jcol= length[1];

	cout << "No. of rows" << jrow << "No. of columns" << jcol;


	//Let 4 images at Jth level be A,Dh,Dv,Dd
	vector<vector< double> > A(jrow, vector<double>(jcol));
	vector<vector< double> > Dh(jrow, vector<double>(jcol));
	vector<vector< double> > Dv(jrow, vector<double>(jcol));
	vector<vector< double> > Dd(jrow, vector<double>(jcol));
	for (int i=0;i < jrow;i++){
	    for (int j=0; j < jcol;j++) {
	        A[i][j]=output[i*jcol+j];
	        Dh[i][j]=output[jrow*jcol+i*jcol+j];
	        Dv[i][j]=output[2*jrow*jcol+i*jcol+j];
	        Dd[i][j]=output[3*jrow*jcol+i*jcol+j];

	    }
	}

	vector<vector<double> >  dwt_output= dwtdisp;

	maxval(dwt_output,max);// max value is needed to take care of overflow which happens because
	// of convolution operations performed on unsigned 8 bit images

	//Displaying Scaled Image
	// Creating Image in OPENCV
	IplImage *cvImg; // image used for output
	CvSize imgSize; // size of output image

	imgSize.width = cols_n;
	imgSize.height = rows_n;

	cvImg = cvCreateImage( imgSize, 8, 1 );
	// dwt_hold is created to hold the dwt output as further operations need to be
	// carried out on dwt_output in order to display scaled images.
	vector<vector<double> > dwt_hold(rows_n, vector<double>( cols_n));
	dwt_hold = dwt_output;
	// Setting coefficients of created image to the scaled DWT output values
	for (int i = 0; i < imgSize.height; i++ ) {
		for (int j = 0; j < imgSize.width; j++ ){
			if ( dwt_output[i][j] <= 0.0){
				dwt_output[i][j] = 0.0;
			}
			if ( i <= (length2[0]) && j <= (length2[1]) ) {
				((uchar*)(cvImg->imageData + cvImg->widthStep*i))[j] =
						(char) ( (dwt_output[i][j] / max) * 255.0);
			} else {
				((uchar*)(cvImg->imageData + cvImg->widthStep*i))[j] =
						(char) (dwt_output[i][j]) ;
			}
		}
	}

	cvNamedWindow( "DWT Image", 1 ); // creation of a visualisation window
	cvShowImage( "DWT Image", cvImg ); // image visualisation
	cvWaitKey();
	cvDestroyWindow("DWT Image");
	cvSaveImage("dwt.bmp",cvImg);


*/
	return 0;
}
