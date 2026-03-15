#pragma once

namespace Vane::Memory
{

struct AllocatorStatistics
{
    size_t Allocated = 0;
    size_t AllocatedBytes = 0;

    size_t Freed = 0;
    size_t FreedBytes = 0;
};

}
