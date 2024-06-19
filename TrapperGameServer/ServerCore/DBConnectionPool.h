#pragma once
#include "DBConnection.h"

class DBConnectionPool
{
public:
	DBConnectionPool();
	~DBConnectionPool();

	// Ŀ�ؼ� Ǯ�� ������ִ� �Լ�
	bool					Connect(int32 connectionCount, const WCHAR* connectionString);
	void					Clear();

	DBConnection*			Pop();
	void					Push(DBConnection* connection);

private:
	USE_LOCK;
	// ȯ���� ����ϴ� �ڵ�
	SQLHENV					_environment = SQL_NULL_HANDLE;
	// ������ �������� ����� �����ϱ� ���ؼ� vector�� ��� �ִ´�.
	Vector<DBConnection*>	_connections;
};

