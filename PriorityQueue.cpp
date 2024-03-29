// CLASS: PriorityQueue.cpp
//
// Author: Patel Zil, 7876456
//
// REMARKS: Data structure used to hold different types
//          of events according to its time for the simulator
//          to process it accordingly
//
//-----------------------------------------

#include "PriorityQueue.h"
#include "Node.h"
#include "OrderedItem.h"


PriorityQueue::PriorityQueue() : front(nullptr), size(0) {}
int PriorityQueue::getSize() {return size; }
bool PriorityQueue::isEmpty() {return size == 0;}

OrderedItem *PriorityQueue::getFront()
{
    OrderedItem *result = nullptr;
    if(front != nullptr){
        result = dynamic_cast<OrderedItem *> (front->getItem());
    }
    return result;
}// getFront

/* insert(OrderedItem *)
 *
 * Inserts event into the priority queue according
 * to the time of the event.
 *
 */
void PriorityQueue::insert(OrderedItem *newItem )
{
    Node *curr = front;
    Node *prev = nullptr;

    // search for the position at which the newItem will be placed in the priority queue
    // condition equal to zero so that an event with similar eventTime is added later as it came after the already present event
    while(curr != nullptr && ((dynamic_cast<OrderedItem *>(curr->getItem()))->compareTo(newItem) <= 0))
    {
        prev = curr;
        curr = curr->getNext();
    }

    // insert the newItem into the Priority queue
    if(prev != nullptr)
    {
        prev->setNext(new Node(newItem, curr));
    }
    else // special case: adding to empty priority queue
    {
        front = new Node(newItem, curr);
    }
    size++;
}

/* deleteHighest()
 *
 * delete the first Node(highest priority) from the priority queue
 *
 */
OrderedItem *PriorityQueue::deleteHighest()
{
    OrderedItem *result = nullptr;
    if(front != nullptr)
    {
        Node *curr = front;
        result = dynamic_cast<OrderedItem *>(front->getItem());
        // special case: removing item from priority queue with only 1 event
        if(size == 1)
        {
            front = nullptr;
        }
        else
        {
            front = front->getNext();
        }
        size--;
        delete(curr);
    }
    return result;
}

// destructor
PriorityQueue::~PriorityQueue() {}