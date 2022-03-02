#pragma once
#include "sundry.h"

std::string sundry::file_input(std::string file_name) {

	std::string input;
	std::fstream file;
	file.open(file_name, std::ios::in);

	//while (!file.eof()) {
		file >> input;
	//}
	file.close();

	return input;
}

std::string sundry::file_output(std::string output, std::string file_name) {

	std::fstream file;
	file.open(file_name, std::ios::out);
    file << output;
	file.close();

	return "return";
}