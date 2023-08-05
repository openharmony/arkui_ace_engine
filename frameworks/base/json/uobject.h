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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_JSON_UOBJECT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_JSON_UOBJECT_H

#include <memory>
#include <string>
#include <unordered_map>

namespace OHOS {
enum class ItemType : uint8_t {
    STRING = 0,
    SIZE_T,
    INT32,
    INT64,
    DOUBLE,
    BOOL,
    UOBJECT,
};

class UObject {
public:
    UObject() = default;
    ~UObject() = default;

    void AddItemToObject(const std::string& key, const char* value);
    void AddItemToObject(const std::string& key, const std::string& value);
    void AddItemToObject(const std::string& key, size_t value);
    void AddItemToObject(const std::string& key, int32_t value);
    void AddItemToObject(const std::string& key, int64_t value);
    void AddItemToObject(const std::string& key, double value);
    void AddItemToObject(const std::string& key, bool value);
    void AddItemToObject(const std::string& key, const std::shared_ptr<UObject>& value);

    std::string GetString(const std::string& key) const;
    size_t GetSizeT(const std::string& key) const;
    int32_t GetInt32(const std::string& key) const;
    int64_t GetInt64(const std::string& key) const;
    double GetDouble(const std::string& key) const;
    bool GetBool(const std::string& key) const;
    std::shared_ptr<UObject> GetObject(const std::string& key) const;

    bool Contains(const std::string& key) const;

    void Serialize(char* buffer, int32_t bufferLen);
    void Deserialize(const char* buffer, int32_t bufferLen);

    size_t Hash();

    int32_t EstimateBufferSize();

private:
    void WriteChar(char value);
    void WriteInt32(int32_t value);
    void WriteInt64(int64_t value);
    void WriteSizeT(size_t value);
    void WriteDouble(double value);
    void WriteString(const std::string& value);

    void WriteKV(const std::string& key, const std::string& value);
    void WriteKV(const std::string& key, size_t value);
    void WriteKV(const std::string& key, int32_t value);
    void WriteKV(const std::string& key, int64_t value);
    void WriteKV(const std::string& key, double value);
    void WriteKV(const std::string& key, bool value);
    void WriteObj(const std::string& key, const std::shared_ptr<UObject>& obj);

    char ReadChar();
    int32_t ReadInt32();
    int64_t ReadInt64();
    size_t ReadSizeT();
    double ReadDouble();
    std::string ReadString(int32_t len);
    std::shared_ptr<UObject> ReadObj(int32_t len);

    std::string ReadKey();
    void ReadKV();

    char* buffer_ = nullptr;
    const char* constBuffer_ = nullptr;
    int32_t bufferLen_ = 0;
    int32_t offset_ = 0;
    size_t hashValue_ = 0;
    std::unordered_map<std::string, std::string> stringItems_;
    std::unordered_map<std::string, size_t> sizetItems_;
    std::unordered_map<std::string, int32_t> int32Items_;
    std::unordered_map<std::string, int64_t> int64Items_;
    std::unordered_map<std::string, double> doubleItems_;
    std::unordered_map<std::string, bool> boolItems_;
    std::unordered_map<std::string, std::shared_ptr<UObject>> children_;
};
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_JSON_UOBJECT_H
