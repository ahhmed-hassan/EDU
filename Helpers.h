#pragma once
#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
#include <string_view>
#include "nlohman/json.hpp"
using namespace std; 

inline nlohmann::json parse_json_from_file(std::string const& path)
{
	json res{};
	std::ifstream input(path); 
	if (not input)
		throw std::runtime_error("Cannot open the file : " + path);
	try
	{
		 res=nlohmann::json::parse(input);
	}
	catch (const json::parse_error& )
	{

	}	
	input.close();
	return res; 
}



inline vector<string> ReadFileLines(const string& path) {
	vector<string> lines;

	fstream file_handler(path.c_str());

	if (file_handler.fail()) {
		cout << "\n\nERROR: Can't open the file\n\n";
		return lines;
	}
	string line;

	while (getline(file_handler, line)) {
		if (line.size() == 0)
			continue;
		lines.push_back(line);
	}

	file_handler.close();
	return lines;
}

inline void WriteFileLines(const string& path, const vector<string>& lines, bool append = true) {
	auto status = ios::in | ios::out | ios::app;

	if (!append)
		status = ios::in | ios::out | ios::trunc;	// overwrite

	fstream file_handler(path.c_str(), status);

	if (file_handler.fail()) {
		cout << "\n\nERROR: Can't open the file\n\n";
		return;
	}
	for (const auto& line : lines)
		file_handler << line << "\n";

	file_handler.close();
}

inline vector<string> SplitString(string_view str, const string& delimiter = ",") {
	string s = static_cast<std::string>(str);
	vector<string> strs;

	int pos = 0;
	string substr;
	while ((pos = (int)s.find(delimiter)) != -1) {
		substr = s.substr(0, pos);
		strs.push_back(substr);
		s.erase(0, pos + delimiter.length());
	}
	strs.push_back(s);
	return strs;
}

inline int ToInt(const string& str) {
	istringstream iss(str);
	int num;
	iss >> num;

	return num;
}

inline int read_int(int low, int high,bool noChoices=false) {
	cout << "\nEnter number in range " << low << " - " << high << ": ";
	if (noChoices)
		std::cout << "\t or 0 to go back";
	int value;

	cin >> value;

	if (low <= value && value <= high)
		return value;

	cout << "ERROR: invalid number...Try again\n";
	return read_int(low, high);
}

[[maybe_unused]]inline int show_read_menu(const vector<string>& choices, std::string_view defaultTiltel="Menu",bool choose=true, bool goBack= false) {
	cout << "\n"<<defaultTiltel<<":\n";
	for (int ch = 0; ch < (int)choices.size(); ++ch) {
		cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
	}
	if (!choose)
		return INT_MIN;

	if (!goBack)
		return read_int(1, (int)choices.size(),false);

	return read_int(0, (int)choices.size(), true);
	
}
template <std::ranges::range R>
inline auto to_vector(R&& r) {
	std::vector<std::ranges::range_value_t<R>> v;

	// if we can get a size, reserve that much
	if constexpr (requires { std::ranges::size(r); }) {
		v.reserve(std::ranges::size(r));
	}

	// push all the elements
	for (auto&& e : r) {
		v.push_back(static_cast<decltype(e)&&>(e));
	}

	return v;
}