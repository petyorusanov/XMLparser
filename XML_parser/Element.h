#pragma once
#include<iostream>
#include<vector>
#include<cassert>
#include<string>
#include "Attribute.h"
using namespace std;

class Element
{
private:
	vector<Attribute> attributes;
	vector<Element> subelements;
	string tag;
	string id;
	string text;
public:
	Element();
	~Element();
	Element(const char* assignTag, const char* assignId = " ", const char* assignText = " ");
	Element& operator=(const Element& toBeAdded);

	vector<Attribute> accessAttributes();
	vector<Element>* accessSubelements();

	vector<Element> getSubelements();
	string getTag() const;
	string getId() const;
	string getText() const;
	vector<Attribute> getAttributes() const;

	void addAttribute(string attributeKey, string attributeValue);
	void addSubElement(const Element& toBeAdded); // remove Element* toBeAdded
	void addEmptySubElement();
	void updateTag(string assignTag);
	void updateId(string assignId);
	void addText(string additionalText);
	void printText() const;
	void printAttributes() const;


	void updateElementId(Element* root, string id, int increment);
	bool checkId(Element localRoot, string id);
};