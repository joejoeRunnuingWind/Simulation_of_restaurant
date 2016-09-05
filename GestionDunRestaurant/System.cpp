#include "stdafx.h"
#include "System.h"

const char* CSystem::getSystemName()
{
	return m_stName.c_str();
}


//////////////////////////////////////////////////////////////////////////
CManagerSystem*	CManagerSystem::s_pMe = NULL;
CManagerSystem::CManagerSystem(void)
{
	s_pMe = this;
	m_stName = "Manager System";
}

CManagerSystem::~CManagerSystem(void)
{

}

void CManagerSystem::Initial()
{
	showMainMenu();
}

void CManagerSystem::showMainMenu()
{
	int command;

	while (true)
	{
		command = 0;
		system("cls");
		cout << " 1. Plats" << endl;
		cout << " 2. List de vip" << endl;
		cout << " 3. Employees" << endl;
		cout << " 4. Table" << endl;
		cout << " 9. Return to main menu" << endl;
		cout << "Vous avez de commander pour : ";

		cin >> command;

		if ( command == 9 )
			break;

		switch (command)
		{
		case 1:
			m_platsManager.showMuen();
			break;
		case 2:
			m_vipManager.showMuen();
			break;
		case 3:
			m_employeeManager.showMuen();
			break;
		case 4:
			m_tableManager.showMuen();
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

//////////////////////////////////////////////////////////////////////////

COrderSystem::COrderSystem(void)
{
	m_stName = "Ordering";
	m_pOrder = NULL;
}

COrderSystem::~COrderSystem(void)
{

}

void COrderSystem::Initial()
{
	showMainMenu();
}

void COrderSystem::showMainMenu()
{
	int command;

	while (true)
	{
		command = 0;
		system("cls");
		cout << " 1. order" << endl;
		cout << " 2. check" << endl;
		cout << " 9. Return to main menu" << endl;
		cout << "Vous avez de commander pour : ";

		cin >> command;

		if ( command == 9 )
			break;

		switch (command)
		{
		case 1:
			Ordering();
			break;
		case 2:
			CheckOrder();
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

void COrderSystem::Ordering()
{
	
	if (m_pOrder)
		delete m_pOrder;
	m_pOrder = new COrder();

	SelectTable();
	do{
		SelectPlats();
	} while(ConfirmOrder());
	ConfirmVIP();
	m_list.push_back(*m_pOrder);
	cout << "finish， ";
	system("pause");
}

void COrderSystem::SelectTable()
{
	int table_id;
	int command;
	int i;
	cout << "1. eat in" << endl << "2. take out" << endl;
	cout << "choose（1 or 2）： ";

	bool	b1 = true;
	bool	b2 = true;


	while (b1)
	{
		cin >> command;			
		if (command == 1)
		{
			i = 0;
			while (true)
			{
				CTable* pTable = CManagerSystem::GetMe()->getTableManager()->getTableInfo(i);
				if (pTable == NULL)
					break;
				pTable->showInfo();
				i++;
			}

			cout << "enter your number： ";

			while(b2)
			{
				i = 0;
				cin >> table_id;
				// check
				while (true)
				{
					CTable* pTable = CManagerSystem::GetMe()->getTableManager()->getTableInfo(i);
					if (pTable == NULL)
						break;
					if (table_id == pTable->getTableID())
					{
						m_pOrder->setTableID(table_id);
						pTable->checkIn();
						b2 = false;
						b1 = false;
						break;
					}
					i++;
				}

				if (b2)
				{
					cin.clear();
					std::string t;
					std::getline(cin,t);
					cout << "Error： ";
				}
			}
		}
		else if (command == 2)
		{
			m_pOrder->setTableID(0);
			break;
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

void COrderSystem::SelectPlats()
{
	int i;

	// 选择菜品
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << m_pOrder->getTableID() << "table to order pls..." << endl;
	i = 0;
	while(true)
	{
		CPlats* pPlats = CManagerSystem::GetMe()->getPlatsManager()->getPlatsInfo(i);
		if (pPlats==NULL)
			break;
		printf("%d. %s 价格:%.2f\n", i+1, pPlats->getObjectName(), pPlats->getPlatsPrixP());
		i++;
	}

	cout << "enter the number ，0 to return： ";
	int plats_idx, plats_num;
	while(true)
	{
		cin >> plats_idx;

		if (plats_idx == 0)
			break;

		plats_idx -= 1;

		CPlats* pPlats = CManagerSystem::GetMe()->getPlatsManager()->getPlatsInfo(plats_idx);
		// 
		if (pPlats)
		{
			cout << "enter<" << pPlats->getObjectName() << "> number： ";
			cin >> plats_num;

			m_pOrder->addOrder(*pPlats, plats_num);

			cout << "enter the number ，0 to return：";
		}
		else
		{
			cin.clear();
			std::string t;
			std::getline(cin,t);
			cout << "Error： ";
		}
	}
}

bool COrderSystem::ConfirmOrder()
{
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "confirm..." << endl;
	int i;

	while (true)
	{
		i = 0;
		ORDER_PLATS* p = NULL;
		while (true)
		{
			p = m_pOrder->getOrderInfo(i);
			if (p==NULL)
				break;
			printf("%d. %s x %d\n", i+1, p->plats.getObjectName(), p->num);
			i++;
		}

		int cmd;

		cout << "enter the number ，0 to return： ";
		cin >> cmd;
		if (cmd == 0)
			break;
		cmd -= 1;
		p = m_pOrder->getOrderInfo(cmd);
		if (p==NULL)
		{
			cin.clear();
			std::string t;
			std::getline(cin,t);
			cout << "输入错误，请重新输入！" << endl;
		}
		else
		{
			m_pOrder->deleteOrder(cmd);
		}
	}

	cout << "continue（y/n）： ";

	char command;
	while (true)
	{
		cin >> command;
		if (command == 'y')
		{
			return true;
		}
		else if (command == 'n')
		{
			return false;
		}
		else
		{
			cin.clear();
			std::string t;
			std::getline(cin,t);
			cout << "Error： ";
		}
	}
}

void COrderSystem::ConfirmVIP()
{
	char command;
	int i = 0;
	cout << "become VIP?（y/n）： ";

	cin >> command;
	if (command == 'y')
	{
		for (;i<3;i++)
		{
			string	strName, strBirthday;
			char	buffer[30];

			
			cout << "your name, pls: ";
			memset(buffer, 0, sizeof(buffer));
			while ( strlen(buffer) == 0 )					
			{
				cin >> buffer;
			}
			strName = buffer;

			
			cout << "your birthday, pls（19XX-XX-XX）: ";
			memset(buffer, 0, sizeof(buffer));
			while ( strlen(buffer) == 0 )					
			{
				cin >> buffer;
			}
			strBirthday = buffer;

			if (CManagerSystem::GetMe()->getVipManager()->VerifyVIP(strName, strBirthday))
			{
				cout << "done, enjoy yourself" << endl;
				m_pOrder->setVIPName((char*)strName.c_str());
				break;
			}
			else
			{
				cout << "Error！" << endl;
			}
		}
	}
	else if (command == 'n')
	{
	}
	else
	{
		cin.clear();
		std::string t;
		std::getline(cin,t);
		cout << "Error： ";
	}
	
	if (m_pOrder->getVIPName()==NULL)
	{
		cout << "become VIP?： ";
		cin >> command;
		if (command == 'y')
		{
			CVip	vip;
			char	buffer[30];

			
			cout << "your name, pls: ";
			memset(buffer, 0, sizeof(buffer));
			while ( strlen(buffer) == 0 )					
			{
				cin >> buffer;
			}
			vip.setObjectName(buffer);

			cout << "your birthday, pls（19XX-XX-XX）: ";
			memset(buffer, 0, sizeof(buffer));
			while ( strlen(buffer) == 0 )					
			{
				cin >> buffer;
			}
			vip.setVipBirthday(buffer);

			cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
			vip.showInfo();
			cout << "||||||||||||||||||||||||||||||||||||||||" << endl;
			cout << "confirm, save?（y/n）： ";
			char command;
			while (true)
			{
				cin >> command;
				if (command == 'y')
				{
					CManagerSystem::GetMe()->getVipManager()->addVip(vip);
					vip.setVipBirthday((char*)vip.getObjectName());
					break;
				}
				else if (command == 'n')
				{
					break;
				}
			}
		}
		else if(command == 'n')
		{
		}
		else
		{
			cin.clear();
			std::string t;
			std::getline(cin,t);
			cout << "Error： ";
		}
	}
}

void COrderSystem::CheckOrder()
{
	int i = 0;
	CTable* pTable = NULL;
	while (true)
	{
		pTable = CManagerSystem::GetMe()->getTableManager()->getTableInfo(i);
		if (pTable == NULL)
			break;
		pTable->showInfo();
		i++;
	}

	int id;
	cout << "enter your number： ";
	cin >> id;

	for (i=0; i<m_list.size();i++)
	{
		if (!m_list[i].getCheck())
		{
			if (m_list[i].getTableID()==id)
			{
				cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
				printf("table【%d】order < %d > info\n", id, i);
				int n = 0;
				float count = 0, last = 0;
				while (true)
				{
					ORDER_PLATS* p = m_pOrder->getOrderInfo(n);
					if (p==NULL)
						break;
					count += p->plats.getPlatsPrixP() * p->num;
					printf("%s x %d\t\t%.2f\n", p->plats.getObjectName(), p->num, p->plats.getPlatsPrixP() * p->num);
					n++;
				}
				if (m_list[i].getVIPName()!=NULL)
					last = count * 0.8;
				else
					last = count;

				printf("Sum： %.2f  to pay： %.2f\n", count, last);

				cout << "check?（y/n）: ";
				char command;
				while (true)
				{
					cin >> command;
					if (command == 'y')
					{
						m_list[i].setCheck(false);
						CManagerSystem::GetMe()->getTableManager()->checkOut(id);
						cout << "check succesfully！";
						system("pause");
						break;
					}
					else if (command == 'n')
					{
						break;
					}
				}
				break;
			}
		}
	}
}