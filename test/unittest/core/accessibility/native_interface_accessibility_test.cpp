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

#include "frameworks/core/accessibility/accessibility_node.h"
#include "frameworks/core/accessibility/accessibility_utils.h"
#include "frameworks/core/accessibility/native_interface_accessibility_provider.h"
#include "interfaces/native/native_interface_accessibility.h"
#include "securec.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t BOOL_MASK = 2;
constexpr int32_t SEND_EVENT_FAILED = -1;
const int32_t MAX_CHILD_COUNT = 20;
const int32_t MAX_ACTION_COUNT = 20;
const int32_t MAX_C_STR_CHAR_COUNT = 100;
int32_t g_errcode;

void MockProviderCallBack(int32_t errorCode)
{
    g_errcode = errorCode;
}

void MockEventCallBack(int32_t errorCode)
{
    g_errcode = errorCode;
}

#define TWO_PARAMETER_NULLPTR_TEST(name, para0, para1, result) do {    \
    EXPECT_EQ(OH_ArkUI_##name(para0, nullptr), result);                \
    EXPECT_EQ(OH_ArkUI_##name(nullptr, para1), result);                \
    EXPECT_EQ(OH_ArkUI_##name(nullptr, nullptr), result);              \
} while (0)

#define TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(name, para0, para1, result) do {    \
    EXPECT_EQ(OH_ArkUI_##name(nullptr, para1), result);                               \
} while (0)

#define THREE_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(name, para0, para1, para2, result) do { \
    EXPECT_EQ(OH_ArkUI_##name(para0, para1, nullptr), result);                              \
    EXPECT_EQ(OH_ArkUI_##name(nullptr, para1, para2), result);                              \
    EXPECT_EQ(OH_ArkUI_##name(nullptr, para1, nullptr), result);                            \
} while (0)

#define NATIVE_ADD_ELEMENTINFO(name, para0, para1) do {               \
    EXPECT_EQ(OH_ArkUI_AccessibilityElementInfo##name(para0, para1),  \
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);                \
} while (0)

#define NATIVE_ADD_ELEMENTINFO_WITH_STRING_PTR(name, para0, para1) do {             \
    auto para_##name = para1;                                                       \
    EXPECT_EQ(OH_ArkUI_AccessibilityElementInfo##name(para0, para_##name.c_str()),  \
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);                              \
} while (0)

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
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_NEXT_HTML_ITEM,
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_PREVIOUS_HTML_ITEM,
};

} // namespace

class NativeInterfaceAccessibilityTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};

    void FillNativeAccessibilityElementInfoPart(
        ArkUI_AccessibilityElementInfo& beforeInfo,
        ArkUI_AccessibilityElementInfo& afterInfo)
    {
        // screen rect
        auto rect = beforeInfo.GetScreenRect();
        NATIVE_ADD_ELEMENTINFO(SetScreenRect, &afterInfo, &rect);

        // rangeInfo
        auto rangeInfo = beforeInfo.GetRangeInfo();
        NATIVE_ADD_ELEMENTINFO(SetRangeInfo, &afterInfo, &rangeInfo);

        // GridInfo
        auto gridInfo = beforeInfo.GetGridInfo();
        NATIVE_ADD_ELEMENTINFO(SetGridInfo, &afterInfo, &gridInfo);

        // GridItemInfo
        auto gridItemInfo = beforeInfo.GetGridItemInfo();
        NATIVE_ADD_ELEMENTINFO(SetGridItemInfo, &afterInfo, &gridItemInfo);

        NATIVE_ADD_ELEMENTINFO_WITH_STRING_PTR(SetComponentType,
            &afterInfo, beforeInfo.GetComponentType());
        NATIVE_ADD_ELEMENTINFO_WITH_STRING_PTR(SetContents,
            &afterInfo, beforeInfo.GetContents());
        NATIVE_ADD_ELEMENTINFO_WITH_STRING_PTR(SetHintText,
            &afterInfo, beforeInfo.GetHintText());
        NATIVE_ADD_ELEMENTINFO_WITH_STRING_PTR(SetAccessibilityText,
            &afterInfo, beforeInfo.GetAccessibilityText());
        NATIVE_ADD_ELEMENTINFO_WITH_STRING_PTR(SetAccessibilityDescription,
            &afterInfo, beforeInfo.GetAccessibilityDescription());
        NATIVE_ADD_ELEMENTINFO_WITH_STRING_PTR(SetAccessibilityLevel,
            &afterInfo, beforeInfo.GetAccessibilityLevel());
        NATIVE_ADD_ELEMENTINFO_WITH_STRING_PTR(SetBackgroundColor,
            &afterInfo, beforeInfo.GetBackgroundColor());
        NATIVE_ADD_ELEMENTINFO_WITH_STRING_PTR(SetBackgroundImage,
            &afterInfo, beforeInfo.GetBackgroundImage());
        NATIVE_ADD_ELEMENTINFO_WITH_STRING_PTR(SetBlur,
            &afterInfo, beforeInfo.GetBlur());
        NATIVE_ADD_ELEMENTINFO_WITH_STRING_PTR(SetHitTestBehavior,
            &afterInfo, beforeInfo.GetHitTestBehavior());
    }

    void FillNativeAccessibilityElementInfo(
        ArkUI_AccessibilityElementInfo& beforeInfo,
        ArkUI_AccessibilityElementInfo& afterInfo)
    {
        NATIVE_ADD_ELEMENTINFO(SetParentId, &afterInfo, beforeInfo.GetParentId());
        NATIVE_ADD_ELEMENTINFO(SetElementId, &afterInfo, beforeInfo.GetElementId());
        NATIVE_ADD_ELEMENTINFO(SetSelectedTextStart,
            &afterInfo, beforeInfo.GetTextBeginSelected());
        NATIVE_ADD_ELEMENTINFO(SetSelectedTextEnd,
             &afterInfo, beforeInfo.GetTextEndSelected());
        NATIVE_ADD_ELEMENTINFO(SetCurrentItemIndex, &afterInfo, beforeInfo.GetCurrentIndex());
        NATIVE_ADD_ELEMENTINFO(SetStartItemIndex, &afterInfo, beforeInfo.GetBeginIndex());
        NATIVE_ADD_ELEMENTINFO(SetEndItemIndex, &afterInfo, beforeInfo.GetEndIndex());
        NATIVE_ADD_ELEMENTINFO(SetItemCount, &afterInfo, beforeInfo.GetItemCount());
        NATIVE_ADD_ELEMENTINFO(SetAccessibilityOffset, &afterInfo, beforeInfo.GetOffset());
        NATIVE_ADD_ELEMENTINFO(SetZIndex, &afterInfo, beforeInfo.GetZIndex());
        NATIVE_ADD_ELEMENTINFO(SetAccessibilityOpacity, &afterInfo, beforeInfo.GetOpacity());
        NATIVE_ADD_ELEMENTINFO(SetCheckable, &afterInfo, beforeInfo.IsCheckable());
        NATIVE_ADD_ELEMENTINFO(SetChecked, &afterInfo, beforeInfo.IsChecked());
        NATIVE_ADD_ELEMENTINFO(SetFocusable, &afterInfo, beforeInfo.IsFocusable());
        NATIVE_ADD_ELEMENTINFO(SetFocused, &afterInfo, beforeInfo.IsFocused());
        NATIVE_ADD_ELEMENTINFO(SetVisible, &afterInfo, beforeInfo.IsVisible());
        NATIVE_ADD_ELEMENTINFO(SetAccessibilityFocused,
            &afterInfo, beforeInfo.IsAccessibilityFocused());
        NATIVE_ADD_ELEMENTINFO(SetSelected, &afterInfo, beforeInfo.IsSelected());
        NATIVE_ADD_ELEMENTINFO(SetClickable, &afterInfo, beforeInfo.IsClickable());
        NATIVE_ADD_ELEMENTINFO(SetLongClickable, &afterInfo, beforeInfo.IsLongClickable());
        NATIVE_ADD_ELEMENTINFO(SetEnabled, &afterInfo, beforeInfo.IsEnabled());
        NATIVE_ADD_ELEMENTINFO(SetIsPassword, &afterInfo, beforeInfo.IsPassword());
        NATIVE_ADD_ELEMENTINFO(SetScrollable, &afterInfo, beforeInfo.IsScrollable());
        NATIVE_ADD_ELEMENTINFO(SetEditable, &afterInfo, beforeInfo.IsEditable());
        NATIVE_ADD_ELEMENTINFO(SetIsHint, &afterInfo, beforeInfo.IsHint());
        NATIVE_ADD_ELEMENTINFO(SetAccessibilityGroup,
            &afterInfo, beforeInfo.GetAccessibilityGroup());

        FillNativeAccessibilityElementInfoPart(beforeInfo, afterInfo);
    }

    void BuildNativeAccessibilityElementInfoPart(
        int32_t index,
        ArkUI_AccessibilityElementInfo& nativeInfo)
    {
        // screen rect
        auto leftTopX = ++index;
        auto leftTopY = ++index;
        auto rightBottomX = ++index;
        auto rightBottomY = ++index;
        ArkUI_AccessibleRect screenRect {leftTopX, leftTopY, rightBottomX, rightBottomY};
        nativeInfo.SetRect(screenRect);
        // rangeInfo
        auto min = ++index;
        auto max = ++index;
        auto current = ++index;
        ArkUI_AccessibleRangeInfo rangeInfo {min, max, current};
        nativeInfo.SetRangeInfo(rangeInfo);
        // GridInfo
        auto rowCount = ++index;
        auto columnCount = ++index;
        auto selectionMode = ++index;
        ArkUI_AccessibleGridInfo gridInfo {rowCount, columnCount, selectionMode};
        nativeInfo.SetGridInfo(gridInfo);
        // GridItemInfo
        auto heading = (++index) % BOOL_MASK;
        auto columnIndex = ++index;
        auto rowIndex = ++index;
        auto columnSpan = ++index;
        auto rowSpan = ++index;
        auto selected = (++index) % BOOL_MASK;
        ArkUI_AccessibleGridItemInfo gridItemInfo {heading, columnIndex, rowIndex, columnSpan, rowSpan, selected};
        nativeInfo.SetGridItemInfo(gridItemInfo);

        nativeInfo.SetComponentType(std::to_string(++index));
        nativeInfo.SetContents(std::to_string(++index));
        nativeInfo.SetHintText(std::to_string(++index));
        nativeInfo.SetAccessibilityText(std::to_string(++index));
        nativeInfo.SetAccessibilityDescription(std::to_string(++index));
        nativeInfo.SetAccessibilityLevel(std::to_string(++index));
        nativeInfo.SetBackgroundColor(std::to_string(++index));
        nativeInfo.SetBackgroundImage(std::to_string(++index));
        nativeInfo.SetBlur(std::to_string(++index));
        nativeInfo.SetHitTestBehavior(std::to_string(++index));
    }

    void BuildNativeAccessibilityElementInfo(
        int32_t index,
        ArkUI_AccessibilityElementInfo& nativeInfo)
    {
        nativeInfo.SetPageId(index);
        nativeInfo.SetParentId(++index);
        nativeInfo.SetElementId(++index);
        nativeInfo.SetTextBeginSelected(++index);
        nativeInfo.SetTextEndSelected(++index);
        nativeInfo.SetCurrentIndex(++index);
        nativeInfo.SetBeginIndex(++index);
        nativeInfo.SetEndIndex(++index);
        nativeInfo.SetItemCount(++index);
        nativeInfo.SetOffset(++index);
        nativeInfo.SetZIndex(++index);
        nativeInfo.SetOpacity(++index);
        nativeInfo.SetCheckable((++index) % BOOL_MASK);
        nativeInfo.SetChecked((++index) % BOOL_MASK);
        nativeInfo.SetFocusable((++index) % BOOL_MASK);
        nativeInfo.SetFocused((++index) % BOOL_MASK);
        nativeInfo.SetVisible((++index) % BOOL_MASK);
        nativeInfo.SetAccessibilityFocused((++index) % BOOL_MASK);
        nativeInfo.SetSelected((++index) % BOOL_MASK);
        nativeInfo.SetClickable((++index) % BOOL_MASK);
        nativeInfo.SetLongClickable((++index) % BOOL_MASK);
        nativeInfo.SetEnabled((++index) % BOOL_MASK);
        nativeInfo.SetPassword((++index) % BOOL_MASK);
        nativeInfo.SetScrollable((++index) % BOOL_MASK);
        nativeInfo.SetEditable((++index) % BOOL_MASK);
        nativeInfo.SetHint((++index) % BOOL_MASK);
        nativeInfo.SetAccessibilityGroup((++index) % BOOL_MASK);

        BuildNativeAccessibilityElementInfoPart(index, nativeInfo);
    }

    void CheckTransformElementInfoResultPart(
        ArkUI_AccessibilityElementInfo& beforeInfo,
        ArkUI_AccessibilityElementInfo& afterInfo)
    {
        // screen rect
        EXPECT_EQ(beforeInfo.GetScreenRect().leftTopX,
            afterInfo.GetScreenRect().leftTopX);
        EXPECT_EQ(beforeInfo.GetScreenRect().leftTopY,
            afterInfo.GetScreenRect().leftTopY);
        EXPECT_EQ(beforeInfo.GetScreenRect().rightBottomX,
            afterInfo.GetScreenRect().rightBottomX);
        EXPECT_EQ(beforeInfo.GetScreenRect().rightBottomY,
            afterInfo.GetScreenRect().rightBottomY);

        // rangeInfo
        EXPECT_EQ(beforeInfo.GetRangeInfo().min,
            afterInfo.GetRangeInfo().min);
        EXPECT_EQ(beforeInfo.GetRangeInfo().max,
            afterInfo.GetRangeInfo().max);
        EXPECT_EQ(beforeInfo.GetRangeInfo().current,
            afterInfo.GetRangeInfo().current);

        // GridInfo
        EXPECT_EQ(beforeInfo.GetGridInfo().rowCount,
            afterInfo.GetGridInfo().rowCount);
        EXPECT_EQ(beforeInfo.GetGridInfo().columnCount,
            afterInfo.GetGridInfo().columnCount);
        EXPECT_EQ(beforeInfo.GetGridInfo().selectionMode,
            afterInfo.GetGridInfo().selectionMode);

        // GridItemInfo
        EXPECT_EQ(beforeInfo.GetGridItemInfo().columnIndex,
            afterInfo.GetGridItemInfo().columnIndex);
        EXPECT_EQ(beforeInfo.GetGridItemInfo().rowIndex,
            afterInfo.GetGridItemInfo().rowIndex);
        EXPECT_EQ(beforeInfo.GetGridItemInfo().columnSpan,
            afterInfo.GetGridItemInfo().columnSpan);
        EXPECT_EQ(beforeInfo.GetGridItemInfo().rowSpan,
            afterInfo.GetGridItemInfo().rowSpan);
        EXPECT_EQ(beforeInfo.GetGridItemInfo().heading,
            afterInfo.GetGridItemInfo().heading);
        EXPECT_EQ(beforeInfo.GetGridItemInfo().selected,
            afterInfo.GetGridItemInfo().selected);

        EXPECT_EQ(beforeInfo.GetComponentType(), afterInfo.GetComponentType());
        EXPECT_EQ(beforeInfo.GetContents(), afterInfo.GetContents());
        EXPECT_EQ(beforeInfo.GetHintText(), afterInfo.GetHintText());
        EXPECT_EQ(beforeInfo.GetAccessibilityText(), afterInfo.GetAccessibilityText());
        EXPECT_EQ(beforeInfo.GetAccessibilityDescription(), afterInfo.GetAccessibilityDescription());
        EXPECT_EQ(beforeInfo.GetAccessibilityLevel(), afterInfo.GetAccessibilityLevel());
        EXPECT_EQ(beforeInfo.GetBackgroundColor(), afterInfo.GetBackgroundColor());
        EXPECT_EQ(beforeInfo.GetBlur(), afterInfo.GetBlur());
        EXPECT_EQ(beforeInfo.GetHitTestBehavior(), afterInfo.GetHitTestBehavior());
    }

    void CheckTransformElementInfoResult(
        ArkUI_AccessibilityElementInfo& beforeInfo,
        ArkUI_AccessibilityElementInfo& afterInfo)
    {
        // Page ID not trans
        EXPECT_EQ(beforeInfo.GetParentId(), afterInfo.GetParentId());
        EXPECT_EQ(beforeInfo.GetElementId(), afterInfo.GetElementId());
        EXPECT_EQ(beforeInfo.GetTextBeginSelected(), afterInfo.GetTextBeginSelected());
        EXPECT_EQ(beforeInfo.GetTextEndSelected(), afterInfo.GetTextEndSelected());
        EXPECT_EQ(beforeInfo.GetCurrentIndex(), afterInfo.GetCurrentIndex());
        EXPECT_EQ(beforeInfo.GetBeginIndex(), afterInfo.GetBeginIndex());
        EXPECT_EQ(beforeInfo.GetEndIndex(), afterInfo.GetEndIndex());
        EXPECT_EQ(beforeInfo.GetItemCount(), afterInfo.GetItemCount());
        EXPECT_EQ(beforeInfo.GetOffset(), afterInfo.GetOffset());
        EXPECT_EQ(beforeInfo.GetZIndex(), afterInfo.GetZIndex());
        EXPECT_EQ(beforeInfo.GetOpacity(), afterInfo.GetOpacity());
        EXPECT_EQ(beforeInfo.IsCheckable(), afterInfo.IsCheckable());
        EXPECT_EQ(beforeInfo.IsChecked(), afterInfo.IsChecked());
        EXPECT_EQ(beforeInfo.IsFocusable(), afterInfo.IsFocusable());
        EXPECT_EQ(beforeInfo.IsFocused(), afterInfo.IsFocused());
        EXPECT_EQ(beforeInfo.IsVisible(), afterInfo.IsVisible());
        EXPECT_EQ(beforeInfo.IsAccessibilityFocused(), afterInfo.IsAccessibilityFocused());
        EXPECT_EQ(beforeInfo.IsSelected(), afterInfo.IsSelected());
        EXPECT_EQ(beforeInfo.IsClickable(), afterInfo.IsClickable());
        EXPECT_EQ(beforeInfo.IsLongClickable(), afterInfo.IsLongClickable());
        EXPECT_EQ(beforeInfo.IsEnabled(), afterInfo.IsEnabled());
        EXPECT_EQ(beforeInfo.IsPassword(), afterInfo.IsPassword());
        EXPECT_EQ(beforeInfo.IsScrollable(), afterInfo.IsScrollable());
        EXPECT_EQ(beforeInfo.IsEditable(), afterInfo.IsEditable());
        EXPECT_EQ(beforeInfo.IsHint(), afterInfo.IsHint());
        EXPECT_EQ(beforeInfo.GetAccessibilityGroup(), afterInfo.GetAccessibilityGroup());

        CheckTransformElementInfoResultPart(beforeInfo, afterInfo);
    }
};

/**
 * @tc.name: accessibilityTest001
 * @tc.desc: native_interface_accessibility.cpp abnormal
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceAccessibilityTestNg, AccessibilityProviderTest001, TestSize.Level1)
{
    int32_t ret;
    char testStr[] = "test";
    int64_t testChildNodeIds[10];
    ArkUI_AccessibilityProvider testProvider;
    ArkUI_AccessibilityProviderCallbacks testCallbacks;
    ArkUI_AccessibilityEventInfo testEventInfo;
    ArkUI_AccessibilityElementInfo testElementInfo;

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityProviderRegisterCallback,
        &testProvider, &testCallbacks, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    OH_ArkUI_SendAccessibilityAsyncEvent(nullptr, &testEventInfo, MockProviderCallBack);
    OH_ArkUI_SendAccessibilityAsyncEvent(&testProvider, &testEventInfo, nullptr);
    OH_ArkUI_SendAccessibilityAsyncEvent(nullptr, &testEventInfo, nullptr);

    OH_ArkUI_DestoryAccessibilityElementInfo(nullptr);

    OH_ArkUI_DestoryAccessibilityEventInfo(nullptr);

    ret = OH_ArkUI_AccessibilityElementInfoSetElementId(nullptr, 0);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    ret = OH_ArkUI_AccessibilityElementInfoSetParentId(nullptr, 0);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetComponentType,
        &testElementInfo, testStr, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetContents,
        &testElementInfo, testStr, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetHintText,
        &testElementInfo, testStr, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetAccessibilityText,
        &testElementInfo, testStr, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetAccessibilityDescription,
        &testElementInfo, testStr, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    THREE_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetChildNodeIds,
        &testElementInfo, 0, testChildNodeIds, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
}

/**
 * @tc.name: accessibilityTest002
 * @tc.desc: native_interface_accessibility.cpp abnormal
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceAccessibilityTestNg, AccessibilityProviderTest002, TestSize.Level1)
{
    int32_t ret;
    ArkUI_AccessibilityElementInfo testElementInfo;
    ArkUI_AccessibleAction testOperationActions;
    ArkUI_AccessibleRect screenRect;

    THREE_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetOperationActions,
        &testElementInfo, 1, &testOperationActions, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    ret = OH_ArkUI_AccessibilityElementInfoSetOperationActions(&testElementInfo, 0, &testOperationActions);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetScreenRect,
        &testElementInfo, &screenRect, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetScreenRect,
        &testElementInfo, &screenRect, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetCheckable,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetChecked,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetFocusable,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetFocused,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetVisible,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetAccessibilityFocused,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetSelected,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetClickable,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetLongClickable,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetEnabled,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetIsPassword,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetScrollable,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetEditable,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetIsHint,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    ArkUI_AccessibleRangeInfo rangeInfo;
    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetRangeInfo,
        &testElementInfo, &rangeInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
}

/**
 * @tc.name: accessibilityTest003
 * @tc.desc: native_interface_accessibility.cpp abnormal
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceAccessibilityTestNg, AccessibilityProviderTest003, TestSize.Level1)
{
    ArkUI_AccessibilityElementInfo testElementInfo;
    char testStr[] = "test";

    ArkUI_AccessibleGridInfo gridInfo;
    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetGridInfo,
        &testElementInfo, &gridInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    ArkUI_AccessibleGridItemInfo gridItem;
    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetGridItemInfo,
        &testElementInfo, &gridItem, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetSelectedTextStart,
        &testElementInfo, 0, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetSelectedTextEnd,
        &testElementInfo, 0, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetCurrentItemIndex,
        &testElementInfo, 0, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetStartItemIndex,
        &testElementInfo, 0, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetEndItemIndex,
        &testElementInfo, 0, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetItemCount,
        &testElementInfo, 0, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetAccessibilityOffset,
        &testElementInfo, 0, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetAccessibilityGroup,
        &testElementInfo, true, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetAccessibilityLevel,
        &testElementInfo, testStr, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetZIndex,
        &testElementInfo, 0, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetAccessibilityOpacity,
        &testElementInfo, 0, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetBackgroundColor,
        &testElementInfo, testStr, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetBackgroundImage,
        &testElementInfo, testStr, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetBlur,
        &testElementInfo, testStr, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityElementInfoSetHitTestBehavior,
        &testElementInfo, testStr, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityEventSetEventType,
        &testElementInfo, ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_INVALID,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
}

/**
 * @tc.name: accessibilityTest004
 * @tc.desc: native_interface_accessibility.cpp abnormal
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceAccessibilityTestNg, AccessibilityProviderTest004, TestSize.Level1)
{
    ArkUI_AccessibilityEventInfo eventInfo;
    ArkUI_AccessibilityElementInfo elementInfo;
    int32_t ret;
    char testStr[] = "test";

    std::map<std::string, std::string> actionArguments;
    ArkUI_AccessibilityActionArguments arguments(actionArguments);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityEventSetTextAnnouncedForAccessibility,
        &eventInfo, testStr, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityEventSetRequestFocusId,
        &eventInfo, 0, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    TWO_PARAMETER_NULLPTR_TEST(AccessibilityEventSetElementInfo,
        &eventInfo, &elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    ret =  OH_ArkUI_FindAccessibilityActionArgumentByKey(nullptr, testStr, nullptr);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    ret =  OH_ArkUI_FindAccessibilityActionArgumentByKey(&arguments, nullptr, nullptr);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    ret =  OH_ArkUI_FindAccessibilityActionArgumentByKey(nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
}

/**
 * @tc.name: accessibilityTest005
 * @tc.desc: set elementinfo success
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceAccessibilityTestNg, AccessibilityUtilsTest005, TestSize.Level1)
{
    ArkUI_AccessibilityElementInfo beforeInfo;
    ArkUI_AccessibilityElementInfo afterInfo;

    BuildNativeAccessibilityElementInfo(1, beforeInfo);
    FillNativeAccessibilityElementInfo(beforeInfo, afterInfo); // set afterinfo by api
    CheckTransformElementInfoResult(beforeInfo, afterInfo);
}

/**
 * @tc.name: accessibilityTest006
 * @tc.desc: OH_ArkUI_AccessibilityProviderRegisterCallback
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceAccessibilityTestNg, AccessibilityUtilsTest006, TestSize.Level1)
{
    ArkUI_AccessibilityProvider provider;
    // 1. register call back nullptr return fail
    int32_t ret = OH_ArkUI_AccessibilityProviderRegisterCallback(&provider, nullptr);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    // 2 event null return fail
    g_errcode = 0;
    OH_ArkUI_SendAccessibilityAsyncEvent(&provider, nullptr, MockEventCallBack);
    EXPECT_EQ(g_errcode, SEND_EVENT_FAILED);

    // 3 event alloced
    ArkUI_AccessibilityEventInfo* eventInfo =  OH_ArkUI_CreateAccessibilityEventInfo();
    OH_ArkUI_SendAccessibilityAsyncEvent(&provider, eventInfo, MockEventCallBack);
    EXPECT_NE(eventInfo, nullptr);
    OH_ArkUI_DestoryAccessibilityEventInfo(eventInfo);
}

/**
 * @tc.name: accessibilityTest006
 * @tc.desc: OH_ArkUI_AccessibilityElementInfoSetChildNodeIds
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceAccessibilityTestNg, AccessibilityUtilsTest007, TestSize.Level1)
{
    int64_t ret;
    ArkUI_AccessibilityElementInfoList list;
    int64_t childNodeIds[MAX_CHILD_COUNT];

    // test OH_ArkUI_AddAndGetAccessibilityElementInfo
    ArkUI_AccessibilityElementInfo* elementInfo = OH_ArkUI_AddAndGetAccessibilityElementInfo(&list);
    EXPECT_NE(elementInfo, nullptr);

    // abnormal  nullptr
    THREE_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetChildNodeIds,
        elementInfo, 0, childNodeIds, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    // abnormal  childCount <= 0
    ret = OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(elementInfo, 0, childNodeIds);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    // add child
    std::vector<int64_t> childIdsVector;
    auto now = std::chrono::system_clock::now();
    int64_t childCount =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
        .count();
    childCount = (childCount % MAX_CHILD_COUNT) + 1;
    for (int64_t i = 0; i < childCount; i++) {
        childIdsVector.push_back(i);
        childNodeIds[i] = i;
    }

    ret = OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(elementInfo, childCount, childNodeIds);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);

    EXPECT_EQ(elementInfo->GetChildNodeIds(), childIdsVector);
}

/**
 * @tc.name: accessibilityTest008
 * @tc.desc: OH_ArkUI_AccessibilityElementInfoSetOperationActions
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceAccessibilityTestNg, AccessibilityUtilsTest008, TestSize.Level1)
{
    int64_t ret;
    ArkUI_AccessibleAction operationActions[MAX_ACTION_COUNT];

    // test OH_ArkUI_CreateAccessibilityElementInfo
    ArkUI_AccessibilityElementInfo* elementInfo = OH_ArkUI_CreateAccessibilityElementInfo();
    EXPECT_NE(elementInfo, nullptr);

    // abnormal  nullptr
    THREE_PARAMETER_NULLPTR_TEST_WITHOUT_SECOND(AccessibilityElementInfoSetOperationActions,
        elementInfo, 0, operationActions, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    // abnormal  operationCount <= 0
    ret = OH_ArkUI_AccessibilityElementInfoSetOperationActions(elementInfo, 0, operationActions);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);

    // add action
    auto now = std::chrono::system_clock::now();
    int64_t actionCount =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
        .count();
    actionCount = (actionCount % MAX_ACTION_COUNT) + 1;

    auto startIndex = actionCount;
    char string[MAX_ACTION_COUNT][MAX_C_STR_CHAR_COUNT];
    for (int64_t i = 0; i < actionCount; i++) {
        ArkUI_Accessibility_ActionType actionType
            = actionTypeVector[(startIndex + i) % actionTypeVector.size()];
        auto content = std::to_string(startIndex + i);
        (void)strcpy_s(string[i], MAX_C_STR_CHAR_COUNT, content.c_str());
        operationActions[i].actionType = actionType;
        operationActions[i].description = string[i];
    }
    ret = OH_ArkUI_AccessibilityElementInfoSetOperationActions(elementInfo, actionCount, operationActions);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);

    EXPECT_EQ(elementInfo->GetOperationActions().size(), actionCount);
    auto afterActionVetor = elementInfo->GetOperationActions();
    for (int64_t i = 0; i < actionCount; i++) {
        EXPECT_EQ(afterActionVetor[i].actionType,
            operationActions[i].actionType);
        std::string str1(afterActionVetor[i].description);
        std::string str2(operationActions[i].description);
        EXPECT_EQ(str1, str2);
    }
    OH_ArkUI_DestoryAccessibilityElementInfo(elementInfo);
}

/**
 * @tc.name: accessibilityTest009
 * @tc.desc: OH_ArkUI_AccessibilityElementInfoSetOperationActions
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceAccessibilityTestNg, AccessibilityUtilsTest009, TestSize.Level1)
{
    int64_t ret;
    ArkUI_AccessibleAction operationActions[MAX_ACTION_COUNT];

    // test OH_ArkUI_CreateAccessibilityElementInfo
    ArkUI_AccessibilityElementInfo* elementInfo = OH_ArkUI_CreateAccessibilityElementInfo();
    EXPECT_NE(elementInfo, nullptr);

    // add support action
    // ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_NEXT_HTML_ITEM
    // and ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_PREVIOUS_HTML_ITEM
    int32_t actionCount = 2;
    char string[MAX_ACTION_COUNT][MAX_C_STR_CHAR_COUNT];
    auto startIndex = actionCount;
    auto content = std::to_string(startIndex);
    (void)strcpy_s(string[0], MAX_C_STR_CHAR_COUNT, content.c_str());
    operationActions[0].actionType = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_NEXT_HTML_ITEM;
    operationActions[0].description = string[1];
    content = std::to_string(startIndex + 1);
    (void)strcpy_s(string[1], MAX_C_STR_CHAR_COUNT, content.c_str());
    operationActions[1].actionType = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_PREVIOUS_HTML_ITEM;
    operationActions[1].description = string[1];

    ret = OH_ArkUI_AccessibilityElementInfoSetOperationActions(elementInfo, actionCount, operationActions);
    EXPECT_EQ(ret, ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL);

    EXPECT_EQ(elementInfo->GetOperationActions().size(), actionCount);
    auto afterActionVetor = elementInfo->GetOperationActions();
    for (int64_t i = 0; i < actionCount; i++) {
        EXPECT_EQ(afterActionVetor[i].actionType,
            operationActions[i].actionType);
        std::string str1(afterActionVetor[i].description);
        std::string str2(operationActions[i].description);
        EXPECT_EQ(str1, str2);
    }
    OH_ArkUI_DestoryAccessibilityElementInfo(elementInfo);
}
} // namespace OHOS::Ace::NG
