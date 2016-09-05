#pragma once
#include "Object.h"

#ifndef DB_LENGTH_MAX
#define DB_LENGTH_MAX 30
#endif

struct DB_EMPLOYEE_INFO
{
	char	szCode[DB_LENGTH_MAX];
	char	szName[DB_LENGTH_MAX];
	int		nSex;
	int		nTravail;

	DB_EMPLOYEE_INFO()
	{
		memset(szCode, 0, DB_LENGTH_MAX);
		memset(szName, 0, DB_LENGTH_MAX);
		nSex = -1;
		nTravail = -1;
	}
};

enum EMPLOYEE_OBJECT_TYPE
{
	EOT_NONE = -1,
	EOT_MANAGER,	// manager
	EOT_WAITER,		// waiter
	EOT_CHEF,		// Chef
	EOT_MAX
};

enum EMPLOYEE_OBJECT_SEX
{
	EOS_NONE = -1,
	EOS_MALE,
	EOS_FAMALE
};

class CEmployee : public CObject
{

public:

	virtual void			showInfo();

	virtual OBJECT_TYPE		getObjectType() { return OT_EMPLOYEE; }

	EMPLOYEE_OBJECT_SEX		getSex();
	void					setSex(EMPLOYEE_OBJECT_SEX sex);
	EMPLOYEE_OBJECT_TYPE	getTravail();							
	void					setTravail(EMPLOYEE_OBJECT_TYPE tyep);	

	void					getDataBaseInfo(DB_EMPLOYEE_INFO& info);	
protected:
	EMPLOYEE_OBJECT_SEX		m_nSex;
	EMPLOYEE_OBJECT_TYPE	m_nTravail;

public:
	CEmployee(void);
	CEmployee(DB_EMPLOYEE_INFO info);
	~CEmployee(void);
};

class CEmployeeManager
{
public:
	void		showMuen();

	void		listEmployee();
	void		addEmployee();
	void		delEmployee();

	void		readFile();				// 取得文件记录
	void		writeFile();			// 保存到文件记录

protected:
	vector< CEmployee >		m_list;

public:
	CEmployeeManager();
	virtual ~CEmployeeManager();
};