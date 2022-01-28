#include <algorithm>
#include <fstream>
#include <sstream>

#include <Config.h>

namespace ctddll
{
	bool Config::load(std::string const& filename)
	{
		// Le nom du fichier n'est pas vide.
		if (filename.empty() == true)
		{
			return false;
		}

		// On ouvre puis ferme le fichier.
		std::stringstream ss;
		std::ifstream f;
		f.open(filename);
		if (!f.is_open())
		{
			throw std::exception("failed open");
		}
		ss << f.rdbuf();
		f.close();

		// On remplie picojson avec le contenue du fichier;
		picojson::value v;
		ss >> v;
		if (!picojson::get_last_error().empty())
			throw std::exception(picojson::get_last_error().c_str());

		// On parse le contenue du fichier.
		picojson::object& root{ v.get<picojson::object>() };
		picojson::object& objSchema{ root["schema"].get<picojson::object>() };
		picojson::array&  objConfig{ root["config"].get<picojson::array>() };

		if (   loadSchema(objSchema) == false
			|| loadSchemaReference(objSchema) == false)
		{
			return false;
		}

		return true;
	}

	bool Config::loadSchema(picojson::object& objSchema)
	{
		for (auto& [key, value] : objSchema)
		{
			std::string keyName{ key.c_str() };
			if (keyName.starts_with("#") == false)
			{
				CommonType ct;
				ct.name = keyName;
				ct.type = getTypeFromKeyName(value.get<std::string>());
				schemas.emplace_back(ct);
			}			
		}
		return true;
	}

	bool Config::loadSchemaReference(picojson::object& objSchema)
	{
		bool end{ true };

		do
		{
			end = true;
			for (auto& [key, value] : objSchema)
			{
				std::string keyName{ key.c_str() };
				if (keyName.starts_with("#") == true)
				{
					CommonType refCom = searchCommonType(keyName);
					if (refCom.type != KeyType::UNKNOW)
					{
						if (refCom.type == KeyType::ARRAY)
						{
							CommonType ct;
							ct.type = getTypeFromKeyName(value.get<std::string>());
							ct.name = refCom.name;
							references.push_back(ct);
						}
						else if (refCom.type == KeyType::DICT)
						{
							ContainerType ct;
							ct.type = KeyType::DICT;
							ct.name = refCom.name;

							for (auto& [k, v] : value.get<picojson::object>())
							{
								CommonType common;
								common.type = getTypeFromKeyName(v.get<std::string>());
								common.name = k;
								ct.keyvalues.push_back(common);
							}
						}
					}
				}
				else
				{
					end = false;
				}
			}
		} while (end == false);
		return true;
	}

	bool Config::loadConfig(picojson::array& config)
	{
		for (auto& arr : config)
		{
			for (auto& [key, value] : arr.get<picojson::object>())
			{
				std::string keyName{ key.c_str() };
				auto type{ getTypeFromKeyName(keyName) };
				if (type == KeyType::UNKNOW)
				{
					std::cerr << "The keyName is unknow. You should define in schema." << std::endl;
					return false;
				}
			}
		}

		return true;
	}

	KeyType Config::getTypeFromKeyName(std::string const& keyName) const
	{
		KeyType type{ KeyType::UNKNOW };
		return type;
	}

	CommonType Config::searchCommonType(std::string const& keyName) const
	{
		CommonType ct;

		auto findIn =
			[&](std::vector<CommonType> const& container)
			-> std::vector<CommonType>::const_iterator
		{
			size_t countHash{ 0 };
			for (auto i{0}; i < keyName.size() && keyName[i] == '#'; ++i)
			{
				++countHash;
			}

			auto buildCompare =
				[](size_t count, std::string const& name)
				-> std::string
			{
				std::string str{ name };
				str.insert(str.begin(), '#', count);
				return str;
			};

			auto it = std::find_if(
				schemas.begin(),
				schemas.end(),
				[&](CommonType const& ct)
				{
					return buildCompare(countHash, ct.name) == keyName;
				}
			);
			return it;
		};

		std::vector<std::vector<CommonType>> v{schemas, references};
		for (auto const& it : v)
		{
			auto ref = findIn(it);
			if (ref != it.end())
			{
				ct = *ref;
			}
		}

		return ct;
	}
}