class Player
{
  public:
	int low_id, high_id, cfd;
	int name_set = 0;
	std::string token, ip, name;
	CsvReader csv;
	DataBase db;
};
