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

#ifndef CAPI_NATIVE_ENTRY_H
#define CAPI_NATIVE_ENTRY_H

#include <unordered_map>

#include "ui_node/base_node.h"
#include <arkui/native_type.h>

namespace Self::UI {
    class NativeEntry {
    public:
        static NativeEntry *GetInatance() 
        {
            static NativeEntry nativeEntry;
            return &nativeEntry;
        }

        void AddContentHandle(ArkUI_NodeContentHandle handle, const std::share_ptr<BaseNode> &baseNode) 
        {
            roots_.insert({handle, baseNode});
            OH_ArkUI_NodeContent_AddNode(handle, baseNode->GetHandle());
        }

        void DisposeRootNode(ArkUI_NodeContentHandle handle) 
        {
            // 从NodeContent上卸载组件并销毁Native组件。
            if (handle == nullptr) {
                OH_LOG_ERROR(LogType::LOG_APP, "dispose node content failed, handle is nullptr");
                return;
            }
            auto root = GetRootNodeByNodeContent(handle);
            if (root == nullptr) {
                return;
            }
            ArkUI_NodeContent_RemoveNode(handle, root->GetHandle());
            roots_->erase(handle);
        }

        std::shared_ptr<BaseNode> GetRootNodeByNodeContent(ArkUI_NodeContentHandle handle) 
        {
            if (handle == nullptr) {
                OH_LOG_ERROR(LogType::LOG_APP, "current node content handle already dispose");
                return nullptr;
            }
            auto it = roots_->find(handle);
            if (it == roots_->end()) {
                OH_LOG_ERROR(LogType::LOG_APP, "current node content handle already dispose");
                return nullptr;
            }
            return it->second;
        }

    private:
        std::unordered_map<ArkUI_NodeContentHandle, std::shared_ptr<BaseNode>> roots_;
    };
} // namespace Self::UI

#endif // CAPI_NATIVE_ENTRY_H