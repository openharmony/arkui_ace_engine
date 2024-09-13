/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
// Mark self, parent, children to remeasure.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_MEASURE = 1;
// Mark self to reLayout.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_LAYOUT = 1 << 1;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_DIFF = 1 << 2;

// Mark self to remeasure.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF = 1 << 3;

// Mark self and parent to remeasure.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT = 1 << 4;

// Mark self remeasure due to child size may change, which may mark parent, self and children to remeasure.
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_BY_CHILD_REQUEST = 1 << 5;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_RENDER = 1 << 6;
inline constexpr PropertyChangeFlag PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST = 1 << 7;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_EVENT = 1 << 8;

inline constexpr PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD = 1 << 9;

using FrameNodeChangeInfoFlag = uint32_t;
inline constexpr FrameNodeChangeInfoFlag FRAME_NODE_CHANGE_INFO_NONE = 0;
inline constexpr FrameNodeChangeInfoFlag FRAME_NODE_CHANGE_START_SCROLL = 1 << 1;
inline constexpr FrameNodeChangeInfoFlag FRAME_NODE_CHANGE_END_SCROLL = 1 << 2;
inline constexpr FrameNodeChangeInfoFlag FRAME_NODE_CHANGE_START_ANIMATION = 1 << 3;
inline constexpr FrameNodeChangeInfoFlag FRAME_NODE_CHANGE_GEOMETRY_CHANGE = 1 << 4;
inline constexpr FrameNodeChangeInfoFlag FRAME_NODE_CHANGE_TRANSFORM_CHANGE = 1 << 5;
inline constexpr FrameNodeChangeInfoFlag FRAME_NODE_CHANGE_TRANSITION_START = 1 << 6;

inline bool CheckNeedMakePropertyDiff(PropertyChangeFlag flag)
{
    return (flag & PROPERTY_UPDATE_DIFF) == PROPERTY_UPDATE_DIFF;
}

bool CheckNeedRender(PropertyChangeFlag propertyChangeFlag);

bool CheckNeedRequestMeasureAndLayout(PropertyChangeFlag propertyChangeFlag);

bool CheckNeedRequestParentMeasure(PropertyChangeFlag propertyChangeFlag);

bool CheckNeedMeasure(PropertyChangeFlag propertyChangeFlag);

bool CheckNeedLayout(PropertyChangeFlag propertyChangeFlag);

bool CheckMeasureFlag(PropertyChangeFlag propertyChangeFlag);

bool CheckForceParentMeasureFlag(PropertyChangeFlag propertyChangeFlag);

bool CheckLayoutFlag(PropertyChangeFlag propertyChangeFlag);

bool CheckMeasureSelfFlag(PropertyChangeFlag propertyChangeFlag);

bool CheckMeasureSelfAndParentFlag(PropertyChangeFlag propertyChangeFlag);

bool CheckMeasureSelfAndChildFlag(PropertyChangeFlag propertyChangeFlag);

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
protected:                                                  \
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
    }                                                              \
    void Reset##name()                                             \
    {                                                              \
        auto& groupProperty = Get##group();                        \
        if (groupProperty) {                                       \
            groupProperty->Reset##name();                          \
        }                                                          \
    }

// For different members of the same type, such as the same foreground and background color types, but the interface
// names provided to the outside world need to be different.
#define ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM_GET(group, groupItem, name, type) \
public:                                                                            \
    std::optional<type> Get##name() const                                          \
    {                                                                              \
        auto& groupProperty = Get##group();                                        \
        if (groupProperty) {                                                       \
            return groupProperty->Get##groupItem();                                \
        }                                                                          \
        return std::nullopt;                                                       \
    }                                                                              \
    bool Has##name() const                                                         \
    {                                                                              \
        auto& groupProperty = Get##group();                                        \
        if (groupProperty) {                                                       \
            return groupProperty->Has##groupItem();                                \
        }                                                                          \
        return false;                                                              \
    }                                                                              \
    type Get##name##Value(const type& defaultValue) const                          \
    {                                                                              \
        auto& groupProperty = Get##group();                                        \
        if (groupProperty) {                                                       \
            if (groupProperty->Has##groupItem()) {                                 \
                return groupProperty->Get##groupItem##Value();                     \
            }                                                                      \
        }                                                                          \
        return defaultValue;                                                       \
    }

#define ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(group, name, type, changeFlag) \
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_GET(group, name, type)             \
    void Update##name(const type& value)                                   \
    {                                                                      \
        auto& groupProperty = GetOrCreate##group();                        \
        if (groupProperty->Check##name(value)) {                           \
            return;                                                        \
        }                                                                  \
        groupProperty->Update##name(value);                                \
        UpdatePropertyChangeFlag(changeFlag);                              \
    }

#define ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(group, groupItem, name, type, changeFlag) \
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM_GET(group, groupItem, name, type)             \
    void Update##name(const type& value)                                                   \
    {                                                                                      \
        auto& groupProperty = GetOrCreate##group();                                        \
        if (groupProperty->Check##groupItem(value)) {                                      \
            return;                                                                        \
        }                                                                                  \
        groupProperty->Update##groupItem(value);                                           \
        UpdatePropertyChangeFlag(changeFlag);                                              \
    }

#define ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_AND_CALLBACK(group, name, type, changeFlag) \
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_GET(group, name, type)                          \
    void Update##name(const type& value)                                                \
    {                                                                                   \
        auto& groupProperty = GetOrCreate##group();                                     \
        if (groupProperty->Check##name(value)) {                                        \
            return;                                                                     \
        }                                                                               \
        groupProperty->Update##name(value);                                             \
        UpdatePropertyChangeFlag(changeFlag);                                           \
        On##name##Update(value);                                                        \
    }

#define ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(group, name, type) \
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_GET(group, name, type) \
    void Update##name(const type& value)                       \
    {                                                          \
        auto& groupProperty = GetOrCreate##group();            \
        if (groupProperty->Check##name(value)) {               \
            return;                                            \
        }                                                      \
        groupProperty->Update##name(value);                    \
        On##name##Update(value);                               \
    }

#define ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_GET(name, type)   \
public:                                                          \
    const std::optional<type>& Get##name() const                 \
    {                                                            \
        return prop##name##_;                                    \
    }                                                            \
    bool Has##name() const                                       \
    {                                                            \
        return prop##name##_.has_value();                        \
    }                                                            \
    const type& Get##name##Value() const                         \
    {                                                            \
        return prop##name##_.value();                            \
    }                                                            \
    const type& Get##name##Value(const type& defaultValue) const \
    {                                                            \
        if (!Has##name()) {                                      \
            return defaultValue;                                 \
        }                                                        \
        return prop##name##_.value();                            \
    }                                                            \
    std::optional<type> Clone##name() const                      \
    {                                                            \
        return prop##name##_;                                    \
    }                                                            \
    void Reset##name()                                           \
    {                                                            \
        return prop##name##_.reset();                            \
    }                                                            \
                                                                 \
protected:                                                       \
    std::optional<type> prop##name##_;

#define ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(name, type, changeFlag) \
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_GET(name, type)             \
public:                                                                \
    void Update##name(const type& value)                               \
    {                                                                  \
        if (prop##name##_.has_value()) {                               \
            if (NearEqual(prop##name##_.value(), value)) {             \
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
                return;                                                                   \
            }                                                                             \
        }                                                                                 \
        prop##name##_ = value;                                                            \
        UpdatePropertyChangeFlag(changeFlag);                                             \
        On##name##Update(value);                                                          \
    }

#define ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(name, type) \
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_GET(name, type)      \
public:                                                         \
    void Update##name(const type& value)                        \
    {                                                           \
        if (prop##name##_.has_value()) {                        \
            if (NearEqual(prop##name##_.value(), value)) {      \
                return;                                         \
            }                                                   \
        }                                                       \
        prop##name##_ = value;                                  \
        On##name##Update(value);                                \
    }

#define ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP_FOR_VIRTUAL_NODE(name, type)                 \
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_GET(name, type)                                       \
public:                                                                                          \
    void Update##name(const type& value, const int64_t accessibilityIdForVirtualNode = -2100000) \
    {                                                                                            \
        if (prop##name##_.has_value()) {                                                         \
            if (NearEqual(prop##name##_.value(), value)) {                                       \
                return;                                                                          \
            }                                                                                    \
        }                                                                                        \
        prop##name##_ = value;                                                                   \
        On##name##Update(value, accessibilityIdForVirtualNode);                                  \
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
    }                                                   \
    void Reset##name()                                  \
    {                                                   \
        prop##name.reset();                             \
    }

#define ACE_DEFINE_PROPERTY_GROUP_ITEM_WITH_CALLBACK(name, type) \
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_GET(name, type)       \
public:                                                          \
    bool Update##name(const type& value)                         \
    {                                                            \
        if (prop##name##_.has_value()) {                         \
            if (NearEqual(prop##name##_.value(), value)) {       \
                return false;                                    \
            }                                                    \
        }                                                        \
        On##name##Update(value);                                 \
        prop##name##_ = value;                                   \
        return true;                                             \
    }

#define ACE_PROPERTY_TO_JSON_VALUE(target, type) \
    do {                                         \
        if (target) {                            \
            (target)->ToJsonValue(json, filter); \
        } else {                                 \
            type p;                              \
            p.ToJsonValue(json, filter);         \
        }                                        \
    } while (false)

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
