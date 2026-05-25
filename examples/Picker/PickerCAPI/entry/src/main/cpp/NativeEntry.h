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

#ifndef NATIVEENTRY_H
#define NATIVEENTRY_H

#include <js_native_api_types.h>
#include <arkui/native_type.h>
#include <memory>
#include "ArkUIBaseNode.h"

namespace NativeModule {

napi_value CreateNativeRoot(napi_env env, napi_callback_info info);
napi_value DestroyNativeRoot(napi_env env, napi_callback_info info);

class NativeEntry {
public:
    static NativeEntry *GetInstance()
    {
        static NativeEntry nativeEntry;
        return &nativeEntry;
    }

    void SetContentHandle(ArkUI_NodeContentHandle handle)
    {
        handle_ = handle;
    }

    void SetRootNode(const std::shared_ptr<ArkUIBaseNode> &baseNode)
    {
        root_ = baseNode;
        OH_ArkUI_NodeContent_AddNode(handle_, root_->GetHandle());
    }

    void DisposeRootNode()
    {
        if (root_) {
            OH_ArkUI_NodeContent_RemoveNode(
                handle_, root_->GetHandle());
        }
        root_.reset();
    }

    void SwitchRootNode(
        const std::shared_ptr<ArkUIBaseNode> &newNode)
    {
        DisposeRootNode();
        SetRootNode(newNode);
    }

    ArkUI_NodeContentHandle GetContentHandle() const
    {
        return handle_;
    }

private:
    std::shared_ptr<ArkUIBaseNode> root_;
    ArkUI_NodeContentHandle handle_;
};

} // namespace NativeModule

#endif // NATIVEENTRY_H