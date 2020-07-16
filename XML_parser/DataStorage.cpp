#include "DataStorage.h"
#include<iomanip>

DataStorage::DataStorage() : root(nullptr)
{

}

DataStorage::~DataStorage()
{
	delete root;
}

Element* DataStorage::findElementByID(Element localRoot, string elementId)
{
	if (!localRoot.getId().compare(elementId))
	{
		return &localRoot;
	}
	unsigned int i = 0;
	while (!localRoot.getSubelements().empty() && i < localRoot.getSubelements().size())
	{
		Element* temp = findElementByID(localRoot.getSubelements()[i], elementId);
		if (temp != nullptr)
		{
			return temp;
		}
		i++;
	}
	return nullptr;
}

bool DataStorage::Select(Element localRoot, string elementId, string attributeKey)
{
	if (!localRoot.getId().compare(elementId))
	{
		unsigned int i = 0;
		while (i < localRoot.accessAttributes().size() && !localRoot.accessAttributes()[i].getKey().compare(attributeKey))
		{
			i++;
		}
		if (i < localRoot.accessAttributes().size())
		{
			cout << "Element ID: " << elementId
				<< "\nAttribute key: " << attributeKey
				<< "\nAttribute value: " << localRoot.accessAttributes()[i].getKey() << endl;
		}
		else
		{
			cout << "Element with ID: " << elementId << " does not have an attribute with key: " << attributeKey << endl;
		}
		return true;
	}
	unsigned int i = 0;
	while (!localRoot.getSubelements().empty() && i < localRoot.getSubelements().size())
	{
		if (Select(localRoot.getSubelements()[i], elementId, attributeKey))
		{
			return true;
		}
		i++;
	}
	return false;
}

bool DataStorage::Set(Element localRoot, string elementId, string attributeKey, string assignValue)
{
	if (!localRoot.getId().compare(elementId))
	{
		unsigned int i = 0;
		while (i < localRoot.accessAttributes().size() && !localRoot.accessAttributes()[i].getKey().compare(attributeKey))
		{
			i++;
		}
		if (i < localRoot.accessAttributes().size())
		{
			localRoot.accessAttributes()[i].setValue(assignValue);
			cout << "New value set to: " << assignValue << endl;
		}
		else
		{
			cout << "Element with ID: " << elementId << " does not have an attribute with key: " << attributeKey << endl;
		}
		return true;
	}
	unsigned int i = 0;
	while (!localRoot.getSubelements().empty() && i < localRoot.getSubelements().size())
	{
		if (Set(localRoot.getSubelements()[i], elementId, attributeKey, assignValue))
		{
			return true;
		}
		i++;
	}
	return false;
}

vector<Attribute> DataStorage::Children(Element localRoot, string elementId)
{
	if (!localRoot.getId().compare(elementId))
	{
		vector<Attribute> store;
		for (unsigned int i = 0; i < localRoot.getSubelements().size(); i++)
		{
			store.resize(localRoot.getSubelements()[i].accessAttributes().size());
			for (unsigned int j = 0; j < localRoot.getSubelements()[i].accessAttributes().size(); j++)
			{
				store.push_back(localRoot.getSubelements()[i].accessAttributes()[j]);
			}
		}
		return store;
	}
	unsigned int i = 0;
	while (!localRoot.getSubelements().empty() && i < localRoot.getSubelements().size())
	{
		/*if (Children(root.getSubelements()[i], elementId) != vector<Attribute>())
		{
			return Children(root.getSubelements()[i], elementId);
		}*/
		/*return Children(root.getSubelements()[i], elementId);*/

		vector<Attribute> temp = Children(localRoot.getSubelements()[i], elementId);
		if (!temp.empty())
		{
			return temp;
		}
		i++;
	}
	return vector<Attribute>();
}

Element* DataStorage::Child(Element localRoot, string elementId, unsigned int n)
{
	if (!localRoot.getId().compare(elementId))
	{
		if (n >= localRoot.getSubelements().size())
		{
			return nullptr;
		}
		else
		{
			return &localRoot.getSubelements()[n];
		}
	}
	unsigned int i = 0;
	while (!localRoot.getSubelements().empty() && i < localRoot.getSubelements().size())
	{
		Element* temp = Child(localRoot.getSubelements()[i], elementId, n);
		if (temp != nullptr)
		{
			return temp;
		}
		i++;
	}
	return nullptr;
}

string DataStorage::Text(Element localRoot, string elementId)
{
	Element* temp(findElementByID(localRoot, elementId));
	return temp->getText();
}

bool DataStorage::Delete(Element localRoot, string elementId, string attributeKey)
{
	if (!localRoot.getId().compare(elementId))
	{
		unsigned int i = 0;
		while (localRoot.accessAttributes()[i].getKey().compare(attributeKey) && i < localRoot.accessAttributes().size())
		{
			i++;
		}
		localRoot.accessAttributes().erase(localRoot.accessAttributes().begin() + i);
		return true;
	}
	unsigned int i = 0;
	while (!localRoot.getSubelements().empty() && i < localRoot.getSubelements().size())
	{
		if (Delete(localRoot.getSubelements()[i], elementId, attributeKey))
		{
			return true;
		}
		i++;
	}
	return false;
}

bool DataStorage::NewChild(Element localRoot, string elementId)
{
	if (!localRoot.getId().compare(elementId))
	{
		string newId;
		newId.resize(strlen("new_element"));
		newId.assign("new_element");
		localRoot.addEmptySubElement();
		localRoot.accessSubelements()->back().updateElementId(root, newId, 0);
		return true;
	}
	unsigned int i = 0;
	while (!localRoot.getSubelements().empty() && i < localRoot.getSubelements().size())
	{
		if (NewChild(localRoot.getSubelements()[i], elementId))
		{
			return true;
		}
		i++;
	}
	return false;
}

void DataStorage::Print(Element * localRoot, int balance)
{
	cout << setw(balance * 10) << "<" << localRoot->getTag() << " '" << localRoot->getId() << "'";
	localRoot->printAttributes();
	cout << ">" << endl;
	cout << setw((balance + 1) * 10) << localRoot->getText() << endl;
	if (localRoot->getSubelements().empty())
	{
		return;
	}
	unsigned int i = 0;
	while (i < localRoot->getSubelements().size())
	{
		Print(&localRoot->getSubelements()[i], balance + 1);
		i++;
	}
	return;
}

Element * DataStorage::accessRoot()
{
	return root;
}

void DataStorage::addRoot()
{
	root = new Element();
}