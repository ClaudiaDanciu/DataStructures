#pragma once
#include "TaskObject.h"
using namespace std;

#define SIZE 20

class ToDoQueue {
private:
    int count;
    TaskObject** data;
public:
    ToDoQueue() {
        data = new TaskObject*[SIZE];
        count = 0;
    }
    ~ToDoQueue() {}
    void Insert(TaskObject* item) {
        if (isEmpty()) {
            data[count++] = item;
        } else {
            int i;
            for (i = count - 1; i >= 0; i--) {
                if (*item < *data[i]) {
                    data[i + 1] = data[i];
                } else {
                    break;
                }
            }
            data[i + 1] = item;
            count++;
        }
    }
    TaskObject* Remove() {
        return data[--count];
    }
    bool isEmpty() {
        return count == 0;
    }
};
