/**
 * @file
 * @author Alexander Sherikov
 * @date 03.01.2012 19:17:44 MSK
 */


#ifndef LOG_DEBUG_H
#define LOG_DEBUG_H

#include <qi/os.hpp>
#include <qi/log.hpp>

#include <cstdio>
#include <alcore/alptr.h>
#include <almemoryfastaccess/almemoryfastaccess.h>
#include <alproxies/almotionproxy.h>

#include "joints_sensors_id.h"



/**
 * @brief Log time of existance on destruction.
 */
class spy_timer
{
    public:
        spy_timer();
        ~spy_timer();

    private:
        qi::os::timeval end_time;
        qi::os::timeval start_time;
};



using namespace AL;
using namespace std;

class spy_log
{
    public:
        spy_log (ALPtr<ALMemoryFastAccess>);
        ~spy_log ();

        void logJointValues (ALPtr<ALMemoryFastAccess>, ALPtr<ALMemoryFastAccess>);

        void logCoM (AL::ALPtr<AL::ALMotionProxy>, ALPtr<ALMemoryFastAccess>);
        void logFoot (AL::ALPtr<AL::ALMotionProxy>, ALPtr<ALMemoryFastAccess>);
        void logJointVelocities (ALPtr<ALMemoryFastAccess>, const double);

    private:
        FILE *FJointsLog;
        FILE *FCoMLog;
        FILE *FRightFootLog;
        FILE *FLeftFootLog;
        FILE *FJointVelocities;
        vector<float> sensorValues;
        vector<float> sensorOldValues;
};

#endif // LOG_DEBUG_H
