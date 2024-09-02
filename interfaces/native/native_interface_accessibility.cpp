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
        return OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER;
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

int32_t OH_ArkUI_SetAccessibilityElementInfoElementId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t elementId)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetElementId(elementId);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoComponentId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t componentId)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetComponentId(componentId);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoParentId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t parentId)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetParentId(parentId);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoComponentType(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* componentType)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(componentType, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetComponentType(componentType);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoContents(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* contents)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(contents, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetContents(contents);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoHintText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hintText)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(hintText, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetHintText(hintText);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityText)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(accessibilityText, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetAccessibilityText(accessibilityText);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityDescription(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityDescription)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(accessibilityDescription, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetAccessibilityDescription(accessibilityDescription);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoChildNodeIds(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t childCount, int64_t* childNodeIds)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(childNodeIds, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    if (childCount <= 0) {
        return OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER;
    }
    elementInfo->ClearChildNodeIds();
    for (int32_t i = 0; i < childCount; i++) {
        elementInfo->AddChildNodeId(childNodeIds[i]);
    }
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoOperationActions(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t operationCount,
    ArkUI_AccessibleAction* operationActions)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(operationActions, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    if (operationCount <= 0) {
        return OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER;
    }
    elementInfo->ClearChildNodeIds();
    for (int32_t i = 0; i < operationCount; i++) {
        elementInfo->AddOperationAction(operationActions[i]);
    }
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoScreenRect(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRect* screenRect)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(screenRect, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetRect(*screenRect);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoCheckable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checkable)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetCheckable(checkable);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoChecked(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checked)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetChecked(checked);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoFocusable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool focusable)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetFocusable(focusable);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isFocused)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetFocused(isFocused);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoVisible(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isVisible)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetVisible(isVisible);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityFocused)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetAccessibilityFocused(accessibilityFocused);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoSelected(
    ArkUI_AccessibilityElementInfo* elementInfo, bool selected)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetSelected(selected);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool clickable)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetClickable(clickable);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoLongClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool longClickable)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetLongClickable(longClickable);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoEnabled(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isEnabled)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetEnabled(isEnabled);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoIsPassword(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isPassword)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetPassword(isPassword);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoScrollable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool scrollable)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetScrollable(scrollable);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoEditable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool editable)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetEditable(editable);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoIsHint(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isHint)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetHint(isHint);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoRangeInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRangeInfo* rangeInfo)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(rangeInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetRangeInfo(*rangeInfo);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoGridInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridInfo* gridInfo)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(gridInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetGridInfo(*gridInfo);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoGridItemInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridItemInfo* gridItem)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(gridItem, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetGridItemInfo(*gridItem);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoTextBeginSelected(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t textBeginSelected)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetTextBeginSelected(textBeginSelected);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoTextEndSelected(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t textEndSelected)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetTextEndSelected(textEndSelected);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoCurrentItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t currentItemIndex)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetCurrentIndex(currentItemIndex);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoBeginItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t beginItemIndex)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetBeginIndex(beginItemIndex);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoEndItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t endItemIndex)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetEndIndex(endItemIndex);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoItemCount(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t itemCount)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetItemCount(itemCount);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityOffset(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t offset)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetOffset(offset);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityGroup(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityGroup)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetAccessibilityGroup(accessibilityGroup);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityLevel(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityLevel)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(accessibilityLevel, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetAccessibilityLevel(accessibilityLevel);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoZIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t zIndex)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetZIndex(zIndex);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoAccessibilityOpacity(
    ArkUI_AccessibilityElementInfo* elementInfo, float opacity)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    if (std::isnan(opacity)) {
        return OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER;
    }
    elementInfo->SetOpacity(opacity);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoBackgroundColor(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundColor)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(backgroundColor, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetBackgroundColor(backgroundColor);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoBackgroundImage(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundImage)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(backgroundImage, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetBackgroundImage(backgroundImage);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoBlur(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* blur)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(blur, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetBlur(blur);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityElementInfoHitTestBehavior(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hitTestBehavior)
{
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(hitTestBehavior, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    elementInfo->SetHitTestBehavior(hitTestBehavior);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityEventEventType(
    ArkUI_AccessibilityEventInfo* eventInfo, ArkUI_AccessibilityEventType eventType)
{
    CHECK_NULL_RETURN(eventInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    eventInfo->SetEventType(eventType);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityEventTextAnnouncedForAccessibility(
    ArkUI_AccessibilityEventInfo* eventInfo, const char* textAnnouncedForAccessibility)
{
    CHECK_NULL_RETURN(eventInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    eventInfo->SetTextAnnouncedForAccessibility(textAnnouncedForAccessibility);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityEventRequestFocusId(
    ArkUI_AccessibilityEventInfo* eventInfo, int32_t requestFocusId)
{
    CHECK_NULL_RETURN(eventInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    eventInfo->SetRequestFocusId(requestFocusId);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_SetAccessibilityEventElementInfo(
    ArkUI_AccessibilityEventInfo* eventInfo, ArkUI_AccessibilityElementInfo* elementInfo)
{
    CHECK_NULL_RETURN(eventInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(elementInfo, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    eventInfo->SetElementInfo(elementInfo);
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

int32_t OH_ArkUI_FindAccessibilityActionArgumentByKey(
    ArkUI_AccessibilityActionArguments* arguments, const char* key, char** value)
{
    CHECK_NULL_RETURN(arguments, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    CHECK_NULL_RETURN(key, OH_ARKUI_ACCESSIBILITY_RESULT_BAD_PARAMETER);
    *value = const_cast<char*>(arguments->FindValueByKey(key));
    return OH_ARKUI_ACCESSIBILITY_RESULT_SUCCESS;
}

#ifdef __cplusplus
};
#endif

