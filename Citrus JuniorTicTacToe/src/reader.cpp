#include "reader.h"

Reader::Reader(){}

Reader::~Reader(){}

//for extracting tele data
void Reader::readTele(std::string filename, std::string savename){
	std::ifstream file;
	std::string line;

	/*
	file.open(filename);
	if(file.is_open()){
		std::string apos = "&apos;";
		std::string quot = "&quot;";
		std::string amp = "&amp;";
		std::string gt = "&gt;";
		std::string lt = "&lt;";
		while(std::getline(file, line)){

			std::size_t found = line.find("text");
			std::size_t bold = line.find("text bold");
			std::size_t found2;

			if(found != std::string::npos && found != bold){
				std::getline(file, line);
				found = line.find("<");
				if(found != std::string::npos){}

				else{
					found = line.find(" ");
					if(found != std::string::npos){
						//std::cout << "thing" << "\n";
						found2 = line.find(" ", found + 2);
						if(found2 != std::string::npos){
							//std::cout << line + "\n";

							found = line.find(apos);
							while(found != std::string::npos){
								line.replace(found, 6, "\'");
								found = line.find(apos);
							}

							found = line.find(quot);
							while(found != std::string::npos){
								line.replace(found, 6, "\"");
								found = line.find(quot);
							}
							found = line.find(amp);
							while(found != std::string::npos){
								line.replace(found, 5, "&");
								found = line.find(amp);
							}
							found = line.find(gt);
							while(found != std::string::npos){
								line.replace(found, 4, ">");
								found = line.find(gt);
							}
							found = line.find(lt);
							while(found != std::string::npos){
								line.replace(found, 4, "<");
								found = line.find(lt);
							}

							//this->saveFile(savename, line);
							std::cout << line + "\n";

						}
						else{
							//this->saveFile(savename, line);
							//std::cout << line + "\n";
						}
					}
				}
			}

		}

		std::cout << "\n\n\n\n\n\n\n --TEST-- \n\n\n\n\n\n";

	}
	else{
		std::cout << "Shits broken";
	}
	file.close();
	*/

	//get the message id being replied to and the text that is the reply
	file.open(filename);
	if(file.is_open()){
		while(std::getline(file, line)){
			std::size_t found = line.find("In reply to <a");
			if(found != std::string::npos){
				//std::cout << line + "\n";
				//std::cout << line.substr(35, 7) << "\n";
				_replyID.push_back(line.substr(35, 7));


				bool temp = true;
				while(std::getline(file, line) && temp){
					std::size_t found = line.find("text");
					if(found != std::string::npos){
						std::getline(file, line);

						std::size_t link= line.find("<a href");
						std::size_t div = line.find("<div");
						if(link == std::string::npos && div == std::string::npos){
							//std::cout << line << "\n";

							//clean up
							std::string apos = "&apos;";
							std::string quot = "&quot;";
							std::string amp = "&amp;";
							std::string gt = "&gt;";
							std::string lt = "&lt;";
							found = line.find(apos);
							while(found != std::string::npos){
								line.replace(found, 6, "\'");
								found = line.find(apos);
							}
							found = line.find(quot);
							while(found != std::string::npos){
								line.replace(found, 6, "\"");
								found = line.find(quot);
							}
							found = line.find(amp);
							while(found != std::string::npos){
								line.replace(found, 5, "&");
								found = line.find(amp);
							}
							found = line.find(gt);
							while(found != std::string::npos){
								line.replace(found, 4, ">");
								found = line.find(gt);
							}
							found = line.find(lt);
							while(found != std::string::npos){
								line.replace(found, 4, "<");
								found = line.find(lt);
							}
							_replyMessage.push_back(line);
							temp = false;
						}

					}
				}
			}

		}
	}
	file.close();
	std::cout << "\n\n\n\n\n\n\n --TEST-- \n\n\n\n\n\n";

	//get the message that is being replied to
	file.open(filename);
	if(file.is_open()){
		while(std::getline(file, line)){
			std::size_t found = line.find("id=");

			if(found != std::string::npos){
				for(int i = 0; i < (signed) _replyID.size(); i++){
					std::size_t messageID = line.find(_replyID.at(i));
					if(messageID != std::string::npos){
						//std::cout << line << "\n";
						bool temp = true;
						while(std::getline(file, line) && temp){
							std::size_t found = line.find("text");
							if(found != std::string::npos){
								std::getline(file, line);

								//clean up
								std::string apos = "&apos;";
								std::string quot = "&quot;";
								std::string amp = "&amp;";
								std::string gt = "&gt;";
								std::string lt = "&lt;";
								found = line.find(apos);
								while(found != std::string::npos){
									line.replace(found, 6, "\'");
									found = line.find(apos);
								}
								found = line.find(quot);
								while(found != std::string::npos){
									line.replace(found, 6, "\"");
									found = line.find(quot);
								}
								found = line.find(amp);
								while(found != std::string::npos){
									line.replace(found, 5, "&");
									found = line.find(amp);
								}
								found = line.find(gt);
								while(found != std::string::npos){
									line.replace(found, 4, ">");
									found = line.find(gt);
								}
								found = line.find(lt);
								while(found != std::string::npos){
									line.replace(found, 4, "<");
									found = line.find(lt);
								}

								//std::cout << line << "\n";
								_repliedMessage.insert({_replyID.at(i), line});
								temp = false;
							}
						}
						if(_repliedMessage.find(_replyID.at(i)) != _repliedMessage.end()){
							int j = i + 1;
							bool thing = true;
							while(j < (signed) _replyID.size() && thing){
								if(_replyID.at(i) == _replyID.at(j)){
									_replyID[j] = _replyID.at(i) + "other";
									thing = false;
									_repliedMessage.insert({_replyID.at(j), line});
								}
								j++;
							}

						}
						else{
							_repliedMessage.insert({_replyID.at(i), line});
						}

					}
				}
			}

		}
	}
	file.close();

	std::cout << "\n\n\n\n\n test \n\n\n\n";
	std::cout << _replyMessage.size() << "\n";
	std::cout << _repliedMessage.size() << "\n";

	//export to file

	std::string temp = "";
	for(int i = 0; i < (signed) _replyID.size() && i < (signed) _replyMessage.size(); i++){
		if(_repliedMessage.find(_replyID.at(i)) != _repliedMessage.end()){

			temp +=_replyMessage.at(i);
			temp += " ||replies to|| ";
			temp += _repliedMessage.at(_replyID.at(i));
			temp += "\n";
			this->saveFile(savename, temp);
			std::cout << i;
			std::cout << temp;
			temp = "";
		}

	}
	_replyMessage.clear();
	_replyID.clear();
	_repliedMessage.clear();
}


void Reader::saveFile(std::string filename, std::string input){
	std::ofstream saveFile;
	saveFile.open(filename, std::ios_base::app);

	saveFile << input + "\n";
	saveFile.close();
}
