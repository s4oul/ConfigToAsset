#pragma once

#include <string>
#include <vector>

#include <EnumType.hpp>
#include <picojson.h>

namespace ctddll
{
	struct CommonType
	{
		std::string   name;
		KeyType       type{ KeyType::UNKNOW };
	};

	struct ContainerType : public CommonType
	{
		std::vector<CommonType> keyvalues;
	};

	class Config
	{
	private:
		std::vector<CommonType> schemas;
		std::vector<CommonType> references;

		bool       loadSchema(picojson::object& objSchema);
		bool       loadSchemaReference(picojson::object& objSchema);
		bool       loadConfig(picojson::array& config);
		KeyType    getTypeFromKeyName(std::string const& keyName) const;
		CommonType searchCommonType(std::string const& keyName) const;

	public:
		Config() = default;
		~Config() = default;

		bool load(std::string const& filename);
	};
}
