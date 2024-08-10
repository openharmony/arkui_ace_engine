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

#include "base/json/uobject.h"

#include "securec.h"
#include "base/log/log_wrapper.h"

namespace OHOS {
namespace {
template<typename T>
size_t HashItem(const std::string& key, const T& value)
{
    return std::hash<std::string>()(key) + std::hash<T>()(value);
}
} // namespace

void UObject::AddItemToObject(const std::string& key, const char* value)
{
    if (value) {
        stringItems_[key] = value;
    }
}

void UObject::AddItemToObject(const std::string& key, const std::string& value)
{
    stringItems_[key] = value;
}

void UObject::AddItemToObject(const std::string& key, size_t value)
{
    sizetItems_[key] = value;
}

void UObject::AddItemToObject(const std::string& key, int32_t value)
{
    int32Items_[key] = value;
}

void UObject::AddItemToObject(const std::string& key, int64_t value)
{
    int64Items_[key] = value;
}

void UObject::AddItemToObject(const std::string& key, double value)
{
    doubleItems_[key] = value;
}

void UObject::AddItemToObject(const std::string& key, bool value)
{
    boolItems_[key] = value;
}

void UObject::AddItemToObject(const std::string& key, const std::shared_ptr<UObject>& value)
{
    if (value) {
        children_[key] = std::move(value);
    }
}

std::string UObject::GetString(const std::string& key) const
{
    auto iter = stringItems_.find(key);
    if (iter != stringItems_.end()) {
        return iter->second;
    }
    return "";
}

size_t UObject::GetSizeT(const std::string& key) const
{
    auto sizetIter = sizetItems_.find(key);
    if (sizetIter != sizetItems_.end()) {
        return sizetIter->second;
    }
    auto doubleIter = doubleItems_.find(key);
    if (doubleIter != doubleItems_.end()) {
        return static_cast<size_t>(doubleIter->second);
    }
    return 0;
}

int32_t UObject::GetInt32(const std::string& key) const
{
    auto int32Iter = int32Items_.find(key);
    if (int32Iter != int32Items_.end()) {
        return int32Iter->second;
    }
    auto doubleIter = doubleItems_.find(key);
    if (doubleIter != doubleItems_.end()) {
        return static_cast<int32_t>(doubleIter->second);
    }
    return 0;
}

int64_t UObject::GetInt64(const std::string& key) const
{
    auto int64Iter = int64Items_.find(key);
    if (int64Iter != int64Items_.end()) {
        return int64Iter->second;
    }
    auto doubleIter = doubleItems_.find(key);
    if (doubleIter != doubleItems_.end()) {
        return static_cast<int64_t>(doubleIter->second);
    }
    return 0;
}

double UObject::GetDouble(const std::string& key) const
{
    auto iter = doubleItems_.find(key);
    if (iter != doubleItems_.end()) {
        return iter->second;
    }
    return 0;
}

bool UObject::GetBool(const std::string& key) const
{
    auto iter = boolItems_.find(key);
    if (iter != boolItems_.end()) {
        return iter->second;
    }
    return false;
}

std::shared_ptr<UObject> UObject::GetObject(const std::string& key) const
{
    auto iter = children_.find(key);
    if (iter != children_.end()) {
        return iter->second;
    }
    return std::make_shared<UObject>();
}

bool UObject::Contains(const std::string& key) const
{
    return stringItems_.count(key) || sizetItems_.count(key) || int32Items_.count(key) || int64Items_.count(key) ||
           doubleItems_.count(key) || boolItems_.count(key) || children_.count(key);
}

void UObject::Serialize(char* buffer, int32_t bufferLen)
{
    if (!buffer) {
        LOGE("|ERROR| buffer is null");
        return;
    }

    buffer_ = buffer;
    bufferLen_ = bufferLen;
    offset_ = 0;

    for (const auto& item : stringItems_) {
        WriteKV(item.first, item.second);
    }
    for (const auto& item : sizetItems_) {
        WriteKV(item.first, item.second);
    }
    for (const auto& item : int32Items_) {
        WriteKV(item.first, item.second);
    }
    for (const auto& item : int64Items_) {
        WriteKV(item.first, item.second);
    }
    for (const auto& item : doubleItems_) {
        WriteKV(item.first, item.second);
    }
    for (const auto& item : boolItems_) {
        WriteKV(item.first, item.second);
    }
    for (const auto& item : children_) {
        WriteObj(item.first, item.second);
    }
}

void UObject::Deserialize(const char* buffer, int32_t bufferLen)
{
    if (!buffer) {
        LOGE("|ERROR| buffer is null");
        return;
    }

    constBuffer_ = buffer;
    offset_ = 0;

    while (offset_ < bufferLen) {
        ReadKV();
    }
}

size_t UObject::Hash()
{
    hashValue_ = 0;

    for (const auto& item : stringItems_) {
        hashValue_ += HashItem(item.first, item.second);
    }
    for (const auto& item : sizetItems_) {
        hashValue_ += HashItem(item.first, item.second);
    }
    for (const auto& item : int32Items_) {
        hashValue_ += HashItem(item.first, item.second);
    }
    for (const auto& item : int64Items_) {
        hashValue_ += HashItem(item.first, item.second);
    }
    for (const auto& item : doubleItems_) {
        hashValue_ += HashItem(item.first, item.second);
    }
    for (const auto& item : boolItems_) {
        hashValue_ += HashItem(item.first, item.second);
    }
    for (const auto& item : children_) {
        hashValue_ += item.second->Hash();
    }

    return hashValue_;
}

int32_t UObject::EstimateBufferSize()
{
    size_t buffsize = 0;

    for (auto& item : stringItems_) {
        buffsize += sizeof(uint8_t) + sizeof(int32_t) + item.first.length() + sizeof(int32_t) + item.second.length();
    }
    for (auto& item : sizetItems_) {
        buffsize += sizeof(uint8_t) + sizeof(int32_t) + item.first.length() + sizeof(size_t);
    }
    for (auto& item : int32Items_) {
        buffsize += sizeof(uint8_t) + sizeof(int32_t) + item.first.length() + sizeof(int32_t);
    }
    for (auto& item : int64Items_) {
        buffsize += sizeof(uint8_t) + sizeof(int32_t) + item.first.length() + sizeof(int64_t);
    }
    for (auto& item : doubleItems_) {
        buffsize += sizeof(uint8_t) + sizeof(int32_t) + item.first.length() + sizeof(double);
    }
    for (auto& item : boolItems_) {
        buffsize += sizeof(uint8_t) + sizeof(int32_t) + item.first.length() + sizeof(bool);
    }
    for (auto& child : children_) {
        buffsize += sizeof(uint8_t) + sizeof(int32_t) + child.first.length() + sizeof(int32_t) +
                    static_cast<size_t>(child.second->EstimateBufferSize());
    }

    return static_cast<int32_t>(buffsize);
}

void UObject::WriteChar(char value)
{
    buffer_[0] = value;
    offset_++;
    buffer_++;
}

void UObject::WriteInt32(int32_t value)
{
    if (memcpy_s(buffer_, bufferLen_ - offset_, &value, sizeof(int32_t)) != 0) {
        LOGE("memcpy overflow.");
        return;
    }
    offset_ += static_cast<int32_t>(sizeof(int32_t));
    buffer_ += sizeof(int32_t);
}

void UObject::WriteSizeT(size_t value)
{
    if (memcpy_s(buffer_, bufferLen_ - offset_, &value, sizeof(size_t)) != 0) {
        LOGE("memcpy overflow.");
        return;
    }
    offset_ += static_cast<int32_t>(sizeof(size_t));
    buffer_ += sizeof(size_t);
}

void UObject::WriteInt64(int64_t value)
{
    if (memcpy_s(buffer_, bufferLen_ - offset_, &value, sizeof(int64_t)) != 0) {
        LOGE("memcpy overflow.");
        return;
    }
    offset_ += static_cast<int32_t>(sizeof(int64_t));
    buffer_ += sizeof(int64_t);
}

void UObject::WriteDouble(double value)
{
    if (memcpy_s(buffer_, bufferLen_ - offset_, &value, sizeof(double)) != 0) {
        LOGE("memcpy overflow.");
        return;
    }
    offset_ += static_cast<int32_t>(sizeof(double));
    buffer_ += sizeof(double);
}

void UObject::WriteString(const std::string& value)
{
    if (value.empty()) {
        return;
    }
    if (memcpy_s(buffer_, bufferLen_ - offset_, value.c_str(), value.length()) != 0) {
        LOGE("memcpy overflow.");
        return;
    }
    offset_ += static_cast<int32_t>(value.length());
    buffer_ += value.length();
}

void UObject::WriteKV(const std::string& key, const std::string& value)
{
    WriteChar(static_cast<char>(ItemType::STRING));
    WriteInt32(key.length());
    WriteString(key);
    WriteInt32(value.length());
    WriteString(value);
}

void UObject::WriteKV(const std::string& key, size_t value)
{
    WriteChar(static_cast<char>(ItemType::SIZE_T));
    WriteInt32(key.length());
    WriteString(key);
    WriteSizeT(value);
}

void UObject::WriteKV(const std::string& key, int32_t value)
{
    WriteChar(static_cast<char>(ItemType::INT32));
    WriteInt32(key.length());
    WriteString(key);
    WriteInt32(value);
}

void UObject::WriteKV(const std::string& key, int64_t value)
{
    WriteChar(static_cast<char>(ItemType::INT64));
    WriteInt32(key.length());
    WriteString(key);
    WriteInt64(value);
}

void UObject::WriteKV(const std::string& key, double value)
{
    WriteChar(static_cast<char>(ItemType::DOUBLE));
    WriteInt32(key.length());
    WriteString(key);
    WriteDouble(value);
}

void UObject::WriteKV(const std::string& key, bool value)
{
    WriteChar(static_cast<char>(ItemType::BOOL));
    WriteInt32(key.length());
    WriteString(key);
    WriteChar(value);
}

void UObject::WriteObj(const std::string& key, const std::shared_ptr<UObject>& obj)
{
    WriteChar(static_cast<char>(ItemType::UOBJECT));
    WriteInt32(key.length());
    WriteString(key);
    int32_t len = obj->EstimateBufferSize();
    WriteInt32(len);
    obj->Serialize(buffer_, len);
    buffer_ += len;
    offset_ += len;
}

char UObject::ReadChar()
{
    char result = constBuffer_[0];
    offset_++;
    constBuffer_++;
    return result;
}

int32_t UObject::ReadInt32()
{
    int32_t result;
    if (memcpy_s(&result, sizeof(int32_t), constBuffer_, sizeof(int32_t)) != 0) {
        LOGE("memcpy overflow.");
        return 0;
    }
    offset_ += static_cast<int32_t>(sizeof(int32_t));
    constBuffer_ += sizeof(int32_t);
    return result;
}

int64_t UObject::ReadInt64()
{
    int64_t result;
    if (memcpy_s(&result, sizeof(int64_t), constBuffer_, sizeof(int64_t)) != 0) {
        LOGE("memcpy overflow.");
        return 0;
    }
    offset_ += static_cast<int32_t>(sizeof(int64_t));
    constBuffer_ += sizeof(int64_t);
    return result;
}

size_t UObject::ReadSizeT()
{
    size_t result;
    if (memcpy_s(&result, sizeof(size_t), constBuffer_, sizeof(size_t)) != 0) {
        LOGE("memcpy overflow.");
        return 0;
    }
    offset_ += static_cast<int32_t>(sizeof(size_t));
    constBuffer_ += sizeof(size_t);
    return result;
}

double UObject::ReadDouble()
{
    double result;
    if (memcpy_s(&result, sizeof(double), constBuffer_, sizeof(double)) != 0) {
        LOGE("memcpy overflow.");
        return 0;
    }
    offset_ += static_cast<int32_t>(sizeof(double));
    constBuffer_ += sizeof(double);
    return result;
}

std::string UObject::ReadString(int32_t len)
{
    std::string result(constBuffer_, len);
    offset_ += len;
    constBuffer_ += len;
    return result;
}

std::shared_ptr<UObject> UObject::ReadObj(int32_t len)
{
    std::shared_ptr<UObject> obj = std::make_shared<UObject>();
    obj->Deserialize(constBuffer_, len);
    offset_ += len;
    constBuffer_ += len;
    return obj;
}

std::string UObject::ReadKey()
{
    int32_t keyLen = ReadInt32();
    std::string key = ReadString(keyLen);
    return key;
}

void UObject::ReadKV()
{
    ItemType type = static_cast<ItemType>(ReadChar());
    if (type == ItemType::STRING) {
        std::string key = ReadKey();
        int32_t valueLen = ReadInt32();
        std::string value = ReadString(valueLen);
        AddItemToObject(key, value);
    } else if (type == ItemType::SIZE_T) {
        std::string key = ReadKey();
        size_t value = ReadSizeT();
        AddItemToObject(key, value);
    } else if (type == ItemType::INT32) {
        std::string key = ReadKey();
        int32_t value = ReadInt32();
        AddItemToObject(key, value);
    } else if (type == ItemType::INT64) {
        std::string key = ReadKey();
        int64_t value = ReadInt64();
        AddItemToObject(key, value);
    } else if (type == ItemType::DOUBLE) {
        std::string key = ReadKey();
        double value = ReadDouble();
        AddItemToObject(key, value);
    } else if (type == ItemType::BOOL) {
        std::string key = ReadKey();
        bool value = ReadChar();
        AddItemToObject(key, value);
    } else if (type == ItemType::UOBJECT) {
        std::string key = ReadKey();
        int32_t objLen = ReadInt32();
        std::shared_ptr<UObject> obj = ReadObj(objLen);
        AddItemToObject(key, obj);
    }
}
} // namespace OHOS
