#define CATCH_CONFIG_RUNNER 
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "XmlElement.h"

_Uint32t check(const std::string &str);

void txtToXml(std::string txtFile);

TEST_CASE("Checking to_string()")
{
	XmlElement el("title");
	REQUIRE(el.toString() == "<title>\n</title>\n");

	XmlElement el1("title","someText");
	REQUIRE(el1.toString() == "<title>\n    someText\n</title>\n");
}

TEST_CASE("checking check()")
{
	REQUIRE(check("") == 0);
	REQUIRE(check("q") == 113);
	REQUIRE(check("q q") == 258);
	REQUIRE(check("q q\n") == 268);
}

TEST_CASE("checking txtToXml()")
{
	txtToXml("file");
	std::ifstream f1 ("file.xml");
	std::string s;
	std::getline(f1, s);
	REQUIRE(s == "<article>");
	std::getline(f1, s);
	REQUIRE(s == "    <title>");
	std::getline(f1, s);
	REQUIRE(s == "        Food");
	std::getline(f1, s);
	REQUIRE(s == "    </title>");
	std::getline(f1, s);
	REQUIRE(s == "    <athor>");
	std::getline(f1, s);
	REQUIRE(s == "        Maryna");
	std::getline(f1, s);
	REQUIRE(s == "    </athor>");
	std::getline(f1, s);
	REQUIRE(s == "    <body>");
	std::getline(f1, s);
	REQUIRE(s == "        Meat Fish");
	std::getline(f1, s);
	REQUIRE(s == "    </body>");
	std::getline(f1, s);
	REQUIRE(s == "    <hash>");
	std::getline(f1, s);
	REQUIRE(s == "        817");
	std::getline(f1, s);
	REQUIRE(s == "    </hash>");
	std::getline(f1, s);
	REQUIRE(s == "</article>");
	f1.close();
}

int main(int argc, char* argv[])
{
	/*txtToXml("file");
	system("pause");
	return 0;*/

	int result = Catch::Session().run(argc, argv);
	getchar();
	return result;
}

void txtToXml(std::string txtFile)
{
	std::string line;
	std::ifstream in(txtFile + ".txt");
	std::getline(in, line);
	auto article = XmlElement::create("article").addElement("title", line);
	std::getline(in, line);
	article.addElement("athor", line);
	std::string body;
	while (!in.eof())
	{
		std::getline(in, line);
		if (!in.eof()) body += line + '\n';
	}
	body.resize(body.length() - 1);
	line.erase(line.begin(), line.begin() + 3);
	article.addElement("body", body).addElement("hash", line);
	in.close();
	_Uint32t hash;
	std::stringstream(line) >> hash;
	if (hash != check(body)) std::cout << "Hash mismatch";
	else
	{
		std::ofstream out(txtFile + ".xml");
		out << article.toStr();
		out.close();
	}
};

_Uint32t check(const std::string &str)
{
	_Uint32t sum = 0;
	for (auto c : str) sum += c;
	return sum;
}