#pragma once
#include <iostream>

class Data {
public:
	int m_ID;
	std::string m_Name;
	int m_Quantity;
	int m_Price;

	Data(int ID, std::string Name, int Quantity, int Price)
	{
		this->m_ID = ID;
		this->m_Name = Name;
		this->m_Quantity = Quantity;
		this->m_Price = Price;
	}
};

std::ostream& operator << (std::ostream& stream, Data& obj)
{
	stream << obj.m_ID << "," << obj.m_Name << "," << obj.m_Quantity << "," << obj.m_Price;
	return stream;
}

class Hashtable {
private:
	int m_Keys;
	std::vector<std::pair<int, Data* >>* m_Table;
public:

	Hashtable(int Keys)
	{
		this->m_Keys = Keys;
		m_Table = new std::vector<std::pair<int, Data* >>[Keys];
	}

	int getHashIndex(int Key)
	{
		return (Key % this->m_Keys);
	}

	void insert(int ID, std::string Name, int Quantity, int Price)
	{
		int Index = getHashIndex(ID);
		m_Table[Index].push_back(std::make_pair(ID, (new Data(ID, Name, Quantity, Price))));
	}

	Data getObjectFromKey(int Key)
	{
		int Index = getHashIndex(Key);
		for (size_t i = 0; i < m_Table[Index].size(); i++)
		{
			if (m_Table[Index][i].first == Key)
			{
				return *(m_Table[Index][i].second);
			}
		}
	}

	void deleteObjectFromKey(int Key)
	{
		int Index = getHashIndex(Key);
		for (size_t i = 0; i < m_Table[Index].size(); i++)
		{
			if (m_Table[Index][i].first == Key)
			{
				delete m_Table[Index][i].second;
				m_Table[Index][i].second = NULL;
				m_Table[Index].erase(m_Table[Index].begin() + i);
				return;
			}
		}
	}

	void editObjectFromKey(int Key, std::string Name, int Quantity, int Price)
	{
		int Index = getHashIndex(Key);
		for (size_t i = 0; i < m_Table[Index].size(); i++)
		{
			if (m_Table[Index][i].first == Key)
			{
				m_Table[Index][i].second->m_Name = Name;
				m_Table[Index][i].second->m_Quantity = Quantity;
				m_Table[Index][i].second->m_Price = Price;
				break;
			}
		}
	}

	void setQuantityFromKey(int Key,  int Quantity)
	{
		int Index = getHashIndex(Key);
		for (size_t i = 0; i < m_Table[Index].size(); i++)
		{
			if (m_Table[Index][i].first == Key)
			{
				if (Quantity == 0)
					deleteObjectFromKey(Key);
				else 
					m_Table[Index][i].second->m_Quantity = Quantity;
				
				break;
			}
		}
	}

	bool isKeyExist(int Key)
	{
		int Index = getHashIndex(Key);
		for (size_t i = 0; i < m_Table[Index].size(); i++)
		{
			if (m_Table[Index][i].first == Key)
			{
				return true;
			}
		}
		return false;
	}

	void printAll()
	{
		for (int i = 0; i < m_Keys; i++)
		{
			std::cout << "[" << i << "] = ";
			for (size_t j = 0; j < m_Table[i].size(); j++)
			{
				std::cout << m_Table[i][j].first << " : {" << *(m_Table[i][j].second) << "} , ";
			}
			std::cout << std::endl;
		}
	}

	// Operator
	Data operator [](int Key)
	{
		return (this->getObjectFromKey(Key));
	}
};
