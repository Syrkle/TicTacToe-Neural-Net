#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>


class Reader{
public:
	Reader();
	~Reader();

	void readTele(std::string filename, std::string savename);
	void saveFile(std::string filename, std::string input);
private:
	std::string _contents;

	std::vector<std::string> _replyID;
	std::vector<std::string> _replyMessage;
	std::vector<std::string> _test;

	std::map<std::string, std::string> _repliedMessage;

};
