/**
 * @file
 * @author Alexander Sherikov
 */

#include "nao_spy.h"

/**
 * @brief Initializes variables, that are necessary for fast reading of data from memory.
 */
void nao_spy::initFastRead()
{
    // Sensors names
    vector<string> fSensorKeys;

    fSensorKeys.clear();

    fSensorKeys.resize(JOINTS_NUM);

    // Joints Sensor list
    fSensorKeys[HEAD_PITCH]       = std::string("Device/SubDeviceList/HeadPitch/Position/Sensor/Value");
    fSensorKeys[HEAD_YAW]         = std::string("Device/SubDeviceList/HeadYaw/Position/Sensor/Value");

    fSensorKeys[L_ANKLE_PITCH]    = std::string("Device/SubDeviceList/LAnklePitch/Position/Sensor/Value");
    fSensorKeys[L_ANKLE_ROLL]     = std::string("Device/SubDeviceList/LAnkleRoll/Position/Sensor/Value");
    fSensorKeys[L_ELBOW_ROLL]     = std::string("Device/SubDeviceList/LElbowRoll/Position/Sensor/Value");
    fSensorKeys[L_ELBOW_YAW]      = std::string("Device/SubDeviceList/LElbowYaw/Position/Sensor/Value");
    fSensorKeys[L_HIP_PITCH]      = std::string("Device/SubDeviceList/LHipPitch/Position/Sensor/Value");
    fSensorKeys[L_HIP_ROLL]       = std::string("Device/SubDeviceList/LHipRoll/Position/Sensor/Value");
    fSensorKeys[L_HIP_YAW_PITCH]  = std::string("Device/SubDeviceList/LHipYawPitch/Position/Sensor/Value");
    fSensorKeys[L_KNEE_PITCH]     = std::string("Device/SubDeviceList/LKneePitch/Position/Sensor/Value");
    fSensorKeys[L_SHOULDER_PITCH] = std::string("Device/SubDeviceList/LShoulderPitch/Position/Sensor/Value");
    fSensorKeys[L_SHOULDER_ROLL]  = std::string("Device/SubDeviceList/LShoulderRoll/Position/Sensor/Value");
    fSensorKeys[L_WRIST_YAW]      = std::string("Device/SubDeviceList/LWristYaw/Position/Sensor/Value");

    fSensorKeys[R_ANKLE_PITCH]    = std::string("Device/SubDeviceList/RAnklePitch/Position/Sensor/Value");
    fSensorKeys[R_ANKLE_ROLL]     = std::string("Device/SubDeviceList/RAnkleRoll/Position/Sensor/Value");
    fSensorKeys[R_ELBOW_ROLL]     = std::string("Device/SubDeviceList/RElbowRoll/Position/Sensor/Value");
    fSensorKeys[R_ELBOW_YAW]      = std::string("Device/SubDeviceList/RElbowYaw/Position/Sensor/Value");
    fSensorKeys[R_HIP_PITCH]      = std::string("Device/SubDeviceList/RHipPitch/Position/Sensor/Value");
    fSensorKeys[R_HIP_ROLL]       = std::string("Device/SubDeviceList/RHipRoll/Position/Sensor/Value");
    // note, that R_HIP_YAW_PITCH is controlled by the same motor as L_HIP_YAW_PITCH 
    fSensorKeys[R_HIP_YAW_PITCH]  = std::string("Device/SubDeviceList/RHipYawPitch/Position/Sensor/Value");
    fSensorKeys[R_KNEE_PITCH]     = std::string("Device/SubDeviceList/RKneePitch/Position/Sensor/Value");
    fSensorKeys[R_SHOULDER_PITCH] = std::string("Device/SubDeviceList/RShoulderPitch/Position/Sensor/Value");
    fSensorKeys[R_SHOULDER_ROLL]  = std::string("Device/SubDeviceList/RShoulderRoll/Position/Sensor/Value");
    fSensorKeys[R_WRIST_YAW]      = std::string("Device/SubDeviceList/RWristYaw/Position/Sensor/Value");

    // Create the fast memory access
    accessSensorValues->ConnectToVariables(getParentBroker(), fSensorKeys, false);


    // Joints Sensor list
    fSensorKeys[HEAD_PITCH]       = std::string("Device/SubDeviceList/HeadPitch/Position/Actuator/Value");
    fSensorKeys[HEAD_YAW]         = std::string("Device/SubDeviceList/HeadYaw/Position/Actuator/Value");

    fSensorKeys[L_ANKLE_PITCH]    = std::string("Device/SubDeviceList/LAnklePitch/Position/Actuator/Value");
    fSensorKeys[L_ANKLE_ROLL]     = std::string("Device/SubDeviceList/LAnkleRoll/Position/Actuator/Value");
    fSensorKeys[L_ELBOW_ROLL]     = std::string("Device/SubDeviceList/LElbowRoll/Position/Actuator/Value");
    fSensorKeys[L_ELBOW_YAW]      = std::string("Device/SubDeviceList/LElbowYaw/Position/Actuator/Value");
    fSensorKeys[L_HIP_PITCH]      = std::string("Device/SubDeviceList/LHipPitch/Position/Actuator/Value");
    fSensorKeys[L_HIP_ROLL]       = std::string("Device/SubDeviceList/LHipRoll/Position/Actuator/Value");
    fSensorKeys[L_HIP_YAW_PITCH]  = std::string("Device/SubDeviceList/LHipYawPitch/Position/Actuator/Value");
    fSensorKeys[L_KNEE_PITCH]     = std::string("Device/SubDeviceList/LKneePitch/Position/Actuator/Value");
    fSensorKeys[L_SHOULDER_PITCH] = std::string("Device/SubDeviceList/LShoulderPitch/Position/Actuator/Value");
    fSensorKeys[L_SHOULDER_ROLL]  = std::string("Device/SubDeviceList/LShoulderRoll/Position/Actuator/Value");
    fSensorKeys[L_WRIST_YAW]      = std::string("Device/SubDeviceList/LWristYaw/Position/Actuator/Value");

    fSensorKeys[R_ANKLE_PITCH]    = std::string("Device/SubDeviceList/RAnklePitch/Position/Actuator/Value");
    fSensorKeys[R_ANKLE_ROLL]     = std::string("Device/SubDeviceList/RAnkleRoll/Position/Actuator/Value");
    fSensorKeys[R_ELBOW_ROLL]     = std::string("Device/SubDeviceList/RElbowRoll/Position/Actuator/Value");
    fSensorKeys[R_ELBOW_YAW]      = std::string("Device/SubDeviceList/RElbowYaw/Position/Actuator/Value");
    fSensorKeys[R_HIP_PITCH]      = std::string("Device/SubDeviceList/RHipPitch/Position/Actuator/Value");
    fSensorKeys[R_HIP_ROLL]       = std::string("Device/SubDeviceList/RHipRoll/Position/Actuator/Value");
    // note, that R_HIP_YAW_PITCH is controlled by the same motor as L_HIP_YAW_PITCH 
    fSensorKeys[R_HIP_YAW_PITCH]  = std::string("Device/SubDeviceList/RHipYawPitch/Position/Actuator/Value");
    fSensorKeys[R_KNEE_PITCH]     = std::string("Device/SubDeviceList/RKneePitch/Position/Actuator/Value");
    fSensorKeys[R_SHOULDER_PITCH] = std::string("Device/SubDeviceList/RShoulderPitch/Position/Actuator/Value");
    fSensorKeys[R_SHOULDER_ROLL]  = std::string("Device/SubDeviceList/RShoulderRoll/Position/Actuator/Value");
    fSensorKeys[R_WRIST_YAW]      = std::string("Device/SubDeviceList/RWristYaw/Position/Actuator/Value");

    // Create the fast memory access
    accessActuatorValues->ConnectToVariables(getParentBroker(), fSensorKeys, false);
}
