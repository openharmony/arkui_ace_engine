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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_PROPERTY_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_PROPERTY_H

#include "ui/base/ace_type.h"
#include "ui/properties/dirty_flag.h"

namespace OHOS::Ace::Kit {

class FrameNode;

class ACE_FORCE_EXPORT Property : public virtual AceType {
    DECLARE_ACE_TYPE(Property, AceType);

public:
    Property() = default;
    ~Property() override = default;

    void CleanDirty();
    void UpdateRender();
    void UpdateMeasure(bool onlySelf);
    void UpdatePaintFlag(NG::PropertyChangeFlag propertyChangeFlag);
    void UpdateLayoutFlag(NG::PropertyChangeFlag propertyChangeFlag);
    void SetHost(const WeakPtr<FrameNode>& host);
private:
    WeakPtr<FrameNode> host_;

    ACE_DISALLOW_COPY_AND_MOVE(Property);
};

} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_PROPERTY_H
