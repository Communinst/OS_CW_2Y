
#include <inner_architecture.h>

#include <direct.h>
#include <filesystem>
#include <windows.h>
#include <fstream>
#include <iostream>

#include <climits>
#include <fcntl.h>
#include <sys/stat.h>

#include <io.h>
#include <stdio.h>
#include <stdlib.h>

#include <cstring>
#include <climits>




#pragma region TKEY TOOLS

int db_storage::fw_key_comparator::operator() (
    const tkey_flyweight first,
    const tkey_flyweight second)
{

    return (first.get()->get_data().compare(second.get()->get_data()));

}

#pragma endregion TKEY TOOLS




#pragma region ERRORS

db_storage::setup_fault::setup_fault (
    const std::string &mes) :
    logic_error(mes)
{   }

db_storage::existent_struct_insertion_attempt_exception::existent_struct_insertion_attempt_exception () :
    logic_error("Passed structure's already in base. An existent structure insertion attempts are prohibited.")
{   }

db_storage::nonexistent_struct_disposal_attempt_exception::nonexistent_struct_disposal_attempt_exception () :
    logic_error("Passed structure's not in base. A nonexistent structure can't be disposed.")
{   }

db_storage::nonexistent_struct_obtaining_attempt_exception::nonexistent_struct_obtaining_attempt_exception () :
    logic_error("Passed structure's not in base. A nonexistent structure can't be obtained.")
{   }

db_storage::nonesixtent_struct_updating_attempt_exception::nonesixtent_struct_updating_attempt_exception () :
    logic_error("Passed structure's not in base. A nonexistent structure can't be updated.")
{   }

db_storage::nonexistent_file_path_hit_attempt_exception::nonexistent_file_path_hit_attempt_exception () :
    logic_error("Passed file path does not exist. A nonexistent file/directory can't be reached.")
{   }

db_storage::invalid_path_exception::invalid_path_exception () :
    logic_error("Path is invalid.")
{   }

db_storage::path_length_exception::path_length_exception (
    const std::string op) :
    logic_error("Path is too" + op + '+')
{   }

db_storage::invalid_name_exception::invalid_name_exception (
    const std::string name,
    const std::string of) :
    logic_error(name + "is not allowed for " + of)
{   }

db_storage::insertion_failure::insertion_failure () :
    logic_error("Insertion attempt failed.")
{   }

#pragma endregion ERRORS




#pragma region THROWS

db_storage &db_storage::throw_if_init ()
{
    if (_mode == ipc::mode::UNINITIALIZED)
    {   
        return *this;
    }

    throw db_storage::setup_fault ("Mode re-initialization is prohibited.");
}

db_storage &db_storage::throw_if_uninit ()
{
    if (_mode != ipc::mode::UNINITIALIZED)
    {
        return *this;
    }

    throw db_storage::setup_fault ("None of the operations can be carryed out without mode initialization.");
}

db_storage &db_storage::throw_if_invalid_params (
    size_t id,
    ipc::mode mode)
{
    if (mode != ipc::mode::UNINITIALIZED && id > 0)
    {
        return *this;
    }

    throw db_storage::setup_fault("Passed parameters are invalid.");
}

db_storage &db_storage::throw_if_invalid_path (
    const std::string path)
{

    if (_mode == ipc::mode::FILE)
    {
        if (_access(path.c_str(), 0) == -1)
        {
            throw db_storage::nonexistent_file_path_hit_attempt_exception();
        }   
    }

    return *this;

}

db_storage &db_storage::throw_if_invalid_file_name (
    const std::string file_name)
{
    if (_mode == ipc::mode::FILE)
    {
        bool space = false;
        for (char ch : file_name)
        {
            if (!isalnum(ch) && ch != '_' && ch != '-' && ch != ' ')
            {
                throw db_storage::invalid_name_exception(file_name, "file");
            }
            space = ch == ' ';
        }
        if (space)
        {
            throw db_storage::invalid_name_exception(file_name, "file");
        }
    }

    return *this;

}

db_storage &db_storage::throw_if_path_too_long (
    const std::string path)
{

    if (_mode == ipc::mode::FILE)
    {
        char cwd[MAX_PATH];
        char *code = getcwd(cwd, MAX_PATH);
        if (code == nullptr)
        {
            throw db_storage::invalid_path_exception();
        }
        if ((std::string(cwd) + path).size() > MAX_PATH - 10)
        {
            throw db_storage::path_length_exception("big");
        }
    }

    return *this;

}


#pragma endregion THROWS




#pragma region TDATA


    #pragma region RAM_TDATA IMPLEMENTATION

db_storage::ram_tdata::ram_tdata (
    const user &other) :
    _user_data(other)
{   }

db_storage::ram_tdata::ram_tdata (
    user &&other) :
    _user_data(std::move(other))
{   }

user &db_storage::ram_tdata::get_user_data ()
{
    return _user_data;
}

    #pragma endregion RAM_TDATA IMPLEMENTATION



    #pragma region FILE_TDATA IMPLEMENTATION

db_storage::file_tdata::file_tdata (
    long int file_pos) :
    _cur_file_pos(file_pos)
{   }

void db_storage::file_tdata::serialize (
    const std::string &path,
	const std::string &key,
	const user &value,
	bool update_flag)
{

    std::ofstream data_strm (path, std::ios::binary | std::ios::app);

    if (!data_strm.is_open())
    {
        throw std::ios::failure("File down the path can't be opened.");
    }

    if (_cur_file_pos == -1 || update_flag)
    {
        _cur_file_pos = data_strm.tellp();
    }

    else
    {
        data_strm.seekp(_cur_file_pos, std::ios::beg);
    }

    size_t login_length = key.size();
    size_t nick_length = value.get_nick().size();
    size_t pass_length = value.get_password().size();


    data_strm.write (reinterpret_cast<const char *>(&nick_length), sizeof(size_t));
    data_strm.write (value.get_nick().c_str(), sizeof(char) * nick_length);

    data_strm.write (reinterpret_cast<const char *>(value.get_balance()), sizeof(long int));

    data_strm.write (reinterpret_cast<const char *>(&login_length), sizeof(size_t));
    data_strm.write (key.c_str(), sizeof(char) * login_length);

    data_strm.write (reinterpret_cast<const char *>(&pass_length), sizeof(size_t));
    data_strm.write (value.get_password().c_str(), sizeof(char) * pass_length);

    data_strm.flush();

    if (data_strm.fail())
    {
        throw std::ios::failure("Serialization failure.");
    }

}

user db_storage::file_tdata::deserialize (
		const std::string &path) const
{
    std::ifstream data_strm (path, std::ios::binary);

    if (!data_strm.is_open())
    {
        throw std::ios::failure("File down the path can't be opened.");
    }

    if (_cur_file_pos == -1)
    {
        throw std::logic_error ("Wrong file data pointer.");
    }

//
    //std::string login, nickname, password;
    //size_t login_length, nick_length, pass_length;
    //long balance;
//
    //data_strm.read (reinterpret_cast<char *>(&nick_length), sizeof(size_t));
    //data_strm.read (reinterpret_cast<char *>(&nickname), sizeof(char) * nick_length);
 //
    //data_strm.read (reinterpret_cast<char *>(&balance), sizeof(long int));
 //
    //data_strm.read (reinterpret_cast<char *>(&login_length), sizeof(size_t));
    //data_strm.read (reinterpret_cast<char *>(&login), sizeof(char) * login_length);
 //
    //data_strm.read (reinterpret_cast<char *>(&pass_length), sizeof(size_t));
    //data_strm.read (reinterpret_cast<char *>(&password), sizeof(char) * pass_length);

    
    size_t login_length, nick_length, pass_length;
    long balance;

    data_strm.read (reinterpret_cast<char *>(&nick_length), sizeof(size_t));
    std::string nickname (nick_length + 1, '\0');
    data_strm.read (reinterpret_cast<char *>(&nickname), sizeof(char) * nick_length);
 
    data_strm.read (reinterpret_cast<char *>(&balance), sizeof(long int));
 
    data_strm.read (reinterpret_cast<char *>(&login_length), sizeof(size_t));
    std::string login (login_length + 1, '\0');
    data_strm.read (reinterpret_cast<char *>(&login), sizeof(char) * login_length);
 
    data_strm.read (reinterpret_cast<char *>(&pass_length), sizeof(size_t));
    std::string password (pass_length + 1, '\0');
    data_strm.read (reinterpret_cast<char *>(&password), sizeof(char) * pass_length);

    user user_data (
        nickname,
        password,
        balance);

    return user_data;

}   


    #pragma endregion FILE_TDATA IMPLEMENTATION


#pragma endregion TDATA




#pragma region COLLECTION PROPS IMPLEMENTATION




allocator *db_storage::collection::get_allocator() const noexcept
{
    return _allocator.get();
}

void db_storage::collection::clear()
{
    delete _tdata;
    
    _tdata = nullptr;
    _allocator = nullptr;
};

void db_storage::collection::copy_from(
    collection const &other)
{
    switch (_search_tvar = other._search_tvar)
    {
        case ipc::search_tvar::B:
            try
            {
                _tdata = new b_tree<tkey_flyweight, tdata *>(
                    *dynamic_cast<b_tree<tkey_flyweight, tdata *> *>(other._tdata));
            }
            catch (std::bad_alloc const &)
            {
                throw;
            }

        default:
            break;
    }
    
    _fit_mode = other._fit_mode;
    _allocator = other._allocator;
};

void db_storage::collection::move_from(
    collection &&other)
{
    switch (_search_tvar = other._search_tvar)
    {
        case ipc::search_tvar::B:
            try
            {
                _tdata = new b_tree<tkey_flyweight, tdata *>(
                    std::move(*dynamic_cast<b_tree<tkey_flyweight, tdata *> *>(other._tdata)));
            }
            catch (std::bad_alloc const &)
            {
                throw;
            }
        default:
            break;
    }
    
    _fit_mode = other._fit_mode;
    _allocator = std::move(other._allocator);
};

void db_storage::collection::check_if_refresh (
    const std::string &path)
{

    if ( _disposed_amount > 0.33 * _records_amount)
    {
        refresh(path);
        flyweight_string_singleton::get_singleton()->update();
        _disposed_amount = 0;
    }

}

void db_storage::collection::refresh (
    const std::string &path)
{

    if (get_singleton()->_mode == ipc::mode::RAM)
    {
        return;
    }

    std::string tmp_dir_path = DC_utilities::make_path({path, "tmp"});
    std::string data_path = DC_utilities::make_path({path, std::to_string(get_singleton()->_id)});
    std::string tmp_data_path = DC_utilities::make_path({path, "tmp", std::to_string(get_singleton()->_id)});

    if (_access(data_path.c_str(), 0) == -1)
    {
        return;
    }

    mkdir(tmp_dir_path.c_str());

    switch (_search_tvar)
    {
        case ipc::search_tvar::B:
        {
            long pos = 0;
            auto iter = dynamic_cast<b_tree<tkey_flyweight, tdata *> *>(_tdata)->begin_infix();
            auto iter_end = dynamic_cast<b_tree<tkey_flyweight, tdata *> *>(_tdata)->end_infix();

            std::fstream tmp_data_strm(tmp_data_path, std::ios::binary | std::ios::trunc);

            tmp_data_strm.close();

            for (; iter != iter_end ; iter++)
            {
                tkey key = (*(std::get<2>(*iter))).get_data();
                file_tdata *data = dynamic_cast<file_tdata *>(std::get<3>(*iter));
                user user_data = data->deserialize(data_path);
                data->serialize(tmp_data_path, key, user_data, true);
            }

            tmp_data_strm.flush();

            tmp_data_strm.open(tmp_data_path, std::ios::in | std::ios::binary);
            if (!tmp_data_strm.is_open())
            {
                throw std::ios::failure("Tmp file down the path can't be opened.");
            }
            
            std::fstream data_stream(data_path, std::ios::out | std::ios::binary | std::ios::trunc);
            if (!data_stream.is_open())
            {
                throw std::ios::failure("Origin ile down the path can't be opened.");
            }
            
            (data_stream << tmp_data_strm.rdbuf()).flush();
            std::filesystem::remove_all(tmp_dir_path);
            //std::remove(tmp_data_path.c_str());

        }
        default:
            break;
    }

}


    #pragma region RoF IMPLEMENTATION

db_storage::collection::~collection()
{
    clear();
}

db_storage::collection::collection(
    const collection &other)
{
    copy_from(other);
}

db_storage::collection &db_storage::collection::operator=(
    const collection &other)
{
    if (this != &other)
    {
        clear();
        copy_from(other);
    }
    
    return *this;
}

db_storage::collection::collection(
    collection &&other) noexcept
{
    move_from(std::move(other));
}

db_storage::collection &db_storage::collection::operator=(
    db_storage::collection &&other) noexcept
{
    if (this != &other)
    {
        clear();
        move_from(std::move(other));
    }

    return *this;
}

    #pragma endregion RoF IMPLEMENTATION


    #pragma BASICS

db_storage::collection::collection (
    ipc::search_tvar search_tvar,
    ipc::allocator_var allocator_var,
    allocator_with_fit_mode::fit_mode fit_mode,
    size_t param_for_tree) :
        _search_tvar(search_tvar),
        _fit_mode(fit_mode),
        _allocator_var(allocator_var),
        _records_amount(0),
        _disposed_amount(0)
{
    switch (search_tvar)
    {
        case ipc::search_tvar::B:
            _tdata = new b_tree<tkey_flyweight, tdata *>(
                param_for_tree,
                db_storage::fw_key_comparator());

        default:
            break;
    }

    try
    {
        switch (allocator_var)
        {
            case ipc::allocator_var::GLOBAL_HEAP:
               _allocator = std::make_shared<allocator_global_heap>();
               break;

            case ipc::allocator_var::BOUNDARY_TAGS:
                _allocator = std::make_shared<allocator_boundary_tags>(
                    1 << 22, 
                    nullptr, 
                    nullptr, 
                    _fit_mode);
                break;

            default:
                break;

        }
    }
    catch (const std::bad_alloc &)
    {
        delete _tdata;
        throw;
    }

}


void db_storage::collection::add_to_inner (
    const std::string &user_name,
    const user &user,
    const std::string &path)
{

    check_if_refresh(path);

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(user_name);
    tdata *data = nullptr;

    try
    {
        if (get_singleton()->_mode == ipc::mode::RAM)
        {
            data = reinterpret_cast<ram_tdata *>(allocate_with_guard(sizeof(tdata), 1));
            allocator::construct(reinterpret_cast<ram_tdata *>(data), user);
        }
        else if (get_singleton()->_mode == ipc::mode::FILE)
        {
            data = reinterpret_cast<file_tdata *>(allocate_with_guard(sizeof(file_tdata), 1));
            allocator::construct(reinterpret_cast<file_tdata *>(data));
        }
    }
    catch (const std::bad_alloc &)
    {
        deallocate_with_guard(data);
        throw;
    }
    
    try
    {
        if (get_singleton()->_mode == ipc::mode::FILE)
        {
            reinterpret_cast<file_tdata *>(data)->serialize(path, fw.get()->get_data(), user);
        }

        _tdata->insert(fw, data);

    }
    catch (const std::bad_alloc &)
    {
        deallocate_with_guard(data);
        throw;
    }
    catch (const std::ios::failure &)
    {
        allocator::destruct(data);
        deallocate_with_guard(data);
        throw std::ios::failure("Attempt to write file's failed");
    }
    catch (const search_tree<tkey_flyweight, tdata *>::insertion_of_existent_key_attempt_exception_exception &)
    {
        allocator::destruct(data);
        deallocate_with_guard(data);
        throw db_storage::existent_struct_insertion_attempt_exception();
    }

    std::cout << _records_amount << std::endl;
    _records_amount += 1;

}

void db_storage::collection::add_to_inner (
    const std::string &user_name,
    const user &&user,
    const std::string &path)
{

    check_if_refresh(path);

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(user_name);
    tdata *data = nullptr;

    try
    {
        if (get_singleton()->_mode == ipc::mode::RAM)
        {
            data = reinterpret_cast<ram_tdata *>(allocate_with_guard(sizeof(tdata), 1));
            allocator::construct(reinterpret_cast<ram_tdata *>(data), std::move(user));
        }
        else if (get_singleton()->_mode == ipc::mode::FILE)
        {
            data = reinterpret_cast<file_tdata *>(allocate_with_guard(sizeof(file_tdata), 1));
            allocator::construct(reinterpret_cast<file_tdata *>(data));
        }
    }
    catch (const std::bad_alloc &)
    {
        deallocate_with_guard(data);
        throw;
    }
    
    try
    {
        if (get_singleton()->_mode == ipc::mode::FILE)
        {
            reinterpret_cast<file_tdata *>(data)->serialize(path, fw.get()->get_data(), user);
        }

        _tdata->insert(fw, data);

    }
    catch (const std::bad_alloc &)
    {
        deallocate_with_guard(data);
        throw;
    }
    catch (const std::ios::failure &)
    {
        allocator::destruct(data);
        deallocate_with_guard(data);
        throw std::ios::failure("Attempt to write file's failed");
    }
    catch (const search_tree<tkey_flyweight, tdata *>::insertion_of_existent_key_attempt_exception_exception &)
    {
        allocator::destruct(data);
        deallocate_with_guard(data);
        throw db_storage::existent_struct_insertion_attempt_exception();
    }

    _records_amount += 1;
}


void db_storage::collection::update_inner (
    const std::string &user_name,
    const user &user,
    const std::string &path)
{
    check_if_refresh(path);

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(user_name);
    tdata *data = nullptr;
    
    try
    {
        if (get_singleton()->_mode == ipc::mode::RAM)
        {
            data = reinterpret_cast<ram_tdata *>(allocate_with_guard(sizeof(ram_tdata), 1));
            allocator::construct(reinterpret_cast<ram_tdata *>(data), user);
            
        }
        else
        {
            data = reinterpret_cast<file_tdata *>(allocate_with_guard(sizeof(file_tdata), 1));
            allocator::construct(reinterpret_cast<file_tdata *>(data));
        }
    }
    catch (std::bad_alloc const &)
    {
        deallocate_with_guard(data);
        throw;
        // TODO
    }
    
    try
    {
        if (get_singleton()->_mode == ipc::mode::FILE)
        {
            reinterpret_cast<file_tdata *>(data)->serialize(path, fw.get()->get_data(), user);
        }
        
        _tdata->update(fw, data);
    }
    catch (std::ios::failure const &)
    {
        allocator::destruct(data);
        deallocate_with_guard(data);
        throw std::ios::failure("Attempt to write file's failed");
    }
    catch (std::bad_alloc const &)
    {
        deallocate_with_guard(data);
        throw;
    }
    catch (search_tree<tkey, tdata *>::updating_of_nonexistent_key_attempt_exception const &)
    {
        allocator::destruct(data);
        deallocate_with_guard(data);
        throw db_storage::nonesixtent_struct_updating_attempt_exception();
    }

}

void db_storage::collection::update_inner (
    const std::string &user_name,
    const user &&user,
    const std::string &path)
{
    check_if_refresh(path);

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(user_name);
    tdata *data = nullptr;
    
    try
    {
        if (get_singleton()->_mode == ipc::mode::RAM)
        {
            data = reinterpret_cast<ram_tdata *>(allocate_with_guard(sizeof(ram_tdata), 1));
            allocator::construct(reinterpret_cast<ram_tdata *>(data), std::move(user));
            
        }
        else
        {
            data = reinterpret_cast<file_tdata *>(allocate_with_guard(sizeof(file_tdata), 1));
            allocator::construct(reinterpret_cast<file_tdata *>(data));
        }
    }
    catch (std::bad_alloc const &)
    {
        deallocate_with_guard(data);
        throw;
        // TODO
    }
    
    try
    {
        if (get_singleton()->_mode == ipc::mode::FILE)
        {
            reinterpret_cast<file_tdata *>(data)->serialize(path, fw.get()->get_data(), user);
        }
        
        _tdata->update(fw, data);
    }
    catch (std::ios::failure const &)
    {
        allocator::destruct(data);
        deallocate_with_guard(data);
        throw std::ios::failure("Attempt to write file's failed");
    }
    catch (std::bad_alloc const &)
    {
        deallocate_with_guard(data);
        throw;
    }
    catch (search_tree<tkey, tdata *>::updating_of_nonexistent_key_attempt_exception const &)
    {
        allocator::destruct(data);
        deallocate_with_guard(data);
        throw db_storage::nonesixtent_struct_updating_attempt_exception();
    }
}

user db_storage::collection::dispose_from_inner (
    const std::string &user_name,
    const std::string &path)
{

    check_if_refresh(path);

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(user_name);
    tdata *data = nullptr;
    user user;

    try
    {
        data = _tdata->dispose(fw);
    }
    catch (const search_tree<tkey_flyweight, tdata *>::disposal_of_nonexistent_key_attempt_exception &)
    {
        flyweight_string_singleton::get_singleton()->update();
        throw db_storage::nonexistent_struct_disposal_attempt_exception();
    }
    if (get_singleton()->_mode == ipc::mode::FILE)
    {
        try
        {
            user = dynamic_cast<file_tdata *>(data)->deserialize(path);
        }
        catch (std::ios::failure const &)
        {
            allocator::destruct(data);
            deallocate_with_guard(data);
            throw std::ios::failure("Failed to parse disposed data");
        }
    }
    else
    {
        user = dynamic_cast<ram_tdata *>(data)->_user_data;
    }

    _records_amount--;

    return user;

} 

user db_storage::collection::obtain_from_inner (
    const std::string &user_name,
    const std::string &path
    )
{   
    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(user_name);
    
    tdata *data = nullptr;

    try
    {
        data = _tdata->obtain(fw);
    }
    catch (const search_tree<tkey_flyweight, tdata *>::obtaining_of_nonexistent_key_attempt_exception &)
    {
        flyweight_string_singleton::get_singleton()->update();
        throw db_storage::nonexistent_struct_obtaining_attempt_exception();
    }
    
    if (get_singleton()->_mode == ipc::mode::FILE)
    {
        try
        {
            return dynamic_cast<file_tdata *>(data)->deserialize(path);
        }
        catch (std::ios::failure const &)
        {
            throw std::ios::failure("Attempt to read file failed");
        }
    }
    else
    {
        user us = dynamic_cast<ram_tdata *>(data)->_user_data;
        return dynamic_cast<ram_tdata *>(data)->_user_data;
    }

}

std::vector<std::pair<tkey, tvalue>> db_storage::collection::obtain_between(
    const tkey &lower_bound,
    const tkey &upper_bound,
    bool lower_bound_inclusive,
    bool upper_bound_inclusive,
    const std::string &path)
{
    check_if_refresh(path);
    
    tkey_flyweight fw_lower = flyweight_string_singleton::get_singleton()->get_sample(lower_bound);
    tkey_flyweight fw_upper = flyweight_string_singleton::get_singleton()->get_sample(upper_bound);
    
    std::vector<typename associative_container<tkey_flyweight, tdata *>::key_value_pair> data_vec =
            _tdata->obtain_between(fw_lower, fw_upper, lower_bound_inclusive, upper_bound_inclusive);
    
    std::vector<std::pair<tkey, tvalue>> value_vec;
    value_vec.reserve(data_vec.size());
    
    for (auto kvp : data_vec)
    {
        if (get_singleton()->_mode == ipc::mode::FILE)
        {
            try
            {
                value_vec.emplace_back(kvp.key.get()->get_data(), dynamic_cast<file_tdata *>(kvp.value)->deserialize(path));
            }
            catch (std::ios::failure const &)
            {
                throw std::ios::failure("Failed to read data");
            }
        }
        else
        {
            value_vec.emplace_back(kvp.key.get()->get_data(), dynamic_cast<ram_tdata *>(kvp.value)->_user_data);
        }
    }
    
    return value_vec;
}

std::pair<tkey, tvalue> db_storage::collection::obtain_max(
    std::string const &path)
{
    check_if_refresh(path);
    
    tkey key;
    tdata *data = nullptr;
    
    switch (_search_tvar)
    {
        default:
        {
            b_tree<tkey_flyweight, tdata *> *tree = dynamic_cast<b_tree<tkey_flyweight, tdata *> *>(_tdata);
            
            auto iter = tree->rbegin_infix();
            auto iter_end = tree->rend_infix();
            
            if (iter == iter_end)
            {
                throw db_storage::nonexistent_struct_obtaining_attempt_exception();
            }
            
            key = std::get<2>(*iter).get()->get_data();
            data = std::get<3>(*iter);
        }
            
    }
    
    if (get_singleton()->_mode == ipc::mode::FILE)
    {
        try
        {
            return make_pair(key, dynamic_cast<file_tdata *>(data)->deserialize(path));
        }
        catch (std::ios::failure const &)
        {
            throw std::ios::failure("Failed to read data");
        }
    }
    else
    {
        return make_pair(key, dynamic_cast<ram_tdata *>(data)->_user_data);
    }
};

std::pair<tkey, tvalue> db_storage::collection::obtain_next(
    std::string const &path,
        tkey const &key)
{
    check_if_refresh(path);
    
    tkey_flyweight fw_key = flyweight_string_singleton::get_singleton()->get_sample(key);

    tkey next_key;
    tdata *data = nullptr;
    
    switch (_search_tvar)
    {
        default:
        {
            b_tree<tkey_flyweight, tdata *> *tree = dynamic_cast<b_tree<tkey_flyweight, tdata *> *>(_tdata);
            
            auto iter = tree->begin_infix();
            auto iter_end = tree->end_infix();
            
            while (iter != iter_end && fw_key_comparator()(fw_key, std::get<2>(*iter)))
            {
                ++iter;
            }
            
            if (iter == iter_end)
            {
                throw db_storage::nonexistent_struct_obtaining_attempt_exception();
            }
            
            next_key = std::get<2>(*iter).get()->get_data();
            data = std::get<3>(*iter);
            
            if (++iter != iter_end)
            {
                next_key = std::get<2>(*iter).get()->get_data();
                data = std::get<3>(*iter);
            }
            
        }
            
    }
    
    if (get_singleton()->_mode == ipc::mode::FILE)
    {
        try
        {
            return make_pair(next_key, dynamic_cast<file_tdata *>(data)->deserialize(path));
        }
        catch (std::ios::failure const &)
        {
            throw std::ios::failure("Failed to read data");
        }
    }
    else
    {
        return make_pair(next_key, dynamic_cast<ram_tdata *>(data)->_user_data);
    }
};

std::pair<tkey, tvalue> db_storage::collection::obtain_min(
    std::string const &path)
{
    check_if_refresh(path);
    
    tkey key;
    tdata *data = nullptr;
    
    switch (_search_tvar)
    {
        default:
        {
            b_tree<tkey_flyweight, tdata *> *tree = dynamic_cast<b_tree<tkey_flyweight, tdata *> *>(_tdata);
            
            auto iter = tree->begin_infix();
            auto iter_end = tree->end_infix();
            
            if (iter == iter_end)
            {
                throw db_storage::nonexistent_struct_obtaining_attempt_exception();
            }
            
            key = std::get<2>(*iter).get()->get_data();
            data = std::get<3>(*iter);
        }
            
    }
    
    if (get_singleton()->_mode == ipc::mode::FILE)
    {
        try
        {
            return make_pair(key, dynamic_cast<file_tdata *>(data)->deserialize(path));
        }
        catch (std::ios::failure const &)
        {
            throw std::ios::failure("Failed to read data");
        }
    }
    else
    {
        return make_pair(key, dynamic_cast<ram_tdata *>(data)->_user_data);
    }
};

size_t db_storage::collection::get_records_amount()
{
    return _records_amount;
}

    #pragma endregion BASICS

#pragma endregion COLLECTION PROPS IMPLEMENTATION




#pragma region SCHEMA PROPS IMPLEMENTATION


void db_storage::schema::clear()
{
    delete _collections;
    _collections = nullptr;
}

void db_storage::schema::copy_from(
    const schema &other)
{
    switch (_search_tvar = other._search_tvar)
    {
        case ipc::search_tvar::B:
            try
            {
                _collections = new b_tree<tkey_flyweight, collection>(
                    *dynamic_cast<b_tree<tkey_flyweight, collection> *>(other._collections));
            }
            catch (std::bad_alloc const &)
            {
                throw;
            }
        default:
            break;
    }
}

void db_storage::schema::move_from(
    schema &&other)
{
    switch (_search_tvar = other._search_tvar)
    {
        case ipc::search_tvar::B:
            try
            {
                _collections = new b_tree<tkey_flyweight, collection>(
                    std::move(*dynamic_cast<b_tree<tkey_flyweight, collection> *>(other._collections)));
            }
            catch (std::bad_alloc const &)
            {
                throw;
            }
        default:
            break;
    }
    
    other._collections = nullptr;
}	


db_storage::schema::~schema()
{
    clear();
}

db_storage::schema::schema(
    const db_storage::schema &other)
{
    copy_from(other);
}

db_storage::schema &db_storage::schema::operator=(
    const db_storage::schema &other)
{
    if (this != &other)
    {
        clear();
        copy_from(other);
    }
    
    return *this;
}

db_storage::schema::schema(
    db_storage::schema &&other) noexcept
{
    move_from(std::move(other));
}

db_storage::schema &db_storage::schema::operator=(
    db_storage::schema &&other) noexcept
{
    if (this != &other)
    {
        clear();
        move_from(std::move(other));
    }
    
    return *this;
}


db_storage::schema::schema (
    ipc::search_tvar search_tvar,
    size_t param_for_tree) :
        _search_tvar(search_tvar)
        //_records_amount(0)
{
    try
    {
        switch (search_tvar)
        {
            case ipc::search_tvar::B:
                _collections = new b_tree<tkey_flyweight, collection>(
                    param_for_tree,
                    db_storage::fw_key_comparator());
                break;

            default:
                break;
        }
    }
    catch (const std::bad_alloc &)
    {
        delete _collections;
        throw;
    }
}

void db_storage::schema::add_to_inner (
    const std::string &collection_name,
    ipc::search_tvar search_tvar,
    ipc::allocator_var allocator_var,
    allocator_with_fit_mode::fit_mode fit_mode,
    size_t param_for_tree)
{

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(collection_name);

    try
    {   
        _collections->insert(fw, collection(search_tvar, allocator_var, fit_mode, param_for_tree));
    }
    catch (const search_tree<tkey_flyweight, collection>::insertion_of_existent_key_attempt_exception_exception &)
    {
        throw db_storage::existent_struct_insertion_attempt_exception();
    }
    
}

void db_storage::schema::dispose_from_inner (
    const std::string &collection_name)
{

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(collection_name);

    try
    {
        _collections->dispose(fw);
    }
    catch (const search_tree<tkey_flyweight, collection>::disposal_of_nonexistent_key_attempt_exception &)
    {
        flyweight_string_singleton::get_singleton()->update();
        throw db_storage::nonexistent_struct_disposal_attempt_exception();
    }

} 

db_storage::collection &db_storage::schema::obtain_from_inner (
    const std::string &collection_name)
{   
    
    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(collection_name);

    try
    {
        return const_cast<collection &>(_collections->obtain(fw));
    }
    catch (const search_tree<tkey_flyweight, collection>::obtaining_of_nonexistent_key_attempt_exception &)
    {
        flyweight_string_singleton::get_singleton()->update();
        throw db_storage::nonexistent_struct_obtaining_attempt_exception();
    }

}

#pragma endregion SCHEMA PROPS IMPLEMENTATION




#pragma region POOL PROPS IMPLEMENTATION


void db_storage::pool::clear()
{
    delete _schemas;
    _schemas = nullptr;
}

void db_storage::pool::copy_from(
    const db_storage::pool &other)
{
    switch (_search_tvar = other._search_tvar)
    {
        case ipc::search_tvar::B:
            try
            {
                _schemas = new b_tree<tkey_flyweight , schema>(
                    *dynamic_cast<b_tree<tkey_flyweight, schema> *>(other._schemas));
            }
            catch (std::bad_alloc const &)
            {
                throw;
            }
        default:
            break;
    }
}

void db_storage::pool::move_from(
    db_storage::pool &&other)
{
    switch (_search_tvar = other._search_tvar)
    {
        case ipc::search_tvar::B:
            try
            {
                _schemas = new b_tree<tkey_flyweight, schema>(
                    std::move(*dynamic_cast<b_tree<tkey_flyweight, schema> *>(other._schemas)));
            }
            catch (std::bad_alloc const &)
            {
                throw;
            }
        default:
            break;
    }
    
    other._schemas = nullptr;
}


db_storage::pool::~pool()
{
    clear();
}

db_storage::pool::pool(
    const pool &other)
{
    copy_from(other);
}

db_storage::pool &db_storage::pool::operator=(
    const db_storage::pool &other)
{
    if (this != &other)
    {
        clear();
        copy_from(other);
    }
    
    return *this;
}

db_storage::pool::pool(
    db_storage::pool &&other) noexcept
{
    move_from(std::move(other));
}

db_storage::pool &db_storage::pool::operator=(
    db_storage::pool &&other) noexcept
{
    if (this != &other)
    {
        clear();
        move_from(std::move(other));
    }
    
    return *this;
}


db_storage::pool::pool (
    ipc::search_tvar search_tvar,
    size_t param_for_tree) :
    _search_tvar(search_tvar)
{
    //switch (search_tvar)
    //{
    //case ipc::search_tvar::B:
    //    try
    //    {
    //        _schemas = new b_tree<tkey_flyweight, schema>(
    //            param_for_tree,
    //            db_storage::fw_key_comparator());
    //    }
    //    catch (const std::bad_alloc &e)
    //    {
    //        throw e;
    //    }
    //default:
    //    break;
    //}

    switch (search_tvar)
    {
    case ipc::search_tvar::B:
        //break;
    case ipc::search_tvar::B_PLUS:
        //break;
    case ipc::search_tvar::B_STAR:
        //break;
    case ipc::search_tvar::B_STAR_PLUS:
        //break;
    default:
        try
        {
            _schemas = new b_tree<tkey_flyweight, schema>(param_for_tree, db_storage::fw_key_comparator());
        }
        catch (std::bad_alloc const &)
        {
            // TODO LOG
            throw;
        }
        break;
    }

}

void db_storage::pool::add_to_inner (
    const std::string &schema_name,
    ipc::search_tvar search_tvar,
    size_t param_for_tree)
{

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(schema_name);

    try
    {
        _schemas->insert(fw, schema(search_tvar, param_for_tree));        
    }
    catch (const search_tree<tkey_flyweight, schema>::insertion_of_existent_key_attempt_exception_exception &)
    {
        throw db_storage::existent_struct_insertion_attempt_exception();
    }

}

void db_storage::pool::dispose_from_inner (
    const std::string &schema_name)
{

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(schema_name);

    try
    {
        _schemas->dispose(fw);
    }
    catch (const search_tree<tkey_flyweight, schema>::disposal_of_nonexistent_key_attempt_exception &)
    {
        flyweight_string_singleton::get_singleton()->update();
        throw db_storage::nonexistent_struct_disposal_attempt_exception();
    }

}

db_storage::schema &db_storage::pool::obtain_from_inner (
    const std::string &schema_name)
{
    
    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(schema_name);

    try
    {
        return const_cast<schema &>(_schemas->obtain(fw));
    }
    catch (const search_tree<tkey_flyweight, schema>::obtaining_of_nonexistent_key_attempt_exception &)
    {
        flyweight_string_singleton::get_singleton()->update();
        throw db_storage::nonexistent_struct_obtaining_attempt_exception();
    }

}

#pragma endregion POOL PROPS IMPLEMENTATION




#pragma region DB_MANAGER PROPS IMPLEMENTATION


#pragma region BASIC PROPS IMPLEMENTATION

size_t db_storage::get_id () const noexcept
{
    return _id;
}

db_storage *db_storage::setup (
    size_t id,
    ipc::mode mode)
{   
    throw_if_init()
        .throw_if_invalid_params(id, mode);

    _id = id;
    _mode = mode;

    return this;
}

db_storage *db_storage::clear()
{
    if (get_singleton()->_mode == ipc::mode::RAM)
    {
        return this;
    }
    
    if (_access("pools", 0) == -1)
    {
        return this;
    }
    
    for (auto const &pool_entry : std::filesystem::directory_iterator("pools"))
    {
        if (!std::filesystem::is_directory(pool_entry)) continue;
        
        std::string pool_name = pool_entry.path().string();
        std::string pool_cfg_path = DC_utilities::make_path({"pools", pool_name, "cfg"});
        
        if (_access(pool_cfg_path.c_str(), 0) == -1) continue;
        
        for (auto const &schema_entry : std::filesystem::directory_iterator(DC_utilities::make_path({"pools", pool_name})))
        {
            if (!std::filesystem::is_directory(schema_entry)) continue;
            
            std::string schema_name = schema_entry.path().string();
            std::string schema_cfg_path = DC_utilities::make_path({"pools", pool_name, schema_name, "cfg"});
            
            if (_access(schema_cfg_path.c_str(), 0) == -1) continue;
            
            for (auto const &collection_entry : std::filesystem::directory_iterator(DC_utilities::make_path({"pools", pool_name, schema_name})))
            {
                if (!std::filesystem::is_directory(collection_entry)) continue;
                
                std::string collection_name = collection_entry.path().string();
                std::string collection_cfg_path = DC_utilities::make_path({"pools", pool_name, schema_name, collection_name, "cfg"});
            
                if (_access(collection_cfg_path.c_str(), 0) == -1) continue;
                
                for (auto const &table_entry : std::filesystem::directory_iterator(DC_utilities::make_path({"pools", pool_name, schema_name, collection_name})))
                {
                    if (std::filesystem::is_directory(table_entry)) continue;
                    
                    if (table_entry.path().string() == std::to_string(get_singleton()->_id))
                    {
                        remove(table_entry.path().filename());
                    }
                }
            }
        }
    }
    
    return this;
}

void db_storage::add_to_inner (
    const std::string &pool_name,
    ipc::search_tvar search_tvar,
    size_t param_for_tree)
{

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(pool_name);

    try
    {
        pool pool(search_tvar, param_for_tree);
        _pools.insert(fw, pool);
    }
    catch (const search_tree<tkey_flyweight, pool>::insertion_of_existent_key_attempt_exception_exception &)
    {
        throw db_storage::existent_struct_insertion_attempt_exception();
    }
    

}

void db_storage::dispose_from_inner (
    const std::string &pool_name)
{
    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(pool_name);

    try
    {
        _pools.dispose(fw);
    }
    catch (const db_storage::nonexistent_struct_disposal_attempt_exception &)
    {
        flyweight_string_singleton::get_singleton()->update();
        throw db_storage::nonexistent_struct_disposal_attempt_exception();
    }
    

}

db_storage::pool &db_storage::obtain_from_inner (
    const std::string &pool_name)
{
    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(pool_name);

    try
    {
        return const_cast<pool &>(_pools.obtain(fw));
    }
    catch (const db_storage::nonexistent_struct_obtaining_attempt_exception &)
    {
        flyweight_string_singleton::get_singleton()->update();
        throw db_storage::nonexistent_struct_obtaining_attempt_exception();
    }

}

#pragma endregion BASIC PROPS IMPLEMENTATION



#pragma region SINGLETON PROPS IMPLEMENTATION

db_storage::db_storage () :
    _id(0),
    _mode(ipc::mode::UNINITIALIZED),
    _pools(8, db_storage::fw_key_comparator())
{   }

db_storage *db_storage::get_singleton ()
{
    static db_storage *singleton = new db_storage();
    return singleton;
}

#pragma endregion SINGLETON PROPS IMPLEMENTATION



#pragma region RAM BASIC INTERFACE IMPLEMENTATION

db_storage *db_storage::add_pool (
    const std::string &pool_name,
    ipc::search_tvar search_tvar,
    size_t param_for_tree)
{

    std::string path = DC_utilities::make_path({"pools", pool_name});

    throw_if_uninit()
        .throw_if_path_too_long(path)
        .throw_if_invalid_file_name(pool_name)
        .add_to_inner(pool_name, search_tvar, param_for_tree);

    if (get_singleton()->_mode == ipc::mode::FILE)
    {

        std::string config_path = DC_utilities::make_path({path, "_cfg"});

        if (_access(path.c_str(), 0) == -1 || _access(config_path.c_str(), 0) == -1)
        {
            try
            {
                std::filesystem::create_directories(path.c_str());

                std::ofstream stream(config_path);

                if (!stream.is_open())
                {
                    throw std::ios::failure("Failed to open the configuration file.");
                }

                stream << static_cast<int>(search_tvar) << std::endl;
                stream << param_for_tree << std::endl;

                stream.flush();

                if (stream.fail())
                {
                    throw std::ios::failure("Failed to write the configuration file");
                }
            }
            catch (std::ios::failure const &)
            {
                remove(config_path.c_str());
                rmdir(path.c_str());
                dispose_from_inner(path);

                throw db_storage::insertion_failure();
            }
        }
        
    }

    return this;

    }

db_storage *db_storage::dispose_pool (
    const std::string &pool_name)
{
    throw_if_uninit()
        .dispose_from_inner(pool_name);

    std::string path = DC_utilities::make_path({"pools", pool_name});

    std::filesystem::remove_all(path);

    return this;
    
}

db_storage *db_storage::add_schema (
    const std::string &pool_name,
    const std::string &schema_name,
    ipc::search_tvar search_tvar,
    size_t param_for_tree)
{

    std::string prev_path = DC_utilities::make_path({"pools", pool_name});
    std::string path = DC_utilities::make_path({"pools", pool_name, schema_name});

    pool &pool = throw_if_uninit()
        .throw_if_invalid_path(prev_path)
        .throw_if_invalid_file_name(schema_name)
        .throw_if_path_too_long(path)
        .obtain_from_inner(pool_name);
    
    pool.add_to_inner(
            schema_name,
            search_tvar,
            param_for_tree);
        
    if (get_singleton()->_mode == ipc::mode::FILE)
    {
        std::string config_path = DC_utilities::make_path({path, "cfg"});
        
        if (_access(path.c_str(), 0) == -1 || _access(config_path.c_str(), 0) == -1)
        {
            try
            {

                mkdir(path.c_str());

                std::ofstream stream(config_path);

                if (!stream.is_open())
                {
                    throw std::ios::failure("Failed to open the configuration file.");
                }

                stream << static_cast<int>(search_tvar) << std::endl;
                stream << param_for_tree << std::endl;

                stream.flush();

                if (stream.fail())
                {
                    throw std::ios::failure("Failed to write the configuration file");
                }
            }
            catch (std::ios::failure const &)
            {
                remove(config_path.c_str());
                rmdir(path.c_str());
                dispose_from_inner(path);
                
                throw db_storage::insertion_failure();
            }
        }
    }
    
    return this;

}

db_storage *db_storage::dispose_schema (
    const std::string &pool_name,
    const std::string &schema_name)
{
    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .dispose_from_inner(schema_name);

    std::string path = DC_utilities::make_path({"pools", pool_name, schema_name});
    
    std::filesystem::remove_all(path);
    
    return this;
    
}

db_storage *db_storage::add_collection (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    ipc::search_tvar search_tvar,
    ipc::allocator_var allocator_var,
    allocator_with_fit_mode::fit_mode fit_mode,
    size_t param_for_tree)
{

    std::string prev_path = DC_utilities::make_path({"pools", pool_name, schema_name});
    std::string path = DC_utilities::make_path({"pools", pool_name, schema_name, collection_name});

    schema &sample = throw_if_uninit()
        .throw_if_invalid_path(prev_path)
        .throw_if_invalid_file_name(collection_name)
        .throw_if_path_too_long(path)
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name);
        
    sample.add_to_inner(collection_name, search_tvar, allocator_var, fit_mode, param_for_tree);

    if (get_singleton()->_mode == ipc::mode::FILE)
    {
        std::string config_path = DC_utilities::make_path({path, "cfg"});
        std::string storage_path = DC_utilities::make_path({path, std::to_string(_id)});
        
        if (_access(path.c_str(), 0) == -1 || _access(config_path.c_str(), 0) == -1 ||
                _access(storage_path.c_str(), 0) == -1)
        {
            try
            {
                mkdir(path.c_str());
                
                std::ofstream storage_stream(storage_path.c_str());
                storage_stream.close();
                
                if (_access(storage_path.c_str(), 0) == -1)
                {
                    throw std::ios::failure("Failed to create the storage file");
                }
                
                std::ofstream stream(config_path);
                if (!stream.is_open())
                {
                    throw std::ios::failure("Failed to open the configuration file");
                }
                
                stream << static_cast<int>(search_tvar) << std::endl;
                stream << static_cast<int>(allocator_var) << std::endl;
                stream << static_cast<int>(fit_mode) << std::endl;
                stream << param_for_tree << std::endl;

                stream.flush();
                
                if (stream.fail())
                {
                    throw std::ios::failure("Failed to write the configuration file");
                }
            }
            catch (std::ios::failure const &)
            {
                remove(storage_path.c_str());
                remove(config_path.c_str());
                rmdir(path.c_str());
                sample.dispose_from_inner(collection_name);
                
                throw db_storage::insertion_failure();
            }
        }
    }

    return this;

}

db_storage *db_storage::dispose_collection (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name)
{

    std::string path = DC_utilities::make_path({"pools", pool_name, schema_name, collection_name});

    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .dispose_from_inner(collection_name);

    std::filesystem::remove_all(path);

    return this;

}


db_storage *db_storage::add_user_data (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    const std::string &user_name,
    const user &user)
{

    std::string path = DC_utilities::make_path(
        {"pools", pool_name, schema_name, collection_name, std::to_string(_id)});

    collection &collection = throw_if_uninit()
        .throw_if_invalid_path(path)
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name);
        
    collection.add_to_inner(user_name, user, path);

    //TODO FILE

    return this;

}

db_storage *db_storage::add_user_data (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    const std::string &user_name,
    const user &&user)
{

    std::string path = DC_utilities::make_path(
        {"pools", pool_name, schema_name, collection_name, std::to_string(_id)});

    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .add_to_inner(user_name, std::move(user), path);

    return this;

}


db_storage *db_storage::udpdate_user_data (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    const std::string &user_name,
    const user &user)
{

    std::string path = DC_utilities::make_path(
        {"pools", pool_name, schema_name, collection_name, std::to_string(_id)});

    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .update_inner(user_name, user, path);

    return this;
}

db_storage *db_storage::udpdate_user_data (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    const std::string &user_name,
    const user &&user)
{

    std::string path = DC_utilities::make_path(
        {"pools", pool_name, schema_name, collection_name, std::to_string(_id)});

    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .update_inner(user_name, std::move(user), path);

    return this;

};

user db_storage::dispose_user_data (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    const std::string &user_name)
{

    std::string path = DC_utilities::make_path(
        {"pools", pool_name, schema_name, collection_name, std::to_string(_id)});

    return throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .dispose_from_inner(user_name, path);

};

user db_storage::obtain_user_data (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    const std::string &user_name)
{

    std::string path = DC_utilities::make_path(
        {"pools", pool_name, schema_name, collection_name, std::to_string(_id)});

    return throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .obtain_from_inner(user_name, path);

}


std::vector<std::pair<tkey, tvalue>> db_storage::obtain_between(
	const std::string &pool_name,
	const std::string &schema_name,
	const std::string &collection_name,
    const tkey &lower_bound,
    const tkey &upper_bound,
    bool lower_bound_inclusive,
    bool upper_bound_inclusive)
{
    
    std::string path = DC_utilities::make_path(
        {"pools", pool_name, schema_name, collection_name, std::to_string(_id)});

    return throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .obtain_between(lower_bound, upper_bound, lower_bound_inclusive, upper_bound_inclusive, path);

};


std::pair<tkey, tvalue> db_storage::obtain_min_user(
	const std::string &pool_name,
	const std::string &schema_name,
	const std::string &collection_name)
{

    std::string path = DC_utilities::make_path(
        {"pools", pool_name, schema_name, collection_name, std::to_string(_id)});

    return throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .obtain_min(path);

};
	
std::pair<tkey, tvalue> db_storage::obtain_max_user(
	const std::string &pool_name,
	const std::string &schema_name,
	const std::string &collection_name)
{

    std::string path = DC_utilities::make_path(
        {"pools", pool_name, schema_name, collection_name, std::to_string(_id)});

    return throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .obtain_max(path);

};
	
std::pair<tkey, tvalue> db_storage::obtain_next_user(
	const std::string &pool_name,
	const std::string &schema_name,
	const std::string &collection_name,
	const tkey &user_name)
{

    std::string path = DC_utilities::make_path(
        {"pools", pool_name, schema_name, collection_name, std::to_string(_id)});

    return throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .obtain_next(path, user_name);

};



#pragma endregion RAM BASIC INTERFACE IMPLEMENTATION


#pragma endregion DB_MANAGER PROPS IMPLEMENTATION
