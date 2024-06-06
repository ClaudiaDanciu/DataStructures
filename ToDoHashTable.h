#pragma once
#include <iostream>
#include <string>
#include "TaskObject.h"
using namespace std;

#define TABLE_SIZE 17
#define PRIME 19

class ToDoHashTable {
private:
    TaskObject** data;
    int count;
    int GetASCIIKey(string key) {
        int ASCIItotal = 0;
        for (char c : key) {
            ASCIItotal += (int)c;
        }
        return ASCIItotal;
    }
    int HashFunction(string key) {
        int ASCIIKey = GetASCIIKey(key);
        return ASCIIKey % TABLE_SIZE;
    }
    int DoubleHashFunction(string key) {
        int ASCIIKey = GetASCIIKey(key);
        return PRIME - (ASCIIKey % TABLE_SIZE);
    }
public:
    ToDoHashTable() {
        data = new TaskObject*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            data[i] = NULL;
        }
    }
    bool isFull() {
        return count == TABLE_SIZE;
    }
    void Display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (data[i] != NULL) {
                cout << "Index: " << i << "\tPriority: " << data[i]->priority << "\tTask: " << data[i]->task << endl;
            }
        }
    }
    void Insert(TaskObject* item) {
        if (isFull()) return;
        string key = item->task;
        int hash = HashFunction(key);
        if (data[hash] != NULL) {
            int doubleHash = DoubleHashFunction(key);
            int index = 1;
            while (true) {
                int newHash = (hash + index * doubleHash) % TABLE_SIZE;
                if (data[newHash] == NULL) {
                    data[newHash] = item;
                    break;
                }
                index++;
            }
        } else {
            data[hash] = item;
        }
        count++;
    }
    TaskObject* Search(string key) {
        int hash = HashFunction(key);
        int doubleHash = DoubleHashFunction(key);
        int index = 0;
        while (data[(hash + index * doubleHash) % TABLE_SIZE] != NULL) {
            TaskObject* item = data[(hash + index * doubleHash) % TABLE_SIZE];
            if (item->task == key) {
                return item;
            }
            index++;
        }
        return NULL;
    }
    TaskObject* CompleteTask(string key) {
        int hash = HashFunction(key);
        int doubleHash = DoubleHashFunction(key);
        int index = 0;
        while (data[(hash + index * doubleHash) % TABLE_SIZE] != NULL) {
            TaskObject* item = data[(hash + index * doubleHash) % TABLE_SIZE];
            if (item->task == key) {
                data[(hash + index * doubleHash) % TABLE_SIZE] = NULL;
                return item;
            }
            index++;
        }
        return NULL;
    }
};
