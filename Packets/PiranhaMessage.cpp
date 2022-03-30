#include "Server/Login/LoginOkMessage.cpp"
#include "Server/Home/OwnHomeDataMessage.cpp"
#include "Server/Home/AvatarNameChangeFailedMessage.cpp"
#include "Server/Commands/LogicChangeAvatarNameCommand.cpp"
#include "Client/Login/LoginMessage.cpp"
#include "Client/Home/AnalyticsEventMessage.cpp"
#include "Client/Home/SetNameMessage.cpp"

class PiranhaMessage
{
  public:
	int id, fd;
	Player player;
	char *buffer;
	void bound(int a1, char *a2);
	LoginMessage LoginMessagePacket;
	AnalyticsEventMessage AnalyticsEventMessagePacket;
	SetNameMessage SetNameMessagePacket;
	void process();
};
void PiranhaMessage::bound(int a1, char *a2)
{
	id = a1;
	buffer = a2;
}
void PiranhaMessage::process()
{
	switch (id)
	{
	case 10101:
		LoginMessagePacket.stream.buffer = buffer;
		LoginMessagePacket.player = player;
		LoginMessagePacket.decode();
		LoginMessagePacket.process();
		player = LoginMessagePacket.reload();
		break;
	case 10110:
		AnalyticsEventMessagePacket.stream.buffer = buffer;
		AnalyticsEventMessagePacket.player = player;
		AnalyticsEventMessagePacket.decode();
		AnalyticsEventMessagePacket.process();
		player = AnalyticsEventMessagePacket.reload();
		break;
	case 10212:
		SetNameMessagePacket.stream.buffer = buffer;
		SetNameMessagePacket.player = player;
		SetNameMessagePacket.decode();
		SetNameMessagePacket.process();
		player = SetNameMessagePacket.reload();
		break;
	}
}
