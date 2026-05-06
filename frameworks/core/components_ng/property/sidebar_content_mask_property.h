/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_SIDEBAR_CONTENT_MASK_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_SIDEBAR_CONTENT_MASK_PROPERTY_H

#include <vector>
#include <functional>
#include "base/memory/ace_type.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace::NG {
class SidebarContentMaskProperty : public AceType {
    DECLARE_ACE_TYPE(SidebarContentMaskProperty, AceType);

public:
    SidebarContentMaskProperty(bool isShowMask, const Color& maskColor)
    {
        isShowMask_ = isShowMask;
        maskColor_ = maskColor;
    };
    ~SidebarContentMaskProperty() override = default;

    bool GetIsShowMask() const
    {
        return isShowMask_;
    }

    void SetIsShowMask(bool isShowMask)
    {
        isShowMask_ = isShowMask;
    }

    Color GetMaskColor() const
    {
        return maskColor_;
    }

    void SetMaskColor(const Color& maskColor)
    {
        maskColor_ = maskColor;
    }

    bool operator==(const SidebarContentMaskProperty& other) const
    {
        return isShowMask_ == other.GetIsShowMask() && maskColor_ == other.GetMaskColor();
    }

    SidebarContentMaskProperty& operator=(const SidebarContentMaskProperty& other)
    {
        if (this != &other) {
            isShowMask_ = other.GetIsShowMask();
            maskColor_ = other.GetMaskColor();
        }
        return *this;
    }

private:
    bool isShowMask_ = false;
    Color maskColor_;
};
} // namespace OHOS::Ace::NG {
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_SIDEBAR_CONTENT_MASK_PROPERTY_H
