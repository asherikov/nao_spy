/**
 * @file
 * @author Alexander Sherikov
 * @date 03.01.2012 19:17:44 MSK
 */


#include <cmath>

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



spy_log::spy_log (ALPtr<ALMemoryFastAccess> accessSensorValues)
{
    accessSensorValues->GetValues (sensorOldValues);
    FJointsLog = fopen ("./spy_joints.log", "w");
    FCoMLog = fopen ("./spy_com.log", "w");
    FRightFootLog = fopen ("./spy_right_foot.log", "w");
    FLeftFootLog = fopen ("./spy_left_foot.log", "w");
    FJointVelocities = fopen ("./spy_joint_velocities.log", "w");
}

spy_log::~spy_log ()
{
    fclose (FJointsLog);
    fclose (FCoMLog);
    fclose (FRightFootLog);
    fclose (FLeftFootLog);
    fclose (FJointVelocities);
}



void spy_log::logJointValues(
        ALPtr<ALMemoryFastAccess> accessSensorValues,
        ALPtr<ALMemoryFastAccess> accessActuatorValues)
{
    accessSensorValues->GetValues (sensorValues);
    for (int i = 0; i < JOINTS_NUM; i++)
    {
        fprintf (FJointsLog, "%f ", sensorValues[i]);
    }
    fprintf (FJointsLog, "    ");


    accessActuatorValues->GetValues (sensorValues);
    for (int i = 0; i < JOINTS_NUM; i++)
    {
        fprintf (FJointsLog, "%f ", sensorValues[i]);
    }
    fprintf (FJointsLog, "\n");
}


void spy_log::logJointVelocities (ALPtr<ALMemoryFastAccess> accessSensorValues, const double time)
{
    accessSensorValues->GetValues (sensorValues);
    for (int i = 0; i < JOINTS_NUM; i++)
    {
        fprintf (FJointVelocities, "%f ", fabs(sensorOldValues[i] - sensorValues[i]) / time);
        sensorOldValues[i] = sensorValues[i];
    }
    fprintf (FJointVelocities, "\n");
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

    rfoot = motionProxy->getPosition("RLeg",1,true);
    lfoot = motionProxy->getPosition("LLeg",1,true);
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
    lfoot = motionProxy->getPosition("LLeg",1,false);
    fprintf (FLeftFootLog, "%f %f %f    ", lfoot[0], lfoot[1], lfoot[2]);
    rfoot = motionProxy->getPosition("RLeg",1,false);
    fprintf (FRightFootLog, "%f %f %f    ", rfoot[0], rfoot[1], rfoot[2]);

    lfoot.clear();
    lfoot = motionProxy->getPosition("LLeg",1,true);
    fprintf (FLeftFootLog, "%f %f %f     ", lfoot[0], lfoot[1], lfoot[2]);
    rfoot.clear();
    rfoot = motionProxy->getPosition("RLeg",1,true);
    fprintf (FRightFootLog, "%f %f %f    ", rfoot[0], rfoot[1], rfoot[2]);



    double swing_foot[3];
    nao.init (
        IGM_SUPPORT_RIGHT,
        rfoot[0], rfoot[1], rfoot[2],
        rfoot[3], rfoot[4], rfoot[5]);
    nao.state.getSwingFoot(swing_foot);
    fprintf (FLeftFootLog, "%f %f %f\n", swing_foot[0], swing_foot[1], swing_foot[2]);

    nao.init (
        IGM_SUPPORT_LEFT,
        lfoot[0], lfoot[1], lfoot[2],
        lfoot[3], lfoot[4], lfoot[5]);
    nao.state.getSwingFoot(swing_foot);
    fprintf (FRightFootLog, "%f %f %f\n", swing_foot[0], swing_foot[1], swing_foot[2]);
}
