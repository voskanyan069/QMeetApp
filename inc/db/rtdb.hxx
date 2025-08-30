#ifndef __DB_RTDB_HXX__
#define __DB_RTDB_HXX__

#define RTDB_FILENAME       ".qmeetapp.rtdb"
#define RTDB_JSON_TEMPLATE  "{\"account\": {\"username\": \"\", \"password\": \"\"}, \"meetings\": []}"

#include <string>
#include <nlohmann/json.hpp>

namespace DB
{
    class RTDB;
}

class DB::RTDB
{
private:
    RTDB();

public:
    ~RTDB();
    RTDB(const RTDB&) = delete;
    RTDB& operator=(const RTDB&) = delete;

public:
    static RTDB* GetInstance();

public:
    void GetJson(nlohmann::json& jsonData);
    void DumpToFile(const nlohmann::json& jsonData);

private:
    static RTDB* m_instance;
    std::string m_rtdbFilePath;
};

#endif // __DB_RTDB_HXX__
