/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_JAVASCRIPT_VALUE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_JAVASCRIPT_VALUE_H

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace OHOS::Ace {
enum class WebHitTestType : int { EDIT = 0, EMAIL, HTTP, HTTP_IMG, IMG, MAP, PHONE, UNKNOWN };

enum class WebJavaScriptBridgeError : int {
    NO_ERROR0 = 0,
    UNKNOWN_OBJECT_ID,
    OBJECT_IS_GONE,
    METHOD_NOT_FOUND,
    ACCESS_TO_OBJECT_GET_CLASS_IS_BLOCKED,
    EXCEPTION_RAISED,
    NON_ASSIGNABLE_TYPES,
    RENDER_FRAME_DELETED
};

union WebJSValueUnion {
    int n;
    double f;
    bool b;
    WebJSValueUnion() {}
    WebJSValueUnion(int value) : n(value) {}
    WebJSValueUnion(double value) : f(value) {}
    WebJSValueUnion(bool value) : b(value) {}
};

class WebJavaScriptValue {
public:
    enum class Type : unsigned char { NONE = 0, BOOLEAN, INTEGER, DOUBLE, STRING, BINARY, DICTIONARY, LIST };

    WebJavaScriptValue() {}
    explicit WebJavaScriptValue(Type type) : type_(type) {}
    explicit WebJavaScriptValue(int value) : type_(Type::INTEGER), data_(value) {}
    explicit WebJavaScriptValue(double value) : type_(Type::DOUBLE), data_(value) {}
    explicit WebJavaScriptValue(bool value) : type_(Type::BOOLEAN), data_(value) {}
    explicit WebJavaScriptValue(const std::string& value) : type_(Type::STRING), str_(value) {}
    WebJavaScriptValue(const char* data, size_t len) : type_(Type::BINARY), str_(data, len) {}
    explicit WebJavaScriptValue(const std::vector<WebJavaScriptValue>& value)
        : type_(Type::LIST), listValue_(value.begin(), value.end())
    {}
    explicit WebJavaScriptValue(const std::map<std::string, WebJavaScriptValue>& value)
        : type_(Type::DICTIONARY), dictionaryValue_(value)
    {}

    explicit WebJavaScriptValue(const WebJavaScriptValue& value) : type_(value.type_)
    {
        switch (type_) {
            case Type::NONE:
                break;
            case Type::BOOLEAN:
                data_.b = value.data_.b;
                break;
            case Type::INTEGER:
                data_.n = value.data_.n;
                break;
            case Type::DOUBLE:
                data_.f = value.data_.f;
                break;
            case Type::STRING:
                str_ = value.str_;
                break;
            case Type::BINARY:
                str_ = value.str_;
                break;
            case Type::LIST:
                listValue_ = value.listValue_;
                break;
            case Type::DICTIONARY:
                dictionaryValue_ = value.dictionaryValue_;
                break;
            default:
                break;
        }
    }

    WebJavaScriptValue(std::vector<WebJavaScriptValue>&& value) : type_(Type::LIST)
    {
        std::swap(listValue_, value);
    }
    WebJavaScriptValue(std::map<std::string, WebJavaScriptValue>&& value) : type_(Type::DICTIONARY)
    {
        std::swap(dictionaryValue_, value);
    }
    WebJavaScriptValue(WebJavaScriptValue&& value)
    {
        *this = std::move(value);
    }

    ~WebJavaScriptValue() = default;

    WebJavaScriptValue& operator=(const WebJavaScriptValue& value)
    {
        SetType(value.type_);
        switch (type_) {
            case Type::NONE:
                break;
            case Type::BOOLEAN:
                data_.b = value.data_.b;
                break;
            case Type::INTEGER:
                data_.n = value.data_.n;
                break;
            case Type::DOUBLE:
                data_.f = value.data_.f;
                break;
            case Type::STRING:
                str_ = value.str_;
                break;
            case Type::BINARY:
                str_ = value.str_;
                break;
            case Type::LIST:
                listValue_ = value.listValue_;
                break;
            case Type::DICTIONARY:
                dictionaryValue_ = value.dictionaryValue_;
                break;
            default:
                break;
        }
        return *this;
    }

    WebJavaScriptValue& operator=(WebJavaScriptValue&& value)
    {
        std::swap(type_, value.type_);
        switch (type_) {
            case Type::NONE:
                break;
            case Type::BOOLEAN:
                std::swap(data_.b, value.data_.b);
                break;
            case Type::INTEGER:
                std::swap(data_.n, value.data_.n);
                break;
            case Type::DOUBLE:
                std::swap(data_.f, value.data_.f);
                break;
            case Type::STRING:
                std::swap(str_, value.str_);
                break;
            case Type::BINARY:
                std::swap(str_, value.str_);
                break;
            case Type::LIST:
                std::swap(listValue_, value.listValue_);
                break;
            case Type::DICTIONARY:
                std::swap(dictionaryValue_, value.dictionaryValue_);
                break;
            default:
                break;
        }
        return *this;
    }

    bool operator==(WebJavaScriptValue& oVal)
    {
        if (type_ != oVal.type_)
            return false;
        switch (type_) {
            case Type::NONE:
                return false;
            case Type::BOOLEAN:
                return data_.b == oVal.data_.b;
            case Type::INTEGER:
                return data_.n == oVal.data_.n;
            case Type::DOUBLE:
                return data_.f == oVal.data_.f;
            case Type::STRING:
                return str_ == oVal.str_;
            case Type::LIST:
                if ((*this).listValue_.size() != oVal.listValue_.size())
                    return false;
                for (size_t i = 0; i < listValue_.size(); ++i) {
                    WebJavaScriptValue& lVal = oVal.listValue_[i];
                    WebJavaScriptValue& rVal = (*this).listValue_[i];
                    if (!(lVal == rVal)) {
                        return false;
                    }
                }
                return true;
            case Type::DICTIONARY:
                if ((*this).dictionaryValue_.size() != oVal.dictionaryValue_.size())
                    return false;
                for (auto item : dictionaryValue_) {
                    WebJavaScriptValue& lVal = oVal.dictionaryValue_[item.first];
                    WebJavaScriptValue& rVal = (*this).dictionaryValue_[item.first];
                    if (!(lVal == rVal)) {
                        return false;
                    }
                }
                return true;
            case Type::BINARY:
                return str_ == oVal.str_;
            default:
                return false;
        }
        return false;
    }

    bool IsNone()
    {
        return GetType() == Type::NONE;
    }

    bool IsBoolean()
    {
        return GetType() == Type::BOOLEAN;
    }

    bool IsString()
    {
        return GetType() == Type::STRING;
    }

    bool IsDouble()
    {
        return GetType() == Type::DOUBLE;
    }

    bool IsINTEGER()
    {
        return GetType() == Type::INTEGER;
    }

    bool IsList()
    {
        return GetType() == Type::LIST;
    }

    bool IsDictionary()
    {
        return GetType() == Type::DICTIONARY;
    }

    bool IsBinary()
    {
        return GetType() == Type::BINARY;
    }

    bool GetBoolean()
    {
        return data_.b;
    }

    void SetBoolean(bool value)
    {
        data_.b = value;
    }

    void SetString(const std::string& value)
    {
        str_ = value;
    }

    std::string GetString()
    {
        return str_;
    }

    void SetDouble(double value)
    {
        data_.f = value;
    }

    double GetDouble()
    {
        return data_.f;
    }

    void SetInt(int value)
    {
        data_.n = value;
    }

    int GetInt()
    {
        return data_.n;
    }

    size_t GetListValueSize()
    {
        return listValue_.size();
    }

    std::vector<WebJavaScriptValue> GetListValue()
    {
        return listValue_;
    }

    WebJavaScriptValue& GetListValue(unsigned int index)
    {
        return listValue_[index];
    }

    void AddListValue(const WebJavaScriptValue& value)
    {
        SetType(Type::LIST);
        listValue_.push_back(value);
    }

    void deleteListValue()
    {
        SetType(Type::LIST);
        listValue_.pop_back();
    }

    size_t GetDictionaryValueSize()
    {
        return dictionaryValue_.size();
    }

    std::vector<std::string> GetDictionaryValueKeys()
    {
        std::vector<std::string> ret;
        for (auto item : dictionaryValue_) {
            ret.push_back(item.first);
        }
        return ret;
    }

    bool HasDictionaryValueKey(const std::string& key)
    {
        return dictionaryValue_.count(key) == 1;
    }

    std::map<std::string, WebJavaScriptValue> GetDictionaryValue()
    {
        return dictionaryValue_;
    }

    WebJavaScriptValue& GetDictionaryValue(const std::string& key)
    {
        return dictionaryValue_[key];
    }

    void AddDictionaryValue(const std::string& key, WebJavaScriptValue& value)
    {
        dictionaryValue_[key] = value;
    }

    void DeleteDictionaryValue(const std::string& key)
    {
        dictionaryValue_.erase(key);
    }

    size_t GetBinaryValueSize()
    {
        return str_.size();
    }

    const char* GetBinaryValue()
    {
        return (const char*)str_.c_str();
    }

    void SetJsonString(const std::string& value)
    {
        json_ = value;
    }

    std::string GetJsonString()
    {
        return json_;
    }

    Type GetType()
    {
        return type_;
    }

    void SetType(Type type)
    {
        type_ = type;
    }

    int error_ = 0;

private:
    Type type_ = Type::NONE;
    WebJSValueUnion data_;
    std::string str_;
    std::string json_;
    std::map<std::string, WebJavaScriptValue> dictionaryValue_;
    std::vector<WebJavaScriptValue> listValue_;
};
using WebJSValue = WebJavaScriptValue;
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_JAVASCRIPT_VALUE_H
