
#include "flyweight_string.h"

flyweight_string::flyweight_string(
        const std::string &data) :
        _data(data)
{   }

const std::string &flyweight_string::get_data() const
{
    return _data;
}
