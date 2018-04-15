#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <fstream>
#include <string>
#include <vector>

namespace Project1
{
	class Config
	{
	public:
		std::vector<int> Threads;
		std::vector<int> Nodes;

		static Config FromFile(std::string& path);
	private:
		rapidjson::Document _document;
		Config(std::string& path);
	};
}