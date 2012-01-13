/**
 * @file
 * @author Antonio Paolillo
 * @author Dimitar Dimitrov
 * @author Alexander Sherikov
 */

#include "nao_spy.h"


/**
 * Constructor for nao_spy object
 * @param broker The parent broker
 * @param name The name of the module
 */
nao_spy::nao_spy(ALPtr<ALBroker> broker, const string& name) : 
    ALModule(broker, name),
    accessSensorValues (ALPtr<ALMemoryFastAccess>(new ALMemoryFastAccess())),
    accessActuatorValues (ALPtr<ALMemoryFastAccess>(new ALMemoryFastAccess()))
{
    setModuleDescription("Collect sensor values while a robot is walking.");

    functionName( "spy", getName() , "spy");
    BIND_METHOD( nao_spy::spy );
}



/**
 * Destructor for nao_spy object
 */
nao_spy::~nao_spy()
{
}



// Initialisation of ALmemory fast access, DCM commands, Alias, stiffness, ...
/**
 * @brief 
 */
void nao_spy::init()
{
    bool isDCMRunning;


// Is the DCM running ?
    try
    {
        isDCMRunning = getParentBroker()->getProxy("ALLauncher")->call<bool>("isModulePresent", std::string("DCM"));
    }
    catch (ALError& e)
    {
        throw ALERROR(getName(), __FUNCTION__, "Error when connecting to DCM : " + e.toString());
    }
    if (!isDCMRunning)
    {
        throw ALERROR(getName(), __FUNCTION__, "Error no DCM running ");
    }


// proxies
    try
    {
        // Get the DCM proxy
        dcmProxy = getParentBroker()->getDcmProxy();
    }
    catch (ALError& e)
    {
        throw ALERROR(getName(), __FUNCTION__, "Impossible to create DCM Proxy : " + e.toString());
    }

    try
    {
        motionProxy = getParentBroker()->getMotionProxy();
    }
    catch(AL::ALError &e)
    {
        throw ALERROR(getName(), __FUNCTION__, "Impossible to create Motion Proxy : " + e.toString());
    }

    initFastRead();
}



void nao_spy::spy()
{
    SPY_LOG_OPEN;
    try
    {
        fDCMPostProcessConnection =
            getParentBroker()->getProxy("DCM")->getModule()->atPostProcess
            (boost::bind(&nao_spy::callbackEveryCycle_walk, this));
    }
    catch (const AL::ALError &e)
    {
        throw ALERROR(getName(), __FUNCTION__, 
                "Error when connecting to DCM postProccess: " + e.toString());
    }

    motionProxy->setStiffnesses("Body", 1.0f);
    motionProxy->walkInit();
    motionProxy->walkTo(0.4f, 0.0f, 0.0f);
    motionProxy->setStiffnesses("Body", 0.0f);
    // Remove the postProcess call back connection
    fDCMPostProcessConnection.disconnect();
    SPY_LOG_CLOSE;
}



/**
 * @brief 
 */
void nao_spy::callbackEveryCycle_walk()
{
    SPY_TIMER;
    SPY_LOG_JOINTS(accessSensorValues, accessActuatorValues);
    SPY_LOG_COM(motionProxy);
    SPY_LOG_FOOT(motionProxy);
}
