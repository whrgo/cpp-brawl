class AnalyticsEventMessage
{
  public:
	std::string type, event;
	ByteStream stream;
	Player player;
	void decode();
	void process();
	Player reload();
};
void AnalyticsEventMessage::decode()
{
	type = stream.readString();
	event = stream.readString();
}
void AnalyticsEventMessage::process()
{
	if (CONFIG::LogGameAnalytics)
	{
		std::cout << type << " " << event << "\n";
	}
}
Player AnalyticsEventMessage::reload()
{
	stream.offset = 7;
	return player;
}
