/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXTPICKER_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXTPICKER_PROPERTIES_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/color.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace::NG {
struct ItemDivider final {
    Dimension strokeWidth = 0.0_vp;
    Dimension startMargin = 0.0_vp;
    Dimension endMargin = 0.0_vp;
    Color color = Color::TRANSPARENT;
    bool isRtl = false;
    bool isNull = false;

    RefPtr<ResourceObject> strokeWidthResObj;
    RefPtr<ResourceObject> startMarginResObj;
    RefPtr<ResourceObject> endMarginResObj;
    RefPtr<ResourceObject> colorResObj;

    bool operator==(const ItemDivider& itemDivider) const
    {
        return (strokeWidth == itemDivider.strokeWidth) && (startMargin == itemDivider.startMargin) &&
               (endMargin == itemDivider.endMargin) && (color == itemDivider.color) &&
               (isRtl == itemDivider.isRtl);
    }
};

struct DividerInfo {
    float startMargin = 0.0f;
    float endMargin = 0.0f;
    float dividerWidth = 0.0f;
    float dividerLength = 0.0f;
    float dividerMargin = 0.0f;
    double dividerHeight = 0.0f;
    Color dividerColor = Color::TRANSPARENT;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXTPICKER_PROPERTIES_H
