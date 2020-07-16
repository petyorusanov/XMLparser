#pragma once
#include<vector>
#include<cstring>
#include "Element.h"
class DataStorage
{
private:
	Element* root;
public:
	DataStorage();
	~DataStorage();
	Element* findElementByID(Element localRoot, string elementId);
	bool Select(Element localRoot, string elementId, string attributeKey);
	bool Set(Element localRoot, string elementId, string attributeKey, string assignValue);
	vector<Attribute> Children(Element localRoot, string elementId);
	Element* Child(Element localRoot, string elementId, unsigned int n);
	string Text(Element localRoot, string elementId);
	bool Delete(Element localRoot, string elementId, string attributeKey);
	bool NewChild(Element localRoot, string elementId);
	void Print(Element* localRoot, int balance);

	Element* accessRoot();
	void addRoot();
};