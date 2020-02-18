#include "EndAssembly.h"
#include "Part.h"
#include "ProductArrival.h"
#include "Simulation.h"
#include "StartAssembly.h"
#include "Queue.h"
#include <iostream>
using namespace std;

EndAssembly::EndAssembly(int theTime, Simulation *sim, Part *thePart, Part *theOtherPart)
    : Event(theTime,sim), myPart(thePart), mySecPart(theOtherPart){}

//  1) For the main station, create ProductArrival event.
//     If main station available & P0,P1 are waiting schedule StartAssembly.
//  2) For the finishing station calculate statistics for the assembly of product.
void EndAssembly::processEvent()
{
    if(myPart->getPartNumber() == 0 || myPart->getPartNumber() == 1) // main station parts
    {
        sim->setMainStatus(false); // set main station to not busy
        cout << "At time " << sim->getSimulationTime() << ": Part P1 and P2 have been assembled in the Main Station to produce P3." << endl;

        // remove front part from the respective queues
        sim->removePart(this->myPart->getPartNumber());

        Part *newPart = new Part(3, sim->getSimulationTime());
        sim->addPartialProduct(newPart);

        // schedule Product Arrival
        ProductArrival *proEvent = new ProductArrival(sim->getSimulationTime(), this->sim, newPart);
        sim->addEvent(proEvent);

        // both P0 and P1 are waiting and main station is not busy
        if(!sim->getPartQueues(0)->isEmpty() && !sim->getPartQueues(1)->isEmpty() && !sim->isMainBusy())
        {
            StartAssembly *newStart = new StartAssembly(sim->getSimulationTime(), sim, dynamic_cast<Part *>(sim->getPartQueues(0)->getFront()), dynamic_cast<Part *>(sim->getPartQueues(1)->getFront())); // start assemblying  P0
            sim->addEvent(newStart);
        }
    }
    else // finishing station
    {
        sim->setFinishingStatus(false); // set finishing station is not busy
        // todo: remove part P2 and P3 from their queues
        cout << "At time " << sim->getSimulationTime() << ": Part P3 and P4 have been assembled in Finishing station to produce a finished product." << endl;
    }
}// end processEvent

EndAssembly::~EndAssembly() {}