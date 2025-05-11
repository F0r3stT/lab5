#include "lab5.3.2.h"
#include <iostream>
using namespace std;

map<string, vector<string>> planeTowns;
map<string, set<string>> townPlane;

ComType getCom(const string& cmd)
{
    if(cmd =="CREATE_PLANE")
        return CREATE_PLANE;
    if(cmd =="PLANES_FOR_TOWN")
        return PLANES_FOR_TOWN;
    if(cmd == "TOWNS_FOR_PLANE")
        return TOWNS_FOR_PLANE;
    if(cmd == "PLANES")
        return PLANES;
    if(cmd == "INFO")
        return INFO;
    return UNKNOWN;
}

void CreatePlane(string &plane, const vector<string>& towns){
    planeTowns[plane] = towns; //сохраняем маршрут ["A350"] = {"Mocsow",Kazan..}
    for(auto& town: towns){ //проходим по каждому городу
        townPlane[town].insert(plane); //добавляем самолёт, в список самолётов пролетающих через город
        //["Moscow"] = {"A241", "SU-29"};
    }
}

void PlanesTown(string& town){
    if(!townPlane.count(town)){ //есть ли в городе хоть один самолёт который через него летит
        cout << "Города нету\n"; 
        return;
    }

    int i=1;
    for(auto& plane: townPlane[town]){ //выводим название рейса и самолёта, перебирает значения по ключу(городу)
        cout << i++ << ". " << plane << endl;
    }
}

void TownPlanes(string& plane){
    if(!planeTowns.count(plane)){ //проверка на существование самолёта
        cout << "Нету самолета\n";
        return;
    }

    for(auto& town: planeTowns[plane])//перебор всех городов через которые летает самолёт
    {
        cout << town << ": "; 
    // plane - имя самолёта
        vector<string> others; //список других самолётов, которые делают остановку в этом городе
        for(auto& p: townPlane[town]){
            if (p != plane){ //если p(самолёт из списка) не совпадает с самолётом для которого выполняем запрос
                others.push_back(p); //то добавляем в вектор других самолётов
            }
        }

        if(others.empty()){ //если others пуст
            cout << "нету других самолётов\n"; 
        }
        else
        {
            int i=1;//если есть другие, то выводим с нумерацией
            for(auto &other : others){
                cout << i++ << ". " << other << " ";
            }
        cout << endl;
        }
    }
}


void AllPlan()
{
    if(planeTowns.empty()){
        cout << "Самолёты отсутствуют\n"; //если самолёты не добавлены
        return;
    }
        //перебираем самолёты, по ключу имени самолёта и списка городов
    for(auto& [plane, towns]: planeTowns){
        cout << plane << ": "; // имя самолёта
        int i=1;
        for(auto& town : towns){ //перебор и печать списка городов
            cout << i++ << ". " << town << " ";
        }
    cout << endl;
    }
}