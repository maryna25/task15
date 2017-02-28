#include "XmlElement.h"

std::string XmlElement::toString(size_t indent) const
{
	std::ostringstream oss;
	std::string i(indent_size * indent, ' '); //to make it pretty
	oss << i << "<" << name << ">" << std::endl;
	if (text.size() > 0)
	{
		oss << std::string(indent_size *(indent + 1), ' ') << text << std::endl;
	}
	for (const auto elem : elements)
	{
		oss << elem.toString(indent+1);
	}
	oss << i << "</" << name << ">" << std::endl;
	return oss.str();
}

XmlBuilder XmlElement::create(const std::string &name)
{
	return XmlBuilder{ name };
}