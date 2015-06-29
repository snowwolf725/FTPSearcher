// CkTarProgress.h: interface for the CkTarProgress class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CKTARROGRESS_H
#define _CKTARPROGRESS_H

#pragma once

#pragma pack (push, 8) 

class CkTarProgress  
{
    public:
	CkTarProgress() { }
	virtual ~CkTarProgress() { }

	// Called periodically to check to see if the method call should be aborted.
	virtual void AbortCheck(bool *abort) { }

};
#pragma pack (pop)

#endif
