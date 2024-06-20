#pragma once
#include "Types.h"
#include <windows.h>
#include "DBBind.h"

namespace SP
{
	
    class InsertGold : public DBBind<2,0>
    {
    public:
    	InsertGold(DBConnection& conn) : DBBind(conn, L"{CALL dbo.spInsertGold(?,?)}") { }
    	template<int32 N> void In_PlayerId(WCHAR(&v)[N]) { BindParam(0, v); };
    	template<int32 N> void In_PlayerId(const WCHAR(&v)[N]) { BindParam(0, v); };
    	void In_PlayerId(WCHAR* v, int32 count) { BindParam(0, v, count); };
    	void In_PlayerId(const WCHAR* v, int32 count) { BindParam(0, v, count); };
    	template<int32 N> void In_PlayerPassword(WCHAR(&v)[N]) { BindParam(1, v); };
    	template<int32 N> void In_PlayerPassword(const WCHAR(&v)[N]) { BindParam(1, v); };
    	void In_PlayerPassword(WCHAR* v, int32 count) { BindParam(1, v, count); };
    	void In_PlayerPassword(const WCHAR* v, int32 count) { BindParam(1, v, count); };

    private:
    };


     
};