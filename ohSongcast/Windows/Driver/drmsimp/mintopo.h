
/*++

Copyright (c) 1997-2000  Microsoft Corporation All Rights Reserved

Module Name:

    minitopo.h

Abstract:

    Declaration of topology miniport.

--*/

#ifndef _MSVAD_MINTOPO_H_
#define _MSVAD_MINTOPO_H_

#include "basetopo.h"

//=============================================================================
// Classes
//=============================================================================

///////////////////////////////////////////////////////////////////////////////
// CMiniportTopology 
//   

class CMiniportTopology : 
    public CMiniportTopologyMSVAD,
    public IMiniportTopology,
    public CUnknown
{
public:
    DECLARE_STD_UNKNOWN();
    DEFINE_STD_CONSTRUCTOR(CMiniportTopology);
    ~CMiniportTopology();

    IMP_IMiniportTopology;

	void CreateWaveMiniport();
	void DestroyWaveMiniport();
	NTSTATUS PropertyHandlerWave(IN PPCPROPERTY_REQUEST PropertyRequest);

private:
	CMiniportWaveCyclic* m_pWaveMiniport;
};

typedef CMiniportTopology *PCMiniportTopology;

extern NTSTATUS PropertyHandler_Jack(IN PPCPROPERTY_REQUEST PropertyRequest);

#endif

