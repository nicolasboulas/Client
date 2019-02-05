#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <windows.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

class client
{
	char* receptionBuffer;
	char* sendingBuffer;
	WSADATA WSAData;
	SOCKET sock;
	SOCKADDR_IN sin;
	string ipAddress = "192.168.43.137";


public:
	boolean isMyTurn = false;
	client();
	int connection();
	boolean sendCase(int x, int y);
	int* receiveCase();
	int disconnection();
	void askTurn();
	void setBufferData(char* data);
	void clearBuffers();
};
