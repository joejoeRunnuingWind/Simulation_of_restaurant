#include "stdafx.h"
#include "Vip.h"


CVip::CVip(void)
{
	m_strBirthday = "";
}

CVip::CVip(DB_VIP_INFO info)
{
	setObjectName(info.szName);
	setVipBirthday(info.szBirthday);
}

CVip::~CVip(void)
{
}

void CVip::showInfo()
{
	printf("Name: %s Birthday: %s\n", getObjectName(), getVipBirthday());
}

const char* CVip::getVipBirthday()
{
	return m_strBirthday.c_str();
}

void CVip::setVipBirthday(char* day)
{
	if (day != NULL)
		m_strBirthday = day;
}

void CVip::getDataBaseInfo(DB_VIP_INFO& info)
{
	if (strlen(getObjectName()) < DB_LENGTH_MAX)
		strcpy(info.szName, getObjectName());

	if (strlen(getVipBirthday()) < DB_LENGTH_MAX)
		strcpy(info.szBirthday, getVipBirthday());
}

//////////////////////////////////////////////////////////////////////////
CVipManager::CVipManager()
{
	readFile();
}

CVipManager::~CVipManager()
{
}

void CVipManager::showMuen()
{
	int command;
	while (true)
	{
		command = 0;
		system("cls");
		cout << "Menu Vip..." << endl;
		cout << " 1. List VIP" << endl;
		cout << " 2. Add VIP" << endl;
		cout << " 3. Del VIP" << endl;
		cout << " 9. Return to previous menu" << endl;
		cout << "Vous avez de commander pour : ";

		cin >> command;
		switch (command)
		{
		case 1:
			listVip();
			break;
		case 2:
			addVip();
			break;
		case 3:
			delVip();
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

void CVipManager::listVip()
{
	if ( m_list.size() == 0 )
	{
		cout << "no info£¡";
		system("pause");
		return;
	}

	int i;
	cout << endl << "##### Vip info #####" << endl;

	for (i = 0; i < m_list.size(); i++)
	{
		cout << "Name: " << m_list[i].getObjectName() << " Birthday: " << m_list[i].getVipBirthday() << endl;
	}
	system("pause");
}

void CVipManager::addVip()
{
	CVip	vip;
	char	buffer[30];


	cout << "Enter the name: ";
	memset(buffer, 0, sizeof(buffer));
	while ( strlen(buffer) == 0 )					
	{
		cin >> buffer;
	}
	vip.setObjectName(buffer);


	cout << "Enter the birthday£¨19XX-XX-XX£©: ";
	memset(buffer, 0, sizeof(buffer));
	while ( strlen(buffer) == 0 )					
	{
		cin >> buffer;
	}
	vip.setVipBirthday(buffer);


	cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
	vip.showInfo();
	cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "confirm, save?£¨y/n£©£º ";
	char command;
	while (true)
	{
		cin >> command;
		if (command == 'y')
		{
			m_list.push_back(vip);
			writeFile();
			break;
		}
		else if (command == 'n')
		{
			break;
		}
	}
}

void CVipManager::addVip(CVip& vip)
{
	m_list.push_back(vip);
	writeFile();
}

void CVipManager::delVip()
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

		cout << endl << "##### delete #####" << endl;

		for (i = 0; i < m_list.size(); i++)
		{
			cout << i+1 << ". " << m_list[i].getObjectName() << endl;
		}

		cout << endl << "enter the number £¬0 to return£º ";
		cin >> idx;
		idx -= 1;
		if (idx == -1) 
			break;
		else if (idx < m_list.size())
		{
			cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
			m_list[idx].showInfo();
			cout << "confirm?£¨y/n£©";

			char command;
			while (true)
			{
				cin >> command;
				if (command == 'y')
				{
					vector< CVip >::iterator it = m_list.begin();
					int i = 0;
					for (;i<idx;i++)
					{
						it++;
					}
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

void CVipManager::readFile()
{
	fstream file;
	DB_VIP_INFO info;

	file.open("vip.db", ios::binary|ios::in|ios::out);
	if (file)
	{
		while(!file.eof())
		{
			file.read((char*)&info, sizeof(DB_VIP_INFO));
			if (file.gcount() != sizeof(DB_VIP_INFO))
				break;
			CVip* e = new CVip(info);
			m_list.push_back(*e);
			delete e;
		}
		file.close();
	}
}

void CVipManager::writeFile()
{
	fstream file;
	DB_VIP_INFO info;

	file.open("vip.db", ios::binary|ios::in|ios::out|ios::trunc);
	if (file)
	{
		int i = 0;
		for (;i<m_list.size();i++)
		{
			m_list[i].getDataBaseInfo(info);
			file.write((char*)&info, sizeof(DB_VIP_INFO));
		}
		file.close();
	}
}

bool CVipManager::VerifyVIP(string& name, string& pass)
{
	int i = 0;
	for (;i<m_list.size();i++)
	{
		if (name == m_list[i].getObjectName())
		{
			if (pass==m_list[i].getVipBirthday())
				return true;
		}
	}
	return false;
}