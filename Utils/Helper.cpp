char const hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
std::string int2str(int a1)
{
	// convert int type to std::string type
	return std::to_string(a1);
}
std::string random_string(size_t length)
{
	auto randchar = []() -> char {
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}
int random(int a1, int a2)
{
	srand(time(NULL));
	return a1 + rand() % ((a2 + 1) - a1);
}
std::string char2hex(char *bytes, int size)
{
	std::string str;
	for (int i = 0; i < size; ++i)
	{
		const char ch = bytes[i];
		str.append(&hex[(ch & 0xF0) >> 4], 1);
		str.append(&hex[ch & 0xF], 1);
	}
	return str;
}
void log(std::string str)
{
	// logger...obviosly
	std::cout << str << "\n";
}
char *gpn(int sockFD)
{
	// convert fd to a client ip string.
	struct sockaddr_in addr;
	socklen_t addr_size = sizeof(struct sockaddr_in);
	getpeername(sockFD, (struct sockaddr *)&addr, &addr_size);
	char *clientip = new char[20];
	strcpy(clientip, inet_ntoa(addr.sin_addr));
	return clientip;
}
int getPacketID(char *buf)
{
	return ((buf[0] << 8) | buf[1]);
}
int getPacketLength(char *buf)
{
	return ((buf[2] << 16) | (buf[3] << 8) | buf[4]);
}
