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
#include <new>
#include <string>

#include "base/utils/utils.h"
#include "frameworks/core/accessibility/native_interface_accessibility_impl.h"
#include "frameworks/core/accessibility/native_interface_accessibility_provider.h"
#include "interfaces/native/node/node_model.h"
#include "interfaces/native/native_error_message_macros.h"
#include "native_type.h"

namespace {
int32_t ReturnAccessibilityResultWithFunctionName(
    int32_t result, int32_t successCode, const char* functionName)
{
    if (result != successCode) {
        SET_ERROR_FUNCTION_NAME(functionName);
    }
    return result;
}
} // namespace

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
        SET_ERROR_MESSAGE(ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER,
            __FUNCTION__, "provider or callbacks is null");
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER;
    }
    return ReturnAccessibilityResultWithFunctionName(
        provider->AccessibilityProviderRegisterCallback(callbacks),
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL, __FUNCTION__);
}

int32_t OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance(
    const char* instanceId, ArkUI_AccessibilityProvider* provider,
    ArkUI_AccessibilityProviderCallbacksWithInstance* callbacks)
{
    if ((instanceId == nullptr) || (provider == nullptr) || (callbacks == nullptr)) {
        SET_ERROR_MESSAGE(ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER,
            __FUNCTION__, "instanceId, provider, or callbacks is null");
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER;
    }
    return ReturnAccessibilityResultWithFunctionName(
        provider->AccessibilityProviderRegisterCallbackWithInstance(instanceId, callbacks),
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL, __FUNCTION__);
}

void OH_ArkUI_SendAccessibilityAsyncEvent(
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityEventInfo* eventInfo,
    void (*callback)(int32_t errorCode))
{
    if ((provider == nullptr) || (callback == nullptr)) {
        SET_ERROR_MESSAGE(ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER,
            __FUNCTION__, "provider or callback is null");
        return;
    }
    provider->SendAccessibilityAsyncEvent(eventInfo, callback);
}

ArkUI_AccessibilityElementInfo* OH_ArkUI_AddAndGetAccessibilityElementInfo(
    ArkUI_AccessibilityElementInfoList* list)
{
    if (list == nullptr) {
        SET_ERROR_MESSAGE(
            ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
            "list is null");
        return nullptr;
    }
    auto elementInfo = list->AddAndGetElementInfo();
    return elementInfo;
}

ArkUI_AccessibilityElementInfo* OH_ArkUI_CreateAccessibilityElementInfo(void)
{
    auto elementInfo = new (std::nothrow) ArkUI_AccessibilityElementInfo();
    if (elementInfo == nullptr) {
        SET_ERROR_MESSAGE(ARKUI_ACCESSIBILITY_NATIVE_RESULT_OUT_OF_MEMORY,
            __FUNCTION__, "Failed to create accessibility element info");
        return nullptr;
    }
    return elementInfo;
}

void OH_ArkUI_DestoryAccessibilityElementInfo(
    ArkUI_AccessibilityElementInfo* elementInfo)
{
    if (elementInfo == nullptr) {
        SET_ERROR_MESSAGE(
            ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
            "elementInfo is null");
        return;
    }
    delete elementInfo;
}

ArkUI_AccessibilityEventInfo* OH_ArkUI_CreateAccessibilityEventInfo(void)
{
    auto eventInfo = new (std::nothrow) ArkUI_AccessibilityEventInfo();
    if (eventInfo == nullptr) {
        SET_ERROR_MESSAGE(ARKUI_ACCESSIBILITY_NATIVE_RESULT_OUT_OF_MEMORY,
            __FUNCTION__, "Failed to create accessibility event info");
        return nullptr;
    }
    return eventInfo;
}

void OH_ArkUI_DestoryAccessibilityEventInfo(ArkUI_AccessibilityEventInfo* eventInfo)
{
    if (eventInfo == nullptr) {
        SET_ERROR_MESSAGE(
            ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
            "eventInfo is null");
        return;
    }
    delete eventInfo;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetElementId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t elementId)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetElementId(elementId);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetParentId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t parentId)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetParentId(parentId);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetComponentType(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* componentType)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        componentType,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "componentType is null");
    elementInfo->SetComponentType(componentType);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetContents(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* contents)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        contents,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "contents is null");
    elementInfo->SetContents(contents);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetHintText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hintText)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        hintText,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "hintText is null");
    elementInfo->SetHintText(hintText);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityText)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        accessibilityText,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "accessibilityText is null");
    elementInfo->SetAccessibilityText(accessibilityText);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityDescription(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityDescription)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        accessibilityDescription,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "accessibilityDescription is null");
    elementInfo->SetAccessibilityDescription(accessibilityDescription);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t childCount, int64_t* childNodeIds)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        childNodeIds,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "childNodeIds is null");
    if (childCount <= 0) {
        SET_ERROR_MESSAGE(ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER,
            __FUNCTION__, "childCount must be greater than zero");
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
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        operationActions,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "operationActions is null");
    if (operationCount <= 0) {
        SET_ERROR_MESSAGE(ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER,
            __FUNCTION__, "operationCount must be greater than zero");
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
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        screenRect,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "screenRect is null");
    elementInfo->SetRect(*screenRect);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetCheckable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checkable)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetCheckable(checkable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetChecked(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checked)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetChecked(checked);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetFocusable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool focusable)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetFocusable(focusable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isFocused)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetFocused(isFocused);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetVisible(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isVisible)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetVisible(isVisible);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityFocused)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetAccessibilityFocused(accessibilityFocused);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetSelected(
    ArkUI_AccessibilityElementInfo* elementInfo, bool selected)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetSelected(selected);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool clickable)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetClickable(clickable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetLongClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool longClickable)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetLongClickable(longClickable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetEnabled(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isEnabled)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetEnabled(isEnabled);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetIsPassword(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isPassword)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetPassword(isPassword);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetScrollable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool scrollable)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetScrollable(scrollable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetEditable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool editable)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetEditable(editable);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetIsHint(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isHint)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetHint(isHint);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetRangeInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRangeInfo* rangeInfo)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        rangeInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "rangeInfo is null");
    elementInfo->SetRangeInfo(*rangeInfo);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetGridInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridInfo* gridInfo)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        gridInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "gridInfo is null");
    elementInfo->SetGridInfo(*gridInfo);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetGridItemInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridItemInfo* gridItem)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        gridItem,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "gridItem is null");
    elementInfo->SetGridItemInfo(*gridItem);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetSelectedTextStart(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t selectedTextStart)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetTextBeginSelected(selectedTextStart);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetSelectedTextEnd(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t selectedTextEnd)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetTextEndSelected(selectedTextEnd);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetCurrentItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t currentItemIndex)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetCurrentIndex(currentItemIndex);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetStartItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t startItemIndex)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetBeginIndex(startItemIndex);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetEndItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t endItemIndex)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetEndIndex(endItemIndex);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetItemCount(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t itemCount)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetItemCount(itemCount);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityOffset(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t offset)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetOffset(offset);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityGroup(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityGroup)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetAccessibilityGroup(accessibilityGroup);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityLevel)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        accessibilityLevel,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "accessibilityLevel is null");
    elementInfo->SetAccessibilityLevel(accessibilityLevel);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetZIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t zIndex)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    elementInfo->SetZIndex(zIndex);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityOpacity(
    ArkUI_AccessibilityElementInfo* elementInfo, float opacity)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    if (std::isnan(opacity)) {
        SET_ERROR_MESSAGE(
            ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
            "opacity is NaN");
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER;
    }
    elementInfo->SetOpacity(opacity);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetBackgroundColor(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundColor)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        backgroundColor,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "backgroundColor is null");
    elementInfo->SetBackgroundColor(backgroundColor);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetBackgroundImage(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundImage)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        backgroundImage,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "backgroundImage is null");
    elementInfo->SetBackgroundImage(backgroundImage);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetBlur(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* blur)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        blur,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "blur is null");
    elementInfo->SetBlur(blur);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetHitTestBehavior(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hitTestBehavior)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        hitTestBehavior,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "hitTestBehavior is null");
    elementInfo->SetHitTestBehavior(hitTestBehavior);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityEventSetEventType(
    ArkUI_AccessibilityEventInfo* eventInfo, ArkUI_AccessibilityEventType eventType)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        eventInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "eventInfo is null");
    eventInfo->SetEventType(eventType);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityEventSetTextAnnouncedForAccessibility(
    ArkUI_AccessibilityEventInfo* eventInfo, const char* textAnnouncedForAccessibility)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        eventInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "eventInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        textAnnouncedForAccessibility,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "textAnnouncedForAccessibility is null");
    eventInfo->SetTextAnnouncedForAccessibility(textAnnouncedForAccessibility);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityEventSetRequestFocusId(
    ArkUI_AccessibilityEventInfo* eventInfo, int32_t requestFocusId)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        eventInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "eventInfo is null");
    eventInfo->SetRequestFocusId(requestFocusId);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityEventSetElementInfo(
    ArkUI_AccessibilityEventInfo* eventInfo, ArkUI_AccessibilityElementInfo* elementInfo)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        eventInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "eventInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    eventInfo->SetElementInfo(elementInfo);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_FindAccessibilityActionArgumentByKey(
    ArkUI_AccessibilityActionArguments* arguments, const char* key, char** value)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        arguments,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "arguments is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        key,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "key is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        value,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "value is null");
    *value = const_cast<char*>(arguments->FindValueByKey(key));
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_AccessibilityElementInfoSetComponentIdentifier(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* identifier)
{
    CHECK_NULL_RETURN_WITH_MESSAGE(
        elementInfo,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "elementInfo is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        identifier,
        ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER, __FUNCTION__,
        "identifier is null");
    constexpr size_t MAX_IDENTIFIER_LEN = 1024;
    size_t len = strnlen(identifier, MAX_IDENTIFIER_LEN + 1);
    if (len > MAX_IDENTIFIER_LEN) {
        std::string truncatedIdentifier(identifier, 0, MAX_IDENTIFIER_LEN);
        elementInfo->SetComponentIdentifier(truncatedIdentifier.c_str());
    } else {
        elementInfo->SetComponentIdentifier(identifier);
    }
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}

int32_t OH_ArkUI_NativeModule_GetNativeAccessibilityProvider(
    ArkUI_NodeHandle* node, ArkUI_AccessibilityProvider** provider)
{
    if ((node == nullptr) || (provider == nullptr)) {
        SET_ERROR_MESSAGE(
            ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "node or provider is null");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_NodeHandle nativeNode = *node;
    *provider = nullptr;

    if (!OHOS::Ace::NodeModel::IsValidArkUINode(nativeNode)) {
        SET_ERROR_MESSAGE(
            ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "node is invalid");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    if (nativeNode->type != ARKUI_NODE_CUSTOM) {
        SET_ERROR_MESSAGE(
            ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "node is not a custom node");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }

    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl,
        ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__,
        "impl is null");
    auto arkuiProvider = impl->getNodeModifiers()->getFrameNodeModifier()->getAccessibilityProvider(
        nativeNode->uiNodeHandle);
    if (arkuiProvider == nullptr) {
        SET_ERROR_MESSAGE(
            ARKUI_ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "Failed to get accessibility provider");
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    *provider = arkuiProvider;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

#ifdef __cplusplus
};
#endif
