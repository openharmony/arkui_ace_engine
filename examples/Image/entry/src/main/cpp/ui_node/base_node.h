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

#ifndef CAPI_BASE_NOSE_H
#define CAPI_BASE_NODE_H

#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <list>
#include <memory>
#include <string>

#include "utils/log.h"
#include "base_node.h"
#include "ui_node/native_module.h"

namespace Self::UI {

class BaseNode {
public:
    BaseNode(ArkUI_NodeHandle handle, const std::string &tag)
        : handle_(handle), nativeModule_(Self::UI::NativeModuleInstance::GetInstance()->GetNativeNodeAPI()), tag_(tag) {
        }

    virtual ~BaseNode() 
    {
        // 封装析构函数，实现子节点移除功能
        if (!children_.empty()) {
            for (const auto &child : children_) {
                nativeModule_->removeChild(handle_, child->GetHandle());
            }
            children_.clear();
        }
        OH_LOG_INFO(LogType::LOG_APP, "%{public}s destructor", tag_.c_str());
        // 封装析构函数，统一回收节点资源
        nativeModule_->disposeNode(handle_);
    }

    std::string GetTag() { return tag_; }

    void AddChild(const std::shared_ptr<BaseNode> &child)
    {
        children_.emplace_back(child);
        OnAddChild(child);
    }

    void RemoveChild(const std::shared_ptr<BaseNode> &child) 
    {
        children_.remove(child);
        OnRemoveChild(child);
    }

    void InsertChild(const std::shared_ptr<BaseNode> &child, int32_t index) 
    {
        if (index >= children_.size()) {
            AddChild(child);
        } else {
            auto iter = children_.begin();
            std::advance(iter, index);
            children_.insert(iter,child);
            OnInsertChild(child, index);
        }
    }

    ArkUI_NodeHandle GetHandle() const { return handle_; }

protected:
    // 针对父容器子类需要重载下面的函数，实现组件挂载和卸载。
    virtual void OnAddChild(const std::shared_ptr<BaseNode> &child) {}
    virtual void OnRemoveChild(const std::shared_ptr<BaseNode> &child) {}
    virtual void OnInsertChild(const std::shared_ptr<BaseNode> &child, int32_t index) {}

    ArkUI_NodeHandle handle_;
    ArkUI_NativeNodeAPI_1 *nativeModule_ = nullptr;

private:
    std::string tag_ = "Base";
    std::list<std::shared_ptr<BaseNode>> children_;
};

} // namespace Self::UI

#endif // CAPI_BASE_NODE_H