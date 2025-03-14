#ifndef ORDERSPRIORQUEUE_H
#define ORDERSPRIORQUEUE_H
#include <iostream>
#include "Orders.h"

using namespace std;


// Node structure for the priority queue
struct orderNode 
{
    Orders* order;           // data
    orderNode* next;        // Pointer to the next node
};

class orderPriorQ 
{
public:
    orderNode* front;       

    // Constructor
    orderPriorQ() : front(nullptr) {}

    // Add an order to the priority queue based on its priority
    void enqueue(Orders * order) 
    {
        orderNode* newNode = new orderNode;
        newNode->order = order;
        newNode->next = nullptr;

		// empty or higher priority than front (technically lower but ykwim, 1 < 3 but 1 has "higher priority" )
        if (front == nullptr || order->priority < front->order->priority) 
        {
            newNode->next = front;
            front = newNode;
			cout << "Order added to the Restaurants queue" << endl;
            return;
        }
        else 
        {
            // Traverse to find position 
            orderNode* current = front;
            while (current->next != nullptr && current->next->order->priority <= order->priority) 
            {
                current = current->next;
            }
            // Insert
            newNode->next = current->next;
            current->next = newNode;
            cout << "Order added to the Restaurants queue" << endl;
            return;
        }
		cout << "Order could not be added to the Restaurants queue" << endl;
        return;
    }

    // Add an order based on its weight priority
    void enqueueByWeight(Orders* order)
    {
        
            orderNode* newNode = new orderNode;
            newNode->order = order;
            newNode->next = nullptr;

            // Check for an empty queue or if the new order has a smaller weight than the front
            if (front == nullptr || order->weight < front->order->weight)
            {
                newNode->next = front;
                front = newNode;
                cout << "Order added to the Restaurant's queue based on shortest weight" << endl;
                return;
            }
            else
            {
                // Traverse to find the correct position for the new order
                orderNode* current = front;
                while (current->next != nullptr && current->next->order->weight <= order->weight)
                {
                    current = current->next;
                }
                // Insert the new order at the correct position
                newNode->next = current->next;
                current->next = newNode;
                cout << "Order added to the Restaurant's queue based on shortest weight" << endl;
                return;
            }
            cout << "Order could not be added to the Restaurant's queue" << endl;
            return;
        

    }


    void printres()
    {
        if(front)
		cout << front->order->restaurantName;
    }
	//Process an order with highest priority
    Orders* dequeue() 
    {
        if (front == nullptr) 
        {
            cout << "\nQueue is empty!" << endl;
            return nullptr;
        }
        orderNode* temp = front;
        if (front->order->orderedDishes.removedDish())
        {
			cout << " Order corrupted !" << endl;
			cout << " A dish was removed from the order after it was placed. Order is now corrupted and will be removed from the queue." << endl;
			front = front->next;
			delete temp;
			return nullptr;
        }
        Orders* order = front->order;
        front = front->next;
        delete temp;  // Delete the node
        return order;
    }

    // To dequeee an order by weight
    Orders* dequeueByWeight()
    {
        if (front == nullptr)
        {
            cout << "\nQueue is empty!" << endl;
            return nullptr;
        }
        orderNode* temp = front;
        Orders* order = front->order;
        front = front->next;
        delete temp;  // Delete the node
        return order;
    }

    // Peek a boo ! look but dont pop
    Orders* peek() const 
    {
        if (front != nullptr) 
        {
            return front->order;
        }
        return nullptr;
    }

	//display the queue (for debugging and shii)
    void displayQueue() const 
    {
        if (!front)
            cout << "The queue is empty!\n";
        orderNode* current = front;
        while (current != nullptr) 
        {
            current->order->displayOrder();
            current = current->next;
        }
    }

	// good ol isEmpty function
    bool isEmpty() const 
    {
        return front == nullptr;
    }
};

#endif // !ORDERSPRIORQUEUE_H