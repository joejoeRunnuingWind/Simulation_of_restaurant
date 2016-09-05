#pragma once
#include "object.h"

#ifndef DB_LENGTH_MAX
#define DB_LENGTH_MAX 30
#endif

struct DB_VIP_INFO
{
	char	szName[DB_LENGTH_MAX];
	char	szBirthday[DB_LENGTH_MAX];

	DB_VIP_INFO()
	{
		memset(szName, 0, DB_LENGTH_MAX);
		memset(szBirthday, 0, DB_LENGTH_MAX);
	}
};

class CVip : public CObject
{
public:

	virtual void		showInfo();

	virtual OBJECT_TYPE		getObjectType() { return OT_CUSTOMER; }

	const char*			getVipBirthday();
	void				setVipBirthday(char* day);
	
	void				getDataBaseInfo(DB_VIP_INFO& info);		

protected:
	string		m_strBirthday;

public:
	CVip(void);
	CVip(DB_VIP_INFO info);
	~CVip(void);
};

class CVipManager
{
public:
	void		showMuen();

	void		listVip();
	void		addVip();
	void		addVip(CVip& vip);
	void		delVip();

	void		readFile();				
	void		writeFile();			

	bool		VerifyVIP(string& name, string& pass);

protected:
	vector< CVip >		m_list;

public:
	CVipManager();
	~CVipManager();
};

