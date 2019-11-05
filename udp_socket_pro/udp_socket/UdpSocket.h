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

public:
	SOCKADDR_IN remote_addr;

public:
	~UdpSocket();
	UdpSocket();

	void srv_bind(string local_ip, short local_port);	//服务器绑定。作为服务器使用时调用。
	void set_remote_addr(string remote_ip, short port);	//设置远程地址。在send前可以随时调用，更改目标地址。

	int send(char* buf, int send_len);
	int send(string buf);
	int recv(char* buf,SOCKADDR_IN* addr);	//buf 接受数据的buffer, addr远程发送数据计算机的地址
	int recv(char* buf);
	void close();	//析构时会被调用，close可以不被显示调用
};