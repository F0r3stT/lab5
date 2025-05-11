#pragma once //проверка на уникальность включения заголовочного файла
#include <string>
#include <vector>
#include <set>
#include <map>


extern std::map<std::string, std::vector<std::string>> planeTowns;
extern std::map<std::string, std::set<std::string>> townPlane; //все самолёты делающие остановку в городе
enum ComType{
    CREATE_PLANE,
    PLANES_FOR_TOWN,
    TOWNS_FOR_PLANE,
    PLANES,
    INFO,
    UNKNOWN
};
ComType getCom(const std::string& cmd);
void CreatePlane(std::string &plane, const std::vector<std::string>& towns);
void PlanesTown(std::string& town);
void TownPlanes(std::string& plane);
void AllPlan();

