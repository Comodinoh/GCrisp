#pragma once

#include <gcpch.h>


namespace GCrisp
{
    class UUID
    {
    public:
        UUID() : UUID(0) {};
        UUID(const UUID& id) = default;

        explicit UUID(const uint32_t& id) : m_ID(id) {}

        inline uint32_t Get() const {return m_ID;}

        operator uint32_t() const {return m_ID;}

        auto operator<=>(const UUID&) const = default;

        static UUID Generate()
        {
            s_Counter++;
            return UUID(s_Counter);
        }

        static void Destroy(const UUID& uuid)
        {
            s_Counter--;
            // TODO: IDK if to reset the provided UUID to 0
            // uuid = UUID();
        }
    private:
        uint32_t m_ID = 0;

        static uint32_t s_Counter;
    };

}

namespace std
{
    template<>
    struct hash<GCrisp::UUID>
    {
        size_t operator()(const GCrisp::UUID& cmp) const noexcept
        {
            return std::hash<uint32_t>()(cmp.Get());
        }
    };
}
