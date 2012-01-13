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

#define SPY_TIMER spy_timer timer




using namespace AL;
using namespace std;

class spy_log
{
    public:
        spy_log ();
        ~spy_log ();

        void logJointValues (
                ALPtr<ALMemoryFastAccess> accessSensorValues,
                ALPtr<ALMemoryFastAccess> accessActuatorValues);

        void logCoM (AL::ALPtr<AL::ALMotionProxy>);
        void logFoot (AL::ALPtr<AL::ALMotionProxy>);

    private:
        FILE *FJointsLog;
        FILE *FCoMLog;
        FILE *FRightFootLog;
        FILE *FLeftFootLog;
        vector<float> sensorValues;
};

extern spy_log *spy_log_instance;

#define SPY_LOG_OPEN spy_log_instance = new spy_log
#define SPY_LOG_CLOSE delete spy_log_instance
#define SPY_LOG_JOINTS(sensors,actuators) spy_log_instance->logJointValues(sensors,actuators)
#define SPY_LOG_COM(proxy) spy_log_instance->logCoM(proxy)
#define SPY_LOG_FOOT(proxy) spy_log_instance->logFoot(proxy)

#endif // LOG_DEBUG_H
