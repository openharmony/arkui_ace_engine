/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#ifndef NATIVE_NODE_SAMPLE_ACCESSIBILITYMAKER_H
#define NATIVE_NODE_SAMPLE_ACCESSIBILITYMAKER_H

#include <functional>
#include <arkui/native_node.h>
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <unordered_map>
#include "Manager.h"

class AccessibilityMaker {
public:
    AccessibilityMaker();
    ~AccessibilityMaker();
    static ArkUI_NodeHandle CreateNativeNode();
    static ArkUI_NodeHandle CreateNativeNode_multiple();
    static ArkUI_NodeHandle CreateNativeNoCustom();
    static ArkUI_NodeHandle BuildTextNode(ArkUI_NativeNodeAPI_1* nodeApi, const char* content);
    static ArkUI_NodeHandle BuildTextNodeWithoutAccessibilityFocus(ArkUI_NativeNodeAPI_1* nodeApi, const char* content);
    static void SetAccessibilityDisabled(bool isDisabled);
    static bool IsAccessibilityDisabled();
    static int32_t GetAccessibilityProvider(ArkUI_NodeHandle* customNode, const char* id);
    static ArkUI_NodeHandle BuildColumnNode(ArkUI_NativeNodeAPI_1* nodeApi);
    static void SetAccessibilityMode(ArkUI_NativeNodeAPI_1* nodeApi, ArkUI_NodeHandle node,
        ArkUI_AccessibilityMode mode);
    static void GetUniqueId(ArkUI_NativeNodeAPI_1* nodeApi, ArkUI_NodeHandle node);
    static void CreateAccessibilityProviderSection(ArkUI_NativeNodeAPI_1* nodeApi, ArkUI_NodeHandle parent);
    static void CreateAccessibilityProviderSection_noCustom(ArkUI_NativeNodeAPI_1* nodeApi, ArkUI_NodeHandle parent);
    static void CreateAccessibilityProviderSection_multiple(ArkUI_NativeNodeAPI_1* nodeApi, ArkUI_NodeHandle parent);
    
    static int32_t FindAccessibilityNodeInfosById(const char* instanceId, int64_t elementId,
                                                  ArkUI_AccessibilitySearchMode mode,
                                                  int32_t requestId,
                                                  ArkUI_AccessibilityElementInfoList *elementList);
    
    static int32_t FindAccessibilityNodeInfosByText(const char* instanceId, int64_t elementId,
                                                    const char *text, int32_t requestId,
                                                    ArkUI_AccessibilityElementInfoList *elementList);
    
    static int32_t FindFocusedAccessibilityNode(const char* instanceId, int64_t elementId,
                                                ArkUI_AccessibilityFocusType focusType,
                                                int32_t requestId,
                                                ArkUI_AccessibilityElementInfo *elementInfo);
    
    static int32_t FindNextFocusAccessibilityNode(const char* instanceId, int64_t elementId,
                                                  ArkUI_AccessibilityFocusMoveDirection direction,
                                                  int32_t requestId,
                                                  ArkUI_AccessibilityElementInfo *elementInfo);
    
    static int32_t ExecuteAccessibilityAction(const char* instanceId, int64_t elementId,
                                              ArkUI_Accessibility_ActionType action,
                                              ArkUI_AccessibilityActionArguments *actionArguments,
                                              int32_t requestId);
    
    static int32_t ClearFocusedFocusAccessibilityNode(const char* instanceId);
    
    static int32_t GetAccessibilityNodeCursorPosition(const char* instanceId, int64_t elementId,
                                                     int32_t requestId, int32_t *index);
    
    static int32_t FindAccessibilityNodeInfosById(int64_t elementId, ArkUI_AccessibilitySearchMode mode,
                                                  int32_t requestId,
                                                  ArkUI_AccessibilityElementInfoList* elementList);
    
    static int32_t FindAccessibilityNodeInfosByText(int64_t elementId, const char* text, int32_t requestId,
                                                    ArkUI_AccessibilityElementInfoList* elementList);
    
    static int32_t FindFocusedAccessibilityNode(int64_t elementId, ArkUI_AccessibilityFocusType focusType,
                                                int32_t requestId,
                                                ArkUI_AccessibilityElementInfo* elementInfo);
    
    static int32_t FindNextFocusAccessibilityNode(int64_t elementId,
                                                  ArkUI_AccessibilityFocusMoveDirection direction,
                                                  int32_t requestId,
                                                  ArkUI_AccessibilityElementInfo* elementInfo);
    
    static int32_t ExecuteAccessibilityAction(int64_t elementId, ArkUI_Accessibility_ActionType action,
                                              ArkUI_AccessibilityActionArguments *actionArguments,
                                              int32_t requestId);
    
    static int32_t ClearFocusedFocusAccessibilityNode();
    
    static int32_t GetAccessibilityNodeCursorPosition(int64_t elementId, int32_t requestId, int32_t* index);
    
    static void SendAccessibilityAsyncEvent(ArkUI_AccessibilityElementInfo *elementInfo,
                                            ArkUI_AccessibilityEventType eventType);
    static ArkUI_AccessibilityProviderCallbacksWithInstance accessibilityProviderCallbacksWithInstance_;
};

#endif // NATIVE_NODE_SAMPLE_ACCESSIBILITYMAKER_H
