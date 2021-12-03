/*
 * circular_path.c
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

#include "circular_path.h"
#include "circular_path_private.h"

/* Block states (default storage) */
DW_circular_path_T circular_path_DW;

/* Real-time model */
static RT_MODEL_circular_path_T circular_path_M_;
RT_MODEL_circular_path_T *const circular_path_M = &circular_path_M_;
real_T look1_binlcpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = 1.0;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

/* Model step function */
void circular_path_step(void)
{
  /* local block i/o variables */
  real_T rtb_Internal;
  real_T rtb_Internal_g;
  real_T rtb_Product1;
  real_T rtb_Product2;
  real_T rtb_Product3;
  real_T rtb_FilterCoefficient;
  real_T rtb_Tsamp;
  real_T rtb_uDLookupTable;
  real_T rtb_uDLookupTable1;
  real_T rtb_Gain2;
  real_T rtb_Gain3;
  real_T rtb_Switch;
  real_T rtb_IntegralGain;
  real_T rtb_DiscreteTimeIntegrator_a;
  real_T rtb_IntegralGain_g;
  real_T rtb_Subtract2;
  real_T rtb_Sum;
  real_T rtb_Switch_a4;
  real_T rtb_Switch_p;
  real_T tmp;
  real_T tmp_0;

  /* DiscreteStateSpace: '<S8>/Internal' */
  {
    rtb_Internal = (circular_path_P.Internal_C[0])*
      circular_path_DW.Internal_DSTATE[0]
      + (circular_path_P.Internal_C[1])*circular_path_DW.Internal_DSTATE[1]
      + (circular_path_P.Internal_C[2])*circular_path_DW.Internal_DSTATE[2];
  }

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Constant'
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator'
   *  Gain: '<S9>/Gain'
   */
  if (circular_path_P.Motor_sensorType > circular_path_P.Switch_Threshold) {
    rtb_Switch_a4 = circular_path_P.Gain_Gain *
      circular_path_DW.DiscreteTimeIntegrator_DSTATE_p;
  } else {
    rtb_Switch_a4 = rtb_Internal;
  }

  /* End of Switch: '<S2>/Switch' */

  /* DiscreteStateSpace: '<S12>/Internal' */
  {
    rtb_Internal_g = (circular_path_P.Internal_C_f[0])*
      circular_path_DW.Internal_DSTATE_l[0]
      + (circular_path_P.Internal_C_f[1])*circular_path_DW.Internal_DSTATE_l[1]
      + (circular_path_P.Internal_C_f[2])*circular_path_DW.Internal_DSTATE_l[2];
  }

  /* Switch: '<S3>/Switch' incorporates:
   *  Constant: '<S3>/Constant'
   *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator'
   *  Gain: '<S13>/Gain'
   */
  if (circular_path_P.Motor1_sensorType > circular_path_P.Switch_Threshold_k) {
    rtb_Switch_p = circular_path_P.Gain_Gain_p *
      circular_path_DW.DiscreteTimeIntegrator_DSTATE_n;
  } else {
    rtb_Switch_p = rtb_Internal_g;
  }

  /* End of Switch: '<S3>/Switch' */

  /* Product: '<S6>/Product' incorporates:
   *  Constant: '<S6>/Wheel Radius'
   *  Gain: '<S6>/Gain1'
   *  Sum: '<S6>/Common Mode'
   */
  rtb_DiscreteTimeIntegrator_a = (rtb_Switch_a4 + rtb_Switch_p) *
    (circular_path_P.Gain1_Gain * circular_path_P.RobotSimulator_wheelR);

  /* Product: '<S6>/Product1' incorporates:
   *  Constant: '<S6>/Wheel Radius'
   *  Constant: '<S6>/Wheel Spacing'
   *  Product: '<S6>/Divide'
   *  Sum: '<S6>/Differential'
   */
  rtb_Product1 = circular_path_P.RobotSimulator_wheelR /
    circular_path_P.RobotSimulator_axleLength * (rtb_Switch_p - rtb_Switch_a4);

  /* Product: '<S6>/Product2' incorporates:
   *  DiscreteIntegrator: '<S6>/Discrete-Time Integrator2'
   *  Trigonometry: '<S6>/Comp_x'
   */
  rtb_Product2 = rtb_DiscreteTimeIntegrator_a * cos
    (circular_path_DW.DiscreteTimeIntegrator2_DSTATE);

  /* Product: '<S6>/Product3' incorporates:
   *  DiscreteIntegrator: '<S6>/Discrete-Time Integrator2'
   *  Trigonometry: '<S6>/Comp_y'
   */
  rtb_Product3 = rtb_DiscreteTimeIntegrator_a * sin
    (circular_path_DW.DiscreteTimeIntegrator2_DSTATE);

  /* S-Function (sfun_time): '<S6>/Soft Real Time' */

  /* Level2 S-Function Block: '<S6>/Soft Real Time' (sfun_time) */
  {
    SimStruct *rts = circular_path_M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* Gain: '<Root>/Gain9' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  Gain: '<Root>/Gain1'
   *  Gain: '<S1>/Gain5'
   *  Rounding: '<S1>/Rounding Function'
   */
  rtb_IntegralGain_g = 6.2831853071795862 * circular_path_P.wheelR /
    circular_path_P.ticksPerRot;
  rtb_DiscreteTimeIntegrator_a = ceil(circular_path_P.ticksPerRot / 360.0 *
    circular_path_DW.DiscreteTimeIntegrator_DSTATE_k) * rtb_IntegralGain_g;

  /* Gain: '<Root>/Gain1' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   *  Gain: '<S1>/Gain6'
   *  Rounding: '<S1>/Rounding Function1'
   */
  rtb_IntegralGain_g *= ceil(circular_path_P.ticksPerRot / 360.0 *
    circular_path_DW.DiscreteTimeIntegrator1_DSTAT_n);

  /* Sum: '<Root>/Subtract2' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant2'
   *  Product: '<Root>/Divide'
   *  Product: '<Root>/Divide1'
   *  Sum: '<Root>/Subtract1'
   */
  rtb_Subtract2 = circular_path_P.Constant2_Value -
    (rtb_DiscreteTimeIntegrator_a / circular_path_P.axleLength -
     rtb_IntegralGain_g / circular_path_P.axleLength);

  /* Gain: '<S102>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S94>/Filter'
   *  Gain: '<S93>/Derivative Gain'
   *  Sum: '<S94>/SumD'
   */
  rtb_FilterCoefficient = (circular_path_P.PIDController1_D * rtb_Subtract2 -
    circular_path_DW.Filter_DSTATE) * circular_path_P.PIDController1_N;

  /* Sum: '<S108>/Sum' incorporates:
   *  DiscreteIntegrator: '<S99>/Integrator'
   *  Gain: '<S104>/Proportional Gain'
   */
  rtb_Sum = (circular_path_P.PIDController1_P * rtb_Subtract2 +
             circular_path_DW.Integrator_DSTATE) + rtb_FilterCoefficient;

  /* Sum: '<Root>/Subtract' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Gain: '<Root>/Average'
   *  Sum: '<Root>/Add'
   */
  rtb_IntegralGain_g = circular_path_P.Constant1_Value_g - (rtb_IntegralGain_g -
    rtb_DiscreteTimeIntegrator_a) * circular_path_P.Average_Gain;

  /* SampleTimeMath: '<S46>/Tsamp' incorporates:
   *  Gain: '<S43>/Derivative Gain'
   *
   * About '<S46>/Tsamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_Tsamp = circular_path_P.PIDController_D * rtb_IntegralGain_g *
    circular_path_P.Tsamp_WtEt;

  /* Sum: '<S60>/Sum' incorporates:
   *  Delay: '<S44>/UD'
   *  DiscreteIntegrator: '<S51>/Integrator'
   *  Gain: '<S56>/Proportional Gain'
   *  Sum: '<S44>/Diff'
   */
  rtb_DiscreteTimeIntegrator_a = (circular_path_P.PIDController_P *
    rtb_IntegralGain_g + circular_path_DW.Integrator_DSTATE_p) + (rtb_Tsamp -
    circular_path_DW.UD_DSTATE);

  /* Gain: '<S7>/vtow' */
  tmp = 1.0 / circular_path_P.wheelR;

  /* Saturate: '<S58>/Saturation' */
  if (rtb_DiscreteTimeIntegrator_a >
      circular_path_P.PIDController_UpperSaturationLi) {
    tmp_0 = circular_path_P.PIDController_UpperSaturationLi;
  } else if (rtb_DiscreteTimeIntegrator_a <
             circular_path_P.PIDController_LowerSaturationLi) {
    tmp_0 = circular_path_P.PIDController_LowerSaturationLi;
  } else {
    tmp_0 = rtb_DiscreteTimeIntegrator_a;
  }

  /* Lookup_n-D: '<Root>/1-D Lookup Table' incorporates:
   *  Gain: '<S7>/change parameters'
   *  Gain: '<S7>/vtow'
   *  Saturate: '<S58>/Saturation'
   *  SignalConversion generated from: '<S7>/change parameters'
   */
  rtb_uDLookupTable = look1_binlcpw((circular_path_P.changeparameters_Gain[0] *
    tmp_0 + circular_path_P.changeparameters_Gain[2] * rtb_Sum) * tmp,
    circular_path_P.motorSp, circular_path_P.motorIp, 254U);

  /* Lookup_n-D: '<Root>/1-D Lookup Table1' incorporates:
   *  Gain: '<S7>/change parameters'
   *  Gain: '<S7>/vtow'
   *  Saturate: '<S58>/Saturation'
   *  SignalConversion generated from: '<S7>/change parameters'
   */
  rtb_uDLookupTable1 = look1_binlcpw((circular_path_P.changeparameters_Gain[1] *
    tmp_0 + circular_path_P.changeparameters_Gain[3] * rtb_Sum) * tmp,
    circular_path_P.motorSp, circular_path_P.motorIp, 254U);

  /* Gain: '<S1>/Gain2' */
  rtb_Gain2 = circular_path_P.Gain2_Gain * rtb_Switch_a4;

  /* Gain: '<S1>/Gain3' */
  rtb_Gain3 = circular_path_P.Gain3_Gain * rtb_Switch_p;

  /* Gain: '<S40>/ZeroGain' */
  rtb_Switch_a4 = circular_path_P.ZeroGain_Gain * rtb_DiscreteTimeIntegrator_a;

  /* DeadZone: '<S42>/DeadZone' */
  if (rtb_DiscreteTimeIntegrator_a >
      circular_path_P.PIDController_UpperSaturationLi) {
    rtb_DiscreteTimeIntegrator_a -=
      circular_path_P.PIDController_UpperSaturationLi;
  } else if (rtb_DiscreteTimeIntegrator_a >=
             circular_path_P.PIDController_LowerSaturationLi) {
    rtb_DiscreteTimeIntegrator_a = 0.0;
  } else {
    rtb_DiscreteTimeIntegrator_a -=
      circular_path_P.PIDController_LowerSaturationLi;
  }

  /* End of DeadZone: '<S42>/DeadZone' */

  /* Gain: '<S48>/Integral Gain' */
  rtb_IntegralGain_g *= circular_path_P.PIDController_I;

  /* Signum: '<S40>/SignPreSat' */
  if (rtb_DiscreteTimeIntegrator_a < 0.0) {
    /* DataTypeConversion: '<S40>/DataTypeConv1' */
    tmp = -1.0;
  } else if (rtb_DiscreteTimeIntegrator_a > 0.0) {
    /* DataTypeConversion: '<S40>/DataTypeConv1' */
    tmp = 1.0;
  } else if (rtb_DiscreteTimeIntegrator_a == 0.0) {
    /* DataTypeConversion: '<S40>/DataTypeConv1' */
    tmp = 0.0;
  } else {
    /* DataTypeConversion: '<S40>/DataTypeConv1' */
    tmp = (rtNaN);
  }

  /* End of Signum: '<S40>/SignPreSat' */

  /* DataTypeConversion: '<S40>/DataTypeConv1' */
  if (rtIsNaN(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  /* Signum: '<S40>/SignPreIntegrator' */
  if (rtb_IntegralGain_g < 0.0) {
    /* DataTypeConversion: '<S40>/DataTypeConv2' */
    rtb_Switch_p = -1.0;
  } else if (rtb_IntegralGain_g > 0.0) {
    /* DataTypeConversion: '<S40>/DataTypeConv2' */
    rtb_Switch_p = 1.0;
  } else if (rtb_IntegralGain_g == 0.0) {
    /* DataTypeConversion: '<S40>/DataTypeConv2' */
    rtb_Switch_p = 0.0;
  } else {
    /* DataTypeConversion: '<S40>/DataTypeConv2' */
    rtb_Switch_p = (rtNaN);
  }

  /* End of Signum: '<S40>/SignPreIntegrator' */

  /* DataTypeConversion: '<S40>/DataTypeConv2' */
  if (rtIsNaN(rtb_Switch_p)) {
    rtb_Switch_p = 0.0;
  } else {
    rtb_Switch_p = fmod(rtb_Switch_p, 256.0);
  }

  /* Switch: '<S40>/Switch' incorporates:
   *  DataTypeConversion: '<S40>/DataTypeConv1'
   *  DataTypeConversion: '<S40>/DataTypeConv2'
   *  Logic: '<S40>/AND3'
   *  RelationalOperator: '<S40>/Equal1'
   *  RelationalOperator: '<S40>/NotEqual'
   */
  if ((rtb_Switch_a4 != rtb_DiscreteTimeIntegrator_a) && ((tmp < 0.0 ? (int32_T)
        (int8_T)-(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp) ==
       (rtb_Switch_p < 0.0 ? (int32_T)(int8_T)-(int8_T)(uint8_T)-rtb_Switch_p :
        (int32_T)(int8_T)(uint8_T)rtb_Switch_p))) {
    /* Switch: '<S40>/Switch' incorporates:
     *  Constant: '<S40>/Constant1'
     */
    rtb_Switch = circular_path_P.Constant1_Value;
  } else {
    /* Switch: '<S40>/Switch' */
    rtb_Switch = rtb_IntegralGain_g;
  }

  /* End of Switch: '<S40>/Switch' */

  /* Gain: '<S96>/Integral Gain' */
  rtb_IntegralGain = circular_path_P.PIDController1_I * rtb_Subtract2;

  /* Matfile logging */
  rt_UpdateTXYLogVars(circular_path_M->rtwLogInfo, (circular_path_M->Timing.t));

  /* Update for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' */
  circular_path_DW.DiscreteTimeIntegrator_DSTATE +=
    circular_path_P.DiscreteTimeIntegrator_gainval * rtb_Product2;

  /* Update for DiscreteIntegrator: '<S6>/Discrete-Time Integrator1' */
  circular_path_DW.DiscreteTimeIntegrator1_DSTATE +=
    circular_path_P.DiscreteTimeIntegrator1_gainval * rtb_Product3;

  /* Update for DiscreteIntegrator: '<S6>/Discrete-Time Integrator2' */
  circular_path_DW.DiscreteTimeIntegrator2_DSTATE +=
    circular_path_P.DiscreteTimeIntegrator2_gainval * rtb_Product1;

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  circular_path_DW.DiscreteTimeIntegrator_DSTATE_p +=
    circular_path_P.DiscreteTimeIntegrator_gainva_d * rtb_Internal;

  /* Update for DiscreteStateSpace: '<S8>/Internal' */
  {
    real_T xnew[3];
    xnew[0] = (circular_path_P.Internal_A[0])*circular_path_DW.Internal_DSTATE[0]
      + (circular_path_P.Internal_A[1])*circular_path_DW.Internal_DSTATE[1]
      + (circular_path_P.Internal_A[2])*circular_path_DW.Internal_DSTATE[2];
    xnew[0] += (circular_path_P.Internal_B[0])*rtb_uDLookupTable;
    xnew[1] = (circular_path_P.Internal_A[3])*circular_path_DW.Internal_DSTATE[0]
      + (circular_path_P.Internal_A[4])*circular_path_DW.Internal_DSTATE[1]
      + (circular_path_P.Internal_A[5])*circular_path_DW.Internal_DSTATE[2];
    xnew[1] += (circular_path_P.Internal_B[1])*rtb_uDLookupTable;
    xnew[2] = (circular_path_P.Internal_A[6])*circular_path_DW.Internal_DSTATE[0]
      + (circular_path_P.Internal_A[7])*circular_path_DW.Internal_DSTATE[1]
      + (circular_path_P.Internal_A[8])*circular_path_DW.Internal_DSTATE[2];
    xnew[2] += (circular_path_P.Internal_B[2])*rtb_uDLookupTable;
    (void) memcpy(&circular_path_DW.Internal_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  circular_path_DW.DiscreteTimeIntegrator_DSTATE_n +=
    circular_path_P.DiscreteTimeIntegrator_gainva_o * rtb_Internal_g;

  /* Update for DiscreteStateSpace: '<S12>/Internal' */
  {
    real_T xnew[3];
    xnew[0] = (circular_path_P.Internal_A_n[0])*
      circular_path_DW.Internal_DSTATE_l[0]
      + (circular_path_P.Internal_A_n[1])*circular_path_DW.Internal_DSTATE_l[1]
      + (circular_path_P.Internal_A_n[2])*circular_path_DW.Internal_DSTATE_l[2];
    xnew[0] += (circular_path_P.Internal_B_b[0])*rtb_uDLookupTable1;
    xnew[1] = (circular_path_P.Internal_A_n[3])*
      circular_path_DW.Internal_DSTATE_l[0]
      + (circular_path_P.Internal_A_n[4])*circular_path_DW.Internal_DSTATE_l[1]
      + (circular_path_P.Internal_A_n[5])*circular_path_DW.Internal_DSTATE_l[2];
    xnew[1] += (circular_path_P.Internal_B_b[1])*rtb_uDLookupTable1;
    xnew[2] = (circular_path_P.Internal_A_n[6])*
      circular_path_DW.Internal_DSTATE_l[0]
      + (circular_path_P.Internal_A_n[7])*circular_path_DW.Internal_DSTATE_l[1]
      + (circular_path_P.Internal_A_n[8])*circular_path_DW.Internal_DSTATE_l[2];
    xnew[2] += (circular_path_P.Internal_B_b[2])*rtb_uDLookupTable1;
    (void) memcpy(&circular_path_DW.Internal_DSTATE_l[0], xnew,
                  sizeof(real_T)*3);
  }

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  circular_path_DW.DiscreteTimeIntegrator_DSTATE_k +=
    circular_path_P.DiscreteTimeIntegrator_gainva_l * rtb_Gain2;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  circular_path_DW.DiscreteTimeIntegrator1_DSTAT_n +=
    circular_path_P.DiscreteTimeIntegrator1_gainv_b * rtb_Gain3;

  /* Update for DiscreteIntegrator: '<S99>/Integrator' */
  circular_path_DW.Integrator_DSTATE += circular_path_P.Integrator_gainval *
    rtb_IntegralGain;

  /* Update for DiscreteIntegrator: '<S94>/Filter' */
  circular_path_DW.Filter_DSTATE += circular_path_P.Filter_gainval *
    rtb_FilterCoefficient;

  /* Update for DiscreteIntegrator: '<S51>/Integrator' */
  circular_path_DW.Integrator_DSTATE_p += circular_path_P.Integrator_gainval_c *
    rtb_Switch;

  /* Update for Delay: '<S44>/UD' */
  circular_path_DW.UD_DSTATE = rtb_Tsamp;

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0s, 0.0s] */
    if ((rtmGetTFinal(circular_path_M)!=-1) &&
        !((rtmGetTFinal(circular_path_M)-circular_path_M->Timing.t[0]) >
          circular_path_M->Timing.t[0] * (DBL_EPSILON))) {
      rtmSetErrorStatus(circular_path_M, "Simulation finished");
    }

    if (rtmGetStopRequested(circular_path_M)) {
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

  circular_path_M->Timing.t[0] = circular_path_M->Timing.clockTick0 *
    circular_path_M->Timing.stepSize0 + circular_path_M->Timing.clockTickH0 *
    circular_path_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.01, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    circular_path_M->Timing.clockTick1++;
    if (!circular_path_M->Timing.clockTick1) {
      circular_path_M->Timing.clockTickH1++;
    }
  }
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

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&circular_path_M->solverInfo,
                          &circular_path_M->Timing.simTimeStep);
    rtsiSetTPtr(&circular_path_M->solverInfo, &rtmGetTPtr(circular_path_M));
    rtsiSetStepSizePtr(&circular_path_M->solverInfo,
                       &circular_path_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&circular_path_M->solverInfo, (&rtmGetErrorStatus
      (circular_path_M)));
    rtsiSetRTModelPtr(&circular_path_M->solverInfo, circular_path_M);
  }

  rtsiSetSimTimeStep(&circular_path_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&circular_path_M->solverInfo,"FixedStepDiscrete");
  circular_path_M->solverInfoPtr = (&circular_path_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = circular_path_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "circular_path_M points to
       static memory which is guaranteed to be non-NULL" */
    circular_path_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    circular_path_M->Timing.sampleTimes =
      (&circular_path_M->Timing.sampleTimesArray[0]);
    circular_path_M->Timing.offsetTimes =
      (&circular_path_M->Timing.offsetTimesArray[0]);

    /* task periods */
    circular_path_M->Timing.sampleTimes[0] = (0.0);
    circular_path_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    circular_path_M->Timing.offsetTimes[0] = (0.0);
    circular_path_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(circular_path_M, &circular_path_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = circular_path_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    circular_path_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(circular_path_M, 10.0);
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

  circular_path_M->solverInfoPtr = (&circular_path_M->solverInfo);
  circular_path_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&circular_path_M->solverInfo, 0.01);
  rtsiSetSolverMode(&circular_path_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* states (dwork) */
  (void) memset((void *)&circular_path_DW, 0,
                sizeof(DW_circular_path_T));

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &circular_path_M->NonInlinedSFcns.sfcnInfo;
    circular_path_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(circular_path_M)));
    circular_path_M->Sizes.numSampTimes = (2);
    rtssSetNumRootSampTimesPtr(sfcnInfo, &circular_path_M->Sizes.numSampTimes);
    circular_path_M->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr
      (circular_path_M)[0]);
    circular_path_M->NonInlinedSFcns.taskTimePtrs[1] = &(rtmGetTPtr
      (circular_path_M)[1]);
    rtssSetTPtrPtr(sfcnInfo,circular_path_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(circular_path_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(circular_path_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput(circular_path_M));
    rtssSetStepSizePtr(sfcnInfo, &circular_path_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(circular_path_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &circular_path_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo, &circular_path_M->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &circular_path_M->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &circular_path_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &circular_path_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &circular_path_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &circular_path_M->solverInfoPtr);
  }

  circular_path_M->Sizes.numSFcns = (1);

  /* register each child */
  {
    (void) memset((void *)&circular_path_M->NonInlinedSFcns.childSFunctions[0],
                  0,
                  1*sizeof(SimStruct));
    circular_path_M->childSfunctions =
      (&circular_path_M->NonInlinedSFcns.childSFunctionPtrs[0]);
    circular_path_M->childSfunctions[0] =
      (&circular_path_M->NonInlinedSFcns.childSFunctions[0]);

    /* Level2 S-Function Block: circular_path/<S6>/Soft Real Time (sfun_time) */
    {
      SimStruct *rts = circular_path_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod = circular_path_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = circular_path_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = circular_path_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &circular_path_M->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &circular_path_M->NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, circular_path_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &circular_path_M->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &circular_path_M->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &circular_path_M->NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &circular_path_M->NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts,
          &circular_path_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* path info */
      ssSetModelName(rts, "Soft Real Time");
      ssSetPath(rts, "circular_path/Robot Simulator/Soft Real Time");
      ssSetRTModel(rts,circular_path_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &circular_path_M->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 1);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)circular_path_P.SoftRealTime_P1_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *) &circular_path_DW.SoftRealTime_RWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &circular_path_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &circular_path_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* RWORK */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &circular_path_DW.SoftRealTime_RWORK);
      }

      /* registration */
      sfun_time(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.0);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      /* Update the BufferDstPort flags for each input port */
    }
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(circular_path_M->rtwLogInfo, 0.0,
    rtmGetTFinal(circular_path_M), circular_path_M->Timing.stepSize0,
    (&rtmGetErrorStatus(circular_path_M)));

  /* Start for S-Function (sfun_time): '<S6>/Soft Real Time' */
  /* Level2 S-Function Block: '<S6>/Soft Real Time' (sfun_time) */
  {
    SimStruct *rts = circular_path_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* InitializeConditions for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' */
  circular_path_DW.DiscreteTimeIntegrator_DSTATE =
    circular_path_P.RobotSimulator_startX;

  /* InitializeConditions for DiscreteIntegrator: '<S6>/Discrete-Time Integrator1' */
  circular_path_DW.DiscreteTimeIntegrator1_DSTATE =
    circular_path_P.RobotSimulator_startY;

  /* InitializeConditions for DiscreteIntegrator: '<S6>/Discrete-Time Integrator2' */
  circular_path_DW.DiscreteTimeIntegrator2_DSTATE =
    circular_path_P.RobotSimulator_startTheta * 0.017453292519943295;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  circular_path_DW.DiscreteTimeIntegrator_DSTATE_p =
    circular_path_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for DiscreteStateSpace: '<S8>/Internal' */
  circular_path_DW.Internal_DSTATE[0] = 0.0;
  circular_path_DW.Internal_DSTATE[1] = 0.0;
  circular_path_DW.Internal_DSTATE[2] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' */
  circular_path_DW.DiscreteTimeIntegrator_DSTATE_n =
    circular_path_P.DiscreteTimeIntegrator_IC_l;

  /* InitializeConditions for DiscreteStateSpace: '<S12>/Internal' */
  circular_path_DW.Internal_DSTATE_l[0] = 0.0;
  circular_path_DW.Internal_DSTATE_l[1] = 0.0;
  circular_path_DW.Internal_DSTATE_l[2] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' */
  circular_path_DW.DiscreteTimeIntegrator_DSTATE_k =
    circular_path_P.DiscreteTimeIntegrator_IC_k;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' */
  circular_path_DW.DiscreteTimeIntegrator1_DSTAT_n =
    circular_path_P.DiscreteTimeIntegrator1_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S99>/Integrator' */
  circular_path_DW.Integrator_DSTATE =
    circular_path_P.PIDController1_InitialConditi_m;

  /* InitializeConditions for DiscreteIntegrator: '<S94>/Filter' */
  circular_path_DW.Filter_DSTATE =
    circular_path_P.PIDController1_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S51>/Integrator' */
  circular_path_DW.Integrator_DSTATE_p =
    circular_path_P.PIDController_InitialConditionF;

  /* InitializeConditions for Delay: '<S44>/UD' */
  circular_path_DW.UD_DSTATE = circular_path_P.PIDController_DifferentiatorICP;
}

/* Model terminate function */
void circular_path_terminate(void)
{
  /* Terminate for S-Function (sfun_time): '<S6>/Soft Real Time' */
  /* Level2 S-Function Block: '<S6>/Soft Real Time' (sfun_time) */
  {
    SimStruct *rts = circular_path_M->childSfunctions[0];
    sfcnTerminate(rts);
  }
}
