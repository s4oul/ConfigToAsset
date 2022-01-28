#include <exception>

#include <EnumType.hpp>

namespace ctddll
{
	KeyType ConverterKeyType::toKeyType(std::string const& key)
	{
		KeyType type{ KeyType::UNKNOW };

		if (key == "CHAR")
		{
			type = KeyType::CHAR;
		}
		else if (key == "UCHAR")
		{
			type = KeyType::UCHAR;
		}
		else if (key == "INT32")
		{
			type = KeyType::INT32;
		}
		else if (key == "UINT32")
		{
			type = KeyType::UINT32;
		}
		else if (key == "INT64")
		{
			type = KeyType::INT64;
		}
		else if (key == "UINT64")
		{
			type = KeyType::UINT64;
		}
		else if (key == "STRING")
		{
			type = KeyType::STRING;
		}
		else if (key == "ARRAY")
		{
			type = KeyType::ARRAY;
		}
		else if (key == "DICT")
		{
			type = KeyType::DICT;
		}
		return type;
	}

	std::string ConverterKeyType::toString(KeyType key)
	{
		std::string type;
		switch (key)
		{
		case KeyType::CHAR:
			type = "CHAR";
			break;
		case KeyType::UCHAR:
			type = "UCHAR";
			break;
		case KeyType::INT32:
			type = "INT32";
			break;
		case KeyType::UINT32:
			type = "UINT32";
			break;
		case KeyType::INT64:
			type = "INT64";
			break;
		case KeyType::UINT64:
			type = "UINT64";
			break;
		case KeyType::STRING:
			type = "STRING";
			break;
		case KeyType::ARRAY:
			type = "STRING";
			break;
		case KeyType::DICT:
			type = "STRING";
			break;
		case KeyType::UNKNOW:
			type = "UNKNOW";
			break;
		default:
			throw std::exception("Unexpected type");
			break;
		}
		return type;
	}
}