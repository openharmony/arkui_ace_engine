/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OH_ACCESSIBILITYDEMO_ACCESSIBILITYMANAGER_H
#define OH_ACCESSIBILITYDEMO_ACCESSIBILITYMANAGER_H

#include <ace/xcomponent/native_interface_xcomponent.h>
#include "scenarios/ScenarioManager.h"

namespace NativeXComponentSample {
class AccessibilityManager {
public:
    AccessibilityManager();
    ~AccessibilityManager();
    void Initialize(const std::string &id, OH_NativeXComponent* nativeXComponent);
    void Initialize(OH_NativeXComponent* nativeXComponent);

    // 初始化所有场景
    void InitializeScenarios();

public:
//    多实例场景
    static int32_t FindAccessibilityNodeInfosById(const char* instanceId, int64_t elementId,
        ArkUI_AccessibilitySearchMode mode, int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    
    static int32_t FindAccessibilityNodeInfosByText(const char* instanceId, int64_t elementId,
        const char* text, int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    
    static int32_t FindFocusedAccessibilityNode(const char* instanceId, int64_t elementId,
        ArkUI_AccessibilityFocusType focusType, int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    
    static int32_t FindNextFocusAccessibilityNode(const char* instanceId, int64_t elementId,
        ArkUI_AccessibilityFocusMoveDirection direction,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    
    static int32_t ExecuteAccessibilityAction(const char* instanceId, int64_t elementId,
        ArkUI_Accessibility_ActionType action, ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId);
    
    static int32_t ClearFocusedFocusAccessibilityNode(const char* instanceId);
    
    static int32_t GetAccessibilityNodeCursorPosition(const char* instanceId, int64_t elementId,
        int32_t requestId, int32_t* index);
//    单实例场景
    static int32_t FindAccessibilityNodeInfosById(int64_t elementId, ArkUI_AccessibilitySearchMode mode,
    int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    
    static int32_t FindAccessibilityNodeInfosByText(int64_t elementId, const char* text, int32_t requestId,
        ArkUI_AccessibilityElementInfoList* elementList);
    
    static int32_t FindFocusedAccessibilityNode(int64_t elementId, ArkUI_AccessibilityFocusType focusType,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    
    static int32_t FindNextFocusAccessibilityNode(int64_t elementId, ArkUI_AccessibilityFocusMoveDirection direction,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    
    static int32_t ExecuteAccessibilityAction(int64_t elementId, ArkUI_Accessibility_ActionType action,
        ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId);
    
    static int32_t ClearFocusedFocusAccessibilityNode();
    
    static int32_t GetAccessibilityNodeCursorPosition(int64_t elementId, int32_t requestId, int32_t* index);
   
private:
    static void SendAccessibilityAsyncEvent(ArkUI_AccessibilityElementInfo *elementInfo,
                                            ArkUI_AccessibilityEventType eventType, std::string announcedText);
private:
    ArkUI_AccessibilityProvider* provider = nullptr;
    ArkUI_AccessibilityProviderCallbacks accessibilityProviderCallbacks_;
    ArkUI_AccessibilityProviderCallbacksWithInstance accessibilityProviderCallbacksWithInstance_;
};
}
#endif //OH_ACCESSIBILITYDEMO_ACCESSIBILITYMANAGER_H
