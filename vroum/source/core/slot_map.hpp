#pragma once

#include "vv_headers.hpp"
#include <limits>
#include <vector>

namespace vv
{

template <typename T>
struct Handle
{
    static Handle<T> null() { return {.id = std::numeric_limits<u32>::max(), .gen=0}; };

    u32 id;
    u32 gen;
};

template <typename T>
class SlotMap
{
public:

    SlotMap(u32 reserved_size = 8)
    {
        m_elements.reserve(reserved_size);
        m_generations.reserve(reserved_size);
    }

    Handle<T> push(T &&el)
    {
        if(m_available_indices.size() == 0)
        {
            m_elements.push_back( std::move(el) );
            m_generations.push_back( 0 );
            return Handle<T>{.id=(u32)m_elements.size()-1, .gen=0};
        }
        else
        {
            u32 idx = m_available_indices.back();
            m_available_indices.pop_back();
            m_elements[idx] = std::move(el);
            return Handle<T>{.id=idx, .gen=m_generations[idx]};
        }
    }

    const T &get(Handle<T> handle) const
    {
        VV_ASSERT( handle.id < m_elements.size(), "Invalid handle" );
        VV_ASSERT( (m_generations[handle.id] == handle.gen), "Use after free for handle");
        VV_ASSERT( (m_elements[handle.id].has_value()), "Use after free for handle");

        return *m_elements[handle.id];
    }

    T &get(Handle<T> handle)
    {
        VV_ASSERT( handle.id < m_elements.size(), "Invalid handle" );
        VV_ASSERT( (m_generations[handle.id] == handle.gen), "Use after free for handle");
        VV_ASSERT( (m_elements[handle.id].has_value()), "Use after free for handle");

        return *m_elements[handle.id];
    }

    void del(Handle<T> handle)
    {
        m_elements[handle.id].reset();
        m_generations[handle.id] += 1;
        m_available_indices.push_back(handle.id);
    }

private:

    // Contains the actual data
    std::vector<Opt<T>> m_elements;

    // Same size as m_elements; m_generations[i] contains the current gen of m_elements[i]
    // generation = how many previous elements where at the same address
    // can be used as a check : if m_elements[Handle<T>.id] != Handle<T>.gen => use after free !
    std::vector<u32> m_generations;

    // Indicies that are not used in m_elements; to be used in priority before pushing to m_elements;
    std::vector<u32> m_available_indices;
};

} // namespace vv