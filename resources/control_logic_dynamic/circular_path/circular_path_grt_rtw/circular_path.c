/*
 * circular_path.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "circular_path".
 *
 * Model version              : 1.3
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Sat Dec  4 22:59:35 2021
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "circular_path.h"
#include "circular_path_private.h"

/* Real-time model */
static RT_MODEL_circular_path_T circular_path_M_;
RT_MODEL_circular_path_T *const circular_path_M = &circular_path_M_;

/* Model step function */
void circular_path_step(void)
{
  /* Matfile logging */
  rt_UpdateTXYLogVars(circular_path_M->rtwLogInfo,
                      (&circular_path_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.01s, 0.0s] */
    if ((rtmGetTFinal(circular_path_M)!=-1) &&
        !((rtmGetTFinal(circular_path_M)-circular_path_M->Timing.taskTime0) >
          circular_path_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(circular_path_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++circular_path_M->Timing.clockTick0)) {
    ++circular_path_M->Timing.clockTickH0;
  }

  circular_path_M->Timing.taskTime0 = circular_path_M->Timing.clockTick0 *
    circular_path_M->Timing.stepSize0 + circular_path_M->Timing.clockTickH0 *
    circular_path_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void circular_path_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)circular_path_M, 0,
                sizeof(RT_MODEL_circular_path_T));
  rtmSetTFinal(circular_path_M, 5.0);
  circular_path_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    circular_path_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(circular_path_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(circular_path_M->rtwLogInfo, (NULL));
    rtliSetLogT(circular_path_M->rtwLogInfo, "tout");
    rtliSetLogX(circular_path_M->rtwLogInfo, "");
    rtliSetLogXFinal(circular_path_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(circular_path_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(circular_path_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(circular_path_M->rtwLogInfo, 0);
    rtliSetLogDecimation(circular_path_M->rtwLogInfo, 1);
    rtliSetLogY(circular_path_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(circular_path_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(circular_path_M->rtwLogInfo, (NULL));
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(circular_path_M->rtwLogInfo, 0.0,
    rtmGetTFinal(circular_path_M), circular_path_M->Timing.stepSize0,
    (&rtmGetErrorStatus(circular_path_M)));
}

/* Model terminate function */
void circular_path_terminate(void)
{
  /* (no terminate code required) */
}
