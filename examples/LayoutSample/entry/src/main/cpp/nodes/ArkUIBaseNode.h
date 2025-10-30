/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef MYAPPLICATION_ARKUIBASENODE_H
#define MYAPPLICATION_ARKUIBASENODE_H

#include <arkui/native_type.h>
#include <list>
#include <memory>

#include "NativeModule.h"
#include <hilog/log.h>
#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0x3200 // 全局domain宏，标识业务领域
#define LOG_TAG "NativeModule"  // 全局tag宏，标识模块日志tag
namespace NativeModule {

class ArkUIBaseNode {
public:
    explicit ArkUIBaseNode(ArkUI_NodeHandle handle)
        : handle_(handle), nativeModule_(NativeModuleInstance::GetInstance()->GetNativeNodeAPI()) {}
    
    virtual ~ArkUIBaseNode()
    {
        // 封装析构函数，实现子节点移除功能
        if (!children_.empty()) {
            for (const auto &child : children_) {
                nativeModule_->removeChild(handle_, child->GetHandle());
            }
            children_.clear();
        }
        // 封装析构函数，统一回收节点资源
        nativeModule_->disposeNode(handle_);
    }
    
    void AddChild(const std::shared_ptr<ArkUIBaseNode> &child)
    {
        children_.emplace_back(child);
        OnAddChild(child);
    }
    
    void RemoveChild(const std::shared_ptr<ArkUIBaseNode> &child)
    {
        children_.remove(child);
        OnRemoveChild(child);
    }
    
    void InsertChild(const std::shared_ptr<ArkUIBaseNode> &child, int32_t index)
    {
        if (index >= children_.size()) {
            AddChild(child);
        } else {
            auto iter = children_.begin();
            std::advance(iter, index);
            children_.insert(iter, child);
            OnInsertChild(child, index);
        }
    }
    
    int GetIndex(const std::shared_ptr<ArkUIBaseNode> &child)
    {
        int index = 0;
        for (const auto &item : children_) {
            if (item == child) {
                return index;
            }
            index++;
        }
        return -1; // 如果没找到，返回-1
    }
    
    ArkUI_NodeHandle GetHandle() const
    {
        if (!this || !handle_) {
            OH_LOG_INFO(LOG_APP, "GetHandle nullptr");
            return nullptr;
        }
        return handle_;
    }

protected:
    virtual void OnAddChild(const std::shared_ptr<ArkUIBaseNode> &child) {}
    
    virtual void OnRemoveChild(const std::shared_ptr<ArkUIBaseNode> &child) {}
    
    virtual void OnInsertChild(const std::shared_ptr<ArkUIBaseNode> &child, int32_t index) {}

    ArkUI_NodeHandle handle_;                       // ArkUI节点句柄
    ArkUI_NativeNodeAPI_1 *nativeModule_ = nullptr; // Native模块API指针

private:
    std::list<std::shared_ptr<ArkUIBaseNode>> children_; // 子节点列表
};

} // namespace NativeModule

#endif // MYAPPLICATION_ARKUIBASENODE_H