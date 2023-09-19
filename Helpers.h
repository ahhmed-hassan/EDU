#pragma once
#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
#include <string_view>
using namespace std;
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

inline int ReadInt(int low, int high) {
	cout << "\nEnter number in range " << low << " - " << high << ": ";
	int value;

	cin >> value;

	if (low <= value && value <= high)
		return value;

	cout << "ERROR: invalid number...Try again\n";
	return ReadInt(low, high);
}

inline int ShowReadMenu(const vector<string_view>& choices, std::string_view defaultTiltel="Menu") {
	cout << "\n"<<defaultTiltel<<":\n";
	for (int ch = 0; ch < (int)choices.size(); ++ch) {
		cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
	}
	return ReadInt(1, (int)choices.size());
}