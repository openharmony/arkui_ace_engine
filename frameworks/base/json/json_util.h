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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_JSON_JSON_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_JSON_JSON_UTIL_H

#include <memory>
#include <string>

#include "base/utils/macros.h"
#include "core/components_ng/base/inspector_filter.h"
#include "interfaces/inner_api/ace/serializeable_object.h"

struct cJSON;

namespace OHOS::Ace {

using JsonObject = cJSON;

class ACE_FORCE_EXPORT JsonValue : public SerializeableObject {
public:
    JsonValue() = default;
    explicit JsonValue(JsonObject* object);
    JsonValue(JsonObject* object, bool isRoot);
    ~JsonValue() override;

    // check functions
    bool IsBool() const;
    bool IsNumber() const;
    bool IsString() const;
    bool IsArray() const;
    bool IsObject() const;
    bool IsValid() const;
    bool IsNull() const;
    bool Contains(const std::string& key) const override;

    // get functions
    bool GetBool() const;
    bool GetBool(const std::string& key, bool defaultValue = false) const override;
    int32_t GetInt() const;
    int32_t GetInt(const std::string& key, int32_t defaultVal = 0) const override;
    uint32_t GetUInt() const;
    uint32_t GetUInt(const std::string& key, uint32_t defaultVal = 0) const override;
    int64_t GetInt64() const;
    int64_t GetInt64(const std::string& key, int64_t defaultVal = 0) const override;
    double GetDouble() const;
    double GetDouble(const std::string& key, double defaultVal = 0.0) const override;
    std::string GetString() const;
    std::string GetString(const std::string& key, const std::string& defaultVal = "") const override;

    std::unique_ptr<JsonValue> GetNext() const;
    std::unique_ptr<JsonValue> GetChild() const;
    std::string GetKey() const;
    virtual std::unique_ptr<JsonValue> GetValue(const std::string& key) const;
    virtual std::unique_ptr<JsonValue> GetObject(const std::string& key) const;
    int32_t GetArraySize() const;
    std::unique_ptr<JsonValue> GetArrayItem(int32_t index) const;
    const JsonObject* GetJsonObject() const;

    // put functions
    bool Put(const char* key, const char* value) override;
    bool Put(const char* key, size_t value) override;
    bool Put(const char* key, int32_t value) override;
    bool Put(const char* key, int64_t value) override;
    bool Put(const char* key, double value) override;
    bool Put(const char* key, bool value) override;
    virtual bool Put(const char* key, const std::unique_ptr<JsonValue>& value);
    bool Put(const std::unique_ptr<JsonValue>& value);

    bool PutFixedAttr(const char* key, const char* value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr);
    bool PutFixedAttr(const char* key, size_t value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr);
    bool PutFixedAttr(const char* key, int32_t value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr);
    bool PutFixedAttr(const char* key, int64_t value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr);
    bool PutFixedAttr(const char* key, double value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr);
    bool PutFixedAttr(const char* key, bool value, const NG::InspectorFilter& filter, NG::FixedAttrBit attr);
    virtual bool PutFixedAttr(const char* key, const std::unique_ptr<JsonValue>& value,
        const NG::InspectorFilter& filter, NG::FixedAttrBit attr);

    bool PutExtAttr(const char* key, const char* value, const NG::InspectorFilter& filter);
    bool PutExtAttr(const char* key, size_t value, const NG::InspectorFilter& filter);
    bool PutExtAttr(const char* key, int32_t value, const NG::InspectorFilter& filter);
    bool PutExtAttr(const char* key, int64_t value, const NG::InspectorFilter& filter);
    bool PutExtAttr(const char* key, double value, const NG::InspectorFilter& filter);
    bool PutExtAttr(const char* key, bool value, const NG::InspectorFilter& filter);
    virtual bool PutExtAttr(const char* key, const std::unique_ptr<JsonValue>& value,
        const NG::InspectorFilter& filter);

    JsonObject* ReleaseJsonObject();
    bool PutRef(const char* key, std::unique_ptr<JsonValue>&& value);
    bool PutRef(std::unique_ptr<JsonValue>&& value);

    // replace functions
    bool Replace(const char* key, const char* value);
    bool Replace(const char* key, int32_t value);
    bool Replace(const char* key, const std::unique_ptr<JsonValue>& value);
    bool Replace(const char* key, bool value);
    bool Replace(const char* key, double value);

    // delete functions
    bool Delete(const char* key);

    // serialize
    std::string ToString() override;

private:
    JsonObject* object_ = nullptr;
    bool isRoot_ = false;
};

class ACE_FORCE_EXPORT JsonUtil final {
public:
    JsonUtil() = delete;
    ~JsonUtil() = delete;
    static std::unique_ptr<JsonValue> ParseJsonData(const char* data, const char** parseEnd = nullptr);
    static std::unique_ptr<JsonValue> ParseJsonString(const std::string& content, const char** parseEnd = nullptr);
    static std::unique_ptr<JsonValue> Create(bool isRoot = true);
    static std::unique_ptr<JsonValue> CreateArray(bool isRoot = true);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_JSON_JSON_UTIL_H
