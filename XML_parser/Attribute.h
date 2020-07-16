#pragma once
#include<string>
using namespace std;
class Attribute
{
private: 
	string key;
	string value;
public:
	Attribute();
	Attribute(string attrKey, string attrValue);
	~Attribute();
	Attribute& operator=(const Attribute& assigner);
	string getKey() const;
	string getValue() const;
	void setValue(string assignValue);
	void print() const;
};