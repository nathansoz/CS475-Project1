#include "Config.h"

using namespace Project1;

Config Config::FromFile(std::string& path)
{
	Config config(path);

	return config;
}

Config::Config(std::string& path)
{
	std::ifstream _fileStream(path);

	if (!_fileStream.is_open())
	{
		throw std::exception();
	}

	std::string text((std::istreambuf_iterator<char>(_fileStream)), std::istreambuf_iterator<char>());

	_fileStream.close();

	_document.Parse(text.c_str());

	rapidjson::Value& threads = _document["threads"];
	for (auto& v : threads.GetArray())
	{
		this->Threads.push_back(v.GetInt());
	}

	rapidjson::Value& nodes = _document["nodes"];
	for (auto& v : nodes.GetArray())
	{
		this->Nodes.push_back(v.GetInt());
	}
}