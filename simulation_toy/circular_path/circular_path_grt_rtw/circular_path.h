/*
 * circular_path.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "circular_path".
 *
 * Model version              : 1.2
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Fri Dec  3 10:37:35 2021
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_circular_path_h_
#define RTW_HEADER_circular_path_h_
#include <stddef.h>
#include <string.h>
#include <float.h>
#include <math.h>
#ifndef circular_path_COMMON_INCLUDES_
#define circular_path_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#endif                                 /* circular_path_COMMON_INCLUDES_ */

#include "circular_path_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetSampleHitArray
#define rtmGetSampleHitArray(rtm)      ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmGetStepSize
#define rtmGetStepSize(rtm)            ((rtm)->Timing.stepSize)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
#define rtmGet_TimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
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
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

#ifndef rtmGetTimeOfLastOutput
#define rtmGetTimeOfLastOutput(rtm)    ((rtm)->Timing.timeOfLastOutput)
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S6>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<S6>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator2_DSTATE;/* '<S6>/Discrete-Time Integrator2' */
  real_T DiscreteTimeIntegrator_DSTATE_p;/* '<S2>/Discrete-Time Integrator' */
  real_T Internal_DSTATE[3];           /* '<S8>/Internal' */
  real_T DiscreteTimeIntegrator_DSTATE_n;/* '<S3>/Discrete-Time Integrator' */
  real_T Internal_DSTATE_l[3];         /* '<S12>/Internal' */
  real_T DiscreteTimeIntegrator_DSTATE_k;/* '<S1>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1_DSTAT_n;/* '<S1>/Discrete-Time Integrator1' */
  real_T Integrator_DSTATE;            /* '<S99>/Integrator' */
  real_T Filter_DSTATE;                /* '<S94>/Filter' */
  real_T Integrator_DSTATE_p;          /* '<S51>/Integrator' */
  real_T UD_DSTATE;                    /* '<S44>/UD' */
  real_T SoftRealTime_RWORK;           /* '<S6>/Soft Real Time' */
} DW_circular_path_T;

/* Parameters (default storage) */
struct P_circular_path_T_ {
  real_T axleLength;                   /* Variable: axleLength
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T lineLength;                   /* Variable: lineLength
                                        * Referenced by: '<S6>/Constant'
                                        */
  real_T motorIp[255];                 /* Variable: motorIp
                                        * Referenced by:
                                        *   '<Root>/1-D Lookup Table'
                                        *   '<Root>/1-D Lookup Table1'
                                        */
  real_T motorSp[255];                 /* Variable: motorSp
                                        * Referenced by:
                                        *   '<Root>/1-D Lookup Table'
                                        *   '<Root>/1-D Lookup Table1'
                                        */
  real_T ticksPerRot;                  /* Variable: ticksPerRot
                                        * Referenced by:
                                        *   '<Root>/Gain1'
                                        *   '<Root>/Gain9'
                                        *   '<S1>/Gain5'
                                        *   '<S1>/Gain6'
                                        */
  real_T wheelR;                       /* Variable: wheelR
                                        * Referenced by:
                                        *   '<Root>/Gain1'
                                        *   '<Root>/Gain9'
                                        *   '<S7>/vtow'
                                        */
  real_T PIDController1_D;             /* Mask Parameter: PIDController1_D
                                        * Referenced by: '<S93>/Derivative Gain'
                                        */
  real_T PIDController_D;              /* Mask Parameter: PIDController_D
                                        * Referenced by: '<S43>/Derivative Gain'
                                        */
  real_T PIDController_DifferentiatorICP;
                              /* Mask Parameter: PIDController_DifferentiatorICP
                               * Referenced by: '<S44>/UD'
                               */
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S48>/Integral Gain'
                                        */
  real_T PIDController1_I;             /* Mask Parameter: PIDController1_I
                                        * Referenced by: '<S96>/Integral Gain'
                                        */
  real_T PIDController1_InitialCondition;
                              /* Mask Parameter: PIDController1_InitialCondition
                               * Referenced by: '<S94>/Filter'
                               */
  real_T PIDController1_InitialConditi_m;
                              /* Mask Parameter: PIDController1_InitialConditi_m
                               * Referenced by: '<S99>/Integrator'
                               */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S51>/Integrator'
                               */
  real_T PIDController_LowerSaturationLi;
                              /* Mask Parameter: PIDController_LowerSaturationLi
                               * Referenced by:
                               *   '<S58>/Saturation'
                               *   '<S42>/DeadZone'
                               */
  real_T PIDController1_N;             /* Mask Parameter: PIDController1_N
                                        * Referenced by: '<S102>/Filter Coefficient'
                                        */
  real_T PIDController1_P;             /* Mask Parameter: PIDController1_P
                                        * Referenced by: '<S104>/Proportional Gain'
                                        */
  real_T PIDController_P;              /* Mask Parameter: PIDController_P
                                        * Referenced by: '<S56>/Proportional Gain'
                                        */
  real_T PIDController_UpperSaturationLi;
                              /* Mask Parameter: PIDController_UpperSaturationLi
                               * Referenced by:
                               *   '<S58>/Saturation'
                               *   '<S42>/DeadZone'
                               */
  real_T RobotSimulator_axleLength; /* Mask Parameter: RobotSimulator_axleLength
                                     * Referenced by: '<S6>/Wheel Spacing'
                                     */
  real_T Motor_sensorType;             /* Mask Parameter: Motor_sensorType
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Motor1_sensorType;            /* Mask Parameter: Motor1_sensorType
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T RobotSimulator_startTheta; /* Mask Parameter: RobotSimulator_startTheta
                                     * Referenced by: '<S6>/Discrete-Time Integrator2'
                                     */
  real_T RobotSimulator_startX;        /* Mask Parameter: RobotSimulator_startX
                                        * Referenced by: '<S6>/Discrete-Time Integrator'
                                        */
  real_T RobotSimulator_startY;        /* Mask Parameter: RobotSimulator_startY
                                        * Referenced by: '<S6>/Discrete-Time Integrator1'
                                        */
  real_T RobotSimulator_wheelR;        /* Mask Parameter: RobotSimulator_wheelR
                                        * Referenced by: '<S6>/Wheel Radius'
                                        */
  real_T Gain_Gain;                    /* Expression: 180/pi
                                        * Referenced by: '<S9>/Gain'
                                        */
  real_T Gain_Gain_p;                  /* Expression: 180/pi
                                        * Referenced by: '<S13>/Gain'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S40>/Constant1'
                                        */
  real_T DiscreteTimeIntegrator_gainval;
                           /* Computed Parameter: DiscreteTimeIntegrator_gainval
                            * Referenced by: '<S6>/Discrete-Time Integrator'
                            */
  real_T DiscreteTimeIntegrator1_gainval;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainval
                           * Referenced by: '<S6>/Discrete-Time Integrator1'
                           */
  real_T DiscreteTimeIntegrator2_gainval;
                          /* Computed Parameter: DiscreteTimeIntegrator2_gainval
                           * Referenced by: '<S6>/Discrete-Time Integrator2'
                           */
  real_T Circle_Value;                 /* Expression: 2*pi
                                        * Referenced by: '<S6>/Circle'
                                        */
  real_T DiscreteTimeIntegrator_gainva_d;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_d
                           * Referenced by: '<S2>/Discrete-Time Integrator'
                           */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: 0
                                        * Referenced by: '<S2>/Discrete-Time Integrator'
                                        */
  real_T Internal_A[9];                /* Computed Parameter: Internal_A
                                        * Referenced by: '<S8>/Internal'
                                        */
  real_T Internal_B[3];                /* Computed Parameter: Internal_B
                                        * Referenced by: '<S8>/Internal'
                                        */
  real_T Internal_C[3];                /* Computed Parameter: Internal_C
                                        * Referenced by: '<S8>/Internal'
                                        */
  real_T Switch_Threshold;             /* Expression: 1
                                        * Referenced by: '<S2>/Switch'
                                        */
  real_T DiscreteTimeIntegrator_gainva_o;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_o
                           * Referenced by: '<S3>/Discrete-Time Integrator'
                           */
  real_T DiscreteTimeIntegrator_IC_l;  /* Expression: 0
                                        * Referenced by: '<S3>/Discrete-Time Integrator'
                                        */
  real_T Internal_A_n[9];              /* Computed Parameter: Internal_A_n
                                        * Referenced by: '<S12>/Internal'
                                        */
  real_T Internal_B_b[3];              /* Computed Parameter: Internal_B_b
                                        * Referenced by: '<S12>/Internal'
                                        */
  real_T Internal_C_f[3];              /* Computed Parameter: Internal_C_f
                                        * Referenced by: '<S12>/Internal'
                                        */
  real_T Switch_Threshold_k;           /* Expression: 1
                                        * Referenced by: '<S3>/Switch'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1/2
                                        * Referenced by: '<S6>/Gain1'
                                        */
  real_T SoftRealTime_P1_Size[2];    /* Computed Parameter: SoftRealTime_P1_Size
                                      * Referenced by: '<S6>/Soft Real Time'
                                      */
  real_T SoftRealTime_P1;              /* Expression: x
                                        * Referenced by: '<S6>/Soft Real Time'
                                        */
  real_T Constant2_Value;              /* Expression: 0.02
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real_T DiscreteTimeIntegrator_gainva_l;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_l
                           * Referenced by: '<S1>/Discrete-Time Integrator'
                           */
  real_T DiscreteTimeIntegrator_IC_k;  /* Expression: 0
                                        * Referenced by: '<S1>/Discrete-Time Integrator'
                                        */
  real_T DiscreteTimeIntegrator1_gainv_b;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainv_b
                           * Referenced by: '<S1>/Discrete-Time Integrator1'
                           */
  real_T DiscreteTimeIntegrator1_IC;   /* Expression: 0
                                        * Referenced by: '<S1>/Discrete-Time Integrator1'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S99>/Integrator'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S94>/Filter'
                                        */
  real_T Constant1_Value_g;            /* Expression: 2
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Average_Gain;                 /* Expression: 0.5
                                        * Referenced by: '<Root>/Average'
                                        */
  real_T Integrator_gainval_c;       /* Computed Parameter: Integrator_gainval_c
                                      * Referenced by: '<S51>/Integrator'
                                      */
  real_T Tsamp_WtEt;                   /* Computed Parameter: Tsamp_WtEt
                                        * Referenced by: '<S46>/Tsamp'
                                        */
  real_T changeparameters_Gain[4];
                                /* Expression: [1 -axleLength/2; 1 axleLength/2]
                                 * Referenced by: '<S7>/change parameters'
                                 */
  real_T Gain2_Gain;                   /* Expression: (180/pi)
                                        * Referenced by: '<S1>/Gain2'
                                        */
  real_T Gain3_Gain;                   /* Expression: (180/pi)
                                        * Referenced by: '<S1>/Gain3'
                                        */
  real_T ZeroGain_Gain;                /* Expression: 0
                                        * Referenced by: '<S40>/ZeroGain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_circular_path_T {
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;

  /*
   * NonInlinedSFcns:
   * The following substructure contains information regarding
   * non-inlined s-functions used in the model.
   */
  struct {
    RTWSfcnInfo sfcnInfo;
    time_T *taskTimePtrs[2];
    SimStruct childSFunctions[1];
    SimStruct *childSFunctionPtrs[1];
    struct _ssBlkInfo2 blkInfo2[1];
    struct _ssSFcnModelMethods2 methods2[1];
    struct _ssSFcnModelMethods3 methods3[1];
    struct _ssSFcnModelMethods4 methods4[1];
    struct _ssStatesInfo2 statesInfo2[1];
    ssPeriodicStatesInfo periodicStatesInfo[1];
    struct _ssPortInfo2 inputOutputPortInfo2[1];
    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      uint_T attribs[1];
      mxArray *params[1];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn0;
  } NonInlinedSFcns;

  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T options;
    int_T numContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[2];
    time_T offsetTimesArray[2];
    int_T sampleTimeTaskIDArray[2];
    int_T sampleHitArray[2];
    int_T perTaskSampleHitsArray[4];
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_circular_path_T circular_path_P;

/* Block states (default storage) */
extern DW_circular_path_T circular_path_DW;

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
 * '<S6>'   : 'circular_path/Robot Simulator'
 * '<S7>'   : 'circular_path/To wlwr'
 * '<S8>'   : 'circular_path/Motor/Motor'
 * '<S9>'   : 'circular_path/Motor/Radians to Degrees'
 * '<S10>'  : 'circular_path/Motor/Motor/Input Delay'
 * '<S11>'  : 'circular_path/Motor/Motor/Output Delay'
 * '<S12>'  : 'circular_path/Motor1/Motor'
 * '<S13>'  : 'circular_path/Motor1/Radians to Degrees'
 * '<S14>'  : 'circular_path/Motor1/Motor/Input Delay'
 * '<S15>'  : 'circular_path/Motor1/Motor/Output Delay'
 * '<S16>'  : 'circular_path/PID Controller/Anti-windup'
 * '<S17>'  : 'circular_path/PID Controller/D Gain'
 * '<S18>'  : 'circular_path/PID Controller/Filter'
 * '<S19>'  : 'circular_path/PID Controller/Filter ICs'
 * '<S20>'  : 'circular_path/PID Controller/I Gain'
 * '<S21>'  : 'circular_path/PID Controller/Ideal P Gain'
 * '<S22>'  : 'circular_path/PID Controller/Ideal P Gain Fdbk'
 * '<S23>'  : 'circular_path/PID Controller/Integrator'
 * '<S24>'  : 'circular_path/PID Controller/Integrator ICs'
 * '<S25>'  : 'circular_path/PID Controller/N Copy'
 * '<S26>'  : 'circular_path/PID Controller/N Gain'
 * '<S27>'  : 'circular_path/PID Controller/P Copy'
 * '<S28>'  : 'circular_path/PID Controller/Parallel P Gain'
 * '<S29>'  : 'circular_path/PID Controller/Reset Signal'
 * '<S30>'  : 'circular_path/PID Controller/Saturation'
 * '<S31>'  : 'circular_path/PID Controller/Saturation Fdbk'
 * '<S32>'  : 'circular_path/PID Controller/Sum'
 * '<S33>'  : 'circular_path/PID Controller/Sum Fdbk'
 * '<S34>'  : 'circular_path/PID Controller/Tracking Mode'
 * '<S35>'  : 'circular_path/PID Controller/Tracking Mode Sum'
 * '<S36>'  : 'circular_path/PID Controller/Tsamp - Integral'
 * '<S37>'  : 'circular_path/PID Controller/Tsamp - Ngain'
 * '<S38>'  : 'circular_path/PID Controller/postSat Signal'
 * '<S39>'  : 'circular_path/PID Controller/preSat Signal'
 * '<S40>'  : 'circular_path/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S41>'  : 'circular_path/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S42>'  : 'circular_path/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S43>'  : 'circular_path/PID Controller/D Gain/Internal Parameters'
 * '<S44>'  : 'circular_path/PID Controller/Filter/Differentiator'
 * '<S45>'  : 'circular_path/PID Controller/Filter/Differentiator/Tsamp'
 * '<S46>'  : 'circular_path/PID Controller/Filter/Differentiator/Tsamp/Internal Ts'
 * '<S47>'  : 'circular_path/PID Controller/Filter ICs/Internal IC - Differentiator'
 * '<S48>'  : 'circular_path/PID Controller/I Gain/Internal Parameters'
 * '<S49>'  : 'circular_path/PID Controller/Ideal P Gain/Passthrough'
 * '<S50>'  : 'circular_path/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S51>'  : 'circular_path/PID Controller/Integrator/Discrete'
 * '<S52>'  : 'circular_path/PID Controller/Integrator ICs/Internal IC'
 * '<S53>'  : 'circular_path/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S54>'  : 'circular_path/PID Controller/N Gain/Passthrough'
 * '<S55>'  : 'circular_path/PID Controller/P Copy/Disabled'
 * '<S56>'  : 'circular_path/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S57>'  : 'circular_path/PID Controller/Reset Signal/Disabled'
 * '<S58>'  : 'circular_path/PID Controller/Saturation/Enabled'
 * '<S59>'  : 'circular_path/PID Controller/Saturation Fdbk/Disabled'
 * '<S60>'  : 'circular_path/PID Controller/Sum/Sum_PID'
 * '<S61>'  : 'circular_path/PID Controller/Sum Fdbk/Disabled'
 * '<S62>'  : 'circular_path/PID Controller/Tracking Mode/Disabled'
 * '<S63>'  : 'circular_path/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S64>'  : 'circular_path/PID Controller/Tsamp - Integral/Passthrough'
 * '<S65>'  : 'circular_path/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S66>'  : 'circular_path/PID Controller/postSat Signal/Forward_Path'
 * '<S67>'  : 'circular_path/PID Controller/preSat Signal/Forward_Path'
 * '<S68>'  : 'circular_path/PID Controller1/Anti-windup'
 * '<S69>'  : 'circular_path/PID Controller1/D Gain'
 * '<S70>'  : 'circular_path/PID Controller1/Filter'
 * '<S71>'  : 'circular_path/PID Controller1/Filter ICs'
 * '<S72>'  : 'circular_path/PID Controller1/I Gain'
 * '<S73>'  : 'circular_path/PID Controller1/Ideal P Gain'
 * '<S74>'  : 'circular_path/PID Controller1/Ideal P Gain Fdbk'
 * '<S75>'  : 'circular_path/PID Controller1/Integrator'
 * '<S76>'  : 'circular_path/PID Controller1/Integrator ICs'
 * '<S77>'  : 'circular_path/PID Controller1/N Copy'
 * '<S78>'  : 'circular_path/PID Controller1/N Gain'
 * '<S79>'  : 'circular_path/PID Controller1/P Copy'
 * '<S80>'  : 'circular_path/PID Controller1/Parallel P Gain'
 * '<S81>'  : 'circular_path/PID Controller1/Reset Signal'
 * '<S82>'  : 'circular_path/PID Controller1/Saturation'
 * '<S83>'  : 'circular_path/PID Controller1/Saturation Fdbk'
 * '<S84>'  : 'circular_path/PID Controller1/Sum'
 * '<S85>'  : 'circular_path/PID Controller1/Sum Fdbk'
 * '<S86>'  : 'circular_path/PID Controller1/Tracking Mode'
 * '<S87>'  : 'circular_path/PID Controller1/Tracking Mode Sum'
 * '<S88>'  : 'circular_path/PID Controller1/Tsamp - Integral'
 * '<S89>'  : 'circular_path/PID Controller1/Tsamp - Ngain'
 * '<S90>'  : 'circular_path/PID Controller1/postSat Signal'
 * '<S91>'  : 'circular_path/PID Controller1/preSat Signal'
 * '<S92>'  : 'circular_path/PID Controller1/Anti-windup/Passthrough'
 * '<S93>'  : 'circular_path/PID Controller1/D Gain/Internal Parameters'
 * '<S94>'  : 'circular_path/PID Controller1/Filter/Disc. Forward Euler Filter'
 * '<S95>'  : 'circular_path/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S96>'  : 'circular_path/PID Controller1/I Gain/Internal Parameters'
 * '<S97>'  : 'circular_path/PID Controller1/Ideal P Gain/Passthrough'
 * '<S98>'  : 'circular_path/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S99>'  : 'circular_path/PID Controller1/Integrator/Discrete'
 * '<S100>' : 'circular_path/PID Controller1/Integrator ICs/Internal IC'
 * '<S101>' : 'circular_path/PID Controller1/N Copy/Disabled'
 * '<S102>' : 'circular_path/PID Controller1/N Gain/Internal Parameters'
 * '<S103>' : 'circular_path/PID Controller1/P Copy/Disabled'
 * '<S104>' : 'circular_path/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S105>' : 'circular_path/PID Controller1/Reset Signal/Disabled'
 * '<S106>' : 'circular_path/PID Controller1/Saturation/Passthrough'
 * '<S107>' : 'circular_path/PID Controller1/Saturation Fdbk/Disabled'
 * '<S108>' : 'circular_path/PID Controller1/Sum/Sum_PID'
 * '<S109>' : 'circular_path/PID Controller1/Sum Fdbk/Disabled'
 * '<S110>' : 'circular_path/PID Controller1/Tracking Mode/Disabled'
 * '<S111>' : 'circular_path/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S112>' : 'circular_path/PID Controller1/Tsamp - Integral/Passthrough'
 * '<S113>' : 'circular_path/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S114>' : 'circular_path/PID Controller1/postSat Signal/Forward_Path'
 * '<S115>' : 'circular_path/PID Controller1/preSat Signal/Forward_Path'
 * '<S116>' : 'circular_path/Robot Simulator/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_circular_path_h_ */
