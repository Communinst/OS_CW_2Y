

//#ifndef __has_include
//  static_assert(false, "__has_include not supported");
//#else
//#  if __cplusplus >= 201703L && __has_include(<filesystem>)
//#    include <filesystem>
//     namespace fs = std::filesystem;
//#  elif __has_include(<experimental/filesystem>)
//#    include <experimental/filesystem>
//     namespace fs = std::experimental::filesystem;
//#  elif __has_include(<boost/filesystem.hpp>)
//#    include <boost/filesystem.hpp>
//     namespace fs = boost::filesystem;
//#  endif
//#endif


#ifndef OPERATING_SYSTEMS_COURSE_WORK_INNER_ARCHITECTURE_H
#define OPERATING_SYSTEMS_COURSE_WORK_INNER_ARCHITECTURE_H

#include "../../relevant_type/include/user.h"
#include "../../associative_container/search_tree/include/search_tree.h"
#include "../../associative_container/search_tree/indexing_tree/b_tree/include/b_tree.h"
#include "../../allocator/allocator/include/allocator.h"
#include "../../allocator/allocator/include/allocator_with_fit_mode.h"
#include "../../logger/logger/include/logger.h"
#include "../../DC_utilities/include/dc_utilities.h"
#include "../../IPC/include/ipc.h"

#include "../../allocator/allocator_global_heap/include/allocator_global_heap.h"
#include "../../allocator/allocator_boundary_tags/include/allocator_boundary_tags.h"





using tkey = std::string;
using tvalue = user;
using tkey_flyweight = std::shared_ptr<flyweight_string>;



//TODO
//1. Cover with error handling classes;
//2. Cover singleton with b_tree; 


class db_storage final //:
    //public logger_guardant,
    //public allocator_guardant
{




#pragma region TKEY TOOLS


//Higher attention if sharedptr will crush

private:

    class fw_key_comparator final 
    {

    public:

        int operator() (
            const tkey_flyweight first,
            const tkey_flyweight second);

    };


#pragma endregion TKEY TOOLS




#pragma region ERRORS

public:

    class setup_fault final :
        public std::logic_error
    {

    public:

        setup_fault(
            const std::string& mes);

    };

    class existent_struct_insertion_attempt_exception final :
        public std::logic_error
    {

    public:

        existent_struct_insertion_attempt_exception ();

    };

    class nonexistent_struct_disposal_attempt_exception final :
        public std::logic_error
    {

    public:

        nonexistent_struct_disposal_attempt_exception ();

    };

    class nonexistent_struct_obtaining_attempt_exception final :
        public std::logic_error
    {

    public:

        nonexistent_struct_obtaining_attempt_exception ();

    };

    class nonesixtent_struct_updating_attempt_exception final :
        public std::logic_error
    {

        public:

            nonesixtent_struct_updating_attempt_exception ();

    };

    class nonexistent_file_path_hit_attempt_exception final :
        public std::logic_error
    {

        public:

            nonexistent_file_path_hit_attempt_exception ();

    };

    class invalid_path_exception final :
        public std::logic_error
    {

        public:

            invalid_path_exception ();

    };

    class path_length_exception final :
        public std::logic_error
    {

        public:

            path_length_exception (
                const std::string op);

    };

    class invalid_name_exception final :
        public std::logic_error
    {

        public:

            invalid_name_exception (
                const std::string name,
                const std::string of);

    };


    class insertion_failure final :
        public std::logic_error
    {

        public:

            insertion_failure ();

    };



#pragma endregion ERRORS




#pragma region THROWS

public:

db_storage &throw_if_init ();
db_storage &throw_if_uninit ();

db_storage &throw_if_invalid_params (
    size_t id,
    ipc::mode mode);

db_storage &throw_if_invalid_path (
    const std::string path);

db_storage &throw_if_invalid_file_name (
    const std::string path);

db_storage &throw_if_path_too_long (
    const std::string path);

#pragma endregion THROWS




#pragma region TDATA

class tdata 
{

public:

   virtual ~tdata() = default;

};

class ram_tdata final :
    public tdata
{

public:

    user _user_data;

public:

    ram_tdata (
        const user &user_data);
    
    ram_tdata (
        user &&user_data);

    user &get_user_data();

};

class file_tdata final :
    public tdata
{

private:

    long int _cur_file_pos;

public:

    file_tdata(
		long int file_pos = -1);
	
	void serialize(
		const std::string &path,
		const std::string &name_key,
		const user &value,
		bool update_flag = false);
	
	user deserialize(
		const std::string &path) const;

};

#pragma endregion TDATA




#pragma region COLLECTION PROPERTIES

public:

    class collection final :
        protected allocator_guardant
    {

        private:

            search_tree<tkey_flyweight, tdata *> *_tdata;
            ipc::search_tvar _search_tvar;

            std::shared_ptr<allocator> _allocator;
            allocator_with_fit_mode::fit_mode _fit_mode;
            ipc::allocator_var _allocator_var;

            size_t _records_amount;
            size_t _disposed_amount;

        public:

            [[nodiscard]] inline allocator *get_allocator () const noexcept;

        private:

            void clear();
		
		    void copy_from(
			    collection const &other);
		
		    void move_from(
			    collection &&other);

            void check_if_refresh (
                const std::string &path);

            void refresh (
                const std::string &path);

        public:

            ~collection();
		
		    collection(
		    	collection const &other);
    
		    collection &operator=(
		    	collection const &other);
    
		    collection(
		    	collection &&other) noexcept;
    
		    collection &operator=(
		    	collection &&other) noexcept;

        public:

            collection (
                ipc::search_tvar search_tvar,
                ipc::allocator_var allocator_var,
                allocator_with_fit_mode::fit_mode fit_mode,
                size_t param_for_tree = 8);

            void add_to_inner (
                const std::string &user_name,
                const user &user,
                const std::string &path);

            void add_to_inner (
                const std::string &user_name,
                const user &&user,
                const std::string &path);

            void update_inner (
                const std::string &user_name,
                const user &user,
                const std::string &path);
            
            void update_inner (
                const std::string &user_name,
                const user &&user,
                const std::string &path);

            user dispose_from_inner (       
                const std::string &user_name,
                const std::string &path);        

            user obtain_from_inner (     
                const std::string &user_name,
                const std::string &path);     

            std::vector<std::pair<tkey, tvalue>> obtain_between(
			    const tkey &lower_bound,
			    const tkey &upper_bound,
			    bool lower_bound_inclusive,
			    bool upper_bound_inclusive,
			    const std::string &path);
		
		    std::pair<tkey, tvalue> obtain_min(
		    	const std::string &path);
    
		    std::pair<tkey, tvalue> obtain_max(
		    	const std::string &path);
    
		    std::pair<tkey, tvalue> obtain_next(
		    	const std::string &path,
		    	const tkey &key);
    
		    size_t get_records_amount();   


    };

#pragma endregion COLLECTION PROPERTIES




#pragma region SCHEMA PROPERTIES

public:

    class schema final 
    {   

    private:

        search_tree<tkey_flyweight, collection> *_collections;
        ipc::search_tvar _search_tvar;

        //size_t _records_amount;

    public:

        //[[nodiscard]] inline allocator *get_allocator () const noexcept;

    private:

		void clear();
		
		void copy_from(
			schema const &other);
		
		void move_from(
			schema &&other);

    public:
	
		~schema();
		
		schema(
			schema const &other);
		
		schema &operator=(
			schema const &other);
		
		schema(
			schema &&other) noexcept;
		
		schema &operator=(
			schema &&other) noexcept;

    public:

        schema (
            ipc::search_tvar search_tvar,
            size_t param_for_tree = 8);

        void add_to_inner (
            const std::string &collection_name,
            ipc::search_tvar search_tvar,
            ipc::allocator_var allocator_var,
            allocator_with_fit_mode::fit_mode fit_mode,
            size_t param_for_tree);

        void dispose_from_inner (
            const std::string &collection_name);
        
        collection &obtain_from_inner (
            const std::string &collection_name);

    };

#pragma endregion SCHEMA PROPERTIES




#pragma region POOL PROPERTIES

public:

    class pool final
    {

    private:

        search_tree<tkey_flyweight, schema> *_schemas;
        ipc::search_tvar _search_tvar;

    private:
	
		void clear();
		
		void copy_from(
			const pool &other);
		
		void move_from(
			pool &&other);	

    public:
	
		~pool();
		
		pool(
			const pool &other);
		
		pool &operator=(
			const pool &other);
		
		pool(
			pool &&other) noexcept;
		
		pool &operator=(
			pool &&other) noexcept;

    public:

        explicit pool (
            ipc::search_tvar search_tvar,
            size_t param_for_t);

        void add_to_inner (
            const std::string &schema_name,
            ipc::search_tvar search_tvar,
            size_t param_for_tree);

        void dispose_from_inner (
            const std::string &schema_name);
        
        schema &obtain_from_inner (
            const std::string &schema_name);

    };

#pragma endregion POOL PROPERTIES




#pragma region DB_MANAGER PROPERTIES


#pragma region BASIC PROPERTIES

private:

    

    size_t _id;
    ipc::mode _mode;
    b_tree<tkey_flyweight, pool> _pools;
    //std::shared_ptr<logger> logger;
    std::shared_ptr<allocator> allocator;

public:

    size_t get_id () const noexcept;

    db_storage *setup (
        size_t id,
        ipc::mode mode);

    db_storage *clear();

private:

    void add_to_inner (
        const std::string &pool_name,
        ipc::search_tvar search_tvar,
        size_t param_for_tree);

    void dispose_from_inner (
        const std::string &pool_name);

public:

    pool &obtain_from_inner (
        const std::string &pool_name);

    


#pragma endregion BASIC PROPERTIES



#pragma region SINGLETON PROPERTIES

private:

    db_storage ();

public:

    static db_storage *get_singleton();

public:

    db_storage (
        const db_storage &) = delete;
    
    db_storage (
        db_storage &&) = delete;

#pragma endregion SINGLETON PROPERTIES



#pragma region RAM BASIC INTERFACE

public:

    db_storage *add_pool (
        const std::string &pool_name,
        ipc::search_tvar search_tvar,
        size_t param_for_tree);

    db_storage *dispose_pool (
        const std::string &pool_name);


    db_storage *add_schema (
        const std::string &pool_name,
        const std::string &schema_name,
        ipc::search_tvar search_tvar,
        size_t param_for_tree);

    db_storage *dispose_schema (
        const std::string &pool_name,
        const std::string &schema_name);


    db_storage *add_collection (
        const std::string &pool_name,
        const std::string &schema_name,
        const std::string &collection_name,
        ipc::search_tvar search_tvar,
        ipc::allocator_var allocator_var,
        allocator_with_fit_mode::fit_mode fit_mode,
        size_t param_for_tree);
    
    db_storage *dispose_collection (
        const std::string &pool_name,
        const std::string &schema_name,
        const std::string &collection_name);
    

    db_storage *add_user_data (
        const std::string &pool_name,
        const std::string &schema_name,
        const std::string &collection_name,
        const std::string &user_name,
        const user &user);
    
    db_storage *add_user_data (
        const std::string &pool_name,
        const std::string &schema_name,
        const std::string &collection_name,
        const std::string &user_name,
        const user &&user);

    db_storage *udpdate_user_data (
        const std::string &pool_name,
        const std::string &schema_name,
        const std::string &collection_name,
        const std::string &user_name,
        const user &user);
    
    db_storage *udpdate_user_data (
        const std::string &pool_name,
        const std::string &schema_name,
        const std::string &collection_name,
        const std::string &user_name,
        const user &&user);

    user dispose_user_data (
        const std::string &pool_name,
        const std::string &schema_name,
        const std::string &collection_name,
        const std::string &user_name);

    user obtain_user_data (
        const std::string &pool_name,
        const std::string &schema_name,
        const std::string &collection_name,
        const std::string &user_name);

    std::vector<std::pair<tkey, tvalue>> obtain_between(
		const std::string &pool_name,
		const std::string &schema_name,
		const std::string &collection_name,
        const tkey &lower_bound,
        const tkey &upper_bound,
        bool lower_bound_inclusive,
        bool upper_bound_inclusive);
	
	std::pair<tkey, tvalue> obtain_min_user(
		const std::string &pool_name,
		const std::string &schema_name,
		const std::string &collection_name);
		
	std::pair<tkey, tvalue> obtain_max_user(
		const std::string &pool_name,
		const std::string &schema_name,
		const std::string &collection_name);
		
	std::pair<tkey, tvalue> obtain_next_user(
		const std::string &pool_name,
		const std::string &schema_name,
		const std::string &collection_name,
		const tkey &user_name);


#pragma endregion RAM BASIC INTERFACE



#pragma endregion DB_MANAGER PROPERTIES


};

#endif