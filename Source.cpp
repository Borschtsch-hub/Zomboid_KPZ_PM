#include <iostream>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <longstr.h>

class Flag {
	std::string _flags[10][2] = {
	{"--help" , "-h"},
	{"--file" , "-f"}
	};
	std::vector<std::string> _temp;
public:
	bool check_file_flag(std::string _str){
		return _str == "-f" || _str == "--file";
	}
	void push_argv(int argc, char* argv[]) {
		for (int i = 1; i < argc; i++) {
			_temp.push_back(argv[i]);
			if (_temp[i - 1].front() != '-' && (check_file_flag(_temp[i - 2]) || i == 1)) {
				std::cout << "ERROR\n";
				return;
			}
		}
	}
	void out_temp() {
		for (auto v : _temp)
			std::cout << v << '\n';
	}
};

Flag flagobj;

std::string Read_from_file();
void Write_to_file();

int main(int argc, char* argv[]) {
	std::string item = "";

	if (argc == 1) {
		std::cout <<LongString::_Help;
		return 0;
	}
	flagobj.push_argv(argc, argv);
	flagobj.out_temp();

	

	for (int i = 1;i < argc ;i++) {
		
		
	}

	/*for (int i = 1; i < argc; i++)
	{
		std::cout << ("%s", argv[i]) << '\n';
	}/*
	

	/*
	
	std::getline(std::cin, temp);

	std::cout << temp << '\n';

	while (true){
		std::cout << "Read or Write: ";
		std::cin >> item;

		if (item == "Read")
			Read_from_file();
		else if (item == "Write") {
			Write_to_file();
		}
		else if (item == "Exit")
			break;
		else std::cout << "Unknown command";
	}
	*/
	return 0;
}

std::string Read_from_file() {
	std::string item;
	std::ifstream file("DATA.csv");

	while (std::getline(file, item)) {
		std::cout << item << '\n';
	}
	file >> item;

	file.close();
	return item;
}

void Write_to_file() {
	std::string item;
	std::ofstream file("DATA.csv");
	while (true) {
		std::cout << "Input: ";
		std::cin >> item;
		if (item == ",")
			break;
		if (item == ";") {
			file << '\n';
			continue;
		}
		file << item + ",";
	}
	file.close();
}