#include "common.h"
#include "Protocol.h"
#include "network.h"

//https://www.rfc-editor.org/rfc/inline-errata/rfc1035.html

using std::cout;
using std::cin;
using std::endl;

bool stop = false;


void encodeHeader() {

}

void handler(socket_t socket,sockaddr_in addr) {

	char buf[1024];
	sockaddr_in clientAddr;
	int nLen = sizeof(addr);
	while (!stop)
	{
		int nRecv = recvfrom(socket, buf, 1024, 0, (sockaddr*)&clientAddr, &nLen);
		if (nRecv < 12) continue;
		DNSHeader* header = (DNSHeader*)&buf;

		if (GETFLAGANSWER(header->flags) == 1) {
			//query
		}else {
			//response
		}
		


		/*if (nRecv > 0)
		{
			buf[nRecv] = '\0';
		}*/
	}


//DNSHeader header;
//header.id = 0x0001;
//SETFLAGQUERY(header.flags);
//header.n_answer = 1;
//Header2BigEndian(header);
	
}


int main() {
	net::init();

	socket_t socketHandle = net::socket(udp);
	sockaddr_in addrin = net::make_addr(53);
	if (socketHandle == socketRet::invalid){
		cout << "Failed create socket: " << net::lastError();
		return -1;
	}
	if (bind(socketHandle, (sockaddr*)&addrin, sizeof(addrin))== -1){
		cout << "Failed bind: " << net::lastError();
		return -2;
	}

	std::thread handler_thread(handler, socketHandle, addrin);
	while (!stop) {
		char buf[100];
		cin.getline(buf,100);

		if (strcmp(buf, "stop") == 0) {
			stop = true;
			net::close(socketHandle);
			cout << "Closing..." << endl;
			handler_thread.join();
		}else {
			cout << "invaild command" << endl;
		}
	}

	return 0;
}

