#include "stdafx.h"
#include "employee.h"


CEmployee::CEmployee(void)
{
	m_nSex = EOS_NONE;
	m_nTravail = EOT_NONE;
}

CEmployee::CEmployee(DB_EMPLOYEE_INFO info)
{
	setObjectCode(info.szCode);
	setObjectName(info.szName);
	setSex((EMPLOYEE_OBJECT_SEX)info.nSex);
	setTravail((EMPLOYEE_OBJECT_TYPE)info.nTravail);
}

CEmployee::~CEmployee(void)
{
}

void CEmployee::showInfo()
{
	CObject::showInfo();

	printf("Sex: %s\n", m_nSex==EOS_MALE?"Male":"Famale");
	cout << "Travail: ";
	switch (m_nTravail)
	{
	case EOT_MANAGER:
		cout << "Manager" << endl;;
		break;

	case EOT_WAITER:
		cout << "Waiter" << endl;;
		break;

	case EOT_CHEF:
		cout << "Chef" << endl;;
		break;
	}
}

EMPLOYEE_OBJECT_SEX CEmployee::getSex()
{
	return m_nSex;
}

void CEmployee::setSex(EMPLOYEE_OBJECT_SEX sex)
{
	m_nSex = sex;
}

EMPLOYEE_OBJECT_TYPE CEmployee::getTravail()
{
	return m_nTravail;
}

void CEmployee::setTravail(EMPLOYEE_OBJECT_TYPE tyep)
{
	m_nTravail = tyep;
}

void CEmployee::getDataBaseInfo(DB_EMPLOYEE_INFO& info)
{
	if (strlen(getObjectCode()) < DB_LENGTH_MAX)
		strcpy(info.szCode, getObjectCode());

	if (strlen(getObjectName()) < DB_LENGTH_MAX)
		strcpy(info.szName, getObjectName());

	info.nSex = getSex();
	info.nTravail = getTravail();
}

//////////////////////////////////////////////////////////////////////////
CEmployeeManager::CEmployeeManager()
{
	readFile();
}

CEmployeeManager::~CEmployeeManager()
{
}

void CEmployeeManager::showMuen()
{
	int command;
	while (true)
	{
		command = 0;
		system("cls");
		cout << "Administration Employess..." << endl;
		cout << " 1. List Employess" << endl;
		cout << " 2. Add Employess" << endl;
		cout << " 3. Del Employess" << endl;
		cout << " 9. Return to previous menu" << endl;
		cout << "Vous avez de commander pour : ";

		cin >> command;

		switch (command)
		{
		case 1:
			listEmployee();
			break;
		case 2:
			addEmployee();
			break;
		case 3:
			delEmployee();
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

void CEmployeeManager::listEmployee()
{
	if ( m_list.size() == 0 )
	{
		cout << "No information！";
		system("pause");
		return;
	}

	int i;
	cout << endl << "##### Employees informations #####" << endl;

	for (i = 0; i < m_list.size(); i++)
	{
		cout << i+1 << ". " << m_list[i].getObjectName() << endl;
	}

	int command = -1;
	while (true)							//若不符合重新输入
	{
		cout << endl << "enter the number ，0 to return： ";
		cin >> command;

		if (command == 0) 
			break;
		else if (command <= m_list.size())
		{
			cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
			m_list[command-1].showInfo();
		}
		else
		{
			cin.clear();
			std::string t;
			std::getline(cin,t);
			cout << "Error！" << endl;
		}
	}
}

void CEmployeeManager::addEmployee()
{
	CEmployee	employee;
	char		buffer[30];

	// read the number
	cout << "Donnez le code d'un employee: ";		//between 1 and 20
	memset(buffer, 0, sizeof(buffer));

	while ( strlen(buffer) == 0 )					
	{
		cin >> buffer;
	}
	employee.setObjectCode(buffer);

	// read the name
	memset(buffer, 0, sizeof(buffer));
	cout << "Donnez le nom d'un employee: ";				
	while ( strlen(buffer) == 0 )							
	{
		cin >> buffer;
	}
	employee.setObjectName(buffer);
	
	
	int sex = EOS_NONE;
	cout << "1. Male" << endl << "2. Famale" << endl;	
	cout << "choose: ";
	while (sex != EOS_MALE && sex != EOS_FAMALE)							
	{
		cin >> sex;
		sex -= 1;
	}
	employee.setSex((EMPLOYEE_OBJECT_SEX)sex);

	
	
	cout << "1. patron" << endl << "2. serveur" << endl << "3. chef de cuisine" << endl;	
	cout << "Donnez son code de travail svp:";												
	int travail = EOT_NONE;
	while (travail == EOT_NONE || travail > EOT_MAX)
	{
		cin >> travail;
		travail -= 1;
	}
	employee.setTravail((EMPLOYEE_OBJECT_TYPE)travail);


	cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
	employee.showInfo();
	cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "confirm pls, save?（y/n）： ";
	char command;
	while (true)
	{
		cin >> command;
		if (command == 'y')
		{
			m_list.push_back(employee);
			writeFile();	
			break;
		}
		else if (command == 'n')
		{
			break;
		}
	}
}

void CEmployeeManager::delEmployee()
{
	int i;
	int idx = -1;

	while (true)							
	{
		if ( m_list.size() == 0 )
		{
			cout << "no information！";
			system("pause");
			return;
		}

		cout << endl << "##### delete #####" << endl;

		for (i = 0; i < m_list.size(); i++)
		{
			cout << i+1 << ". " << m_list[i].getObjectName() << endl;
		}

		cout << endl << "enter the number ，0 to return： ";
		cin >> idx;
		idx -= 1;
		if (idx == -1) 
			break;
		else if (idx < m_list.size())
		{
			cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
			m_list[idx].showInfo();
			cout << "confirm（y/n）";

			char command;
			while (true)
			{
				cin >> command;
				if (command == 'y')
				{
					vector< CEmployee >::iterator it = m_list.begin();
					int i = 0;
					for (;i<idx;i++)
					{
						it++;
					}
					m_list.erase(it);

					writeFile();	// save 
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
			cout << "Error！" << endl;
		}
	}
}

void CEmployeeManager::readFile()
{
	fstream file;
	DB_EMPLOYEE_INFO info;

	file.open("employee.db", ios::binary|ios::in|ios::out);
	if (file)
	{
		while(!file.eof())
		{
			file.read((char*)&info, sizeof(DB_EMPLOYEE_INFO));
			if (file.gcount() != sizeof(DB_EMPLOYEE_INFO))
				break;
			CEmployee* e = new CEmployee(info);
			m_list.push_back(*e);
			delete e;
		}
		file.close();
	}
}

void CEmployeeManager::writeFile()
{
	fstream file;
	DB_EMPLOYEE_INFO info;

	file.open("employee.db", ios::binary|ios::in|ios::out|ios::trunc);
	if (file)
	{
		int i = 0;
		for (;i<m_list.size();i++)
		{
			m_list[i].getDataBaseInfo(info);
			file.write((char*)&info, sizeof(DB_EMPLOYEE_INFO));
		}
		file.close();
	}
}