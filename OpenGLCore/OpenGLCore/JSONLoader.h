#pragma once
#include <string>
#include <map>

#include "json.hpp"
#include "Debug.h"
#include <vector>

using json = nlohmann::json;

namespace Core
{
	/*!
	 * \class JSON Loader
	 *
	 * \brief JSON file loader and saver
	 *
	 * A simple wrapper for basic JSON files
	 *
	 * \author jacki
	 * \date July 2018
	 */
	class JSONLoader
	{
	public:
		JSONLoader();
		~JSONLoader();

		//************************************
		// Method:    LoadJSON
		// FullName:  Core::JSONLoader::LoadJSON
		// Access:    public 
		// Qualifier:
		// Parameter: std::string path
		// Returns:   void
		//************************************
		void LoadJSON(std::string path);

		//************************************
		// Method:    SaveJSON
		// FullName:  Core::JSONLoader::SaveJSON
		// Access:    public 
		// Qualifier:
		// Returns:   void
		//************************************
		void SaveJSON();

		//************************************
		// Method:    SaveJSON
		// FullName:  Core::JSONLoader::SaveJSON
		// Access:    public 
		// Qualifier:
		// Parameter: std::string path
		// Returns:   void
		//************************************
		void SaveJSON(std::string path);

		//************************************
		// Method:    GetValue
		// FullName:  Core::JSONLoader::GetValue
		// Access:    public 
		// Qualifier:
		// Parameter: std::string key
		// Returns:   T
		//************************************
		template <typename T>
		T GetValue(std::string key);


		template <typename T>
		std::vector<T> GetArray(std::string key);


		//************************************
		// Method:    SetValue
		// FullName:  Core::JSONLoader::SetValue
		// Access:    public 
		// Qualifier:
		// Parameter: std::string key
		// Parameter: T val
		// Returns:   void
		//************************************
		template <typename T>
		void SetValue(std::string key, T val);

		std::map<std::string, json::value_type> data;

	private:
		//************************************
		// Method:    HasKey
		// FullName:  Core::JSONLoader::HasKey
		// Access:    private 
		// Qualifier:
		// Parameter: std::string key
		// Returns:   bool
		//************************************
		bool HasKey(std::string key);

		//************************************
		// Method:    JsonValToString
		// FullName:  Core::JSONLoader::JsonValToString
		// Access:    private 
		// Qualifier:
		// Parameter: json::value_type value
		// Returns:   std::string
		//************************************
		std::string JsonValToString(json::value_type value);

		//************************************
		// Method:    PrintKeyVal
		// FullName:  Core::JSONLoader::PrintKeyVal
		// Access:    private 
		// Qualifier:
		// Parameter: std::string key
		// Returns:   void
		//************************************
		void PrintKeyVal(std::string key);

		std::string openPath;
	};

	template<typename T>
	inline T JSONLoader::GetValue(std::string key)
	{
		DBG_ASSERT(!HasKey(key));
		return data[key].get<T>();
	}

	template<typename T>
	inline std::vector<T> JSONLoader::GetArray(std::string key)
	{
		DBG_ASSERT(!HasKey(key));

		std::vector<json::value_type> dirty = data[key].get<std::vector<json::value_type>>();

		std::vector<T> clean = std::vector<T>();

		for (auto& value : dirty)
		{
			clean.push_back(value.get<T>());
		}

		return clean;
	}

	template<typename T>
	inline void JSONLoader::SetValue(std::string key, T val)
	{
		data[key] = static_cast<json::value_type>(val);
	}
}

