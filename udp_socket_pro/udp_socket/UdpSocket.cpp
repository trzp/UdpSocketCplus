#include "UdpSocket.h"

UdpSocket::UdpSocket() //基本初始化
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

void UdpSocket::srv_bind(string local_ip, short local_port)
{
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

void UdpSocket::set_remote_addr(string local_ip, short port)
{
	char* cip = (char*)local_ip.data();
	this->remote_addr.sin_family = AF_INET;
	this->remote_addr.sin_port = htons(port);
	this->remote_addr.sin_addr.S_un.S_addr = inet_addr(cip);
}

int UdpSocket::send(char* buf, int send_len)
{
	int nRet = sendto(this->sock, buf, send_len, 0, (SOCKADDR*)& this->remote_addr, sizeof(SOCKADDR));
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

int UdpSocket::send(string buf)
{
	char* tem = (char*)buf.data();

	int nRet = sendto(this->sock, tem, buf.length(), 0, (SOCKADDR*)&this->remote_addr, sizeof(SOCKADDR));
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

int UdpSocket::recv(char* buf,SOCKADDR_IN* addr)
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

int UdpSocket::recv(char* buf)
{
	SOCKADDR_IN addr;
	return this->recv(buf, &addr);
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