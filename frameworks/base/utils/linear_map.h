/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_LINEAR_MAP_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_LINEAR_MAP_H

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <type_traits>
#include <utility>

namespace OHOS::Ace {
template<typename T>
struct LinearMapNode {
    const char* key;
    T value;
};

constexpr int ConstexprStrCmp(const char* lhs, const char* rhs)
{
    std::size_t index = 0;
    while (lhs[index] != '\0' && rhs[index] != '\0') {
        if (lhs[index] != rhs[index]) {
            return (lhs[index] < rhs[index]) ? -1 : 1;
        }
        ++index;
    }
    if (lhs[index] == rhs[index]) {
        return 0;
    }
    return (lhs[index] == '\0') ? -1 : 1;
}

template<typename T, std::size_t N>
constexpr bool IsSorted(const LinearMapNode<T> (&nodes)[N])
{
    for (std::size_t index = 1; index < N; ++index) {
        if (ConstexprStrCmp(nodes[index - 1].key, nodes[index].key) > 0) {
            return false;
        }
    }
    return true;
}

template<typename T, std::size_t N>
constexpr std::size_t FirstUnsortedIndex(const LinearMapNode<T> (&nodes)[N])
{
    for (std::size_t index = 1; index < N; ++index) {
        if (ConstexprStrCmp(nodes[index - 1].key, nodes[index].key) > 0) {
            return index;
        }
    }
    return N;
}

template<auto& Nodes>
struct LinearMapSortInfo {
    using ArrayType = typename std::remove_reference<decltype(Nodes)>::type;
    static constexpr std::size_t kSize = std::extent<ArrayType>::value;
    static constexpr std::size_t kErrorIndex = []() constexpr {
        for (std::size_t index = 1; index < kSize; ++index) {
            if (ConstexprStrCmp(Nodes[index - 1].key, Nodes[index].key) > 0) {
                return index;
            }
        }
        return kSize;
    }();
};

// Encodes a key string as a template parameter pack so the compiler diagnostic lists the characters.
template<char... Cs>
struct LinearMapSortKeyChars {};

template<typename KeyChars>
struct LinearMapSortOrderFailed; // intentionally incomplete; diagnostic lists KeyChars (the key as char literals)

template<auto& Nodes, std::size_t Idx>
struct LinearMapSortErrorKey {
    static constexpr const auto& arr = Nodes;
    static constexpr std::size_t Len()
    {
        const char* k = arr[Idx].key;
        std::size_t i = 0;
        while (k[i] != '\0') {
            ++i;
        }
        return i;
    }
    template<typename Seq>
    struct KeyCharsFromSeqImpl;
    template<std::size_t... Is>
    struct KeyCharsFromSeqImpl<std::index_sequence<Is...>> {
        using type = LinearMapSortKeyChars<arr[Idx].key[Is]...>;
    };
    using type = typename KeyCharsFromSeqImpl<std::make_index_sequence<Len()>>::type;
};

template<auto& Nodes>
constexpr bool IsSortedWithDetailedLog()
{
    static_assert(LinearMapSortInfo<Nodes>::kSize > 0, "LinearMapNode array must not be empty");
    if constexpr (LinearMapSortInfo<Nodes>::kErrorIndex == LinearMapSortInfo<Nodes>::kSize) {
        return true;
    } else {
        using BadKey = typename LinearMapSortErrorKey<Nodes, LinearMapSortInfo<Nodes>::kErrorIndex>::type;
        return sizeof(LinearMapSortOrderFailed<BadKey>) != 0;
    }
}

// the key type K must can be compared.
template<typename K, typename V>
struct LinearEnumMapNode {
    K key;
    V value;
};

// these binary search functions in linear map, so the map must be sorted by key.
template<typename T>
int64_t BinarySearchFindIndex(const LinearMapNode<T>* vec, size_t length, const char* key)
{
    auto it = std::lower_bound(
        vec, vec + length, key, [](LinearMapNode<T> lhs, const char* key) { return strcmp(lhs.key, key) < 0; });
    if (it == vec + length || strcmp(it->key, key) != 0) {
        return -1;
    } else {
        return it - vec;
    }
}

template<typename K, typename V>
int64_t BinarySearchFindIndex(const LinearEnumMapNode<K, V>* vec, size_t length, K key)
{
    auto it =
        std::lower_bound(vec, vec + length, key, [](LinearEnumMapNode<K, V> lhs, K key) { return lhs.key < key; });
    if (it == vec + length || it->key != key) {
        return -1;
    } else {
        return it - vec;
    }
}
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_LINEAR_MAP_H
