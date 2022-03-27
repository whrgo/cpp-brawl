class LoginOkMessage
{
  public:
	int id = 20104;
	int version = 1;
	ByteStream stream;
	void encode(Player a1);
};
void LoginOkMessage::encode(Player player)
{
	stream.allocate(250);
	stream.writeInt(player.high_id);
	stream.writeInt(player.low_id);
	stream.writeInt(player.high_id);
	stream.writeInt(player.low_id);
	stream.writeString(player.token);
	stream.packetize(player, id, version);
};
