#include <iostream>

#include <Config.h>

static void usage()
{
	std::cout
		<< "./ConverterToDynamicDLL <FILENAME>"
		<< std::endl;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		usage();
		return 1;
	}
	ctddll::Config config;
	config.load(std::string(argv[1]));
	return 0;
}
