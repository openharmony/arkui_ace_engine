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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_SERIALIZEABLE_OBJECT_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_SERIALIZEABLE_OBJECT_H

#include <list>
#include <memory>
#include <string>

#include "macros.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT SerializeableObject {
public:
    SerializeableObject() = default;
    virtual ~SerializeableObject() = default;

    virtual bool Contains(const std::string& key) const = 0;

    virtual bool GetBool(const std::string& key, bool defaultValue = false) const = 0;
    virtual int32_t GetInt(const std::string& key, int32_t defaultVal = 0) const = 0;
    virtual uint32_t GetUInt(const std::string& key, uint32_t defaultVal = 0) const = 0;
    virtual int64_t GetInt64(const std::string& key, int64_t defaultVal = 0) const = 0;
    virtual double GetDouble(const std::string& key, double defaultVal = 0.0) const = 0;
    virtual std::string GetString(const std::string& key, const std::string& defaultVal = "") const = 0;

    virtual bool Put(const char* key, const char* value) = 0;
    virtual bool Put(const char* key, size_t value) = 0;
    virtual bool Put(const char* key, int32_t value) = 0;
    virtual bool Put(const char* key, int64_t value) = 0;
    virtual bool Put(const char* key, double value) = 0;
    virtual bool Put(const char* key, bool value) = 0;

    virtual std::string ToString() = 0;

    virtual void FromString(const std::string& str) {}

    static std::unique_ptr<SerializeableObject> CreateNodeObject();
};

using SerializeableObjectArray = std::list<std::unique_ptr<SerializeableObject>>;
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_SERIALIZEABLE_OBJECT_H
