#pragma once
#include "Plats.h"

#ifndef DB_LENGTH_MAX
#define DB_LENGTH_MAX 30
#endif

enum ORDER_STATE
{
	OS_NONE = -1,
	OS_DINING,
	OS_CHECKOUT
};

struct ORDER_PLATS
{
	CPlats	plats;
	int		num;
};

// ∂©µ•¿‡
class COrder
{
public:

	void	addOrder(CPlats& plats, int num);		
	void	deleteOrder(int index);			

	int		getTableID();					
	void	setTableID(int id);
	
	int		getCustomerNumber();			
	void	setCustomerNumber(int num);

	ORDER_STATE		getOrderState();
	void			setOrderState(ORDER_STATE state);

	const char*		getVIPName();
	void			setVIPName(char* name);

	ORDER_PLATS*	getOrderInfo(int i);

	bool			getCheck() { return m_bCheck; };
	void			setCheck(bool chk) { m_bCheck = chk; }


protected:
	int						m_nTableID;
	int						m_nCustomerNumber;
	ORDER_STATE				m_nState;
	string					m_strVipName;
	bool					m_bCheck;

	vector< ORDER_PLATS >	m_item;	
public:
	COrder(void);
	~COrder(void);
};