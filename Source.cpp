#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include "CLI11.hpp"
#include <filesystem>


const std::string Zomboid_Version = "Zomboid 0.4.3 (15.04.2026)";
const unsigned short page_size = 25;

typedef std::vector<std::vector<std::string>> double_str_vector;

double_str_vector Read_csv(std::ifstream* file, int page);

void Read(std::string filename) {
	std::cout << filename;
}

int main(int argc, char** argv) {

	CLI::App app{ Zomboid_Version };
	app.require_subcommand(1);

	argv = app.ensure_utf8(argv);

	auto Read = app.add_subcommand("read", "Reads from file");
	
	std::filesystem::path filepath;

	Read->add_option("-f,--file", filepath, "Takes file to read");
	//Read->add_option("-d,--dir", filename, "Takes directory to read"); I'm not doing that Twin \/
	
	unsigned short page = 1;

	Read->add_option("-p,--page", page, "Page of your file. Takes only unsigned shorts");

	// Callback for using read subcommand
	Read->callback([&]() {

		std::ifstream file(filepath);
		
		if (!file.is_open()) {//Check for right file
			std::cerr << "Cannot open file:\n\t" << filepath;
			return -1;
		}

		double_str_vector page_content;

		if (filepath.extension() == ".csv")
			page_content = Read_csv(&file, page);
		
		if (page_content.size()-1) {
			for (auto line : page_content) {
				for (auto element : line)
					std::cout << element<< "   " << '\t';
				std::cout << '\n';
			}
		} else std::cout << "Page is empty";
		
		file.close();
		//std::cout << "\nInput was: \n\t" << filepath;//
	});


	CLI11_PARSE(app, argc, argv);
	return 0;
}

// My own pseudo-parser for .csv files, im crine
double_str_vector Read_csv(std::ifstream* file, int page) {
	std::cout << "Page: " << page << '\n';
	std::string content, word = "";
	std::vector<std::string> page_line;
	double_str_vector page_content;

	std::getline(*file, content);
	std::stringstream ss(content);
	// Colummns
	while (std::getline(ss, word, ','))
		page_line.push_back(word);
	page_content.push_back(page_line);
	page_line.clear();

	// Reads from file using std::getline and inputs for selected page
	for (int i = 0; i < (page_size * page) && !file->eof(); i++) {
		std::getline(*file, content);
		std::stringstream ss(content);
		if (i >= page_size * (page - 1)) {
			while (std::getline(ss, word, ','))
				page_line.push_back(word);
			page_content.push_back(page_line);
			page_line.clear();
		}
	}
	return page_content;
}