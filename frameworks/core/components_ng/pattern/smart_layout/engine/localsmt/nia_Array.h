/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#pragma once
#include <cstring>
#include <random>
#include <vector>
class Array {
public:
    std::vector<int32_t> array;
    std::vector<int32_t> indexInArray;
    int32_t arraySize;
    int32_t arrayCapacity;

    Array() : array({}), indexInArray({}), arraySize(0), arrayCapacity(0) {}

    explicit Array(int32_t capacity)
        : array(capacity, -1), indexInArray(capacity, -1), arraySize(0), arrayCapacity(capacity)
    {}

    Array(const Array& prototype)
        : array(prototype.array), indexInArray(prototype.indexInArray), arraySize(prototype.arraySize),
          arrayCapacity(prototype.arrayCapacity)
    {}

    Array& operator=(const Array& other)
    {
        Array temp(other); // 拷贝构造
        swap(*this, temp); // 交换（不抛出异常）
        return *this;
    }

    void swap(Array& first, Array& second) noexcept
    {
        using std::swap;
        swap(first.array, second.array);
        swap(first.indexInArray, second.indexInArray);
        swap(first.arraySize, second.arraySize);
        swap(first.arrayCapacity, second.arrayCapacity);
    }

    ~Array() = default;

    void Clear()
    {
        for (int32_t i = 0; i < arraySize; i++) {
            indexInArray[array[i]] = -1;
        }
        arraySize = 0;
    }

    void InsertElement(int32_t e)
    {
        if (IsInArray(e)) {
            return;
        }
        if (arraySize < arrayCapacity) {
            array[arraySize] = e;
            indexInArray[e] = arraySize;
            arraySize++;
        }
    }

    void DeleteElement(int32_t e)
    {
        if (!IsInArray(e)) {
            return;
        }
        arraySize--;
        int32_t last_e = array[arraySize];
        int32_t e_pos = indexInArray[e];
        array[e_pos] = last_e;
        indexInArray[last_e] = e_pos;
        indexInArray[e] = -1;
    }

    int32_t GetElementByIndex(int32_t index)
    {
        return array[index];
    }

    bool IsInArray(int32_t e) const
    {
        return indexInArray[e] != -1;
    }

    bool IsEmpty() const
    {
        return arraySize == 0;
    }

    int32_t GetCapacity() const
    {
        return arrayCapacity;
    }

    int32_t GetSize() const
    {
        return arraySize;
    }
};