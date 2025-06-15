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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_UNIQUE_VALUED_MAP_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_UNIQUE_VALUED_MAP_H

#include <functional>
#include <optional>
#include <unordered_map>

namespace OHOS::Ace {
template<typename Key, typename Value, typename VHash = std::hash<Value>>
class UniqueValuedMap {
private:
    std::unordered_map<Key, Value> keyToValue;
    std::unordered_map<Value, Key, VHash> valueToKey;

public:
    void Put(const Key& key, const Value& value)
    {
        // Remove previous mapping for this value (if exists)
        auto valueIt = valueToKey.find(value);
        if (valueIt != valueToKey.end()) {
            keyToValue.erase(valueIt->second);
            valueToKey.erase(valueIt);
        }

        // Remove previous mapping for this key (if exists)
        auto keyIt = keyToValue.find(key);
        if (keyIt != keyToValue.end()) {
            valueToKey.erase(keyIt->second);
            keyToValue.erase(keyIt);
        }

        // Add new mappings
        keyToValue[key] = value;
        valueToKey[value] = key;
    }

    std::optional<Value> Get(const Key& key) const
    {
        auto it = keyToValue.find(key);
        if (it == keyToValue.end()) {
            return std::nullopt;
        }
        return it->second;
    }

    std::optional<Key> GetKey(const Value& value) const
    {
        auto it = valueToKey.find(value);
        if (it == valueToKey.end()) {
            return std::nullopt;
        }
        return it->second;
    }

    void Remove(const Key& key)
    {
        auto it = keyToValue.find(key);
        if (it != keyToValue.end()) {
            valueToKey.erase(it->second);
            keyToValue.erase(it);
        }
    }

    void RemoveValue(const Value& value)
    {
        auto it = valueToKey.find(value);
        if (it != valueToKey.end()) {
            keyToValue.erase(it->second);
            valueToKey.erase(it);
        }
    }

    bool ContainsKey(const Key& key) const
    {
        return keyToValue.find(key) != keyToValue.end();
    }

    bool ContainsValue(const Value& value) const
    {
        return valueToKey.find(value) != valueToKey.end();
    }

    size_t Size() const
    {
        return keyToValue.size();
    }

    void Clear()
    {
        keyToValue.clear();
        valueToKey.clear();
    }

    void RemoveIf(std::function<bool(const Key&, const Value&)>&& pred)
    {
        if (!pred) {
            return;
        }
        for (auto it = keyToValue.begin(); it != keyToValue.end();) {
            if (pred(it->first, it->second)) {
                valueToKey.erase(it->second);
                it = keyToValue.erase(it);
            } else {
                ++it;
            }
        }
    }
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_UNIQUE_VALUED_MAP_H
