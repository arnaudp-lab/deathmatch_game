#pragma once

#include <cstdlib>
#include <cstdint>
#include <memory>
#include <optional>

#include "core/errors.hpp"
#include "core/results.hpp"

// TODO: define custom VV_DEBUG / VV_RELEASE etc.
#ifndef NDEBUG

	// NOTE: condition is NOT evaluated in release builds (NDEBUG).
	// Never put code with side effects inside VV_ASSERT's condition —
	// e.g. VV_ASSERT(do_thing(), "..."). do_thing() won't run in release.
    #define VV_ASSERT(condition, message) \
        do { \
            if (!(condition)) { \
                VV_FATAL(message); \
                std::abort(); \
            } \
        } while (0)
#else
	// Even in release mode, we still "use" condition => no "unused variable" tidle
    #define VV_ASSERT(condition, message) ((void)sizeof(condition))
#endif

namespace vv
{
	template <typename T>
	using Opt = std::optional<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Box = std::unique_ptr<T>;

	using f32 = float;
	using f64 = double;

	using u32 = uint32_t;
	using i32 = int32_t;

	using u64 = uint64_t;
	using i64 = int64_t;

	using u16 = uint16_t;
	using i16 = int16_t;

	using u8 = uint8_t;
	using i8 = int8_t;
}