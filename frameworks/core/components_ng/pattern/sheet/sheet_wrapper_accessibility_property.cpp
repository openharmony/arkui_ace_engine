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

#include "core/components_ng/pattern/sheet/sheet_wrapper_accessibility_property.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/property/accessibility_property_helper.h"

namespace OHOS::Ace::NG {
void SheetWrapperAccessibilityProperty::GetExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo)
{
    extraElementInfo.SetExtraElementInfo("isModal", IsAccessibilityModal());
}

bool SheetWrapperAccessibilityProperty::IsAccessibilityModal() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, true);

    bool isModal = false;
    auto sheetPage = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    CHECK_NULL_RETURN(sheetPage, true);
    auto sheetPattern = sheetPage->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, true);
    auto sheetObj = sheetPattern->GetSheetObject();
    CHECK_NULL_RETURN(sheetObj, true);
    auto sheetType = sheetObj->GetSheetType();
    auto sheetLayoutProperty = sheetPage->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(sheetLayoutProperty, true);
    auto sheetStyle = sheetLayoutProperty->GetSheetStyleValue(SheetStyle());
    if (sheetStyle.interactive.has_value()) {
        // the attribute interactive has been set.
        isModal = !sheetStyle.interactive.value();
    } else {
        // if sheet type is POPUP, the default isModal is false, otherwise is true.
        isModal = !(sheetType == SheetType::SHEET_POPUP);
    }
    // if sheet type is full screen, the isModal is true.
    if (sheetType == SheetType::SHEET_CONTENT_COVER) {
        isModal = true;
    }
    return isModal;
}
} // namespace OHOS::Ace::NG