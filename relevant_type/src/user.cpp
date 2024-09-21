
#include <user.h>

user::user () :
    _balance(0),
    _nickname(flyweight_string_singleton::get_singleton()->get_sample("")),
    _password(flyweight_string_singleton::get_singleton()->get_sample(""))
{   }

user::user(
    std::string nickname,
    std::string password, 
    long balance) :
    _nickname(flyweight_string_singleton::get_singleton()->get_sample(nickname)),
    _password(flyweight_string_singleton::get_singleton()->get_sample(password)),
    _balance(balance)
{  }

std::string user::get_nick () const noexcept
{

    return (*(_nickname)).get_data();

}

std::string user::get_password () const noexcept
{

    //Verification/SMTH

    return (*(_password)).get_data();

}

long int user::get_balance () const noexcept
{
    return _balance;
}



void user::copy_from (
    const user &other)
{   
    _balance =other._balance;
    _nickname = other._nickname;
    _password = other._password;
}

void user::move_from (
    user &&other)
{
    _balance = std::move(other._balance);
    _nickname = std::move(other._nickname);
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


