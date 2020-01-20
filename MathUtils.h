#pragma once
#ifndef INC_MATHUTILS_H
#define INC_MATHUTILS_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <numeric>
#include <execution>
#include <algorithm> 
#include <iomanip>

static int mulInv(int a, int b) {
	int b0 = b;
	int x0 = 0;
	int x1 = 1;

	if (b == 1) {
		return 1;
	}

	while (a > 1) {
		int q = a / b;
		int amb = a % b;
		a = b;
		b = amb;

		int xqx = x1 - q * x0;
		x1 = x0;
		x0 = xqx;
	}

	if (x1 < 0) {
		x1 += b0;
	}

	return x1;
}
static std::vector<double> linspace(double min, double max, int n)
{
	std::vector<double> result;
	// vector iterator
	int iterator = 0;

	for (int i = 0; i <= n - 2; i++)
	{
		//double temp = min + i * (max - min) / (floor((double)n) - 1);default code
		double temp = sin(min + i * (max - min) / (floor((double)n) - 1));
		result.push_back(temp);
		//result.insert(result.begin() + iterator, temp);
		iterator += 1;
	}

	//iterator += 1;defaul code
	result.push_back(sin(max));

	//result.insert(result.begin() + iterator, max);default code

	////print
	/*for (std::vector<double>::iterator it = result.begin(); it != result.end(); ++it)
		std::cout << *it << std::endl;
	std::cout << '\n';*/
	///////

	return result;
}

static double interpolate(std::vector<double> &xData, std::vector<double> &yData, double x, bool extrapolate){
//   Returns interpolated value at x from parallel arrays ( xData, yData )
//   Assumes that xData has at least two elements, is sorted and is strictly monotonic increasing
//   boolean argument extrapolate determines behaviour beyond ends of array (if needed)
	int size = xData.size();

	int i = 0;                                                                  // find left end of interval for interpolation
	
	double xL = xData[i], 
		yL = yData[i], 
		xR = xData[i + 1], 
		yR = yData[i + 1];      // points on either side (unless beyond ends)
	if (!extrapolate)                                                         // if beyond ends of array and not extrapolating
	{
		if (x < xL) yR = yL;
		if (x > xR) yL = yR;
	}

	double dydx = (yR - yL) / (xR - xL);                                    // gradient

	return yL + dydx * (x - xL);                                              // linear interpolation
}

#endif