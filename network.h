#pragma once
#include "common.h"

typedef std::pair<socket_t, sockaddr_in> netobject;
using std::pair;


enum socketType {
	udp = SOCK_DGRAM,
	tcp = SOCK_STREAM
};

// recv&send function return value
enum socketRet {
	error = SOCKET_ERROR,
	closed = 0,
	invalid = INVALID_SOCKET,
};



class net {
public:

	//fill sockaddr_in struct
	static sockaddr_in make_addr(uint16_t port, const char* ip = nullptr);

	//create legal and nitialization socket handle
	static socket_t socket(socketType type);

	static unsigned short getPort(sockaddr_in addr);
	static void timeout(socket_t socket, long  millisecond);
	static void setclogState(socket_t s, bool block = true);
	static std::string getsIp(sockaddr_in&);  // sockaddr_in => binstream
	static std::string getsIp(uint32_t ip);   // int => binstream
	static uint32_t getnIp(sockaddr_in&);// sockaddr_in => int
	static int32_t close(socket_t socket);//close socket
	static int lastError();//get last error
	static bool recvInsist(socket_t sock,char* buf,int size);
	static bool sendInsist(socket_t sock,const char* buf,int size);
	static void init();//initialization environment

	//发送数据包 tcp底层函数
	static int send(socket_t dest, const char* buf, int size);
	static int send(socket_t dest, const char* buf);
	static int recv(socket_t dest, char* buf, int size);

	net() = delete;
	~net() = delete;
};