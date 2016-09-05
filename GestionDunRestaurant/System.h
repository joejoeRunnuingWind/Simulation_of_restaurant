#pragma once
#include "employee.h"
#include "Vip.h"
#include "Plats.h"
#include "Table.h"
#include "Order.h"


class CSystem
{
public:

	virtual void	Initial() {};

	virtual void	showMainMenu() {};

	
	virtual const char*	getSystemName();

protected:
	string	m_stName;
};

//////////////////////////////////////////////////////////////////////////

class CManagerSystem : public CSystem
{
public:

	virtual void	Initial();

	virtual void	showMainMenu();

	void			showPlatsMenu();
	void			showVipMenu();
	void			showEmployees();

	CTableManager*	getTableManager() { return &m_tableManager; }
	CCPlatsManager*	getPlatsManager() { return &m_platsManager; }
	CVipManager*	getVipManager() { return &m_vipManager; }

	static CManagerSystem*	GetMe() { return s_pMe; }

protected:

	CEmployeeManager	m_employeeManager;
	CVipManager			m_vipManager;
	CCPlatsManager		m_platsManager;
	CTableManager		m_tableManager;

public:

	static	CManagerSystem*		s_pMe;

public:
	CManagerSystem(void);
	~CManagerSystem(void);
};

//////////////////////////////////////////////////////////////////////////

class COrderSystem : public CSystem
{
public:
	virtual void	Initial();

	virtual void	showMainMenu();

	void			Ordering();			
	void			CheckOrder();		

	void			SelectTable();	
	void			SelectPlats();	
	bool			ConfirmOrder();	
	void			ConfirmVIP();

protected:
	COrder*			m_pOrder;

	vector< COrder >	m_list;

public:
	COrderSystem(void);
	~COrderSystem(void);
};
