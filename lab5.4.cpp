#include <iostream>
#include <vector>
#include <string>

using namespace std;
    
// количество дней в каждом месяце с января по декабрь
const vector<int> m_days = {31,28,31,30,31,30,31,31,30,31,30,31};

    //двуммерный вектор т.к вектор на каждый день месяца внутри которого список названий предметов
void add_c(vector<vector<string>>& schedule, int day, const string& subj){
    for(string& i: schedule[day-1]){ //-1 в векторах дни с 0 а должны быть с 1
        if(i == subj) //если предмет уже есть в расписании ничего не происходит
            return;
    }
    schedule[day-1].push_back(subj); 
}

void view(vector<vector<string>>& schedule, int day){
    vector<string>& classes = schedule[day-1]; //список предметов для дня который введён
    if(classes.empty()){ //если вектор пустой то занятий нету
        cout << "В " << day << " день Мы свободны" << endl;
    }
    else { 
        cout << "В " << day << " день " << classes.size() << " занятий в университете:" << endl;
        for(string& s : classes){ //перечисление всех занятий
            cout << s << endl;
        }
    }
}

//смена месяца на текущий и перенос предметов из недостающих дней в предпоследний
void next_month(vector<vector<string>>& schedule, int& cur_month){
    int old_days = schedule.size(); //количество дней было в текущем месяце
    cur_month = (cur_month +1 )%12; //увеличиваем текущий месяц на 1 и не выходим за пределы от 0 до 11

    int new_days = m_days[cur_month]; //количество дней текущего месяца

    vector<vector<string>> new_schedule(new_days);

    for(int i=0; i<new_days && i < old_days; ++i){
        new_schedule[i] = schedule[i]; //копирование расписания из старого месяца в новый
    }

    //если в новом месяце меньше дней чем в старом то переносит в предпоследний день нового
    if(old_days > new_days){
        for(int i=new_days; i<old_days; i++){ //перебор всех дней старого месяца
            for(string& s : schedule[i]){ //перебор предметов в день i старого месяца

                bool exists = false; //проверка существования предмета
                for(string& x: new_schedule[new_days -2]){ //перебор в предпоследний день нового месяца
                    if(x == s ){ //если текущий предмет старого месяца (s) уже в списке 
                        exists = true; 
                        break;
                    }
                }
            if(!exists) //если предмет не был добавлен в предпоследний день
            {
                new_schedule[new_days -2].push_back(s); //добавляем в предпоследний день 
            }
            }

        }
    }
    schedule = new_schedule;
}


int main()
{
    int n;
    cout << "Введите количество команд: ";
    cin >> n;
    if (n>0){
    int curr_month =0; //индекс текущего месяца 
    //двумерный вектор для хранения расписания
    vector<vector<string>> schedule(m_days[curr_month]); //содержит столько вложенных списков, сколько дней в месяце

    int i = 0;
    cout << "Список доступных команды: CLASS VIEW NEXT INFO" << endl;
while (i < n) {
    string command;
    
    cin >> command;

    if (command == "CLASS") {
        int day;
        string subject;
        cin >> day >> subject;
        cout << "Предмет добавлен" << endl;
        add_c(schedule, day, subject);
    } else if (command == "VIEW") {
        int day;
        cin >> day;
        view(schedule, day);
    } else if (command == "NEXT") {
        next_month(schedule, curr_month);
    }
    else if(command == "INFO"){
        cout << "CLASS: <день месяца> <предмет>" << endl;
        cout << "NEXT: (Переход месяца)" << endl;
        cout << "VIEW: <день месяца> (количество занятий в определённый день месяца)" << endl;
    }
    else {
        cout << "Incorrect command" << endl;
    }

    ++i;
}
    }
    else {
        cout << "Некорректное количество команд"<< endl;
    }
    
    return 0;
}