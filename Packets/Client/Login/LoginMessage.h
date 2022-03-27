class LoginMessage
{
  public:
	int major, minor, build;
	std::string fingerprint;
	ByteStream stream;
	Player player;
	void decode();
	void process();
	Player reload();
};
void LoginMessage::decode()
{
	player.high_id = stream.readInt();
	player.low_id = stream.readInt();
	player.token = stream.readString();
	major = stream.readInt();
	minor = stream.readInt();
	build = stream.readInt();
	fingerprint = stream.readString();
}
void LoginMessage::process()
{
	if (player.low_id == 0)
	{
		player.low_id = random(100000000, 999999999);
		player.token = random_string(40);
		player.db.insert("id", std::to_string(player.low_id));
		player.db.insert("token", player.token);
		player.db.insert("name", "");
		player.db.insert("name_set", "0");
		player.db.save(player.token);
	}
	else
	{
		player.db.load(player.token);
		player.token = player.db.get("token");
		player.name = player.db.get("name");
		std::stringstream ss;
		ss << player.db.get("id");
		ss >> player.low_id;
		std::stringstream ss2;
		ss2 << player.db.get("name_set");
		ss2 >> player.name_set;
	}

	LoginOkMessage LoginOk;
	LoginOk.encode(player);

	OwnHomeDataMessage ohd;
	ohd.encode(player);
}
Player LoginMessage::reload()
{
	stream.offset = 7;
	return player;
}
