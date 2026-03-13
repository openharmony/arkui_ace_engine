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
#ifndef CAPI_FORM_MANAGER_H
#define CAPI_FORM_MANAGER_H

#include <arkui/native_node.h>
#include <cstdint>
#include <functional>
#include <map>
#include <mutex>
#include <napi/native_api.h>
#include <unordered_map>
#include "../common/ArkUIBaseNode.h"

namespace NativeNode::Form {
using EventCallback = std::function<void(ArkUI_NodeEvent*)>;

// 指定对事件进行绑定还是解绑
enum EventOperation {
    BIND_EVENT,
    UNBIND_EVENT,
};

struct NodeRecord {
    ArkUI_NodeHandle nodeHandle;
    int32_t nodeType;
};

const unsigned int LOG_PRINT_DOMAIN = 0xFF00;

class NodeManager {
public:
    ~NodeManager() = default;
    static NodeManager& GetInstance();
    static ArkUI_NativeNodeAPI_1* GetNodeApi();
    
private:
    NodeManager() = default;
    
    std::unordered_map<int32_t, EventCallback> callbackMap_;
    std::map<int32_t, NodeRecord> nativeNodeMap_;
    std::mutex mutex_;
    int32_t nodeId_ = 1;
    
    ArkUI_NodeHandle mainPageScroll_ = nullptr;
    
};

class TransTool {
public:
    static TransTool *GetInstance() {
        static TransTool nativeEntry;
        return &nativeEntry;
    }    
    static napi_value InitButtonDemo(napi_env env, napi_callback_info info);
    static napi_value InitSliderDemo(napi_env env, napi_callback_info info);
    static napi_value InitCheckboxDemo(napi_env env, napi_callback_info info);
    static napi_value InitRadioDemo(napi_env env, napi_callback_info info);
    static napi_value InitToggleDemo(napi_env env, napi_callback_info info);
        
    void SetContentHandle(ArkUI_NodeContentHandle handle) {
        handle_ = handle;
    }

    void SetRootNode(const std::shared_ptr<NativeModule::ArkUIBaseNode> &baseNode) {
        root_ = baseNode;
        // 添加Native组件到NodeContent上用于挂载显示。
        OH_ArkUI_NodeContent_AddNode(handle_, root_->GetHandle());
    }
    void DisposeRootNode() {
        // 从NodeContent上卸载组件并销毁Native组件。
        OH_ArkUI_NodeContent_RemoveNode(handle_, root_->GetHandle());
        root_.reset();
    }
private:
    std::shared_ptr<NativeModule::ArkUIBaseNode> root_;
    ArkUI_NodeContentHandle handle_;    
};
}
#endif //CAPI_FORM_MANAGER_H

