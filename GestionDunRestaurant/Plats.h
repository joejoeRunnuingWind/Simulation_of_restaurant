#pragma once
#include "object.h"

#ifndef DB_LENGTH_MAX
#define DB_LENGTH_MAX 30
#endif

struct DB_PLATS_INFO
{
	char	szName[DB_LENGTH_MAX];
	int		nTyep;
	float	fPrixP;
	float	fPrixS;

	DB_PLATS_INFO()
	{
		memset(szName, 0, DB_LENGTH_MAX);
		nTyep = -1;
		fPrixP = 0;
		fPrixP = 0;
	}
};

enum PLATS_OBJECT_TYPE
{
	POT_NONE = -1,
	POT_ENTREE,
	POT_PLAT,
	POT_DESSERT,
	POT_BOISSON,
	POT_MAX
};

class CPlats : public CObject
{
public:
	virtual void			showInfo();

	virtual OBJECT_TYPE		getObjectType() { return OT_DISHES; }

	PLATS_OBJECT_TYPE		getPlatsType();
	void					setPlatsTyep(PLATS_OBJECT_TYPE type);

	float					getPlatsPrixP();			
	void					setPlatsPrixP(float val);

	float					getPlatsPrixS();			
	void					setPlatsPrixS(float val);

	void					getDataBaseInfo(DB_PLATS_INFO& info);

protected:
	PLATS_OBJECT_TYPE	m_nTyep;
	float				m_fPrixP;
	float				m_fPrixS;
	
public:
	CPlats(void);
	CPlats(DB_PLATS_INFO);
	~CPlats(void);
};

class CCPlatsManager
{
public:
	void		showMuen();

	void		listPlats();
	void		addPlats();
	void		delPlats();

	void		readFile();				
	void		writeFile();			

	CPlats*		getPlatsInfo(int index);

protected:
	vector< CPlats >		m_list;

public:
	CCPlatsManager();
	virtual ~CCPlatsManager();
};