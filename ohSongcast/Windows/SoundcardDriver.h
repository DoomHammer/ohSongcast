#ifndef HEADER_SOUNDCARDDRIVER
#define HEADER_SOUNDCARDDRIVER

#define INITGUID  // For PKEY_AudioEndpoint_GUID

#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <Windows.h>
#include <Mmdeviceapi.h>

#include "../../Ohm.h"
#include "../../OhmSenderDriver.h"

namespace OpenHome {
namespace Av {

class Songcast;

class OhmSenderDriverWindows : public IOhmSenderDriver, public IMMNotificationClient
{
public:
	OhmSenderDriverWindows(const char* aDomain, const char* aManufacturer, TBool aEnabled);
	void SetSongcast(Songcast& aSongcast);
	~OhmSenderDriverWindows();
private:    
	TBool FindDriver(const char* aDomain);
	TBool FindEndpoint(const char* aManufacturer);
	void SetDefaultAudioPlaybackDevice();
	void SetEndpointEnabled(TBool aValue);

	// IOhmSenderDriver
	virtual void SetEnabled(TBool aValue);
	virtual void SetEndpoint(const Endpoint& aEndpoint, TIpAddress aAdapter);
	virtual void SetActive(TBool aValue);
	virtual void SetTtl(TUint aValue);
	virtual void SetLatency(TUint aValue);
	virtual void SetTrackPosition(TUint64 aSampleStart, TUint64 aSamplesTotal);
	virtual void Resend(const Brx& aFrames);

	// IMMNotificationClient
    ULONG STDCALL AddRef();
    ULONG STDCALL Release();
    HRESULT STDCALL QueryInterface(REFIID aId, void** aInterface);

	HRESULT STDCALL OnDefaultDeviceChanged(EDataFlow aFlow, ERole aRole, LPCWSTR aDeviceId);
    HRESULT STDCALL OnDeviceAdded(LPCWSTR aDeviceId);
    HRESULT STDCALL OnDeviceRemoved(LPCWSTR aDeviceId);
    HRESULT STDCALL OnDeviceStateChanged(LPCWSTR aDeviceId, DWORD aNewState);
    HRESULT STDCALL OnPropertyValueChanged(LPCWSTR aDeviceId, const PROPERTYKEY akey);

private:
	HANDLE iHandle;
	WCHAR iEndpointId[100];
	TBool iEnabled;
	ULONG iRefCount;
	Songcast* iSongcast;
	IMMDeviceEnumerator* iDeviceEnumerator;
};

} // namespace Av
} // namespace OpenHome

#endif // HEADER_SOUNDCARDDRIVER

