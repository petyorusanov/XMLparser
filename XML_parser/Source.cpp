#include<iostream>
#include<vector>
#include"XMLparser.h"
#include "Element.h"
using namespace std;



int main()
{
	XMLparser tester;
	string fileName("file1.txt");
	tester.Open(fileName);


	system("pause");
	return 0;
}