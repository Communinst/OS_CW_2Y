
#include <user.h>

user::user(
    std::string login,
    std::string password) :
    _login(flyweight_string_singleton::get_singleton()->get_sample(login)),
    _password(flyweight_string_singleton::get_singleton()->get_sample(password))
{  }

void user::copy_from (
    const user &other)
{   
    _balance =other._balance;
    _login = other._login;
    _password = other._password;
}

void user::move_from (
    user &&other)
{
    _balance = std::move(other._balance);
    _login = std::move(other._login);
    _password = std::move(other._password);
}   

user::user (
    const user &other)
{   
    copy_from(other);
}

user::user (
    user &&other)
{
    if (this != &other)
    {
        move_from(std::move(other));
    }
}

user &user::operator= (
    const user &other)
{
    copy_from(other);
    return *this;
}

user &user::operator= (
    user &&other)
{
    if (this != &other)
    {
        move_from(std::move(other));
    }
    return *this;
}


