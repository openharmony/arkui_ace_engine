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

#include "gtest/gtest.h"

#include "adapter/ohos/osal/js_third_provider_interaction_operation_utils.h"
#include "frameworks/core/accessibility/accessibility_node.h"
#include "frameworks/core/accessibility/accessibility_utils.h"
#include "securec.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const int32_t BOOL_MASK = 2;
    const int32_t MAX_CHILD_COUNT = 20;
    const int32_t MAX_ACTION_COUNT = 20;
    const int32_t MAX_C_STR_COUNT = 30;
    const int32_t MAX_C_STR_CHAR_COUNT = 100;
} // namespace

class AccessibilityProviderUtilsTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};

    void FillNativeAccessibilityElementInfoPart(
        const OHOS::Accessibility::AccessibilityElementInfo& accessibilityElementInfo,
        ArkUI_AccessibilityElementInfo& nativeInfo)
    {
        // screen rect
        ArkUI_AccessibleRect screenRect {
            accessibilityElementInfo.GetRectInScreen().GetLeftTopXScreenPostion(),
            accessibilityElementInfo.GetRectInScreen().GetLeftTopYScreenPostion(),
            accessibilityElementInfo.GetRectInScreen().GetRightBottomXScreenPostion(),
            accessibilityElementInfo.GetRectInScreen().GetRightBottomYScreenPostion()};
        nativeInfo.SetRect(screenRect);
        // rangeInfo
        ArkUI_AccessibleRangeInfo rangeInfo {
            accessibilityElementInfo.GetRange().GetMin(),
            accessibilityElementInfo.GetRange().GetMax(),
            accessibilityElementInfo.GetRange().GetCurrent()};
        nativeInfo.SetRangeInfo(rangeInfo);
        // GridInfo
        ArkUI_AccessibleGridInfo gridInfo {
            accessibilityElementInfo.GetGrid().GetRowCount(),
            accessibilityElementInfo.GetGrid().GetColumnCount(),
            accessibilityElementInfo.GetGrid().GetSelectionMode()};
        nativeInfo.SetGridInfo(gridInfo);
        // GridItemInfo
        ArkUI_AccessibleGridItemInfo gridItemInfo {
            accessibilityElementInfo.GetGridItem().IsHeading(),
            accessibilityElementInfo.GetGridItem().IsSelected(),
            accessibilityElementInfo.GetGridItem().GetColumnIndex(),
            accessibilityElementInfo.GetGridItem().GetRowIndex(),
            accessibilityElementInfo.GetGridItem().GetColumnSpan(),
            accessibilityElementInfo.GetGridItem().GetRowSpan()};
        nativeInfo.SetGridItemInfo(gridItemInfo);

        nativeInfo.SetComponentType(accessibilityElementInfo.GetComponentType());
        nativeInfo.SetContents(accessibilityElementInfo.GetContent());
        nativeInfo.SetHintText(accessibilityElementInfo.GetHint());
        nativeInfo.SetAccessibilityText(accessibilityElementInfo.GetAccessibilityText());
        nativeInfo.SetAccessibilityDescription(accessibilityElementInfo.GetDescriptionInfo());
        nativeInfo.SetAccessibilityLevel(accessibilityElementInfo.GetAccessibilityLevel());
        nativeInfo.SetBackgroundColor(accessibilityElementInfo.GetBackgroundColor());
        nativeInfo.SetBackgroundImage(accessibilityElementInfo.GetBackgroundImage());
        nativeInfo.SetBlur(accessibilityElementInfo.GetBlur());
        nativeInfo.SetHitTestBehavior(accessibilityElementInfo.GetHitTestBehavior());
    }

    void FillNativeAccessibilityElementInfo(
        const OHOS::Accessibility::AccessibilityElementInfo& accessibilityElementInfo,
        ArkUI_AccessibilityElementInfo& nativeInfo)
    {
        nativeInfo.SetPageId(accessibilityElementInfo.GetPageId());
        nativeInfo.SetParentId(accessibilityElementInfo.GetParentNodeId());
        nativeInfo.SetElementId(accessibilityElementInfo.GetAccessibilityId());
        nativeInfo.SetTextBeginSelected(accessibilityElementInfo.GetSelectedBegin());
        nativeInfo.SetTextEndSelected(accessibilityElementInfo.GetSelectedEnd());
        nativeInfo.SetCurrentIndex(accessibilityElementInfo.GetCurrentIndex());
        nativeInfo.SetBeginIndex(accessibilityElementInfo.GetBeginIndex());
        nativeInfo.SetEndIndex(accessibilityElementInfo.GetEndIndex());
        nativeInfo.SetItemCount(accessibilityElementInfo.GetItemCounts());
        nativeInfo.SetOffset(accessibilityElementInfo.GetOffset());
        nativeInfo.SetZIndex(accessibilityElementInfo.GetZIndex());
        nativeInfo.SetOpacity(accessibilityElementInfo.GetOpacity());
        nativeInfo.SetCheckable(accessibilityElementInfo.IsCheckable());
        nativeInfo.SetChecked(accessibilityElementInfo.IsChecked());
        nativeInfo.SetFocusable(accessibilityElementInfo.IsFocusable());
        nativeInfo.SetFocused(accessibilityElementInfo.IsFocused());
        nativeInfo.SetVisible(accessibilityElementInfo.IsVisible());
        nativeInfo.SetAccessibilityFocused(accessibilityElementInfo.HasAccessibilityFocus());
        nativeInfo.SetSelected(accessibilityElementInfo.IsSelected());
        nativeInfo.SetClickable(accessibilityElementInfo.IsClickable());
        nativeInfo.SetLongClickable(accessibilityElementInfo.IsLongClickable());
        nativeInfo.SetEnabled(accessibilityElementInfo.IsEnabled());
        nativeInfo.SetPassword(accessibilityElementInfo.IsPassword());
        nativeInfo.SetScrollable(accessibilityElementInfo.IsScrollable());
        nativeInfo.SetEditable(accessibilityElementInfo.IsEditable());
        nativeInfo.SetHint(accessibilityElementInfo.IsGivingHint());
        nativeInfo.SetAccessibilityGroup(accessibilityElementInfo.GetAccessibilityGroup());

        FillNativeAccessibilityElementInfoPart(accessibilityElementInfo, nativeInfo);
    }

    void BuildAccessibilityElementInfoPart(
        int32_t index,
        OHOS::Accessibility::AccessibilityElementInfo& accessibilityElementInfo)
    {
        std::string content;
        // screen rect
        auto leftTopX = ++index;
        auto leftTopY = ++index;
        auto rightBottomX = ++index;
        auto rightBottomY = ++index;
        OHOS::Accessibility::Rect screenRect (leftTopX, leftTopY, rightBottomX, rightBottomY);
        accessibilityElementInfo.SetRectInScreen(screenRect);
        // rangeInfo
        auto min = ++index;
        auto max = ++index;
        auto current = ++index;
        OHOS::Accessibility::RangeInfo rangeInfo (min, max, current);
        accessibilityElementInfo.SetRange(rangeInfo);
        // GridInfo
        auto rowCount = ++index;
        auto columnCount = ++index;
        auto selectionMode = ++index;
        OHOS::Accessibility::GridInfo gridInfo (rowCount, columnCount, selectionMode);
        accessibilityElementInfo.SetGrid(gridInfo);
        // GridItemInfo
        auto heading = (++index) % BOOL_MASK;
        auto columnIndex = ++index;
        auto rowIndex = ++index;
        auto columnSpan = ++index;
        auto rowSpan = ++index;
        auto selected = (++index) % BOOL_MASK;
        OHOS::Accessibility::GridItemInfo gridItemInfo
            (heading, columnIndex, rowIndex, columnSpan, rowSpan, selected);
        accessibilityElementInfo.SetGridItem(gridItemInfo);

        content = std::to_string(++index);
        accessibilityElementInfo.SetComponentType(content);
        content = std::to_string(++index);
        accessibilityElementInfo.SetContent(content);
        content = std::to_string(++index);
        accessibilityElementInfo.SetHint(content);
        content = std::to_string(++index);
        accessibilityElementInfo.SetAccessibilityText(content);
        content = std::to_string(++index);
        accessibilityElementInfo.SetDescriptionInfo(content);
        content = std::to_string(++index);
        accessibilityElementInfo.SetAccessibilityLevel(content);
        content = std::to_string(++index);
        accessibilityElementInfo.SetBackgroundColor(content);
        content = std::to_string(++index);
        accessibilityElementInfo.SetBackgroundImage(content);
        content = std::to_string(++index);
        accessibilityElementInfo.SetBlur(content);
        content = std::to_string(++index);
        accessibilityElementInfo.SetHitTestBehavior(content);
    }

    void BuildAccessibilityElementInfo(
        int32_t index,
        OHOS::Accessibility::AccessibilityElementInfo& accessibilityElementInfo)
    {
        std::string content;

        accessibilityElementInfo.SetPageId(index);
        accessibilityElementInfo.SetParent(++index);
        accessibilityElementInfo.SetAccessibilityId(++index);
        accessibilityElementInfo.SetSelectedBegin(++index);
        accessibilityElementInfo.SetSelectedEnd(++index);

        accessibilityElementInfo.SetCurrentIndex(++index);
        accessibilityElementInfo.SetBeginIndex(++index);
        accessibilityElementInfo.SetEndIndex(++index);
        accessibilityElementInfo.SetItemCounts(++index);
        accessibilityElementInfo.SetOffset(++index);
        accessibilityElementInfo.SetZIndex(++index);
        accessibilityElementInfo.SetOpacity(++index);
        accessibilityElementInfo.SetCheckable((++index) % BOOL_MASK);
        accessibilityElementInfo.SetChecked((++index) % BOOL_MASK);
        accessibilityElementInfo.SetFocusable((++index) % BOOL_MASK);
        accessibilityElementInfo.SetFocused((++index) % BOOL_MASK);
        accessibilityElementInfo.SetVisible((++index) % BOOL_MASK);
        accessibilityElementInfo.SetAccessibilityFocus((++index) % BOOL_MASK);
        accessibilityElementInfo.SetSelected((++index) % BOOL_MASK);
        accessibilityElementInfo.SetClickable((++index) % BOOL_MASK);
        accessibilityElementInfo.SetLongClickable((++index) % BOOL_MASK);
        accessibilityElementInfo.SetEnabled((++index) % BOOL_MASK);
        accessibilityElementInfo.SetPassword((++index) % BOOL_MASK);
        accessibilityElementInfo.SetScrollable((++index) % BOOL_MASK);
        accessibilityElementInfo.SetEditable((++index) % BOOL_MASK);
        accessibilityElementInfo.SetHinting((++index) % BOOL_MASK);
        accessibilityElementInfo.SetAccessibilityGroup((++index) % BOOL_MASK);

        BuildAccessibilityElementInfoPart(index, accessibilityElementInfo);
    }

    void CheckTransformElementInfoResultPart(
        const OHOS::Accessibility::AccessibilityElementInfo& beforeInfo,
        const OHOS::Accessibility::AccessibilityElementInfo& afterInfo)
    {
        // screen rect
        EXPECT_EQ(beforeInfo.GetRectInScreen().GetLeftTopXScreenPostion(),
            afterInfo.GetRectInScreen().GetLeftTopXScreenPostion());
        EXPECT_EQ(beforeInfo.GetRectInScreen().GetLeftTopYScreenPostion(),
            afterInfo.GetRectInScreen().GetLeftTopYScreenPostion());
        EXPECT_EQ(beforeInfo.GetRectInScreen().GetRightBottomXScreenPostion(),
            afterInfo.GetRectInScreen().GetRightBottomXScreenPostion());
        EXPECT_EQ(beforeInfo.GetRectInScreen().GetRightBottomYScreenPostion(),
            afterInfo.GetRectInScreen().GetRightBottomYScreenPostion());

        // rangeInfo
        EXPECT_EQ(beforeInfo.GetRange().GetMin(),
            afterInfo.GetRange().GetMin());
        EXPECT_EQ(beforeInfo.GetRange().GetMax(),
            afterInfo.GetRange().GetMax());
        EXPECT_EQ(beforeInfo.GetRange().GetCurrent(),
            afterInfo.GetRange().GetCurrent());

        // GridInfo
        EXPECT_EQ(beforeInfo.GetGrid().GetRowCount(),
            afterInfo.GetGrid().GetRowCount());
        EXPECT_EQ(beforeInfo.GetGrid().GetColumnCount(),
            afterInfo.GetGrid().GetColumnCount());
        EXPECT_EQ(beforeInfo.GetGrid().GetSelectionMode(),
            afterInfo.GetGrid().GetSelectionMode());

        // GridItemInfo
        EXPECT_EQ(beforeInfo.GetGridItem().GetColumnIndex(),
            afterInfo.GetGridItem().GetColumnIndex());
        EXPECT_EQ(beforeInfo.GetGridItem().GetRowIndex(),
            afterInfo.GetGridItem().GetRowIndex());
        EXPECT_EQ(beforeInfo.GetGridItem().GetColumnSpan(),
            afterInfo.GetGridItem().GetColumnSpan());
        EXPECT_EQ(beforeInfo.GetGridItem().GetRowSpan(),
            afterInfo.GetGridItem().GetRowSpan());
        EXPECT_EQ(beforeInfo.GetGridItem().IsHeading(),
            afterInfo.GetGridItem().IsHeading());
        EXPECT_EQ(beforeInfo.GetGridItem().IsSelected(),
            afterInfo.GetGridItem().IsSelected());

        EXPECT_EQ(beforeInfo.GetComponentType(), afterInfo.GetComponentType());
        EXPECT_EQ(beforeInfo.GetContent(), afterInfo.GetContent());
        EXPECT_EQ(beforeInfo.GetHint(), afterInfo.GetHint());
        EXPECT_EQ(beforeInfo.GetAccessibilityText(), afterInfo.GetAccessibilityText());
        EXPECT_EQ(beforeInfo.GetDescriptionInfo(), afterInfo.GetDescriptionInfo());
        EXPECT_EQ(beforeInfo.GetAccessibilityLevel(), afterInfo.GetAccessibilityLevel());
        EXPECT_EQ(beforeInfo.GetBackgroundColor(), afterInfo.GetBackgroundColor());
        EXPECT_EQ(beforeInfo.GetBlur(), afterInfo.GetBlur());
        EXPECT_EQ(beforeInfo.GetHitTestBehavior(), afterInfo.GetHitTestBehavior());
    }

    void CheckTransformElementInfoResult(
        const OHOS::Accessibility::AccessibilityElementInfo& beforeInfo,
        const OHOS::Accessibility::AccessibilityElementInfo& afterInfo)
    {
        // Page ID not trans
        EXPECT_EQ(beforeInfo.GetParentNodeId(), afterInfo.GetParentNodeId());
        EXPECT_EQ(beforeInfo.GetAccessibilityId(), afterInfo.GetAccessibilityId());
        EXPECT_EQ(beforeInfo.GetSelectedBegin(), afterInfo.GetSelectedBegin());
        EXPECT_EQ(beforeInfo.GetSelectedEnd(), afterInfo.GetSelectedEnd());
        EXPECT_EQ(beforeInfo.GetCurrentIndex(), afterInfo.GetCurrentIndex());
        EXPECT_EQ(beforeInfo.GetBeginIndex(), afterInfo.GetBeginIndex());
        EXPECT_EQ(beforeInfo.GetEndIndex(), afterInfo.GetEndIndex());
        EXPECT_EQ(beforeInfo.GetItemCounts(), afterInfo.GetItemCounts());
        EXPECT_EQ(beforeInfo.GetOffset(), afterInfo.GetOffset());
        EXPECT_EQ(beforeInfo.GetZIndex(), afterInfo.GetZIndex());
        EXPECT_EQ(beforeInfo.GetOpacity(), afterInfo.GetOpacity());
        EXPECT_EQ(beforeInfo.IsCheckable(), afterInfo.IsCheckable());
        EXPECT_EQ(beforeInfo.IsChecked(), afterInfo.IsChecked());
        EXPECT_EQ(beforeInfo.IsFocusable(), afterInfo.IsFocusable());
        EXPECT_EQ(beforeInfo.IsFocused(), afterInfo.IsFocused());
        EXPECT_EQ(beforeInfo.IsVisible(), afterInfo.IsVisible());
        EXPECT_EQ(beforeInfo.HasAccessibilityFocus(), afterInfo.HasAccessibilityFocus());
        EXPECT_EQ(beforeInfo.IsSelected(), afterInfo.IsSelected());
        EXPECT_EQ(beforeInfo.IsClickable(), afterInfo.IsClickable());
        EXPECT_EQ(beforeInfo.IsLongClickable(), afterInfo.IsLongClickable());
        EXPECT_EQ(beforeInfo.IsEnabled(), afterInfo.IsEnabled());
        EXPECT_EQ(beforeInfo.IsPassword(), afterInfo.IsPassword());
        EXPECT_EQ(beforeInfo.IsScrollable(), afterInfo.IsScrollable());
        EXPECT_EQ(beforeInfo.IsEditable(), afterInfo.IsEditable());
        EXPECT_EQ(beforeInfo.IsGivingHint(), afterInfo.IsGivingHint());
        EXPECT_EQ(beforeInfo.GetAccessibilityGroup(), afterInfo.GetAccessibilityGroup());

        CheckTransformElementInfoResultPart(beforeInfo, afterInfo);
    }

    void BuildAccessibilityEventInfo(
        int32_t index,
        OHOS::Accessibility::AccessibilityEventInfo& beforeEventInfo,
        OHOS::Accessibility::AccessibilityElementInfo& beforeElementInfo)
    {
        beforeEventInfo.SetEventType(static_cast<OHOS::Accessibility::EventType>(index));
        beforeEventInfo.SetPageId(++index);
        beforeEventInfo.SetRequestFocusElementId(++index);
        beforeEventInfo.SetElementInfo(beforeElementInfo);
        beforeEventInfo.SetTextAnnouncedForAccessibility(std::to_string(++index));
    }

    void FillNativeAccessibilityEventInfo(
        ArkUI_AccessibilityEventInfo& nativeEventInfo,
        OHOS::Accessibility::AccessibilityEventInfo& beforeEventInfo,
        ArkUI_AccessibilityElementInfo &info)
    {
        nativeEventInfo.SetEventType(
            static_cast<ArkUI_AccessibilityEventType>(beforeEventInfo.GetEventType()));
        nativeEventInfo.SetPageId(beforeEventInfo.GetPageId());
        nativeEventInfo.SetRequestFocusId(beforeEventInfo.GetRequestFocusElementId());
        nativeEventInfo.SetElementInfo(&(info));
        nativeEventInfo.SetTextAnnouncedForAccessibility(
            beforeEventInfo.GetTextAnnouncedForAccessibility());
    }

    void CheckTransformEventInfoResult(
        const OHOS::Accessibility::AccessibilityEventInfo& beforeEventInfo,
        const OHOS::Accessibility::AccessibilityEventInfo& afterEventInfo)
    {
        EXPECT_EQ(beforeEventInfo.GetEventType(), afterEventInfo.GetEventType());
        // page not transform
        EXPECT_EQ(beforeEventInfo.GetRequestFocusElementId(),
            afterEventInfo.GetRequestFocusElementId());
        CheckTransformElementInfoResult(beforeEventInfo.GetElementInfo(),
            afterEventInfo.GetElementInfo());
        EXPECT_EQ(beforeEventInfo.GetTextAnnouncedForAccessibility(),
            afterEventInfo.GetTextAnnouncedForAccessibility());
    }

    std::vector<ArkUI_Accessibility_ActionType> actionTypeVector = {
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_INVALID,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_LONG_CLICK,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_FORWARD,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_BACKWARD,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_COPY,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_PASTE,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CUT,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SELECT_TEXT,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SET_TEXT,
        ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SET_CURSOR_POSITION,
    };
};

/**
 * @tc.name: accessibilityTest001
 * @tc.desc: TransformAccessbilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderUtilsTestNg, AccessibilityUtilsTest001, TestSize.Level1)
{
    OHOS::Accessibility::AccessibilityElementInfo beforeInfo;
    BuildAccessibilityElementInfo(1, beforeInfo);
    ArkUI_AccessibilityElementInfo info;
    FillNativeAccessibilityElementInfo(beforeInfo, info);
    OHOS::Accessibility::AccessibilityElementInfo afterInfo;
    Framework::TransformAccessbilityElementInfo(info, afterInfo);
    CheckTransformElementInfoResult(beforeInfo, afterInfo);
}

/**
 * @tc.name: accessibilityTest002
 * @tc.desc: TransformAccessbilityEventInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderUtilsTestNg, AccessibilityUtilsTest002, TestSize.Level1)
{
    OHOS::Accessibility::AccessibilityElementInfo beforeElementInfo;
    BuildAccessibilityElementInfo(1, beforeElementInfo);
    ArkUI_AccessibilityElementInfo info;
    FillNativeAccessibilityElementInfo(beforeElementInfo, info);

    OHOS::Accessibility::AccessibilityEventInfo beforeEventInfo;
    BuildAccessibilityEventInfo(1, beforeEventInfo, beforeElementInfo);
    ArkUI_AccessibilityEventInfo nativeEventInfo;
    FillNativeAccessibilityEventInfo(nativeEventInfo, beforeEventInfo, info);

    OHOS::Accessibility::AccessibilityEventInfo accessibilityEventInfo;
    Framework::TransformAccessbilityEventInfo(nativeEventInfo, accessibilityEventInfo);

    CheckTransformEventInfoResult(beforeEventInfo, accessibilityEventInfo);
}

/**
 * @tc.name: accessibilityTest003
 * @tc.desc: Check child
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderUtilsTestNg, AccessibilityUtilsTest003, TestSize.Level1)
{
    OHOS::Accessibility::AccessibilityElementInfo beforeInfo;
    BuildAccessibilityElementInfo(1, beforeInfo);
    ArkUI_AccessibilityElementInfo info;
    FillNativeAccessibilityElementInfo(beforeInfo, info);

    // add child
    std::vector<int64_t> childIds;
    auto now = std::chrono::system_clock::now();
    int64_t childCount =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
        .count();
    childCount = (childCount % MAX_CHILD_COUNT) + 1;
    for (int64_t i = 0; i < childCount; i++) {
        info.AddChildNodeId(i);
        childIds.push_back(i);
    }

    OHOS::Accessibility::AccessibilityElementInfo afterInfo;
    Framework::TransformAccessbilityElementInfo(info, afterInfo);
    CheckTransformElementInfoResult(beforeInfo, afterInfo);

    EXPECT_EQ(afterInfo.GetChildCount(), childCount);
    EXPECT_EQ(afterInfo.GetChildIds(), childIds);

    // clear child
    info.ClearChildNodeIds();
    OHOS::Accessibility::AccessibilityElementInfo afterInfo2;
    Framework::TransformAccessbilityElementInfo(info, afterInfo2);
    CheckTransformElementInfoResult(beforeInfo, afterInfo2);
    EXPECT_EQ(afterInfo2.GetChildCount(), 0);
}

/**
 * @tc.name: accessibilityTest004
 * @tc.desc: Check action
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderUtilsTestNg, AccessibilityUtilsTest004, TestSize.Level1)
{
    OHOS::Accessibility::AccessibilityElementInfo beforeInfo;
    BuildAccessibilityElementInfo(1, beforeInfo);
    ArkUI_AccessibilityElementInfo info;
    FillNativeAccessibilityElementInfo(beforeInfo, info);

    // add action
    std::vector<Accessibility::AccessibleAction> accessibilityActions;
    auto now = std::chrono::system_clock::now();
    int64_t actionCount =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
        .count();
    actionCount = (actionCount % MAX_ACTION_COUNT) + 1;
    auto startIndex = actionCount;
    char string[MAX_C_STR_COUNT][MAX_C_STR_CHAR_COUNT];
    for (int64_t i = 0; i < actionCount; i++) {
        ArkUI_Accessibility_ActionType actionType
            = actionTypeVector[(startIndex + i) % actionTypeVector.size()];
        auto content = std::to_string(startIndex + i);
        (void)strcpy_s(string[i], MAX_C_STR_CHAR_COUNT, content.c_str());
        ArkUI_AccessibleAction tempAction { actionType, string[i]};
        info.AddOperationAction(tempAction);
        Accessibility::AccessibleAction tempAccessibilityActions
            {static_cast<Accessibility::ActionType>(actionType), string[i]};
        accessibilityActions.push_back(tempAccessibilityActions);
    }

    OHOS::Accessibility::AccessibilityElementInfo afterInfo;
    Framework::TransformAccessbilityElementInfo(info, afterInfo);
    CheckTransformElementInfoResult(beforeInfo, afterInfo);

    EXPECT_EQ(afterInfo.GetActionList().size(), actionCount);
    EXPECT_EQ(accessibilityActions.size(), actionCount);
    auto afterActionList = afterInfo.GetActionList();
    for (int64_t i = 0; i < actionCount; i++) {
        EXPECT_EQ(afterActionList[i].GetActionType(),
            accessibilityActions[i].GetActionType());
        EXPECT_EQ(afterActionList[i].GetDescriptionInfo(),
            accessibilityActions[i].GetDescriptionInfo());
    }

    // clear action
    info.ClearOperationActions();
    OHOS::Accessibility::AccessibilityElementInfo afterInfo2;
    Framework::TransformAccessbilityElementInfo(info, afterInfo2);
    CheckTransformElementInfoResult(beforeInfo, afterInfo2);
    EXPECT_EQ(afterInfo2.GetActionList().size(), 0);
}

/**
 * @tc.name: accessibilityTest005
 * @tc.desc: Test TransformAccessbilityElementInfo with nullptr description
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityProviderUtilsTestNg, AccessibilityUtilsTest005, TestSize.Level1)
{
    ArkUI_AccessibleAction nullptrAction0;
    nullptrAction0.description = nullptr;
    ArkUI_AccessibleAction nullptrAction1;
    nullptrAction1.description = "";
    ArkUI_AccessibilityElementInfo info;
    info.AddOperationAction(nullptrAction0);
    info.AddOperationAction(nullptrAction1);
    
    OHOS::Accessibility::AccessibilityElementInfo afterInfo;
    Framework::TransformAccessbilityElementInfo(info, afterInfo);

    auto actionList = afterInfo.GetActionList();
    EXPECT_EQ(actionList.size(), 2);
    EXPECT_EQ(actionList[0].GetDescriptionInfo(), "");
    EXPECT_EQ(actionList[1].GetDescriptionInfo(), "");
}
} // namespace OHOS::Ace::NG
