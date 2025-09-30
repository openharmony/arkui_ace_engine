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

#ifndef SCROLLABLE_COMPONENT_COMMON_ARKUINODE_H
#define SCROLLABLE_COMPONENT_COMMON_ARKUINODE_H

#include <functional>
#include <list>
#include <memory>
#include <algorithm>

#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>

#include "ArkUIUtils.h"

class NodeApiInstance {
public:
    static NodeApiInstance *GetInstance()
    {
        static NodeApiInstance instance;
        return &instance;
    }
    ArkUI_NativeNodeAPI_1 *GetNativeNodeAPI() const
    {
        return nodeApi_;
    }

private:
    NodeApiInstance()
    {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeApi_);
    }
    ArkUI_NativeNodeAPI_1 *nodeApi_ = nullptr;

    NodeApiInstance(const NodeApiInstance &) = delete;
    NodeApiInstance &operator=(const NodeApiInstance &) = delete;
};

class BaseNode : public std::enable_shared_from_this<BaseNode> {
public:
    explicit BaseNode(ArkUI_NodeHandle handle)
        : nodeApi_(NodeApiInstance::GetInstance()->GetNativeNodeAPI()), nodeHandle_(handle)
    {
        if (!IsNotNull(nodeApi_) || !IsNotNull(nodeHandle_)) {
            return;
        }
        RegisterClickEvent();
    }

    virtual ~BaseNode()
    {
        UnregisterClickEvent();
        ClearChildren();
        nodeHandle_ = nullptr;
    }

    BaseNode(const BaseNode &) = delete;
    BaseNode &operator=(const BaseNode &) = delete;

    ArkUI_NodeHandle GetHandle() const
    {
        return nodeHandle_;
    }

    void AddChild(const std::shared_ptr<BaseNode> &child)
    {
        if (!IsNotNull(child) || !ValidateApiAndNode(nodeApi_, nodeHandle_, "BaseNode::AddChild")) {
            return;
        }
        OnAddChild(child);
        children_.push_back(child);
    }

    void RemoveChild(const std::shared_ptr<BaseNode> &child)
    {
        if (!IsNotNull(child) || !ValidateApiAndNode(nodeApi_, nodeHandle_, "BaseNode::RemoveChild")) {
            return;
        }
        auto it = std::find(children_.begin(), children_.end(), child);
        if (it != children_.end()) {
            OnRemoveChild(child);
            children_.erase(it);
        }
    }

    void InsertChild(const std::shared_ptr<BaseNode> &child, int32_t index)
    {
        if (!IsNotNull(child) || !ValidateApiAndNode(nodeApi_, nodeHandle_, "BaseNode::InsertChild")) {
            return;
        }
        OnInsertChild(child, index);
    
        if (index <= 0) {
            children_.push_front(child);
            return;
        }
        int32_t i = 0;
        auto it = children_.begin();
        for (; it != children_.end() && i < index; ++it, ++i) {}
        children_.insert(it, child);
    }

    // ---------------- 通用属性 ----------------

    void SetWidth(float width)
    {
        SetAttributeFloat32(nodeApi_, nodeHandle_, NODE_WIDTH, width);
    }

    void SetHeight(float height)
    {
        SetAttributeFloat32(nodeApi_, nodeHandle_, NODE_HEIGHT, height);
    }

    void SetWidthPercent(float percent)
    {
        SetAttributeFloat32(nodeApi_, nodeHandle_, NODE_WIDTH_PERCENT, percent);
    }

    void SetHeightPercent(float percent)
    {
        SetAttributeFloat32(nodeApi_, nodeHandle_, NODE_HEIGHT_PERCENT, percent);
    }

    void SetPercentWidth(float percent)
    {
        SetWidthPercent(percent);
    }

    void SetPercentHeight(float percent)
    {
        SetHeightPercent(percent);
    }

    void SetSize(float w, float h)
    {
        ::SetSize(nodeApi_, nodeHandle_, w, h);
    }

    void SetSizePercent(float wp, float hp)
    {
        ::SetSizePercent(nodeApi_, nodeHandle_, wp, hp);
    }

    void SetFullSize()
    {
        ::SetFullSize(nodeApi_, nodeHandle_);
    }

    void SetBackgroundColor(uint32_t color)
    {
        ::SetBackgroundColor(nodeApi_, nodeHandle_, color);
    }

    virtual void SetTransparentBackground() final
    {
        ::SetTransparentBackground(nodeApi_, nodeHandle_);
    }

    void SetOpacity(float opacity)
    {
        if (!ValidateApiAndNode(nodeApi_, nodeHandle_, "BaseNode::SetOpacity")) {
            return;
        }
        SetAttributeFloat32(nodeApi_, nodeHandle_, NODE_OPACITY, opacity);
    }

    // ---------------- 事件 ----------------

    void RegisterOnClick(const std::function<void(ArkUI_NodeEvent *)> &callback)
    {
        onClickCallback_ = callback;
    }

protected:
    virtual void OnAddChild(const std::shared_ptr<BaseNode> &child)
    {
        nodeApi_->addChild(nodeHandle_, child->GetHandle());
    }

    virtual void OnRemoveChild(const std::shared_ptr<BaseNode> &child)
    {
        nodeApi_->removeChild(nodeHandle_, child->GetHandle());
    }

    virtual void OnInsertChild(const std::shared_ptr<BaseNode> &child, int32_t index)
    {
        nodeApi_->insertChildAt(nodeHandle_, child->GetHandle(), index);
    }

    virtual void OnNodeEvent(ArkUI_NodeEvent *event)
    {
        if (OH_ArkUI_NodeEvent_GetEventType(event) == NODE_ON_CLICK && onClickCallback_) {
            onClickCallback_(event);
        }
    }

    static void StaticEventReceiver(ArkUI_NodeEvent *event)
    {
        auto *self = reinterpret_cast<BaseNode *>(OH_ArkUI_NodeEvent_GetUserData(event));
        if (IsNotNull(self)) {
            self->OnNodeEvent(event);
        }
    }

private:
    void RegisterClickEvent()
    {
        if (IsNotNull(nodeApi_) && IsNotNull(nodeHandle_)) {
            nodeApi_->registerNodeEvent(nodeHandle_, NODE_ON_CLICK, 0, this);
            hasClickEventRegistered_ = true;
        }
    }

    void UnregisterClickEvent()
    {
        if (IsNotNull(nodeApi_) && IsNotNull(nodeHandle_) && hasClickEventRegistered_) {
            nodeApi_->unregisterNodeEvent(nodeHandle_, NODE_ON_CLICK);
            hasClickEventRegistered_ = false;
        }
    }

    void ClearChildren()
    {
        children_.clear();
    }

protected:
    ArkUI_NativeNodeAPI_1 *nodeApi_ = nullptr;
    ArkUI_NodeHandle nodeHandle_ = nullptr;
    std::list<std::shared_ptr<BaseNode>> children_;
    std::function<void(ArkUI_NodeEvent *)> onClickCallback_;
    bool hasClickEventRegistered_ = false;
};

// 保活容器
template <typename T> inline std::vector<std::shared_ptr<T>> &GetKeepAliveContainer()
{
    static std::vector<std::shared_ptr<T>> keepAliveContainer;
    return keepAliveContainer;
}

#endif // SCROLLABLE_COMPONENT_COMMON_ARKUINODE_H
