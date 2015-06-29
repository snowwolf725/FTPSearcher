// CkSshTunnel.h: interface for the CkSshTunnel class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CkSshTunnel_H
#define _CkSshTunnel_H

#pragma once

#include "CkString.h"
class CkSshTunnelProgress;
#include "CkObject.h"

class CkSshKey;

#pragma pack (push, 8) 

// CLASS: CkSshTunnel
class CkSshTunnel  : public CkObject
{
	void *m_impl;
	bool m_utf8;	// If true, all input "const char *" parameters are utf-8, otherwise they are ANSI strings.

	// Don't allow assignment or copying these objects.
	CkSshTunnel(const CkSshTunnel &);
	CkSshTunnel &operator=(const CkSshTunnel &);

	unsigned long nextIdx(void);
	unsigned long m_resultIdx;
	CkString m_resultString[10];

    public:
	void *getImpl(void) const;

	CkSshTunnel(void *impl);

	CkSshTunnel();
	virtual ~CkSshTunnel();

	// BEGIN PUBLIC INTERFACE
	bool get_Utf8(void) const;
	void put_Utf8(bool b);

	// Error log retrieval and saving (these methods are common to all Chilkat VC++ classes.)
	bool SaveLastError(const char *filename);
    void LastErrorXml(CkString &str);
    void LastErrorHtml(CkString &str);
    void LastErrorText(CkString &str);

    const char *lastErrorText(void);
    const char *lastErrorXml(void);
    const char *lastErrorHtml(void);
	

	// UNLOCKCOMPONENT_BEGIN
	bool UnlockComponent(const char *unlockCode);
	// UNLOCKCOMPONENT_END
	// SSHLOGIN_BEGIN
	void get_SshLogin(CkString &str);
	const char *sshLogin(void);
	void put_SshLogin(const char *newVal);
	// SSHLOGIN_END
	// SSHPASSWORD_BEGIN
	void get_SshPassword(CkString &str);
	const char *sshPassword(void);
	void put_SshPassword(const char *newVal);
	// SSHPASSWORD_END
	// CONNECTLOG_BEGIN
	void get_ConnectLog(CkString &str);
	const char *connectLog(void);
	void put_ConnectLog(const char *newVal);
	// CONNECTLOG_END
	// DESTHOSTNAME_BEGIN
	void get_DestHostname(CkString &str);
	const char *destHostname(void);
	void put_DestHostname(const char *newVal);
	// DESTHOSTNAME_END
	// SSHSERVERHOSTNAME_BEGIN
	void get_SshHostname(CkString &str);
	const char *sshHostname(void);
	void put_SshHostname(const char *newVal);
	// SSHSERVERHOSTNAME_END
	// SSHSERVERPORT_BEGIN
	int get_SshPort(void);
	void put_SshPort(int newVal);
	// SSHSERVERPORT_END
	// DESTPORT_BEGIN
	int get_DestPort(void);
	void put_DestPort(int newVal);
	// DESTPORT_END
	// ISACCEPTING_BEGIN
	bool get_IsAccepting(void);
	// ISACCEPTING_END
	// STOPALLTUNNELS_BEGIN
	bool StopAllTunnels(int maxWaitMs);
	// STOPALLTUNNELS_END
	// GETTUNNELSXML_BEGIN
	bool GetTunnelsXml(CkString &outStr);
	const char *getTunnelsXml(void);
	// GETTUNNELSXML_END
	// STOPACCEPTING_BEGIN
	bool StopAccepting(void);
	// STOPACCEPTING_END
	// BEGINACCEPTING_BEGIN
	bool BeginAccepting(int listenPort);
	// BEGINACCEPTING_END
	// SETSSHAUTHENTICATIONKEY_BEGIN
	bool SetSshAuthenticationKey(CkSshKey &key);
	// SETSSHAUTHENTICATIONKEY_END
	// LISTENBINDIPADDRESS_BEGIN
	void get_ListenBindIpAddress(CkString &str);
	const char *listenBindIpAddress(void);
	void put_ListenBindIpAddress(const char *newVal);
	// LISTENBINDIPADDRESS_END
	// OUTBOUNDBINDIPADDRESS_BEGIN
	void get_OutboundBindIpAddress(CkString &str);
	const char *outboundBindIpAddress(void);
	void put_OutboundBindIpAddress(const char *newVal);
	// OUTBOUNDBINDIPADDRESS_END
	// OUTBOUNDBINDPORT_BEGIN
	int get_OutboundBindPort(void);
	void put_OutboundBindPort(int newVal);
	// OUTBOUNDBINDPORT_END
	// MAXPACKETSIZE_BEGIN
	int get_MaxPacketSize(void);
	void put_MaxPacketSize(int newVal);
	// MAXPACKETSIZE_END
	// TCPNODELAY_BEGIN
	bool get_TcpNoDelay(void);
	void put_TcpNoDelay(bool newVal);
	// TCPNODELAY_END

	// SSHTUNNEL_INSERT_POINT

	// END PUBLIC INTERFACE


};
#pragma pack (pop)


#endif


