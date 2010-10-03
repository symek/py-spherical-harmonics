/*
    Most of this code comes from a well know paper by Ravi Ramamoorthi and Pat Hanrahan:
    http://graphics.stanford.edu/papers/envmap. It was trivally rewritten in C++.

    Reference: This is an implementation of the method described by
               Ravi Ramamoorthi and Pat Hanrahan in their SIGGRAPH 2001
	           paper, "An Efficient Representation for Irradiance
	           Environment Maps".

    Author   : Ravi Ramamoorthi
*/
#include <iostream>
#include <vector>
#include <math.h>
#include "pysh.h"
#define PI 3.1415926535897931
using namespace std;

Probe::Probe(vector<float> pixels) {
    // This is more like a placeholder for now.
    // The whole initialization needs rethinking.
    // Storage could be external optionally copied internally,
    // loaded from a file or passed by reference etc.
    allocateProbe(pixels.size());
    probe = pixels;
    coeffs.resize(9*3);
    matrices.resize(16*3);
    width = sqrt(probe.size()/3);
    }

Probe::~Probe(){
    probe.clear();
    coeffs.clear();
    matrices.clear();
    }

void Probe::allocateProbe(int width) {
    probe.resize(width);
    }

vector<float> Probe::getProbe() {
    return probe;
    }

vector<float> * Probe::getProbeRef() {
    return &probe;
    }

vector<float> Probe::getCoeffs() {
    return coeffs;
    }

vector<float> Probe::getMatrix() {
    /* Lazy compute matrices from coefficents */
    buildMatrix();
    return matrices;
    }

float Probe::sinc(float x){
    if (fabs(x) < 1.0e-4) return 1.0;
    else return(sin(x)/x);
    }

void Probe::prefilter() {

    float u, v, r, theta, phi, x, y, z, domega;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            v = (width/2.0 - i)/(width/2.0);
            u = (j-width/2.0)/(width/2.0);
            r = sqrt(u*u+v*v);
            if (r > 1.0) continue;

            theta = PI*r;
            phi = atan2(v, u);

            x = sin(theta)*cos(phi);
            y = sin(theta)*sin(phi);
            z = cos(theta);
            domega = (2*PI/width)*(2*PI/width)*sinc(theta);

            updateCoeffs(i, j, domega, x, y, z);

        }
    }
}


void Probe::updateCoeffs(int i, int j, float domega, float x, float y, float z) {

    //Row and column:
    int xy = (i*width*3)+(j*3);


    float c;
    for (int col = 0; col < 3; col++) {

        c = 0.282095;
        coeffs[0+(9*col)]  += probe[xy+col]*c*domega;

        c = 0.488603;
        coeffs[1+(9*col)]  += probe[xy+col]*(c*y)*domega;
        coeffs[2+(9*col)]  += probe[xy+col]*(c*z)*domega;
        coeffs[3+(9*col)]  += probe[xy+col]*(c*x)*domega;

        c = 1.092548;
        coeffs[4+(9*col)]  += probe[xy+col]*(c*x*y)*domega;
        coeffs[5+(9*col)]  += probe[xy+col]*(c*y*z)*domega;
        coeffs[7+(9*col)]  += probe[xy+col]*(c*x*z)*domega;

        c = 0.315392 ;
        coeffs[6+(9*col)]  += probe[xy+col]*(c*(3*z*z-1))*domega;

        c = 0.546274 ;
        coeffs[8+(9*col)]  += probe[xy+col]*(c*(x*x-y*y))*domega;
    }
}

void Probe::buildMatrix(void) {

  int col ;
  float c1,c2,c3,c4,c5;
  c1 = 0.429043 ; c2 = 0.511664 ;
  c3 = 0.743125 ; c4 = 0.886227 ; c5 = 0.247708 ;

  for (col = 0 ; col < 3 ; col++) {

    matrices[0+(16*col)] = c1*coeffs[8+(9*col)];
    matrices[1+(16*col)] = c1*coeffs[4+(9*col)];
    matrices[2+(16*col)] = c1*coeffs[7+(9*col)];
    matrices[3+(16*col)] = c2*coeffs[3+(9*col)];
    matrices[4+(16*col)] = c1*coeffs[4+(9*col)];
    matrices[5+(16*col)] = -c1*coeffs[8+(9*col)];
    matrices[6+(16*col)] = c1*coeffs[5+(9*col)];
    matrices[7+(16*col)] = c2*coeffs[1+(9*col)];
    matrices[8+(16*col)] = c1*coeffs[7+(9*col)];
    matrices[9+(16*col)] = c1*coeffs[5+(9*col)];
    matrices[10+(16*col)] = c3*coeffs[6+(9*col)];
    matrices[11+(16*col)] = c2*coeffs[2+(9*col)];
    matrices[12+(16*col)] = c2*coeffs[3+(9*col)];
    matrices[13+(16*col)] = c2*coeffs[1+(9*col)];
    matrices[14+(16*col)] = c2*coeffs[2+(9*col)];
    matrices[15+(16*col)] = c4*coeffs[0+(9*col)] - c5*coeffs[6+(9*col)];
  }
}
