#ifndef COMMAND_H
#define COMMAND_H

#include "DataBus.h"

class Command
{
public:
    virtual void proc(DataBus* dtBus) = 0;
};

#endif // COMMAND_H
