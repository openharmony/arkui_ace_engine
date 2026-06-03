/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOCUS_MANAGER_H
#define FOCUS_MANAGER_H

#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <string>
#include <unordered_map>

namespace NativeXComponentSample {

/**
 * @brief 焦点处理模式枚举
 */
typedef enum {
    /** 按键事件用于焦点导航 */
    FOCUS_KEY_PROCESSING_MODE_NAVIGATION = 0,
    /** 按键事件向上冒泡到祖先节点 */
    FOCUS_KEY_PROCESSING_MODE_ANCESTOR_EVENT,
} FocusKeyProcessingMode;

/**
 * @brief 焦点管理器类，负责处理焦点相关的操作
 */
class FocusManager {
public:
    static FocusManager* GetInstance()
    {
        static FocusManager instance;
        return &instance;
    }

    int RequestFocus(const char* nodeId);
    int RequestFocusAsync(const char* nodeId);
    void ClearFocus(void* uiContext);
    void ActivateFocus(ArkUI_ContextHandle uiContext, bool isActive, bool isAutoInactive);
    void SetAutoTransfer(void* uiContext, bool autoTransfer);
    void SetKeyProcessingMode(void* uiContext, FocusKeyProcessingMode mode);
    int SetNodeFocusable(const char* nodeId, bool focusable);
    std::string GetCurrentFocusNodeId() const;
    void RegisterNodeHandle(const std::string& nodeId, ArkUI_NodeHandle nodeHandle);
    int SetFocusOnTouch(const char* nodeId, bool focusOnTouch);
    int SetNodeDefaultFocus(const char* nodeId, bool isDefault);
    int SetNodeFocusBox(const char* nodeId, float distance, float width, uint32_t color);
    int SetNodeNextFocus(const char* nodeId, const char* nextNodeId, int direction);
    int SetNodeTabStop(const char* nodeId, bool tabStop);

private:
    FocusManager() = default;
    ~FocusManager() = default;
    FocusManager(const FocusManager&) = delete;
    FocusManager& operator=(const FocusManager&) = delete;

    std::string currentFocusNodeId_;
    std::unordered_map<std::string, ArkUI_NodeHandle> nodeHandleMap_;
    bool isActive_ = false;
    bool autoTransfer_ = true;
    FocusKeyProcessingMode keyProcessingMode_ = FOCUS_KEY_PROCESSING_MODE_NAVIGATION;
};

} // namespace NativeXComponentSample

#endif // FOCUS_MANAGER_H
