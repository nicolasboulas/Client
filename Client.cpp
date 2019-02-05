#include "pch.h"
#include "Client.h"



client::client()
{

	receptionBuffer = new char(5);
	sendingBuffer = new char(2);

	int wsok = WSAStartup(MAKEWORD(2, 0), &WSAData);
	if (wsok != 0)
	{
		std::cout << "Erreur WSAStratup" << std::endl;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		std::cout << "Erreur socket" << std::endl;
	}

	int pton = inet_pton(AF_INET, ipAddress.c_str(), &sin.sin_addr);
	if (pton == -1) {
		cout << WSAGetLastError();
	}
	else if (pton == 0) {
		cout << "ip invalide";
	}

	sin.sin_family = AF_INET;
	sin.sin_port = htons(5150);
}

int client::connection() {
	int i = connect(sock, (SOCKADDR *)&sin, sizeof(sin));
	if (i == -1) {
		cout << "erreur de connexion";
	}
	return i;
}

boolean client::sendCase(int x, int y) {
	char données[2] = { static_cast<char>(x + 48), static_cast<char>(y + 48) };
	int confirmation = 0;
	char test[10] = "first";
	setBufferData(test);
	send(sock, sendingBuffer, 6, 0);
	recv(sock, test, 10, 0);
	cout << test << endl;
	/*recv(sock, receptionBuffer, sizeof(receptionBuffer), 0);
	confirmation = receptionBuffer[0] - 48;
	cout << confirmation << endl;*/

	return confirmation == 1;
}

int * client::receiveCase()
{
	int coordonnées[2];
	recv(sock, receptionBuffer, sizeof(receptionBuffer), 0);
	coordonnées[0] = receptionBuffer[0] - 48;
	coordonnées[1] = receptionBuffer[1] - 48;

	return coordonnées;
}



int client::disconnection() {
	closesocket(sock);
	WSACleanup();
	return 0;
}

void client::askTurn()
{
	char buffer[5];
	send(sock, "turn", 4, 0);
	recv(sock, buffer, sizeof(buffer), 0);
	if (buffer[0] == 't') {
		isMyTurn = true;
	}
}

//la taille de date doit etre inferieure a celle du buffer de destination
void client::setBufferData(char* data) {
	for (int i = 0; i <= sizeof(data); i++) {
		sendingBuffer[i] = data[i];
	}
	
	sendingBuffer[sizeof(sendingBuffer)+1] = '\0';
	cout << sendingBuffer;
}
