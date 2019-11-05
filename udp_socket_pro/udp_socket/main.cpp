#include <iostream>
#include "UdpSocket.h"
#include <time.h>

int main()
{
	UdpSocket udp_sock("127.0.0.1",9001);
	char inbuf[128];

	udp_sock.recv_from(inbuf);
	cout << inbuf << endl;

	udp_sock.send_to("hello world","127.0.0.1",6000);

	char buf[12] = "hello world";
	udp_sock.send_to(buf,10,"127.0.0.1", 6000);
	udp_sock.close();
}