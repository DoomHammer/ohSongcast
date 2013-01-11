#include <OpenHome/OhNetTypes.h>
#include <OpenHome/Net/Core/OhNet.h>
#include <OpenHome/Private/Ascii.h>
#include <OpenHome/Private/Maths.h>
#include <OpenHome/Private/Thread.h>
#include <OpenHome/Private/OptionParser.h>
#include <OpenHome/Private/Debug.h>
#include <OpenHome/Private/TestFramework.h>

#include <vector>
#include <stdio.h>

#include "ReceiverManager3.h"


#ifdef _WIN32
#define CDECL __cdecl
#else
#define CDECL 
#endif


namespace OpenHome {
namespace Av {

	class ReceiverManager3Logger : IReceiverManager3Handler
	{
	public:
		ReceiverManager3Logger(Net::CpStack& aCpStack, const Brx& aUri);
		virtual void ReceiverAdded(ReceiverManager3Receiver& aReceiver);
		virtual void ReceiverChanged(ReceiverManager3Receiver& aReceiver);
		virtual void ReceiverRemoved(ReceiverManager3Receiver& aReceiver);
		virtual void ReceiverVolumeControlChanged(ReceiverManager3Receiver& aReceiver);
		virtual void ReceiverVolumeChanged(ReceiverManager3Receiver& aReceiver);
		virtual void ReceiverMuteChanged(ReceiverManager3Receiver& aReceiver);
		virtual void ReceiverVolumeLimitChanged(ReceiverManager3Receiver& aReceiver);
		~ReceiverManager3Logger();
	private:
		ReceiverManager3* iReceiverManager;
	};

} // namespace Av
} // namespace OpenHome

using namespace OpenHome;
using namespace OpenHome::Net;
using namespace OpenHome::TestFramework;
using namespace OpenHome::Av;

// ohz://239.255.255.250:51972/0026-0f21-88aa

ReceiverManager3Logger::ReceiverManager3Logger(Net::CpStack& aCpStack, const Brx& aValue)
{
	iReceiverManager = new ReceiverManager3(aCpStack, *this, aValue, Brx::Empty());
}

ReceiverManager3Logger::~ReceiverManager3Logger()
{
	delete (iReceiverManager);
}

void ReceiverManager3Logger::ReceiverAdded(ReceiverManager3Receiver& aReceiver)
{
    Print("Added   ");
    Print(aReceiver.Room());
    Print("(");
    Print(aReceiver.Group());
    Print(") ");

	switch(aReceiver.Status()) {
	case ReceiverManager3Receiver::eDisconnected:
		Print("Disconnected");
		break;
	case ReceiverManager3Receiver::eConnecting:
		Print("Connecting");
		break;
	case ReceiverManager3Receiver::eConnected:
		Print("Connected");
		break;
	}

	Print("\n");
}

void ReceiverManager3Logger::ReceiverChanged(ReceiverManager3Receiver& aReceiver)
{
    Print("Changed ");
    Print(aReceiver.Room());
    Print("(");
    Print(aReceiver.Group());
    Print(") ");

	switch(aReceiver.Status()) {
	case ReceiverManager3Receiver::eDisconnected:
		Print("Disconnected");
		break;
	case ReceiverManager3Receiver::eConnecting:
		Print("Connecting");
		break;
	case ReceiverManager3Receiver::eConnected:
		Print("Connected");
		break;
	}

    Print("\n");
}

void ReceiverManager3Logger::ReceiverRemoved(ReceiverManager3Receiver& aReceiver)
{
    Print("Removed ");
    Print(aReceiver.Room());
    Print("(");
    Print(aReceiver.Group());
    Print(")");
    Print("\n");
}

void ReceiverManager3Logger::ReceiverVolumeControlChanged(ReceiverManager3Receiver& aReceiver)
{
	Print("Vol Control Changed ");
	Print(aReceiver.Room());
	Print("(");
	Print(aReceiver.Group());
	Print("): ");
    aReceiver.HasVolumeControl() ? printf("Yes\n") : printf("No\n");
	if(aReceiver.HasVolumeControl())
	{
		Print("Vol      ");
		Bws<Ascii::kMaxUintStringBytes> bufferVol;
		Ascii::AppendDec(bufferVol, aReceiver.Volume());
		Print(bufferVol);
		Print("\n");
		Print("Mute      ");
		Bws<Ascii::kMaxUintStringBytes> bufferMute;
		Ascii::AppendDec(bufferMute, aReceiver.Mute());
		Print(bufferMute);
		Print("\n");
		Print("Vol Limit      ");
		Bws<Ascii::kMaxUintStringBytes> bufferVolLim;
		Ascii::AppendDec(bufferVolLim, aReceiver.VolumeLimit());
		Print(bufferVolLim);
		Print("\n");
	}
}

void ReceiverManager3Logger::ReceiverVolumeChanged(ReceiverManager3Receiver& aReceiver)
{
	Print("Vol Changed ");
	Print(aReceiver.Room());
	Print("(");
	Print(aReceiver.Group());
	Print("): ");
	Bws<Ascii::kMaxUintStringBytes> buffer;
	Ascii::AppendDec(buffer, aReceiver.Volume());
    Print(buffer);
    Print("\n");
}

void ReceiverManager3Logger::ReceiverMuteChanged(ReceiverManager3Receiver& aReceiver)
{
	Print("Mute Changed ");
	Print(aReceiver.Room());
	Print("(");
	Print(aReceiver.Group());
	Print("): ");
	Bws<Ascii::kMaxUintStringBytes> buffer;
	Ascii::AppendDec(buffer, aReceiver.Mute());
    Print(buffer);
    Print("\n");
}

void ReceiverManager3Logger::ReceiverVolumeLimitChanged(ReceiverManager3Receiver& aReceiver)
{
	Print("Vol Limit Changed ");
	Print(aReceiver.Room());
	Print("(");
	Print(aReceiver.Group());
	Print("): ");
	Bws<Ascii::kMaxUintStringBytes> buffer;
	Ascii::AppendDec(buffer, aReceiver.VolumeLimit());
    Print(buffer);
    Print("\n");
}

int CDECL main(int aArgc, char* aArgv[])
{
    OptionParser parser;
    OptionUint optionDuration("-d", "--duration", 15, "Number of seconds to run the test");
    parser.AddOption(&optionDuration);
    OptionString optionUri("-u", "--uri", Brx::Empty(), "Uri to monitor");
    parser.AddOption(&optionUri);
    if (!parser.Parse(aArgc, aArgv)) {
        return 1;
    }
    InitialisationParams* initParams = InitialisationParams::Create();
    Library* lib = new Library(initParams);
    std::vector<NetworkAdapter*>* subnetList = lib->CreateSubnetList();
    TIpAddress subnet = (*subnetList)[0]->Subnet();
    Library::DestroySubnetList(subnetList);
    CpStack* cpStack = lib->StartCp(subnet);

    // Debug::SetLevel(Debug::kTopology);

	ReceiverManager3Logger* logger = new ReceiverManager3Logger(*cpStack, Brx::Empty());
	
    Blocker* blocker = new Blocker(lib->Env());
    blocker->Wait(optionDuration.Value());
	delete blocker;
	
	delete logger;
	delete lib;
}
