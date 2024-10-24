#pragma once
#include <string>
#include <vector>
#include <algorithm>

class DBConnection;
class Player 
{
public:
    int id;
    std::wstring playerId;
    std::wstring playerPassword;
    std::wstring playerNickname;

    Player() = default;

    Player(
        int id, 
        std::wstring playerId, 
        std::wstring playerPassword, 
        std::wstring playerNickname
    ) :
        id(id), 
        playerId(playerId), 
        playerPassword(playerPassword), 
        playerNickname(playerNickname)
    { }
};

class PlayerManager
{
public:
    void add_record(const Player& record) 
    {
        data.push_back(record);
    }

    std::vector<Player> find_by_id(const int& value) 
    {
        std::vector<Player> results;
        for (const auto& record : data) 
        {
            if (record.id == value) 
            {
                results.push_back(record);
            }
        }
        return results;
    }

    void update_by_id(const int& key, const Player& new_record) 
    {
        for (auto& record : data) 
        {
            if (record.id == key) 
            {
                record = new_record;
                return;
            }
        }
    }

    void delete_by_id(const int& key) 
    {
        auto it = std::remove_if(data.begin(), data.end(),
            [&key](const Player& record) 
            {
                return record.id == key;
            });
        data.erase(it, data.end());
    }

    void Initialize(DBConnection* conn);

    std::vector<Player>& get_all() 
    {
        return data;
    }

private:
    std::vector<Player> data;
};
class Friends 
{
public:
    std::wstring UserId;
    std::wstring FriendId;

    Friends() = default;

    Friends(
        std::wstring UserId, 
        std::wstring FriendId
    ) :
        UserId(UserId), 
        FriendId(FriendId)
    { }
};

class FriendsManager
{
public:
    void add_record(const Friends& record) 
    {
        data.push_back(record);
    }

    std::vector<Friends> find_by_UserId(const std::wstring& value) 
    {
        std::vector<Friends> results;
        for (const auto& record : data) 
        {
            if (record.UserId == value) 
            {
                results.push_back(record);
            }
        }
        return results;
    }

    void update_by_UserId(const std::wstring& key, const Friends& new_record) 
    {
        for (auto& record : data) 
        {
            if (record.UserId == key) 
            {
                record = new_record;
                return;
            }
        }
    }

    void delete_by_UserId(const std::wstring& key) 
    {
        auto it = std::remove_if(data.begin(), data.end(),
            [&key](const Friends& record) 
            {
                return record.UserId == key;
            });
        data.erase(it, data.end());
    }

    void Initialize(DBConnection* conn);

    std::vector<Friends>& get_all() 
    {
        return data;
    }

private:
    std::vector<Friends> data;
};
class Requests 
{
public:
    std::wstring UserId;
    std::wstring RequestId;

    Requests() = default;

    Requests(
        std::wstring UserId, 
        std::wstring RequestId
    ) :
        UserId(UserId), 
        RequestId(RequestId)
    { }
};

class RequestsManager
{
public:
    void add_record(const Requests& record) 
    {
        data.push_back(record);
    }

    std::vector<Requests> find_by_UserId(const std::wstring& value) 
    {
        std::vector<Requests> results;
        for (const auto& record : data) 
        {
            if (record.UserId == value) 
            {
                results.push_back(record);
            }
        }
        return results;
    }

    void update_by_UserId(const std::wstring& key, const Requests& new_record) 
    {
        for (auto& record : data) 
        {
            if (record.UserId == key) 
            {
                record = new_record;
                return;
            }
        }
    }

    void delete_by_UserId(const std::wstring& key) 
    {
        auto it = std::remove_if(data.begin(), data.end(),
            [&key](const Requests& record) 
            {
                return record.UserId == key;
            });
        data.erase(it, data.end());
    }

    void Initialize(DBConnection* conn);

    std::vector<Requests>& get_all() 
    {
        return data;
    }

private:
    std::vector<Requests> data;
};

class DBManager 
{
public:
    PlayerManager& GetPlayerManager() 
    {
        return player;
    }
    FriendsManager& GetFriendsManager() 
    {
        return friends;
    }
    RequestsManager& GetRequestsManager() 
    {
        return requests;
    }

    void Initialize();
    DBConnection* GetDBConn() { return m_DbConn; }

    std::string ConvertWstringToString(wstring wStr) { return std::string(wStr.begin(), wStr.end()); }
    std::wstring ConvertStringToWstring(string str) { return std::wstring(str.begin(), str.end()); }

private:
    PlayerManager player;
    FriendsManager friends;
    RequestsManager requests;

    DBConnection* m_DbConn = nullptr;
};

extern DBManagerRef GDBManager;