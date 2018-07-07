#pragma once
#include <string>
#include <map>

#include "json.hpp"
#include "Debug.h"
#include <vector>
#include <glm/glm.hpp>

using json = nlohmann::json;

namespace Core
{

	class JSONLoader
	{
	public:
		JSONLoader();
		~JSONLoader();

		bool LoadJSON(std::string path);
		bool SaveJSON();
		bool SaveJSON(std::string path);

		template <typename T>
		T GetValue(std::vector<std::string> keys);

		template <typename T>
		std::vector<T> GetArray(std::vector<std::string> keys);

		glm::vec2 GetVec2(std::vector<std::string> keys);
		glm::vec3 GetVec3(std::vector<std::string> keys);
		glm::vec4 GetVec4(std::vector<std::string> keys);

		template <typename T>
		void SetValue(std::vector<std::string> keys, T val);

		template <typename T>
		void SetArray(std::vector<std::string> keys, std::vector<T> vals);

		void SetVec2(std::vector<std::string> keys, glm::vec2 val);
		void SetVec3(std::vector<std::string> keys, glm::vec3 val);
		void SetVec4(std::vector<std::string> keys, glm::vec4 val);

		std::map<std::string, json::value_type> data;


		//////////////////////////////////
		// virtuals

		void RegenerateFile();
		virtual void LoadFallback() {};
		virtual void SaveSettings();

	private:

		bool HasKey(std::string key, json::value_type root = nullptr);
		std::string JsonValToString(json::value_type value);
		void PrintKeyVal(std::string key);
		void SetVecArray(std::vector<std::string> keys, std::vector<float> vecdata);

		std::string openPath;
	};






	template <typename T>
	inline T JSONLoader::GetValue(std::vector<std::string> keys)
	{
		if (keys.size() > 1)
		{
			//DBG_ASSERT(!HasKey(keys[0]));
			json::value_type current = data[keys[0]];

			for (unsigned int i = 1; i < keys.size(); ++i)
			{
				//DBG_ASSERT(!HasKey(keys[i], current));
				current = current[keys[i]];
			}

			return current.get<T>();
		}
		else
		{
			//DBG_ASSERT(keys.empty());
			//DBG_ASSERT(!HasKey(keys[0]));

			return data[keys[0]].get<T>();
		}
	}

	template<typename T>
	inline std::vector<T> JSONLoader::GetArray(std::vector<std::string> keys)
	{
		std::vector<json::value_type> dirty;

		if (keys.size() > 1)
		{
			//DBG_ASSERT(!HasKey(keys[0]));
			json::value_type current = data[keys[0]];

			for (unsigned int i = 1; i < keys.size(); ++i)
			{
				//DBG_ASSERT(!HasKey(keys[i], current));
				current = current[keys[i]];
			}

			dirty = current.get<std::vector<json::value_type>>();
		}
		else
		{
			//DBG_ASSERT(keys.empty());
			//DBG_ASSERT(!HasKey(keys[0]));

			dirty = data[keys[0]].get<std::vector<json::value_type>>();
		}

		std::vector<T> clean = std::vector<T>();

		for (auto& value : dirty)
		{
			clean.push_back(value.get<T>());
		}

		return clean;
	}

	template<typename T>
	inline void JSONLoader::SetValue(std::vector<std::string> keys, T val)
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
					current[keys[i]] = static_cast<json::value_type>(val);
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
			data[keys[0]] = static_cast<json::value_type>(val);
		}
	}

	template <typename T>
	void JSONLoader::SetArray(std::vector<std::string> keys, std::vector<T> vals)
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
					current[keys[i]] = static_cast<json::value_type>(vals);
				}
				else
				{
					current = current[keys[i]];
				}
			}
		}
		else
		{
			//DBG_ASSERT(keys.empty());
			//DBG_ASSERT(!HasKey(keys[0]));

			data[keys[0]] = static_cast<json::value_type>(vals);
		}
	}
}

