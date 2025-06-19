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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERATION_OPERATION_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERATION_OPERATION_UTILS_H

#include "accessibility_element_info.h"
#include "accessibility_event_info.h"
#include "base/utils/utils.h"
#include "frameworks/core/accessibility/native_interface_accessibility_impl.h"

namespace OHOS::Ace::Framework {
void TransformAccessbilityElementInfo(
    const ArkUI_AccessibilityElementInfo& nativeInfo,
    OHOS::Accessibility::AccessibilityElementInfo& accessibilityElementInfo)
{
    accessibilityElementInfo.SetParent(nativeInfo.GetParentId());
    accessibilityElementInfo.SetComponentType(nativeInfo.GetComponentType());
    accessibilityElementInfo.SetContent(nativeInfo.GetContents());
    accessibilityElementInfo.SetHint(nativeInfo.GetHintText());
    accessibilityElementInfo.SetAccessibilityText(nativeInfo.GetAccessibilityText());
    accessibilityElementInfo.SetDescriptionInfo(nativeInfo.GetAccessibilityDescription());

    auto nodeList = nativeInfo.GetChildNodeIds();
    for (const auto& node : nodeList) {
        accessibilityElementInfo.AddChild(node);
    }

    auto actionList = nativeInfo.GetOperationActions();
    for (const auto& actionItem : actionList) {
        auto action = OHOS::Accessibility::AccessibleAction(
            static_cast<OHOS::Accessibility::ActionType>(actionItem.actionType),
            actionItem.description ? actionItem.description : "");
        accessibilityElementInfo.AddAction(action);
    }

    auto rect = nativeInfo.GetScreenRect();
    auto transformedRect = OHOS::Accessibility::Rect(
        rect.leftTopX, rect.leftTopY, rect.rightBottomX, rect.rightBottomY);
    accessibilityElementInfo.SetRectInScreen(transformedRect);
    accessibilityElementInfo.SetCheckable(nativeInfo.IsCheckable());
    accessibilityElementInfo.SetChecked(nativeInfo.IsChecked());
    accessibilityElementInfo.SetFocusable(nativeInfo.IsFocusable());
    accessibilityElementInfo.SetFocused(nativeInfo.IsFocused());
    accessibilityElementInfo.SetVisible(nativeInfo.IsVisible());
    accessibilityElementInfo.SetAccessibilityFocus(nativeInfo.IsAccessibilityFocused());
    accessibilityElementInfo.SetSelected(nativeInfo.IsSelected());
    accessibilityElementInfo.SetClickable(nativeInfo.IsClickable());
    accessibilityElementInfo.SetLongClickable(nativeInfo.IsLongClickable());
    accessibilityElementInfo.SetEnabled(nativeInfo.IsEnabled());
    accessibilityElementInfo.SetPassword(nativeInfo.IsPassword());
    accessibilityElementInfo.SetScrollable(nativeInfo.IsScrollable());
    accessibilityElementInfo.SetEditable(nativeInfo.IsEditable());
    accessibilityElementInfo.SetHinting(nativeInfo.IsHint());

    auto range = nativeInfo.GetRangeInfo();
    auto transformedRange = OHOS::Accessibility::RangeInfo(range.min, range.max, range.current);
    accessibilityElementInfo.SetRange(transformedRange);

    auto grid = nativeInfo.GetGridInfo();
    auto transformedGrid = OHOS::Accessibility::GridInfo(
        grid.rowCount, grid.columnCount, grid.selectionMode);
    accessibilityElementInfo.SetGrid(transformedGrid);

    auto girdItem = nativeInfo.GetGridItemInfo();
    auto transformedGirdItemInfo = OHOS::Accessibility::GridItemInfo(
        girdItem.rowIndex, girdItem.rowSpan, girdItem.columnIndex,
        girdItem.columnSpan, girdItem.heading, girdItem.selected);
    accessibilityElementInfo.SetGridItem(transformedGirdItemInfo);
    accessibilityElementInfo.SetSelectedBegin(nativeInfo.GetTextBeginSelected());
    accessibilityElementInfo.SetSelectedEnd(nativeInfo.GetTextEndSelected());
    accessibilityElementInfo.SetCurrentIndex(nativeInfo.GetCurrentIndex());
    accessibilityElementInfo.SetBeginIndex(nativeInfo.GetBeginIndex());
    accessibilityElementInfo.SetEndIndex(nativeInfo.GetEndIndex());
    accessibilityElementInfo.SetItemCounts(nativeInfo.GetItemCount());
    accessibilityElementInfo.SetOffset(nativeInfo.GetOffset());
    accessibilityElementInfo.SetAccessibilityGroup(nativeInfo.GetAccessibilityGroup());
    accessibilityElementInfo.SetAccessibilityLevel(nativeInfo.GetAccessibilityLevel());
    accessibilityElementInfo.SetZIndex(nativeInfo.GetZIndex());
    accessibilityElementInfo.SetOpacity(nativeInfo.GetOpacity());
    accessibilityElementInfo.SetBackgroundColor(nativeInfo.GetBackgroundColor());
    accessibilityElementInfo.SetBackgroundImage(nativeInfo.GetBackgroundImage());
    accessibilityElementInfo.SetBlur(nativeInfo.GetBlur());
    accessibilityElementInfo.SetHitTestBehavior(nativeInfo.GetHitTestBehavior());
    accessibilityElementInfo.SetAccessibilityId(nativeInfo.GetElementId());
}

void TransformAccessbilityEventInfo(
    const ArkUI_AccessibilityEventInfo& nativeEventInfo,
    OHOS::Accessibility::AccessibilityEventInfo& accessibilityEventInfo)
{
    accessibilityEventInfo.SetEventType(
        static_cast<OHOS::Accessibility::EventType>(nativeEventInfo.GetEventType()));
    OHOS::Accessibility::AccessibilityElementInfo elementInfo;
    auto info = nativeEventInfo.GetElementInfo();
    if (info != nullptr) {
        TransformAccessbilityElementInfo(*info, elementInfo);
    }

    accessibilityEventInfo.SetElementInfo(elementInfo);
    accessibilityEventInfo.SetTextAnnouncedForAccessibility(
        nativeEventInfo.GetTextAnnouncedForAccessibility());
    accessibilityEventInfo.SetRequestFocusElementId(nativeEventInfo.GetRequestFocusId());
}
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERATION_OPERATION_UTILS_H