#include "JSONLoader.h"

#include <fstream>

using namespace Core;

JSONLoader::JSONLoader()
{
}


JSONLoader::~JSONLoader()
{
}

void Core::JSONLoader::LoadJSON(std::string path)
{
	std::ifstream stream(path.c_str());

	if (stream.fail())
		DBG_ASSERT(true);

	json j;
	stream >> j;

	// Extract json values to map
	data.clear();

	for (auto it = j.begin(); it != j.end(); ++it)
	{
		data[it.key()] = it.value();
	}

	openPath = path;

	stream.close();
}

void Core::JSONLoader::SaveJSON()
{
	SaveJSON(openPath);
}

void Core::JSONLoader::SaveJSON(std::string path)
{
	json j = data;
	std::ofstream stream(path);
	stream << std::setw(4) << j << std::endl;

	stream.close();
}

bool Core::JSONLoader::HasKey(std::string key)
{
	auto it = data.find(key);
	return it != data.end();
}

std::string Core::JSONLoader::JsonValToString(json::value_type value)
{
	if (value.is_boolean())
		return std::to_string(value.get<bool>());
	else if (value.is_string())
		return value.get<std::string>();
	else if (value.is_number_integer())
		return std::to_string(value.get<int>());
	else if (value.is_number_unsigned())
		return std::to_string(value.get<unsigned int>());
	else if (value.is_number_float())
		return std::to_string(value.get<float>());
	else
		DBG_ASSERT(true); // Not supported

	return "";
}

void Core::JSONLoader::PrintKeyVal(std::string key)
{
	printf("%s : %s\n", key.c_str(), JsonValToString(data[key]).c_str());
}