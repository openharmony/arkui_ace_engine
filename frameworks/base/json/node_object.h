/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_JSON_NODE_OBJECT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_JSON_NODE_OBJECT_H

#include "base/json/json_util.h"
#include "base/json/uobject.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT NodeObject : public JsonValue {
public:
    NodeObject();
    ~NodeObject() override = default;

    bool Contains(const std::string& key) const override;

    bool GetBool(const std::string& key, bool defaultValue = false) const override;
    int32_t GetInt(const std::string& key, int32_t defaultVal = 0) const override;
    uint32_t GetUInt(const std::string& key, uint32_t defaultVal = 0) const override;
    int64_t GetInt64(const std::string& key, int64_t defaultVal = 0) const override;
    double GetDouble(const std::string& key, double defaultVal = 0.0) const override;
    std::string GetString(const std::string& key, const std::string& defaultVal = "") const override;
    std::unique_ptr<JsonValue> GetValue(const std::string& key) const override;
    std::unique_ptr<JsonValue> GetObject(const std::string& key) const override;

    bool Put(const char* key, const char* value) override;
    bool Put(const char* key, size_t value) override;
    bool Put(const char* key, int32_t value) override;
    bool Put(const char* key, int64_t value) override;
    bool Put(const char* key, double value) override;
    bool Put(const char* key, bool value) override;
    bool Put(const char* key, const std::unique_ptr<JsonValue>& value) override;
    bool Put(const char* key, const std::unique_ptr<NodeObject>& value);

    std::string ToString() override;
    void FromString(const std::string& buffer) override;

    size_t Hash();
    int32_t EstimateBufferSize();

    static std::unique_ptr<NodeObject> Create();

private:
    std::shared_ptr<UObject> uobject_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_JSON_NODE_OBJECT_H
