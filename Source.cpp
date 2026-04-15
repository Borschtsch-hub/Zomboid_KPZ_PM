#include <iostream>
#include <vector>
#include <fstream>
#include <stdint.h>
#include "CLI11.hpp"

const std::string Zomboid_Version = "Zomboid 0.4.2 (15.04.2026)";
const unsigned short page_size = 25;

void Read(std::string filename) {
	std::cout << filename;
}

int main(int argc, char** argv) {

	CLI::App app{ Zomboid_Version };
	app.require_subcommand(1);

	argv = app.ensure_utf8(argv);

	auto Read = app.add_subcommand("read", "Reads from file");
	//	TODO: Change for something like std::filesystem::path
	std::string filename = "default";

	Read->add_option("-f,--file", filename, "Takes file to read");
	//Read->add_option("-d,--dir", filename, "Takes directory to read"); I'm not doing that Twin \/
	
	unsigned short page = 1;

	Read->add_option("-p,--page", page, "Page of your file");

	// Callback for using read subcommand
	Read->callback([&]() {
		std::ifstream file(filename);
		
		if (!file.is_open()) {//Check for right file
			std::cerr << "Cannot open file:\n\t" << filename;
			return -1;
		}


		std::cout << "Page: " << page << '\n';
		std::string content = "";
		// Reads from file using std::getline and inputs from needed page TODO: try to use .get() func
		for (int i = 0; i <= page_size * page; i++) {
			std::getline(file, content);
			if (i > page_size * (page - 1))
				std::cout << content << '\n';
		}

		file.close();
		//std::cout << "Input was: \n\t" << filename;
	});


	CLI11_PARSE(app, argc, argv);
	return 0;
}

