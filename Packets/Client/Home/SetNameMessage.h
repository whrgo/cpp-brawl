class SetNameMessage
{
  public:
	std::string name;
	int state;
	Player player;
	ByteStream stream;
	void decode();
	void process();
	Player reload();
};
void SetNameMessage::decode()
{
	name = stream.readString();
	state = stream.readVInt();
}
void SetNameMessage::process()
{
	LogicChangeAvatarNameCommand success;
	success.state = state;
	AvatarNameChangeFailedMessage fail;
	if (name.length() >= 2 && name.length() <= 20)
	{
		player.name = name;
		player.name_set = 1;
		player.db.insert("name", name);
		player.db.insert("name_set", "1");
		player.db.save(player.token);
		success.encode(player);
	}
	else
	{
		fail.encode(player);
	}
}
Player SetNameMessage::reload()
{
	stream.offset = 7;
	return player;
}
