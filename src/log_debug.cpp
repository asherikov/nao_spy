/**
 * @file
 * @author Alexander Sherikov
 * @date 03.01.2012 19:17:44 MSK
 */


#include "log_debug.h"
#include "nao_igm.h"


spy_timer::spy_timer()
{
    qi::os::gettimeofday (&start_time);
}

spy_timer::~spy_timer()
{
    qi::os::gettimeofday (&end_time);
    qiLogInfo ("module.nao_spy", "Exec time (sec): %f\n",
        (double) end_time.tv_sec - start_time.tv_sec + 0.000001* (end_time.tv_usec - start_time.tv_usec));
}



spy_log::spy_log ()
{
    FJointsLog = fopen ("./spy_joints.log", "w");
    FCoMLog = fopen ("./spy_com.log", "w");
    FRightFootLog = fopen ("./spy_right_foot.log", "w");
    FLeftFootLog = fopen ("./spy_left_foot.log", "w");
    FSwingFootLog = fopen ("./spy_swing_foot.log", "w");
}

spy_log::~spy_log ()
{
    fclose (FJointsLog);
    fclose (FCoMLog);
    fclose (FRightFootLog);
    fclose (FLeftFootLog);
    fclose (FSwingFootLog);
}



void spy_log::logJointValues(
        ALPtr<ALMemoryFastAccess> accessSensorValues,
        ALPtr<ALMemoryFastAccess> accessActuatorValues)
{
    accessSensorValues->GetValues (sensorValues);
    fprintf (FJointsLog, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f    ",
                        sensorValues[HEAD_PITCH],
                        sensorValues[HEAD_YAW],
                        //
                        sensorValues[L_ANKLE_PITCH],
                        sensorValues[L_ANKLE_ROLL],
                        sensorValues[L_ELBOW_ROLL],
                        sensorValues[L_ELBOW_YAW],
                        sensorValues[L_HIP_PITCH],
                        sensorValues[L_HIP_ROLL],
                        sensorValues[L_HIP_YAW_PITCH],
                        sensorValues[L_KNEE_PITCH],
                        sensorValues[L_SHOULDER_PITCH],
                        sensorValues[L_SHOULDER_ROLL],
                        sensorValues[L_WRIST_YAW],
                        //
                        sensorValues[R_ANKLE_PITCH],
                        sensorValues[R_ANKLE_ROLL],
                        sensorValues[R_ELBOW_ROLL],
                        sensorValues[R_ELBOW_YAW],
                        sensorValues[R_HIP_PITCH],
                        sensorValues[R_HIP_ROLL],
                        sensorValues[R_KNEE_PITCH],
                        sensorValues[R_SHOULDER_PITCH],
                        sensorValues[R_SHOULDER_ROLL],
                        sensorValues[R_WRIST_YAW]);

    accessActuatorValues->GetValues (sensorValues);
    fprintf (FJointsLog, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
                        sensorValues[HEAD_PITCH],
                        sensorValues[HEAD_YAW],
                        //
                        sensorValues[L_ANKLE_PITCH],
                        sensorValues[L_ANKLE_ROLL],
                        sensorValues[L_ELBOW_ROLL],
                        sensorValues[L_ELBOW_YAW],
                        sensorValues[L_HIP_PITCH],
                        sensorValues[L_HIP_ROLL],
                        sensorValues[L_HIP_YAW_PITCH],
                        sensorValues[L_KNEE_PITCH],
                        sensorValues[L_SHOULDER_PITCH],
                        sensorValues[L_SHOULDER_ROLL],
                        sensorValues[L_WRIST_YAW],
                        //
                        sensorValues[R_ANKLE_PITCH],
                        sensorValues[R_ANKLE_ROLL],
                        sensorValues[R_ELBOW_ROLL],
                        sensorValues[R_ELBOW_YAW],
                        sensorValues[R_HIP_PITCH],
                        sensorValues[R_HIP_ROLL],
                        sensorValues[R_KNEE_PITCH],
                        sensorValues[R_SHOULDER_PITCH],
                        sensorValues[R_SHOULDER_ROLL],
                        sensorValues[R_WRIST_YAW]);
}



void spy_log::logCoM(
        AL::ALPtr<AL::ALMotionProxy> motionProxy,
        ALPtr<ALMemoryFastAccess> accessSensorValues)
{
    vector<float> CoM;
    nao_igm nao;
    vector<float> lfoot, rfoot;


    
    accessSensorValues->GetValues (sensorValues);
    for (int i = 0; i < JOINTS_NUM; i++)
    {
        nao.state.q[i] = sensorValues[i];
    }

    rfoot = motionProxy->getPosition("RLeg",1,false);
    lfoot = motionProxy->getPosition("LLeg",1,false);
    if (rfoot[2] < lfoot[2])
    {
        nao.init (
            IGM_SUPPORT_RIGHT,
            rfoot[0], rfoot[1], rfoot[2],
            rfoot[3], rfoot[4], rfoot[5]);
    }
    else
    {
        nao.init (
            IGM_SUPPORT_LEFT,
            lfoot[0], lfoot[1], lfoot[2],
            lfoot[3], lfoot[4], lfoot[5]);
    }
    

    CoM = motionProxy->getCOM("Body",1,false);
    fprintf (FCoMLog, "%f %f %f    ", CoM[0], CoM[1], CoM[2]);

    CoM.clear();
    CoM = motionProxy->getCOM("Body",1,true);
    fprintf (FCoMLog, "%f %f %f    ", CoM[0], CoM[1], CoM[2]);

    double igm_CoM[3];
    nao.state.getCoM(igm_CoM);
    fprintf (FCoMLog, "%f %f %f\n", igm_CoM[0], igm_CoM[1], igm_CoM[2]);
}


void spy_log::logFoot(
        AL::ALPtr<AL::ALMotionProxy> motionProxy,
        ALPtr<ALMemoryFastAccess> accessSensorValues)
{
    nao_igm nao;
    vector<float> lfoot, rfoot;


    accessSensorValues->GetValues (sensorValues);
    for (int i = 0; i < JOINTS_NUM; i++)
    {
        nao.state.q[i] = sensorValues[i];
    }
    rfoot = motionProxy->getPosition("RLeg",1,false);
    lfoot = motionProxy->getPosition("LLeg",1,false);
    if (rfoot[2] < lfoot[2])
    {
        nao.init (
            IGM_SUPPORT_RIGHT,
            rfoot[0], rfoot[1], rfoot[2],
            rfoot[3], rfoot[4], rfoot[5]);
    }
    else
    {
        nao.init (
            IGM_SUPPORT_LEFT,
            lfoot[0], lfoot[1], lfoot[2],
            lfoot[3], lfoot[4], lfoot[5]);
    }


    fprintf (FLeftFootLog, "%f %f %f    ", lfoot[0], lfoot[1], lfoot[2]);
    lfoot.clear();
    lfoot = motionProxy->getPosition("LLeg",1,true);
    fprintf (FLeftFootLog, "%f %f %f\n", lfoot[0], lfoot[1], lfoot[2]);


    fprintf (FRightFootLog, "%f %f %f    ", rfoot[0], rfoot[1], rfoot[2]);
    rfoot.clear();
    rfoot = motionProxy->getPosition("RLeg",1,true);
    fprintf (FRightFootLog, "%f %f %f\n", rfoot[0], rfoot[1], rfoot[2]);


    double swing_foot[3];
    nao.state.getSwingFoot(swing_foot);
    fprintf (FSwingFootLog, "%f %f %f\n", swing_foot[0], swing_foot[1], swing_foot[2]);
}
