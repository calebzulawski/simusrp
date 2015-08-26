#include "mex.h"
#include "matrix.h"
#include "handler.h"
#include "rx.h"
#include "cstring"

#define NRHS_CHECK(n) \
    if ( nrhs != n ) { \
        char *error; \
        sprintf(error, "Expected %d input arguments.  Provided %d.", n, nrhs); \
        mexErrMsgTxt(error); \
    };

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    char *pOption = mxArrayToString( prhs[0] );
    if ( pOption )
    {
        std::string option = pOption;
        if ( option == "newRx" )
        {
            createMxArray(plhs[0], 1);
            createMxArray(plhs[1], reinterpret_cast<long int>( new usrplib::Rx() ));
        } else {
            char *error;
            sprintf(error, "Unrecognized option: %s", pOption);
        }
    } else {
        mexErrMsgTxt("Invalid option type! Must be a string.");
    }
}

inline void createMxArray(mxArray *m_, long int n_)
{
    m_ = mxCreateDoubleMatrix(1, 1, mxREAL);
    double n = n_;
    std::memcpy(mxGetPr(m_), &n, sizeof(double));
}
