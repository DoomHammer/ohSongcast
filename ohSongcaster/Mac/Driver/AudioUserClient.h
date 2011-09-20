#ifndef HEADER_AUDIOUSERCLIENT
#define HEADER_AUDIOUSERCLIENT


#include <IOKit/IOUserClient.h>
#include "AudioDevice.h"
#include "AudioDeviceInterface.h"

#define AudioUserClient BRANDING_AUDIOUSERCLIENT_CLASS


class AudioUserClient : public IOUserClient
{
    OSDeclareDefaultStructors(AudioUserClient);

public:
    virtual bool start(IOService* aProvider);
    virtual void stop(IOService* aProvider);
    virtual IOReturn clientClose();
    virtual IOReturn clientDied();

private:
    static const IOExternalMethodDispatch iMethods[eNumDriverMethods];

    virtual IOReturn externalMethod(uint32_t aSelector, IOExternalMethodArguments* aArgs, IOExternalMethodDispatch* aDispatch, OSObject* aTarget, void* aReference);

    static IOReturn DispatchOpen(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs);
    static IOReturn DispatchClose(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs);
    static IOReturn DispatchSetActive(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs);
    static IOReturn DispatchSetEndpoint(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs);
    static IOReturn DispatchSetTtl(AudioUserClient* aTarget, void* aReference, IOExternalMethodArguments* aArgs);

    IOReturn Open();
    IOReturn Close();
    IOReturn SetActive(uint64_t aActive);
    IOReturn SetEndpoint(uint64_t aIpAddress, uint64_t aPort);
    IOReturn SetTtl(uint64_t aTtl);

    IOReturn DeviceOk();
    
private:
    AudioDevice* iDevice;
};


#endif // HEADER_AUDIOUSERCLIENT


