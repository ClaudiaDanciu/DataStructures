#include <iostream>
#include <string>
#include "ToDoQueue.h"
#include "TaskObject.h"
#include "ToDoHashTable.h"
using namespace std;

#define END "END"
#define EXIT "EXIT"
#define MENU "MENU"

int main() {
    cout << "To-Do List" << endl;
    cout << "Input your task and the priority between 1 and 3" << endl;
    cout << "(1 = Low, 2 = Medium, 3 = High)" << endl;
    cout << "Type 'END' to stop inputting and to view your list!" << endl;

    bool userAddingTasks = true;
    bool userRunningApplication = true;
    bool userIsInMenu = true;

    ToDoQueue* toDoList = new ToDoQueue();

    while (userAddingTasks) {
        string userTaskInput;
        int userPriorityInput;
        cout << "Enter the task: ";
        getline(cin, userTaskInput);
        if (userTaskInput == END) {
            userAddingTasks = false;
            break;
        }
        do {
            cout << "Enter the Priority (1 = Low, 2 = Medium, 3 = High): ";
            cin >> userPriorityInput;
            cout << endl;
            cin.ignore();
            cin.clear();
        } while (userPriorityInput < 1 || userPriorityInput > 3);
        toDoList->Insert(new TaskObject(userPriorityInput, userTaskInput));
    }

    cout << "Your Prioritised To-Do List:" << endl;
    ToDoHashTable* table = new ToDoHashTable();
    while (!toDoList->isEmpty()) {
        TaskObject* item = toDoList->Remove();
        cout << "Priority: " << item->priority << "\tTask: " << item->task << endl;
        table->Insert(item);
    }
    cout << "Your To-Do List Table:" << endl;
    table->Display();

    while (userRunningApplication) {
        string userChoiceInput;
        cout << "To-Do List" << endl;
        cout << "Search or mark a task as Complete" << endl;
        cout << "Type 'EXIT' to exit the application!" << endl;
        cout << "Would you like to Search for or Complete a task (enter 1 or 2):" << endl;
        cout << "1 - Search" << endl;
        cout << "2 - Complete a task" << endl;
        cin >> userChoiceInput;
        cin.ignore();
        cin.clear();
        if (userChoiceInput == EXIT) {
            userRunningApplication = false;
            break;
        }
        userIsInMenu = true;
        while (userIsInMenu) {
            if (userChoiceInput == "1") {
                string userSearchInput;
                TaskObject* objToFind;
                cout << "Search by task name: ";
                getline(cin, userSearchInput);
                if (userSearchInput == MENU) {
                    userIsInMenu = false;
                    break;
                }
                objToFind = table->Search(userSearchInput);
                if (objToFind && objToFind->task == userSearchInput) {
                    cout << "Found Task '" << userSearchInput << "'!" << endl;
                    cout << "Priority: " << objToFind->priority << endl;
                } else {
                    cout << "Task '" << userSearchInput << "' could not be found." << endl;
                }
            } else if (userChoiceInput == "2") {
                string userTaskNameInput;
                TaskObject* objToComplete;
                cout << "Enter the name of the task you wish to mark as complete: ";
                getline(cin, userTaskNameInput);
                if (userTaskNameInput == MENU) {
                    userIsInMenu = false;
                    break;
                }
                objToComplete = table->CompleteTask(userTaskNameInput);
                if (objToComplete && objToComplete->task == userTaskNameInput) {
                    cout << "Task '" << userTaskNameInput << "' has been completed and removed from your list!" << endl;
                    cout << "Your New To-Do List Table:" << endl;
                    table->Display();
                } else {
                    cout << "Task '" << userTaskNameInput << "' could not be found." << endl;
                }
            }
        }
    }
    return 0;
}
