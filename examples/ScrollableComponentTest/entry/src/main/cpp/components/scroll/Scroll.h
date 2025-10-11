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

#ifndef SCROLLABLE_COMPONENT_COMPONENTS_SCROLL_H
#define SCROLLABLE_COMPONENT_COMPONENTS_SCROLL_H

#include <cstdint>
#include <functional>

#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>

#include "common/ArkUINode.h"
#include "common/ArkUIUtils.h"
#include "common/ArkUIScrollEvents.h"

/**
 * @brief ArkUI Scroll 节点轻封装
 */
class Scroll {
public:
    using OnScrollState = std::function<void(ArkUI_ScrollState state)>;
    using OnWillScroll = std::function<void(float dx, float dy, ArkUI_ScrollState state, ArkUI_ScrollSource src)>;
    using OnDidScroll = std::function<void(float dx, float dy, ArkUI_ScrollState state)>;

    void SetOnScrollStateChanged(OnScrollState cb)
    {
        onState_ = std::move(cb);
    }
    void SetOnWillScroll(OnWillScroll cb)
    {
        onWill_ = std::move(cb);
    }
    void SetOnDidScroll(OnDidScroll cb)
    {
        onDid_ = std::move(cb);
    }

    static ArkUI_NodeHandle CreateScrollableInfiniteScroll();

public:
    Scroll()
    {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, api_);
        scroll_ = api_->createNode(ARKUI_NODE_SCROLL);
        api_->addNodeEventReceiver(scroll_, StaticEvent);
        scrollGuard_.Bind(api_, scroll_, this, SCROLL_EVT_ALL);
    }

    ~Scroll()
    {
        scrollGuard_.Release();
        scroll_ = nullptr;
        api_ = nullptr;
    }

    // ===== 通用布局/外观 =====
    void SetWidthPercent(float percent)
    {
        SetAttributeFloat32(api_, scroll_, NODE_WIDTH_PERCENT, percent);
    }
    void SetHeightPercent(float percent)
    {
        SetAttributeFloat32(api_, scroll_, NODE_HEIGHT_PERCENT, percent);
    }
    void SetBackgroundColor(uint32_t color)
    {
        SetAttributeUInt32(api_, scroll_, NODE_BACKGROUND_COLOR, color);
    }

    void SetDirection(ArkUI_ScrollDirection direction)
    {
        ArkUI_NumberValue v{.i32 = static_cast<int32_t>(direction)};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_SCROLL_DIRECTION, &it);
    }

    void SetScrollBarDisplayMode(ArkUI_ScrollBarDisplayMode displayMode)
    {
        ArkUI_NumberValue v{.i32 = static_cast<int32_t>(displayMode)};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_BAR_DISPLAY_MODE, &it);
    }

    void SetScrollBarWidth(float w)
    {
        ArkUI_NumberValue v{.f32 = w};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_BAR_WIDTH, &it);
    }

    void SetScrollBarColor(uint32_t argb)
    {
        ArkUI_NumberValue v{.u32 = argb};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_BAR_COLOR, &it);
    }

    /** @brief 滚动条外边距：top,right,bottom,left（单位：vp） */
    void SetScrollBarMargin(float top, float right, float bottom, float left)
    {
        ArkUI_NumberValue vTop{.f32 = top};
        ArkUI_NumberValue vRight{.f32 = right};
        ArkUI_NumberValue vBottom{.f32 = bottom};
        ArkUI_NumberValue vLeft{.f32 = left};
        ArkUI_NumberValue v[] = {vTop, vRight, vBottom, vLeft};
        ArkUI_AttributeItem it{v, 4};
        api_->setAttribute(scroll_, NODE_SCROLL_BAR_MARGIN, &it);
    }

    void SetEnableScrollInteraction(bool enable)
    {
        ArkUI_NumberValue v{.i32 = enable ? 1 : 0};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, &it);
    }

    void SetFriction(float friction)
    {
        SetAttributeFloat32(api_, scroll_, NODE_SCROLL_FRICTION, friction);
    }

    void SetNestedMode(ArkUI_ScrollNestedMode mode)
    {
        ArkUI_NumberValue v{.i32 = static_cast<int32_t>(mode)};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_NESTED_SCROLL, &it);
    }

    void SetScrollEdge(ArkUI_ScrollEdge edge)
    {
        ArkUI_NumberValue v{.i32 = static_cast<int32_t>(edge)};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_EDGE, &it);
    }

    void SetContentClipMode(ArkUI_ContentClipMode clipMode)
    {
        ArkUI_NumberValue v{.i32 = static_cast<int32_t>(clipMode)};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_CLIP_CONTENT, &it);
    }

    void SetClipContent(bool clip)
    {
        ArkUI_NumberValue v{.i32 = clip ? 1 : 0};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_CLIP_CONTENT, &it);
    }

    void SetPageEnabled(bool enable)
    {
        ArkUI_NumberValue v{.i32 = enable ? 1 : 0};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_PAGE, &it);
    }

    void SetBackToTopEnabled(bool enable)
    {
        ArkUI_NumberValue v{.i32 = enable ? 1 : 0};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_BACK_TO_TOP, &it);
    }

    // 偏移/尺寸/By/Fling/渐隐/限速
    void SetOffset(float x, float y)
    {
        ArkUI_NumberValue vx{.f32 = x};
        ArkUI_NumberValue vy{.f32 = y};
        ArkUI_NumberValue v[] = {vx, vy};
        ArkUI_AttributeItem it{v, 2};
        api_->setAttribute(scroll_, NODE_SCROLL_OFFSET, &it);
    }

    void SetSize(float w, float h)
    {
        ArkUI_NumberValue vw{.f32 = w};
        ArkUI_NumberValue vh{.f32 = h};
        ArkUI_NumberValue v[] = {vw, vh};
        ArkUI_AttributeItem it{v, 2};
        api_->setAttribute(scroll_, NODE_SCROLL_SIZE, &it);
    }

    void ScrollBy(float dx, float dy)
    {
        ArkUI_NumberValue vx{.f32 = dx};
        ArkUI_NumberValue vy{.f32 = dy};
        ArkUI_NumberValue v[] = {vx, vy};
        ArkUI_AttributeItem it{v, 2};
        api_->setAttribute(scroll_, NODE_SCROLL_BY, &it);
    }

    void Fling(float velocity)
    {
        ArkUI_NumberValue v{.f32 = velocity};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_FLING, &it);
    }

    void SetFadingEdge(float len)
    {
        ArkUI_NumberValue v{.f32 = len};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_FADING_EDGE, &it);
    }

    void SetFlingSpeedLimit(float limit)
    {
        ArkUI_NumberValue v{.f32 = limit};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_FLING_SPEED_LIMIT, &it);
    }

    /**
     * @brief 设置 Scroll 组件的边缘效果（越界回弹/发光等）。
     * @param effect [IN] 边缘效果类型，取值为 ArkUI_EdgeEffect（如 ARKUI_EDGE_EFFECT_NONE、ARKUI_EDGE_EFFECT_SPRING）。
     * @param enableWhenContentSmaller [IN] 当内容尺寸小于组件本身时是否仍启用边缘效果（1 启用，0 禁用）。
     * @param edge [IN] 生效方向，ArkUI_EffectEdge，可位或组合（如 ARKUI_EFFECT_EDGE_START | ARKUI_EFFECT_EDGE_END）。
     * @note 对应属性：NODE_SCROLL_EDGE_EFFECT；ArkUI_AttributeItem.value
     * 含义：[0].i32=effect，[1].i32=enableWhenContentSmaller，[2].i32=edge。
     */
    void SetEdgeEffect(ArkUI_EdgeEffect effect, bool enableWhenContentSmaller, ArkUI_EffectEdge edge)
    {
        ArkUI_NumberValue v[3];
        v[0].i32 = static_cast<int32_t>(effect);     // [0] 效果类型
        v[1].i32 = enableWhenContentSmaller ? 1 : 0; // [1] 小内容是否启用
        v[2].i32 = static_cast<int32_t>(edge);       // [2] 生效边（位掩码）

        ArkUI_AttributeItem it{v, 3};
        api_->setAttribute(scroll_, NODE_SCROLL_EDGE_EFFECT, &it);
    }

    void SetSnapAlign(ArkUI_ScrollSnapAlign align)
    {
        ArkUI_NumberValue v{.i32 = static_cast<int32_t>(align)};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(scroll_, NODE_SCROLL_SNAP, &it);
    }

    // ===== 子节点 =====
    void AddChild(ArkUI_NodeHandle child)
    {
        if (child != nullptr) {
            api_->addChild(scroll_, child);
        }
    }

    ArkUI_NodeHandle GetScroll() const
    {
        return scroll_;
    }

private:
    inline void HandleScrollStateChanged(const ArkUI_NodeComponentEvent *comp)
    {
        if (!onState_) {
            return;
        }
        auto state = static_cast<ArkUI_ScrollState>(comp->data[0].i32);
        onState_(state);
    }

    inline void HandleWillScroll(const ArkUI_NodeComponentEvent *comp)
    {
        if (!onWill_) {
            return;
        }
        float dx = comp->data[0].f32;
        float dy = comp->data[1].f32;
        auto state = static_cast<ArkUI_ScrollState>(comp->data[2].i32);
        auto src = static_cast<ArkUI_ScrollSource>(comp->data[3].i32);
        onWill_(dx, dy, state, src);
    }

    inline void HandleDidScroll(const ArkUI_NodeComponentEvent *comp)
    {
        if (!onDid_) {
            return;
        }
        float dx = comp->data[0].f32;
        float dy = comp->data[1].f32;
        auto state = static_cast<ArkUI_ScrollState>(comp->data[2].i32);
        onDid_(dx, dy, state);
    }

    inline void HandleListWillScroll(const ArkUI_NodeComponentEvent *comp)
    {
        if (!onWill_) {
            return;
        }
        float dy = comp->data[0].f32;
        auto state = static_cast<ArkUI_ScrollState>(comp->data[1].i32);
        auto src = static_cast<ArkUI_ScrollSource>(comp->data[2].i32);
        onWill_(0.0f, dy, state, src);
    }

    inline void HandleOnWillScroll(const ArkUI_NodeComponentEvent *comp)
    {
        if (!onWill_) {
            return;
        }
        float d = comp->data[0].f32; // 单轴按约定复用 dy
        auto state = static_cast<ArkUI_ScrollState>(comp->data[1].i32);
        auto src = static_cast<ArkUI_ScrollSource>(comp->data[2].i32);
        onWill_(0.0f, d, state, src);
    }

    static void StaticEvent(ArkUI_NodeEvent *ev)
    {
        if (!ev) {
            return;
        }
        auto *self = reinterpret_cast<Scroll *>(OH_ArkUI_NodeEvent_GetUserData(ev));
        if (!self) {
            return;
        }

        const auto *comp = OH_ArkUI_NodeEvent_GetNodeComponentEvent(ev);
        if (!comp) {
            return;
        }

        switch (OH_ArkUI_NodeEvent_GetEventType(ev)) {
            case NODE_SWIPER_EVENT_ON_SCROLL_STATE_CHANGED:
                self->HandleScrollStateChanged(comp);
                break;
            case NODE_SCROLL_EVENT_ON_WILL_SCROLL:
                self->HandleWillScroll(comp);
                break;
            case NODE_SCROLL_EVENT_ON_DID_SCROLL:
                self->HandleDidScroll(comp);
                break;
            case NODE_LIST_ON_WILL_SCROLL:
                self->HandleListWillScroll(comp);
                break;
            case NODE_ON_WILL_SCROLL:
                self->HandleOnWillScroll(comp);
                break;
            default:
                break;
        }
    }

private:
    ArkUI_NativeNodeAPI_1 *api_{nullptr};
    ArkUI_NodeHandle scroll_{nullptr};
    ScrollEventGuard scrollGuard_{};

    OnScrollState onState_{};
    OnWillScroll onWill_{};
    OnDidScroll onDid_{};
};
#endif // SCROLLABLE_COMPONENT_COMPONENTS_SCROLL_H
