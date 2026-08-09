#pragma once

#include "errors.hpp"

namespace vv
{

template <typename T>
struct Res
{
    Error err = Error::ok;
    T value {};

    bool ok() const { return err == Error::ok; }
    explicit operator bool () const {return err == Error::ok; }
};

} // namespace vv