
#include <inner_architecture.h>





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

#pragma endregion ERRORS




#pragma region THROWS

db_storage &db_storage::throw_if_init ()
{
    if (_mode == mode::UNINITIALIZED)
    {   
        return *this;
    }

    throw db_storage::setup_fault ("Mode re-initialization is prohibited.");
}

db_storage &db_storage::throw_if_uninit ()
{
    if (_mode != mode::UNINITIALIZED)
    {
        return *this;
    }

    throw db_storage::setup_fault ("None of the operations can be carryed out without mode initialization.");
}

db_storage &db_storage::throw_if_invalid_params (
    size_t id,
    mode mode)
{
    if (mode != mode::UNINITIALIZED && id != 0)
    {
        return *this;
    }

    throw db_storage::setup_fault("Passed parameters are invalid.");
}


#pragma endregion THROWS




#pragma region TDATA

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
        case search_tvar::B:
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
        case search_tvar::B:
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




db_storage::collection::collection (
    db_storage::search_tvar search_tvar,
    db_storage::allocator_var allocator_var,
    allocator_with_fit_mode::fit_mode fit_mode,
    size_t param_for_tree) :
        _search_tvar(search_tvar),
        _fit_mode(fit_mode),
        _allocator_var(allocator_var),
        _records_amount(0)
{
    switch (search_tvar)
    {
        case search_tvar::B:
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
            case allocator_var::GLOBAL_HEAP:
               _allocator = std::make_shared<allocator_global_heap>();
               break;

            case allocator_var::BOUNDARY_TAGS:
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
    const user &user)
{

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(user_name);
    tdata *data = nullptr;

    try
    {
        if (get_singleton()->_mode == mode::RAM)
        {
            data = reinterpret_cast<ram_tdata *>(allocate_with_guard(sizeof(tdata), 1));
            allocator::construct(reinterpret_cast<ram_tdata *>(data), user);
        }
        else if (get_singleton()->_mode == mode::FILE)
        {
            //TODO
        }
    }
    catch (const std::bad_alloc &)
    {
        deallocate_with_guard(data);
        throw;
    }
    
    try
    {
        if (get_singleton()->_mode == mode::FILE)
        {
            //TODO
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

    ++_records_amount;

}

void db_storage::collection::add_to_inner (
    const std::string &user_name,
    const user &&user)
{
    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(user_name);
    tdata *data = nullptr;

    try
    {
        if (get_singleton()->_mode == mode::RAM)
        {
            data = reinterpret_cast<ram_tdata *>(allocate_with_guard(sizeof(tdata), 1));
            allocator::construct(reinterpret_cast<ram_tdata *>(data), std::move(user));
        }
        else if (get_singleton()->_mode == mode::FILE)
        {
            //TODO
        }
    }
    catch (const std::bad_alloc &)
    {
        deallocate_with_guard(data);
        throw;
    }
    
    try
    {
        if (get_singleton()->_mode == mode::FILE)
        {
            //TODO
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

    ++_records_amount;
}

void db_storage::collection::update_inner (
    const std::string &user_name,
    const user &user)
{
    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(user_name);
    tdata *data = nullptr;
    
    try
    {
        if (get_singleton()->_mode == mode::RAM)
        {
            data = reinterpret_cast<ram_tdata *>(allocate_with_guard(sizeof(ram_tdata), 1));
            allocator::construct(reinterpret_cast<ram_tdata *>(data), user);
            
        }
        else
        {
            //data = reinterpret_cast<file_tdata *>(allocate_with_guard(sizeof(file_tdata), 1));
            //allocator::construct(reinterpret_cast<file_tdata *>(data));
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
        if (get_singleton()->_mode == mode::FILE)
        {
            //TODO
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
    const user &&user)
{
    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(user_name);
    tdata *data = nullptr;
    
    try
    {
        if (get_singleton()->_mode == mode::RAM)
        {
            data = reinterpret_cast<ram_tdata *>(allocate_with_guard(sizeof(ram_tdata), 1));
            allocator::construct(reinterpret_cast<ram_tdata *>(data), std::move(user));
            
        }
        else
        {
            //data = reinterpret_cast<file_tdata *>(allocate_with_guard(sizeof(file_tdata), 1));
            //allocator::construct(reinterpret_cast<file_tdata *>(data));
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
        if (get_singleton()->_mode == mode::FILE)
        {
            //TODO
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
    const std::string &user_name)
{

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(user_name);

    tdata *data = nullptr;

    try
    {
        data = _tdata->dispose(fw);
    }
    catch (const search_tree<tkey_flyweight, tdata *>::disposal_of_nonexistent_key_attempt_exception &)
    {
        flyweight_string_singleton::get_singleton()->update();
        throw db_storage::nonexistent_struct_disposal_attempt_exception();
    }
    if (get_singleton()->_mode == mode::FILE)
    {
        //TODO
    }

    _records_amount--;

    return dynamic_cast<ram_tdata *>(data)->get_user_data();

} 

user db_storage::collection::obtain_from_inner (
    const std::string &user_name)
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
    
    if (get_singleton()->_mode == mode::FILE)
    {
        //TODO
    }
    else
    {
        return (dynamic_cast<ram_tdata *>(data))->get_user_data();
    }

}

std::vector<std::pair<tkey, tvalue>> db_storage::collection::obtain_between(
    tkey const &lower_bound,
    tkey const &upper_bound,
    bool lower_bound_inclusive,
    bool upper_bound_inclusive,
    std::string const &path)
{
    //collect_garbage(path);
    
    tkey_flyweight fw_lower = flyweight_string_singleton::get_singleton()->get_sample(lower_bound);
    tkey_flyweight fw_upper = flyweight_string_singleton::get_singleton()->get_sample(upper_bound);
    
    std::vector<typename associative_container<tkey_flyweight, tdata *>::key_value_pair> data_vec =
            _tdata->obtain_between(fw_lower, fw_upper, lower_bound_inclusive, upper_bound_inclusive);
    
    std::vector<std::pair<tkey, tvalue>> value_vec;
    value_vec.reserve(data_vec.size());
    
    for (auto kvp : data_vec)
    {
        if (get_singleton()->_mode == mode::RAM)
        {
            value_vec.emplace_back(kvp.key.get()->get_data(), dynamic_cast<ram_tdata *>(kvp.value)->get_user_data());
            
        }
        else
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
    }
    
    return value_vec;
}

std::pair<tkey, tvalue> db_storage::collection::obtain_max(
    std::string const &path)
{
    //collect_garbage(path);
    
    tkey key;
    tdata *data = nullptr;
    
    switch (_search_tvar)
    {
        default:
        {
            b_tree<tkey, tdata *> *tree = dynamic_cast<b_tree<tkey, tdata *> *>(_tdata);
            
            auto iter = tree->rbegin_infix();
            auto iter_end = tree->rend_infix();
            
            if (iter == iter_end)
            {
                throw db_storage::nonexistent_struct_obtaining_attempt_exception();
            }
            
            key = std::get<2>(*iter);
            data = std::get<3>(*iter);
        }
            
    }
    
    if (get_singleton()->_mode == mode::FILE)
    {
        //try
        //{
        //    return make_pair(key, dynamic_cast<file_tdata *>(data)->deserialize(path));
        //}
        //catch (std::ios::failure const &)
        //{
        //    throw std::ios::failure("Failed to read data");
        //}
    }
    else
    {
        return make_pair(key, dynamic_cast<ram_tdata *>(data)->get_user_data());
    }
};

std::pair<tkey, tvalue> db_storage::collection::obtain_next(
    std::string const &path,
    tkey const &key)
{
    //collect_garbage(path);
    
    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(key);
    tkey_flyweight next_key;
    
    tdata *data = nullptr;
    
    switch (_search_tvar)
    {
        default:
        {
            b_tree<tkey_flyweight, tdata *> *tree = dynamic_cast<b_tree<tkey_flyweight, tdata *> *>(_tdata);
            
            auto iter = tree->begin_infix();
            auto iter_end = tree->end_infix();
            
            while (iter != iter_end && fw_key_comparator()(fw, std::get<2>(*iter)))
            {
                ++iter;
            }
            
            if (iter == iter_end)
            {
                throw db_storage::nonexistent_struct_obtaining_attempt_exception();
            }
            
            next_key = std::get<2>(*iter);
            data = std::get<3>(*iter);
            
            if (++iter != iter_end)
            {
                next_key = std::get<2>(*iter);
                data = std::get<3>(*iter);
            }
            
        }
            
    }
    
    if (get_singleton()->_mode == mode::FILE)
    {
        //try
        //{
        //    return make_pair(next_key, dynamic_cast<file_tdata *>(data)->deserialize(path));
        //}
        //catch (std::ios::failure const &)
        //{
        //    throw std::ios::failure("Failed to read data");
        //}
    }
    else
    {
        return make_pair(next_key->get_data(), dynamic_cast<ram_tdata *>(data)->get_user_data());
    }
};

std::pair<tkey, tvalue> db_storage::collection::obtain_min(
    std::string const &path)
{
    //collect_garbage(path);
    
    tkey key;
    tdata *data = nullptr;
    
    switch (_search_tvar)
    {
        default:
        {
            b_tree<tkey, tdata *> *tree = dynamic_cast<b_tree<tkey, tdata *> *>(_tdata);
            
            auto iter = tree->begin_infix();
            auto iter_end = tree->end_infix();
            
            if (iter == iter_end)
            {
                throw db_storage::nonexistent_struct_obtaining_attempt_exception();
            }
            
            key = std::get<2>(*iter);
            data = std::get<3>(*iter);
        }
            
    }
    
    if (get_singleton()->_mode == mode::FILE)
    {
        //try
        //{
        //    return make_pair(key, dynamic_cast<file_tdata *>(data)->deserialize(path));
        //}
        //catch (std::ios::failure const &)
        //{
        //    throw std::ios::failure("Failed to read data");
        //}
    }
    else
    {
        return make_pair(key, dynamic_cast<ram_tdata *>(data)->get_user_data());
    }
};

size_t db_storage::collection::get_records_amount()
{
    return _records_amount;
}


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
        case search_tvar::B:
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
        case search_tvar::B:
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
    db_storage::search_tvar search_tvar,
    size_t param_for_tree) :
        _search_tvar(search_tvar),
        _records_amount(0)
{
    try
    {
        switch (search_tvar)
        {
            case search_tvar::B:
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
    db_storage::search_tvar search_tvar,
    db_storage::allocator_var allocator_var,
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
        return _collections->obtain(fw);
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
        case search_tvar::B:
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
        case search_tvar::B:
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
    db_storage::search_tvar search_tvar,
    size_t param_for_tree)
{
    switch (search_tvar)
    {
    case db_storage::search_tvar::B:
        try
        {
            _schemas = new b_tree<tkey_flyweight, schema>(
                param_for_tree,
                db_storage::fw_key_comparator());
        }
        catch (const std::bad_alloc &e)
        {
            throw e;
        }
    default:
        break;
    }
}

void db_storage::pool::add_to_inner (
    const std::string &schema_name,
    db_storage::search_tvar search_tvar,
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
        return _schemas->obtain(fw);
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
    db_storage::mode mode)
{   
    throw_if_init()
        .throw_if_invalid_params(id, mode);

    _id = id;
    _mode = mode;

    return this;
}

void db_storage::add_to_inner (
    const std::string &pool_name,
    db_storage::search_tvar search_tvar,
    size_t param_for_tree)
{

    tkey_flyweight fw = flyweight_string_singleton::get_singleton()->get_sample(pool_name);

    try
    {
        _pools.insert(fw, pool(search_tvar, param_for_tree));
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
        return _pools.obtain(fw);
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
    _mode(mode::UNINITIALIZED),
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
    db_storage::search_tvar search_tvar,
    size_t param_for_tree)
{

    std::string path = DC_utilities::make_path({"pools", pool_name});

    throw_if_uninit()
        .add_to_inner(pool_name, search_tvar, param_for_tree);

    return this;

}

db_storage *db_storage::dispose_pool (
    const std::string &pool_name)
{
    throw_if_uninit()
        .dispose_from_inner(pool_name);

    return this;
    
}

db_storage *db_storage::add_schema (
    const std::string &pool_name,
    const std::string &schema_name,
    db_storage::search_tvar search_tvar,
    size_t param_for_tree)
{

    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .add_to_inner(
            schema_name,
            search_tvar,
            param_for_tree);
        

    return this;

}

db_storage *db_storage::dispose_schema (
    const std::string &pool_name,
    const std::string &schema_name)
{
    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .dispose_from_inner(schema_name);

    return this;
    
}

db_storage *db_storage::add_collection (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    db_storage::search_tvar search_tvar,
    db_storage::allocator_var allocator_var,
    allocator_with_fit_mode::fit_mode fit_mode,
    size_t param_for_tree)
{

    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .add_to_inner(collection_name, search_tvar, allocator_var, fit_mode, param_for_tree);

    //TODOFILE

    return this;

}

db_storage *db_storage::dispose_collection (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name)
{

    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .dispose_from_inner(collection_name);

    //TODOFILE

    return this;

}


db_storage *db_storage::add_user_data (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    const std::string &user_name,
    const user &user)
{

    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .add_to_inner(user_name, user);

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

    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .add_to_inner(user_name, std::move(user));

    return this;

}


db_storage *db_storage::udpdate_user_data (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    const std::string &user_name,
    const user &user)
{
    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .update_inner(user_name, user);

    return this;
}

db_storage *db_storage::udpdate_user_data (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    const std::string &user_name,
    const user &&user)
{
    throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .update_inner(user_name, std::move(user));

    return this;

};

user db_storage::dispose_user_data (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    const std::string &user_name)
{

    return throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .dispose_from_inner(user_name);

};

user db_storage::obtain_user_data (
    const std::string &pool_name,
    const std::string &schema_name,
    const std::string &collection_name,
    const std::string &user_name)
{

    return throw_if_uninit()
        .obtain_from_inner(pool_name)
        .obtain_from_inner(schema_name)
        .obtain_from_inner(collection_name)
        .obtain_from_inner(user_name);

}



#pragma endregion RAM BASIC INTERFACE IMPLEMENTATION


#pragma endregion DB_MANAGER PROPS IMPLEMENTATION
