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

#include "core/components_ng/pattern/sheet/sheet_mask_accessibility_property.h"

#include "core/components_ng/pattern/sheet/sheet_mask_pattern.h"
#include "core/components_ng/property/accessibility_property_helper.h"

namespace OHOS::Ace::NG {
void SheetMaskAccessibilityProperty::GetExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo)
{
    extraElementInfo.SetExtraElementInfo("isModal", IsAccessibilityModal());
}

bool SheetMaskAccessibilityProperty::IsAccessibilityModal() const
{
    auto maskNode = host_.Upgrade();
    CHECK_NULL_RETURN(maskNode, true);

    auto maskPattern = maskNode->GetPattern<SheetMaskPattern>();
    CHECK_NULL_RETURN(maskPattern, true);
    // sheet mask node can interactive means is in modal.
    return maskPattern->GetIsMaskInteractive();
}
} // namespace OHOS::Ace::NG