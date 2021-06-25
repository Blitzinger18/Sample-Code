#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main()
{
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Initialization of Winsock failed! Exiting" << endl;
		return;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return;
	}

	// Bind the ip to socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(360);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; 

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// socket is listening
	listen(listening, SOMAXCONN);

	//master file 
	fd_set master;
	FD_ZERO(&master);

	// add master socket
	FD_SET(listening, &master);

	//used to exit program later in the code
	bool running = true;

	while (running)
	{

		//copy of master socket

		fd_set copy = master;

		// count of listening sockets
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		// keep connsections running
		for (int i = 0; i < socketCount; i++)
		{
			//assign socket to array
			SOCKET sock = copy.fd_array[i];

			//socket listening
			if (sock == listening)
			{
				//new connection
				SOCKET client = accept(listening, nullptr, nullptr);

				// Add connection
				FD_SET(client, &master);

				// welcome message
				string welcomeMsg = "Welcome to Brandon's ChatRoom!\r\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
			}
			else //messages
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				// Receive message
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
					// Drop client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					// \quit shuts down the server
					if (buf[0] == '\\')
					{
						// check for \quit command 
						string cmd = string(buf, bytesIn);
						if (cmd == "\\quit")
						{
							running = false;
							break;
						}

						// repeat loop until command entered correctly
						continue;
					}

					// send message

					for (int i = 0; i < master.fd_count; i++)
					{
						SOCKET outSock = master.fd_array[i];
						if (outSock != listening && outSock != sock)
						{
							ostringstream ss;
							ss << "SOCKET #" << sock << ": " << buf << "\r\n";
							string strOut = ss.str();

							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
						}
					}
				}
			}
		}
	}

	//remove master socket
	FD_CLR(listening, &master);
	closesocket(listening);

	// server message
	string msg = "Server is shutting down. CYA SOON\r\n";

	while (master.fd_count > 0)
	{
		//socket number
		SOCKET sock = master.fd_array[0];

		//goodbye message
		send(sock, msg.c_str(), msg.size() + 1, 0);

		// remove socket from master
		FD_CLR(sock, &master);
		closesocket(sock);
	}

	// Cleanup winsock
	WSACleanup();

	system("pause");
}
/*	        /  ,'(
		   /`-'   \__.,
		 ,'     .-"\ `---/                     /
	  |`'      /,'||    '.               ,`. ,(,_. _,
  __  |  ,--+--.  ||     `'/  .     _.-"'   `    ""`.
." ,'-'."d__|  `.'_'    _,-    ,.  /        ._      `\_
|,'     `-..-----"._     `.     ` |           `.     \.
 `"V"--._           `.   `._    ' |             \     \,
  \      `----      '. _,-'    ,' |              \     .
   `._             .--`       `.  |               .    |
	  `-.          `,.       ,--  |               L    '
		/   [-,=.---' `.__`,`     `.              |     \
	_.-'    `.._'--.._   - `--+"""" '._           |      `._,
	\        _  ---..__`--._'-.`,  ,' ,`._       j         -,'
   .'        ,-..     ,'    `. `  . ,'  / `._   /`._    ___,-'_
   l        .|_  `,  -' . .-"      v   /   _.`.'`   7",',-,.-" --,
	\      `.  .,  -..',')'"",   .    /  .'    |  ,'.',/| ,.     >
	 V-.    '    -._,-"    _,  .,'   j ,^    ,'/`--' `    -..,   `...
	 '  \/\|.     :/       './`'|    |/    ,' /            `___    ,'
		   | `. ,'`-.        /  |    ' _.-'  |               ,'  ."
		   L._`.'   |       Y,.'|    ,-    ,-'          __.,'  .'
			\ \  /`.|     _,.',''.  .`-,../         ,.-/,...-`'
			 \ ,|| |/_.-\" .+'    \._  _,'       _.'"  |
			  '  ' L| | `,' |      `.""          ,.    |
			  )    `|"      |        `>.. _,..--" j    |
		   ,-'      |____,..'       ,',-"'       /   _,'
		  /"'    _,.'               |(      _..-' `""
		  `----"'                    `'""'"" */