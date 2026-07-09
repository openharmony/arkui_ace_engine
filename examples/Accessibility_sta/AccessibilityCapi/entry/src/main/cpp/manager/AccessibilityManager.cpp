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
// [Start abilitycap_one_start]
#include <arkui/native_interface_accessibility.h>
#include <string>
#include <hilog/log.h>
#include "AccessibilityManager.h"
#include "fakenode/fake_node.h"
// [StartExclude abilitycap_one_start]
using namespace NativeXComponentSample;

static const char *LOG_PRINT_TEXT = "AccessibilityManager";
static const int32_t ACC_NUMBER_ZERO = 0;
static const int32_t ACC_NUMBER_FIRST = 100;
static const int32_t ACC_NUMBER_SECOND = 500;
static const int32_t ACC_NUMBER_THIRD = 800;
static ArkUI_AccessibilityProvider *g_provider = nullptr;
static ArkUI_AccessibilityProviderCallbacksWithInstance g_callbacksWithInstance;
// [Start abilitycap_six_start]
void FillEvent(ArkUI_AccessibilityEventInfo *eventInfo, ArkUI_AccessibilityElementInfo *elementInfo,
               ArkUI_AccessibilityEventType eventType, std::string announcedText)
{
    if (eventInfo == nullptr || elementInfo == nullptr) {
        return;
    }
    OH_ArkUI_AccessibilityEventSetEventType(eventInfo, eventType);
    OH_ArkUI_AccessibilityEventSetElementInfo(eventInfo, elementInfo);
    if (eventType == ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ANNOUNCE_FOR_ACCESSIBILITY && announcedText.size() > 0) {
        OH_ArkUI_AccessibilityEventSetTextAnnouncedForAccessibility(eventInfo, announcedText.data());
    }
}

void SendAccessibilityAsyncEvent(ArkUI_AccessibilityElementInfo *elementInfo,
                                 ArkUI_AccessibilityEventType eventType,
                                 std::string announcedText)
{
    auto eventInfo = OH_ArkUI_CreateAccessibilityEventInfo();
    FillEvent(eventInfo, elementInfo, eventType, announcedText);
    auto callback = [](int32_t errorCode) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT, "result: %{public}d", errorCode);
    };
    OH_ArkUI_SendAccessibilityAsyncEvent(g_provider, eventInfo, callback);
}
// [StartExclude abilitycap_six_start]
// [Start abilitycap_two_start]
int32_t FindAccessibilityNodeInfosById(const char *instanceId, int64_t elementId,
    ArkUI_AccessibilitySearchMode mode, int32_t requestId, ArkUI_AccessibilityElementInfoList *elementList)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
                 "FindAccessibilityNodeInfosById start, instanceId %{public}s elementId: %{public}ld",
                 instanceId, elementId);
    if (elementList == nullptr) {
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER;
    }
    const int64_t parentOfRoot = -2100000;
    if (elementId == -1) {
        elementId = 0;
    }

    if (mode == ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_RECURSIVE_CHILDREN) {
        auto rootNode = OH_ArkUI_AddAndGetAccessibilityElementInfo(elementList);
        if (!rootNode) {
            return ARKUI_ACCESSIBILITY_NATIVE_RESULT_FAILED;
        }
        OH_ArkUI_AccessibilityElementInfoSetElementId(rootNode, 0);
        OH_ArkUI_AccessibilityElementInfoSetParentId(rootNode, parentOfRoot);
        FakeWidget::Instance().fillAccessibilityElement(rootNode);

        ArkUI_AccessibleRect rect;
        rect.leftTopX = ACC_NUMBER_ZERO;
        rect.leftTopY = ACC_NUMBER_ZERO;
        rect.rightBottomX = ACC_NUMBER_THIRD;
        rect.rightBottomY = ACC_NUMBER_THIRD;
        OH_ArkUI_AccessibilityElementInfoSetScreenRect(rootNode, &rect);
        OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(rootNode, "no");

        auto objects = FakeWidget::Instance().GetAllObjects(instanceId);
        int64_t childNodes[1024];
        for (int i = 0; i < objects.size(); i++) {
            int64_t childElementId = i + 1;
            childNodes[i] = childElementId;
            auto child = OH_ArkUI_AddAndGetAccessibilityElementInfo(elementList);
            OH_ArkUI_AccessibilityElementInfoSetElementId(child, childElementId);
            OH_ArkUI_AccessibilityElementInfoSetParentId(child, 0);
            OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(child, "yes");
            objects[i]->fillAccessibilityElement(child);

            ArkUI_AccessibleRect childRect;
            childRect.leftTopX = i * ACC_NUMBER_FIRST;
            childRect.leftTopY = ACC_NUMBER_FIRST;
            childRect.rightBottomX = i * ACC_NUMBER_FIRST + ACC_NUMBER_FIRST;
            childRect.rightBottomY = ACC_NUMBER_SECOND;
            OH_ArkUI_AccessibilityElementInfoSetScreenRect(child, &childRect);
        }
        OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(rootNode, objects.size(), childNodes);
    } else if (mode == ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CURRENT) {
        auto &widget = FakeWidget::Instance();
        AccessibleObject *obj = nullptr;
        if (elementId == 0) {
            obj = &widget;
        } else {
            obj = widget.GetChild(elementId);
        }
        if (!obj) {
            return ARKUI_ACCESSIBILITY_NATIVE_RESULT_FAILED;
        }
        auto node = OH_ArkUI_AddAndGetAccessibilityElementInfo(elementList);
        OH_ArkUI_AccessibilityElementInfoSetElementId(node, elementId);
        OH_ArkUI_AccessibilityElementInfoSetParentId(node, elementId == 0 ? parentOfRoot : 0);
        OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(node, elementId == 0 ? "no" : "yes");
        obj->fillAccessibilityElement(node);

        ArkUI_AccessibleRect nodeRect;
        if (elementId == 0) {
            nodeRect.leftTopX = ACC_NUMBER_ZERO;
            nodeRect.leftTopY = ACC_NUMBER_ZERO;
            nodeRect.rightBottomX = ACC_NUMBER_THIRD;
            nodeRect.rightBottomY = ACC_NUMBER_THIRD;
        } else {
            int i = elementId - 1;
            nodeRect.leftTopX = i * ACC_NUMBER_FIRST;
            nodeRect.leftTopY = ACC_NUMBER_FIRST;
            nodeRect.rightBottomX = i * ACC_NUMBER_FIRST + ACC_NUMBER_FIRST;
            nodeRect.rightBottomY = ACC_NUMBER_SECOND;
        }
        OH_ArkUI_AccessibilityElementInfoSetScreenRect(node, &nodeRect);

        if (elementId == 0) {
            auto objects = FakeWidget::Instance().GetAllObjects(instanceId);
            int64_t childNodes[1024];
            for (int i = 0; i < objects.size(); i++) {
                int64_t childElementId = i + 1;
                childNodes[i] = childElementId;
                auto child = OH_ArkUI_AddAndGetAccessibilityElementInfo(elementList);
                OH_ArkUI_AccessibilityElementInfoSetElementId(child, childElementId);
                OH_ArkUI_AccessibilityElementInfoSetParentId(child, 0);
                objects[i]->fillAccessibilityElement(child);

                ArkUI_AccessibleRect childRect;
                childRect.leftTopX = i * ACC_NUMBER_FIRST;
                childRect.leftTopY = ACC_NUMBER_ZERO;
                childRect.rightBottomX = i * ACC_NUMBER_FIRST + ACC_NUMBER_FIRST;
                childRect.rightBottomY = ACC_NUMBER_SECOND;
                OH_ArkUI_AccessibilityElementInfoSetScreenRect(child, &childRect);
            }
            OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(node, objects.size(), childNodes);
        }
    }
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}
// [End abilitycap_two_start]

// [Start abilitycap_four_start]
int32_t FindAccessibilityNodeInfosByText(const char *instanceId, int64_t elementId,
    const char *text, int32_t requestId, ArkUI_AccessibilityElementInfoList *elementList)
{
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}
// [End abilitycap_four_start]

// [Start abilitycap_five_start]
int32_t FindFocusedAccessibilityNode(const char *instanceId, int64_t elementId,
    ArkUI_AccessibilityFocusType focusType, int32_t requestId, ArkUI_AccessibilityElementInfo *elementInfo)
{
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}
// [End abilitycap_five_start]

// [Start abilitycap_three_start]
int32_t FindNextFocusAccessibilityNode(const char *instanceId, int64_t elementId,
    ArkUI_AccessibilityFocusMoveDirection direction, int32_t requestId,
    ArkUI_AccessibilityElementInfo *elementInfo)
{
    auto objects = FakeWidget::Instance().GetAllObjects(instanceId);
    if ((elementId < 0) || (elementId > objects.size())) {
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_FAILED;
    }
    int64_t nextElementId = -1;
    if (direction == ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_FORWARD) {
        nextElementId = elementId + 1;
    } else {
        nextElementId = elementId - 1;
    }
    if ((nextElementId == -1) && (direction == ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_BACKWARD)) {
        nextElementId = objects.size();
    }
    if (nextElementId > objects.size() || nextElementId <= 0) {
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_FAILED;
    }
    OH_ArkUI_AccessibilityElementInfoSetElementId(elementInfo, nextElementId);
    OH_ArkUI_AccessibilityElementInfoSetParentId(elementInfo, 0);
    objects[nextElementId - 1]->fillAccessibilityElement(elementInfo);
    ArkUI_AccessibleRect rect;
    rect.leftTopX = nextElementId * ACC_NUMBER_FIRST;
    rect.leftTopY = ACC_NUMBER_ZERO;
    rect.rightBottomX = nextElementId * ACC_NUMBER_FIRST + ACC_NUMBER_FIRST;
    rect.rightBottomY = ACC_NUMBER_SECOND;
    OH_ArkUI_AccessibilityElementInfoSetScreenRect(elementInfo, &rect);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}
// [End abilitycap_three_start]
// [EndExclude abilitycap_six_start]
int32_t ExecuteAccessibilityAction(const char *instanceId, int64_t elementId,
    ArkUI_Accessibility_ActionType action, ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId)
{
    auto object = FakeWidget::Instance().GetChild(elementId);
    if (!object) {
        return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
    }
    auto announcedText = object->GetAnnouncedForAccessibility();
    auto element = OH_ArkUI_CreateAccessibilityElementInfo();
    OH_ArkUI_AccessibilityElementInfoSetElementId(element, elementId);
    switch (action) {
        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK:
            if (object) {
                object->OnClick();
                object->fillAccessibilityElement(element);
            }
            SendAccessibilityAsyncEvent(element, ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_CLICKED, announcedText);
            break;
        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS:
            if (object) {
                object->SetFocus(true);
                object->fillAccessibilityElement(element);
            }
            SendAccessibilityAsyncEvent(element, ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUSED,
                                        announcedText);
            break;
        case ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS:
            if (object) {
                object->SetFocus(false);
                object->fillAccessibilityElement(element);
            }
            SendAccessibilityAsyncEvent(element, ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUS_CLEARED,
                                        announcedText);
            break;
        default:
            break;
    }
    OH_ArkUI_DestoryAccessibilityElementInfo(element);
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}
// [End abilitycap_six_start]

// [Start abilitycap_seven_start]
int32_t ClearFocusedFocusAccessibilityNode(const char *instanceId)
{
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}
// [End abilitycap_seven_start]

// [Start abilitycap_eight_start]
int32_t GetAccessibilityNodeCursorPosition(const char *instanceId, int64_t elementId,
    int32_t requestId, int32_t *index)
{
    return ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL;
}
// [End abilitycap_eight_start]
// [EndExclude abilitycap_one_start]
void InitAccessibilityCallbacks()
{
    g_callbacksWithInstance.findAccessibilityNodeInfosById = FindAccessibilityNodeInfosById;
    g_callbacksWithInstance.findAccessibilityNodeInfosByText = FindAccessibilityNodeInfosByText;
    g_callbacksWithInstance.findFocusedAccessibilityNode = FindFocusedAccessibilityNode;
    g_callbacksWithInstance.findNextFocusAccessibilityNode = FindNextFocusAccessibilityNode;
    g_callbacksWithInstance.executeAccessibilityAction = ExecuteAccessibilityAction;
    g_callbacksWithInstance.clearFocusedFocusAccessibilityNode = ClearFocusedFocusAccessibilityNode;
    g_callbacksWithInstance.getAccessibilityNodeCursorPosition = GetAccessibilityNodeCursorPosition;
}

bool RegisterAccessibilityProvider(ArkUI_NodeHandle node, const std::string &id)
{
    InitAccessibilityCallbacks();

    ArkUI_AccessibilityProvider *provider = nullptr;
    int32_t ret = OH_ArkUI_NativeModule_GetNativeAccessibilityProvider(&node, &provider);
    if (ret != 0 || provider == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
                     "GetNativeAccessibilityProvider failed, ret=%{public}d", ret);
        return false;
    }

    ret = OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance(
        id.c_str(), provider, &g_callbacksWithInstance);
    if (ret != 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
                     "RegisterCallbackWithInstance failed, ret=%{public}d", ret);
        return false;
    }

    g_provider = provider;
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
                 "RegisterAccessibilityProvider success, id=%{public}s", id.c_str());
    return true;
}
// [End abilitycap_one_start]
