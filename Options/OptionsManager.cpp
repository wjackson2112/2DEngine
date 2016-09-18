#include "OptionsManager.hpp"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/detail/xml_parser_writer_settings.hpp>

OptionsManager* OptionsManager::instance = NULL;

OptionsManager* OptionsManager::Instance()
{
	if(!instance)
	{
		instance = new OptionsManager();
	}

	return instance;
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