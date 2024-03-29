// CLASS: StartAssembly.h
//
// Author: Patel Zil, 7876456
//
// REMARKS:
//
//-----------------------------------------

#pragma once

#include "Event.h"
class Part;

class StartAssembly: public Event
{
private:
    Part *myPart;
    Part *mySecondPart;
public:
    StartAssembly(int , Simulation *, Part *, Part *);
    ~StartAssembly();
    void processEvent();
};// StartAssembly
