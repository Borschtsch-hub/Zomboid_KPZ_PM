#include <iostream>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <longstr.h>
#include <unordered_map> 

enum eFlag {
	eHelp,
	eFile,
	eId,
	eFind_name,
	eCondition
};

typedef std::unordered_map<eFlag, std::string> uMap;

class Flag {//I dont know what to do with this:
	uMap _flagmap = {
		{eHelp,		 "--help"},
		{eFile,		 "--file"},
		{eId,        "-id"},
		{eFind_name, "-find-name"},
		{eCondition, "--condition"}
	};
	std::string _flags[10][2] = {
		{"--help"		, "-h"},
		{"--file"		, "-f"},
		{"-id"			, ""},
		{"-find-name"	, ""},
		{"--condition"	, "-c"}
	};
	std::vector<std::string> _temp;
public:
	bool check_file_flag(std::string _str){
		return _str == "-f" || _str == "--file";
	}
	void push_argv(int argc, char* argv[]) {
		for (int i = 1; i < argc; i++) {
			_temp.push_back(argv[i]);
			if (_temp[i - 1].front() != '-' && (i == 1 || !check_file_flag(_temp[i - 2]))) {
				std::cout << "Cannot understand meaning of {" << _temp[i - 1] << "}\n\tTry using -f or --file for files.\n";
				return;
			}
		}
	}
	void apply_flags(){
		
	}
	void out_temp() {
		for (auto v : _temp)
			std::cout << v << '\n';
	}
	void print() {
		for (auto i : _flagmap)
			std::cout << i.first << " " << i.second << std::endl;
	}
};
// std::ifstream is to READ from files
Flag flagobj;

std::string Read_from_file();
void Write_to_file();

int main(int argc, char* argv[]) {
	std::string item = "";
	// If you wasn't in mood to write help
	flagobj.print();
	if (argc == 1) {
		std::cout <<LongString::_Help;
		return 0;
	}
	flagobj.push_argv(argc, argv);

	std::ifstream a("DATssA.csv");
	
	for (int i = 1;i < argc ;i++) {
		
		
	}

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