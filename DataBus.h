#ifndef DATABUS_H
#define DATABUS_H

#include <vector>
#include <map>
#include <utility>

class DataBus
{
public:
    void insert(std::string key, void* object);
    std::map<std::string, void*> data;
};

#endif // DATABUS_H

