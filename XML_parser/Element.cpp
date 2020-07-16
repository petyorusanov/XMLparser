#include "Element.h"



Element::Element() : attributes(), subelements(), tag(), id(), text()
{
	
}

Element::Element(const char * assignTag, const char * assignId, const char * assignText) 
	: attributes(), subelements(), tag(assignTag), id(assignId), text(assignText)
{
	
}

Element & Element::operator=(const Element & toBeAdded)
{
	attributes = toBeAdded.attributes;
	subelements = toBeAdded.subelements;
	tag = toBeAdded.tag;
	id = toBeAdded.id;
	text = toBeAdded.text;
	return *this;
}

vector<Element> Element::getSubelements()
{
	return subelements;
}

string Element::getTag() const
{
	return tag;
}

vector<Attribute> Element::accessAttributes()
{
	return attributes;
}

vector<Element>* Element::accessSubelements()
{
	return &subelements;
}

void Element::addAttribute(string attributeKey, string attributeValue)
{
	if (attributes.size() == attributes.capacity())
	{
		attributes.resize(1);
	}
	attributes.push_back(Attribute(attributeKey, attributeValue));
}

void Element::addSubElement(const Element& toBeAdded)
{
	if (subelements.size() == subelements.capacity())
	{
		subelements.resize(1);
	}
	subelements.push_back(toBeAdded);
}

void Element::addEmptySubElement()
{
	if (subelements.size() == subelements.capacity())
	{
		subelements.resize(1);
	}
	subelements.push_back(Element());
}

void Element::updateTag(string assignTag)
{
	tag.resize(assignTag.size());
	tag.assign(assignTag);
}

Element::~Element()
{

}

string Element::getId() const
{
	return id;
}

string Element::getText() const
{
	return text;
}

vector<Attribute> Element::getAttributes() const
{
	return attributes;
}

void Element::updateId(string assignId)
{
	id.resize(assignId.size());
	id.assign(assignId);
}

void Element::addText(string additionalText)
{
	text.resize(additionalText.size());
	text.append(additionalText);
}

void Element::printText() const
{
	cout << text << endl;
}

void Element::printAttributes() const
{
	unsigned int i = 0;
	while (i < attributes.size())
	{
		attributes[i].print();
		i++;
	}
}

//int Element::getDepth()
//{
//	return 0;
//}



void Element::updateElementId(Element* root, string assignId, int increment)
{
	string temp;
	if (increment > 0)
	{
		string inc;
		inc.resize(10);
		temp.resize(assignId.size() + to_string(increment).size() + 1);
		temp.append(assignId);
		temp.append("_");
		temp.append(to_string(increment));
	}
	else
	{
		temp.resize(assignId.size());
		temp.append(assignId);
	}
	if (!checkId(*root, temp))
	{
		if (assignId.compare(temp))
		{
		/*	assignId.append(temp);*/
			id.assign(assignId);
		}
	}
	else
	{
		updateElementId(root, assignId, increment + 1);
	}
}

bool Element::checkId(Element localRoot, string assignId)
{
	if (!localRoot.getId().compare(assignId))
	{
		return true;
	}
	unsigned int i = 0;
	while (!localRoot.getSubelements().empty() && i < localRoot.getSubelements().size())
	{
		if (checkId(localRoot.getSubelements()[i], assignId))
		{
			return true;
		}
		i++;
	}
	return false;
}