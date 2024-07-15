#pragma once
#include "Types.h"
#include <windows.h>
#include "DBBind.h"

namespace SP
{
	
    class InsertPlayer : public DBBind<3,0>
    {
    public:
    	InsertPlayer(DBConnection& conn) : DBBind(conn, L"{CALL dbo.spInsertPlayer(?,?,?)}") { }
    	template<int32 N> void In_PlayerId(WCHAR(&v)[N]) { BindParam(0, v); };
    	template<int32 N> void In_PlayerId(const WCHAR(&v)[N]) { BindParam(0, v); };
    	void In_PlayerId(WCHAR* v, int32 count) { BindParam(0, v, count); };
    	void In_PlayerId(const WCHAR* v, int32 count) { BindParam(0, v, count); };
    	template<int32 N> void In_PlayerPassword(WCHAR(&v)[N]) { BindParam(1, v); };
    	template<int32 N> void In_PlayerPassword(const WCHAR(&v)[N]) { BindParam(1, v); };
    	void In_PlayerPassword(WCHAR* v, int32 count) { BindParam(1, v, count); };
    	void In_PlayerPassword(const WCHAR* v, int32 count) { BindParam(1, v, count); };
    	template<int32 N> void In_PlayerNickname(WCHAR(&v)[N]) { BindParam(2, v); };
    	template<int32 N> void In_PlayerNickname(const WCHAR(&v)[N]) { BindParam(2, v); };
    	void In_PlayerNickname(WCHAR* v, int32 count) { BindParam(2, v, count); };
    	void In_PlayerNickname(const WCHAR* v, int32 count) { BindParam(2, v, count); };

    private:
    };

    class GetPlayer : public DBBind<0,2>
    {
    public:
    	GetPlayer(DBConnection& conn) : DBBind(conn, L"{CALL dbo.spGetPlayer}") { }
    	template<int32 N> void Out_PlayerId(OUT WCHAR(&v)[N]) { BindCol(0, v); };
    	template<int32 N> void Out_PlayerPassword(OUT WCHAR(&v)[N]) { BindCol(1, v); };

    private:
    };

    class CheckPlayerIdExists : public DBBind<1,0>
    {
    public:
    	CheckPlayerIdExists(DBConnection& conn) : DBBind(conn, L"{CALL dbo.spCheckPlayerIdExists(?)}") { }
    	template<int32 N> void In_PlayerId(WCHAR(&v)[N]) { BindParam(0, v); };
    	template<int32 N> void In_PlayerId(const WCHAR(&v)[N]) { BindParam(0, v); };
    	void In_PlayerId(WCHAR* v, int32 count) { BindParam(0, v, count); };
    	void In_PlayerId(const WCHAR* v, int32 count) { BindParam(0, v, count); };

    private:
    };

    class LoginPlayer : public DBBind<2,0>
    {
    public:
    	LoginPlayer(DBConnection& conn) : DBBind(conn, L"{CALL dbo.spLoginPlayer(?,?)}") { }
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

    class DeleteAllGold : public DBBind<0,0>
    {
    public:
    	DeleteAllGold(DBConnection& conn) : DBBind(conn, L"{CALL dbo.spDeleteAllGold}") { }

    private:
    };


     
};