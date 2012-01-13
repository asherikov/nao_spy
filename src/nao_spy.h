/**
 * @file
 * @author Antonio Paolillo
 * @author Dimitar Dimitrov
 * @author Alexander Sherikov
 */


#ifndef NAO_SPY_H
#define NAO_SPY_H


//----------------------------------------
// INCLUDES
//----------------------------------------
#include <alcore/alptr.h>
#include <alcommon/alproxy.h>
#include <alcommon/albroker.h>
#include <alcommon/almodule.h>

#include <alcore/alerror.h>

// Use DCM proxy
#include <alproxies/dcmproxy.h>
#include <alproxies/almotionproxy.h>

// Used to read values of ALMemory directly in RAM
#include <almemoryfastaccess/almemoryfastaccess.h>

#include <boost/bind.hpp>


#include <alcore/alptr.h> // ALPtr
#include <alcommon/almodule.h> // ALModule, ProcessSignalConnection (almodulesynchronization.h)
#include <alcommon/albroker.h> // ALBroker

#include <almemoryfastaccess/almemoryfastaccess.h> // ALMemoryFastAccess

#include <alproxies/dcmproxy.h> // DCMProxy

#include <alvalue/alvalue.h> // ALValue


#include <string> // string

#include "log_debug.h"
#include "joints_sensors_id.h"

//----------------------------------------
// DEFINITIONS
//----------------------------------------


using namespace AL;
using namespace std;



/**
 * @brief The main walking module class.
 */
class nao_spy : public ALModule
{
public:
    // constructors / destructors
    nao_spy(ALPtr<ALBroker> broker, const string& name);
    ~nao_spy ();


    // is called automatically when a library is loaded 
    void init();
    void spy();


private:
    // initialization
    void initFastRead ();

    // Callback called by the DCM every 10ms
    void callbackEveryCycle_walk();


    // Used for postprocess sync with the DCM
    ProcessSignalConnection fDCMPostProcessConnection;

    // Used for fast memory access
    ALPtr<ALMemoryFastAccess> accessSensorValues;
    ALPtr<ALMemoryFastAccess> accessActuatorValues;

    ALPtr<DCMProxy> dcmProxy;
    AL::ALPtr<AL::ALMotionProxy> motionProxy;
};

#endif  // NAO_SPY_H
