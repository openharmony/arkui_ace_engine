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

#include "native_interface_accessibility.h"

#include <cmath>
#include <map>

#include "base/utils/utils.h"
#include "frameworks/core/accessibility/native_interface_accessibility_impl.h"
#include "frameworks/core/accessibility/native_interface_accessibility_provider.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

using ::ArkUI_AccessibilityElementInfo;
using ::ArkUI_AccessibilityEventInfo;
using ::ArkUI_AccessibilityActionArguments;
using ::ArkUI_AccessibilityElementInfoList;

int32_t OH_ArkUI_AccessibilityProviderRegisterCallback(
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityProviderCallbacks* callbacks)
{
    if ((provider == nullptr) || (callbacks == nullptr)) {
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER;
    }
    return provider->AccessibilityProviderRegisterCallback(callbacks);
}

void OH_ArkUI_SendAccessibilityAsyncEvent(
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityEventInfo* eventInfo,
    void (*callback)(int32_t errorCode))
{
    if ((provider == nullptr) || (callback == nullptr)) {
        return;
    }
    provider->SendAccessibilityAsyncEvent(eventInfo, callback);
}

ArkUI_AccessibilityElementInfo* OH_ArkUI_AddAndGetAccessibilityElementInfo(
    ArkUI_AccessibilityElementInfoList* list)
{
    auto elementInfo = list->AddAndGetElementInfo();
    return elementInfo;
}

ArkUI_AccessibilityElementInfo* OH_ArkUI_CreateAccessibilityElementInfo(void)
{
    auto elementInfo = new (std::nothrow) ArkUI_AccessibilityElementInfo();
    if (elementInfo == nullptr) {
        return nullptr;
    }
    return elementInfo;
}

void OH_ArkUI_DestoryAccessibilityElementInfo(
    ArkUI_AccessibilityElementInfo* elementInfo)
{
    if (elementInfo == nullptr) {
        return;
    }
    delete elementInfo;
}

ArkUI_AccessibilityEventInfo* OH_ArkUI_CreateAccessibilityEventInfo(void)
{
    auto eventInfo = new (std::nothrow) ArkUI_AccessibilityEventInfo();
    if (eventInfo == nullptr) {
        return nullptr;
    }
    return eventInfo;
}

void OH_ArkUI_DestoryAccessibilityEventInfo(ArkUI_AccessibilityEventInfo* eventInfo)
{
    if (eventInfo == nullptr) {
        return;
    }
    delete eventInfo;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetElementId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t elementId)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetElementId(elementId);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetParentId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t parentId)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetParentId(parentId);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetComponentType(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* componentType)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(componentType, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetComponentType(componentType);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetContents(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* contents)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(contents, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetContents(contents);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetHintText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hintText)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(hintText, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetHintText(hintText);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityText)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(accessibilityText, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetAccessibilityText(accessibilityText);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityDescription(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityDescription)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(accessibilityDescription, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetAccessibilityDescription(accessibilityDescription);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t childCount, int64_t* childNodeIds)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(childNodeIds, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    if (childCount <= 0) {
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER;
    }
    elementInfo->ClearChildNodeIds();
    for (int32_t i = 0; i < childCount; i++) {
        elementInfo->AddChildNodeId(childNodeIds[i]);
    }
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetOperationActions(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t operationCount,
    ArkUI_AccessibleAction* operationActions)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(operationActions, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    if (operationCount <= 0) {
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER;
    }
    elementInfo->ClearOperationActions();
    for (int32_t i = 0; i < operationCount; i++) {
        elementInfo->AddOperationAction(operationActions[i]);
    }
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetScreenRect(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRect* screenRect)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(screenRect, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetRect(*screenRect);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetCheckable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checkable)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetCheckable(checkable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetChecked(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checked)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetChecked(checked);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetFocusable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool focusable)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetFocusable(focusable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isFocused)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetFocused(isFocused);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetVisible(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isVisible)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetVisible(isVisible);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityFocused)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetAccessibilityFocused(accessibilityFocused);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetSelected(
    ArkUI_AccessibilityElementInfo* elementInfo, bool selected)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetSelected(selected);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool clickable)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetClickable(clickable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetLongClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool longClickable)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetLongClickable(longClickable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetEnabled(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isEnabled)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetEnabled(isEnabled);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetIsPassword(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isPassword)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetPassword(isPassword);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetScrollable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool scrollable)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetScrollable(scrollable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetEditable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool editable)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetEditable(editable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetIsHint(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isHint)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetHint(isHint);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetRangeInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRangeInfo* rangeInfo)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(rangeInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetRangeInfo(*rangeInfo);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetGridInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridInfo* gridInfo)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(gridInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetGridInfo(*gridInfo);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetGridItemInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridItemInfo* gridItem)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(gridItem, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetGridItemInfo(*gridItem);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetSelectedTextStart(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t selectedTextStart)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetTextBeginSelected(selectedTextStart);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetSelectedTextEnd(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t selectedTextEnd)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetTextEndSelected(selectedTextEnd);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetCurrentItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t currentItemIndex)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetCurrentIndex(currentItemIndex);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetStartItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t startItemIndex)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetBeginIndex(startItemIndex);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetEndItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t endItemIndex)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetEndIndex(endItemIndex);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetItemCount(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t itemCount)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetItemCount(itemCount);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityOffset(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t offset)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetOffset(offset);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityGroup(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityGroup)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetAccessibilityGroup(accessibilityGroup);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityLevel)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(accessibilityLevel, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetAccessibilityLevel(accessibilityLevel);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetZIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t zIndex)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetZIndex(zIndex);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityOpacity(
    ArkUI_AccessibilityElementInfo* elementInfo, float opacity)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    if (std::isnan(opacity)) {
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER;
    }
    elementInfo->SetOpacity(opacity);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetBackgroundColor(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundColor)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(backgroundColor, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetBackgroundColor(backgroundColor);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetBackgroundImage(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundImage)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(backgroundImage, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetBackgroundImage(backgroundImage);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetBlur(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* blur)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(blur, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetBlur(blur);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetHitTestBehavior(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hitTestBehavior)
{
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(hitTestBehavior, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    elementInfo->SetHitTestBehavior(hitTestBehavior);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityEventSetEventType(
    ArkUI_AccessibilityEventInfo* eventInfo, ArkUI_AccessibilityEventType eventType)
{
    CHECK_NULL_RETURN(eventInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    eventInfo->SetEventType(eventType);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityEventSetTextAnnouncedForAccessibility(
    ArkUI_AccessibilityEventInfo* eventInfo, const char* textAnnouncedForAccessibility)
{
    CHECK_NULL_RETURN(eventInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    eventInfo->SetTextAnnouncedForAccessibility(textAnnouncedForAccessibility);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityEventSetRequestFocusId(
    ArkUI_AccessibilityEventInfo* eventInfo, int32_t requestFocusId)
{
    CHECK_NULL_RETURN(eventInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    eventInfo->SetRequestFocusId(requestFocusId);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityEventSetElementInfo(
    ArkUI_AccessibilityEventInfo* eventInfo, ArkUI_AccessibilityElementInfo* elementInfo)
{
    CHECK_NULL_RETURN(eventInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(elementInfo, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    eventInfo->SetElementInfo(elementInfo);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_FindAccessibilityActionArgumentByKey(
    ArkUI_AccessibilityActionArguments* arguments, const char* key, char** value)
{
    CHECK_NULL_RETURN(arguments, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(key, ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER);
    *value = const_cast<char*>(arguments->FindValueByKey(key));
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

#ifdef __cplusplus
};
#endif

