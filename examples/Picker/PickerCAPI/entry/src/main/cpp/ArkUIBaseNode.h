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

#ifndef ARKUIBASENODE_H
#define ARKUIBASENODE_H

#include <arkui/native_type.h>
#include <list>
#include <memory>
#include "NativeModule.h"

namespace NativeModule {

class ArkUIBaseNode {
public:
    explicit ArkUIBaseNode(ArkUI_NodeHandle handle)
        : handle_(handle),
          nativeModule_(NativeModuleInstance::GetInstance()->GetNativeNodeAPI()) {}

    virtual ~ArkUIBaseNode()
    {
        if (!children_.empty()) {
            for (const auto &child : children_) {
                nativeModule_->removeChild(handle_, child->GetHandle());
            }
            children_.clear();
        }
        nativeModule_->disposeNode(handle_);
    }

    void AddChild(const std::shared_ptr<ArkUIBaseNode> &child)
    {
        children_.emplace_back(child);
        nativeModule_->addChild(handle_, child->GetHandle());
    }

    void RemoveChild(const std::shared_ptr<ArkUIBaseNode> &child)
    {
        children_.remove(child);
        nativeModule_->removeChild(handle_, child->GetHandle());
    }

    ArkUI_NodeHandle GetHandle() const { return handle_; }

protected:
    ArkUI_NodeHandle handle_;
    ArkUI_NativeNodeAPI_1 *nativeModule_ = nullptr;

private:
    std::list<std::shared_ptr<ArkUIBaseNode>> children_;
};

} // namespace NativeModule

#endif // ARKUIBASENODE_H