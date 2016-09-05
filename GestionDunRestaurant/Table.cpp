#include "stdafx.h"
#include "Table.h"

CTable::CTable()
{
	m_nID = 0;
	m_nSeatNum = 0;
	m_nState = true;
}

CTable::CTable(DB_TABLE_INFO info)
{
	setTableID(info.nID);
	setTableSeatNumber(info.nSeatNum);
	if (info.bState)
		checkOut();
	else
		checkIn();
}

CTable::~CTable()
{
}

void CTable::showInfo()
{
	printf("%d table number of chairs: %d state: %s\n", getTableID(), getTableSeatNumber(), getTableState()?"not in use":"in use");
}

int CTable::getTableID()
{
	return m_nID;
}

void CTable::setTableID(int id)
{
	if (id != 0)
		m_nID = id;
}

int CTable::getTableSeatNumber()
{
	return m_nSeatNum;
}

void CTable::setTableSeatNumber(int num)
{
	if (num != 0)
		m_nSeatNum = num;
}

bool CTable::getTableState()
{
	return m_nState;
}

void CTable::checkIn()
{
	m_nState = false;
}

void CTable::checkOut()
{
	m_nState = true;
}

void CTable::getDataBaseInfo(DB_TABLE_INFO& info)
{
	info.nID = getTableID();
	info.nSeatNum = getTableSeatNumber();
	info.bState = getTableState();
}

//////////////////////////////////////////////////////////////////////////

CTableManager::CTableManager()
{
	readFile();
}

CTableManager::~CTableManager()
{
}

void CTableManager::showMuen()
{
	int command;
	while (true)
	{
		command = 0;
		system("cls");
		cout << "menu table..." << endl;
		cout << " 1. List Table" << endl;
		cout << " 2. Add Table" << endl;
		cout << " 3. Del Table" << endl;
		cout << " 4. Set all tables not in use" << endl;
		cout << " 9. Return to previous menu" << endl;
		cout << "Vous avez de commander pour : ";

		cin >> command;

		switch (command)
		{
		case 1:
			listTable();
			break;
		case 2:
			addTable();
			break;
		case 3:
			delTable();
			break;
		case 4:
			for (int i=0; i<m_list.size(); i++)
				m_list[i].checkOut();
			writeFile();	
			break;
		case 9:
			return;
		default:
			cin.clear();
			std::string t;
			std::getline(cin,t);
			break;
		}
	}
}

void CTableManager::listTable()
{
	if ( m_list.size() == 0 )
	{
		cout << "no info£¡";
		system("pause");
		return;
	}

	int i;
	cout << endl << "##### table info #####" << endl;

	for (i = 0; i < m_list.size(); i++)
	{
		m_list[i].showInfo();
	}

	system("pause");
}

void CTableManager::addTable()
{
	CTable	table;


	int id = 0;
	cout << "number of table: ";		
	while ( id == 0 )					
	{
		cin >> id;
	}
	table.setTableID(id);


	int num = 0;
	cout << "enter the number of chairs: ";				
	while ( num == 0 )							
	{
		cin >> num;
	}
	table.setTableSeatNumber(num);

	
	cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
	table.showInfo();
	cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "confirm, save?£¨y/n£©£º ";
	char command;
	while (true)
	{
		cin >> command;
		if (command == 'y')
		{
			m_list.push_back(table);
			writeFile();	
			break;
		}
		else if (command == 'n')
		{
			break;
		}
	}
}

void CTableManager::delTable()
{
	int i;
	int idx = -1;

	while (true)							
	{
		if ( m_list.size() == 0 )
		{
			cout << "no info£¡";
			system("pause");
			return;
		}

		cout << endl << "##### delete info #####" << endl;

		for (i = 0; i < m_list.size(); i++)
		{
			m_list[i].showInfo();
		}

		cout << endl << "enter the number £¬0 to return£º ";
		cin >> idx;
		if (idx == 0) 
			break;
		else
		{
			vector< CTable >::iterator it = m_list.begin();
			
			while ( it != m_list.end() )
			{
				if ( it->getTableID() == idx )
					break;
				it++;
			}

			if ( it != m_list.end() )
			{
				cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
				it->showInfo();
				cout << "confirm£¨y/n£©";

				char command;
				while (true)
				{
					cin >> command;
					if (command == 'y')
					{
						m_list.erase(it);
						writeFile();	
						break;
					}
					else if (command == 'n')
					{
						break;
					}
				}
				
			}
			else
			{
				cin.clear();
				std::string t;
				std::getline(cin,t);
				cout << "Error£¡" << endl;
			}

		}
	}
}

void CTableManager::readFile()
{
	fstream file;
	DB_TABLE_INFO info;

	file.open("table.db", ios::binary|ios::in|ios::out);
	if (file)
	{
		while(!file.eof())
		{
			file.read((char*)&info, sizeof(DB_TABLE_INFO));
			if (file.gcount() != sizeof(DB_TABLE_INFO))
				break;
			CTable* e = new CTable(info);
			m_list.push_back(*e);
			delete e;
		}
		file.close();
	}
}

void CTableManager::writeFile()
{
	fstream file;
	DB_TABLE_INFO info;

	file.open("table.db", ios::binary|ios::in|ios::out|ios::trunc);
	if (file)
	{
		int i = 0;
		for (;i<m_list.size();i++)
		{
			m_list[i].getDataBaseInfo(info);
			file.write((char*)&info, sizeof(DB_TABLE_INFO));
		}
		file.close();
	}
}

CTable* CTableManager::getTableInfo(int idx)
{
	if (idx >= 0 && idx < m_list.size())
		return &m_list[idx];
	return NULL;
}

void CTableManager::checkIn(int id)
{
	int i = 0;
	for (;i<m_list.size();i++)
	{
		if (m_list[i].getTableID()==id)
		{
			m_list[i].checkIn();
			return;
		}
	}
}

void CTableManager::checkOut(int id)
{
	int i = 0;
	for (;i<m_list.size();i++)
	{
		if (m_list[i].getTableID()==id)
		{
			m_list[i].checkOut();
			return;
		}
	}
}