#ifndef HEADER_AUDIODEVICEINTERFACE
#define HEADER_AUDIODEVICEINTERFACE


enum EDriverMethod
{
    eOpen,              // ()
    eClose,             // ()
    eSetActive,         // (uint64_t aActive)
    eSetEndpoint,       // (uint64_t aIpAddress, uint64_t aPort)
    eSetTtl,            // (uint64_t aTtl)
    eNumDriverMethods
};


#endif // HEADER_AUDIODEVICEINTERFACE


