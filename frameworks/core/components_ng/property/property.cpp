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

#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

bool CheckNeedRender(PropertyChangeFlag propertyChangeFlag)
{
    return ((propertyChangeFlag & PROPERTY_UPDATE_RENDER) == PROPERTY_UPDATE_RENDER);
}

bool CheckNeedLayoutSelf(PropertyChangeFlag propertyChangeFlag)
{
    return ((propertyChangeFlag & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) ||
           ((propertyChangeFlag & PROPERTY_UPDATE_LAYOUT) == PROPERTY_UPDATE_LAYOUT) ||
           ((propertyChangeFlag & PROPERTY_UPDATE_NODE_TREE) == PROPERTY_UPDATE_NODE_TREE) ||
           ((propertyChangeFlag & PROPERTY_UPDATE_CHILD_REQUEST) == PROPERTY_UPDATE_CHILD_REQUEST);
}

bool CheckNeedParentLayout(PropertyChangeFlag propertyChangeFlag)
{
    return CheckNeedLayoutSelf(propertyChangeFlag) ||
           ((propertyChangeFlag & PROPERTY_UPDATE_POSITION) == PROPERTY_UPDATE_POSITION);
}

bool CheckMeasureFlag(PropertyChangeFlag propertyChangeFlag)
{
    return ((propertyChangeFlag & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) ||
           ((propertyChangeFlag & PROPERTY_UPDATE_CHILD_REQUEST) == PROPERTY_UPDATE_CHILD_REQUEST);
}

bool CheckNodeTreeFlag(PropertyChangeFlag propertyChangeFlag)
{
    return ((propertyChangeFlag & PROPERTY_UPDATE_NODE_TREE) == PROPERTY_UPDATE_NODE_TREE);
}

bool CheckLayoutFlag(PropertyChangeFlag propertyChangeFlag)
{
    return ((propertyChangeFlag & PROPERTY_UPDATE_LAYOUT) == PROPERTY_UPDATE_LAYOUT);
}

bool CheckPositionFlag(PropertyChangeFlag propertyChangeFlag)
{
    return ((propertyChangeFlag & PROPERTY_UPDATE_POSITION) == PROPERTY_UPDATE_POSITION);
}

bool CheckTreeChangedFlag(PropertyChangeFlag propertyChangeFlag)
{
    return ((propertyChangeFlag & PROPERTY_UPDATE_NODE_TREE) == PROPERTY_UPDATE_NODE_TREE);
}

bool CheckNoChanged(PropertyChangeFlag propertyChangeFlag)
{
    return (propertyChangeFlag == PROPERTY_UPDATE_NORMAL);
}

#define ACE_DEFINE_STRUCT_PROPERTY(name, type)                \
    std::optional<type> prop##name;                           \
                                                              \
    const std::optional<type>& Get##name() const              \
    {                                                         \
        return prop##name;                                    \
    }                                                         \
    bool Update##name(const type& value##name)                \
    {                                                         \
        if (prop##name == value##name) {                      \
            return false;                                     \
        }                                                     \
        prop##name = value##name;                             \
        return true;                                          \
    }                                                         \
    bool Update##name(const std::optional<type>& value##name) \
    {                                                         \
        if (prop##name == value##name) {                      \
            return false;                                     \
        }                                                     \
        if (!value##name.has_value()) {                       \
            return false;                                     \
        }                                                     \
        prop##name = value##name;                             \
        return true;                                          \
    }                                                         \
    bool Has##name() const                                    \
    {                                                         \
        return prop##name.has_value();                        \
    }                                                         \
    const type& Get##name##Value() const                      \
    {                                                         \
        return prop##name.value();                            \
    }                                                         \
    bool Check##name(const type& value) const                 \
    {                                                         \
        return prop##name == value;                           \
    }

} // namespace OHOS::Ace::NG
