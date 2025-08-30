#include "db/rtdb.hxx"
#include "types/exception.hxx"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

DB::RTDB* DB::RTDB::m_instance = nullptr;

DB::RTDB::RTDB()
    : m_rtdbFilePath()
{
    std::string homePath = std::getenv("HOME");
    m_rtdbFilePath = homePath + "/" + RTDB_FILENAME;
    if ( !fs::exists(m_rtdbFilePath) || fs::is_empty(m_rtdbFilePath) )
    {
        std::ofstream rtdbFile(m_rtdbFilePath);
        if ( rtdbFile.is_open() )
        {
            rtdbFile << std::setw(4) << RTDB_JSON_TEMPLATE << std::endl;
            rtdbFile.close();
        }
    }
}

DB::RTDB::~RTDB()
{
}

DB::RTDB* DB::RTDB::GetInstance()
{
    if (nullptr == m_instance)
    {
        m_instance = new RTDB();
    }
    return m_instance;
}

void DB::RTDB::GetJson(nlohmann::json& jsonData)
{
    std::string rtdbContent;
    std::ifstream rtdbFile(m_rtdbFilePath);
    if ( rtdbFile.is_open() )
    {
        std::string line;
        while (std::getline(rtdbFile, line))
        {
            rtdbContent += line;
        }
        rtdbFile.close();
    }
    try
    {
        jsonData = nlohmann::json::parse(rtdbContent);
    }
    catch (const nlohmann::json::exception& e)
    {
        throw Exception(e.what());
    }
}

void DB::RTDB::DumpToFile(const nlohmann::json& jsonData)
{
    std::string rtdbContent;
    std::ofstream rtdbFile(m_rtdbFilePath);
    if ( rtdbFile.is_open() )
    {
        rtdbFile << std::setw(4) << jsonData << std::endl;
        rtdbFile.close();
    }
}
