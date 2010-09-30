/* sh.i */
%module pysh

/* Vector type */
%include "std_vector.i"

namespace std {
   %template(vectori) vector<int>;
   %template(vectord) vector<double>;
   %template(vectorf) vector<float>;
};


%{
/* Put header files here or function declarations like below */

#include "pysh.h"

%}

%include "pysh.h"

