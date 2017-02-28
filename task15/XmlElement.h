#pragma once
#include <string>
#include <sstream>
#include <vector>

class XmlBuilder;
class XmlElement
{
	friend class XmlBuilder;
	std::string name;
	std::string text;
	std::vector<XmlElement> elements;
	const static size_t indent_size = 4;
public:
	XmlElement()
	{}
	XmlElement(const std::string &name, const std::string &text ="") : name( name ), text( text )
	{}
	virtual ~XmlElement()
	{};
	std::string toString(size_t indent = 0) const;

	static XmlBuilder create(const std::string &name);
};

class XmlBuilder
{
	typedef XmlBuilder& Self;

	XmlElement root;
public:
	XmlBuilder(const std::string &name) : root(name){};

	Self addElement(const std::string &name, const std::string &text)
	{
		root.elements.emplace_back(name, text);
		return *this;
	};
	std::string toStr() const
	{
		return root.toString();
	}
	operator XmlElement()
	{
		return root;
	}
};
