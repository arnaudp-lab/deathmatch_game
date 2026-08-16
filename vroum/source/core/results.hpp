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

    bool ok() const { return m_data.index() == 1; }

    T &value() { return std::get<T>(m_data); }
    const T &value() const{ return std::get<T>(m_data); }
    Error err() const { return std::get<Error>(m_data); }

private:
    Res(const T &val): m_data(val) {}
    Res(const Error &err): m_data(err) {}

    std::variant<T, Error> m_data;
};














// template <typename T>
// class Res
// {
// public:
//     static Res ok( T value ) { return Res( std::in_place_index<0>, std::move(value) ); }
//     static Res fail( Error err ) { return Res( std::in_place_index<1>, err ); }

//     bool ok() const { return m_data.index() == 0; }
//     explicit operator bool() const { return ok(); }

//     T& value() { return std::get<0>(m_data); }
//     Error err() const { return ok() ? Error::ok : std::get<1>(m_data); }

// private:
//     Res( auto tag, auto&& v ) : m_data( tag, std::forward<decltype(v)>(v) ) {}
//     std::variant<T, Error> m_data;
// };

} // namespace vv