#include "DataBus.h"

void DataBus::insert(std::string key, void* object)
{
    data.insert(std::pair<std::string, void*>(key, object));
}
