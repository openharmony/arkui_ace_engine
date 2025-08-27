/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_CONTAINER_MAP_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_CONTAINER_MAP_H

#include <initializer_list>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <stdexcept>
#include <utility>

#include "base/log/log_wrapper.h"

#define list_entry(ptr, type, member) \
    reinterpret_cast<type*>(reinterpret_cast<char*>(ptr) - offsetof(type, member))

namespace OHOS::Ace {
template<typename Key, typename T>
class SafeMap {
public:
    class iterator;
    struct list_head {
        list_head *prev, *next;
        list_head() : prev(this), next(this) {}
        list_head(list_head* head)
        {
            if (head) {
                prev = head;
                next = head->next;
                head->next->prev = this;
                head->next = this;
            } else {
                prev = next = this;
            }
        }
        ~list_head()
        {
            prev->next = next;
            next->prev = prev;
            prev = next = nullptr;
        }
        void add(list_head* head)
        {
            prev->next = next;
            next->prev = prev;
            prev = head;
            next = head->next;
            head->next->prev = this;
            head->next = this;
        }
    };

    using value_type = std::pair<const Key, T>;

private:
    struct TrackedElement {
        T value;
        mutable list_head iterator_head;

        TrackedElement(const T& val) : value(val) {}
        TrackedElement(T&& val) : value(std::move(val)) {}
        TrackedElement(const TrackedElement& rhs) : value(rhs.value) {}
        TrackedElement& operator=(const TrackedElement& rhs)
        {
            if (&rhs != this) {
                this->value = rhs.value;
            }
            return *this;
        }
        template<typename... Args>
        TrackedElement(Args&&... args) : value(std::forward<Args>(args)...)
        {}

        ~TrackedElement()
        {
            invalidate_iterators();
        }

        void invalidate_iterators()
        {
            list_head* pos = iterator_head.next;
            while (pos != &iterator_head) {
                list_head* next = pos->next;
                auto iter = list_entry(pos, iterator, node);
                iter->container_ = nullptr;
                pos = next;
            }
        }

        void invalidate_iterators() const
        {
            list_head* pos = iterator_head.next;
            while (pos != &iterator_head) {
                list_head* next = pos->next;
                auto iter = list_entry(pos, iterator, node);
                iter->container_ = nullptr;
                pos = next;
            }
        }
    };

    std::map<Key, TrackedElement, std::less<>> elements;
    mutable list_head end_iterator_head;

    void invalidate_end_iterators()
    {
        list_head* pos = end_iterator_head.next;
        while (pos != &end_iterator_head) {
            list_head* next = pos->next;
            auto iter = list_entry(pos, iterator, node);
            iter->container_ = nullptr;
            pos = next;
        }
    }

public:
    class iterator {
    private:
        using MapIter = typename std::map<Key, TrackedElement>::iterator;
        SafeMap* container_ = nullptr;
        MapIter inner_iter;
        list_head node;
        friend SafeMap;
        MapIter get_end() const
        {
            return container_ ? container_->elements.end() : MapIter {};
        }

        explicit iterator(SafeMap* container, MapIter it = MapIter {})
            : container_(container), inner_iter(it),
              node(container_
                       ? (inner_iter != get_end() ? &inner_iter->second.iterator_head : &container_->end_iterator_head)
                       : nullptr)
        {}

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;

        iterator() : container_(nullptr), inner_iter(), node() {}

        iterator(const iterator& other) : container_(other.container_), inner_iter(other.inner_iter)
        {
            if (container_) {
                if (inner_iter != get_end()) {
                    node.add(&inner_iter->second.iterator_head);
                } else {
                    node.add(&container_->end_iterator_head);
                }
            }
        }

        iterator& operator=(const iterator& other)
        {
            if (this != &other) {
                container_ = other.container_;
                inner_iter = other.inner_iter;
                if (container_) {
                    if (inner_iter != get_end()) {
                        node.add(&inner_iter->second.iterator_head);
                    } else {
                        node.add(&container_->end_iterator_head);
                    }
                }
            }
            return *this;
        }

        value_type& operator*() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_end()))) {
                LOGF_ABORT("Dereferencing invalid iterator");
            }
            return *reinterpret_cast<value_type*>(&*inner_iter);
        }

        value_type* operator->() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_end()))) {
                LOGF_ABORT("Dereferencing invalid iterator");
            }
            return reinterpret_cast<value_type*>(&*inner_iter);
        }

        iterator& operator++()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Incrementing invalid iterator");
            }
            ++inner_iter;
            if (inner_iter != get_end()) {
                node.add(&inner_iter->second.iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator& operator--()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Decrementing invalid iterator");
            }
            --inner_iter;
            if (inner_iter != get_end()) {
                node.add(&inner_iter->second.iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const
        {
            if (!container_ || !other.container_) {
                return false;
            }
            return inner_iter == other.inner_iter;
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }
    };

    class const_iterator {
    private:
        using MapIter = typename std::map<Key, TrackedElement>::const_iterator;
        const SafeMap* container_ = nullptr;
        MapIter inner_iter;
        list_head node;
        friend SafeMap;
        MapIter get_cend() const
        {
            return container_ ? container_->elements.cend() : MapIter {};
        }

        explicit const_iterator(const SafeMap* container, MapIter it = MapIter {})
            : container_(container), inner_iter(it),
              node(container_
                       ? (inner_iter != get_cend() ? &inner_iter->second.iterator_head : &container_->end_iterator_head)
                       : nullptr)
        {}

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;

        const_iterator() : container_(nullptr), inner_iter(), node() {}
        const_iterator(const iterator& other) : container_(other.container_), inner_iter(other.inner_iter)
        {
            if (container_) {
                if (inner_iter != get_cend()) {
                    node.add(&inner_iter->second.iterator_head);
                } else {
                    node.add(&container_->end_iterator_head);
                }
            }
        }

        const_iterator(const const_iterator& other) : container_(other.container_), inner_iter(other.inner_iter)
        {
            if (container_) {
                if (inner_iter != get_cend()) {
                    node.add(&inner_iter->second.iterator_head);
                } else {
                    node.add(&container_->end_iterator_head);
                }
            }
        }

        const_iterator& operator=(const const_iterator& other)
        {
            if (this != &other) {
                container_ = other.container_;
                inner_iter = other.inner_iter;
                if (container_) {
                    if (inner_iter != get_cend()) {
                        node.add(&inner_iter->second.iterator_head);
                    } else {
                        node.add(&container_->end_iterator_head);
                    }
                }
            }
            return *this;
        }

        const value_type& operator*() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_cend()))) {
                LOGF_ABORT("Dereferencing invalid const_iterator");
            }
            return *reinterpret_cast<const value_type*>(&*inner_iter);
        }

        const value_type* operator->() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_cend()))) {
                LOGF_ABORT("Dereferencing invalid const_iterator");
            }
            return reinterpret_cast<const value_type*>(&*inner_iter);
        }

        const_iterator& operator++()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Incrementing invalid const_iterator");
            }
            ++inner_iter;
            if (inner_iter != get_cend()) {
                node.add(&inner_iter->second.iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const_iterator& operator--()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Dereferencing invalid iterator");
            }
            --inner_iter;
            if (inner_iter != get_cend()) {
                node.add(&inner_iter->second.iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const const_iterator& other) const
        {
            if (!container_ || !other.container_) {
                return false;
            }
            return inner_iter == other.inner_iter;
        }

        bool operator!=(const const_iterator& other) const
        {
            return !(*this == other);
        }
    };

    class reverse_iterator {
    private:
        using MapIter = typename std::map<Key, TrackedElement>::reverse_iterator;
        SafeMap* container_ = nullptr;
        MapIter inner_iter;
        list_head node;
        friend SafeMap;
        MapIter get_rend() const
        {
            return container_ ? container_->elements.rend() : MapIter {};
        }

        explicit reverse_iterator(SafeMap* container, MapIter it = MapIter {})
            : container_(container), inner_iter(it),
              node(container_
                       ? (inner_iter != get_rend() ? &inner_iter->second.iterator_head : &container_->end_iterator_head)
                       : nullptr)
        {}

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;

        reverse_iterator() : container_(nullptr), inner_iter(), node() {}

        reverse_iterator(const reverse_iterator& other) : container_(other.container_), inner_iter(other.inner_iter)
        {
            if (container_) {
                if (inner_iter != get_rend()) {
                    node.add(&inner_iter->second.iterator_head);
                } else {
                    node.add(&container_->end_iterator_head);
                }
            }
        }

        reverse_iterator& operator=(const reverse_iterator& other)
        {
            if (this != &other) {
                container_ = other.container_;
                inner_iter = other.inner_iter;
                if (container_) {
                    if (inner_iter != get_rend()) {
                        node.add(&inner_iter->second.iterator_head);
                    } else {
                        node.add(&container_->end_iterator_head);
                    }
                }
            }
            return *this;
        }

        value_type& operator*() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_rend()))) {
                LOGF_ABORT("Dereferencing invalid reverse iterator");
            }
            return *reinterpret_cast<value_type*>(&*inner_iter);
        }

        value_type* operator->() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_rend()))) {
                LOGF_ABORT("Dereferencing invalid reverse iterator");
            }
            return reinterpret_cast<value_type*>(&*inner_iter);
        }

        reverse_iterator& operator++()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Incrementing invalid reverse iterator");
            }
            ++inner_iter;
            if (inner_iter != get_rend()) {
                node.add(&inner_iter->second.iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reverse_iterator& operator--()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Decrementing invalid iterator");
            }
            --inner_iter;
            if (inner_iter != get_rend()) {
                node.add(&inner_iter->second.iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const reverse_iterator& other) const
        {
            return inner_iter == other.inner_iter;
        }

        bool operator!=(const reverse_iterator& other) const
        {
            return !(*this == other);
        }
    };

    class const_reverse_iterator {
    private:
        using MapIter = typename std::map<Key, TrackedElement>::const_reverse_iterator;
        const SafeMap* container_ = nullptr;
        MapIter inner_iter;
        list_head node;
        friend SafeMap;
        MapIter get_crend() const
        {
            return container_ ? container_->elements.crend() : MapIter {};
        }

        explicit const_reverse_iterator(const SafeMap* container, MapIter it = MapIter {})
            : container_(container), inner_iter(it),
              node(container_ ? (inner_iter != get_crend() ? &inner_iter->second.iterator_head
                                                           : &container_->end_iterator_head)
                              : nullptr)
        {}

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;

        const_reverse_iterator() : container_(nullptr), inner_iter(), node() {}

        const_reverse_iterator(const reverse_iterator& other)
            : container_(other.container_), inner_iter(other.inner_iter)
        {
            if (container_) {
                if (inner_iter != get_crend()) {
                    node.add(&inner_iter->second.iterator_head);
                } else {
                    node.add(&container_->end_iterator_head);
                }
            }
        }

        const_reverse_iterator(const const_reverse_iterator& other)
            : container_(other.container_), inner_iter(other.inner_iter)
        {
            if (container_) {
                if (inner_iter != get_crend()) {
                    node.add(&inner_iter->second.iterator_head);
                } else {
                    node.add(&container_->end_iterator_head);
                }
            }
        }

        const_reverse_iterator& operator=(const const_reverse_iterator& other)
        {
            if (this != &other) {
                container_ = other.container_;
                inner_iter = other.inner_iter;
                if (container_) {
                    if (inner_iter != get_crend()) {
                        node.add(&inner_iter->second.iterator_head);
                    } else {
                        node.add(&container_->end_iterator_head);
                    }
                }
            }
            return *this;
        }

        const value_type& operator*() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_crend()))) {
                LOGF_ABORT("Dereferencing invalid const_reverse iterator");
            }
            return *reinterpret_cast<const value_type*>(&*inner_iter);
        }

        const value_type* operator->() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_crend()))) {
                LOGF_ABORT("Dereferencing invalid const_reverse iterator");
            }
            return reinterpret_cast<const value_type*>(&*inner_iter);
        }

        const_reverse_iterator& operator++()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Incrementing invalid const_reverse iterator");
            }
            ++inner_iter;
            if (inner_iter != get_crend()) {
                node.add(&inner_iter->second.iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        const_reverse_iterator operator++(int)
        {
            const_reverse_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const_reverse_iterator& operator--()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Decrementing invalid const_reverse iterator");
            }
            --inner_iter;
            if (inner_iter != get_crend()) {
                node.add(&inner_iter->second.iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        const_reverse_iterator operator--(int)
        {
            const_reverse_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const const_reverse_iterator& other) const
        {
            return inner_iter == other.inner_iter;
        }

        bool operator!=(const const_reverse_iterator& other) const
        {
            return !(*this == other);
        }
    };

    SafeMap() = default;

    SafeMap(std::initializer_list<std::pair<const Key, T>> ilist)
    {
        for (const auto& val : ilist) {
            elements.emplace(val.first, val.second);
        }
    }
    SafeMap(const SafeMap& other) : elements(other.elements) {}

    SafeMap(SafeMap&& other) noexcept
    {
        elements = std::move(other.elements);
    }
    ~SafeMap()
    {
        invalidate_end_iterators();
    }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        auto [it, inserted] = elements.insert(value);
        return { iterator(this, it), inserted };
    }

    std::pair<iterator, bool> insert(value_type&& value)
    {
        auto [it, inserted] = elements.insert(std::forward<value_type>(value));
        return { iterator(this, it), inserted };
    }

    template<class P>
    std::pair<iterator, bool> insert(P&& value)
    {
        auto [it, inserted] = elements.insert(std::forward<P>(value));
        return { iterator(this, it), inserted };
    }

    iterator insert(const_iterator pos, const value_type& value)
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !pos.container_)) {
            LOGF_ABORT("Inserting with invalid iterator");
        }
        return iterator(this, elements.insert(pos.inner_iter, value));
    }

    iterator insert(const_iterator pos, value_type&& value)
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !pos.container_)) {
            LOGF_ABORT("Inserting with invalid iterator");
        }
        return iterator(this, elements.insert(pos.inner_iter, std::forward<value_type>(value)));
    }

    template<class P>
    iterator insert(const_iterator pos, P&& value)
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !pos.container_)) {
            LOGF_ABORT("Inserting with invalid iterator");
        }
        return iterator(this, elements.insert(pos.inner_iter, std::forward<P>(value)));
    }

    template<class InputIt>
    void insert(InputIt first, InputIt last)
    {
        elements.insert(first, last);
    }

    void insert(std::initializer_list<value_type> ilist)
    {
        elements.insert(ilist.begin(), ilist.end());
    }

    template<class... Args>
    std::pair<iterator, bool> emplace(Args&&... args)
    {
        auto [it, inserted] = elements.emplace(std::forward<Args>(args)...);
        return { iterator(this, it), inserted };
    }

    template<typename M>
    std::pair<iterator, bool> insert_or_assign(const Key& k, M&& obj)
    {
        auto [it, inserted] = elements.insert_or_assign(k, std::forward<M>(obj));
        return { iterator(this, it), inserted };
    }
    template<class M>
    std::pair<iterator, bool> insert_or_assign(Key&& k, M&& obj)
    {
        auto [it, inserted] = elements.insert_or_assign(std::forward<Key>(k), std::forward<M>(obj));
        return { iterator(this, it), inserted };
    }
    template<class M>
    iterator insert_or_assign(const_iterator hint, const Key& k, M&& obj)
    {
        return iterator(this, elements.insert_or_assign(hint.inner_iter, k, std::forward<M>(obj)));
    }
    template<class M>
    iterator insert_or_assign(const_iterator hint, Key&& k, M&& obj)
    {
        return iterator(this, elements.insert_or_assign(hint.inner_iter, std::forward<Key>(k), std::forward<M>(obj)));
    }

    template<typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args)
    {
        return iterator(this, elements.emplace_hint(hint.inner_iter, std::forward<Args>(args)...));
    }

    template<typename... Args>
    std::pair<iterator, bool> try_emplace(const Key& k, Args&&... args)
    {
        auto [it, inserted] = elements.try_emplace(k, std::forward<Args>(args)...);
        return { iterator(this, it), inserted };
    }
    template<class... Args>
    std::pair<iterator, bool> try_emplace(Key&& k, Args&&... args)
    {
        auto [it, inserted] = elements.try_emplace(std::forward<Key>(k), std::forward<Args>(args)...);
        return { iterator(this, it), inserted };
    }
    template<class... Args>
    iterator try_emplace(const_iterator hint, Key&& k, Args&&... args)
    {
        auto result = elements.try_emplace(hint.inner_iter, std::forward<Key>(k), std::forward<Args>(args)...);
        return iterator(this, result);
    }
    template<class... Args>
    iterator try_emplace(const_iterator hint, const Key& k, Args&&... args)
    {
        auto result = elements.try_emplace(hint.inner_iter, k, std::forward<Args>(args)...);
        return iterator(this, result);
    }

    void swap(SafeMap& other) noexcept
    {
        elements.swap(other.elements);
    }

    auto extract(const_iterator pos)
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                         (!pos.container_ || pos.inner_iter == elements.end()))) {
            LOGF_ABORT("extract with invalid iterator");
        }
        auto node = elements.extract(pos.inner_iter);
        if (!node.empty()) {
            node.mapped().invalidate_iterators();
        }
        return node;
    }
    auto extract(const Key& k)
    {
        auto node = elements.extract(k);
        if (!node.empty()) {
            node.mapped().invalidate_iterators();
        }
        return node;
    }

    void merge(SafeMap& other)
    {
        elements.merge(other.elements);
    }

    size_t count(const Key& k) const
    {
        return elements.count(k);
    }

    std::pair<iterator, iterator> equal_range(const Key& k)
    {
        auto [first, last] = elements.equal_range(k);
        return { iterator(this, first), iterator(this, last) };
    }

    iterator lower_bound(const Key& k)
    {
        return iterator(this, elements.lower_bound(k));
    }

    const_iterator lower_bound(const Key& k) const
    {
        return const_iterator(this, elements.lower_bound(k));
    }

    iterator upper_bound(const Key& k)
    {
        return iterator(this, elements.upper_bound(k));
    }

    const_iterator upper_bound(const Key& k) const
    {
        return const_iterator(this, elements.upper_bound(k));
    }

    typename std::map<Key, TrackedElement>::key_compare key_comp() const
    {
        return elements.key_comp();
    }

    typename std::map<Key, TrackedElement>::value_compare value_comp() const
    {
        return elements.value_comp();
    }

    decltype(auto) get_allocator() const noexcept
    {
        return elements.get_allocator();
    }

    T& operator[](const Key& key)
    {
        return elements[key].value;
    }

    T& operator[](Key&& key)
    {
        return elements[key].value;
    }
    T& at(const Key& k)
    {
        if (elements.find(k) == elements.end()) {
            LOGF_ABORT("SafeMap::at: key not found");
        }
        return elements.at(k).value;
    }

    const T& at(const Key& k) const
    {
        if (elements.find(k) == elements.end()) {
            LOGF_ABORT("SafeMap::at: key not found");
        }
        return elements.at(k).value;
    }

    iterator erase(iterator pos)
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                         (!pos.container_ || pos.inner_iter == elements.end()))) {
            LOGF_ABORT("Erasing with invalid iterator");
        }
        return iterator(this, elements.erase(pos.inner_iter));
    }

    iterator erase(const_iterator pos)
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                         (!pos.container_ || pos.inner_iter == elements.end()))) {
            LOGF_ABORT("Erasing with invalid iterator");
        }
        return iterator(this, elements.erase(pos.inner_iter));
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                         (!first.container_ || !last.container_ || first.inner_iter == elements.end()))) {
            LOGF_ABORT("Erasing with invalid iterator");
        }
        return iterator(this, elements.erase(first.inner_iter, last.inner_iter));
    }

    size_t erase(Key key)
    {
        return elements.erase(key);
    }

    iterator find(const Key& key)
    {
        return iterator(this, elements.find(key));
    }

    const_iterator find(const Key& key) const
    {
        return const_iterator(this, elements.find(key));
    }

    template<typename K>
    iterator find(const K& x)
    {
        return iterator(this, elements.find(x));
    }

    template<typename K>
    const_iterator find(const K& x) const
    {
        return const_iterator(this, elements.find(x));
    }

    size_t size() const
    {
        return elements.size();
    }

    bool empty() const
    {
        return elements.empty();
    }

    int max_size() const
    {
        return elements.max_size();
    }

    void clear()
    {
        elements.clear();
    }

    iterator begin()
    {
        return iterator(this, elements.begin());
    }
    const_iterator begin() const
    {
        return const_iterator(this, elements.begin());
    }
    iterator end()
    {
        return iterator(this, elements.end());
    }
    const_iterator end() const
    {
        return const_iterator(this, elements.end());
    }
    const_iterator cbegin() const
    {
        return const_iterator(this, elements.begin());
    }
    const_iterator cend()
    {
        return const_iterator(this, elements.end());
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator(this, elements.rbegin());
    }
    reverse_iterator rend()
    {
        return reverse_iterator(this, elements.rend());
    }
    const_reverse_iterator rbegin() const
    {
        return crbegin();
    }
    const_reverse_iterator rend() const
    {
        return crend();
    }
    const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator(this, elements.crbegin());
    }
    const_reverse_iterator crend() const
    {
        return const_reverse_iterator(this, elements.crend());
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_CONTAINER_MAP_H