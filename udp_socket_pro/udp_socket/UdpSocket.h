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
	
private:
	SOCKADDR_IN gen_addr(char ip[], short port);

public:
	~UdpSocket();
	UdpSocket(string local_ip,short local_port);	//��Ϊ������ǰ󶨵���ip�Ͷ˿ڣ��������ݣ�Ҳ�ɷ������ݣ�
	UdpSocket();	//����Ϊ�ͻ��ˣ��������ݣ�

	int send_to(char* buf, int send_len,string ip, short port);
	int send_to(string buf, string ip, short port);
	int recv_from(char* buf,SOCKADDR_IN* addr);	//buf �������ݵ�buffer, addrԶ�̷������ݼ�����ĵ�ַ
	int recv_from(char* buf);
	void close();	//����ʱ�ᱻ���ã�close���Բ�����ʾ����
};