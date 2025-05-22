
#include "Allocator.h"
#include "memory"

namespace GCrisp::Memory
{

void* Allocator::Allocate(size_t size)
{

    void* mem = malloc(size);

    AllocatedMemory& allocated = m_Data.Allocated[mem];
    allocated.Memory = mem;
    allocated.Size = size;

    m_Statistics.Allocated++;
    m_Statistics.AllocatedBytes += size;

    GC_CORE_TRACE("Allocated {0}", m_Statistics.Allocated);

    return mem;
}

bool Allocator::Free(void* data)
{
    if (data == nullptr)
        return false;

    auto iter = m_Data.Allocated.find(data);

    m_Statistics.Freed++;

    if (iter == m_Data.Allocated.end()) {
        GC_CORE_WARN("Freeing not registered memory address {0}", data);
    } else {
        AllocatedMemory& allocated = iter->second;
        m_Statistics.FreedBytes += allocated.Size;
        m_Data.Allocated.erase(iter);
    }

    GC_CORE_TRACE("Freed {0}", m_Statistics.Freed);

    free(data);
    return true;
}

}
