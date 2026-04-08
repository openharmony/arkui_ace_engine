/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "base/json/json_util.h"

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace OHOS::Ace {
namespace {
using MockItems = std::vector<std::pair<std::string, std::string>>;
using MockObjectRefs = std::unordered_map<std::string, std::shared_ptr<JsonValue>>;
using MockArrayRefs = std::vector<std::shared_ptr<JsonValue>>;

struct MockJsonState {
    std::shared_ptr<MockItems> items = std::make_shared<MockItems>();
    size_t index = 0;
    bool isIterator = false;
    bool isArray = false;
    bool isString = false;
    std::string stringValue;
    std::shared_ptr<MockObjectRefs> objectRefs = std::make_shared<MockObjectRefs>();
    std::shared_ptr<MockArrayRefs> arrayRefs = std::make_shared<MockArrayRefs>();
};

std::unordered_map<const JsonValue*, MockJsonState>& JsonState()
{
    static auto* state = new std::unordered_map<const JsonValue*, MockJsonState>();
    return *state;
}

std::recursive_mutex& JsonStateMutex()
{
    static auto* mutex = new std::recursive_mutex();
    return *mutex;
}

MockJsonState DefaultState()
{
    return MockJsonState {};
}

void EnsureState(MockJsonState& state)
{
    if (!state.items) {
        state.items = std::make_shared<MockItems>();
    }
    if (!state.objectRefs) {
        state.objectRefs = std::make_shared<MockObjectRefs>();
    }
    if (!state.arrayRefs) {
        state.arrayRefs = std::make_shared<MockArrayRefs>();
    }
}

void InitStateLocked(const JsonValue* value)
{
    JsonState()[value] = DefaultState();
}

MockJsonState GetStateLocked(const JsonValue* value)
{
    auto it = JsonState().find(value);
    if (it != JsonState().end()) {
        return it->second;
    }
    return DefaultState();
}

void SetStateLocked(const JsonValue* value, const MockJsonState& state)
{
    JsonState()[value] = state;
}

bool IsIteratorValid(const MockJsonState& state)
{
    return state.isIterator && state.items && state.index < state.items->size();
}

void SetIteratorStateLocked(const JsonValue* value, const std::shared_ptr<MockItems>& items, size_t index)
{
    auto state = GetStateLocked(value);
    state.items = items ? items : std::make_shared<MockItems>();
    state.index = index;
    state.isIterator = true;
    state.isArray = false;
    state.isString = false;
    state.stringValue.clear();
    SetStateLocked(value, state);
}

std::string ToStringValue(bool value)
{
    return value ? "true" : "false";
}

std::shared_ptr<JsonValue> ShareCloneLocked(const JsonValue& value)
{
    auto clone = std::make_shared<JsonValue>(nullptr);
    auto source = GetStateLocked(&value);
    SetStateLocked(clone.get(), source);
    return clone;
}

std::unique_ptr<JsonValue> UniqueCloneLocked(const JsonValue& value)
{
    auto clone = std::make_unique<JsonValue>(nullptr);
    auto source = GetStateLocked(&value);
    SetStateLocked(clone.get(), source);
    return clone;
}

std::unique_ptr<JsonValue> MakeStringValueLocked(const std::string& value)
{
    auto json = std::make_unique<JsonValue>(nullptr);
    auto state = GetStateLocked(json.get());
    state.isString = true;
    state.isArray = false;
    state.isIterator = false;
    state.stringValue = value;
    EnsureState(state);
    SetStateLocked(json.get(), state);
    return json;
}

std::shared_ptr<JsonValue> MakeSharedStringValueLocked(const std::string& value)
{
    auto json = std::make_shared<JsonValue>(nullptr);
    auto state = GetStateLocked(json.get());
    state.isString = true;
    state.isArray = false;
    state.isIterator = false;
    state.stringValue = value;
    EnsureState(state);
    SetStateLocked(json.get(), state);
    return json;
}

void UpsertItemLocked(MockJsonState& state, const std::string& key, const std::string& value)
{
    EnsureState(state);
    for (auto& item : *(state.items)) {
        if (item.first == key) {
            item.second = value;
            return;
        }
    }
    state.items->emplace_back(key, value);
}

void AppendArrayItemLocked(MockJsonState& state, const std::shared_ptr<JsonValue>& value)
{
    EnsureState(state);
    state.isArray = true;
    state.isString = false;
    if (value) {
        state.arrayRefs->emplace_back(value);
        state.items->emplace_back("", value->GetString());
    }
}
} // namespace

void MarkAsArrayForMockJson(const JsonValue* value)
{
    if (!value) {
        return;
    }
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(value);
    state.isArray = true;
    state.isString = false;
    EnsureState(state);
    SetStateLocked(value, state);
}

JsonValue::JsonValue(JsonObject* object) : object_(object)
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    InitStateLocked(this);
}

JsonValue::JsonValue(JsonObject* object, bool isRoot) : object_(object), isRoot_(isRoot)
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    InitStateLocked(this);
}

JsonValue::~JsonValue()
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    JsonState().erase(this);
}

bool JsonValue::IsBool() const
{
    return false;
}

bool JsonValue::IsNumber() const
{
    return false;
}

bool JsonValue::IsString() const
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    return state.isString || IsIteratorValid(state);
}

bool JsonValue::IsArray() const
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    return GetStateLocked(this).isArray;
}

bool JsonValue::IsObject() const
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    return !state.isIterator && !state.isArray && !state.isString;
}

bool JsonValue::IsValid() const
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    if (!state.isIterator) {
        return true;
    }
    return IsIteratorValid(state);
}

bool JsonValue::IsNull() const
{
    return !IsValid();
}

bool JsonValue::Contains(const std::string& key) const
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    EnsureState(state);
    if (state.objectRefs->find(key) != state.objectRefs->end()) {
        return true;
    }
    for (const auto& item : *(state.items)) {
        if (item.first == key) {
            return true;
        }
    }
    return false;
}

bool JsonValue::GetBool() const
{
    return false;
}

bool JsonValue::GetBool(const std::string& key, bool defaultValue) const
{
    (void)key;
    return defaultValue;
}

int32_t JsonValue::GetInt() const
{
    return 0;
}

int32_t JsonValue::GetInt(const std::string& key, int32_t defaultVal) const
{
    (void)key;
    return defaultVal;
}

uint32_t JsonValue::GetUInt() const
{
    return 0;
}

uint32_t JsonValue::GetUInt(const std::string& key, uint32_t defaultVal) const
{
    (void)key;
    return defaultVal;
}

int64_t JsonValue::GetInt64() const
{
    return 0;
}

int64_t JsonValue::GetInt64(const std::string& key, int64_t defaultVal) const
{
    (void)key;
    return defaultVal;
}

double JsonValue::GetDouble() const
{
    return 0.0;
}

double JsonValue::GetDouble(const std::string& key, double defaultVal) const
{
    (void)key;
    return defaultVal;
}

std::string JsonValue::GetString() const
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    if (state.isString) {
        return state.stringValue;
    }
    if (IsIteratorValid(state)) {
        return (*(state.items))[state.index].second;
    }
    return {};
}

std::string JsonValue::GetString(const std::string& key, const std::string& defaultVal) const
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    EnsureState(state);
    auto refIter = state.objectRefs->find(key);
    if (refIter != state.objectRefs->end() && refIter->second) {
        return refIter->second->GetString();
    }
    for (const auto& item : *(state.items)) {
        if (item.first == key) {
            return item.second;
        }
    }
    return defaultVal;
}

std::unique_ptr<JsonValue> JsonValue::GetNext() const
{
    auto next = std::make_unique<JsonValue>(nullptr);
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    if (state.isIterator && state.items) {
        SetIteratorStateLocked(next.get(), state.items, state.index + 1);
    } else {
        SetIteratorStateLocked(next.get(), std::make_shared<MockItems>(), 0);
    }
    return next;
}

std::string JsonValue::GetKey() const
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    if (IsIteratorValid(state)) {
        return (*(state.items))[state.index].first;
    }
    return {};
}

std::unique_ptr<JsonValue> JsonValue::GetChild() const
{
    auto child = std::make_unique<JsonValue>(nullptr);
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    if (!state.isIterator && !state.isString && state.items && !state.items->empty()) {
        SetIteratorStateLocked(child.get(), state.items, 0);
    } else {
        SetIteratorStateLocked(child.get(), std::make_shared<MockItems>(), 1);
    }
    return child;
}

std::unique_ptr<JsonValue> JsonValue::GetValue(const std::string& key) const
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    EnsureState(state);

    auto refIter = state.objectRefs->find(key);
    if (refIter != state.objectRefs->end() && refIter->second) {
        return UniqueCloneLocked(*(refIter->second));
    }

    for (const auto& item : *(state.items)) {
        if (item.first == key) {
            return MakeStringValueLocked(item.second);
        }
    }

    auto invalid = std::make_unique<JsonValue>(nullptr);
    SetIteratorStateLocked(invalid.get(), std::make_shared<MockItems>(), 1);
    return invalid;
}

std::unique_ptr<JsonValue> JsonValue::GetObject(const std::string& key) const
{
    auto object = GetValue(key);
    if (object && object->IsValid()) {
        return object;
    }
    auto invalid = std::make_unique<JsonValue>(nullptr);
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    SetIteratorStateLocked(invalid.get(), std::make_shared<MockItems>(), 1);
    return invalid;
}

int32_t JsonValue::GetArraySize() const
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    EnsureState(state);
    if (state.isArray || !state.arrayRefs->empty()) {
        return static_cast<int32_t>(state.arrayRefs->size());
    }
    return static_cast<int32_t>(state.items->size());
}

std::unique_ptr<JsonValue> JsonValue::GetArrayItem(int32_t index) const
{
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    EnsureState(state);
    const auto safeIndex = (index < 0) ? 0 : index;
    if (state.isArray || !state.arrayRefs->empty()) {
        if (safeIndex >= static_cast<int32_t>(state.arrayRefs->size())) {
            auto invalid = std::make_unique<JsonValue>(nullptr);
            SetIteratorStateLocked(invalid.get(), std::make_shared<MockItems>(), 1);
            return invalid;
        }
        auto value = (*(state.arrayRefs))[static_cast<size_t>(safeIndex)];
        if (!value) {
            auto invalid = std::make_unique<JsonValue>(nullptr);
            SetIteratorStateLocked(invalid.get(), std::make_shared<MockItems>(), 1);
            return invalid;
        }
        return UniqueCloneLocked(*value);
    }

    auto item = std::make_unique<JsonValue>(nullptr);
    SetIteratorStateLocked(item.get(), state.items, static_cast<size_t>(safeIndex));
    return item;
}

const JsonObject* JsonValue::GetJsonObject() const
{
    return object_;
}

bool JsonValue::Put(const char* key, const char* value)
{
    if (!key || !value) {
        return false;
    }

    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    EnsureState(state);

    UpsertItemLocked(state, key, value);
    (*(state.objectRefs))[key] = MakeSharedStringValueLocked(value);
    SetStateLocked(this, state);
    return true;
}

bool JsonValue::Put(const char* key, size_t value)
{
    const auto stringValue = std::to_string(value);
    return Put(key, stringValue.c_str());
}

bool JsonValue::Put(const char* key, int32_t value)
{
    const auto stringValue = std::to_string(value);
    return Put(key, stringValue.c_str());
}

bool JsonValue::Put(const char* key, int64_t value)
{
    const auto stringValue = std::to_string(value);
    return Put(key, stringValue.c_str());
}

bool JsonValue::Put(const char* key, double value)
{
    const auto stringValue = std::to_string(value);
    return Put(key, stringValue.c_str());
}

bool JsonValue::Put(const char* key, bool value)
{
    const auto stringValue = ToStringValue(value);
    return Put(key, stringValue.c_str());
}

bool JsonValue::Put(const char* key, const std::unique_ptr<JsonValue>& value)
{
    if (!key || !value) {
        return false;
    }
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    EnsureState(state);
    (*(state.objectRefs))[key] = ShareCloneLocked(*value);
    UpsertItemLocked(state, key, value->GetString());
    SetStateLocked(this, state);
    return true;
}

bool JsonValue::Put(const char* key, const std::shared_ptr<JsonValue>& value)
{
    if (!key || !value) {
        return false;
    }
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    EnsureState(state);
    (*(state.objectRefs))[key] = ShareCloneLocked(*value);
    UpsertItemLocked(state, key, value->GetString());
    SetStateLocked(this, state);
    return true;
}

bool JsonValue::Put(const std::shared_ptr<JsonValue>& value)
{
    if (!value) {
        return false;
    }
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    AppendArrayItemLocked(state, ShareCloneLocked(*value));
    SetStateLocked(this, state);
    return true;
}

bool JsonValue::Put(const std::unique_ptr<JsonValue>& value)
{
    if (!value) {
        return false;
    }
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    AppendArrayItemLocked(state, ShareCloneLocked(*value));
    SetStateLocked(this, state);
    return true;
}

bool JsonValue::PutFixedAttr(const char* key, const char* value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr)
{
    (void)filter;
    (void)attr;
    return Put(key, value);
}

bool JsonValue::PutFixedAttr(const char* key, size_t value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr)
{
    (void)filter;
    (void)attr;
    return Put(key, value);
}

bool JsonValue::PutFixedAttr(const char* key, int32_t value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr)
{
    (void)filter;
    (void)attr;
    return Put(key, value);
}

bool JsonValue::PutFixedAttr(const char* key, int64_t value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr)
{
    (void)filter;
    (void)attr;
    return Put(key, value);
}

bool JsonValue::PutFixedAttr(const char* key, double value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr)
{
    (void)filter;
    (void)attr;
    return Put(key, value);
}

bool JsonValue::PutFixedAttr(const char* key, bool value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr)
{
    (void)filter;
    (void)attr;
    return Put(key, value);
}

bool JsonValue::PutFixedAttr(
    const char* key, const std::unique_ptr<JsonValue>& value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr)
{
    (void)filter;
    (void)attr;
    return Put(key, value);
}

JsonObject* JsonValue::ReleaseJsonObject()
{
    auto object = object_;
    object_ = nullptr;
    return object;
}

bool JsonValue::PutRef(const char* key, std::unique_ptr<JsonValue>&& value)
{
    if (!value) {
        return false;
    }
    return Put(key, value);
}

bool JsonValue::PutRef(std::unique_ptr<JsonValue>&& value)
{
    if (!value) {
        return false;
    }
    return Put(value);
}

bool JsonValue::PutRef(std::shared_ptr<JsonValue>&& value)
{
    if (!value) {
        return false;
    }
    return Put(value);
}

bool JsonValue::Replace(const char* key, const char* value)
{
    return Put(key, value);
}

bool JsonValue::Replace(const char* key, int32_t value)
{
    return Put(key, value);
}

bool JsonValue::Replace(const char* key, const std::unique_ptr<JsonValue>& value)
{
    return Put(key, value);
}

bool JsonValue::Replace(const char* key, bool value)
{
    return Put(key, value);
}

bool JsonValue::Replace(const char* key, double value)
{
    return Put(key, value);
}

bool JsonValue::Delete(const char* key)
{
    if (!key) {
        return false;
    }
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    auto state = GetStateLocked(this);
    EnsureState(state);
    state.objectRefs->erase(key);
    auto& items = *(state.items);
    for (auto iter = items.begin(); iter != items.end(); ++iter) {
        if (iter->first == key) {
            items.erase(iter);
            SetStateLocked(this, state);
            return true;
        }
    }
    SetStateLocked(this, state);
    return false;
}

std::string JsonValue::ToString()
{
    return "{}";
}

std::unique_ptr<JsonValue> JsonValue::Duplicate()
{
    auto duplicated = std::make_unique<JsonValue>(nullptr);
    std::lock_guard<std::recursive_mutex> lock(JsonStateMutex());
    SetStateLocked(duplicated.get(), GetStateLocked(this));
    return duplicated;
}
} // namespace OHOS::Ace
