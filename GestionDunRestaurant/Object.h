#pragma once

class CObject
{
public:

	enum OBJECT_TYPE
	{
		OT_NONE = -1,
		OT_EMPLOYEE,		
		OT_CUSTOMER,		
		OT_DISHES			
	};

public:
	virtual const char*		getObjectCode() { return m_strCode.c_str(); }
	virtual void			setObjectCode(char* code) { m_strCode = code; }

	virtual const char*		getObjectName() { return m_strName.c_str(); }
	virtual bool			setObjectName(char* name) 
	{ 
		if (name == NULL) return false;
		m_strName = name;
		return true;
	}

	virtual OBJECT_TYPE		getObjectType() { return OT_NONE; }

	virtual void			showInfo()
	{
		printf("ID: %s\nName: %s\n", m_strCode.c_str(), m_strName.c_str());
	}


protected:
	string			m_strCode;
	string			m_strName;

public:
	CObject() 
	{ 
		m_strCode = "";
		m_strName = "";
	}

	~CObject() {}
};