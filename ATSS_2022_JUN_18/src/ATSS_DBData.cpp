#include "inc/ATSS_Includes.h"
extern ATSS_Communication atss_communication_obj;
extern ATSS_MessageProcessor msg_processor_obj;

ATSS_DBData :: ATSS_DBData()
{
    //    printf("\n ATSS_DBData constructor call");
    pthread_mutex_init(&rolling_stock_lock, NULL);
    pthread_mutex_init(&junction_info_lock, NULL);

}


// ________________________________________________________________________________________________________________________________________________________________________________________________

#include <iostream>
#define SIZE 5
using namespace std;

class Queue
{
private:
    int items[SIZE], front, rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }
    // Check if the queue is full
    bool isFull()
    {
        if (front == 0 && rear == SIZE - 1)
        {
            return true;
        }
        if (front == rear + 1)
        {
            return true;
        }
        return false;
    }
    // Check if the queue is empty
    bool isEmpty()
    {
        if (front == -1)
            return true;
        else
            return false;
    }
    // Adding an element
    void enQueue(int element)
    {
        if (isFull())
        {
            cout << "\nQueue is full";
        }
        else
        {
            if (front == -1)
            {
                front = 0;
            }
            rear = (rear + 1) % SIZE;
            items[rear] = element;
            cout << endl<< "Inserted " << element << endl;
        }
    }
    // Removing an element
    int deQueue()
    {
        int element;
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return (-1);
        }
        else
        {
            element = items[front];
            if (front == rear)
            {
                front = -1;
                rear = -1;
            }
            // Q has only one element,
            // so we reset the queue after deleting it.
            else
            {
                front = (front + 1) % SIZE;
            }
            return (element);
        }
    }

    void display()
    {
        // Function to display status of Circular Queue
        int i;
        if (isEmpty())
        {
            cout << endl<< "Empty Queue" << endl;
        }
        else
        {
            cout << "\nFront -> " << front;
            cout << endl<< "Items -> ";
            for (i = front; i != rear; i = (i + 1) % SIZE)
                cout << items[i]<<" ";
            cout << items[i];
            cout << endl<< "Rear -> " << rear;
        }
    }
};
