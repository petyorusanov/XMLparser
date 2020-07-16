#pragma once
#include<iostream>
#include<vector>
#include<cstring>
#include<fstream>
#include<string>
#include<stack>
#include "Element.h"
#include "DataStorage.h"

class XMLparser
{
private:
	fstream file;
	string currentReadData;
	string lastOpenedFile;
	DataStorage xmlTree;
	stack<Element*> currentReadElements;
	bool inTag;
	bool betweenTags;
	bool closingTag;
	bool hasId;
public:
	XMLparser();
	bool isOpen(); // checks if a file is open
	void Open(string fileName);
	void Close();
	void Save();
	void SaveAs(string directory);
	void Exit();
	void Print();

	void write(Element * localRoot, int balance);
	void parsePieceOfText();
};