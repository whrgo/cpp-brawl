class OwnHomeDataMessage
{
  public:
	int id = 24101;
	int version = 0;
	ByteStream stream;
	void encode(Player player);
};
void OwnHomeDataMessage::encode(Player player)
{
	stream.allocate(1500);

	stream.writeVInt(0);
	stream.writeVInt(0);

	stream.writeVInt(CONFIG::Trophies);

	stream.writeVInt(CONFIG::Trophies);

	stream.writeVInt(0);

	stream.writeVInt(200);

	stream.writeVInt(99999);

	stream.writeDataReference(28, 0);

	stream.writeDataReference(43, 0);

	stream.writeVInt(0);

	stream.writeVInt(0);

	// unlocked skins array
	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeBoolean(false);

	stream.writeVInt(0);

	stream.writeVInt(86400); // Trophy League End Timer

	stream.writeVInt(0);

	stream.writeVInt(86400); // Season End Timer

	stream.writeVInt(0);

	stream.writeBoolean(false);

	stream.writeBoolean(false);

	stream.writeUInt(4);

	stream.writeVInt(2);

	stream.writeVInt(2);

	stream.writeVInt(2);

	stream.writeVInt(0); // Name Change Cost

	stream.writeVInt(0); // Name Change Timer

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeVInt(0); // array

	stream.writeVInt(0);

	stream.writeVInt(1);

	stream.writeDataReference(16, 0);

	stream.writeString(CONFIG::Region);

	stream.writeString(CONFIG::SupportedContentCreator);
	// animations array //
	stream.writeVInt(0); // count

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeVInt(0);

	// Quests Array

	stream.writeBoolean(true);
	stream.writeVInt(0);

	// Emotes Array

	stream.writeBoolean(true);

	stream.writeVInt(0);

	stream.writeVInt(0); // Shop Timestamp

	stream.writeVInt(100); // Tokens for Brawl Box

	stream.writeVInt(10); // Tokens for Big Box

	stream.writeVInt(30);

	stream.writeVInt(3);

	stream.writeVInt(80);

	stream.writeVInt(10);

	stream.writeVInt(50);

	stream.writeVInt(1000);

	stream.writeVInt(500);

	stream.writeVInt(50);

	stream.writeVInt(999900);

	stream.writeVInt(0);

	// events ids //

	stream.writeVInt(2);
	stream.writeVInt(1);
	stream.writeVInt(1);

	// events Array
	stream.writeVInt(1); // count
	stream.writeVInt(1);
	stream.writeVInt(1); // index
	stream.writeVInt(0);
	stream.writeVInt(99999);
	stream.writeVInt(0);
	stream.writeDataReference(15, 2);
	stream.writeVInt(2);
	stream.writeString();
	stream.writeVInt(0);
	stream.writeVInt(0);
	stream.writeVInt(0);
	stream.writeVInt(0); // modifiers
	stream.writeVInt(0);
	stream.writeVInt(0);

	stream.writeVInt(0); // upcoming events Array

	stream.writeVInt(8);
	stream.writeVInt(20);
	stream.writeVInt(35);
	stream.writeVInt(75);
	stream.writeVInt(140);
	stream.writeVInt(290);
	stream.writeVInt(480);
	stream.writeVInt(800);
	stream.writeVInt(1250);

	stream.writeVInt(8);
	stream.writeVInt(1);
	stream.writeVInt(2);
	stream.writeVInt(3);
	stream.writeVInt(4);
	stream.writeVInt(5);
	stream.writeVInt(10);
	stream.writeVInt(15);
	stream.writeVInt(20);

	stream.writeVInt(3);
	stream.writeVInt(10);
	stream.writeVInt(30);
	stream.writeVInt(80);

	stream.writeVInt(3);
	stream.writeVInt(6);
	stream.writeVInt(20);
	stream.writeVInt(60);

	stream.writeVInt(4);
	stream.writeVInt(20);
	stream.writeVInt(50);
	stream.writeVInt(140);
	stream.writeVInt(280);

	stream.writeVInt(4);
	stream.writeVInt(150);
	stream.writeVInt(400);
	stream.writeVInt(1200);
	stream.writeVInt(2600);

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeVInt(10);

	stream.writeVInt(0);

	stream.writeBoolean(false);

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeBoolean(true);

	stream.writeVInt(0);

	// menu theme array

	stream.writeVInt(1);
	stream.writeInt(1);
	stream.writeInt(41000000);

	stream.writeVInt(0);

	stream.writeVInt(0);

	stream.writeInt(player.high_id); // high id

	stream.writeInt(player.low_id); // low id

	stream.writeVInt(0);
	stream.writeVInt(0);

	stream.writeBoolean(false);
	stream.writeBoolean(false);

	stream.writeVInt(0);

	stream.writeVInt(0);
	stream.writeVInt(1);
	stream.writeVInt(0);
	stream.writeVInt(1);
	stream.writeVInt(0);
	stream.writeVInt(1);

	stream.writeString(player.name);
	stream.writeVInt(player.name_set);

	stream.writeInt(0);

	stream.writeVInt(8);

	// unlocked brawlers
	std::vector<int> cards = player.csv.getCharactersCards();
	std::vector<int> characters = player.csv.getCharacters();
	std::vector<int> abilities = player.csv.getAbilities();
	stream.writeVInt(cards.size() + 4);
	for (int index = 0; index < cards.size(); index++)
	{
		stream.writeDataReference(23, cards[index]);
		stream.writeVInt(1);
	}

	stream.writeVInt(5);
	stream.writeVInt(1);
	stream.writeVInt(0);

	stream.writeVInt(5);
	stream.writeVInt(8);
	stream.writeVInt(CONFIG::Gold);

	stream.writeVInt(5);
	stream.writeVInt(9);
	stream.writeVInt(0);

	stream.writeVInt(5);
	stream.writeVInt(10);
	stream.writeVInt(CONFIG::StarPoints);

	// brawler trophies
	stream.writeVInt(characters.size());
	for (int index = 0; index < characters.size(); index++)
	{
		stream.writeDataReference(16, characters[index]);
		stream.writeVInt(0);
	}

	// brawler trophies for rank
	stream.writeVInt(characters.size());
	for (int index = 0; index < characters.size(); index++)
	{
		stream.writeDataReference(16, characters[index]);
		stream.writeVInt(0);
	}

	stream.writeVInt(0);

	// upg points
	stream.writeVInt(characters.size());
	for (int index = 0; index < characters.size(); index++)
	{
		stream.writeDataReference(16, characters[index]);
		stream.writeVInt(0);
	}

	// power levels
	stream.writeVInt(characters.size());
	for (int index = 0; index < characters.size(); index++)
	{
		stream.writeDataReference(16, characters[index]);
		stream.writeVInt(8);
	}

	// cards
	stream.writeVInt(abilities.size());
	for (int index = 0; index < abilities.size(); index++)
	{
		stream.writeDataReference(23, abilities[index]);
		stream.writeVInt(1);
	}

	// new brawler tag
	stream.writeVInt(0);

	stream.writeVInt(CONFIG::Gems);

	stream.writeVInt(0);
	stream.writeVInt(0);
	stream.writeVInt(0);
	stream.writeVInt(0);
	stream.writeVInt(0);
	stream.writeVInt(0);
	stream.writeVInt(0);
	stream.writeVInt(0);
	stream.writeVInt(0);
	stream.writeVInt(0);
	stream.writeVInt(2);
	stream.writeVInt(0);

	stream.packetize(player, id, version);
};
