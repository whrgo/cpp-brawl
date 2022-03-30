class LogicChangeAvatarNameCommand
{
  public:
	int id = 24111;
	int version = 0;
	int state;
	ByteStream stream;
	void encode(Player a1);
};
void LogicChangeAvatarNameCommand::encode(Player player)
{
	stream.allocate(50);
	stream.writeVInt(201);
	stream.writeString(player.name);
	stream.writeVInt(state);
	stream.packetize(player, id, version);
};
