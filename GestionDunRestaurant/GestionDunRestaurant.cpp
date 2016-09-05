// GestionDunRestaurant.cpp 
//

#include "stdafx.h"
#include "System.h"

#define	OPTIONS_COUNT	2			

CManagerSystem	g_manager;
COrderSystem	g_order;

int _tmain(int argc, _TCHAR* argv[])
{
	int i, opt = 0;										
	CSystem*	pSystem[OPTIONS_COUNT] = { &g_order, &g_manager };	
			
	while (true)
	{
		system("cls");

		for (i = 0; i < OPTIONS_COUNT; i++)
		{
			cout << " " << i+1 << "." << pSystem[i]->getSystemName() << endl;	
		}
		cout << " 9.Exit" << endl;

		while (true)
		{
			cout << "vous etes client ou serveur (0-" << OPTIONS_COUNT << " or 9) : ";			
			cin >> opt;

			if ( opt > 0 && opt <= OPTIONS_COUNT ) 
			{
				pSystem[opt-1]->Initial();
				break;
			}
			else if ( opt == 9 )
			{
				return 0;
			}
			else
			{
				cin.clear();
				std::string t;
				std::getline(cin,t);
				cout << "erreur de saisir, le redonnez svp !" << endl;
				cout << endl;
			}
		}

	}

	return 0;
}

