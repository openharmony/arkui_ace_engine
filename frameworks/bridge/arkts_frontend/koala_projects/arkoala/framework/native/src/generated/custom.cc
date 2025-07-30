/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "DeserializerBase.h"

#include <algorithm>
#include <vector>

struct MyDeserializer : CustomDeserializer {
    std::vector<std::string> supported;
    MyDeserializer() {
        supported.push_back("Function");
        supported.push_back("Resource");
        DeserializerBase::registerCustomDeserializer(this);
    }
    virtual bool supports(const std::string& kind) {
        return std::find(supported.begin(), supported.end(), kind) != supported.end();
    }
    virtual InteropCustomObject deserialize(DeserializerBase* deserializer, const std::string& kind) {
        InteropString value = deserializer->readString();
        (void)value;
        InteropCustomObject result;
        strcpy(result.kind, "NativeError");
        result.id = 0;
        strcat(result.kind, kind.c_str());
        return result;
    }

};
MyDeserializer deserilizer;

struct DateDeserializer final : CustomDeserializer {
    const std::vector<std::string> supported = {"Date"};
    DateDeserializer() {
        DeserializerBase::registerCustomDeserializer(this);
    }
    virtual bool supports(const std::string& kind) {
        return std::find(supported.begin(), supported.end(), kind) != supported.end();
    }
    virtual InteropCustomObject deserialize(DeserializerBase* deserializer, const std::string& kind) {
        InteropCustomObject result = {};
        result.string = deserializer->readString();
        strncpy(result.kind, kind.c_str(), sizeof(result.kind) - 1);
        return result;
    }
};
DateDeserializer dateDeserializer;