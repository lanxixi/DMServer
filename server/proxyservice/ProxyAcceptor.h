#pragma once
#include "ProxyServiceHandle.h"
#include "ace/Acceptor.h"
#include "ace/SOCK_Acceptor.h"

//此处可以使用ACE_Cached_Connect_Strategy来优化
typedef ACE_Acceptor<ProxyServiceHandle, ACE_SOCK_ACCEPTOR> ProxyAcceptor;
