#pragma once
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#pragma comment(lib,"WS2_32.lib")

//需要在项目属性-> c/c++ -> 预处理器 -> 预处理器定义: 添加定义 _WINSOCK_DEPRECATED_NO_WARNINGS

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
	UdpSocket(string local_ip,short local_port);	//作为服务端是绑定到的ip和端口（接受数据，也可发送数据）
	UdpSocket();	//仅作为客户端（发送数据）

	int send_to(char* buf, int send_len,string ip, short port);
	int send_to(string buf, string ip, short port);
	int recv_from(char* buf,SOCKADDR_IN* addr);	//buf 接受数据的buffer, addr远程发送数据计算机的地址
	int recv_from(char* buf);
	void close();	//析构时会被调用，close可以不被显示调用
};