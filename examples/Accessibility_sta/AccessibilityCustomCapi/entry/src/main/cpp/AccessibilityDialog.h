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

#ifndef ACCESSIBILITYCUSTOMCAPI_ACCESSIBILITYDIALOG_H
#define ACCESSIBILITYCUSTOMCAPI_ACCESSIBILITYDIALOG_H

#include <functional>
#include <arkui/native_node.h>
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <unordered_map>
#include "Manager.h"

class AccessibilityDialog {
public:
    AccessibilityDialog();
    ~AccessibilityDialog();
    static ArkUI_NodeHandle CreateNativeNodeDialog();
    static void CloseCustomDialog();
    static void MainViewMethod(ArkUI_NodeContentHandle handle);
    static void OnButtonClicked(ArkUI_NodeEvent *event);
    static void CreateAccessibilityProviderSection_dialog(ArkUI_NativeNodeAPI_1* nodeApi);
    static int32_t GetAccessibilityProvider(ArkUI_NodeHandle* customNode, const char* id);
    static ArkUI_AccessibilityProviderCallbacksWithInstance accessibilityProviderCallbacksWithInstance_;
    static int32_t FindAccessibilityNodeInfosById(const char* instanceId, int64_t elementId,
                                                  ArkUI_AccessibilitySearchMode mode,
                                                  int32_t requestId,
                                                  ArkUI_AccessibilityElementInfoList* elementList);
    
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

    static void FillElementRect(int64_t elementId, ArkUI_AccessibleRect& rect);
    static void InitRootNode(ArkUI_AccessibilityElementInfo* rootNode, int parentOfRoot);
    static void AddChildNodesForRoot(const char* instanceId, ArkUI_AccessibilityElementInfoList* elementList,
                                     ArkUI_AccessibilityElementInfo* rootNode);
    static void HandlePrefetchCurrentMode(const char* instanceId, int64_t elementId,
                              ArkUI_AccessibilityElementInfoList* elementList, int parentOfRoot);
};

#endif //ACCESSIBILITYCUSTOMCAPI_ACCESSIBILITYDIALOG_H
