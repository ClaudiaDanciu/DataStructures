#include <iostream>
#include <cassert>
#include "TaskObject.h"
#include "ToDoQueue.h"
#include "ToDoHashTable.h"

void testTaskObject() {
    TaskObject task1(1, "Task 1");
    TaskObject task2(2, "Task 2");
    assert(task1.priority == 1);
    assert(task1.task == "Task 1");
    assert(task2.priority == 2);
    assert(task2.task == "Task 2");
    assert(task1 < task2);
    std::cout << "TaskObject tests passed!" << std::endl;
}

void testToDoQueue() {
    ToDoQueue queue;
    TaskObject task1(1, "Task 1");
    TaskObject task2(2, "Task 2");
    TaskObject task3(3, "Task 3");
    queue.Insert(&task1);
    queue.Insert(&task2);
    queue.Insert(&task3);
    assert(!queue.isEmpty());
    assert(queue.Remove()->task == "Task 3");
    assert(queue.Remove()->task == "Task 2");
    assert(queue.Remove()->task == "Task 1");
    assert(queue.isEmpty());

    // Additional tests
    queue.Insert(&task1);
    queue.Insert(&task2);
    assert(queue.Remove()->task == "Task 2");
    assert(queue.Remove()->task == "Task 1");
    assert(queue.isEmpty());

    std::cout << "ToDoQueue tests passed!" << std::endl;
}

void testToDoHashTable() {
    ToDoHashTable table;
    TaskObject task1(1, "Task 1");
    TaskObject task2(2, "Task 2");
    TaskObject task3(3, "Task 3");
    table.Insert(&task1);
    table.Insert(&task2);
    table.Insert(&task3);
    assert(table.Search("Task 1") != nullptr);
    assert(table.Search("Task 2") != nullptr);
    assert(table.Search("Task 3") != nullptr);
    assert(table.Search("Nonexistent Task") == nullptr);
    assert(table.CompleteTask("Task 1")->task == "Task 1");
    assert(table.Search("Task 1") == nullptr);

    // Additional tests
    assert(table.CompleteTask("Task 2")->task == "Task 2");
    assert(table.Search("Task 2") == nullptr);
    assert(table.CompleteTask("Task 3")->task == "Task 3");
    assert(table.Search("Task 3") == nullptr);
    assert(table.Search("Nonexistent Task") == nullptr);

    std::cout << "ToDoHashTable tests passed!" << std::endl;
}

int main() {
    testTaskObject();
    testToDoQueue();
    testToDoHashTable();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
