#pragma once
#include <string>
#include <vector>
#include <algorithm>

class DBConnection;

{%- for table in tables %}
class {{ table.name }} 
{
public:
    {%- for column in table.columns %}
    {{ column.type }} {{ column.name }};
    {%- endfor %}

    {{ table.name }}() = default;

    {{ table.name }}(
        {%- for column in table.columns %}
        {{ column.type }} {{ column.name }}{%- if not loop.last %}, {% endif %}
        {%- endfor %}
    ) :
        {%- for column in table.columns %}
        {{ column.name }}({{ column.name }}){%- if not loop.last %}, {% endif %}
        {%- endfor %}
    { }
};

class {{ table.name }}Manager
{
public:
    void add_record(const {{ table.name }}& record) 
    {
        data.push_back(record);
    }

    std::vector<{{ table.name }}> find_by_{{ table.columns[0].name }}(const {{ table.columns[0].type }}& value) 
    {
        std::vector<{{ table.name }}> results;
        for (const auto& record : data) 
        {
            if (record.{{ table.columns[0].name }} == value) 
            {
                results.push_back(record);
            }
        }
        return results;
    }

    void update_by_{{ table.columns[0].name }}(const {{ table.columns[0].type }}& key, const {{ table.name }}& new_record) 
    {
        for (auto& record : data) 
        {
            if (record.{{ table.columns[0].name }} == key) 
            {
                record = new_record;
                return;
            }
        }
    }

    void delete_by_{{ table.columns[0].name }}(const {{ table.columns[0].type }}& key) 
    {
        auto it = std::remove_if(data.begin(), data.end(),
            [&key](const {{ table.name }}& record) 
            {
                return record.{{ table.columns[0].name }} == key;
            });
        data.erase(it, data.end());
    }

    void Initialize(DBConnection* conn);

    std::vector<{{ table.name }}>& get_all() 
    {
        return data;
    }

private:
    std::vector<{{ table.name }}> data;
};

{%- endfor %}

class DBManager 
{
public:
    {%- for table in tables %}
    {{ table.name }}Manager& Get{{ table.name }}Manager() 
    {
        return {{ table.name.lower() }};
    }
    {%- endfor %}

    void Initialize();
    DBConnection* GetDBConn() { return m_DbConn; }

    std::string ConvertWstringToString(wstring wStr) { return std::string(wStr.begin(), wStr.end()); }
    std::wstring ConvertStringToWstring(string str) { return std::wstring(str.begin(), str.end()); }

private:
    {%- for table in tables %}
    {{ table.name }}Manager {{ table.name.lower() }};
    {%- endfor %}

    DBConnection* m_DbConn = nullptr;
};

extern DBManagerRef GDBManager;