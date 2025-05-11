#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Visitor{
    string ticket; //номер талона, время
    int duration;
};

string generate_tick()
{
    int num = rand()%1000; // берёт остаток от деления на 1000 взятый по модулю
    return "T" + to_string(num); //добавляем T к преобразованной в строку переменной num
}

int main()
{
    srand(time(0));
    int num_win;
    cout << "Введите количество окон: ";
    cin >> num_win;
    if(num_win >=0){
    vector<Visitor> visitors; // очередь всех посетителей
    vector<vector<Visitor>> windows(num_win); //посетители по каждому окну
    vector<int> win_times(num_win, 0); //время обслуживания в каждом окне

    string cmd;
    cout << "Введите команду: ";
    while(cin >> cmd){

        if(cmd == "ENQUEUE"){
            int dur;
            cin >> dur; //ввод продолжительности
            if(dur >0){
            visitors.push_back({generate_tick(),dur}); //добавление посетителя в очередь и генерация его билета

            cout << "-> " << visitors.back().ticket << endl; //вывод номера
            }
            else {
                cout << "Некорректное значение" << endl;
            }
        }
    
    else if(cmd == "DISTRIBUTE"){
        for (const auto& v : visitors) {
            int min_index = min_element(win_times.begin(), win_times.end()) - win_times.begin();
        //поиск окна с минимальной суммой времени

            windows[min_index].push_back(v); //в это окно назначаем посетителя
            win_times[min_index] += v.duration; // нагрузку увеличиваем
        }
        for (int i = 0; i < num_win; ++i) { //проход по всем онкнам от 0 до количества окон
            cout << "Окно " << (i + 1) << " " << win_times[i] << " минут: "; //вывод информацию о всех окон
        
            if (windows[i].empty()) { //если посетителя в окне нету
                cout << "(пусто)";

            } 
            else { //если окно не пустое, проходимся по посетителям это окне
                for (auto j = windows[i].begin(); j != windows[i].end(); j++) {
                    //итератор на начало списка и проход до конца
                    cout << (*j).ticket; //разыменываем, получаем доступ и выводим поле ticket
                    if (next(j) != windows[i].end()) 
                        cout << ", "; //если следующей элемент не равен последнему, запятая
                }
            }
            cout << "\n";
        }
        break;
    }
    else if(cmd == "INFO")
    {
        cout << "Доступные команды: ENQUEUE DISTRIBUTE INFO" << endl;
    }
    else{
        cout << "Неизвестная команда" << endl;
        continue;
        }
    }
}else{
    cout << "Некорректное значение окон" << endl;
}

    return 0;
}