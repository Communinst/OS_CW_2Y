#ifndef OPERATING_SYSTEMS_COURSE_WORK_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H
#define OPERATING_SYSTEMS_COURSE_WORK_ALLOCATOR_GLOBAL_HEAP_H

#include <allocator.h>
#include <logger.h>
#include <logger_guardant.h>
#include <typename_holder.h>

class allocator_global_heap final:
    public allocator,
    private logger_guardant,
    private typename_holder
{

private:
    
    logger *_logger;

private:

    allocator_global_heap* get_allocator(void *const mem_seg) const noexcept;
    size_t get_size(void *const mem_seg) const noexcept;
    std::string get_byte_data(void *const mem_seg) const noexcept;

public:
    
    explicit allocator_global_heap(
        logger *logger = nullptr);
    
    ~allocator_global_heap() override;
    
    allocator_global_heap(
        allocator_global_heap const &other) = delete;
    
    allocator_global_heap &operator=(
        allocator_global_heap const &other) = delete;
    
    allocator_global_heap(
        allocator_global_heap &&other) noexcept;
    
    allocator_global_heap &operator=(
        allocator_global_heap &&other) noexcept;

public:
    
    [[nodiscard]] void *allocate(
        size_t value_size,
        size_t values_count) override;
    
    void deallocate(
        void *at) override;

private:
    
    inline logger *get_logger() const override;

private:
    
    inline std::string get_typename() const noexcept override;

public:

};

#endif // OPERATING_SYSTEMS_COURSE_WORK_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H