/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_MEM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_MEM_H

#include <cstdlib>
#include <limits>
#include <memory>
#include <type_traits>
#include <utility>

#include "base/log/log.h"

namespace OHOS::Ace::NG {

template <typename T,
          typename = std::enable_if_t<std::is_trivially_default_constructible<T>::value &&
                                      std::is_trivially_destructible<T>::value>>
class AutoTMalloc {
public:
    explicit AutoTMalloc(T* ptr = nullptr) : fPtr_(ptr) {}
    explicit AutoTMalloc(size_t count)
        : fPtr_(count ? (T*)MallocThrow(count, sizeof(T)) : nullptr) {}

    AutoTMalloc(AutoTMalloc&&) = default;
    AutoTMalloc& operator=(AutoTMalloc&&) = default;
    void realloc(size_t count)
    {
        fPtr_.reset(count ? (T*)ReallocThrow(fPtr_.release(), count * sizeof(T)) : nullptr);
    }

    T* Reset(size_t count = 0)
    {
        fPtr_.reset(count ? (T*)MallocThrow(count, sizeof(T)) : nullptr);
        return this->get();
    }
    T* get() const { return fPtr_.get(); }
    operator T*() { return fPtr_.get(); }
    operator const T*() const { return fPtr_.get(); }
    T& operator[](int index) { return fPtr_.get()[index]; }
    const T& operator[](int index) const { return fPtr_.get()[index]; }
    const T* data() const { return fPtr_.get(); }
    T* data() { return fPtr_.get(); }
    T* release() { return fPtr_.release(); }

private:
    enum {
        MALLOC_ZERO_INITIALIZE   = 1 << 0,
        MALLOC_THROW             = 1 << 1,
    };

    static inline void* ThrowOnFailure(size_t size, void* p)
    {
        if (size > 0 && p == nullptr) {
            TAG_LOGE(AceLogTag::ACE_CANVAS_COMPONENT, "canvas paint out of memory");
        }
        return p;
    }

    static inline size_t Add(size_t x, size_t y)
    {
        return x + y;
    }

    static inline uint32_t Mul32(uint32_t x, uint32_t y)
    {
        uint64_t bx = x;
        uint64_t by = y;
        uint64_t result = bx * by;
        return result;
    }

    static inline uint64_t Mul64(uint64_t x, uint64_t y)
    {
        if (x <= std::numeric_limits<uint64_t>::max() >> INT32SIZE
            && y <= std::numeric_limits<uint64_t>::max() >> INT32SIZE) {
            return x * y;
        } else {
            auto hi = [](uint64_t x) { return x >> INT32SIZE; };
            auto lo = [](uint64_t x) { return x & INT32VALUE; };
            uint64_t lx_ly = lo(x) * lo(y);
            uint64_t hx_ly = hi(x) * lo(y);
            uint64_t lx_hy = lo(x) * hi(y);
            uint64_t result = Add(lx_ly, (hx_ly << INT32SIZE));
            result = Add(result, (lx_hy << INT32SIZE));
            return result;
        }
    }

    static inline void* MallocFlags(size_t size, unsigned flags)
    {
        void* p;
        if (flags & MALLOC_ZERO_INITIALIZE) {
            p = std::calloc(size, 1);
        } else {
            p = std::malloc(size);
        }
        if (flags & MALLOC_THROW) {
            return ThrowOnFailure(size, p);
        } else {
            return p;
        }
    }

    static inline void* MallocThrow(size_t x, size_t y)
    {
        auto size = sizeof(size_t) == sizeof(uint64_t)? Mul64(x, y): Mul32(x, y);
        return MallocFlags(size, MALLOC_THROW);
    }

    static inline void* ReallocThrow(void*addr, size_t size)
    {
        return nullptr;
    }

    template <typename V, V* P>
    struct FunctionWrapper {
        template <typename... Args>
        auto operator()(Args&&... args) const-> decltype(P(std::forward<Args>(args)...))
        {
            return P(std::forward<Args>(args)...);
        }
    };

    std::unique_ptr<T, FunctionWrapper<void(void*),  free>> fPtr_;
    static constexpr uint32_t INT32SIZE = 32;
    static constexpr uint32_t INT32VALUE = 0xFFFFFFFF;
};

} // namespce OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CANVAS_PAINT_MEM_H
