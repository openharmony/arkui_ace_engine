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

#pragma once

#include <iostream>
#include <unordered_map>

template<typename Key, typename Value, typename VHash = std::hash<Value>>
class UniqueValuedMap {
private:
    std::unordered_map<Key, Value> keyToValue;
    std::unordered_map<Value, Key, VHash> valueToKey;

public:
    void put(const Key& key, const Value& value)
    {
        // Remove previous mapping for this value (if exists)
        if (valueToKey.count(value)) {
            Key oldKey = valueToKey[value];
            keyToValue.erase(oldKey);
        }

        // Remove previous mapping for this key (if exists)
        if (keyToValue.count(key)) {
            Value oldValue = keyToValue[key];
            valueToKey.erase(oldValue);
        }

        // Add new mappings
        keyToValue[key] = value;
        valueToKey[value] = key;
    }

    std::optional<Value> get(const Key& key) const
    {
        if (!keyToValue.count(key)) {
            return std::nullopt;
        }
        return keyToValue.at(key);
    }

    std::optional<Key> getKey(const Value& value) const
    {
        if (!valueToKey.count(value)) {
            return std::nullopt;
        }
        return valueToKey.at(value);
    }

    void remove(const Key& key)
    {
        if (keyToValue.count(key)) {
            Value value = keyToValue[key];
            keyToValue.erase(key);
            valueToKey.erase(value);
        }
    }

    void removeValue(const Value& value)
    {
        if (valueToKey.count(value)) {
            Key key = valueToKey[value];
            valueToKey.erase(value);
            keyToValue.erase(key);
        }
    }

    bool containsKey(const Key& key) const
    {
        return keyToValue.count(key) > 0;
    }

    bool containsValue(const Value& value) const
    {
        return valueToKey.count(value) > 0;
    }

    size_t size() const
    {
        return keyToValue.size();
    }

    void clear()
    {
        keyToValue.clear();
        valueToKey.clear();
    }
};