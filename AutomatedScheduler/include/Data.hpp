sf::Font font;
struct Job
{
	Electrux::SlicedTime exec_time;
	std::string taskname;
	std::string file;
};

bool fexists(std::string _file)
{
	std::ifstream infile(_file);
	return infile.good();
}