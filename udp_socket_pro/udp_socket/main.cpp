#include <iostream>
#include "UdpSocket.h"
#include <time.h>

int main()
{
	UdpSocket udp_sock;
	udp_sock.srv_bind("127.0.0.1", 9001);
	char inbuf[128];

	udp_sock.recv(inbuf);
	cout << inbuf << endl;

	udp_sock.set_remote_addr("127.0.0.1", 6000);
	udp_sock.send("hello world");

	char buf[12] = "hello world";
	//udp_sock.set_remote_addr("127.0.0.1", 6001); //可以动态修改地址
	udp_sock.send(buf,10);
	udp_sock.close();
}