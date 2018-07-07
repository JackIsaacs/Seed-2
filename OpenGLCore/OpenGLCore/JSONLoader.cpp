#include "JSONLoader.h"

#include <fstream>
#include "println.h"

using namespace Core;

JSONLoader::JSONLoader()
{
}


JSONLoader::~JSONLoader()
{
}

bool Core::JSONLoader::LoadJSON(std::string path)
{
	openPath = path;
	std::ifstream stream(path.c_str());

	if (stream.fail())
	{
		stream.close();
		println("Failed to Load: %s", path.c_str());
		LoadFallback();		// Load fallback values into child class
		RegenerateFile();	// Regenerate json file with fallback values
		return false;
	}
	else if (stream.peek() == std::ifstream::traits_type::eof())
	{
		// File empty
		stream.close();
		println("File Empty: %s", path.c_str());
		LoadFallback();		// Load fallback values into child class
		RegenerateFile();	// Regenerate json file with fallback values
		return false;
	}
	else
	{
		// Loaded fine, with data

		json j;
		stream >> j;

		// Extract json values to map
		data.clear();

		for (auto it = j.begin(); it != j.end(); ++it)
		{
			data[it.key()] = it.value();
		}


		stream.close();

		println("Loaded: %s", path.c_str());
	
		return true;
	}
}

bool Core::JSONLoader::SaveJSON()
{
	if (openPath != "")
	{
		return SaveJSON(openPath);
	}
	else
	{
		return false;
	}
}

bool Core::JSONLoader::SaveJSON(std::string path)
{
	json j = data;
	std::ofstream stream(path);

	if (stream.fail())
		return false;

	stream << std::setw(2) << j << std::endl;

	stream.close();

	return true;
}

void Core::JSONLoader::SetVec2(std::vector<std::string> keys, glm::vec2 val)
{
	std::vector<float> data = { val.x, val.y };
	SetVecArray(keys, data);
}

void Core::JSONLoader::SetVec3(std::vector<std::string> keys, glm::vec3 val)
{
	std::vector<float> data = { val.x, val.y, val.z };
	SetVecArray(keys, data);
}

void Core::JSONLoader::SetVec4(std::vector<std::string> keys, glm::vec4 val)
{
	std::vector<float> data = { val.x, val.y, val.z, val.w };
	SetVecArray(keys, data);
}

void Core::JSONLoader::RegenerateFile()
{
	println("Regenerating: %s", openPath.c_str());

	FILE* file;
	fopen_s(&file, openPath.c_str(), "w");
	fclose(file);

	SaveSettings();
}

void Core::JSONLoader::SaveSettings()
{
	if (SaveJSON(openPath))
	{
		println("Saved: %s", openPath.c_str());
	}
	else
	{
		println("Couldn't open: %s", openPath.c_str());
		println("Regenerating: %s", openPath.c_str());
		RegenerateFile();
	}
}

glm::vec2 Core::JSONLoader::GetVec2(std::vector<std::string> keys)
{
	std::vector<float> data = GetArray<float>(keys);
	DBG_ASSERT(data.size() != 2);
	return { data[0], data[1] };
}

glm::vec3 Core::JSONLoader::GetVec3(std::vector<std::string> keys)
{
	std::vector<float> data = GetArray<float>(keys);
	DBG_ASSERT(data.size() != 3);
	return { data[0], data[1], data[2] };
}

glm::vec4 Core::JSONLoader::GetVec4(std::vector<std::string> keys)
{
	std::vector<float> data = GetArray<float>(keys);
	DBG_ASSERT(data.size() != 4);
	return { data[0], data[1], data[2], data[3] };
}

bool Core::JSONLoader::HasKey(std::string key, json::value_type root)
{
	if (root == nullptr) root = data;

	auto it = root.find(key);
	return it != root.end();
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

void Core::JSONLoader::SetVecArray(std::vector<std::string> keys, std::vector<float> vecdata)
{
	if (keys.size() > 1)
	{
		//DBG_ASSERT(!HasKey(keys[0]));
		json::value_type& current = data[keys[0]];

		for (unsigned int i = 1; i < keys.size(); ++i)
		{
			//DBG_ASSERT(!HasKey(keys[i], current));

			if (i == keys.size() - 1)
			{
				// Set correct key in map directly with new value
				current[keys[i]] = static_cast<json::value_type>(vecdata);
			}
			else
			{
				current = current[keys[i]];
			}
		}
	}
	else
	{
		//DBG_ASSERT(!HasKey(keys[0]));
		data[keys[0]] = static_cast<json::value_type>(vecdata);
	}
}
