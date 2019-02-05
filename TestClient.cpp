#include "pch.h"
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <windows.h>
#include "Client.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main() {
	
	client client;
	client.connection();
	client.sendCase(1, 2);

	//client.askTurn;
	//cout << client.isMyTurn << endl;
	int* cases = client.receiveCase();
	cout << cases[0] << " " << cases[1] << endl;
	while (1);
	Sleep(2500);
//	client.disconnection();
	return 0;
}
