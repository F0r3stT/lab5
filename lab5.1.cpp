#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

const vector<char> zones = {'A', 'B'};
const int n_shelves = 6;
const int n_sections = 4;
const int n_levels = 4;
const int m_capacity = 10;

map<string, map<string, int>> warehouse;

bool isValid(string& addr, int& shelv, int& sect, int& level)
{
    if(addr.size() < 4 || addr.size() > 5)
        return false;
    
    char zone = addr[0];
    if(zone != 'A' && zone != 'B')
        return false;
        
    //проверка что все символы после первого цифры
    for (size_t i = 1; i < addr.size(); i++) {
    if (addr[i] < '0' || addr[i] > '9') {
        return false;
    }
}
    //разбор строки с адресом и преобразует её числовые значения:
    if (addr.size() == 4) { // адрес может быть как 4х значеным значением
        shelv = addr[1] - '0'; //стеллаж
        sect = addr[2] - '0'; //секция
        level = addr[3] - '0'; //уровень

    } else { //так и 5
        shelv = (addr[1] - '0') * 10 + (addr[2] - '0'); //если стеллаж записан двузначным символом
        sect = addr[3] - '0';
        level = addr[4] - '0';
    }

    return shelv >= 1 && shelv <= n_shelves && sect >= 1 && sect <= n_sections && level >= 1 && level <= n_levels;
}

void addIt(const string& name, int qty, string addr) {
    int shelv, sect, level;
    if (!isValid(addr, shelv, sect, level)) {
        cout << "Неверный адрес\n";
        return;
    }

    int current = warehouse[addr][name];
    if (current + qty > m_capacity) {
        cout << "Превышение вместимости ячейки\n";
        return;
    }

    warehouse[addr][name] += qty;
    cout << "Товар добавлен\n";
}
void removeIt(string& name, int c, string& addr)
{
    //*
    int shelv, sect,level;
    if(!isValid(addr,shelv,sect,level))
    {
        cout << "Incorrect addres \n";
        return;
    }
    auto a = warehouse.find(addr);
    if(a == warehouse.end() || (*a).second.find(name) == (*a).second.end() || (*a).second[name] < c){
        cout << "Not enough items to remove\n";
        return;
    }


    warehouse[addr][name] -= c;
    if(warehouse[addr][name] == 0){ // если после удаления товара в ячейке addr стало 0
        warehouse[addr].erase(name); //то он удаляется из списка товаров этой ячейки
    }
    if(warehouse[addr].empty()){//если ячейка addr пустая
        warehouse.erase(addr); //то и сама ячейка удаляется 
    }
    cout << "Товар удалён\n";
}

void info()
{
    int cUsed = 0; //общее кол-во товара на складе
    int Cells = n_sections * n_levels * n_shelves * 2; //общее количество ячеек
    int Capac = Cells * m_capacity; // максимальная вместимость склада
    
    map<char, int> zoneUsed;

    // перебор ячейеек и подсчёт количества товара     
    for(auto& [addr,item]: warehouse){
        int cTotal =0;
        for(auto& [name, count] : item){
            cTotal += count;
        }
        cUsed += cTotal;
        zoneUsed[addr[0]] += cTotal;
    }

    cout << fixed << setprecision(2) << "Общая загруженность: " << (100.0* cUsed / Capac) << endl;

    for(char z: zones) 
    {//перебор всех символов
        int c = n_shelves * n_sections * n_levels * m_capacity; //макс вместимость зоны
    // стеллажи * секции * уровни * товары в одной ячейке
        int zoneF = zoneUsed[z]; //берём товары, которые реально хранятся в Z
        cout << "Зона " << z << ": " << (100.0 * zoneF / c) << endl; 
    }

    cout << "Содержимое ячеек \n";
    for(auto& [addr,item] : warehouse)
    {
        cout << addr << ": ";
        for(auto &[name,count] : item)
        {
            cout << name << " " << count << " ";
        }
        cout << endl;
    }

    cout << "Пустые ячейки \n";
    for (char z : zones) { //проход по зонам
        for (int x = 1; x <= n_shelves; x++){ //стеллажи от 1 до 6
            for (int c = 1; c <= n_sections; c++){ //секции от 1 до 4
                for(int y=1; y <= n_levels; y++){ //полки от 1 до 4
                ostringstream os; // поток для построения строки адреса ячейки
                os << z; //адрес зоны

                if( x < 10) // если номер стеллажа однозначный
                    os << x;
                else
                    os << x / 10 << x % 10; // если двузначный

                os << c << y; //добавляем номер секции и уровень
                string addr = os.str(); //преобразование в строку
                if(!warehouse.count(addr)){ //проверка, есть ли такой адрес уже
                    cout << addr << " ";
                }
            }
        }
    }
}
    cout << endl;
}


int main()
{
    setlocale(LC_ALL,"RU");
    string strok;
    cout << "Введите команду (ADD, REMOVE, INFO) или EXIT для выхода:\n";
    while (getline(cin, strok)) { // через getline считываем всю строку включая пробелы и тд
        istringstream ss(strok); // строковый поток, чтобы считывать команды
        string cmd, name, addr;
        int qty;
        ss >> cmd; 

        if (cmd == "ADD") {
            ss >> name >> qty >> addr; //считывает все данные название количество и адрес ячейки
            addIt(name, qty, addr);
        } else if (cmd == "REMOVE") { 
            ss >> name >> qty >> addr;
            removeIt(name, qty, addr);
        } else if (cmd == "INFO") {
            info();
        }
        else if(cmd == "EXIT"){
            break;
        } else {
            cout << "Неизвестная команда\n";
         
        }
    }
    return 0;
}