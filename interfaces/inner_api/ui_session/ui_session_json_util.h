/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_UI_SESSION_JSON_UTIL_H
#define FOUNDATION_ACE_INTERFACE_UI_SESSION_JSON_UTIL_H

#include <memory>
#include <string>

#include "base/utils/macros.h"

struct cJSON;

namespace OHOS::Ace {

using JsonObject = cJSON;

class ACE_FORCE_EXPORT InspectorJsonValue {
public:
    InspectorJsonValue() = default;
    explicit InspectorJsonValue(JsonObject* object);
    InspectorJsonValue(JsonObject* object, bool isRoot);
    ~InspectorJsonValue();
    // put functions
    bool Put(const char* key, const char* value);
    bool Put(const char* key, size_t value);
    bool Put(const char* key, int32_t value);
    bool Put(const char* key, int64_t value);
    bool Put(const char* key, double value);
    bool Put(const char* key, bool value);
    bool Put(const char* key, const std::unique_ptr<InspectorJsonValue>& value);
    bool Put(const std::unique_ptr<InspectorJsonValue>& value);
    bool Replace(const char* key, const char* value);
    // serialize
    std::string ToString();
    bool IsObject() const;
    bool Contains(const std::string& key) const;
    const JsonObject* GetJsonObject() const;

private:
    JsonObject* object_ = nullptr;
    bool isRoot_ = false;
};

class ACE_FORCE_EXPORT InspectorJsonUtil final {
public:
    InspectorJsonUtil() = delete;
    ~InspectorJsonUtil() = delete;
    static std::shared_ptr<InspectorJsonValue> Create(bool isRoot = true);
    static std::shared_ptr<InspectorJsonValue> CreateArray(bool isRoot = true);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACE_UI_SESSION_JSON_UTIL_H