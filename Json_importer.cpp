#include "Json_importer.h"

json_importer::json_importer(char * filename)
{
	file = std::fopen(filename, "r");
	if (!file) {
		std::cout << "Config file " <<  filename << " was not found\n";
		exit(1);
	}
	Parse();
}

json_importer::~json_importer()
{
	std::fclose(file);
}

int json_importer::get_int(char* class_name, char* attr)
{
	auto obj = get_obj(class_name);
	auto iter = obj.FindMember(attr);

	if (iter != obj.MemberEnd())
	{
		auto type = iter->value.GetType();
		if (type != rapidjson::kNumberType)
		{
			std::cout << class_name << "." << attr << " is not an integer\n";
			exit(1);
		}
		else {
			return iter->value.GetInt();
		}
	}
	else
	{
		std::cout << "Key " << attr << " in object " << class_name << " was not found\n";
		exit(1);
	}
}

char json_importer::get_char(char* class_name, char* attr)
{
	auto obj = get_obj(class_name);
	auto iter = obj.FindMember(attr);

	if (iter != obj.MemberEnd())
	{
		auto type = iter->value.GetType();
		if (type != rapidjson::kStringType)
		{
			std::cout << class_name << "." << attr << " is not a string\n";
			exit(1);
		}
		else
			if (iter->value.GetStringLength())
				return iter->value.GetString()[0];
			else {
				std::cout << "Key " << attr << " in object " << class_name << " is empty string\n";
				exit(1);
			}
	}
	else
	{
		std::cout << "Key " << attr << " in object " << class_name << " was not found\n";
		exit(1);
	}
}

void json_importer::Parse()
{
	char buffer[65536];
	rapidjson::FileReadStream source(file, buffer, sizeof(buffer));
	rapidjson::ParseResult result = data.ParseStream(source);
	if (!result) {
		std::cout << "JSON parse error: " << rapidjson::GetParseError_En(result.Code()) << std::endl;
		exit(1);
	}
} 