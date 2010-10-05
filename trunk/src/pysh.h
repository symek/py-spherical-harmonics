#include <vector>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "rgbe.h"
using namespace std;


class Probe {
    public:
        // Constructor initializes probe's vector (x*y*3channels).
        // This is slow when called from python (~10s for 2k*2k)
        // TODO: check if float[] would perform faster
        // (though we like one-dim vector<> for transparent conversion Python<->C++)
        Probe(vector<float>);
        Probe(void);

        // Deconstructor deletes private fields: probe, matrices, coeffs.
        ~Probe();

        //Load pixels from hdr
        int load(const char * filename);

        // Get image's pixels stored inside a class.
        vector <float>   getProbe(void);

        // Gets reference to the image stored inside a class.
        // (much faster from within Python)
        vector <float> * getProbeRef(void);

        // Gets vector of coefficients: 9x3
        vector <float>   getCoeffs(void);

        // Gets vector of matrices: 16x3
        vector <float>   getMatrix(void);

        // Performs actual computation on the image probe.
        void             prefilter(void);


    private:
        // Allocates pixel's vector (probe).
        // This will suit better in case we will load probes internally.
        // For a moment it's rather pointless.
        void  allocateProbe(int);

        // internal stuff:
        float sinc(float);
        void  updateCoeffs(int, int, float, float, float, float);
        void  buildMatrix(void);

        // width of a square image probe.
        int           width;

        // Probe vector.
        vector<float> probe;

        // Coefficients and matrices vectors.
        vector<float> coeffs;
        vector<float> matrices;


};


