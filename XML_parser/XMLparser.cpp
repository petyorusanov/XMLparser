#include "XMLparser.h"
#include <iomanip>

XMLparser::XMLparser() : file(), currentReadData(), lastOpenedFile(), xmlTree(), currentReadElements()
{
	inTag = false;
	betweenTags = false;
	closingTag = false;
	hasId = false;
}

bool XMLparser::isOpen()
{
	return file.is_open();
}

void XMLparser::Open(string fileName)
{
	file.open(fileName, ios::in);
	lastOpenedFile.resize(fileName.size());
	lastOpenedFile.assign(fileName);
	getline(file, currentReadData);
	while (!file.eof())
	{
		getline(file, currentReadData);
		parsePieceOfText();
	}
	Close();
}

void XMLparser::Close()
{
	file.close();
}

void XMLparser::Save()
{
	file.open(lastOpenedFile, ios::out);
	write(xmlTree.accessRoot(), 0);
}

void XMLparser::SaveAs(string directory)
{

}

void XMLparser::Exit()
{
}

void XMLparser::Print()
{
	xmlTree.Print(xmlTree.accessRoot(), 0);
}

void XMLparser::write(Element * localRoot, int balance)
{
	file << setw(balance * 10 + localRoot->getTag().size() + localRoot->getId().size()) << "<" << localRoot->getTag() << " '" << localRoot->getId() << "'";
	unsigned int i = 0;
	while(i < localRoot->getAttributes().size())
	{
		file << " " << localRoot->getAttributes()[i].getKey() << "='" << localRoot->getAttributes()[i].getValue() << "'";
	}
	file << ">" << endl;
	file << setw((balance + 1) * 10 + localRoot->getText().size()) << localRoot->getText() << endl;
	if (localRoot->getSubelements().empty())
	{
		return;
	}
	i = 0;
	while (i < localRoot->getSubelements().size())
	{
		write(&localRoot->getSubelements()[i], balance + 1);
		i++;
	}
	return;
}

void XMLparser::parsePieceOfText()
{
	unsigned int i = 0;
	while (i < currentReadData.size())
	{
		if (currentReadData[i] == ' ')
		{
			i++;
		}
		if (currentReadData[i] == '<')
		{
			inTag = true;
			betweenTags = false;
			if (currentReadData[i + 1] != '/')
			{
				unsigned int j = i + 2;
				int quotesCounter = 0;
				while (currentReadData[j] != '>' && !closingTag) // checks if the tag is closing 
				{
					if (currentReadData[j] == '"')
					{
						quotesCounter++;
					}
					else if (currentReadData[j] == '/' && quotesCounter % 2 == 0) // checks if we are outside of attribute text
					{
						closingTag = true;
					}
					j++;
				}
				if (!currentReadElements.empty())
				{
					currentReadElements.top()->addEmptySubElement();
					currentReadElements.push(&currentReadElements.top()->accessSubelements()->back());
				}
				else
				{
					xmlTree.addRoot();
					currentReadElements.push(xmlTree.accessRoot());
				}
				i++;
				if (currentReadData[i] != ' ')
				{
					string currentElementTag;
					unsigned int j = i;
					while (currentReadData[j + 1] != ' ' && currentReadData[j + 1] != '>')
					{
						j++;
					}
					currentElementTag.resize(j - i + 2);
					for (unsigned int k = 0; k <= j - i; k++)
					{
						currentElementTag[k] = currentReadData[i];
						i++;
					}
					currentReadElements.top()->updateTag(currentElementTag);
				}
			}
			else
			{
				closingTag = true;
			}
		}
		if (currentReadData[i] == '>' && inTag)
		{
			inTag = false;
			if (currentReadData[i + 1] < currentReadData.size())
			{
				betweenTags = true;
			}
			if (closingTag)
			{
				currentReadElements.pop();
				closingTag = false;
			}
			hasId = false;
		}
		if (currentReadData[i] == 'i' && currentReadData[i + 1] == 'd' && currentReadData[i + 2] == '=' && inTag)
		{
			i += 4;
			hasId = true;
			if (currentReadData[i] == '"')
			{
				currentReadElements.top()->updateElementId(xmlTree.accessRoot(), "auto_generated", 0);
			}
			else
			{
				string currentElementId;
				unsigned int j = i;
				while (currentReadData[j + 1] != '"')
				{
					j++;
				}
				currentElementId.resize(j - i + 2);
				for (unsigned int k = 0; k <= j - i; k++)
				{
					currentElementId[k] = currentReadData[i];
					i++;
				}
				i++;
				currentReadElements.top()->updateElementId(xmlTree.accessRoot(), currentElementId, 0);
			}
		}
		if (inTag && !hasId)
		{
			currentReadElements.top()->updateElementId(xmlTree.accessRoot(), "auto_generated", 0);
			hasId = true;
		}
		if (betweenTags)
		{
			while (currentReadData[i] == ' ' && i < currentReadData.size())
			{
				i++;
			}
			if (i < currentReadData.size() && currentReadData[i] != '<')
			{
				string currentReadText;
				unsigned int j = i;
				while (j < currentReadData.size())
				{
					j++;
				}
				currentReadText.resize(j - i + 1);
				for (unsigned int k = 0; k < j - i; k++)
				{
					currentReadText[k] = currentReadData[i];
					i++;
				}
				currentReadElements.top()->addText(currentReadText);
			}
		}
		else if (inTag && currentReadData[i] != '>' && currentReadData[i] != '/' && currentReadData[i] != ' ' && hasId) // adds attributes
		{
			string currentAttributeKey;
			string currentAttributeValue;
			unsigned int j = i;
			while (currentReadData[j + 1] != '=')
			{
				j++;
			}
			currentAttributeKey.resize(j - i + 2);
			for (unsigned int k = 0; k <= j - i; k++)
			{
				currentAttributeKey[k] = currentReadData[i];
				i++;
			}
			i += 2;
			if (currentReadData[i] != '"')
			{
				j = i;
				while (currentReadData[j + 1] != '"')
				{
					j++;
				}
				currentAttributeValue.resize(j - i + 2);
				for (unsigned int k = 0; k <= j - i; k++)
				{
					currentAttributeValue[k] = currentReadData[i];
					i++;
				}
				i++;
			}
			currentReadElements.top()->addAttribute(currentAttributeKey, currentAttributeValue);
		}
	}
}