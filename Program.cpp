#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "config.h"
#include "DataBase/DataBase.h"
#include "Utils/CsvHelper.h"
#include "CsvReader/CsvReader.h"
#include "Logic/Player.h"
#include "Utils/Helper.h"
#include "DataStream/ByteStream.h"
#include "Packets/PiranhaMessage.h"

void connection(int cfd)
{
	// client session
	try
	{
		std::string client = gpn(cfd);
		log(client + " connected.");
		int recv = 1, id, length;
		Player player;
		player.ip = client;
		player.cfd = cfd;
		char buffer[1024];
		PiranhaMessage PiranhaMessageSession;
		PiranhaMessageSession.player = player;
		PiranhaMessageSession.fd = cfd;
		while (recv > 0)
		{
			strcpy(buffer, new char[1024]);
			recv = read(cfd, buffer, 1024);
			if (recv > 0)
			{
				id = getPacketID(buffer);
				length = getPacketLength(buffer);
				std::cout << "received packet with id: " << int2str(id) << "|length: " << int2str(length) << "\n";
				if (sizeof(buffer) >= 7)
				{
					PiranhaMessageSession.bound(id, buffer);
					PiranhaMessageSession.process();
				}
			}
		}
		std::cout << client << " disconnected.\n";
	}
	catch (int e)
	{
		std::cout << "unexpected error was handled";
	}
	close(cfd);
}

int main(int argc, char *argv[])
{
	int port = 9339;
	int fd;
	int binded;
	int opt = 1;
	int client;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	
	fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	binded = bind(fd, (struct sockaddr *)&address, sizeof(address));
	log("server is listening on port: " + int2str(port));
	// we have to keep the thread saved in memory
	std::vector<std::unique_ptr<std::thread>> threads;

	while (true)
	{
		listen(fd, 1);
		client = accept(fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
		// create a new thread for the client
		threads.emplace_back(new std::thread(connection, client));
	}
}
