#pragma once
#include "GateServiceHandle.h"
#include "ace/Acceptor.h"
#include "ace/SOCK_Acceptor.h"

//此处可以使用ACE_Cached_Connect_Strategy来优化
typedef ACE_Acceptor<GateServiceHandle, ACE_SOCK_ACCEPTOR> GateAcceptor;
