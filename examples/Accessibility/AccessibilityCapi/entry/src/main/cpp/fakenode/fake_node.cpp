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

#include <arkui/native_interface_accessibility.h>

#include "fake_node.h"


namespace {

const int MAX_ACTION_COUNT = 10;        // Maximum number of actions
const int MAX_CHILD_NODES = 1024;       // Maximum number of child nodes
const int PARENT_OF_ROOT = -2100000;    // Parent ID for root node
const int32_t RANGE_VALUE_MIN = 0;      // Minimum range value
const int32_t RANGE_VALUE_CURRENT = 20; // Current range value
const int32_t RANGE_VALUE_MAX = 100;    // Maximum range value
const int32_t GRID_COUNT_VALUE = 5;     // Grid count value
const int32_t GRID_INDEX_VALUE = 5;     // Grid index value
const int32_t GRID_SPAN_VALUE = 2;      // Grid span value
const int BOOL_TRUE = 1;                // Boolean true value

} // namespace


namespace NativeXComponentSample {

/**
 * @brief Fills an accessibility element with information from this accessible object
 * @param element Pointer to the accessibility element info to be filled
 *
 * This method populates the accessibility element with all relevant properties
 * including text, description, component type, state information, and supported actions.
 */
void AccessibleObject::fillAccessibilityElement(ArkUI_AccessibilityElementInfo *element)
{
    // Set the properties of the accessibility element based on the properties of the node.
    if (!accessibilityText_.empty()) {
        OH_ArkUI_AccessibilityElementInfoSetAccessibilityText(
            element, accessibilityText_.data());
    }
    if (!accessibilityDescription_.empty()) {
        OH_ArkUI_AccessibilityElementInfoSetAccessibilityDescription(
            element, accessibilityDescription_.data());
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
    OH_ArkUI_AccessibilityElementInfoSetSelected(element, checkable_);
    OH_ArkUI_AccessibilityElementInfoSetAccessibilityFocused(element, Focused());
    OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(
        element, accessibilityLevel_.data());
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
        if (RANGE_VALUE_MIN <= selectedTextStart_ &&
            selectedTextStart_ <= static_cast<int>(accessibilityText_.size())) {
            OH_ArkUI_AccessibilityElementInfoSetSelectedTextStart(
                element, selectedTextStart_);
        }
        if (RANGE_VALUE_MIN <= selectedTextEnd_ &&
            selectedTextEnd_ <= static_cast<int>(accessibilityText_.size())) {
            OH_ArkUI_AccessibilityElementInfoSetSelectedTextEnd(
                element, selectedTextEnd_);
        }
    }
    if ((itemCount_ >= endItemIndex_) && (endItemIndex_ > RANGE_VALUE_MIN) &&
        (startItemIndex_ <= currentItemIndex_) &&
        (currentItemIndex_ <= endItemIndex_)) {
        OH_ArkUI_AccessibilityElementInfoSetItemCount(element, itemCount_);
        OH_ArkUI_AccessibilityElementInfoSetStartItemIndex(
            element, startItemIndex_);
        OH_ArkUI_AccessibilityElementInfoSetCurrentItemIndex(
            element, currentItemIndex_);
        OH_ArkUI_AccessibilityElementInfoSetEndItemIndex(element, endItemIndex_);
    }
    OH_ArkUI_AccessibilityElementInfoSetAccessibilityOffset(element, offset_);
    OH_ArkUI_AccessibilityElementInfoSetZIndex(element, zIndex_);
    OH_ArkUI_AccessibilityElementInfoSetAccessibilityOpacity(element, opacity_);
    OH_ArkUI_AccessibilityElementInfoSetBackgroundImage(
        element, backgroundImage_.data());
    OH_ArkUI_AccessibilityElementInfoSetBackgroundColor(
        element, backgroundColor_.data());
    OH_ArkUI_AccessibilityElementInfoSetBlur(element, blue_.data());
    OH_ArkUI_AccessibilityElementInfoSetHitTestBehavior(
        element, hitTestBehavior_.data());

    ArkUI_AccessibleAction actions[MAX_ACTION_COUNT];
    int index = 0;
    if (this->Clickable()) {
        actions[index].actionType = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK;
        actions[index].description = "Click";
        index++;
    }

    if (this->Focusable()) {
        actions[index].actionType =
            ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS;
        actions[index].description = "Focus";
        index++;
        actions[index].actionType =
            ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS;
        actions[index].description = "ClearFocus";
        index++;
    }
    if (index > RANGE_VALUE_MIN) {
        OH_ArkUI_AccessibilityElementInfoSetOperationActions(
            element, index, actions);
    }
}

/**
 * @brief Adds a button node to the widget
 * @param fillText Whether to fill accessibility text for the button
 * @param fillDescription Whether to fill accessibility description for the button
 */
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

/**
 * @brief Adds a text node to the widget
 * @param fillText Whether to fill accessibility text for the text
 * @param fillDescription Whether to fill accessibility description for the text
 */
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

/**
 * @brief Adds a slider node to the widget
 * @param fillText Whether to fill accessibility text for the slider
 * @param fillDescription Whether to fill accessibility description for the slider
 */
void FakeWidget::AddSlider(const bool fillText, const bool fillDescription)
{
    static int i = 1;
    auto node = new FakeSlider("slider" + std::to_string(i));
    ArkUI_AccessibleRangeInfo rangeInfo;
    rangeInfo.current = RANGE_VALUE_CURRENT;
    rangeInfo.min = RANGE_VALUE_MIN;
    rangeInfo.max = RANGE_VALUE_MAX;
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

/**
 * @brief Adds a list node to the widget
 * @param fillText Whether to fill accessibility text for the list
 * @param fillDescription Whether to fill accessibility description for the list
 */
void FakeWidget::AddList(const bool fillText, const bool fillDescription)
{
    static int i = 1;
    auto node = new FakeList("list" + std::to_string(i));
    ArkUI_AccessibleGridInfo gridInfo;
    gridInfo.columnCount = GRID_COUNT_VALUE;
    gridInfo.rowCount = GRID_COUNT_VALUE;
    gridInfo.selectionMode = RANGE_VALUE_MIN;
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

/**
 * @brief Adds a swiper node to the widget
 * @param fillText Whether to fill accessibility text for the swiper
 * @param fillDescription Whether to fill accessibility description for the swiper
 */
void FakeWidget::AddSwiper(const bool fillText, const bool fillDescription)
{
    static int i = 1;
    auto node = new FakeSwiper("swiper" + std::to_string(i));
    ArkUI_AccessibleGridItemInfo gridItemInfo;
    gridItemInfo.rowSpan = GRID_SPAN_VALUE;
    gridItemInfo.rowIndex = GRID_INDEX_VALUE;
    gridItemInfo.columnSpan = GRID_SPAN_VALUE;
    gridItemInfo.columnIndex = GRID_INDEX_VALUE;
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

} // namespace NativeXComponentSample
