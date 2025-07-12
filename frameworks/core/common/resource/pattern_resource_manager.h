/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_PATTERN_REOURCE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_PATTERN_REOURCE_MANAGER_H

#include <functional>
#include <map>
#include <string>
#include <unordered_map>

#include "base/memory/ace_type.h"

#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace {
enum class ValueType {
    UNKNOWN = 0,
    CALDIMENSION,
    COLOR,
    DOUBLE,
    DIMENSION,
    FLOAT,
    FONT_WEIGHT,
    MEDIA,
    STRING,
    U16STRING,
    VECTOR_STRING
};

using VariantValue = std::variant<std::string, std::u16string, float, double, Color, CalcDimension,
    std::vector<std::string>, FontWeight>;

class PropertyValueBase : public virtual AceType {
    DECLARE_ACE_TYPE(PropertyValueBase, AceType);
public:
    virtual ~PropertyValueBase() = default;
    VariantValue& GetValue()
    {
        return value_;
    }
    ValueType GetValueType()
    {
        return valueType_;
    }
    void SetValue(const VariantValue& value)
    {
        value_ = value;
    }
    void SetValueType(const ValueType& valueType)
    {
        valueType_ = valueType;
    }
private:
    ValueType valueType_;
    VariantValue value_;
};

class PatternResourceManager final : public AceType {
    DECLARE_ACE_TYPE(PatternResourceManager, AceType);

public:
    PatternResourceManager() = default;
    ~PatternResourceManager() override = default;

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc);

    void AddResCache(const std::string& key, const std::string& value);

    std::string GetResCacheMapByKey(const std::string& key);

    void RemoveResource(const std::string& key);

    void ReloadResources();

    bool Empty();

    template<typename T>
    void UpdateProperty(std::function<void(const std::string&, const RefPtr<PropertyValueBase>&)>&& propUpdateFunc,
        const std::string& key, const RefPtr<ResourceObject>& resObj)
    {
        auto value = AceType::MakeRefPtr<PropertyValueBase>();
        if constexpr (std::is_same_v<T, std::string>) {
            value->SetValueType(ValueType::STRING);
        } else if (std::is_same_v<T, std::u16string>) {
            value->SetValueType(ValueType::U16STRING);
        } else if constexpr(std::is_same_v<T, Color>) {
            value->SetValueType(ValueType::COLOR);
        } else if constexpr(std::is_same_v<T, double>) {
            value->SetValueType(ValueType::DOUBLE);
        } else if constexpr(std::is_same_v<T, CalcDimension>) {
            value->SetValueType(ValueType::CALDIMENSION);
        } else if constexpr(std::is_same_v<T, float>) {
            value->SetValueType(ValueType::FLOAT);
        } else if constexpr(std::is_same_v<T, std::vector<std::string>>) {
            value->SetValueType(ValueType::VECTOR_STRING);
        }
        ParsePropertyValue(resObj, value);
        if (propUpdateFunc) {
            propUpdateFunc(key, value);
        }
    }

    template<typename T>
    void RegisterResource(std::function<void(const std::string&, const RefPtr<PropertyValueBase>&)>&& propUpdateFunc,
        const std::string& key, const RefPtr<ResourceObject>& resObj, T value)
    {
        auto&& updateFunc = [weakptr = AceType::WeakClaim(this), propUpdateFunc, key](
                                const RefPtr<ResourceObject>& resObj) mutable {
            auto manager = weakptr.Upgrade();
            if (manager) {
                manager->UpdateProperty<T>(std::move(propUpdateFunc), key, resObj);
            }
        };
        AddResource(key, resObj, std::move(updateFunc));
    }

    void ParsePropertyValue(const RefPtr<ResourceObject>& resObj, RefPtr<PropertyValueBase> value);
private:
    struct ResourceUpdater {
        RefPtr<ResourceObject> obj;
        std::function<void(const RefPtr<ResourceObject>&)> updateFunc;
    };
    std::unordered_map<std::string, ResourceUpdater> resMap_;
    std::vector<std::string> resKeyArray_;
    std::unordered_map<std::string, std::map<bool, std::string>> resCacheMap_;
};
}
#endif
