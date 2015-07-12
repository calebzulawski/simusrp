#include "manager.h"

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME  simusrp_rx

#include "simstruc.h" //SimStruct

static void mdlInitializeSizes(SimStruct *S)
{
    // No expected parameters
    ssSetNumSFcnParams(S, 0);

    // Parameter mismatch will be reported by Simulink
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return;
    }

    // Specify I/O
    if (!ssSetNumInputPorts(S, 0)) return;
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    if (!ssSetNumOutputPorts(S,1)) return;

    ssSetNumSampleTimes(S, 1); // Might need to change to PORT_BASED_SAMPLE_TIMES

    //Store manager in PWork vector
    ssSetNumPWork(S, 1);

    ssSetSimStateCompliance(S, USE_CUSTOM_SIM_STATE);

    ssSetOptions(S,
                 SS_OPTION_EXCEPTION_FREE_CODE);

}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S); 
}

#define MDL_START
static void mdlStart(SimStruct *S)
{
    // Init manager and store in Pwork
    auto mgr  = new Manager();
    ssGetPWork(S)[0] = mgr;
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
    // Retrieve manager from PWork vector
    auto mgr = static_cast<Manager*>(ssGetPWork(S)[0]);
    
    // Get data addresses of input
    InputPtrsType inputs = ssGetInputPortSignalPtrs(S,0);
}

static void mdlTerminate(SimStruct *S)
{
    // Retrieve and destroy C++ object
    auto mgr = static_cast<Manager*>(ssGetPWork(S)[0]);
    delete mgr;
}


// Required S-function trailer
#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
