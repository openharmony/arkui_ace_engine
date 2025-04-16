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

#ifndef GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER_UNION_H
#define GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER_UNION_H

#pragma once

#include <type_traits>

#include "core/interfaces/native/utility/generated/converter_generated.h"

namespace OHOS::Ace::NG::Converter {
namespace detail {
template<typename T, std::size_t I, typename = void>
struct UnionIndex : std::integral_constant<int, 0> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_0, std::void_t<decltype(T().value0)>> :
    std::integral_constant<int, SELECTOR_ID_0> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_1, std::void_t<decltype(T().value1)>> :
    std::integral_constant<int, SELECTOR_ID_1> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_2, std::void_t<decltype(T().value2)>> :
    std::integral_constant<int, SELECTOR_ID_2> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_3, std::void_t<decltype(T().value3)>> :
    std::integral_constant<int, SELECTOR_ID_3> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_4, std::void_t<decltype(T().value4)>> :
    std::integral_constant<int, SELECTOR_ID_4> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_5, std::void_t<decltype(T().value5)>> :
    std::integral_constant<int, SELECTOR_ID_5> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_6, std::void_t<decltype(T().value6)>> :
    std::integral_constant<int, SELECTOR_ID_6> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_7, std::void_t<decltype(T().value7)>> :
    std::integral_constant<int, SELECTOR_ID_7> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_8, std::void_t<decltype(T().value8)>> :
    std::integral_constant<int, SELECTOR_ID_8> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_9, std::void_t<decltype(T().value9)>> :
    std::integral_constant<int, SELECTOR_ID_9> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_10, std::void_t<decltype(T().value10)>> :
    std::integral_constant<int, SELECTOR_ID_10> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_11, std::void_t<decltype(T().value11)>> :
    std::integral_constant<int, SELECTOR_ID_11> {};
template<typename T>
struct UnionIndex<T, SELECTOR_ID_12, std::void_t<decltype(T().value12)>> :
    std::integral_constant<int, SELECTOR_ID_12> {};

constexpr std::size_t MAX_UNION_INDEX = SELECTOR_ID_12;

template<typename T, std::size_t... Is>
constexpr int GetUnionSize(std::index_sequence<Is...>)
{
    return std::max({UnionIndex<T, Is>::value...});
}

template<class... Ts>
struct Overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide
template<class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

template<typename T, std::size_t>
struct UnionVisitor;

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_1> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            default: visitor();break;
        }
    }
};

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_2> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            case SELECTOR_ID_2: visitor(src.value2);break;
            default: visitor();break;
        }
    }
};

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_3> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            case SELECTOR_ID_2: visitor(src.value2);break;
            case SELECTOR_ID_3: visitor(src.value3);break;
            default: visitor();break;
        }
    }
};

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_4> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            case SELECTOR_ID_2: visitor(src.value2);break;
            case SELECTOR_ID_3: visitor(src.value3);break;
            case SELECTOR_ID_4: visitor(src.value4);break;
            default: visitor();break;
        }
    }
};

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_5> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            case SELECTOR_ID_2: visitor(src.value2);break;
            case SELECTOR_ID_3: visitor(src.value3);break;
            case SELECTOR_ID_4: visitor(src.value4);break;
            case SELECTOR_ID_5: visitor(src.value5);break;
            default: visitor();break;
        }
    }
};

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_6> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            case SELECTOR_ID_2: visitor(src.value2);break;
            case SELECTOR_ID_3: visitor(src.value3);break;
            case SELECTOR_ID_4: visitor(src.value4);break;
            case SELECTOR_ID_5: visitor(src.value5);break;
            case SELECTOR_ID_6: visitor(src.value6);break;
            default: visitor();break;
        }
    }
};

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_7> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            case SELECTOR_ID_2: visitor(src.value2);break;
            case SELECTOR_ID_3: visitor(src.value3);break;
            case SELECTOR_ID_4: visitor(src.value4);break;
            case SELECTOR_ID_5: visitor(src.value5);break;
            case SELECTOR_ID_6: visitor(src.value6);break;
            case SELECTOR_ID_7: visitor(src.value7);break;
            default: visitor();break;
        }
    }
};

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_8> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            case SELECTOR_ID_2: visitor(src.value2);break;
            case SELECTOR_ID_3: visitor(src.value3);break;
            case SELECTOR_ID_4: visitor(src.value4);break;
            case SELECTOR_ID_5: visitor(src.value5);break;
            case SELECTOR_ID_6: visitor(src.value6);break;
            case SELECTOR_ID_7: visitor(src.value7);break;
            case SELECTOR_ID_8: visitor(src.value8);break;
            default: visitor();break;
        }
    }
};

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_9> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            case SELECTOR_ID_2: visitor(src.value2);break;
            case SELECTOR_ID_3: visitor(src.value3);break;
            case SELECTOR_ID_4: visitor(src.value4);break;
            case SELECTOR_ID_5: visitor(src.value5);break;
            case SELECTOR_ID_6: visitor(src.value6);break;
            case SELECTOR_ID_7: visitor(src.value7);break;
            case SELECTOR_ID_8: visitor(src.value8);break;
            case SELECTOR_ID_9: visitor(src.value9);break;
            default: visitor();break;
        }
    }
};

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_10> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            case SELECTOR_ID_2: visitor(src.value2);break;
            case SELECTOR_ID_3: visitor(src.value3);break;
            case SELECTOR_ID_4: visitor(src.value4);break;
            case SELECTOR_ID_5: visitor(src.value5);break;
            case SELECTOR_ID_6: visitor(src.value6);break;
            case SELECTOR_ID_7: visitor(src.value7);break;
            case SELECTOR_ID_8: visitor(src.value8);break;
            case SELECTOR_ID_9: visitor(src.value9);break;
            case SELECTOR_ID_10: visitor(src.value10);break;
            default: visitor();break;
        }
    }
};

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_11> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            case SELECTOR_ID_2: visitor(src.value2);break;
            case SELECTOR_ID_3: visitor(src.value3);break;
            case SELECTOR_ID_4: visitor(src.value4);break;
            case SELECTOR_ID_5: visitor(src.value5);break;
            case SELECTOR_ID_6: visitor(src.value6);break;
            case SELECTOR_ID_7: visitor(src.value7);break;
            case SELECTOR_ID_8: visitor(src.value8);break;
            case SELECTOR_ID_9: visitor(src.value9);break;
            case SELECTOR_ID_10: visitor(src.value10);break;
            case SELECTOR_ID_11: visitor(src.value11);break;
            default: visitor();break;
        }
    }
};

template<typename T>
struct UnionVisitor<T, SELECTOR_ID_12> {
    template<typename V>
    static void Visit(const T& src, const V& visitor)
    {
        switch (src.selector) {
            case SELECTOR_ID_0: visitor(src.value0);break;
            case SELECTOR_ID_1: visitor(src.value1);break;
            case SELECTOR_ID_2: visitor(src.value2);break;
            case SELECTOR_ID_3: visitor(src.value3);break;
            case SELECTOR_ID_4: visitor(src.value4);break;
            case SELECTOR_ID_5: visitor(src.value5);break;
            case SELECTOR_ID_6: visitor(src.value6);break;
            case SELECTOR_ID_7: visitor(src.value7);break;
            case SELECTOR_ID_8: visitor(src.value8);break;
            case SELECTOR_ID_9: visitor(src.value9);break;
            case SELECTOR_ID_10: visitor(src.value10);break;
            case SELECTOR_ID_11: visitor(src.value11);break;
            case SELECTOR_ID_12: visitor(src.value12);break;
            default: visitor();break;
        }
    }
};
} // namespace detail

template<typename T>
constexpr std::size_t UnionLastIndex =
    detail::GetUnionSize<T>(std::make_index_sequence<detail::MAX_UNION_INDEX + 1>{});

template<typename T, typename... Fs, decltype(T().selector) = 0>
void VisitUnion(const T& src, Fs... funcs)
{
    detail::UnionVisitor<T, UnionLastIndex<T>>::Visit(src, detail::Overloaded{funcs...});
}

template<typename T, typename... Fs, decltype(T().value.selector) = 0>
void VisitUnion(const T& src, Fs... funcs)
{
    if (src.tag != INTEROP_TAG_UNDEFINED) {
        using U = decltype(T().value);
        detail::UnionVisitor<U, UnionLastIndex<U>>::Visit(src.value, detail::Overloaded{funcs...});
    } else {
        detail::Overloaded{funcs...}();
    }
}
} // namespace OHOS::Ace::NG::Converter
#endif // GENERATED_FOUNDATION_ACE_FRAMEWORKS_CORE_UTILITY_CONVERTER_UNION_H
