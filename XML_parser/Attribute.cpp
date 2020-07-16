#include "Attribute.h"
#include<iostream>


Attribute::Attribute() : key(), value()
{

}

Attribute::Attribute(string attrKey, string attrValue)
{
	key.resize(attrKey.size());
	key.assign(attrKey);
	value.resize(attrValue.size());
	value.assign(attrValue);
}

Attribute::~Attribute()
{

}

Attribute & Attribute::operator=(const Attribute & assigner)
{
	key.resize(assigner.key.size());
	key = assigner.getKey();
	value.resize(assigner.value.size());
	value = assigner.getValue();
	return *this;
}

string Attribute::getKey() const
{
	return key;
}

string Attribute::getValue() const
{
	return value;
}

void Attribute::setValue(string assignValue)
{
	value.resize(assignValue.size());
	value.assign(assignValue);
}

void Attribute::print() const
{
	cout << " " << key << "='" << value << "'";
}
