class AvatarNameChangeFailedMessage
{
  public:
	int id = 20205;
	int version = 0;
	ByteStream stream;
	void encode(Player a1);
};
void AvatarNameChangeFailedMessage::encode(Player player)
{
	stream.allocate(10);
	stream.writeVInt(0);
	stream.packetize(player, id, version);
};
