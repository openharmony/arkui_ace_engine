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

#ifndef SCROLLABLE_COMPONENT_COMPONENTS_REFRESH_H
#define SCROLLABLE_COMPONENT_COMPONENTS_REFRESH_H

#include <functional>
#include <memory>

#include <arkui/native_node.h>
#include <arkui/native_type.h>

#include "common/ArkUINode.h"

inline constexpr int32_t K_REFRESH_OFFSET_DATA_INDEX = 0;
inline constexpr int32_t K_REFRESH_STATE_DATA_INDEX = 0;

class Refresh : public BaseNode {
public:
    static ArkUI_NodeHandle CreateRefreshList();

    Refresh()
        : BaseNode(NodeApiInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_REFRESH)),
          registrar_(nodeApi_, GetHandle())
    {
        nodeApi_->addNodeEventReceiver(GetHandle(), StaticEvent);
    }

    // ===== 属性（组件范围）=====
    void SetRefreshing(bool refreshing)
    {
        ArkUI_NumberValue v[]{{.i32 = refreshing ? 1 : 0}};
        ArkUI_AttributeItem item{v, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_REFRESH_REFRESHING, &item);
    }

    void SetHeaderContent(const std::shared_ptr<BaseNode> &header)
    {
        if (header == nullptr) {
            nodeApi_->resetAttribute(GetHandle(), NODE_REFRESH_CONTENT);
            header_.reset();
            return;
        }
        ArkUI_AttributeItem item{nullptr, 0, nullptr, header->GetHandle()};
        nodeApi_->setAttribute(GetHandle(), NODE_REFRESH_CONTENT, &item);
        header_ = header;
    }

    void SetPullDownRatio(float ratio)
    {
        ArkUI_NumberValue v[]{{.f32 = ratio}};
        ArkUI_AttributeItem item{v, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_REFRESH_PULL_DOWN_RATIO, &item);
    }

    void SetRefreshOffset(float vp)
    {
        ArkUI_NumberValue v[]{{.f32 = vp}};
        ArkUI_AttributeItem item{v, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_REFRESH_OFFSET, &item);
    }

    void SetPullToRefresh(bool enable)
    {
        ArkUI_NumberValue v[]{{.i32 = enable ? 1 : 0}};
        ArkUI_AttributeItem item{v, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_REFRESH_PULL_TO_REFRESH, &item);
    }

    void SetMaxPullDownDistance(float vp)
    {
        ArkUI_NumberValue v[]{{.f32 = vp}};
        ArkUI_AttributeItem item{v, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_REFRESH_MAX_PULL_DOWN_DISTANCE, &item);
    }

    void AttachChild(const std::shared_ptr<BaseNode> &child)
    {
        if (child != nullptr) {
            AddChild(child);
        }
    }

    // ===== 事件注册 =====
    void RegisterOnRefresh(const std::function<void()> &cb)
    {
        onRefresh_ = cb;
        registrar_.RegisterEvent(NODE_REFRESH_ON_REFRESH, this);
    }

    void RegisterOnOffsetChange(const std::function<void(float)> &cb)
    {
        onOffsetChange_ = cb;
        registrar_.RegisterEvent(NODE_REFRESH_ON_OFFSET_CHANGE, this);
    }

    void RegisterOnStateChange(const std::function<void(int32_t)> &cb)
    {
        onStateChange_ = cb;
        registrar_.RegisterEvent(NODE_REFRESH_STATE_CHANGE, this);
    }

private:
    static void StaticEvent(ArkUI_NodeEvent *ev)
    {
        if (ev == nullptr) {
            return;
        }
        auto *self = reinterpret_cast<Refresh *>(OH_ArkUI_NodeEvent_GetUserData(ev));
        if (self == nullptr) {
            return;
        }
        self->OnNodeEvent(ev);
    }

    void OnNodeEvent(ArkUI_NodeEvent *ev) override
    {
        const int32_t type = OH_ArkUI_NodeEvent_GetEventType(ev);
        ArkUI_NodeComponentEvent *ce = OH_ArkUI_NodeEvent_GetNodeComponentEvent(ev);

        switch (type) {
            case NODE_REFRESH_ON_REFRESH:
                if (onRefresh_) {
                    onRefresh_();
                }
                break;
            case NODE_REFRESH_ON_OFFSET_CHANGE:
                if (ce != nullptr && onOffsetChange_) {
                    onOffsetChange_(ce->data[K_REFRESH_OFFSET_DATA_INDEX].f32);
                }
                break;
            case NODE_REFRESH_STATE_CHANGE:
                if (ce != nullptr && onStateChange_) {
                    onStateChange_(ce->data[K_REFRESH_STATE_DATA_INDEX].i32);
                }
                break;
            default:
                break;
        }
    }

private:
    std::shared_ptr<BaseNode> header_;
    std::function<void()> onRefresh_;
    std::function<void(float)> onOffsetChange_;
    std::function<void(int32_t)> onStateChange_;

    NodeEventRegistrar registrar_;
};

#endif // SCROLLABLE_COMPONENT_COMPONENTS_REFRESH_H
