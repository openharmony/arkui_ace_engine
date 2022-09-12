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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_PROPERTY_H

#include <cstdint>
#include <optional>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace::NG {
using PropertyChangeFlag = uint32_t;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_NORMAL = 0;
// Affects self size.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_MEASURE = 1;
// Affects the child position.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_LAYOUT = 1 << 1;
// Affects self position.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_POSITION = 1 << 2;

// Mark self be measure boundary to remeasure.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF = 1 << 3;

// Mark self measure due to child size may change.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_BY_CHILD_REQUEST = 1 << 4;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_RENDER = 1 << 5;
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST = 1 << 6;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_EVENT = 1 << 8;

bool CheckNeedRender(PropertyChangeFlag propertyChangeFlag);

bool CheckNeedRequestMeasureAndLayout(PropertyChangeFlag propertyChangeFlag);

bool CheckNeedRequestParentMeasure(PropertyChangeFlag propertyChangeFlag);

bool CheckMeasureFlag(PropertyChangeFlag propertyChangeFlag);

bool CheckLayoutFlag(PropertyChangeFlag propertyChangeFlag);

bool CheckPositionFlag(PropertyChangeFlag propertyChangeFlag);

bool CheckMeasureSelfFlag(PropertyChangeFlag propertyChangeFlag);

bool CheckUpdateByChildRequest(PropertyChangeFlag propertyChangeFlag);

bool CheckNoChanged(PropertyChangeFlag propertyChangeFlag);

// For XXXProperty Class
#define ACE_DEFINE_PROPERTY_GROUP(group, type)              \
public:                                                     \
    const std::unique_ptr<type>& GetOrCreate##group()       \
    {                                                       \
        if (!prop##group##_) {                              \
            prop##group##_ = std::make_unique<type>();      \
        }                                                   \
        return prop##group##_;                              \
    }                                                       \
    const std::unique_ptr<type>& Get##group() const         \
    {                                                       \
        return prop##group##_;                              \
    }                                                       \
    std::unique_ptr<type> Clone##group() const              \
    {                                                       \
        if (prop##group##_) {                               \
            return std::make_unique<type>(*prop##group##_); \
        }                                                   \
        return nullptr;                                     \
    }                                                       \
    void Reset##group()                                     \
    {                                                       \
        return prop##group##_.reset();                      \
    }                                                       \
                                                            \
protected:                                                    \
    std::unique_ptr<type> prop##group##_;

#define ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_GET(group, name, type) \
public:                                                            \
    std::optional<type> Get##name() const                          \
    {                                                              \
        auto& groupProperty = Get##group();                        \
        if (groupProperty) {                                       \
            return groupProperty->Get##name();                     \
        }                                                          \
        return std::nullopt;                                       \
    }                                                              \
    bool Has##name() const                                         \
    {                                                              \
        auto& groupProperty = Get##group();                        \
        if (groupProperty) {                                       \
            return groupProperty->Has##name();                     \
        }                                                          \
        return false;                                              \
    }                                                              \
    type Get##name##Value(const type& defaultValue) const          \
    {                                                              \
        auto& groupProperty = Get##group();                        \
        if (groupProperty) {                                       \
            if (groupProperty->Has##name()) {                      \
                return groupProperty->Get##name##Value();          \
            }                                                      \
        }                                                          \
        return defaultValue;                                       \
    }

#define ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(group, name, type, changeFlag) \
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_GET(group, name, type)             \
    void Update##name(const type& value)                                   \
    {                                                                      \
        auto& groupProperty = GetOrCreate##group();                        \
        if (groupProperty->Check##name(value)) {                           \
            LOGD("the %{public}s is same, just ignore", #name);            \
            return;                                                        \
        }                                                                  \
        groupProperty->Update##name(value);                                \
        UpdatePropertyChangeFlag(changeFlag);                              \
    }

#define ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_AND_CALLBACK(group, name, type, changeFlag) \
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_GET(group, name, type)                          \
    void Update##name(const type& value)                                                \
    {                                                                                   \
        auto& groupProperty = GetOrCreate##group();                                     \
        if (groupProperty->Check##name(value)) {                                        \
            LOGD("the %{public}s is same, just ignore", #name);                         \
            return;                                                                     \
        }                                                                               \
        groupProperty->Update##name(value);                                             \
        UpdatePropertyChangeFlag(changeFlag);                                           \
        On##name##Update(value);                                                        \
    }

#define ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(group, name, type)  \
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_GET(group, name, type)  \
    void Update##name(const type& value)                        \
    {                                                           \
        auto& groupProperty = GetOrCreate##group();             \
        if (groupProperty->Check##name(value)) {                \
            LOGD("the %{public}s is same, just ignore", #name); \
            return;                                             \
        }                                                       \
        groupProperty->Update##name(value);                     \
        On##name##Update(value);                                \
    }

#define ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_GET(name, type) \
public:                                                        \
    const std::optional<type>& Get##name()                     \
    {                                                          \
        return prop##name##_;                                  \
    }                                                          \
    bool Has##name() const                                     \
    {                                                          \
        return prop##name##_.has_value();                      \
    }                                                          \
    const type& Get##name##Value() const                       \
    {                                                          \
        return prop##name##_.value();                          \
    }                                                          \
    std::optional<type> Clone##name() const                    \
    {                                                          \
        return prop##name##_;                                  \
    }                                                          \
    void Reset##name()                                         \
    {                                                          \
        return prop##name##_.reset();                          \
    }                                                          \
                                                               \
private:                                                       \
    std::optional<type> prop##name##_;

#define ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(name, type, changeFlag) \
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_GET(name, type)             \
public:                                                                \
    void Update##name(const type& value)                               \
    {                                                                  \
        if (prop##name##_.has_value()) {                               \
            if (NearEqual(prop##name##_.value(), value)) {             \
                LOGD("the %{public}s is same, just ignore", #name);    \
                return;                                                \
            }                                                          \
        }                                                              \
        prop##name##_ = value;                                         \
        UpdatePropertyChangeFlag(changeFlag);                          \
    }

#define ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(name, type, changeFlag) \
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_GET(name, type)                                \
public:                                                                                   \
    void Update##name(const type& value)                                                  \
    {                                                                                     \
        if (prop##name##_.has_value()) {                                                  \
            if (NearEqual(prop##name##_.value(), value)) {                                \
                LOGD("the %{public}s is same, just ignore", #name);                       \
                return;                                                                   \
            }                                                                             \
        }                                                                                 \
        prop##name##_ = value;                                                            \
        UpdatePropertyChangeFlag(changeFlag);                                             \
        On##name##Update(value);                                                          \
    }

#define ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(name, type)     \
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_GET(name, type)          \
public:                                                             \
    void Update##name(const type& value)                            \
    {                                                               \
        if (prop##name##_.has_value()) {                            \
            if (NearEqual(prop##name##_.value(), value)) {          \
                LOGD("the %{public}s is same, just ignore", #name); \
                return;                                             \
            }                                                       \
        }                                                           \
        prop##name##_ = value;                                      \
        On##name##Update(value);                                    \
    }

// For Property Group Struct
#define ACE_DEFINE_PROPERTY_GROUP_ITEM(name, type)      \
    std::optional<type> prop##name;                     \
                                                        \
    const std::optional<type>& Get##name() const        \
    {                                                   \
        return prop##name;                              \
    }                                                   \
    bool Has##name() const                              \
    {                                                   \
        return prop##name.has_value();                  \
    }                                                   \
    type Get##name##Value() const                       \
    {                                                   \
        return prop##name.value();                      \
    }                                                   \
    bool Update##name(const type& value)                \
    {                                                   \
        if (prop##name.has_value()) {                   \
            if (NearEqual(prop##name.value(), value)) { \
                return false;                           \
            }                                           \
        }                                               \
        prop##name = value;                             \
        return true;                                    \
    }                                                   \
    bool Check##name(const type& value) const           \
    {                                                   \
        if (!prop##name.has_value()) {                  \
            return false;                               \
        }                                               \
        return NearEqual(prop##name.value(), value);    \
    }

class ACE_EXPORT Property : public virtual AceType {
    DECLARE_ACE_TYPE(Property, AceType);

public:
    Property() = default;

    ~Property() override = default;

    PropertyChangeFlag GetPropertyChangeFlag() const
    {
        return propertyChangeFlag_;
    }

    void CleanDirty()
    {
        propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    }

    void UpdatePropertyChangeFlag(PropertyChangeFlag propertyChangeFlag)
    {
        propertyChangeFlag_ = propertyChangeFlag_ | propertyChangeFlag;
    }

protected:
    PropertyChangeFlag propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    ACE_DISALLOW_COPY_AND_MOVE(Property);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_PROPERTY_H