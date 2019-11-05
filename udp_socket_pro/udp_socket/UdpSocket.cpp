#include "UdpSocket.h"


UdpSocket::UdpSocket(string local_ip,short local_port)
{
	WSAData wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		throw "[Error] WSA startup failure";
	}

	this->sock = socket(AF_INET, SOCK_DGRAM,0);
	if (sock == SOCKET_ERROR) 
	{
		throw WSAGetLastError();
	}

	char* tem_ip = (char*)local_ip.data();
	SOCKADDR_IN local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(local_port);
	local_addr.sin_addr.s_addr = inet_addr(tem_ip);

	//绑定到指定地址
	if (bind(this->sock, (SOCKADDR*)& local_addr, sizeof(local_addr)) == SOCKET_ERROR)
	{
		throw "[socket error] bing error";
	}
	this->is_server = true;
}

UdpSocket::UdpSocket()
{
	WSAData wsd;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		throw "[Error] WSA startup failure";
	}

	this->sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == SOCKET_ERROR)
	{
		throw WSAGetLastError();
	}
}

SOCKADDR_IN UdpSocket::gen_addr(char ip[], short port)
{
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ip);
	return addr;
}

int UdpSocket::send_to(char* buf, int send_len, string ip, short port)
{
	SOCKADDR_IN addr;
	char* cip = (char*)ip.data();
	addr = this->gen_addr(cip, port);
	int nRet = sendto(this->sock, buf, send_len, 0, (SOCKADDR*)& addr, sizeof(SOCKADDR));
	if (nRet == SOCKET_ERROR)
	{
		cout << "[sendto Error] " << WSAGetLastError() << endl;
		return 0;
	}
	else
	{
		return 1;
	}
}

int UdpSocket::send_to(string buf, string ip, short port)
{
	char* cip = (char*)ip.data();
	char* tem = (char*)buf.data();

	SOCKADDR_IN addr;
	addr = this->gen_addr(cip, port);

	int nRet = sendto(this->sock, tem, buf.length(), 0, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	if (nRet == SOCKET_ERROR) 
	{
		cout << "[sendto Error] " << WSAGetLastError() << endl;
		return 0;
	}
	else
	{
		return 1;
	}
}

int UdpSocket::recv_from(char* buf,SOCKADDR_IN* addr)
{
	if (!this->is_server)
	{
		cout << "[warning] UdpSocket did not initialize as server!" << endl;
		return 0;
	}

	int addr_len = sizeof(*addr);
	int nRet = recvfrom(this->sock,buf,strlen(buf),0,(SOCKADDR*)addr, &addr_len);

	if (nRet == SOCKET_ERROR) 
	{
		cout << "[socket Error] recvfrom error " << WSAGetLastError() << endl;
		return 0;
	}
	else
	{
		return 1;
	}
}

int UdpSocket::recv_from(char* buf)
{
	SOCKADDR_IN addr;
	return this->recv_from(buf, &addr);
}

void UdpSocket::close()
{
	closesocket(this->sock);
	WSACleanup();
}


UdpSocket::~UdpSocket()
{
	try
	{
		this->close();
	}
	catch(int e)
	{
	}
}