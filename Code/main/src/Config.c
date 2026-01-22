#include "headers/Config.h"

/*---Controller---*/

//Controller gains:
const float KpX = 1500.f;
const float KpY = 1500.f;
const float KpZ = 1500.f;

const float KdX = 150.f;
const float KdY = 150.f;
const float KdZ = 0.f;

const float KiX = 0.f; //450.f;
const float KiY = 0.f; //450.f;
const float KiZ = 0.f;

//Integrator wind-up limits:
const float WindUpX = 100.f;
const float WindupY = 100.f;
const float WindUpZ = 100.f;

//Throttle limits:
const float TMax = 1920.f;
const float TMin = 1050.f;
const float TCutoff = 980.f;
const float TPowerOff = 0.f;

//Arm threshold for the four radio channels
const uint32_t ArmCh0 = 1200; //Yaw
const uint32_t ArmCh1 = 1000; //Throttle
const uint32_t ArmCh2 = 1200; //Pitch
const uint32_t ArmCh3 = 1200; //Roll

//Controller behavior selection
const float RollRate = 1.f; //Not implemented
const float PitchRate = 1.f; //Not implemented
const float YawRate = 1.f;



/*---Estimator---*/

//For the complementary filter
const float KpXe = 0.5f;
const float KpYe = 0.5f; 
const float KpZe = 0.0f; //Set to 0 until magnetometer is introduced

//For gyro-bias estimation
const float KiXe = 0.15f;
const float KiYe = 0.15f; 
const float KiZe = 0.0f; //Set to 0 until magnetometer is introduced

//Gyroscope LP-filter time constant
const float Lambda = 0.0107f;
