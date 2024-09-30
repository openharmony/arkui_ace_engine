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

#include "base/json/node_object.h"

#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace {
std::shared_ptr<UObject> FromJsonObject(const std::unique_ptr<JsonValue>& json)
{
    if (!json->IsObject()) {
        return nullptr;
    }

    auto object = std::make_shared<UObject>();
    auto jsonSize = json->GetArraySize();

    for (auto i = 0; i < jsonSize; ++i) {
        auto item = json->GetArrayItem(i);
        if (item->IsString()) {
            object->AddItemToObject(item->GetKey(), item->GetString());
        } else if (item->IsBool()) {
            object->AddItemToObject(item->GetKey(), item->GetBool());
        } else if (item->IsNumber()) {
            object->AddItemToObject(item->GetKey(), item->GetDouble());
        } else if (item->IsObject()) {
            object->AddItemToObject(item->GetKey(), FromJsonObject(item));
        } else {
            LOGE("UITree |ERROR| not match key=%{public}s", item->GetKey().c_str());
        }
    }

    return object;
}
} // namespace

NodeObject::NodeObject() : uobject_(std::make_shared<UObject>()) {}

bool NodeObject::Contains(const std::string& key) const
{
    CHECK_NULL_RETURN(uobject_, false);
    return uobject_->Contains(key);
}

bool NodeObject::GetBool(const std::string& key, bool defaultValue) const
{
    CHECK_NULL_RETURN(uobject_, false);
    if (Contains(key)) {
        return uobject_->GetBool(key);
    }
    return defaultValue;
}

int32_t NodeObject::GetInt(const std::string& key, int32_t defaultVal) const
{
    CHECK_NULL_RETURN(uobject_, 0);
    if (Contains(key)) {
        return uobject_->GetInt32(key);
    }
    return defaultVal;
}

uint32_t NodeObject::GetUInt(const std::string& key, uint32_t defaultVal) const
{
    CHECK_NULL_RETURN(uobject_, 0);
    if (Contains(key)) {
        return uobject_->GetInt32(key);
    }
    return defaultVal;
}

int64_t NodeObject::GetInt64(const std::string& key, int64_t defaultVal) const
{
    CHECK_NULL_RETURN(uobject_, 0);
    if (Contains(key)) {
        return uobject_->GetInt64(key);
    }
    return defaultVal;
}

double NodeObject::GetDouble(const std::string& key, double defaultVal) const
{
    CHECK_NULL_RETURN(uobject_, 0);
    if (Contains(key)) {
        return uobject_->GetDouble(key);
    }
    return defaultVal;
}

std::string NodeObject::GetString(const std::string& key, const std::string& defaultVal) const
{
    CHECK_NULL_RETURN(uobject_, "");
    if (Contains(key)) {
        return uobject_->GetString(key);
    }
    return defaultVal;
}

std::unique_ptr<JsonValue> NodeObject::GetValue(const std::string& key) const
{
    CHECK_NULL_RETURN(uobject_, std::make_unique<NodeObject>());
    if (Contains(key)) {
        auto object = std::make_unique<NodeObject>();
        object->uobject_ = uobject_->GetObject(key);
        return object;
    }
    return std::make_unique<NodeObject>();
}

std::unique_ptr<JsonValue> NodeObject::GetObject(const std::string& key) const
{
    return GetValue(key);
}

bool NodeObject::Put(const char* key, const char* value)
{
    CHECK_NULL_RETURN(uobject_, false);
    if (!value || !key) {
        return false;
    }

    uobject_->AddItemToObject(std::string(key), std::string(value));
    return true;
}

bool NodeObject::Put(const char* key, size_t value)
{
    CHECK_NULL_RETURN(uobject_, false);
    if (!key) {
        return false;
    }

    uobject_->AddItemToObject(std::string(key), value);
    return true;
}

bool NodeObject::Put(const char* key, int32_t value)
{
    CHECK_NULL_RETURN(uobject_, false);
    if (!key) {
        return false;
    }

    uobject_->AddItemToObject(std::string(key), value);
    return true;
}

bool NodeObject::Put(const char* key, int64_t value)
{
    CHECK_NULL_RETURN(uobject_, false);
    if (!key) {
        return false;
    }

    uobject_->AddItemToObject(std::string(key), value);
    return true;
}

bool NodeObject::Put(const char* key, double value)
{
    CHECK_NULL_RETURN(uobject_, false);
    if (!key) {
        return false;
    }

    uobject_->AddItemToObject(std::string(key), value);
    return true;
}

bool NodeObject::Put(const char* key, bool value)
{
    CHECK_NULL_RETURN(uobject_, false);
    if (!key) {
        return false;
    }

    uobject_->AddItemToObject(std::string(key), value);
    return true;
}

bool NodeObject::Put(const char* key, const std::unique_ptr<JsonValue>& value)
{
    CHECK_NULL_RETURN(uobject_, false);
    if (!value || !key) {
        return false;
    }

    uobject_->AddItemToObject(std::string(key), FromJsonObject(value));
    return true;
}

bool NodeObject::Put(const char* key, const std::unique_ptr<NodeObject>& value)
{
    CHECK_NULL_RETURN(uobject_, false);
    if (!value || !key) {
        return false;
    }

    uobject_->AddItemToObject(std::string(key), value->uobject_);
    return true;
}

std::string NodeObject::ToString()
{
    CHECK_NULL_RETURN(uobject_, "");
    int32_t objectSize = uobject_->EstimateBufferSize();
    std::string buffer("", objectSize);
    uobject_->Serialize(buffer.data(), objectSize);
    return buffer;
}

void NodeObject::FromString(const std::string& buffer)
{
    CHECK_NULL_VOID(uobject_);
    uobject_->Deserialize(buffer.data(), buffer.size());
}

size_t NodeObject::Hash()
{
    CHECK_NULL_RETURN(uobject_, 0);
    return uobject_->Hash();
}

int32_t NodeObject::EstimateBufferSize()
{
    CHECK_NULL_RETURN(uobject_, 0);
    return uobject_->EstimateBufferSize();
}

std::unique_ptr<NodeObject> NodeObject::Create()
{
    return std::make_unique<NodeObject>();
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateNodeObject()
{
    return new NodeObject();
}
} // namespace OHOS::Ace
