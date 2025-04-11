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

#include "interfaces/inner_api/ui_session/ui_session_json_util.h"

#include "cJSON.h"

namespace OHOS::Ace {

InspectorJsonValue::InspectorJsonValue(JsonObject* object) : object_(object) {}

InspectorJsonValue::InspectorJsonValue(JsonObject* object, bool isRoot) : object_(object), isRoot_(isRoot) {}

InspectorJsonValue::~InspectorJsonValue()
{
    if (object_ != nullptr && isRoot_) {
        cJSON_Delete(object_);
    }
    object_ = nullptr;
}

bool InspectorJsonValue::Contains(const std::string& key) const
{
    return cJSON_HasObjectItem(object_, key.c_str());
}

bool InspectorJsonValue::IsObject() const
{
    return cJSON_IsObject(object_);
}

bool InspectorJsonValue::Put(const char* key, const char* value)
{
    if (!value || !key) {
        return false;
    }

    cJSON* child = cJSON_CreateString(value);
    if (child == nullptr) {
        return false;
    }
    cJSON_AddItemToObject(object_, key, child);
    return true;
}

bool InspectorJsonValue::Put(const char* key, const std::unique_ptr<InspectorJsonValue>& value)
{
    if (!value || !key) {
        return false;
    }
    cJSON* jsonObject = cJSON_Duplicate(value->GetJsonObject(), true);
    if (jsonObject == nullptr) {
        return false;
    }

    cJSON_AddItemToObject(object_, key, jsonObject);
    return true;
}

// add item to array
bool InspectorJsonValue::Put(const std::unique_ptr<InspectorJsonValue>& value)
{
    if (!value) {
        return false;
    }
    cJSON* jsonObject = cJSON_Duplicate(value->GetJsonObject(), true);
    if (jsonObject == nullptr) {
        return false;
    }

    cJSON_AddItemToArray(object_, jsonObject);
    return true;
}

bool InspectorJsonValue::Put(const char* key, size_t value)
{
    if (key == nullptr) {
        return false;
    }

    cJSON* child = cJSON_CreateNumber(static_cast<double>(value));
    if (child == nullptr) {
        return false;
    }
    cJSON_AddItemToObject(object_, key, child);
    return true;
}

bool InspectorJsonValue::Put(const char* key, int32_t value)
{
    if (key == nullptr) {
        return false;
    }

    cJSON* child = cJSON_CreateNumber(static_cast<double>(value));
    if (child == nullptr) {
        return false;
    }
    cJSON_AddItemToObject(object_, key, child);
    return true;
}

bool InspectorJsonValue::Put(const char* key, int64_t value)
{
    return Put(key, static_cast<double>(value));
}

bool InspectorJsonValue::Put(const char* key, double value)
{
    if (key == nullptr) {
        return false;
    }

    cJSON* child = cJSON_CreateNumber(value);
    if (child == nullptr) {
        return false;
    }
    cJSON_AddItemToObject(object_, key, child);
    return true;
}

bool InspectorJsonValue::Put(const char* key, bool value)
{
    if (key == nullptr) {
        return false;
    }

    cJSON* child = cJSON_CreateBool(value);
    if (child == nullptr) {
        return false;
    }
    cJSON_AddItemToObject(object_, key, child);
    return true;
}

bool InspectorJsonValue::Replace(const char* key, const char* value)
{
    if ((value == nullptr) || (key == nullptr)) {
        return false;
    }

    cJSON* child = cJSON_CreateString(value);
    if (child == nullptr) {
        return false;
    }
    if (!cJSON_ReplaceItemInObject(object_, key, child)) {
        cJSON_Delete(child);
        return false;
    }
    return true;
}

const JsonObject* InspectorJsonValue::GetJsonObject() const
{
    return object_;
}

std::string InspectorJsonValue::ToString()
{
    std::string result;
    if (!object_) {
        return result;
    }

    // It is null-terminated.
    char* unformatted = cJSON_PrintUnformatted(object_);
    if (unformatted != nullptr) {
        result = unformatted;
        cJSON_free(unformatted);
    }
    return result;
}

std::shared_ptr<InspectorJsonValue> InspectorJsonUtil::Create(bool isRoot)
{
    return std::make_shared<InspectorJsonValue>(cJSON_CreateObject(), isRoot);
}

std::unique_ptr<InspectorJsonValue> InspectorJsonUtil::CreateObject(bool isRoot)
{
    return std::make_unique<InspectorJsonValue>(cJSON_CreateObject(), isRoot);
}
} // namespace OHOS::Ace