#pragma once

struct DB_TABLE_INFO
{
	int		nID;
	int		nSeatNum;
	bool	bState;

	DB_TABLE_INFO()
	{
		nID = 0;
		nSeatNum = 0;
		bState = 0;
	}
};


class CTable
{
public:
	virtual void	showInfo();

	int				getTableID();				
	void			setTableID(int id);

	int				getTableSeatNumber();			
	void			setTableSeatNumber(int num);

	bool			getTableState();				
	void			checkIn();						
	void			checkOut();						

	void			getDataBaseInfo(DB_TABLE_INFO& info);

protected:

	int		m_nID;							
	int		m_nSeatNum;						
	bool	m_nState;						

public:
	CTable();
	CTable(DB_TABLE_INFO info);
	~CTable();
};

class CTableManager
{
public:
	void		showMuen();

	void		listTable();
	void		addTable();
	void		delTable();

	void		readFile();				
	void		writeFile();			

	CTable*		getTableInfo(int idx);	

	void		checkIn(int id);				
	void		checkOut(int id);				

protected:
	vector< CTable >		m_list;

public:
	CTableManager();
	virtual ~CTableManager();
};