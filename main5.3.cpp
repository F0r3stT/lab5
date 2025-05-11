#include <iostream>
#include <sstream>
#include "lab5.3.2.h"


using namespace std;

int main()
{
    string asd;
    cout << "Введите доступные команды: CREATE_PLANE PLANES_FOR_TOWN TOWNS_FOR_PLANE PLANES INFO\n";
    while(getline(cin, asd)){
        istringstream in(asd); //поток ввода
        // инициализируется содержимым строки asd
        string cmd, name;
        in >> cmd; //считываем строку и сохраняем в cmd

        ComType type = getCom(cmd);//возвращает тип команды в виде перечисления enum

        if(type == CREATE_PLANE){
            in >> name;
            vector<string> towns;
            string town;
            while(in >> town){ //цикл подсчёта последующих слов (города)
                towns.push_back(town);
            }
            CreatePlane(name, towns);
            cout << "Самолёт с заданным маршрутом создан\n";
        }
        else if(type == PLANES_FOR_TOWN){
            in >> name; 
            PlanesTown(name); //читаем в функцию, выводяющую все самолёты по условию
        }
        else if(type == TOWNS_FOR_PLANE){
            in >> name;
            TownPlanes(name);
        }
        else if (type == PLANES){
            AllPlan();
        }
        else if(type == INFO){
            cout << "Команда СREATE_PLANE: <название самолёта>, <город 1>, <город 2>" << endl;
            cout << "Команда PLANES_FOR_TOWN: <город>" << endl;
            cout << "Команда TOWNS_FOR_PLANE: <название самолёта>" << endl;
            cout << "Команда PLANES: " << endl;
        }
        else {
            cout <<"Неизвестная команда" << endl;
        }
    }




    return 0;
}