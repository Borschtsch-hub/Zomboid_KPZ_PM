#include <iostream>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <longstr.h>
#include <unordered_map> 

const std::string Zomboid_Version = "Zomboid 0.2 (25.03.2026)";

enum eFlags {
	eHelp,
	eFile,
	eId,
	eFind_name,
	eCondition,
	ePage,
	eVersion
};

typedef std::unordered_map<std::string, eFlags> uMap;

std::vector<std::string> Read_from_file(std::string inpfilename = "Data.csv", std::string page = "1");
void Write_to_file();

class Flag {//I dont know what to do with this:
	uMap _flagmap = {
		{"--help",		eHelp},
		{"-h",			eHelp},
		{"--file",		eFile,},
		{"-f",			eFile,},
		{"-id",			eId},
		{"-find-name",	eFind_name},
		{"--condition", eCondition},
		{"-c",			eCondition},
		{"--page",		ePage},
		{"-p",			ePage},
		{"--version",	eVersion},
		{"-v",			eVersion}
	};
	std::vector<std::string> _temp;
	eFlags _flagenum = eHelp;
public:
	bool check_file_flag(std::string _str){
		return _str == "-f" || _str == "--file";
	}
	void push_argv(int argc, char* argv[]) {
		for (int i = 1; i < argc; i++) {
			_temp.push_back(argv[i]);
			if (_temp[i - 1].front() != '-' && (i == 1 || _flagmap[_temp[i - 2]] != eFile)) {
				std::cerr << "Cannot understand meaning of {" << _temp[i - 1] << "}\n\tTry using -f or --file for files.\n";
				return;
			}
		}
	}
	void apply_flags(int argc = 3){
		_flagenum = _flagmap[_temp[0]];
		switch (_flagenum) {
		case 0:
			std::cout << LongString::_Help;
			break;
		case 1:
			(argc == 5) ? Read_from_file(_temp[1], _temp[3]) : Read_from_file(_temp[1]);
			break;
		case 2:
			std::cout << "Id\n";
			break;
		case 3:
			std::cout << "Find-name\n";
			break;
		case 4:
			std::cout << "Condition\n";
			break;
		case 6:
			std::cout << Zomboid_Version;
			break;
		}
	}
	// Another function to apply flags for -f flag
	void out_temp() {
		for (auto v : _temp)
			std::cout << v;
	}
};
// std::ifstream is to READ from files
Flag flagobj;


int main(int argc, char* argv[]) {
	
	std::vector<std::string> item = Read_from_file();
	for(auto v: item)
		std::cout << v << '\n';

	// If you wasn't in mood to write --help
	if (argc == 1) {
		std::cout <<LongString::_Help;
		return 0;
	}
	flagobj.push_argv(argc, argv);

	flagobj.apply_flags(argc);

	return 0;
}

std::vector<std::string> Read_from_file(std::string inpfilename, std::string page) {
	std::vector<std::string> item;
	std::string line = "";
	std::cout <<'\n' << inpfilename << '\n';
	std::ifstream file(inpfilename);

	if (!file.is_open()) {
		std::cerr << "ERROR. Cannot open file";
		return item;
	}
	while (std::getline(file, line)) {
		item.push_back(line);
	}

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