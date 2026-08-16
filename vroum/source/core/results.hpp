#pragma once

#include "errors.hpp"
#include <variant>

namespace vv
{

template <typename T>
struct Res
{
public:
    static Res<T> ok(const T &val) { return Res<T>(val); }
    static Res<T> fail(const Error &err) { return Res<T>(err); }

    bool is_ok() const { return m_data.index() == 0; }

    T &value() { return std::get<T>(m_data); }
    const T &value() const{ return std::get<T>(m_data); }
    Error err() const { return is_ok() ? Error::ok : std::get<Error>(m_data); }

private:
    Res(const T &val): m_data(val) {}
    Res(const Error &err): m_data(err) {}

    std::variant<T, Error> m_data;
};


} // namespace vv