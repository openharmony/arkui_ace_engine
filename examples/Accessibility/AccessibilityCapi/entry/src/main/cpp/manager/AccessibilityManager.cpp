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
#include <hilog/log.h>
#include <cstdint>
#include <string>

#include "common/common.h"
#include "fakenode/fake_node.h"
#include "AccessibilityManager.h"
#include "scenarios/Scenario1LoginPage.h"
#include "scenarios/Scenario2AudioPlayer.h"
#include "scenarios/Scenario3NewsList.h"
#include "scenarios/Scenario7Settings.h"


namespace {

const char* DEFAULT_ID = "XComponentIdSingle";
const char* LOG_PRINT_TEXT = "AccessibilityManager";
const int32_t NUMBER_ZERO = 0;
const int32_t NUMBER_FIRST = 100;
const int32_t NUMBER_SECOND = 500;
const int32_t NUMBER_THIRD = 800;
const int PARENT_OF_ROOT = -2100000;
const int MAX_CHILD_NODES = 1024;
const int64_t INVALID_ELEMENT_ID = -1;
const int64_t ROOT_ELEMENT_ID = 0;
const int64_t FOCUS_DIRECTION_FORWARD = 1;
const int64_t FOCUS_DIRECTION_BACKWARD = -1;

} // namespace


namespace NativeXComponentSample {

ArkUI_AccessibilityProvider *g_provider = nullptr;

/**
 * @brief Fills an accessibility event with information
 * @param eventInfo Pointer to the event info to be filled
 * @param elementInfo Pointer to the element info associated with the event
 * @param eventType The type of accessibility event
 * @param announcedText The text to announce for the event
 */
void FillEvent(ArkUI_AccessibilityEventInfo *eventInfo,
    ArkUI_AccessibilityElementInfo *elementInfo,
    ArkUI_AccessibilityEventType eventType,
    std::string announcedText)
{
    if (eventInfo == nullptr) {
        return;
    }
    if (elementInfo == nullptr) {
        return;
    }
    // Set event type
    OH_ArkUI_AccessibilityEventSetEventType(eventInfo, eventType);
    // Set element info for the event
    OH_ArkUI_AccessibilityEventSetElementInfo(eventInfo, elementInfo);

    if (eventType ==
        ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ANNOUNCE_FOR_ACCESSIBILITY &&
        announcedText.size() > 0) {
        // Set priority announcement text for accessibility node
        OH_ArkUI_AccessibilityEventSetTextAnnouncedForAccessibility(
            eventInfo, announcedText.data());
    }
}

/**
 * @brief Sends an asynchronous accessibility event
 * @param elementInfo Pointer to the element info
 * @param eventType The type of event to send
 * @param announcedText The text to announce
 */
void AccessibilityManager::SendAccessibilityAsyncEvent(
    ArkUI_AccessibilityElementInfo *elementInfo,
    ArkUI_AccessibilityEventType eventType,
    std::string announcedText)
{
    auto eventInfo = OH_ArkUI_CreateAccessibilityEventInfo();
    // 1. Fill event content
    FillEvent(eventInfo, elementInfo, eventType, announcedText);
    // 2. Callback
    auto callback = [](int32_t errorCode) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
            "result: %{public}d", errorCode);
    };
    // 3. Call interface to send event to OH side
    OH_ArkUI_SendAccessibilityAsyncEvent(g_provider, eventInfo, callback);
}

/**
 * @brief Constructor for AccessibilityManager
 */
AccessibilityManager::AccessibilityManager()
{
    // Initialize all scenarios
    InitializeScenarios();
    // Multi-instance scenarios
    accessibilityProviderCallbacksWithInstance_.findAccessibilityNodeInfosById =
        FindAccessibilityNodeInfosById;
    accessibilityProviderCallbacksWithInstance_.findAccessibilityNodeInfosByText =
        FindAccessibilityNodeInfosByText;
    accessibilityProviderCallbacksWithInstance_.findFocusedAccessibilityNode =
        FindFocusedAccessibilityNode;
    accessibilityProviderCallbacksWithInstance_.findNextFocusAccessibilityNode =
        FindNextFocusAccessibilityNode;
    accessibilityProviderCallbacksWithInstance_.executeAccessibilityAction =
        ExecuteAccessibilityAction;
    accessibilityProviderCallbacksWithInstance_.
        clearFocusedFocusAccessibilityNode = ClearFocusedFocusAccessibilityNode;
    accessibilityProviderCallbacksWithInstance_.
        getAccessibilityNodeCursorPosition = GetAccessibilityNodeCursorPosition;
    // Single-instance scenarios
    accessibilityProviderCallbacks_.findAccessibilityNodeInfosById =
        FindAccessibilityNodeInfosById;
    accessibilityProviderCallbacks_.findAccessibilityNodeInfosByText =
        FindAccessibilityNodeInfosByText;
    accessibilityProviderCallbacks_.findFocusedAccessibilityNode =
        FindFocusedAccessibilityNode;
    accessibilityProviderCallbacks_.findNextFocusAccessibilityNode =
        FindNextFocusAccessibilityNode;
    accessibilityProviderCallbacks_.executeAccessibilityAction =
        ExecuteAccessibilityAction;
    accessibilityProviderCallbacks_.clearFocusedFocusAccessibilityNode =
        ClearFocusedFocusAccessibilityNode;
    accessibilityProviderCallbacks_.getAccessibilityNodeCursorPosition =
        GetAccessibilityNodeCursorPosition;
}

/**
 * @brief Destructor for AccessibilityManager
 */
AccessibilityManager::~AccessibilityManager()
{
    // Clean up scenario manager
    ScenarioManager::GetInstance().Cleanup();
}

/**
 * @brief Initializes all available scenarios
 */
void AccessibilityManager::InitializeScenarios()
{
    // Register scenario 1: Login page
    ScenarioManager::GetInstance().RegisterScenario(
        "scenario1_login", new Scenario1LoginPage());

    // Register scenario 2: Audio player
    ScenarioManager::GetInstance().RegisterScenario(
        "scenario2_audio", new Scenario2AudioPlayer());

    // Register scenario 3: News list
    ScenarioManager::GetInstance().RegisterScenario(
        "scenario3_news", new Scenario3NewsList());

    // Register scenario 7: Settings page
    ScenarioManager::GetInstance().RegisterScenario(
        "scenario7_settings", new Scenario7Settings());

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "All scenarios registered successfully");
}

/**
 * @brief Initializes accessibility for a specific instance
 * @param id The instance ID
 * @param nativeXComponent Pointer to the native XComponent
 */
void AccessibilityManager::Initialize(const std::string &id,
    OH_NativeXComponent *nativeXComponent)
{
    int32_t ret = OH_NativeXComponent_GetNativeAccessibilityProvider(
        nativeXComponent, &provider);
    if (provider == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
            "get provider is null");
        return;
    }
    // 2. Register callback functions
    ret = OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance(
        id.c_str(), provider, &accessibilityProviderCallbacksWithInstance_);
    if (ret != 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
                     "InterfaceDesignTest "
                     "OH_ArkUI_AccessibilityProviderRegisterCallback failed");
        return;
    }
    g_provider = provider;

    // 3. Automatically set default scenario
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "Setting default scenario for instance: %{public}s", id.c_str());
    ScenarioManager::GetInstance().SetScenarioForInstance(id, "scenario1_login");
}

/**
 * @brief Finds accessibility nodes by element ID
 * @param instanceId The instance ID
 * @param elementId The element ID to search for
 * @param mode The search mode
 * @param requestId The request ID
 * @param elementList Pointer to the element list to populate
 * @return Result code indicating success or failure
 */
int32_t AccessibilityManager::FindAccessibilityNodeInfosById(
    const char* instanceId, int64_t elementId,
    ArkUI_AccessibilitySearchMode mode, int32_t requestId,
    ArkUI_AccessibilityElementInfoList *elementList)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "FindAccessibilityNodeInfosById start, instanceId "
        "%{public}s elementId: %{public}ld, "
        "requestId: %{public}d, mode: %{public}d", instanceId,
        elementId, requestId, static_cast<int32_t>(mode));

    // Get scenario from ScenarioManager
    auto* scenario = ScenarioManager::GetInstance().GetScenario(instanceId);
    if (!scenario) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
            "No scenario found for instance %{public}s", instanceId);
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }
    if (elementList == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
            "FindAccessibilityNodeInfosById elementList is null");
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }
    int ret = 0;
    if (elementId == INVALID_ELEMENT_ID) {
        elementId = ROOT_ELEMENT_ID;
    }

    if (mode ==
        ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_RECURSIVE_CHILDREN) {
        // Get scenario root node
        auto* rootNode = scenario->GetRootNode();
        if (!rootNode) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
                "No root node found for scenario");
            return OH_NATIVEXCOMPONENT_RESULT_FAILED;
        }

        // Add root node
        auto rootInfo = OH_ArkUI_AddAndGetAccessibilityElementInfo(elementList);
        if (!rootInfo) {
            return OH_NATIVEXCOMPONENT_RESULT_FAILED;
        }

        OH_ArkUI_AccessibilityElementInfoSetElementId(rootInfo,
            rootNode->GetElementId());
        OH_ArkUI_AccessibilityElementInfoSetParentId(rootInfo, PARENT_OF_ROOT);

        // Key: Call fillAccessibilityElement, this calls all native interfaces!
        rootNode->fillAccessibilityElement(rootInfo);

        ArkUI_AccessibleRect rect;
        rect.leftTopX = NUMBER_ZERO;
        rect.leftTopY = NUMBER_ZERO;
        rect.rightBottomX = NUMBER_THIRD;
        rect.rightBottomY = NUMBER_THIRD;
        ret = OH_ArkUI_AccessibilityElementInfoSetScreenRect(rootInfo, &rect);
        // Set root node to not be recognized by accessibility assistive services.
        OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(rootInfo, "no");
        auto objects = FakeWidget::Instance().GetAllObjects(instanceId);
        int64_t childNodes[MAX_CHILD_NODES];
        for (int i = NUMBER_ZERO; i < objects.size(); i++) {
            int elementId = i + 1;

            childNodes[i] = elementId;
        }
        for (int i = NUMBER_ZERO; i < objects.size(); i++) {
            int elementId = i + 1;
            childNodes[i] = elementId;
            auto child = OH_ArkUI_AddAndGetAccessibilityElementInfo(elementList);
            // Set child node info.
            OH_ArkUI_AccessibilityElementInfoSetElementId(child, elementId);
            OH_ArkUI_AccessibilityElementInfoSetParentId(child, ROOT_ELEMENT_ID);
            // Set current component to be recognized by accessibility services.
            OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(child, "yes");
            objects[i]->fillAccessibilityElement(child);

            ArkUI_AccessibleRect rect;
            rect.leftTopX = i * NUMBER_FIRST;
            rect.leftTopY = NUMBER_FIRST;
            rect.rightBottomX = i * NUMBER_FIRST + NUMBER_FIRST;
            rect.rightBottomY = NUMBER_SECOND;
            OH_ArkUI_AccessibilityElementInfoSetScreenRect(child, &rect);
            if (objects[i]->ObjectType() == "FakeSlider") {
                auto rangeInfo = objects[i]->GetRangeInfo();
                OH_ArkUI_AccessibilityElementInfoSetRangeInfo(child, &rangeInfo);
            }
            if (objects[i]->ObjectType() == "FakeList") {
                auto gridInfo = objects[i]->GetGridInfo();
                OH_ArkUI_AccessibilityElementInfoSetGridInfo(child, &gridInfo);
            }
            if (objects[i]->ObjectType() == "FakeSwiper") {
                auto gridItemInfo = objects[i]->GetGridItemInfo();
                OH_ArkUI_AccessibilityElementInfoSetGridItemInfo(child,
                    &gridItemInfo);
            }
        }

        ret = OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(
            rootInfo, objects.size(), childNodes);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
            "FindAccessibilityNodeInfosById child count: %{public}ld "
            "%{public}d",
            objects.size(), ret);
    } else if (mode == ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CURRENT) {
        auto &widget = FakeWidget::Instance();
        AccessibleObject *obj = nullptr;
        if (elementId == ROOT_ELEMENT_ID) {
            obj = &widget;
        } else {
            obj = widget.GetChild(elementId);
        }
        if (!obj) {
            return OH_NATIVEXCOMPONENT_RESULT_FAILED;
        }
        auto node = OH_ArkUI_AddAndGetAccessibilityElementInfo(elementList);
        OH_ArkUI_AccessibilityElementInfoSetElementId(node, elementId);
        OH_ArkUI_AccessibilityElementInfoSetParentId(
            node, elementId == ROOT_ELEMENT_ID ? PARENT_OF_ROOT : ROOT_ELEMENT_ID);
        OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(
            node, elementId == ROOT_ELEMENT_ID ? "no" : "yes");
        obj->fillAccessibilityElement(node);
        ArkUI_AccessibleRect rect;
        if (elementId == ROOT_ELEMENT_ID) {
            rect.leftTopX = NUMBER_ZERO;
            rect.leftTopY = NUMBER_ZERO;
            rect.rightBottomX = NUMBER_THIRD;
            rect.rightBottomY = NUMBER_THIRD;
        } else {
            int i = elementId - 1;
            rect.leftTopX = i * NUMBER_FIRST;
            rect.leftTopY = NUMBER_FIRST;
            rect.rightBottomX = i * NUMBER_FIRST + NUMBER_FIRST;
            rect.rightBottomY = NUMBER_SECOND;
        }

        OH_ArkUI_AccessibilityElementInfoSetScreenRect(node, &rect);
        if (elementId == ROOT_ELEMENT_ID) {
            auto objects = FakeWidget::Instance().GetAllObjects(instanceId);
            int64_t childNodes[MAX_CHILD_NODES];

            for (int i = NUMBER_ZERO; i < objects.size(); i++) {
                int elementId = i + 1;

                childNodes[i] = elementId;
                auto child = OH_ArkUI_AddAndGetAccessibilityElementInfo(
                    elementList);
                OH_ArkUI_AccessibilityElementInfoSetElementId(child,
                    elementId);
                OH_ArkUI_AccessibilityElementInfoSetParentId(child, ROOT_ELEMENT_ID);

                objects[i]->fillAccessibilityElement(child);

                ArkUI_AccessibleRect rect;
                rect.leftTopX = i * NUMBER_FIRST;
                rect.leftTopY = NUMBER_ZERO;
                rect.rightBottomX = i * NUMBER_FIRST + NUMBER_FIRST;
                rect.rightBottomY = NUMBER_SECOND;
                OH_ArkUI_AccessibilityElementInfoSetScreenRect(child, &rect);
            }
            ret = OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(
                node, objects.size(), childNodes);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
                "FindAccessibilityNodeInfosById child2 count: "
                "%{public}ld",
                objects.size());
        }
    }
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "FindAccessibilityNodeInfosById end");
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

/**
 * @brief Finds accessibility nodes by text content
 * @param instanceId The instance ID
 * @param elementId The element ID to search from
 * @param text The text to search for
 * @param requestId The request ID
 * @param elementList Pointer to the element list to populate
 * @return Result code indicating success or failure
 */
int32_t AccessibilityManager::FindAccessibilityNodeInfosByText(
    const char* instanceId, int64_t elementId,
    const char *text, int32_t requestId,
    ArkUI_AccessibilityElementInfoList *elementList)
{
    // Third-party framework needs to implement logic to query
    // accessibility nodes by text content.
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "FindAccessibilityNodeInfosByText start, instanceId "
        "%{public}s elementId: %{public}ld, "
        "requestId: %{public}d, text: %{public}s.", instanceId,
        elementId, requestId, text);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

/**
 * @brief Finds the currently focused accessibility node
 * @param instanceId The instance ID
 * @param elementId The element ID to search from
 * @param focusType The type of focus
 * @param requestId The request ID
 * @param elementInfo Pointer to the element info to populate
 * @return Result code indicating success or failure
 */
int32_t AccessibilityManager::FindFocusedAccessibilityNode(
    const char* instanceId, int64_t elementId,
    ArkUI_AccessibilityFocusType focusType, int32_t requestId,
    ArkUI_AccessibilityElementInfo *elementInfo)
{
    // Third-party framework needs to implement logic to get focused
    // element info based on specified node.
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "FindFocusedAccessibilityNode start instanceId %{public}s, "
        "elementId: %{public}ld, requestId: %{public}d, "
        "focusType: %{public}d",
        instanceId, elementId, requestId,
        static_cast<int32_t>(focusType));
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

/**
 * @brief Finds the next accessibility node to focus
 * @param instanceId The instance ID
 * @param elementId The current element ID
 * @param direction The direction to move focus
 * @param requestId The request ID
 * @param elementInfo Pointer to the element info to populate
 * @return Result code indicating success or failure
 */
int32_t AccessibilityManager::FindNextFocusAccessibilityNode(
    const char* instanceId, int64_t elementId,
    ArkUI_AccessibilityFocusMoveDirection direction, int32_t requestId,
    ArkUI_AccessibilityElementInfo *elementInfo)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "FindNextFocusAccessibilityNode instanceId %{public}s "
        "elementId: %{public}ld, requestId: %{public}d, "
        "direction: %{public}d",
        instanceId, elementId, requestId,
        static_cast<int32_t>(direction));

    // Get node from scenario
    auto* scenario = ScenarioManager::GetInstance().GetScenario(instanceId);
    if (!scenario) {
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }

    const auto& nodes = scenario->GetNodes();
    // nodes contains root node, so subtract 1 from count
    size_t nodeCount = nodes.size();

    if ((elementId < 0) || (elementId > static_cast<int64_t>(nodeCount))) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
            "elementId invalid");
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }
    int64_t nextElementId = INVALID_ELEMENT_ID;
    if (direction == ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_FORWARD) {
        nextElementId = elementId + FOCUS_DIRECTION_FORWARD;
    } else {
        nextElementId = elementId + FOCUS_DIRECTION_BACKWARD;
    }

    // Screen reader constraint: if root node and backward,
    // return to last node
    if ((nextElementId == INVALID_ELEMENT_ID) &&
        (direction == ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_BACKWARD)) {
        nextElementId = nodeCount;
    }

    if (nextElementId > nodeCount) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
            "nextElementId invalid");
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }

    if (nextElementId < 0) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
            "nextElementId less than zero");
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }

    auto* nextNode = scenario->GetNodeById(nextElementId);
    if (!nextNode) {
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }

    OH_ArkUI_AccessibilityElementInfoSetElementId(elementInfo,
        nextNode->GetElementId());
    OH_ArkUI_AccessibilityElementInfoSetParentId(
        elementInfo,
        nextNode->GetParent() ? nextNode->GetParent()->GetElementId() : ROOT_ELEMENT_ID);
    nextNode->fillAccessibilityElement(elementInfo);
    ArkUI_AccessibleRect rect;
    rect.leftTopX = nextElementId * NUMBER_FIRST;
    rect.leftTopY = NUMBER_ZERO;
    rect.rightBottomX = nextElementId * NUMBER_FIRST + NUMBER_FIRST;
    rect.rightBottomY = NUMBER_SECOND;
    OH_ArkUI_AccessibilityElementInfoSetScreenRect(elementInfo, &rect);
    auto eventInfo = OH_ArkUI_CreateAccessibilityEventInfo();
    OH_ArkUI_AccessibilityEventSetRequestFocusId(eventInfo, requestId);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "%{public}ld", nextElementId);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

/**
 * @brief Executes an accessibility action on a node
 * @param instanceId The instance ID
 * @param elementId The element ID to perform the action on
 * @param action The type of action to execute
 * @param actionArguments Additional arguments for the action
 * @param requestId The request ID
 * @return Result code indicating success or failure
 */
int32_t AccessibilityManager::ExecuteAccessibilityAction(
    const char* instanceId, int64_t elementId,
    ArkUI_Accessibility_ActionType action,
    ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "ExecuteAccessibilityAction instanceId %{public}s "
        "elementId: %{public}ld, "
        "action: %{public}d, requestId: %{public}d",
        instanceId, elementId, action, requestId);

    // Get node from scenario
    auto* scenario = ScenarioManager::GetInstance().GetScenario(instanceId);
    if (!scenario) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
            "No scenario found for instance %{public}s", instanceId);
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }

    // Delegate to scenario to handle action
    bool handled = scenario->HandleAction(elementId, action);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "ExecuteAccessibilityAction: action=%{public}d, "
        "handled=%{public}d",
        action, handled);

    return handled ? OH_NATIVEXCOMPONENT_RESULT_SUCCESS :
                     OH_NATIVEXCOMPONENT_RESULT_FAILED;
}

/**
 * @brief Clears the currently focused accessibility node
 * @param instanceId The instance ID
 * @return Result code indicating success or failure
 */
int32_t AccessibilityManager::ClearFocusedFocusAccessibilityNode(
    const char* instanceId)
{
    // Third-party framework needs to implement behavior to clear
    // the currently focused node.
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "ClearFocusedFocusAccessibilityNode, instanceId %{public}s",
        instanceId);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

/**
 * @brief Gets the cursor position in a text component
 * @param instanceId The instance ID
 * @param elementId The element ID of the text component
 * @param requestId The request ID
 * @param index Pointer to store the cursor position
 * @return Result code indicating success or failure
 */
int32_t AccessibilityManager::GetAccessibilityNodeCursorPosition(
    const char* instanceId, int64_t elementId,
    int32_t requestId, int32_t *index)
{
    // Third-party framework needs to implement logic to get current
    // cursor position in component (text component).
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
        "GetAccessibilityNodeCursorPosition, instanceId %{public}s "
        "elementId: %{public}ld, requestId: %{public}d, "
        "index: %{public}d",
        instanceId, elementId, requestId, index);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

/**
 * @brief Initializes accessibility for single instance mode
 * @param nativeXComponent Pointer to the native XComponent
 */
void AccessibilityManager::Initialize(OH_NativeXComponent *nativeXComponent)
{
    int32_t ret = OH_NativeXComponent_GetNativeAccessibilityProvider(
        nativeXComponent, &provider);
    if (provider == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
            "get provider is null");
        return;
    }
    // 2. Register callback functions
    ret = OH_ArkUI_AccessibilityProviderRegisterCallback(
        provider, &accessibilityProviderCallbacks_);
    if (ret != 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, LOG_PRINT_TEXT,
            "InterfaceDesignTest "
            "OH_ArkUI_AccessibilityProviderRegisterCallback failed");
        return;
    }
    g_provider = provider;
}

// Single instance wrapper functions
int32_t AccessibilityManager::FindAccessibilityNodeInfosById(
    int64_t elementId, ArkUI_AccessibilitySearchMode mode,
    int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList)
{
    return FindAccessibilityNodeInfosById(DEFAULT_ID, elementId, mode,
        requestId, elementList);
}

int32_t AccessibilityManager::FindAccessibilityNodeInfosByText(
    int64_t elementId, const char* text, int32_t requestId,
    ArkUI_AccessibilityElementInfoList* elementList)
{
    return FindAccessibilityNodeInfosByText(DEFAULT_ID, elementId, text,
        requestId, elementList);
}

int32_t AccessibilityManager::FindFocusedAccessibilityNode(
    int64_t elementId, ArkUI_AccessibilityFocusType focusType,
    int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo)
{
    return FindFocusedAccessibilityNode(DEFAULT_ID, elementId, focusType,
        requestId, elementInfo);
}

int32_t AccessibilityManager::FindNextFocusAccessibilityNode(
    int64_t elementId, ArkUI_AccessibilityFocusMoveDirection direction,
    int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo)
{
    return FindNextFocusAccessibilityNode(DEFAULT_ID, elementId, direction,
        requestId, elementInfo);
}

int32_t AccessibilityManager::ExecuteAccessibilityAction(
    int64_t elementId, ArkUI_Accessibility_ActionType action,
    ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId)
{
    return ExecuteAccessibilityAction(DEFAULT_ID, elementId, action,
        actionArguments, requestId);
}

int32_t AccessibilityManager::ClearFocusedFocusAccessibilityNode()
{
    return ClearFocusedFocusAccessibilityNode(DEFAULT_ID);
}

int32_t AccessibilityManager::GetAccessibilityNodeCursorPosition(
    int64_t elementId, int32_t requestId, int32_t* index)
{
    return GetAccessibilityNodeCursorPosition(DEFAULT_ID, elementId,
        requestId, index);
}

} // namespace NativeXComponentSample
