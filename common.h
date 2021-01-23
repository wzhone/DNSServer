#pragma once
#include <iostream>
#include <thread>
#include <algorithm>
#include <assert.h>
#include <thread>

#ifdef __linux__
	#define PLATFORM LINUX
	#define LINUX
	#define SOCKET int
	#define SOCKET_ERROR (-1)  
	#include <endian.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/ioctl.h>
	#include <netdb.h>
	#include <netinet/ip.h>
	#include <netinet/in.h>
	#include <string.h>	
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <fcntl.h> 
	#include <errno.h> 

	#define ULONG long
	#define INVALID_SOCKET  (SOCKET)(~0)
	typedef int socket_t;

	//error function return value
	namespace socketError {
		const int timeout = ETIMEDOUT;
		const int hostdown = EHOSTDOWN;
	};
#endif

#ifdef _WIN32

	#include <WinSock2.h>
	#include <ws2tcpip.h>
	#pragma comment (lib,"ws2_32")
	#define MSG_NOSIGNAL 0
	typedef SOCKET socket_t;
	//error function return value
	namespace socketError {
		const int timeout = WSAETIMEDOUT;
		const int hostdown = WSAEHOSTDOWN;
	};

#endif