﻿/*===========================================================================*\
 *                                                                           *
 *                           Halftone QR Codes                               *
 *                   Copyright (C) 2012 by Hung-Kuo Chu                      *
 * http://cgv.cs.nthu.edu.tw/projects/Recreational_Graphics/Halftone_QRCodes *
 *                                                                           *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *  Halftone QR Codes is free software: you can redistribute it              *
 *  and/or modify it under the terms of the GNU Lesser General Public        *
 *  License as published by the Free Software Foundation, either version     *
 *  3 of the License, or (at your option) any later version with the         *
 *  following exceptions:                                                    *
 *                                                                           *
 *  If other files instantiate templates or use macros                       *
 *  or inline functions from this file, or you compile this file and         *
 *  link it with other files to produce an executable, this file does        *
 *  not by itself cause the resulting executable to be covered by the        *
 *  GNU Lesser General Public License. This exception does not however       *
 *  invalidate any other reasons why the executable file might be            *
 *  covered by the GNU Lesser General Public License.                        *
 *                                                                           *
 *  Halftone QR Codes is distributed in the hope that it will be             *
 *  useful, but WITHOUT ANY WARRANTY; without even the implied warranty      *
 *  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *  See the GNU Lesser General Public License for more details.              *
 *                                                                           *
 *  You should have received a copy of the GNU LesserGeneral Public          *
 *  License along with Visual QR Code Generator.                             *
 *  If not, see <http://www.gnu.org/licenses/>.                              *
 *                                                                           *
\*===========================================================================*/

#include "HQRC.h"

using namespace std;
using namespace cv;
using namespace HQRCdata;
using namespace HQRCALGORITHM;
using namespace Similarity;
using namespace energy;


	static double randomV5All[] = {
		0.996587,0.972723,0.91178,0.888032,0.990668,0.966763,
		0.906025,0.882084,0.950941,0.926565,0.865868,0.842189,
		0.944696,0.921006,0.859774,0.836105,0.79524,0.819961,
		0.879459,0.904132,0.80047,0.824955,0.885379,0.910416,
		0.842135,0.866804,0.927028,0.951514,0.848168,0.872598,
		0.932711,0.957726,0.979275,0.955467,0.894512,0.870784,
		0.973408,0.949629,0.8886,0.864693,0.933425,0.909488,
		0.848109,0.824379,0.927603,0.903873,0.842517,0.818701,
		0.812412,0.837096,0.8972,0.921409,0.817911,0.842647,
		0.903064,0.92775,0.859349,0.883705,0.944551,0.9689,
		0.865278,0.889789,0.95015,0.974822,0.995218,0.97143,
		0.910487,0.886465,0.989287,0.965624,0.904465,0.88079,
		0.949414,0.925313,0.86448,0.840195,0.942925,0.919362,
		0.85865,0.834653,0.796127,0.820468,0.880782,0.905087,
		0.801827,0.826527,0.887046,0.911565,0.843785,0.868258,
		0.928344,0.952897,0.849584,0.874175,0.934333,0.958928,
		0.977858,0.954101,0.893123,0.869165,0.972126,0.948227,
		0.887083,0.86295,0.931931,0.907692,0.846866,0.823277,
		0.925762,0.902411,0.840972,0.817318,0.81325,0.838006,
		0.898417,0.922991,0.819848,0.843952,0.904143,0.92882,
		0.860859,0.885301,0.945534,0.970466,0.866987,0.89115,
		0.951717,0.976232,0.983223,0.959057,0.898361,0.874423,
		0.977324,0.9533,0.89212,0.868183,0.936959,0.913117,
		0.852096,0.828265,0.931014,0.907094,0.8461,0.822509,
		0.809073,0.832921,0.892716,0.917428,0.813963,0.838111,
		0.898899,0.923302,0.855714,0.880583,0.940459,0.96498,
		0.861292,0.886355,0.946597,0.971039,0.965727,0.941631,
		0.880845,0.85667,0.959946,0.936036,0.875021,0.851529,
		0.919847,0.895476,0.834545,0.810305,0.913592,0.889983,
		0.828976,0.804689,0.825811,0.850291,0.910286,0.934896,
		0.831645,0.855628,0.916246,0.941306,0.873263,0.897719,
		0.957725,0.982388,0.879301,0.903486,0.963797,0.988398,
		0.981781,0.957808,0.897106,0.872765,0.97576,0.952056,
		0.890834,0.866713,0.935713,0.911863,0.850632,0.826345,
		0.929722,0.905897,0.844469,0.820656,0.809841,0.834048,
		0.894423,0.918843,0.815322,0.840381,0.900385,0.924923,
		0.857621,0.882165,0.941825,0.966751,0.863415,0.887914,
		0.947993,0.972515,0.964395,0.940359,0.879293,0.855467,
		0.9587,0.934665,0.873563,0.849952,0.918325,0.894422,
		0.83347,0.809404,0.912267,0.888605,0.827118,0.803038,
		0.826977,0.851855,0.912028,0.936226,0.832576,0.857176,
		0.917722,0.942238,0.874685,0.899527,0.959355,0.983822,
		0.880654,0.905227,0.965116,0.98985,0.990017,0.966187,
		0.905414,0.881524,0.984402,0.960535,0.899498,0.875416,
		0.943956,0.920213,0.859119,0.834834,0.938232,0.914297,
		0.852913,0.829574,0.801355,0.825543,0.885643,0.910657,
		0.806882,0.831738,0.89161,0.916628,0.848959,0.873465,
		0.933592,0.957974,0.854533,0.87923,0.939438,0.963952,
		0.972845,0.948961,0.8878,0.863895,0.967248,0.943202,
		0.881759,0.858434,0.926749,0.902843,0.841934,0.817706,
		0.920548,0.897157,0.83632,0.811733,0.819027,0.843759,
		0.903505,0.927872,0.824568,0.849069,0.909241,0.934042,
		0.866162,0.890884,0.951062,0.975521,0.871846,0.896445,
		0.956758,0.981356,0.988676,0.96496,0.903822,0.879804,
		0.982973,0.959076,0.897922,0.873959,0.942937,0.918796,
		0.857701,0.833984,0.936526,0.913213,0.852088,0.827942,
		0.802454,0.826959,0.887137,0.911909,0.80813,0.833264,
		0.893413,0.917997,0.850447,0.875001,0.934929,0.959512,
		0.856133,0.880357,0.940861,0.965466,0.97137,0.947441,
		0.886781,0.862852,0.96567,0.941975,0.880964,0.857174,
		0.925247,0.901554,0.840774,0.816501,0.919407,0.895451,
		0.834978,0.810996,0.82053,0.844815,0.904832,0.929377,
		0.825872,0.850629,0.910979,0.935491,0.867571,0.891798,
		0.952246,0.976693,0.873522,0.898087,0.95829,0.982805,
		0.976534,0.952622,0.89183,0.867847,0.970838,0.946785,
		0.88551,0.861792,0.93072,0.906712,0.845609,0.8212,
		0.924682,0.900929,0.839831,0.815696,0.815208,0.839068,
		0.899408,0.923971,0.820604,0.844886,0.905697,0.930176,
		0.861975,0.886998,0.947054,0.971847,0.868134,0.892881,
		0.952963,0.977606,0.959118,0.935552,0.874504,0.850271,
		0.953691,0.929404,0.868541,0.844227,0.913378,0.889756,
		0.8279,0.80443,0.907391,0.88326,0.822852,0.798739,
		0.832948,0.857165,0.917055,0.941296,0.83829,0.862923,
		0.923242,0.9475,0.87964,0.904317,0.964433,0.989029,
		0.885703,0.910321,0.970543,0.994824,0.975233,0.951429,
		0.889851,0.866225,0.969235,0.945482,0.884398,0.86057,
		0.929333,0.905139,0.844579,0.819957,0.923123,0.899397,
		0.838572,0.814418,0.816244,0.840948,0.900915,0.925565,
		0.822171,0.846603,0.906801,0.931364,0.863786,0.8886,
		0.94871,0.973122,0.869802,0.894417,0.954431,0.979018,
		0.958098,0.933957,0.872543,0.849163,0.952249,0.928227,
		0.866969,0.843291,0.912395,0.888262,0.827056,0.802777,
		0.90594,0.882107,0.821375,0.797026,0.833846,0.858292,
		0.918534,0.943036,0.839488,0.863864,0.92423,0.948996,
		0.881049,0.905898,0.965725,0.990427,0.887307,0.911829,
		0.971673,0.996321
};
void Mat_Decompose(const cv::Mat& _src, cv::Mat& _out, cv::Mat& _mask)
{
	/// The input should be channel 3 with float type
	if(_src.channels() < 1 || _src.channels() > 4  )
		CV_Error(CV_StsBadArg, "_src has incorrect channel (not 1,2,3,4)");

	int srcDim = _src.channels();
	if(srcDim == 1 || srcDim == 3)
	{
		_out = _src.clone();	
	}
	else if(srcDim == 2)
	{
		VecMat channels;
		cv::split(_src, channels);
		_out = channels[0];
		_mask = channels[1];
		cv::threshold(_mask, _mask, 1, 255, cv::THRESH_BINARY);		
	}
	else if(srcDim == 4)
	{
		_out = Mat(_src.size(), CV_MAKETYPE(_src.depth(), 3));
		_mask = Mat(_src.size(), CV_MAKETYPE(_src.depth(), 1));		
		Mat out[] = { _out, _mask };
		int from_to[] = { 0,0, 1,1, 2,2, 3,3 };
		mixChannels(&_src, 1, out, 2, from_to, 4);
		cv::threshold(_mask, _mask, 1, 255, cv::THRESH_BINARY);				
	}	
}
cv::Mat DBCvt_ID2Pattern(int _id, int _size)
{	
	System::String^ binStr = Convert::ToString(_id, 2);
	int length = _size*_size;		
	cv::Mat img(_size, _size, CV_8UC1);
	img.setTo(cv::Scalar::all(255));
	uchar* imgPtr = img.ptr<uchar>(0);
	for(int i = 0; i < binStr->Length; ++i)
		imgPtr[i] = (System::Convert::ToInt32(binStr->Substring(binStr->Length-i-1, 1))==1) ? 0 : 255;
	return img;
}
int DBCvt_Pattern2ID(const cv::Mat& _img)
{
	int nRows = _img.rows;
	int nCols = _img.cols;
	if (_img.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}

	double id = 0.0;
	int bit = 0;
	for(int i = 0; i < nRows; ++i)
	{
		const uchar* imgPtr = _img.ptr<uchar>(i);		
		for (int j = 0; j < nCols; ++j)		
		{
			if(imgPtr[j] == 0) id += std::pow(2.0, (double)bit);		
			bit++;
		}
	}

	return cv::saturate_cast<int>(id);
}

#define ALLCHANNEL -1

static double getSSIM(IplImage* src1, IplImage* src2, IplImage* mask,
	const double K1,
	const double K2,
	const int L,
	const int downsamplewidth,
	const int gaussian_window,
	const double gaussian_sigma,
	IplImage* dest)
{
	// default settings
	const double C1 = (K1 * L) * (K1 * L); //6.5025 C1 = (K(1)*L)^2;
	const double C2 = (K2 * L) * (K2 * L); //58.5225 C2 = (K(2)*L)^2;

	//　get width and height
	int x=src1->width, y=src1->height;

	//　distance (down sampling) setting
	int rate_downsampling = std::max(1, int((std::min(x,y) / downsamplewidth) + 0.5));

	int nChan=1, d=IPL_DEPTH_32F;

	//　size before down sampling
	CvSize size_L = cvSize(x, y);

	//　size after down sampling
	CvSize size = cvSize(x / rate_downsampling, y / rate_downsampling);

	//　image allocation
	cv::Ptr<IplImage> img1 = cvCreateImage( size, d, nChan);
	cv::Ptr<IplImage> img2 = cvCreateImage( size, d, nChan);


	//　convert 8 bit to 32 bit float value
	cv::Ptr<IplImage> img1_L = cvCreateImage( size_L, d, nChan);
	cv::Ptr<IplImage> img2_L = cvCreateImage( size_L, d, nChan);
	cvConvert(src1, img1_L);
	cvConvert(src2, img2_L);

	//　down sampling
	cvResize(img1_L, img1);
	cvResize(img2_L, img2);

	//　buffer alocation
	cv::Ptr<IplImage> img1_sq = cvCreateImage( size, d, nChan);
	cv::Ptr<IplImage> img2_sq = cvCreateImage( size, d, nChan);
	cv::Ptr<IplImage> img1_img2 = cvCreateImage( size, d, nChan);

	//　pow and mul
	cvPow( img1, img1_sq, 2 );
	cvPow( img2, img2_sq, 2 );
	cvMul( img1, img2, img1_img2, 1 );

	//　get sigma
	cv::Ptr<IplImage> mu1 = cvCreateImage( size, d, nChan);
	cv::Ptr<IplImage> mu2 = cvCreateImage( size, d, nChan);
	cv::Ptr<IplImage> mu1_sq = cvCreateImage( size, d, nChan);
	cv::Ptr<IplImage> mu2_sq = cvCreateImage( size, d, nChan);
	cv::Ptr<IplImage> mu1_mu2 = cvCreateImage( size, d, nChan);


	cv::Ptr<IplImage> sigma1_sq = cvCreateImage( size, d, nChan);
	cv::Ptr<IplImage> sigma2_sq = cvCreateImage( size, d, nChan);
	cv::Ptr<IplImage> sigma12 = cvCreateImage( size, d, nChan);

	//　allocate buffer
	cv::Ptr<IplImage> temp1 = cvCreateImage( size, d, nChan);
	cv::Ptr<IplImage> temp2 = cvCreateImage( size, d, nChan);
	cv::Ptr<IplImage> temp3 = cvCreateImage( size, d, nChan);

	//ssim map
	cv::Ptr<IplImage> ssim_map = cvCreateImage( size, d, nChan);


	//////////////////////////////////////////////////////////////////////////
	// 	// PRELIMINARY COMPUTING

	//　gaussian smooth
	cvSmooth( img1, mu1, CV_GAUSSIAN, gaussian_window, gaussian_window, gaussian_sigma );
	cvSmooth( img2, mu2, CV_GAUSSIAN, gaussian_window, gaussian_window, gaussian_sigma );

	//　get mu
	cvPow( mu1, mu1_sq, 2 );
	cvPow( mu2, mu2_sq, 2 );
	cvMul( mu1, mu2, mu1_mu2, 1 );

	//　calc sigma
	cvSmooth( img1_sq, sigma1_sq, CV_GAUSSIAN, gaussian_window, gaussian_window, gaussian_sigma );
	cvAddWeighted( sigma1_sq, 1, mu1_sq, -1, 0, sigma1_sq );

	cvSmooth( img2_sq, sigma2_sq, CV_GAUSSIAN, gaussian_window, gaussian_window, gaussian_sigma);
	cvAddWeighted( sigma2_sq, 1, mu2_sq, -1, 0, sigma2_sq );

	cvSmooth( img1_img2, sigma12, CV_GAUSSIAN, gaussian_window, gaussian_window, gaussian_sigma );
	cvAddWeighted( sigma12, 1, mu1_mu2, -1, 0, sigma12 );


	//////////////////////////////////////////////////////////////////////////
	// FORMULA

	// (2*mu1_mu2 + C1)
	cvScale( mu1_mu2, temp1, 2 );
	cvAddS( temp1, cvScalarAll(C1), temp1 );

	// (2*sigma12 + C2)
	cvScale( sigma12, temp2, 2 );
	cvAddS( temp2, cvScalarAll(C2), temp2 );

	// ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
	cvMul( temp1, temp2, temp3, 1 );

	// (mu1_sq + mu2_sq + C1)
	cvAdd( mu1_sq, mu2_sq, temp1 );
	cvAddS( temp1, cvScalarAll(C1), temp1 );

	// (sigma1_sq + sigma2_sq + C2)
	cvAdd( sigma1_sq, sigma2_sq, temp2 );
	cvAddS( temp2, cvScalarAll(C2), temp2 );

	// ((mu1_sq + mu2_sq + C1).*(sigma1_sq + sigma2_sq + C2))
	cvMul( temp1, temp2, temp1, 1 );

	// ((2*mu1_mu2 + C1).*(2*sigma12 + C2))./((mu1_sq + mu2_sq + C1).*(sigma1_sq + sigma2_sq + C2))
	cvDiv( temp3, temp1, ssim_map, 1 );

	cv::Ptr<IplImage> stemp = cvCreateImage( size, IPL_DEPTH_8U, 1);
	cv::Ptr<IplImage> mask2 = cvCreateImage( size, IPL_DEPTH_8U, 1);

	cvConvertScale(ssim_map, stemp, 255.0, 0.0);
	cvResize(stemp,dest);
	cvResize(mask,mask2);

	CvScalar index_scalar = cvAvg( ssim_map, mask2 );

	// through observation, there is approximately 
	// 1% error max with the original matlab program

	return index_scalar.val[0];
}


double xcvCalcSSIM(IplImage* src, IplImage* dest, int channel, int method, IplImage* _mask,
	const double K1,
	const double K2,
	const int L,
	const int downsamplewidth,
	const int gaussian_window,
	const double gaussian_sigma,
	IplImage* ssim_map
	)
{  
	IplImage* mask;
	IplImage* __mask=cvCreateImage(cvGetSize(src),8,1);
	IplImage* smap=cvCreateImage(cvGetSize(src),8,1);

	cvSet(__mask,cvScalarAll(255));


	if(_mask==NULL)mask=__mask;
	else mask=_mask;
	IplImage* ssrc;
	IplImage* sdest;
	if(src->nChannels==1)
	{
		ssrc=cvCreateImage(cvGetSize(src),8,3);
		sdest=cvCreateImage(cvGetSize(src),8,3);
		cvCvtColor(src,ssrc,CV_GRAY2BGR);
		cvCvtColor(dest,sdest,CV_GRAY2BGR);
	}
	else
	{
		ssrc = cvCloneImage(src);
		sdest = cvCloneImage(dest);
		cvCvtColor(dest,sdest,method);
		cvCvtColor(src,ssrc,method);
	}

	IplImage* gray[4];
	IplImage* sgray[4];
	for(int i=0;i<4;i++)
	{
		gray[i] = cvCreateImage(cvGetSize(src),8,1);
		sgray[i] = cvCreateImage(cvGetSize(src),8,1);
	}

	cvSplit(sdest,gray[0],gray[1],gray[2],NULL);
	cvSplit(ssrc,sgray[0],sgray[1],sgray[2],NULL);

	double sn=0.0;

	if(channel==ALLCHANNEL)
	{
		for(int i=0;i<src->nChannels;i++)
		{
			sn+=getSSIM(sgray[i],gray[i],mask,K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma,smap);
		}
		sn/=(double)src->nChannels; 
	}
	else
	{
		sn	= getSSIM(sgray[channel],gray[channel],mask,K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma,smap);
	}

	for(int i=0;i<4;i++)
	{
		cvReleaseImage(&gray[i]);
		cvReleaseImage(&sgray[i]);
	}

	if(ssim_map!=NULL)cvCopy(smap,ssim_map);
	cvReleaseImage(&smap);
	cvReleaseImage(&__mask);
	cvReleaseImage(&ssrc);
	cvReleaseImage(&sdest);
	return sn;
}

double xcvCalcDSSIM(IplImage* src, IplImage* dest, int channel, int method, IplImage* _mask,
	const double K1,
	const double K2,
	const int L,
	const int downsamplewidth,
	const int gaussian_window,
	const double gaussian_sigma,
	IplImage* ssim_map
	)
{
	double ret = xcvCalcSSIM(src, dest, channel, method, _mask, K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma,ssim_map);
	if(ret==0)ret=-1.0;
	else ret =(1.0 / ret) - 1.0;
	return ret;
}
double xcvCalcSSIMBB(IplImage* src, IplImage* dest, int channel, int method, int boundx,int boundy,const double K1,	const double K2,	const int L, const int downsamplewidth, const int gaussian_window, const double gaussian_sigma, IplImage* ssim_map)
{
	IplImage* mask = cvCreateImage(cvGetSize(src),8,1);
	cvZero(mask);
	cvRectangle(mask,cvPoint(boundx,boundy),cvPoint(src->width-boundx,src->height-boundy),cvScalarAll(255),CV_FILLED);

	double ret = xcvCalcSSIM(src,dest,channel,method,mask,K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma,ssim_map);
	cvReleaseImage(&mask);
	return ret;
}

double xcvCalcDSSIMBB(IplImage* src, IplImage* dest, int channel, int method, int boundx,int boundy,const double K1,	const double K2,	const int L, const int downsamplewidth, const int gaussian_window, const double gaussian_sigma, IplImage* ssim_map)
{
	IplImage* mask = cvCreateImage(cvGetSize(src),8,1);
	cvZero(mask);
	cvRectangle(mask,cvPoint(boundx,boundy),cvPoint(src->width-boundx,src->height-boundy),cvScalarAll(255),CV_FILLED);

	double ret = xcvCalcSSIM(src,dest,channel,method,mask,K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma,ssim_map);
	cvReleaseImage(&mask);

	if(ret==0)ret=-1.0;
	else ret = (1.0 / ret) - 1.0;
	return ret;
}

double NFSSIM::calcSSIM(cv::Mat& src1, cv::Mat& src2, int channel, int method, cv::Mat& mask, const double K1, const double K2,	const int L, const int downsamplewidth, const int gaussian_window, const double gaussian_sigma, cv::Mat& ssim_map)
{
	if(ssim_map.empty())ssim_map.create(src1.size(),CV_8U);

	if(mask.empty())
	{
		xcvCalcSSIM(&IplImage(src1),&IplImage(src2),channel,method,NULL,K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma, &IplImage(ssim_map));
		return xcvCalcSSIM(&IplImage(src1),&IplImage(src2),channel,method,NULL,K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma, &IplImage(ssim_map));
	}
	else
		return xcvCalcSSIM(&IplImage(src1),&IplImage(src2),channel,method,&IplImage(mask),K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma, &IplImage(ssim_map));
}

double NFSSIM::calcSSIMBB(cv::Mat& src1, cv::Mat& src2, int channel, int method, int boundx, int boundy, const double K1, const double K2, const int L, const int downsamplewidth, const int gaussian_window, const double gaussian_sigma, cv::Mat& ssim_map)
{
	if(ssim_map.empty())ssim_map.create(src1.size(),CV_8U);
	return xcvCalcSSIMBB(&IplImage(src1),&IplImage(src2),channel,method,boundx,boundy,K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma, &IplImage(ssim_map));
}

double NFSSIM::calcDSSIM(cv::Mat& src1, cv::Mat& src2, int channel, int method, cv::Mat& mask, const double K1, const double K2,	const int L, const int downsamplewidth, const int gaussian_window, const double gaussian_sigma, cv::Mat& ssim_map)
{
	if(ssim_map.empty())ssim_map.create(src1.size(),CV_8U);

	if(mask.empty())
	{
		xcvCalcSSIM(&IplImage(src1),&IplImage(src2),channel,method,NULL,K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma, &IplImage(ssim_map));
		return xcvCalcDSSIM(&IplImage(src1),&IplImage(src2),channel,method,NULL,K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma, &IplImage(ssim_map));
	}
	else
		return xcvCalcDSSIM(&IplImage(src1),&IplImage(src2),channel,method,&IplImage(mask),K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma, &IplImage(ssim_map));
}

double NFSSIM::calcDSSIMBB(cv::Mat& src1, cv::Mat& src2, int channel, int method, int boundx, int boundy, const double K1, const double K2, const int L, const int downsamplewidth, const int gaussian_window, const double gaussian_sigma, cv::Mat& ssim_map)
{
	if(ssim_map.empty())ssim_map.create(src1.size(),CV_8U);
	return xcvCalcDSSIMBB(&IplImage(src1),&IplImage(src2),channel,method,boundx,boundy,K1,K2,L,downsamplewidth,gaussian_window,gaussian_sigma, &IplImage(ssim_map));
}


bool HKCPDBProc1::Execute(HKCAppItem^ _appItem)
{
	/// Get data ready
	HKCPDBParam^ pdbParam = _appItem->Param->PDB;
	HKCPDBData& pdbData = _appItem->Data->PDBData;	

	/// Clear old data
	pdbData.Clear(); 

	/// Set the size of pattern
	int pSize = 3;
	pdbParam->PSize = pSize;
	pdbData.PSize = pSize;

	/// Read pattern data
	int pNum = (int)Math::Pow(2, pSize*pSize);	
	VecPtrn& patterns = pdbData.Patterns;
	patterns.resize(pNum, NULL);
	for(int i = 0; i < pNum; ++i)
	{		
		HKCPattern* ptrnPtr = new HKCPattern;
		ptrnPtr->ID = i;
		ptrnPtr->RVal = ptrnPtr->RVal2 = randomV5All[i];
		patterns[ptrnPtr->ID] = ptrnPtr;		
	}		

	/// Decode pattern's id into image
	VecPtrn& whites = pdbData.Whites;
	VecPtrn& blacks = pdbData.Blacks;
	for(VecPtrn::iterator p_it = patterns.begin(); p_it != patterns.end(); ++p_it)
	{
		HKCPattern* p_pt = (*p_it);	

		/// Decode the id to pattern image
		p_pt->Img = DBCvt_ID2Pattern(p_pt->ID, pdbData.PSize);			

		/// Record the code of center pixel and assign the pattern to proper pool.
		/// White(Tag=0) and black(Tag=1)
		p_pt->Tag = (p_pt->Img.at<uchar>(1,1) == 0) ? 1 : 0;
		if(p_pt->Tag) 
			blacks.push_back(p_pt);
		else 
			whites.push_back(p_pt);
	}

	/// Compute the pair-wise pattern similarity	
	//HKCPSFunc^ psFunc = gcnew HKCPSMSE;
	//HKCPSFunc^ psFunc = gcnew HKCPSPSNR;
	HKCPSFunc^ psFunc = gcnew HKCPSSSIM;

	//fstream fp;
	//fp.open("123.txt", ios::out);//開啟檔案
	int simcount=0;
	cv::Size mSize(patterns.size(), patterns.size());
	pdbData.SimMap = cv::Mat::zeros(mSize, CV_64FC1);
	Mat_<double> _SimMap = pdbData.SimMap;
	for(size_t i = 0; i < patterns.size(); ++i)
	{
		HKCPattern* p_pt1 = patterns[i];	
		for(size_t j = i; j < patterns.size(); ++j)
		{
			HKCPattern* p_pt2 = patterns[j];	

			/// Compute the pattern similarity
			//double simVal = psFunc->Compute(p_pt1->Img, p_pt2->Img);
			//_SimMap[p_pt1->ID][p_pt2->ID] = simVal;
			//if(j != i) _SimMap[p_pt2->ID][p_pt1->ID] = simVal;
			_SimMap[p_pt1->ID][p_pt2->ID] = simvals[simcount];
			if(j != i) _SimMap[p_pt2->ID][p_pt1->ID] =  simvals[simcount];
			simcount++;
		}

	}	
	//fp.close();
	/// Normalize the similarity map
	psFunc->Normalize(pdbData.SimMap, 0.0, 1.0);
	pdbData.isReady = true;
	return true;
}
/// Generate QR code
bool HKCQRCGen1::Execute(HKCAppItem^ _appItem)
{
	if(!_appItem) return false;		

	/// Get data ready
	HKCPDBData& pdbData = _appItem->Data->PDBData;
	HKCQRCData& qrcData = _appItem->Data->QRCData;	
	qrcData.Clear(); /// Clear old data

	HKCQRCParam^ qrcParam = _appItem->Param->QRCode;
	qrcData.Text = MarshalString(qrcParam->Text);
	qrcData.Ver = qrcParam->Version;
	qrcData.ECL = (int)qrcParam->ECLvl;	

	/////////////////////////////////////////////////
	/// Generate QR code data
	/////////////////////////////////////////////////
	QRcode *qrcodeB;				
	QRcode *qrcodeC;				
	QRcode *qrcodeT;				
	int QRMask=-1;						
	int QRSize=qrcData.Ver*4+17;	
	QRencodeMode qrMode=QR_MODE_8;	
	QRecLevel QRlv=(QRecLevel)(int(qrcData.ECL));/// QR code error correction level
	char inputStringChar[1024];		
	int stringSize=qrcData.Text.length();
	qrcData.Text.copy(inputStringChar,stringSize,0); 
	*(inputStringChar+stringSize)='\0'; 

	
	changeColorFlag(0); 
	changeCodeWFlag(0);    
	changeMaskFlag(QRMask);

	/// ｲ｣･ﾍQR code
	qrcodeB = QRcode_encodeString(inputStringChar,qrcData.Ver,(QRecLevel)QRlv,qrMode,1);
	if(!qrcodeB)
	{
		Console::WriteLine("HKCQRCGen1::Execute() : Generate QR code failed!");
		return false;
	}

	/// Check if the version is changed
	if(qrcData.Ver != qrcodeB->version)
	{
		qrcData.Ver = qrcodeB->version; 
		qrcParam->Version = qrcData.Ver;
		QRSize=qrcData.Ver*4+17;

		Console::WriteLine("HKCQRCGen1::Execute() : The version of QR code is changed to " + Int32(qrcData.Ver).ToString() + "!");
	}

	
	changeColorFlag(1);
	changeCodeWFlag(0);
	changeMaskFlag(-2);

	
	qrcodeC = QRcode_encodeString(inputStringChar,qrcData.Ver,(QRecLevel)QRlv,qrMode,1);
	if(!qrcodeC)
	{
		Console::WriteLine("HKCQRCGen1::Execute() : Generate RS block map failed!");
		free(qrcodeB);
		return false;
	}

	
	changeColorFlag(1);
	changeCodeWFlag(3);
	changeMaskFlag(-2);

	
	qrcodeT = QRcode_encodeString(inputStringChar,qrcData.Ver,(QRecLevel)QRlv,qrMode,1);
	if(!qrcodeT)
	{
		Console::WriteLine("HKCQRCGen1::Execute() : Generate code word map failed!");
		free(qrcodeB);
		free(qrcodeC);
		return false;
	}

	/////////////////////////////////////////////////
	/// Compute QR code data
	/////////////////////////////////////////////////
	/// Update the error correction information
	int qrSpec[6];
	QRspec_getEccSpec(qrcData.Ver, QRlv, qrSpec);
	qrcData.ECC = QRspec_rsEcCapacity(qrSpec);	
	qrcParam->ECCap = QRspec_rsEcCapacity(qrSpec);
	qrcParam->RSNum = QRspec_rsBlockNum(qrSpec);
	int rsbNum[2] = {QRspec_rsBlockNum1(qrSpec), QRspec_rsBlockNum2(qrSpec)}; 
	int rsbSize[2] = {QRspec_rsCodeWords1(qrSpec), QRspec_rsCodeWords2(qrSpec)};

	/// Pre-allocate RS block and code words
	VecRSB& qrcRSBlocks = qrcData.RSBlocks;
	qrcRSBlocks.resize(qrcParam->RSNum, NULL);
	for(int i = 0; i < qrcParam->RSNum; ++i)
	{
		int rsbCWs = (i < rsbNum[0]) ? rsbSize[0] : rsbSize[1];
		HKCRSBlock* rsBlock = new HKCRSBlock;
		rsBlock->CodeWords.resize(rsbCWs, NULL);
		for(int j = 0; j < rsbCWs; ++j)
			rsBlock->CodeWords[j] = new HKCCodeWord;
		qrcRSBlocks[i] = rsBlock;
	}

	Mat& qrcode = qrcData.QRCode;
	Mat& qrcRS = qrcData.RSMap;
	Mat& qrcCW = qrcData.CWMap;
	qrcode.create(QRSize,QRSize,CV_8UC1);
	qrcRS.create(QRSize,QRSize,CV_32SC1);
	qrcCW.create(QRSize,QRSize,CV_32SC1);

	VecMdu& qrcModules = qrcData.Modules;
	qrcModules.resize(QRSize*QRSize);

	for(int y = 0; y < QRSize; ++y)
	{
		uchar* qrcPtr = qrcode.ptr<uchar>(y);
		int* RSPtr = qrcRS.ptr<int>(y);
		int* CWPtr = qrcCW.ptr<int>(y);
		int yStep = y*QRSize;
		for(int x = 0; x < QRSize; ++x)
		{
			int xStep = yStep + x;

			/// Pixel color (Black/White)
			unsigned char qrcVal = (qrcodeB->data[xStep] & 1) ? 0 : 255;
			qrcPtr[x] = qrcVal;			

			/// Type of module
			// if (int)qrcodeC->data[xStep] == 136||(int)qrcodeC->data[xStep] == 137 => version information
			// if (int)qrcodeC->data[xStep] == 132||(int)qrcodeC->data[xStep] == 129 => Format Information
			// if (int)qrcodeC->data[xStep] == 160||(int)qrcodeC->data[xStep] == 161 => Alignment Patterns
			// if (int)qrcodeC->data[xStep] == 144||(int)qrcodeC->data[xStep] == 145 => Timing Patterns
			// if (int)qrcodeC->data[xStep] == 192||(int)qrcodeC->data[xStep] == 193  => Separators Patterns & Position Detection Patterns
			// if (int)qrcodeC->data[xStep] == 82 => Remaining Bits
			int mType = -1;
			int rsVal = (int)qrcodeC->data[xStep];
			if(rsVal > 0 && rsVal < 82) mType = 0;				/// Data codeword
			else if(rsVal == 82) mType = 1;						/// Remaining Bits
			else if(rsVal == 136 || rsVal == 137) mType = 2;	/// Version Information
			else if(rsVal == 132 || rsVal == 129) mType = 3;	/// Format Information
			else if(rsVal == 160 || rsVal == 161) mType = 4;	/// Alignment Patterns
			else if(rsVal == 144 || rsVal == 145) mType = 5;	/// Timing Patterns
			else if(rsVal == 192 || rsVal == 193) mType = 6;	/// Separators Patterns & Position Detection Patterns

			/// Index of RS block
			RSPtr[x] = (mType == 0) ? rsVal : -1;

			/// Index of code word in RS block
			int cwVal = (int)qrcodeT->data[xStep];
			CWPtr[x] = (mType == 0) ? cwVal : -1;			

			/// Get module data
			HKCModule* qrcModule = new HKCModule;
			qrcModule->Type = mType;
			qrcModule->Pos = cv::Point(x,y);		/// Image location
			qrcModule->QRC = (qrcVal) ? 0 : 1;	/// QR code value(1: Black, 0: white)
			qrcModule->RSID = rsVal;				/// RS block index (1-based index)
			qrcModule->CWID = cwVal;				/// Code word index (1-based index)
			qrcModules[xStep] = qrcModule;

			/// Get RS block and code word data
			if(mType == 0)
			{
				HKCRSBlock* rsBlock = qrcRSBlocks[rsVal-1];
				rsBlock->CodeWords[cwVal-1]->Modules.push_back(qrcModule);
			}
		}
	}

	free(qrcodeB);
	free(qrcodeC);
	free(qrcodeT);

	/// Once we have the original QR code image, 
	/// create an upsample version image 	
	int pSize = pdbData.PSize;
	Mat& qrcImg = qrcData.QRCImg;
	cv::Size newSize = qrcode.size();
	newSize.width *= pSize;
	newSize.height *= pSize;
	cv::resize(qrcode, qrcImg, newSize, 0, 0, INTER_NEAREST);

	/// The QR code data is ready now!
	qrcData.isReady = true;



	return true;
}
/// Default Data initialization
bool HKCDataInit1::Execute(HKCAppItem^ _appItem)
{
	if(!_appItem) return false;
	if(!_appItem->Data->PDBData.isReady || !_appItem->Data->QRCData.isReady)
	{
		Console::WriteLine("HKCDataInit1::Execute() : QR code or database is not ready yet!");
		return false;
	}
	/////////////////////////////////////////////////
	/// Initialize image data
	/////////////////////////////////////////////////			
	/// Get data ready
	HKCImgData& imgData = _appItem->Data->ImgData;
	HKCQRCParam^ QRCparam = _appItem->Param->QRCode;
	int Ver = QRCparam->Version;
	int QRsize= (Ver*4+17)*3;
	Size dsize = Size(QRsize,QRsize);
	Mat& rgbImg = imgData.RGBImg;
	Mat& mask = imgData.Mask;
	Mat& srcImg= imgData.SrcImg;
	Mat tmask;
	
	
	if (mask.empty())
	{	
		resize(srcImg,srcImg,dsize);
		Mat_Decompose(srcImg, rgbImg, mask);
	}
	else
	{	resize(srcImg,srcImg,dsize);
		resize(mask,mask,dsize);
		Mat_Decompose(srcImg,rgbImg,tmask);
	}
		
	if(rgbImg.empty())
	{
		Console::WriteLine("HKCDataInit1::Execute() : Decompose source image failed");
		return false;
	}
	if(mask.empty()) 
	{
		mask.create(rgbImg.size(), CV_8UC1);
		mask.setTo(cv::Scalar::all(255));
	}


	
	/// Get the painter's canvas	
	Mat& userMap = imgData.UserMap;
	
	//HKCMediaItem^ cnvsItem = _appItem->Find("Painter Canvas");	
	if(!imgData.UserMap.empty())
	{	
		resize(userMap,userMap,dsize);
		int srcDim = userMap.channels();
		if(srcDim != 1 && srcDim != 3)
		{			
			//Mat* cnvsImg = (Mat*)(cnvsItem->Media->Data());
			Mat userimg= imgData.UserMap;
			Mat cnvsImg[]={userimg};
			userMap = Mat(cnvsImg->size(), CV_8UC3);
			Mat tmpImg = Mat(userMap.size(), CV_8UC1);		
			Mat out[] = { userMap, tmpImg };
			int from_to[] = { 0,0, 1,1, 2,2, 3,3 };
			mixChannels(cnvsImg, 1, out, 2, from_to, 4);
		}
	}	

	/// The image data is ready now!
	imgData.isReady = true;
	Console::WriteLine("initial done");
	
	return true;
}
/*                        Internal Operations                          */
/// Perform data initialization
bool HKCOptimizer::Initialize(HKCAppItem^ _appItem)
{
	if(!_appItem) return false;

	/// Get data ready	
	HKCImgData& imgData = _appItem->Data->ImgData;	
	HKCQRCData& qrcData = _appItem->Data->QRCData;	
	HKCPDBData& pdbData = _appItem->Data->PDBData;	
	if(!imgData.isReady || !qrcData.isReady || !pdbData.isReady)
	{
		Console::WriteLine("HKCOptimizer::Initialize() : Necessary data are not ready yet!");
		return false;
	}

	Mat& imgMsk = imgData.Mask;
	Mat& impMap = imgData.ImpMap;
	Mat& hltnImg = imgData.HalftoneImg;
	Mat& qrcMap = qrcData.QRCode;
	VecMdu& modules = qrcData.Modules;
	VecRSB& rsblocks = qrcData.RSBlocks;
	GraphT& mdGraph = qrcData.MdGraph;	
	cv::Size qrcSize = qrcMap.size();
	int pSize = pdbData.PSize;	
	Mat& simMap = pdbData.SimMap;	

	HKCOptmParam^ optmParam = _appItem->Param->Optimize;	
	double sigmaE = optmParam->SigmaS;

	/// Cleanup data of RS blocks and codewords
	VecRSB::iterator r_it = rsblocks.begin(), r_end = rsblocks.end();
	for(; r_it != r_end; ++r_it)
	{
		HKCRSBlock* r_pt = (*r_it);
		r_pt->Tag = -1;

		VecCW::iterator cw_it = r_pt->CodeWords.begin(), cw_end = r_pt->CodeWords.end(); 
		for(; cw_it != cw_end; ++cw_it)
		{
			HKCCodeWord* cw_pt = (*cw_it);
			cw_pt->Tag = -1;
		}
	}

	/// Down sample mask
	Mat mask;
	cv::resize(imgMsk, mask, qrcSize, CV_INTER_AREA);
	cv::threshold(mask, mask, 1, 255, THRESH_BINARY);	

	/// Build the module graph's vertices list
	mdGraph.clear();	
	GVIndexM gVidxMap = boost::get(boost::vertex_index, mdGraph);
	VecMdu::iterator m_it = modules.begin(), m_end = modules.end();
	for(; m_it != m_end; ++m_it)
	{
		HKCModule* m_pt = (*m_it);

		/// Currently we consider only data codewords within the mask
		if(m_pt->Type != 0 || mask.at<uchar>(m_pt->Pos) == 0) 
		{
			m_pt->PID1 = m_pt->PID2 = m_pt->VID = -1;
			continue;
		}

		/// Convert the halftone image to pattern ID
		cv::Rect pRect(m_pt->Pos*pSize, cv::Size(pSize, pSize));		
		int pID = DBCvt_Pattern2ID(hltnImg(pRect));
		m_pt->PID1 = m_pt->PID2 = pID;

		/// Get the importance weight
		m_pt->Weit = impMap.at<double>(m_pt->Pos);

		/// Set the tag of belonging RS block and codeword
		rsblocks[m_pt->RSID-1]->Tag = 0;
		rsblocks[m_pt->RSID-1]->CodeWords[m_pt->CWID-1]->Tag = 0;

		/// Add module node to the graph
		GVDescT v = boost::add_vertex(m_pt, mdGraph);

		/// Module's vertex index in the graph
		m_pt->VID = gVidxMap[v];
	}

	/// Update data of RS blocks and codewords
	r_it = rsblocks.begin(); r_end = rsblocks.end();
	for(; r_it != r_end; ++r_it)
	{
		HKCRSBlock* r_pt = (*r_it);
		if(r_pt->Tag == -1) continue;

		VecCW::iterator cw_it = r_pt->CodeWords.begin(), cw_end = r_pt->CodeWords.end(); 
		for(; cw_it != cw_end; ++cw_it)
		{
			HKCCodeWord* cw_pt = (*cw_it);
			if(cw_pt->Tag == -1) continue;

			int mdCount = 0;
			cw_pt->Priority = 0;
			cw_pt->Weit = 0.0;

			VecMdu::iterator m_it = cw_pt->Modules.begin(), m_end = cw_pt->Modules.end();
			for(; m_it != m_end; ++m_it)
			{
				HKCModule* m_pt = (*m_it);
				if(m_pt->PID1 == -1) continue;

				cw_pt->Weit += m_pt->Weit;
				mdCount++;
			}

			/// Averaged weight
			cw_pt->Weit /= (double)mdCount;
		}
	}

	/// Build the module graph's edges list
	int gNumV = boost::num_vertices(mdGraph);
	GVElemntM gVelmtMap = boost::get(boost::vertex_element, mdGraph);
	GEDescT eDesc;
	bool eFlag;
	for(int i = 0; i < gNumV; ++i)
	{
		HKCModule* m1_pt = gVelmtMap[i];
		for(int j = i+1; j < gNumV; ++j )
		{
			HKCModule* m2_pt = gVelmtMap[j];

			/// Check if two modules are adjacent to each other (4-neighbors)
			int dx = Math::Abs(m1_pt->Pos.x - m2_pt->Pos.x);
			int dy = Math::Abs(m1_pt->Pos.y - m2_pt->Pos.y);
			if((dx == 1 && dy == 0) || (dx == 0 && dy == 1))
			{
				/// edge weight = exp(-dist(m1, m2) / (2*sigma))				
				double eWeit = Math::Exp(simMap.at<double>(m1_pt->PID1, m2_pt->PID1)*-sigmaE);
				boost::tie(eDesc, eFlag) = boost::add_edge(i, j, GEWeightT(eWeit), mdGraph);
				if(!eFlag) printf("repeated edge: (%d ,%d)\n", i, j);
			}
		}
	}	

	VecPtrn& patterns = pdbData.Patterns;
	VecPtrn::iterator p_it;
	if(optmParam->NormRel)
	{		
		/// Normalize pattern's reliability
		double minRel = 1.0e5, maxRel = -1.0e5; 		
		for(p_it = patterns.begin(); p_it != patterns.end(); ++p_it)
		{
			HKCPattern* p_pt = (*p_it);	
			if(p_pt->RVal2 < minRel) minRel = p_pt->RVal2;
			if(p_pt->RVal2 > maxRel) maxRel = p_pt->RVal2;
		}
		double itvlRel = fabs(maxRel - minRel);
		for(p_it = patterns.begin(); p_it != patterns.end(); ++p_it)
		{
			HKCPattern* p_pt = (*p_it);	
			p_pt->RVal = fabs(p_pt->RVal2 - minRel) / itvlRel;
		}
		printf("Normalize pattern's reliability...(%f, %f)\n", minRel, maxRel);
	}	
	else
	{
		/// Keep the original reliability
		for(p_it = patterns.begin(); p_it != patterns.end(); ++p_it)
		{
			HKCPattern* p_pt = (*p_it);	
			p_pt->RVal = p_pt->RVal2;
		}
	}

	return true;
}
/// Analyze the optimized result
void HKCOptimizer::Analyze(HKCAppItem^ _appItem)
{
	if(!_appItem) return;

	/// Get data ready		
	HKCQRCData& qrcData = _appItem->Data->QRCData;	
	HKCPDBData& pdbData = _appItem->Data->PDBData;		
	VecRSB& rsblocks = qrcData.RSBlocks;	
	VecPtrn& patterns = pdbData.Patterns;		

	/// Check if there are broken RS blocks
	printf("ECC=%d [", qrcData.ECC);		
	VecRSB::iterator r_it = rsblocks.begin(), r_end = rsblocks.end();
	for(int i = 0; r_it != r_end; ++r_it, ++i)
	{
		HKCRSBlock* r_pt = (*r_it);
		if(r_pt->Tag == -1) continue;

		int numErrCWs = 0;		/// Number of erroneous codewords		
		VecCW::iterator cw_it = r_pt->CodeWords.begin(), cw_end = r_pt->CodeWords.end(); 
		for(; cw_it != cw_end; ++cw_it)
		{	
			HKCCodeWord* cw_pt = (*cw_it);
			if(cw_pt->Tag == -1) continue;

			int numErrMds = 0;		/// Number of erroneous modules								
			VecMdu::iterator m_it = cw_pt->Modules.begin(), m_end = cw_pt->Modules.end();
			for(; m_it != m_end; ++m_it)
			{
				HKCModule* m_pt = (*m_it);
				if(m_pt->PID2 == -1) continue;

				HKCPattern* p_pt = patterns[m_pt->PID2];
				if(m_pt->QRC != p_pt->Tag) 
				{
					numErrMds++;				
					break;
				}
			}

			if(numErrMds != 0) numErrCWs++;			
		}		

		if(numErrCWs > qrcData.ECC)				
			printf(" RSB%d(X):%d", i, numErrCWs);
		else
			printf(" RSB%d(O):%d", i, numErrCWs);					
	}
	printf(" ]\n");	
}
/// Perform pattern assignment optimization using iterative constrained Graph-Cuts
bool HKCUGCOptmzr::Optimize(HKCAppItem^ _appItem)
{	
	if(!_appItem) return false;	

	/// Get data ready	
	HKCImgData& imgData = _appItem->Data->ImgData;	
	HKCQRCData& qrcData = _appItem->Data->QRCData;	
	HKCPDBData& pdbData = _appItem->Data->PDBData;

	VecRSB& rsblocks = qrcData.RSBlocks;
	GraphT& mdGraph = qrcData.MdGraph;	
	VecPtrn& patterns = pdbData.Patterns;
	Mat& simMap = pdbData.SimMap;	

	HKCOptmParam^ optmParam = _appItem->Param->Optimize;
	double nScale = optmParam->NScale; /// Numerical scale factor

	/// Initialize data for GCO
	typedef GCoptimizationGridGraph::EnergyTermType energyT;
	int num_sites = boost::num_vertices(mdGraph); 
	int num_labels = patterns.size(); 

	/// Create an energy function object
	EnergyFunc<SimEnrgyWithPenalty, RelEnrgyLinear> energyFunc(SimEnrgyWithPenalty(), RelEnrgyLinear(),	
		patterns, simMap, mdGraph);

	/// Set up the array for data costs
	/// dataCost is an array s.t. the data cost for pixel p and  label l is stored at dataArray[pixel*num_labels+l].
	energyT *dataCosts = new energyT[num_sites*num_labels];
	for(int i = 0; i < num_sites; ++i)
	{
		int shift = i*num_labels;
		for(int l = 0; l < num_labels; ++l)
			dataCosts[shift+l] = cv::saturate_cast<energyT>(energyFunc.DataCost(i, l, optmParam)*nScale);
	}	

	/// Set up the array for smooth costs
	/// V is an array of smoothness costs, such that V_pq(label1,label2)  is stored at V[label1+num_labels*label2]
	energyT *smoothCosts = new energyT[num_labels*num_labels];
	for(int y = 0; y < simMap.rows; ++y)
	{
		double* simPtr = simMap.ptr<double>(y);
		for(int x = y; x < simMap.cols; ++x)
		{						
			energyT simVal = cv::saturate_cast<energyT>(simPtr[x]*nScale);			
			smoothCosts[y+x*num_labels] = simVal;
			if(x != y) smoothCosts[x+y*num_labels] = simVal;			
		}
	}

	try
	{
		GCoptimizationGeneralGraph *gc = new GCoptimizationGeneralGraph(num_sites,num_labels);
		gc->setDataCost(dataCosts);
		gc->setSmoothCost(smoothCosts);

		/// Set up a neighborhood system	
		/// setNeighbors(SiteID s1, SiteID s2, EnergyTermType weight=1);
		/// Specifies neighbors individually. You must call this function exactly once  for any pair of 
		/// neighboring sites s1 and s2. That is if you call setNeighbors(s1,s2) then you should not call 
		/// setNeighbors(s2,s1).   If Vpq(l_p,l_q) = V(l_p,l_q)*w_pq, where V(l_p,l_q) is some function that
		/// depends only on the labels l_p,l_q, then specify w_pq by using: setNeighbors(p,q,w_pq). 
		GVIndexM gVIdxMap = boost::get(boost::vertex_index, mdGraph);
		GEIterT e_it, e_end;
		boost::tie(e_it, e_end) = boost::edges(mdGraph);	
		for(int i = 0; e_it != e_end; ++e_it, ++i)
		{		
			energyT eWeit = cv::saturate_cast<energyT>(energyFunc.EdgeWeight((*e_it), optmParam));									
			gc->setNeighbors(gVIdxMap[boost::source((*e_it), mdGraph)], gVIdxMap[boost::target((*e_it), mdGraph)], eWeit);			
		}

		printf("\nBefore optimization energy is %d\n",gc->compute_energy());
		int iterN = 0;
		GVElemntM gVelmtMap = boost::get(boost::vertex_element, mdGraph);
		while(1)
		{
			/// Run swap
			gc->swap(-1);

			/// Get the optimal result
			for(int i = 0; i < num_sites; ++i)
			{
				HKCModule* m_pt = gVelmtMap[i];
				m_pt->PID2 = gc->whatLabel(i);
			}	

			iterN++;
			printf("Iteration %d, ", iterN);

			/// Number of allowable error codewords per RS block
			int trgECWs = (optmParam->MaxECNum == -1) ? (int)((double)qrcData.ECC*0.49) : optmParam->MaxECNum;
			if(trgECWs == 0) break;

			/// For each RS block, pick one candidate codeword
			/// For each candidate codeword, release the penalty in the data cost term
			printf("ECC=%d [", qrcData.ECC);	
			VecCW candiCWs; /// Candidate codewords
			VecRSB::iterator r_it = rsblocks.begin(), r_end = rsblocks.end();
			for(int i = 0; r_it != r_end; ++r_it, ++i)
			{
				HKCRSBlock* r_pt = (*r_it);
				if(r_pt->Tag == -1) continue;
				
				VecCW errCWs, okCWs;
				VecCW::iterator cw_it = r_pt->CodeWords.begin(), cw_end = r_pt->CodeWords.end(); 
				for(; cw_it != cw_end; ++cw_it)
				{	
					HKCCodeWord* cw_pt = (*cw_it);
					if(cw_pt->Tag == -1) continue;

					int numErrMds = 0;		/// Number of erroneous modules					
					//int numUnlockMds = 0;	/// How many modules are benefited from releasing the data cost penalty? 
					VecMdu::iterator m_it = cw_pt->Modules.begin(), m_end = cw_pt->Modules.end();
					for(; m_it != m_end; ++m_it)
					{
						HKCModule* m_pt = (*m_it);
						if(m_pt->PID2 == -1) continue;

						HKCPattern* p_pt = patterns[m_pt->PID2];
						if(m_pt->QRC != p_pt->Tag)
							numErrMds++;

						/*HKCPattern* p2_pt = patterns[m_pt->PID1];
						if(m_pt->QRC != p2_pt->Tag)
							numUnlockMds++;*/
					}

					if(numErrMds != 0) errCWs.push_back(cw_pt);					
					else if(cw_pt->Priority != -1)
					{
						//double w = 0.3;
						//cw_pt->Priority = w*cw_pt->Weit + (1.0-w)*((double)numUnlockMds/8.0);	
						cw_pt->Priority = cw_pt->Weit;	
						okCWs.push_back(cw_pt);
					}					
				}		
				
				if((int)errCWs.size() > qrcData.ECC)				
					printf(" RSB%d(X):%d", i, errCWs.size());
				else
					printf(" RSB%d(O):%d", i, errCWs.size());

				if((int)errCWs.size() < trgECWs)				
				{
					std::sort(okCWs.begin(), okCWs.end(), HKCCodeWord::Priority_GreatThan());
					candiCWs.push_back(okCWs[0]);					
				}				
			}
			printf(" ]\n");

			if(candiCWs.empty()) break;

			/// Update the data costs
			VecCW::iterator cw_it = candiCWs.begin(), cw_end = candiCWs.end(); 
			for(; cw_it != cw_end; ++cw_it)
			{	
				HKCCodeWord* cw_pt = (*cw_it);
				cw_pt->Priority = -1;

				VecMdu::iterator m_it = cw_pt->Modules.begin(), m_end = cw_pt->Modules.end();
				for(; m_it != m_end; ++m_it)
				{
					HKCModule* m_pt = (*m_it);
					if(m_pt->PID2 == -1) continue;

					int vIdx = m_pt->VID;
					int shift = vIdx*num_labels;
					for(int l = 0; l < num_labels; ++l)
					{
						if(m_pt->QRC != patterns[l]->Tag)							
							dataCosts[shift+l] = cv::saturate_cast<energyT>(energyFunc.DataCostNoPenalty(vIdx, l, optmParam)*nScale);							
					}
				}			
			}
		}

		printf("After optimization energy is %d\n",gc->compute_energy());

		delete gc;
	}
	catch (GCException e)
	{
		e.Report();
	}	

	delete [] dataCosts;	dataCosts = NULL;
	delete [] smoothCosts;	smoothCosts = NULL;

	return true;

}
/// Perform pattern assignment optimization using nearest-neighbor approach
/// This approach find the most similar pattern without breaking the original QR code at center location
bool HKCNNOptmzr::Optimize(HKCAppItem^ _appItem)
{
	if(!_appItem) return false;	

	/// Get data ready	
	HKCImgData& imgData = _appItem->Data->ImgData;	
	HKCQRCData& qrcData = _appItem->Data->QRCData;	
	HKCPDBData& pdbData = _appItem->Data->PDBData;		

	VecRSB& rsblocks = qrcData.RSBlocks;
	GraphT& mdGraph = qrcData.MdGraph;		
	VecPtrn& patterns = pdbData.Patterns;
	Mat& simMap = pdbData.SimMap;			

	/// For each module, find the closest pattern with the same center color as
	/// original QR code	
	/// Optimal PIDs	
	int gNumV = boost::num_vertices(mdGraph);
	GVElemntM gVelmtMap = boost::get(boost::vertex_element, mdGraph);	
	GVIterT m_it, m_end;
	boost::tie(m_it, m_end) = boost::vertices(mdGraph);		
	for(int i = 0; m_it != m_end; ++m_it, ++i)
	{
		HKCModule* m_pt = gVelmtMap[(*m_it)];
		VecPtrn& ptrnPool = (m_pt->QRC == 1) ? pdbData.Blacks : pdbData.Whites;

		double simVal, simMin = 1.0e9;
		int pID = -1;
		VecPtrn::iterator p_it = ptrnPool.begin();
		VecPtrn::iterator p_end = ptrnPool.end();
		for(; p_it != p_end; ++p_it)
		{
			HKCPattern* p_pt = (*p_it);
			if(m_pt->QRC != p_pt->Tag) cout << "Wrong!!!" << endl;
			simVal = simMap.at<double>(m_pt->PID1, p_pt->ID);
			if(simVal < simMin)
			{
				simMin = simVal;
				pID = p_pt->ID;
			}
		}

		m_pt->PID2 = pID;

		/// Show progress...
		printf("Pattern assignment (NN1)...%3d%% \r", (int)(100*(float(i)/float(gNumV))));			
	}
	/// Show progress...
	printf("Pattern assignment (NN1)...done\n");	

	return true;
}