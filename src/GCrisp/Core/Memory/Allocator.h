#pragma once

#include "Statistics.h"
#include "map"

namespace GCrisp::Memory
{

struct AllocatedMemory
{
    void* Memory;
    size_t Size;
};

struct AllocatorData
{
    std::map<const void*, AllocatedMemory> Allocated;
};

class Allocator
{
public:
    Allocator()
    {
    }

    ~Allocator()
    {
    }

    // void Init();
    //
    // void Shutdown();

    void* Allocate(size_t size);

    bool Free(void* data);

    template <typename T, typename... Args>
    T* Construct(Args&&... args)
    {
        void* mem = Allocate(sizeof(T));
        return new(mem) T(std::forward<Args>(args)...);
    }

    template <typename T>
    T* ConstructArray(const size_t n)
    {
        void* mem = Allocate(n * sizeof(T));
        memset(mem, 0, n * sizeof(T));
        return static_cast<T*>(mem);
    }

    template <typename T>
    void Delete(T* obj)
    {
        obj->~T();
        Free(obj);
    }


    inline AllocatorStatistics& GetStatistics()
    {
        return m_Statistics;
    }

private:
    AllocatorStatistics m_Statistics{};

    AllocatorData m_Data{};
};

inline Allocator* g_GlobalAllocator = nullptr;

inline Allocator* GetGlobalAllocator() { return g_GlobalAllocator; }

}