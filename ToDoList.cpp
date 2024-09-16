#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// for error handeling of due date in addTAsk() function
int monthDay(int month){
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return 29;
    }
}

class Task{
public:
    string name;
    string description;
    int date;
    int month;
    bool completed;

    // display all info of the choosen task
    void taskInfo() const {
        cout<<"Name : "<<this->name<<endl;
        cout<<"Description : "<<this->description<<endl;
        cout<<"Due Date : "<<this->date<<"-"<<this->month<<endl;
        if(this->completed == true) cout<<"Completed"<<endl;
        else cout<<"Not Completed"<<endl;
        cout<<endl;
    }

    // read all info from the file to vector
    void updateInfo(vector <Task>& vTask) {
        ifstream update("taskDataBase.txt");
        string str;
        Task task;
        int i = 0;
        while(getline(update, str)){
            task.name = str;
            getline(update,str);
            task.description = str;
            getline(update,str);
            task.date = stoi(str);
            getline(update,str);
            task.month = stoi(str);
            getline(update,str);
            task.completed = (str == "1");
            i++;
            vTask.push_back(task);
        }
        update.close();
    }

    // add a new task in vector
    void addTask(vector <Task>& vTask) {
        Task task;
        cin.ignore();
        cout<<"_Enter Task Info_"<<endl;
        cout<<" Name : ";
        getline(cin,task.name);
        cout<<" Description : ";
        getline(cin,task.description);
        cout << " Due Date (format: dd mm) : ";

        while(1) {
            cin >> task.date >> task.month;

            if (cin.fail()) {
                cout << "Invalid input! Please enter numbers only. Enter Again (dd mm) : ";
                cin.clear();
                cin.ignore(10000, '\n');
            } else if ((task.month >= 1 && task.month <= 12) && (task.date >= 1 && task.date <= monthDay(task.month))) {
                break;
            } else {
                cout << "Invalid Date! Enter Again (dd mm) : ";
            }
        }

        task.completed = false;
        
        vTask.push_back(task);
        cout<<task.name<<" is added."<<endl;
    }

    // remove the choosen task from the vector
    void removeTask(vector <Task>& vTask) {
        int taskNo;
        int i = 1;
        cout<<"_TASKS_"<<endl;
        for(const auto& vTask : vTask){
            cout<<" "<<i++<<". "<<vTask.name<<endl;
        }
        cout<<"Select Task : ";
        cin>>taskNo;
        cout<<vTask[taskNo-1].name<<" is removed"<<endl;
        vTask.erase(vTask.begin()+taskNo-1);
    }

    // set completed to 1
    void markCompleted(vector <Task>& vTask) {
        int taskNo;
        int i = 1;
        cout<<"_TASKS_"<<endl;
        for(const auto& vTask : vTask){
            cout<<" "<<i++<<". "<<vTask.name<<endl;
        }
        cout<<"Select Task : ";
        cin>>taskNo;
        vTask[taskNo-1].completed = true;
        cout<<"YayY! You Completed "<<vTask[taskNo-1].name<<endl;
    }

    // show all uncompleted tasks
    void checkDue(vector <Task>& vTask) {
        cout<<"_DUE TASKS_"<<endl;
        int i = 1, count = 0;
        for(const auto& vTask : vTask){
            if(vTask.completed == 0){
                cout<<" "<<i++<<". "<<vTask.name<<endl;
                cout<<"    Date : "<<vTask.date<<"-"<<vTask.month<<endl<<endl;
                count++;
            }
        }
        if(count == 0) cout<<"No Due Tasks.\n";
    }
};

    // write info to file from vector
void saveInfo(const vector <Task>& vTask){ 
        ofstream save("taskDataBase.txt");
        for(const Task& obj : vTask){
            save<<obj.name<<endl;
            save<<obj.description<<endl;
            save<<obj.date<<endl;
            save<<obj.month<<endl;
            save<<obj.completed<<endl;
        }
        save.close();
    }

int main() {
    vector <Task> vTask;
    Task task;
    task.updateInfo(vTask);

    int expr,taskNo,i = 1;
    char cont;
        cout<<"Hello!\n";
    do {
        // menu
        cout<<"\nWhat do you wanna do?\n";
        cout<<" 1. Add Task\n";
        cout<<" 2. Remove Task\n";
        cout<<" 3. Mark Completed\n";
        cout<<" 4. Check Due Tasks\n";
        cout<<" 5. Show Task Info\n";
        cout<<"Choose : ";
        cin>>expr;
        cout<<endl;
        switch(expr) {
            case 1 :
                task.addTask(vTask);
                break;

            case 2 :
                task.removeTask(vTask);
                break;

            case 3 :
                task.markCompleted(vTask);
                break;

            case 4 :
                task.checkDue(vTask);
                break;

            case 5 :
                i = 1;
                cout<<"_TASKS_"<<endl;
                for(const auto& vTask : vTask){
                    cout<<" "<<i++<<". "<<vTask.name<<endl;
                }
                cout<<" "<<i<<". All Tasks\n";

                cout<<"Select Task : ";
                cin>>taskNo;
                cout<<endl;

                if(taskNo == i){
                    for(const auto& vTask : vTask){
                        vTask.taskInfo();
                    } 
                } else {
                        vTask[taskNo-1].taskInfo();
                    }
                break;

            default :
                cout<<"Invalid Option!\n";
                break;
        }
        cout<<"\nDo you want to continue (y/n) : ";
        cin.ignore();
        cin>>cont;

        if(cont == 'n'){
            cout<<"\nThanks for using the program!\n";
            cout<<"\nProgrammed By Dibya.\n";
            break;
        }
    }while (cont == 'y');

    saveInfo(vTask);
}