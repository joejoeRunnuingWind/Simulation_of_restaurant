#include "stdafx.h"
#include "Order.h"


COrder::COrder(void)
{
	m_nTableID = 0;
	m_nCustomerNumber = 0;
	m_nState = OS_NONE;
	m_strVipName = "";
	m_bCheck = false;
}

COrder::~COrder(void)
{
}

void COrder::addOrder(CPlats& plats, int num)
{
	ORDER_PLATS	order;

	order.plats = plats;
	order.num = num;
	m_item.push_back(order);
}

void COrder::deleteOrder(int index)
{
	vector< ORDER_PLATS >::iterator it = m_item.begin();

	int i = 0;
	while(it != m_item.end())
	{
		if (i==index)
		{
			m_item.erase(it);
			break;
		}
		i++;
		it++;
	}
}

int	COrder::getTableID()
{
	return m_nTableID;
}

void COrder::setTableID(int id)
{
	m_nTableID = id;
}

int COrder::getCustomerNumber()
{
	return m_nCustomerNumber;
}

void COrder::setCustomerNumber(int num)
{
	m_nCustomerNumber = num;
}

ORDER_STATE COrder::getOrderState()
{
	return m_nState;
}

void COrder::setOrderState(ORDER_STATE state)
{
	m_nState = state;
}

const char* COrder::getVIPName()
{
	if (m_strVipName != "")
		return m_strVipName.c_str();
	return NULL;
}

void COrder::setVIPName(char* name)
{
	if (name)
		m_strVipName = name;
}

ORDER_PLATS* COrder::getOrderInfo(int i)
{
	if (i > -1 && i < m_item.size())
		return &m_item[i];
	return NULL;
}
