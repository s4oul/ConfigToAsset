#pragma once

#include <cstdint>
#include <algorithm>
#include <string>

namespace ctddll
{
	enum class KeyType : std::uint8_t
	{
		CHAR,
		UCHAR,
		INT32,
		UINT32,
		INT64,
		UINT64,
		STRING,
		ARRAY,
		DICT,
		UNKNOW
	};

	class ConverterKeyType
	{
	public:
		static KeyType toKeyType(std::string const& key);
		static std::string toString(KeyType key);
	};
}
