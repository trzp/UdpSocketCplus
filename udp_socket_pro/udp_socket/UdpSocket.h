#pragma once
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#pragma comment(lib,"WS2_32.lib")

//��Ҫ����Ŀ����-> c/c++ -> Ԥ������ -> Ԥ����������: ��Ӷ��� _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

class UdpSocket
{
private:
	SOCKET sock;
	bool is_server = false;

public:
	SOCKADDR_IN remote_addr;

public:
	~UdpSocket();
	UdpSocket();

	void srv_bind(string local_ip, short local_port);	//�������󶨡���Ϊ������ʹ��ʱ���á�
	void set_remote_addr(string remote_ip, short port);	//����Զ�̵�ַ����sendǰ������ʱ���ã�����Ŀ���ַ��

	int send(char* buf, int send_len);
	int send(string buf);
	int recv(char* buf,SOCKADDR_IN* addr);	//buf �������ݵ�buffer, addrԶ�̷������ݼ�����ĵ�ַ
	int recv(char* buf);
	void close();	//����ʱ�ᱻ���ã�close���Բ�����ʾ����
};