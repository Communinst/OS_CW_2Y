
#include <singleton.h>


flyweight_string_singleton::flyweight_string_singleton()
{  }


flyweight_string_singleton *flyweight_string_singleton::get_singleton()
{
    static auto *singleton = new flyweight_string_singleton();
    return singleton;
}


std::shared_ptr<flyweight_string> flyweight_string_singleton::get_sample(const std::string &data)
{
    auto iter = _pool.find(data);
    if (iter != _pool.end())
    {
        return (iter->second);
    }

    auto new_flyweight_sample = std::make_shared<flyweight_string>(data);
    _pool[data] = new_flyweight_sample;

    return new_flyweight_sample;

}


void flyweight_string_singleton::update()
{
    for (auto iter = _pool.begin(); iter != _pool.end(); )
    {
        if (iter->second.use_count() == 1)
        {
            auto tmp = iter;
            ++iter;
            _pool.erase(tmp->first);
        }
        //To prevent ovelapping
        else
        {
            ++iter;
        }
    }
}

