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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_CONTAINER_LIST_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_CONTAINER_LIST_H

#include <initializer_list>
#include <iostream>
#include <list>
#include <memory>
#include <stdexcept>
#include <utility>

#include "base/log/log_wrapper.h"

#define list_entry(ptr, type, member) \
    reinterpret_cast<type*>(reinterpret_cast<char*>(ptr) - offsetof(type, member))

namespace OHOS::Ace {

template<typename T>
class SafeList {
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
    
private:
    struct TrackedElement {
        T value;
        mutable list_head iterator_head;

        TrackedElement(const T& val={}) : value(val) {}
        TrackedElement(T&& val) : value(std::forward<T>(val)) {}
        TrackedElement(const TrackedElement& rhs): value(rhs.value) {}
        TrackedElement& operator=(const TrackedElement& rhs) {
            if (&rhs != this) {
                this->value = rhs.value;
            }
        }

        ~TrackedElement()
        {
            invalidate_iterators();
        }

        void invalidate_iterators()
        {
            list_head *pos, *next;
            pos = iterator_head.next;
            while (pos != &iterator_head) {
                next = pos->next;
                auto iter = list_entry(pos, iterator, node);
                iter->container_ = nullptr;
                pos = next;
            }
        }

        void invalidate_iterators() const
        {
            list_head *pos, *next;
            pos = iterator_head.next;
            while (pos != &iterator_head) {
                next = pos->next;
                auto iter = list_entry(pos, iterator, node);
                iter->container_ = nullptr;
                pos = next;
            }
        }

        bool operator<(const TrackedElement& other) const
        {
            return value < other.value;
        }

        bool operator>(const TrackedElement& other) const
        {
            return value > other.value;
        }

        bool operator==(const TrackedElement& other) const
        {
            return value == other.value;
        }

        bool operator!=(const TrackedElement& other) const
        {
            return value != other.value;
        }
    };

    std::list<TrackedElement> elements;
    mutable list_head end_iterator_head;

    void invalidate_end_iterators()
    {
        list_head *pos, *next;
        pos = end_iterator_head.next;
        while (pos != &end_iterator_head) {
            next = pos->next;
            auto iter = list_entry(pos, iterator, node);
            iter->container_ = nullptr;
            pos = next;
        }
    }

public:
    class iterator {
    private:
        using ListIter = typename std::list<TrackedElement>::iterator;
        SafeList* container_ = nullptr;
        ListIter inner_iter;
        list_head node;
        friend SafeList;
        ListIter get_end() const
        {
            return container_ ? container_->elements.end() : ListIter {};
        }

        explicit iterator(SafeList* container, ListIter it = ListIter {})
            : container_(container), inner_iter(it),
              node(container_ ? (inner_iter != get_end() ? &inner_iter->iterator_head : &container_->end_iterator_head)
                              : nullptr)
        {}

    public:
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        explicit iterator() : container_(nullptr), inner_iter(), node() {}

        iterator(const iterator& other) : container_(other.container_), inner_iter(other.inner_iter)
        {
            if (container_) {
                if (inner_iter != get_end()) {
                    node.add(&inner_iter->iterator_head);
                } else {
                    node.add(&container_->end_iterator_head);
                }
            }
        }
        
        T& operator*() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_end()))) {
                LOGF_ABORT("Dereferencing invalid iterator");
            }
            return inner_iter->value;
        }

        T* operator->() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_end()))) {
                LOGF_ABORT("Dereferencing invalid iterator");
            }
            return &inner_iter->value;
        }

        iterator& operator=(const iterator& other)
        {
            if (this != &other) {
                container_ = other.container_;
                inner_iter = other.inner_iter;

                if (container_) {
                    if (inner_iter != get_end()) {
                        node.add(&inner_iter->iterator_head);
                    } else {
                        node.add(&container_->end_iterator_head);
                    }
                }
            }
            return *this;
        }

        iterator& operator++()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Incrementing invalid iterator");
            }
            ++inner_iter;
            if (inner_iter != get_end()) {
                node.add(&inner_iter->iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        iterator operator++(int)
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Decrementing invalid iterator");
            }
            --inner_iter;
            if (inner_iter != get_end()) {
                node.add(&inner_iter->iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        iterator operator--(int)
        {
            auto temp = *this;
            --(*this);
            return temp;
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
        using ListIter = typename std::list<TrackedElement>::const_iterator;
        const SafeList* container_ = nullptr;
        ListIter inner_iter;
        list_head node;
        friend SafeList;
        ListIter get_cend() const
        {
            return container_ ? container_->elements.cend() : ListIter {};
        }

        explicit const_iterator(const SafeList* container, ListIter it = ListIter {})
            : container_(container), inner_iter(it),
              node(container_ ? (inner_iter != get_cend() ? &inner_iter->iterator_head : &container_->end_iterator_head)
                              : nullptr)
        {}

    public:
        explicit const_iterator() : container_(nullptr), inner_iter(), node() {}

        const_iterator(const iterator& other) : container_(other.container_), inner_iter(other.inner_iter)
        {
            if (container_) {
                if (inner_iter != get_cend()) {
                    node.add(&inner_iter->iterator_head);
                } else {
                    node.add(&container_->end_iterator_head);
                }
            }
        }

        const_iterator(const const_iterator& other) : container_(other.container_), inner_iter(other.inner_iter)
        {
            if (container_) {
                if (inner_iter != get_cend()) {
                    node.add(&inner_iter->iterator_head);
                } else {
                    node.add(&container_->end_iterator_head);
                }
            }
        }

        const T& operator*() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_cend()))) {
                LOGF_ABORT("Dereferencing invalid const_iterator");
            }
            return inner_iter->value;
        }

        const T* operator->() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_cend()))) {
                LOGF_ABORT("Dereferencing invalid const_iterator");
            }
            return &inner_iter->value;
        }

        const_iterator& operator=(const const_iterator& other)
        {
            if (this != &other) {
                container_ = other.container_;
                inner_iter = other.inner_iter;
                if (container_) {
                    if (inner_iter != get_cend()) {
                        node.add(&inner_iter->iterator_head);
                    } else {
                        node.add(&container_->end_iterator_head);
                    }
                }
            }
            return *this;
        }

        const_iterator& operator++()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Incrementing invalid const_iterator");
            }
            ++inner_iter;
            if (inner_iter != get_cend()) {
                node.add(&inner_iter->iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        const_iterator operator++(int)
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        const_iterator& operator--()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Dereferencing invalid iterator");
            }
            --inner_iter;
            if (inner_iter != get_cend()) {
                node.add(&inner_iter->iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        const_iterator operator--(int)
        {
            auto temp = *this;
            --(*this);
            return temp;
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
        using ListIter = typename std::list<TrackedElement>::reverse_iterator;
        SafeList* container_ = nullptr;
        ListIter inner_iter;
        list_head node;
        friend SafeList;

        ListIter get_rend() const
        {
            return container_ ? container_->elements.rend() : ListIter {};
        }

        explicit reverse_iterator(SafeList* container, ListIter it = ListIter {})
            : container_(container), inner_iter(it),
              node(container_ ? (inner_iter != get_rend() ? &inner_iter->iterator_head : &container_->end_iterator_head)
                              : nullptr)
        {}

    public:
        explicit reverse_iterator() : container_(nullptr), inner_iter(), node() {}

        reverse_iterator(const reverse_iterator& other) : container_(other.container_), inner_iter(other.inner_iter)
        {
            if (container_) {
                if (inner_iter != get_rend()) {
                    node.add(&inner_iter->iterator_head);
                } else {
                    node.add(&container_->end_iterator_head);
                }
            }
        }

        T& operator*() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_rend()))) {
                LOGF_ABORT("Dereferencing invalid reverse iterator");
            }
            return inner_iter->value;
        }

        T* operator->() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_rend()))) {
                LOGF_ABORT("Dereferencing invalid reverse iterator");
            }
            return &inner_iter->value;
        }

        reverse_iterator& operator=(const reverse_iterator& other)
        {
            if (this != &other) {
                container_ = other.container_;
                inner_iter = other.inner_iter;
                if (container_) {
                    if (inner_iter != get_rend()) {
                        node.add(&inner_iter->iterator_head);
                    } else {
                        node.add(&container_->end_iterator_head);
                    }
                }
            }
            return *this;
        }

        reverse_iterator& operator++()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Incrementing invalid reverse iterator");
            }
            ++inner_iter;
            if (inner_iter != get_rend()) {
                node.add(&inner_iter->iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        reverse_iterator operator++(int)
        {
            auto tmp = *this;
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
                node.add(&inner_iter->iterator_head);
            } else {
                node.add(&container_->end_iterator_head);
            }
            return *this;
        }

        reverse_iterator operator--(int)
        {
            auto tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const reverse_iterator& other) const
        {
            if (!container_ || !other.container_) {
                return false;
            }
            return inner_iter == other.inner_iter;
        }

        bool operator!=(const reverse_iterator& other) const
        {
            return !(*this == other);
        }
    };

    class const_reverse_iterator {
    private:
        using ListIter = typename std::list<TrackedElement>::const_reverse_iterator;
        const SafeList* container_ = nullptr;
        ListIter inner_iter;
        list_head node;
        friend SafeList;

        ListIter get_crend() const
        {
            return container_ ? container_->elements.crend() : ListIter {};
        }

        explicit const_reverse_iterator(const SafeList* container, ListIter it = ListIter {})
            : container_(container), inner_iter(it),
              node(container_ ? (inner_iter != get_crend() ? &inner_iter->iterator_head : &container_->end_iterator_head)
                              : nullptr)
        {}

    public:
        explicit const_reverse_iterator() : container_(nullptr), inner_iter(), node() {}

        const_reverse_iterator(const reverse_iterator& other)
            : container_(other.container_), inner_iter(other.inner_iter)
        {
            if (container_) {
                if (inner_iter != get_crend()) {
                    node.add(&inner_iter->iterator_head);
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
                    node.add(&inner_iter->iterator_head);
                } else {
                    node.add(&container_->end_iterator_head);
                }
            }
        }

        const T& operator*() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_crend()))) {
                LOGF_ABORT("Dereferencing invalid const_reverse iterator");
            }
            return inner_iter->value;
        }

        const T* operator->() const
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                             (!container_ || inner_iter == get_crend()))) {
                LOGF_ABORT("Dereferencing invalid const_reverse iterator");
            }
            return &inner_iter->value;
        }

        const_reverse_iterator& operator=(const const_reverse_iterator& other)
        {
            if (this != &other) {
                container_ = other.container_;
                inner_iter = other.inner_iter;
                if (container_) {
                    if (inner_iter != get_crend()) {
                        node.add(&inner_iter->iterator_head);
                    } else {
                        node.add(&container_->end_iterator_head);
                    }
                }
            }
            return *this;
        }

        const_reverse_iterator& operator++()
        {
            if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !container_)) {
                LOGF_ABORT("Incrementing invalid const_reverse iterator");
            }
            ++inner_iter;
            if (inner_iter != get_crend()) {
                node.add(&inner_iter->iterator_head);
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
                node.add(&inner_iter->iterator_head);
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
            if (!container_ || !other.container_) {
                return false;
            }
            return inner_iter == other.inner_iter;
        }

        bool operator!=(const const_reverse_iterator& other) const
        {
            return !(*this == other);
        }
    };

    SafeList() = default;
    SafeList(std::initializer_list<T> value)
    {
        for (const auto& val : value) {
            push_back(val);
        }
    }
    SafeList(const SafeList& other):elements(other.elements){}
    SafeList(SafeList&& other) : elements(std::forward<std::list<TrackedElement>>(other.elements)) {}

    ~SafeList()
    {
        invalidate_end_iterators();
    }

    void push_back(const T& value)
    {
        elements.emplace_back(value);
    }

    void push_back(T&& value)
    {
        elements.emplace_back(std::forward<T>(value));
    }

    void push_front(const T& value)
    {
        elements.emplace_front(value);
    }

    void push_front(T&& value)
    {
        elements.emplace_front(std::forward<T>(value));
    }

    void pop_front()
    {
        if (elements.empty()) {
            LOGF_ABORT("pop_front called on empty container");
        }
        elements.pop_front();
    }

    void pop_back()
    {
        if (elements.empty()) {
            LOGF_ABORT("pop_back called on empty container");
        }
        elements.pop_back();
    }

    iterator erase(iterator& pos)
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() &&
                         (!pos.container_ || pos.inner_iter == elements.end()))) {
            LOGF_ABORT("Erasing with invalid iterator");
        }
        return iterator(this, elements.erase(pos.inner_iter));
    }

    iterator erase(const_iterator& pos)
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

    iterator insert(const_iterator pos, const T& value)
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !pos.container_)) {
            LOGF_ABORT("Inserting with invalid iterator");
        }
        return iterator(this, elements.insert(pos.inner_iter, value));
    }
    iterator insert( const_iterator pos, T&& value )
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !pos.container_)) {
            LOGF_ABORT("Inserting with invalid iterator");
        }
        return iterator(this, elements.insert(pos.inner_iter, std::forward<T>(value)));
    }
    iterator insert(const_iterator pos, size_t count, const T& value) 
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !pos.container_)) {
            LOGF_ABORT("Inserting with invalid iterator");
        }
        return iterator(this, elements.insert(pos.inner_iter, count, value));
    }
    iterator insert(const_iterator pos, std::initializer_list<T> values)
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !pos.container_)) {
            LOGF_ABORT("Inserting with invalid iterator");
        }
        return iterator(this, elements.insert(pos.inner_iter, values.begin(), values.end()));
    }

    template<typename InputIt, typename std::enable_if<!std::is_same<InputIt, const_iterator>::value, int>::type = 0>
    iterator insert_impl(const_iterator pos, InputIt first, InputIt last)
    {
        return iterator(this, elements.insert(pos.inner_iter, first, last));
    }

    template<typename InputIt, typename std::enable_if<std::is_same<InputIt, const_iterator>::value, int>::type = 0>
    iterator insert_impl(const_iterator pos, InputIt first, InputIt last)
    {
        return iterator(this, elements.insert(pos.inner_iter, first.inner_iter, last.inner_iter));
    }

    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        if (ACE_UNLIKELY(OHOS::Ace::SystemProperties::DetectUseInvalidIterator() && !pos.container_)) {
            LOGF_ABORT("Inserting with invalid iterator");
        }
        return insert_impl(pos, first, last);
    }

    decltype(auto) get_allocator() const noexcept {
        return elements.get_allocator();
    }

    void assign(size_t count, const T& value)
    {
        clear();
        for (int i = 0; i < count; ++i) {
            emplace_back(value);
        }
    }

    void assign(std::initializer_list<T> values)
    {
        assign(values.begin(), values.end());
    }

    template<typename InputIt>
    auto assign(InputIt first, InputIt last)
        -> typename std::enable_if<!std::is_integral<InputIt>::value>::type 
    {
        clear();
        for (; first != last; ++first) {
            emplace_back(*first);
        }
    }

    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args)
    {
        auto iter = elements.emplace(pos.inner_iter,T(std::forward<Args>(args)...));
        return iterator(this, iter);
    }

    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        elements.emplace_back(T(std::forward<Args>(args)...));
    }

    template<typename... Args>
    void emplace_front(Args&&... args)
    {
        elements.emplace_front(T(std::forward<Args>(args)...));
    }

    T& front()
    {
        if (elements.empty()) {
            LOGF_ABORT("SafeList: front() called on empty container");
        }
        return elements.front().value;
    }

    const T& front() const
    {
        if (elements.empty()) {
            LOGF_ABORT("SafeList: front() called on empty container");
        }
        return elements.front().value;
    }

    T& back()
    {
        if (elements.empty()) {
            LOGF_ABORT("SafeList: back() called on empty container");
        }
        return elements.back().value;
    }

    const T& back() const
    {
        if (elements.empty()) {
            LOGF_ABORT("SafeList: back() called on empty container");
        }
        return elements.back().value;
    }

    void clear()
    {
        elements.clear();
    }

    bool empty() const
    {
        return elements.empty();
    }

    int size() const
    {
        return elements.size();
    }

    int max_size() const
    {
        return elements.max_size();
    }

    void sort() {
        elements.sort();
    }

    template<typename Compare>
    void sort(Compare comp)
    {
        auto adapted_comp = [comp](const TrackedElement& a, const TrackedElement& b) {
            return comp(a.value, b.value);
        };
        elements.sort(adapted_comp);
    }

    template<typename BinaryPredicate>
    void unique(BinaryPredicate pred)
    {
        auto adapted_pred = [pred](const TrackedElement& a, const TrackedElement& b) {
            return pred(a.value, b.value);
        };
        elements.unique(adapted_pred);
    }

    void unique()
    {
        elements.unique();
    }

    void reverse() noexcept {
        elements.reverse();
    }

    void remove(const T& value)
    {
        elements.remove_if([&](const TrackedElement& elem) { return elem.value == value; });
    }

    template<typename UnaryPredicate>
    void remove_if(UnaryPredicate pred)
    {
        elements.remove_if([&](const TrackedElement& elem) { return pred(elem.value); });
    }

    void splice(iterator pos, SafeList& other)
    {
        if (other.empty()) {
            return;
        } 
        elements.splice(pos.inner_iter, other.elements);
    }

    void splice(iterator pos, SafeList& other, iterator it)
    {
        elements.splice(pos.inner_iter, other.elements, it.inner_iter);
    }

    void splice(iterator pos, SafeList& other, iterator first, iterator last)
    {
        elements.splice(pos.inner_iter, other.elements, first.inner_iter, last.inner_iter);
    }

    void merge(SafeList& other)
    {
        elements.merge(other.elements);
    }

    template<typename Compare>
    void merge(SafeList& other, Compare comp)
    {
        auto adapted_comp = [comp](const TrackedElement& a, const TrackedElement& b) {
            return comp(a.value, b.value);
        };
        elements.merge(other.elements, adapted_comp);
    }

    void swap(SafeList& other) noexcept {
        elements.swap(other.elements);
    }

    void resize(size_t count)
    {
        elements.resize(count);
    }

    void resize(size_t count, const T& value)
    {
        elements.resize(count,value);
    }

    iterator begin()
    {
        return iterator(this, elements.begin());
    }
    const_iterator begin() const
    {
        return const_iterator(this, elements.cbegin());
    }
    iterator end()
    {
        return iterator(this, elements.end());
    }
    const_iterator end() const
    {
        return const_iterator(this, elements.cend());
    }
    const_iterator cbegin() const
    {
        return const_iterator(this, elements.cbegin());
    }

    const_iterator cend() const
    {
        return const_iterator(this, elements.cend());
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator(this, elements.rbegin());
    }
    reverse_iterator rend()
    {
        return reverse_iterator(this, elements.rend());
    }
    const_reverse_iterator rbegin() const { 
        return crbegin();
    }
    const_reverse_iterator rend() const { 
        return crend();
    }
    const_reverse_iterator crbegin() const { 
        return const_reverse_iterator(this, elements.crbegin());
    }
    const_reverse_iterator crend() const { 
        return const_reverse_iterator(this, elements.crend());
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_CONTAINER_LIST_H