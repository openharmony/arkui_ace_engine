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
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include <arkui/native_interface_accessibility.h>
#include "fake_node.h"
namespace NativeXComponentSample {
const int32_t NUMBER_MIN = 0;
const int32_t NUMBER_CURRENT = 20;
const int32_t NUMBER_MAX = 100;
const int32_t NUMBER_COUNT = 5;
const int32_t NUMBER_INDEX = 5;
const int32_t NUMBER_SPAN = 2;

void AccessibleObject::fillAccessibilityElement(ArkUI_AccessibilityElementInfo *element)
{
    // Set the properties of the accessibility element based on the properties of the node.
    if (!accessibilityText_.empty()) {
        OH_ArkUI_AccessibilityElementInfoSetAccessibilityText(element, accessibilityText_.data());
    }
    if (!accessibilityDescription_.empty()) {
        OH_ArkUI_AccessibilityElementInfoSetAccessibilityDescription(element, accessibilityDescription_.data());
    }
    OH_ArkUI_AccessibilityElementInfoSetComponentType(element, ObjectType());
    OH_ArkUI_AccessibilityElementInfoSetContents(element, Name().data());
    OH_ArkUI_AccessibilityElementInfoSetIsHint(element, Focused());
    OH_ArkUI_AccessibilityElementInfoSetHintText(element, Hint());
    OH_ArkUI_AccessibilityElementInfoSetVisible(element, IsVisible());
    OH_ArkUI_AccessibilityElementInfoSetEnabled(element, IsEnable());
    OH_ArkUI_AccessibilityElementInfoSetClickable(element, Clickable());
    OH_ArkUI_AccessibilityElementInfoSetFocusable(element, Focusable());
    OH_ArkUI_AccessibilityElementInfoSetFocused(element, Focused());
    OH_ArkUI_AccessibilityElementInfoSetIsPassword(element, isPassword_);
    OH_ArkUI_AccessibilityElementInfoSetScrollable(element, isScrollable_);
    OH_ArkUI_AccessibilityElementInfoSetLongClickable(element, isLongClick_);
    OH_ArkUI_AccessibilityElementInfoSetEditable(element, true);
    OH_ArkUI_AccessibilityElementInfoSetAccessibilityGroup(element, isGroup_);
    OH_ArkUI_AccessibilityElementInfoSetCheckable(element, checkable_);
    OH_ArkUI_AccessibilityElementInfoSetChecked(element, checked_);
    OH_ArkUI_AccessibilityElementInfoSetSelected(element, isSelected_);
    OH_ArkUI_AccessibilityElementInfoSetAccessibilityFocused(element, Focused());
    OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(element, accessibilityLevel_.data());
    if (ObjectType() == "FakeSlider") {
        OH_ArkUI_AccessibilityElementInfoSetRangeInfo(element, &rangeInfo_);
    }
    if (ObjectType() == "FakeList") {
        OH_ArkUI_AccessibilityElementInfoSetGridInfo(element, &gridInfo_);
    }
    if (ObjectType() == "FakeSwiper") {
        OH_ArkUI_AccessibilityElementInfoSetGridItemInfo(element, &gridItemInfo_);
    }
    if (selectedTextStart_ < selectedTextEnd_) {
        if (0 <= selectedTextStart_ && selectedTextStart_ <= static_cast<int>(accessibilityText_.size())) {
            OH_ArkUI_AccessibilityElementInfoSetSelectedTextStart(element, selectedTextStart_);
        }
        if (0 <= selectedTextEnd_ && selectedTextEnd_ <= static_cast<int>(accessibilityText_.size())) {
            OH_ArkUI_AccessibilityElementInfoSetSelectedTextEnd(element, selectedTextEnd_);
        }
    }
    if ((itemCount_ >= endItemIndex_) && (endItemIndex_ > 0) && (startItemIndex_ <= currentItemIndex_) &&
        (currentItemIndex_ <= endItemIndex_)) {
        OH_ArkUI_AccessibilityElementInfoSetItemCount(element, itemCount_);
        OH_ArkUI_AccessibilityElementInfoSetStartItemIndex(element, startItemIndex_);
        OH_ArkUI_AccessibilityElementInfoSetCurrentItemIndex(element, currentItemIndex_);
        OH_ArkUI_AccessibilityElementInfoSetEndItemIndex(element, endItemIndex_);
    }
    OH_ArkUI_AccessibilityElementInfoSetAccessibilityOffset(element, offset_);
    OH_ArkUI_AccessibilityElementInfoSetZIndex(element, zIndex_);
    OH_ArkUI_AccessibilityElementInfoSetAccessibilityOpacity(element, opacity_);
    OH_ArkUI_AccessibilityElementInfoSetBackgroundImage(element, backgroundImage_.data());
    OH_ArkUI_AccessibilityElementInfoSetBackgroundColor(element, backgroundColor_.data());
    OH_ArkUI_AccessibilityElementInfoSetBlur(element, blue_.data());
    OH_ArkUI_AccessibilityElementInfoSetHitTestBehavior(element, hitTestBehavior_.data());
    
    ArkUI_AccessibleAction actions[10];
    int index = 0;
    if (this->Clickable()) {
        actions[index].actionType = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK;
        actions[index].description = "Click";
        index++;
    }

    if (this->Focusable()) {
        actions[index].actionType = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS;
        actions[index].description = "Focus";
        index++;
        actions[index].actionType = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS;
        actions[index].description = "ClearFocus";
        index++;
    }
    if (index > 0) {
        OH_ArkUI_AccessibilityElementInfoSetOperationActions(element, index, actions);
    }
}

void FakeWidget::AddButton(const bool fillText, const bool fillDescription)
{
    static int i = 1;
    auto node = new FakeButton("button" + std::to_string(i));
    if (fillText) {
        node->SetAccessibilityText("this is Text for button.");
    }
    if (fillDescription) {
        node->SetAccessibilityDescription("this is Description for button.");
    }
    objects.push_back(node);
    i++;
}

void FakeWidget::AddText(const bool fillText, const bool fillDescription)
{
    static int i = 1;
    auto node = new FakeText("text" + std::to_string(i));
    if (fillText) {
        node->SetAccessibilityText("this is Text for text.");
    }
    if (fillDescription) {
        node->SetAccessibilityDescription("this is Description for text.");
    }
    objects.push_back(node);
    i++;
}

void FakeWidget::AddSlider(const bool fillText, const bool fillDescription)
{
    static int i = 1;
    auto node = new FakeSlider("slider" + std::to_string(i));
    ArkUI_AccessibleRangeInfo rangeInfo;
    rangeInfo.current = NUMBER_CURRENT;
    rangeInfo.min = NUMBER_MIN;
    rangeInfo.max = NUMBER_MAX;
    node->SetRangeInfo(rangeInfo);
    if (fillText) {
        node->SetAccessibilityText("this is Text for slider.");
    }
    if (fillDescription) {
        node->SetAccessibilityDescription("this is Description for slider.");
    }
    objects.push_back(node);
    i++;
}
void FakeWidget::AddList(const bool fillText, const bool fillDescription)
{
    static int i = 1;
    auto node = new FakeList("list" + std::to_string(i));
    ArkUI_AccessibleGridInfo gridInfo;
    gridInfo.columnCount = NUMBER_COUNT;
    gridInfo.rowCount = NUMBER_COUNT;
    gridInfo.selectionMode = NUMBER_MIN;
    node->SetGridInfo(gridInfo);
    if (fillText) {
        node->SetAccessibilityText("this is Text for list.");
    }
    if (fillDescription) {
        node->SetAccessibilityDescription("this is Description for list.");
    }
    objects.push_back(node);
    i++;
}

void FakeWidget::AddSwiper(const bool fillText, const bool fillDescription)
{
    static int i = 1;
    auto node = new FakeSwiper("swiper" + std::to_string(i));
    ArkUI_AccessibleGridItemInfo gridItemInfo;
    gridItemInfo.rowSpan = NUMBER_SPAN;
    gridItemInfo.rowIndex = NUMBER_INDEX;
    gridItemInfo.columnSpan = NUMBER_SPAN;
    gridItemInfo.columnIndex = NUMBER_INDEX;
    gridItemInfo.selected = true;
    gridItemInfo.heading = true;
    node->SetGridItemInfo(gridItemInfo);
    if (fillText) {
        node->SetAccessibilityText("this is Text for list.");
    }
    if (fillDescription) {
        node->SetAccessibilityDescription("this is Description for list.");
    }
    objects.push_back(node);
    i++;
}
}