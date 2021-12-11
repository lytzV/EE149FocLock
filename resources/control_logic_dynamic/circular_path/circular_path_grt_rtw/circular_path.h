/*
 * circular_path.h
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

#ifndef RTW_HEADER_circular_path_h_
#define RTW_HEADER_circular_path_h_
#include <float.h>
#include <string.h>
#include <stddef.h>
#ifndef circular_path_COMMON_INCLUDES_
#define circular_path_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* circular_path_COMMON_INCLUDES_ */

#include "circular_path_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Real-time Model Data Structure */
struct tag_RTM_circular_path_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Model entry point functions */
extern void circular_path_initialize(void);
extern void circular_path_step(void);
extern void circular_path_terminate(void);

/* Real-time Model object */
extern RT_MODEL_circular_path_T *const circular_path_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'circular_path'
 * '<S1>'   : 'circular_path/Encoder'
 * '<S2>'   : 'circular_path/Motor'
 * '<S3>'   : 'circular_path/Motor1'
 * '<S4>'   : 'circular_path/PID Controller'
 * '<S5>'   : 'circular_path/PID Controller1'
 * '<S6>'   : 'circular_path/To wlwr'
 * '<S7>'   : 'circular_path/Motor/Motor'
 * '<S8>'   : 'circular_path/Motor/Radians to Degrees'
 * '<S9>'   : 'circular_path/Motor/Motor/Input Delay'
 * '<S10>'  : 'circular_path/Motor/Motor/Output Delay'
 * '<S11>'  : 'circular_path/Motor1/Motor'
 * '<S12>'  : 'circular_path/Motor1/Radians to Degrees'
 * '<S13>'  : 'circular_path/Motor1/Motor/Input Delay'
 * '<S14>'  : 'circular_path/Motor1/Motor/Output Delay'
 * '<S15>'  : 'circular_path/PID Controller/Anti-windup'
 * '<S16>'  : 'circular_path/PID Controller/D Gain'
 * '<S17>'  : 'circular_path/PID Controller/Filter'
 * '<S18>'  : 'circular_path/PID Controller/Filter ICs'
 * '<S19>'  : 'circular_path/PID Controller/I Gain'
 * '<S20>'  : 'circular_path/PID Controller/Ideal P Gain'
 * '<S21>'  : 'circular_path/PID Controller/Ideal P Gain Fdbk'
 * '<S22>'  : 'circular_path/PID Controller/Integrator'
 * '<S23>'  : 'circular_path/PID Controller/Integrator ICs'
 * '<S24>'  : 'circular_path/PID Controller/N Copy'
 * '<S25>'  : 'circular_path/PID Controller/N Gain'
 * '<S26>'  : 'circular_path/PID Controller/P Copy'
 * '<S27>'  : 'circular_path/PID Controller/Parallel P Gain'
 * '<S28>'  : 'circular_path/PID Controller/Reset Signal'
 * '<S29>'  : 'circular_path/PID Controller/Saturation'
 * '<S30>'  : 'circular_path/PID Controller/Saturation Fdbk'
 * '<S31>'  : 'circular_path/PID Controller/Sum'
 * '<S32>'  : 'circular_path/PID Controller/Sum Fdbk'
 * '<S33>'  : 'circular_path/PID Controller/Tracking Mode'
 * '<S34>'  : 'circular_path/PID Controller/Tracking Mode Sum'
 * '<S35>'  : 'circular_path/PID Controller/Tsamp - Integral'
 * '<S36>'  : 'circular_path/PID Controller/Tsamp - Ngain'
 * '<S37>'  : 'circular_path/PID Controller/postSat Signal'
 * '<S38>'  : 'circular_path/PID Controller/preSat Signal'
 * '<S39>'  : 'circular_path/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S40>'  : 'circular_path/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S41>'  : 'circular_path/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S42>'  : 'circular_path/PID Controller/D Gain/Internal Parameters'
 * '<S43>'  : 'circular_path/PID Controller/Filter/Differentiator'
 * '<S44>'  : 'circular_path/PID Controller/Filter/Differentiator/Tsamp'
 * '<S45>'  : 'circular_path/PID Controller/Filter/Differentiator/Tsamp/Internal Ts'
 * '<S46>'  : 'circular_path/PID Controller/Filter ICs/Internal IC - Differentiator'
 * '<S47>'  : 'circular_path/PID Controller/I Gain/Internal Parameters'
 * '<S48>'  : 'circular_path/PID Controller/Ideal P Gain/Passthrough'
 * '<S49>'  : 'circular_path/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S50>'  : 'circular_path/PID Controller/Integrator/Discrete'
 * '<S51>'  : 'circular_path/PID Controller/Integrator ICs/Internal IC'
 * '<S52>'  : 'circular_path/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S53>'  : 'circular_path/PID Controller/N Gain/Passthrough'
 * '<S54>'  : 'circular_path/PID Controller/P Copy/Disabled'
 * '<S55>'  : 'circular_path/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S56>'  : 'circular_path/PID Controller/Reset Signal/Disabled'
 * '<S57>'  : 'circular_path/PID Controller/Saturation/Enabled'
 * '<S58>'  : 'circular_path/PID Controller/Saturation Fdbk/Disabled'
 * '<S59>'  : 'circular_path/PID Controller/Sum/Sum_PID'
 * '<S60>'  : 'circular_path/PID Controller/Sum Fdbk/Disabled'
 * '<S61>'  : 'circular_path/PID Controller/Tracking Mode/Disabled'
 * '<S62>'  : 'circular_path/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S63>'  : 'circular_path/PID Controller/Tsamp - Integral/Passthrough'
 * '<S64>'  : 'circular_path/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S65>'  : 'circular_path/PID Controller/postSat Signal/Forward_Path'
 * '<S66>'  : 'circular_path/PID Controller/preSat Signal/Forward_Path'
 * '<S67>'  : 'circular_path/PID Controller1/Anti-windup'
 * '<S68>'  : 'circular_path/PID Controller1/D Gain'
 * '<S69>'  : 'circular_path/PID Controller1/Filter'
 * '<S70>'  : 'circular_path/PID Controller1/Filter ICs'
 * '<S71>'  : 'circular_path/PID Controller1/I Gain'
 * '<S72>'  : 'circular_path/PID Controller1/Ideal P Gain'
 * '<S73>'  : 'circular_path/PID Controller1/Ideal P Gain Fdbk'
 * '<S74>'  : 'circular_path/PID Controller1/Integrator'
 * '<S75>'  : 'circular_path/PID Controller1/Integrator ICs'
 * '<S76>'  : 'circular_path/PID Controller1/N Copy'
 * '<S77>'  : 'circular_path/PID Controller1/N Gain'
 * '<S78>'  : 'circular_path/PID Controller1/P Copy'
 * '<S79>'  : 'circular_path/PID Controller1/Parallel P Gain'
 * '<S80>'  : 'circular_path/PID Controller1/Reset Signal'
 * '<S81>'  : 'circular_path/PID Controller1/Saturation'
 * '<S82>'  : 'circular_path/PID Controller1/Saturation Fdbk'
 * '<S83>'  : 'circular_path/PID Controller1/Sum'
 * '<S84>'  : 'circular_path/PID Controller1/Sum Fdbk'
 * '<S85>'  : 'circular_path/PID Controller1/Tracking Mode'
 * '<S86>'  : 'circular_path/PID Controller1/Tracking Mode Sum'
 * '<S87>'  : 'circular_path/PID Controller1/Tsamp - Integral'
 * '<S88>'  : 'circular_path/PID Controller1/Tsamp - Ngain'
 * '<S89>'  : 'circular_path/PID Controller1/postSat Signal'
 * '<S90>'  : 'circular_path/PID Controller1/preSat Signal'
 * '<S91>'  : 'circular_path/PID Controller1/Anti-windup/Passthrough'
 * '<S92>'  : 'circular_path/PID Controller1/D Gain/Internal Parameters'
 * '<S93>'  : 'circular_path/PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S94>'  : 'circular_path/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S95>'  : 'circular_path/PID Controller1/I Gain/Internal Parameters'
 * '<S96>'  : 'circular_path/PID Controller1/Ideal P Gain/Passthrough'
 * '<S97>'  : 'circular_path/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S98>'  : 'circular_path/PID Controller1/Integrator/Discrete'
 * '<S99>'  : 'circular_path/PID Controller1/Integrator ICs/Internal IC'
 * '<S100>' : 'circular_path/PID Controller1/N Copy/Disabled'
 * '<S101>' : 'circular_path/PID Controller1/N Gain/Internal Parameters'
 * '<S102>' : 'circular_path/PID Controller1/P Copy/Disabled'
 * '<S103>' : 'circular_path/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S104>' : 'circular_path/PID Controller1/Reset Signal/Disabled'
 * '<S105>' : 'circular_path/PID Controller1/Saturation/Passthrough'
 * '<S106>' : 'circular_path/PID Controller1/Saturation Fdbk/Disabled'
 * '<S107>' : 'circular_path/PID Controller1/Sum/Sum_PID'
 * '<S108>' : 'circular_path/PID Controller1/Sum Fdbk/Disabled'
 * '<S109>' : 'circular_path/PID Controller1/Tracking Mode/Disabled'
 * '<S110>' : 'circular_path/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S111>' : 'circular_path/PID Controller1/Tsamp - Integral/Passthrough'
 * '<S112>' : 'circular_path/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S113>' : 'circular_path/PID Controller1/postSat Signal/Forward_Path'
 * '<S114>' : 'circular_path/PID Controller1/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_circular_path_h_ */
