std::string lower(std::string a1)
{
	for (char &v1 : a1)
		v1 = std::tolower(v1);
	return a1;
}
class CsvReader
{
  public:
	std::vector<std::string> brawlers;
	std::vector<int> getCharacters();
	std::vector<std::string> getLockedCharacters();
	std::vector<int> getCharactersCards();
	std::vector<int> getAbilities();
};
int getIndexOfStringElementFromVector(std::vector<std::string> vec, std::string item)
{
	int index;
	for (int offset = 0; offset < vec.size(); offset++)
	{
		if (vec[offset] == item)
		{
			index = offset;
		}
	}
	return index;
}
std::vector<int> CsvReader::getCharacters()
{
	std::vector<int> characters;
	int index = -1;
	io::CSVReader<3> in("CsvReader/Assets/characters.csv");
	in.read_header(io::ignore_extra_column, "Type", "Disabled", "LockedForChronos");
	std::string type, disabled, locked;
	while (in.read_row(type, disabled, locked))
	{
		if (lower(type) == "hero" && lower(disabled) != "true" && lower(locked) != "true")
		{
			characters.push_back(index);
		}
		index += 1;
	}
	return characters;
}
std::vector<std::string> CsvReader::getLockedCharacters()
{
	std::vector<std::string> characters;
	int index = -1;
	io::CSVReader<4> in("CsvReader/Assets/characters.csv");
	in.read_header(io::ignore_extra_column, "Name", "Type", "Disabled", "LockedForChronos");
	std::string type, disabled, locked, name;
	while (in.read_row(name, type, disabled, locked))
	{
		if (lower(type) == "hero")
		{
			if (lower(disabled) == "true" || lower(locked) == "true")
			{
				characters.push_back(lower(name));
			}
		}
		index += 1;
	}
	return characters;
}
std::vector<int> CsvReader::getCharactersCards()
{
	std::vector<int> cards;
	std::vector<std::string> lc = getLockedCharacters();
	int index = -1, iof;
	bool match;
	io::CSVReader<3> in("CsvReader/Assets/cards.csv");
	in.read_header(io::ignore_extra_column, "MetaType", "Target", "Type");
	std::string type, target, t;
	while (in.read_row(type, target, t))
	{
		if (lower(type) == "0" && lower(t) == "unlock")
		{
			match = false;
			for (iof = 0; iof < lc.size(); iof++)
			{
				if (lc[iof] == lower(target))
				{
					match = true;
				}
			}
			if (!match)
			{
				cards.push_back(index);
			}
		}
		index += 1;
	}
	return cards;
}
std::vector<int> CsvReader::getAbilities()
{
	std::vector<int> result;
	int index = -1;
	io::CSVReader<2> in("CsvReader/Assets/cards.csv");
	in.read_header(io::ignore_extra_column, "MetaType", "LockedForChronos");
	std::string type, locked;
	while (in.read_row(type, locked))
	{
		if (type == "5" || type == "4")
		{
			if (lower(locked) != "true")
			{
				result.push_back(index);
			}
		}
		index += 1;
	}
	return result;
}
