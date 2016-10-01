#include "OptionsManager.hpp"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/detail/xml_parser_writer_settings.hpp>

OptionsManager::OptionsManager()
{
	read();
}

OptionsManager::~OptionsManager()
{
	write();
}

void OptionsManager::write()
{
	write_xml("options.xml", pt, std::locale(), 
		boost::property_tree::xml_parser::xml_writer_make_settings('\t', 1));
}

void OptionsManager::read()
{
	read_xml("options.xml", pt, boost::property_tree::xml_parser::trim_whitespace);
}

string OptionsManager::getValue(string path)
{
	return pt.get<std::string>(path);
}

void OptionsManager::setValue(string path, string value)
{
	pt.put(path, value);
}

void OptionsManager::removeValue(string path)
{
	std::size_t last_period;
	string path_to;
	string child;
	do
	{
		last_period = path.find_last_of(".");
		path_to = path.substr(0, last_period);
		child = path.substr(path.find_last_of(".") + 1);

		//If there isn't a period in the path because this is a root node
		if(path_to.compare(child) == 0)
		{
			pt.erase(path_to);
			break;
		}

		//Otherwise just erase the child
		else
		{
			pt.get_child(path_to).erase(child);
		}

		//If the upper node is now empty, advance up the path and delete it too
		path = path_to;
	} while(pt.get_child(path_to).empty());
}