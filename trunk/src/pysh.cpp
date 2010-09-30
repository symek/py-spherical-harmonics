#include <iostream>
#include <vector>
#include <math.h>
#include "pysh.h"
using namespace std;

vector<float> filterSH(vector <float> pixels)
{
	int width = sqrt(pixels.size()/3);
	cout << "Image width: " << width << endl;

	vector<vector<vector<float> > > hdr;

  	hdr.resize(width);
  	for (int i = 0; i < width; ++i) {
    	hdr[i].resize(width);
    	for (int j = 0; j < width; ++j) {
			hdr[i][j].resize(3);
			for (int k = 0; k < 3; k++) {
				hdr[i][j][k] = pixels[i+j+k];
			}
      	}
	}

	for (int l = 0; l < 100; l++)
	cout << hdr[l][0][0] << ": " << pixels[l] << endl;

	return pixels;
}

