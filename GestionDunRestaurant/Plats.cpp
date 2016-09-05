#include "stdafx.h"
#include "Plats.h"


CPlats::CPlats(void)
{
	m_nTyep = POT_NONE;
	m_fPrixP = 0;
	m_fPrixS = 0;
}

CPlats::CPlats(DB_PLATS_INFO info)
{
	setObjectName(info.szName);
	setPlatsTyep((PLATS_OBJECT_TYPE)info.nTyep);
	setPlatsPrixP(info.fPrixP);
	setPlatsPrixS(info.fPrixS);
}

CPlats::~CPlats(void)
{
}

void CPlats::showInfo()
{
	printf("[%s] ", getObjectName());

	switch (getPlatsType())
	{
	case POT_ENTREE:
		cout << "Entree ";
		break;

	case POT_PLAT:
		cout << "Plat ";
		break;

	case POT_DESSERT:
		cout << "Dessetr ";
		break;

	case POT_BOISSON:
		cout << "Boisson ";
		break;
	}

	cout << getPlatsPrixP() << "/" << getPlatsPrixS() << endl;
}

PLATS_OBJECT_TYPE CPlats::getPlatsType()
{
	return m_nTyep;
}

void CPlats::setPlatsTyep(PLATS_OBJECT_TYPE type)
{
	m_nTyep = type;
}

float CPlats::getPlatsPrixP()
{
	return m_fPrixP;
}

void CPlats::setPlatsPrixP(float val)
{
	m_fPrixP = val;
}

float CPlats::getPlatsPrixS()
{
	return m_fPrixS;
}

void CPlats::setPlatsPrixS(float val)
{
	m_fPrixS = val;
}

void CPlats::getDataBaseInfo(DB_PLATS_INFO& info)
{
	if (strlen(getObjectName()) < DB_LENGTH_MAX)
		strcpy(info.szName, getObjectName());

	info.nTyep = getPlatsType();
	info.fPrixP = getPlatsPrixP();
	info.fPrixS = getPlatsPrixS();
}

//////////////////////////////////////////////////////////////////////////

CCPlatsManager::CCPlatsManager()
{
	readFile();
}

CCPlatsManager::~CCPlatsManager()
{

}

void CCPlatsManager::showMuen()
{
	int command;
	while (true)
	{
		command = 0;
		system("cls");
		cout << "Menu plats..." << endl;
		cout << " 1. List Plats" << endl;
		cout << " 2. Add Plats" << endl;
		cout << " 3. Del Plats" << endl;
		cout << " 9. Return to previous menu" << endl;
		cout << "Vous avez de commander pour : ";

		cin >> command;

		switch (command)
		{
		case 1:
			listPlats();
			break;
		case 2:
			addPlats();
			break;
		case 3:
			delPlats();
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

void CCPlatsManager::listPlats()
{
	if ( m_list.size() == 0 )
	{
		cout << "no information£¡";
		system("pause");
		return;
	}

	int i;
	cout << endl << "##### plats infos #####" << endl;

	for (i = 0; i < m_list.size(); i++)
	{
		cout << i+1 << ". " << m_list[i].getObjectName() << endl;
	}

	int command = -1;
	while (true)							//reenter
	{
		cout << endl << "enter the number £¬0 to return£º ";
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
			cout << "Error£¡" << endl;
		}
	}
}

void CCPlatsManager::addPlats()
{
	CPlats	plats;
	char	buffer[30];


	memset(buffer, 0, sizeof(buffer));
	cout << "Donnez le nom d'un plats: ";				
	while ( strlen(buffer) == 0 )							
	{
		cin >> buffer;
	}
	plats.setObjectName(buffer);


	int type = POT_NONE;
	cout << "1. entree" << endl << "2. plat" << endl << "3. dessert" << endl << "4. boisson" << endl;
	cout << "son type: ";
	while (type == POT_NONE || type > POT_MAX)							
	{
		cin >> type;
		type -= 1;
	}
	plats.setPlatsTyep((PLATS_OBJECT_TYPE)type);

	
	float prixP, prixS;
	cout << "son prix: ";
	cin >> prixP;
	cout << "cout de plat: ";
	cin>>prixS;

	plats.setPlatsPrixP(prixP);
	plats.setPlatsPrixS(prixS);

	
	cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
	plats.showInfo();
	cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "confirm, save?£¨y/n£©£º ";
	char command;
	while (true)
	{
		cin >> command;
		if (command == 'y')
		{
			m_list.push_back(plats);
			writeFile();	
			break;
		}
		else if (command == 'n')
		{
			break;
		}
	}
}

void CCPlatsManager::delPlats()
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
			cout << "confirm£¨y/n£©";

			char command;
			while (true)
			{
				cin >> command;
				if (command == 'y')
				{
					vector< CPlats >::iterator it = m_list.begin();
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

void CCPlatsManager::readFile()
{
	fstream file;
	DB_PLATS_INFO info;

	file.open("plats.db", ios::binary|ios::in|ios::out);
	if (file)
	{
		while(!file.eof())
		{
			file.read((char*)&info, sizeof(DB_PLATS_INFO));
			if (file.gcount() != sizeof(DB_PLATS_INFO))
				break;
			CPlats* e = new CPlats(info);
			m_list.push_back(*e);
			delete e;
		}
		file.close();
	}
}

void CCPlatsManager::writeFile()
{
	fstream file;
	DB_PLATS_INFO info;

	file.open("plats.db", ios::binary|ios::in|ios::out|ios::trunc);
	if (file)
	{
		int i = 0;
		for (;i<m_list.size();i++)
		{
			m_list[i].getDataBaseInfo(info);
			file.write((char*)&info, sizeof(DB_PLATS_INFO));
		}
		file.close();
	}
}

CPlats*	CCPlatsManager::getPlatsInfo(int index)
{
	if (index>=0 && index<m_list.size())
		return &m_list[index];
	return NULL;
}