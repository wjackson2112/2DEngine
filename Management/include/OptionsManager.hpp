#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <cstddef>

using boost::property_tree::ptree;
using std::string;

class OptionsManager
{
private:
	OptionsManager();
	~OptionsManager();

	ptree pt;
public:
	//Meyer's Singleton
	static OptionsManager& Instance()
	{
		static OptionsManager instance;
		return instance;
	}

	void write();
	void read();

	string 	getValue(string path);
	void   	setValue(string path, string value);
	void   	removeValue(string path);
};

#endif