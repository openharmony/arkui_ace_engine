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

#ifndef SCROLLABLE_COMPONENT_COMPONENTS_LIST_H
#define SCROLLABLE_COMPONENT_COMPONENTS_LIST_H

#include <functional>
#include <memory>

#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <hilog/log.h>

#include "common/ArkUINode.h"
#include "common/ArkUIUtils.h"
#include "common/ArkUINodeAdapter.h"
#include "common/ArkUIScrollEvents.h"
#include "components/list/List.h"
#include "components/list/ListItemSwipe.h"
#include "components/list/ListItemGroup.h"

#ifndef LOG_TAG
#define LOG_TAG "List"
#endif

class List : public BaseNode {
public:
    static ArkUI_NodeHandle CreateAlphabetIndexedList();

    // 嵌套滚动模式常量
    static constexpr int32_t kNestedScrollParentFirst = 0;
    static constexpr int32_t kNestedScrollChildFirst = 1;
    static constexpr int32_t kNestedScrollSelfFirst = 2;

    // 组件事件数据数组索引常量
    static constexpr int32_t kScrollIndexFirstDataIndex = 0;
    static constexpr int32_t kScrollIndexLastDataIndex = 3;

    static constexpr int32_t kVisibleChangeFirstChildDataIndex = 0;
    static constexpr int32_t kVisibleChangeStartAreaDataIndex = 1;
    static constexpr int32_t kVisibleChangeStartIndexDataIndex = 2;
    static constexpr int32_t kVisibleChangeLastChildDataIndex = 3;
    static constexpr int32_t kVisibleChangeEndAreaDataIndex = 4;
    static constexpr int32_t kVisibleChangeEndIndexDataIndex = 5;

    static constexpr int32_t kScrollFrameBeginDataIndex = 0;

    static constexpr uint32_t kColorTransparent = 0x00000000U;

    // —— 可视内容变化事件数据 —— //
    struct VisibleContentChange {
        int32_t firstChildIndex = -1; // 可视区域首个“子组件”（item/header/footer）索引
        ArkUI_ListItemGroupArea startArea = ARKUI_LIST_ITEM_GROUP_AREA_OUTSIDE; // 起点区
        int32_t startItemIndex = -1;                                            // 若起点不是 item，则为 -1

        int32_t lastChildIndex = -1; // 可视区域最后一个“子组件”索引
        ArkUI_ListItemGroupArea endArea = ARKUI_LIST_ITEM_GROUP_AREA_OUTSIDE; // 终点区
        int32_t endItemIndex = -1;                                            // 若终点不是 item，则为 -1

        bool StartOnItem() const
        {
            return startArea == ARKUI_LIST_ITEM_SWIPE_AREA_ITEM && startItemIndex >= 0;
        }
        bool EndOnItem() const
        {
            return endArea == ARKUI_LIST_ITEM_SWIPE_AREA_ITEM && endItemIndex >= 0;
        }
    };

public:
    List()
        : BaseNode(NodeApiInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_LIST)),
          nodeApi_(NodeApiInstance::GetInstance()->GetNativeNodeAPI())
    {
        if (!IsNotNull(nodeApi_) || !IsNotNull(GetHandle())) {
            return;
        }

        nodeApi_->addNodeEventReceiver(GetHandle(), &List::StaticEventReceiver);
        const uint32_t scrollEventMask = SCROLL_EVT_FRAME_BEGIN | SCROLL_EVT_REACH_END;
        scrollEventGuard_.Bind(nodeApi_, GetHandle(), this, scrollEventMask);
    }

    ~List() override
    {
        scrollEventGuard_.Release();

        if (!IsNotNull(nodeApi_)) {
            return;
        }
        UnregisterSpecificEvents();
        ResetListAdapter();
        CleanupChildrenMainSizeOption();
    }

    // ========================================
    // 通用属性设置接口
    // ========================================
    void SetClipContent(bool clipEnabled)
    {
        SetAttributeInt32(nodeApi_, GetHandle(), NODE_SCROLL_CLIP_CONTENT, clipEnabled ? 1 : 0);
    }

    void SetEdgeEffectSpring(bool springEnabled)
    {
        int32_t effectValue = springEnabled ? ARKUI_EDGE_EFFECT_SPRING : ARKUI_EDGE_EFFECT_NONE;
        SetAttributeInt32(nodeApi_, GetHandle(), NODE_SCROLL_EDGE_EFFECT, effectValue);
    }

    void SetScrollBarVisible(bool visible)
    {
        int32_t displayMode = visible ? ARKUI_SCROLL_BAR_DISPLAY_MODE_ON : ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF;
        SetAttributeInt32(nodeApi_, GetHandle(), NODE_SCROLL_BAR_DISPLAY_MODE, displayMode);
    }

    void SetItemSpacing(float spacing)
    {
        SetAttributeFloat32(nodeApi_, GetHandle(), NODE_LIST_SPACE, spacing);
    }

    void SetScrollBarState(bool visible)
    {
        SetScrollBarVisible(visible);
    }
    void SetSpace(float spacing)
    {
        SetItemSpacing(spacing);
    }

    void SetNestedScrollMode(int32_t mode)
    {
        SetAttributeInt32(nodeApi_, GetHandle(), NODE_SCROLL_NESTED_SCROLL, mode);
    }

    // ========================================
    // 滚动控制接口
    // ========================================
    void ScrollToIndex(int32_t index)
    {
        ScrollToIndex(index, false, ARKUI_SCROLL_ALIGNMENT_START);
    }

    void ScrollToIndex(int32_t index, bool smooth, ArkUI_ScrollAlignment align)
    {
        ArkUI_NumberValue v[3];
        v[0].i32 = index;                       // value[0]
        v[1].i32 = smooth ? 1 : 0;              // value[1] (optional)
        v[2].i32 = static_cast<int32_t>(align); // value[2] (optional)

        ArkUI_AttributeItem it{v, 3};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_SCROLL_TO_INDEX, &it);
    }

    void ScrollToIndexInGroup(int32_t groupIndex, int32_t itemIndex)
    {
        ArkUI_NumberValue values[] = {{.i32 = groupIndex}, {.i32 = itemIndex}};
        ArkUI_AttributeItem item{values, 2};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_SCROLL_TO_INDEX_IN_GROUP, &item);
    }

    // ========================================
    // 适配器设置接口
    // ========================================
    void SetLazyAdapter(const std::shared_ptr<ArkUINodeAdapter> &adapter)
    {
        if (!IsNotNull(adapter)) {
            nodeApi_->resetAttribute(GetHandle(), NODE_LIST_NODE_ADAPTER);
            listAdapter_.reset();
            return;
        }
        adapter->EnsurePlaceholderTypeOr(static_cast<int32_t>(ARKUI_NODE_LIST_ITEM));
        ArkUI_AttributeItem item{nullptr, 0, nullptr, adapter->GetAdapter()};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_NODE_ADAPTER, &item);
        listAdapter_ = adapter;
    }

    // —— 扩展属性 —— //
    void SetDirection(ArkUI_Axis axis)
    {
        ArkUI_NumberValue v0{};
        v0.i32 = static_cast<int32_t>(axis);
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_DIRECTION, &it);
    }

    void SetSticky(ArkUI_StickyStyle sticky)
    {
        ArkUI_NumberValue v0{};
        v0.i32 = static_cast<int32_t>(sticky);
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_STICKY, &it);
    }

    void SetCachedCount(int32_t count)
    {
        ArkUI_NumberValue v0{};
        v0.i32 = count;
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_CACHED_COUNT, &it);
    }

    void SetInitialIndex(int32_t index)
    {
        ArkUI_NumberValue v0{};
        v0.i32 = index;
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_INITIAL_INDEX, &it);
    }

    void SetDivider(float widthPx)
    {
        ArkUI_NumberValue v0{};
        v0.f32 = widthPx;
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_DIVIDER, &it);
    }

    void SetAlignListItem(ArkUI_ListItemAlignment align)
    {
        ArkUI_NumberValue v0{};
        v0.i32 = static_cast<int32_t>(align);
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_ALIGN_LIST_ITEM, &it);
    }

    void SetChildrenMainSizeOption(ArkUI_ListChildrenMainSize *opt)
    {
        ArkUI_AttributeItem it{nullptr, 0, nullptr, opt};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_CHILDREN_MAIN_SIZE, &it);
        childrenMainSizeOption_ = opt;
    }

    void SetFocusWrapMode(int mode)
    {
        ArkUI_NumberValue v0{};
        v0.i32 = mode;
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_FOCUS_WRAP_MODE, &it);
    }

    void SetMaintainVisibleContentPosition(bool on)
    {
        ArkUI_NumberValue v0{};
        v0.i32 = on ? 1 : 0;
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_MAINTAIN_VISIBLE_CONTENT_POSITION, &it);
    }

    void SetStackFromEnd(bool on)
    {
        ArkUI_NumberValue v0{};
        v0.i32 = on ? 1 : 0;
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_STACK_FROM_END, &it);
    }

    void SetSyncLoad(bool on)
    {
        ArkUI_NumberValue v0{};
        v0.i32 = on ? 1 : 0;
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_SYNC_LOAD, &it);
    }

    void SetScrollSnapAlign(int align /*ARKUI_SCROLL_SNAP_ALIGN_**/)
    {
        ArkUI_NumberValue v0{};
        v0.i32 = align;
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_SCROLL_SNAP_ALIGN, &it);
    }

    void SetLanes(int lanes)
    {
        ArkUI_NumberValue v0{};
        v0.i32 = lanes;
        ArkUI_AttributeItem it{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_LIST_LANES, &it);
    }

    void SetContentOffsets(float startPx, float endPx)
    {
        ArkUI_NumberValue v0{};
        v0.f32 = startPx;
        ArkUI_AttributeItem it0{&v0, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_SCROLL_CONTENT_START_OFFSET, &it0);

        ArkUI_NumberValue v1{};
        v1.f32 = endPx;
        ArkUI_AttributeItem it1{&v1, 1};
        nodeApi_->setAttribute(GetHandle(), NODE_SCROLL_CONTENT_END_OFFSET, &it1);
    }

    // ========================================
    // 事件注册接口
    // ========================================
    void RegisterOnScrollIndex(const std::function<void(int32_t, int32_t)> &callback)
    {
        onScrollIndexCallback_ = callback;
        if (!isScrollIndexEventRegistered_) {
            nodeApi_->registerNodeEvent(GetHandle(), NODE_LIST_ON_SCROLL_INDEX, 0, this);
            isScrollIndexEventRegistered_ = true;
        }
    }

    // 可视区域变化
    void RegisterOnVisibleContentChange(const std::function<void(const VisibleContentChange &)> &callback)
    {
        onVisibleChangeCallback_ = callback;
        if (!isVisibleChangeEventRegistered_) {
            nodeApi_->registerNodeEvent(GetHandle(), NODE_LIST_ON_SCROLL_VISIBLE_CONTENT_CHANGE, 0, this);
            isVisibleChangeEventRegistered_ = true;
        }
    }

    void RegisterOnWillScroll(const std::function<void()> &callback)
    {
        onWillScrollCallback_ = callback;
        if (!isWillScrollEventRegistered_) {
            nodeApi_->registerNodeEvent(GetHandle(), NODE_LIST_ON_WILL_SCROLL, 0, this);
            isWillScrollEventRegistered_ = true;
        }
    }

    void RegisterOnDidScroll(const std::function<void()> &callback)
    {
        onDidScrollCallback_ = callback;
        if (!isDidScrollEventRegistered_) {
            nodeApi_->registerNodeEvent(GetHandle(), NODE_LIST_ON_DID_SCROLL, 0, this);
            isDidScrollEventRegistered_ = true;
        }
    }

    void RegisterOnReachEnd(const std::function<void()> &callback)
    {
        onReachEndCallback_ = callback;
    }

    void RegisterOnScrollFrameBegin(const std::function<void(float)> &callback)
    {
        onScrollFrameBeginCallback_ = callback;
    }

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override
    {
        BaseNode::OnNodeEvent(event);

        ArkUI_NodeComponentEvent *componentEvent = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
        if (!IsNotNull(componentEvent)) {
            return;
        }

        int32_t eventType = OH_ArkUI_NodeEvent_GetEventType(event);
        HandleSpecificListEvent(eventType, componentEvent);
    }

private:
    void UnregisterSpecificEvents()
    {
        if (isScrollIndexEventRegistered_) {
            nodeApi_->unregisterNodeEvent(GetHandle(), NODE_LIST_ON_SCROLL_INDEX);
        }
        if (isVisibleChangeEventRegistered_) {
            nodeApi_->unregisterNodeEvent(GetHandle(), NODE_LIST_ON_SCROLL_VISIBLE_CONTENT_CHANGE);
        }
        if (isWillScrollEventRegistered_) {
            nodeApi_->unregisterNodeEvent(GetHandle(), NODE_LIST_ON_WILL_SCROLL);
        }
        if (isDidScrollEventRegistered_) {
            nodeApi_->unregisterNodeEvent(GetHandle(), NODE_LIST_ON_DID_SCROLL);
        }
    }

    void ResetListAdapter()
    {
        if (IsNotNull(listAdapter_)) {
            nodeApi_->resetAttribute(GetHandle(), NODE_LIST_NODE_ADAPTER);
            listAdapter_.reset();
        }
    }

    void CleanupChildrenMainSizeOption()
    {
        if (IsNotNull(childrenMainSizeOption_)) {
            nodeApi_->resetAttribute(GetHandle(), NODE_LIST_CHILDREN_MAIN_SIZE);
            OH_ArkUI_ListChildrenMainSizeOption_Dispose(childrenMainSizeOption_);
            childrenMainSizeOption_ = nullptr;
        }
    }

    void OnScrollIndexEvt(const ArkUI_NodeComponentEvent *ev)
    {
        if (!onScrollIndexCallback_) {
            return;
        }
        const int32_t firstIndex = ev->data[kScrollIndexFirstDataIndex].i32;
        const int32_t lastIndex = ev->data[kScrollIndexLastDataIndex].i32;
        onScrollIndexCallback_(firstIndex, lastIndex);
    }

    void OnVisibleChangeEvt(const ArkUI_NodeComponentEvent *ev)
    {
        if (!onVisibleChangeCallback_) {
            return;
        }
        VisibleContentChange v{};
        v.firstChildIndex = ev->data[kVisibleChangeFirstChildDataIndex].i32;
        v.startArea = static_cast<ArkUI_ListItemGroupArea>(ev->data[kVisibleChangeStartAreaDataIndex].i32);
        v.startItemIndex = ev->data[kVisibleChangeStartIndexDataIndex].i32;
        v.lastChildIndex = ev->data[kVisibleChangeLastChildDataIndex].i32;
        v.endArea = static_cast<ArkUI_ListItemGroupArea>(ev->data[kVisibleChangeEndAreaDataIndex].i32);
        v.endItemIndex = ev->data[kVisibleChangeEndIndexDataIndex].i32;
        onVisibleChangeCallback_(v);
    }

    void OnReachEndEvt()
    {
        if (onReachEndCallback_) {
            onReachEndCallback_();
        }
    }

    void OnScrollFrameBeginEvt(const ArkUI_NodeComponentEvent *ev)
    {
        if (onScrollFrameBeginCallback_) {
            onScrollFrameBeginCallback_(ev->data[kScrollFrameBeginDataIndex].f32);
        }
    }

    void OnWillScrollEvt()
    {
        if (onWillScrollCallback_) {
            onWillScrollCallback_();
        }
    }

    void OnDidScrollEvt()
    {
        if (onDidScrollCallback_) {
            onDidScrollCallback_();
        }
    }

    void HandleSpecificListEvent(int32_t eventType, ArkUI_NodeComponentEvent *ev)
    {
        switch (eventType) {
            case NODE_LIST_ON_SCROLL_INDEX:
                OnScrollIndexEvt(ev);
                break;
            case NODE_LIST_ON_SCROLL_VISIBLE_CONTENT_CHANGE:
                OnVisibleChangeEvt(ev);
                break;
            case NODE_SCROLL_EVENT_ON_REACH_END:
                OnReachEndEvt();
                break;
            case NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN:
                OnScrollFrameBeginEvt(ev);
                break;
            case NODE_LIST_ON_WILL_SCROLL:
                OnWillScrollEvt();
                break;
            case NODE_LIST_ON_DID_SCROLL:
                OnDidScrollEvt();
                break;
            default:
                break;
        }
    }

    ArkUI_ListChildrenMainSize *EnsureChildrenMainSizeOption()
    {
        if (!childrenMainSizeOption_) {
            auto *opt = OH_ArkUI_ListChildrenMainSizeOption_Create();
            SetChildrenMainSizeOption(opt);
        }
        return childrenMainSizeOption_;
    }

    void ChildrenMainSizeSetDefault(float mainSize)
    {
        auto *opt = EnsureChildrenMainSizeOption();
        if (!opt) {
            return;
        }
        OH_ArkUI_ListChildrenMainSizeOption_SetDefaultMainSize(opt, mainSize);
    }

    float ChildrenMainSizeGetDefault() const
    {
        if (!childrenMainSizeOption_) {
            return 0.0f;
        }
        return OH_ArkUI_ListChildrenMainSizeOption_GetDefaultMainSize(childrenMainSizeOption_);
    }

    void ChildrenMainSizeResize(int32_t size)
    {
        auto *opt = EnsureChildrenMainSizeOption();
        if (!opt) {
            return;
        }
        OH_ArkUI_ListChildrenMainSizeOption_Resize(opt, size);
    }

    void ChildrenMainSizeSplice(int32_t index, int32_t deleteCount, int32_t addCount)
    {
        auto *opt = EnsureChildrenMainSizeOption();
        if (!opt) {
            return;
        }
        OH_ArkUI_ListChildrenMainSizeOption_Splice(opt, index, deleteCount, addCount);
    }

    void ChildrenMainSizeUpdate(int32_t index, float mainSize)
    {
        auto *opt = EnsureChildrenMainSizeOption();
        if (!opt) {
            return;
        }
        OH_ArkUI_ListChildrenMainSizeOption_UpdateSize(opt, index, mainSize);
    }

    float ChildrenMainSizeGet(int32_t index) const
    {
        if (!childrenMainSizeOption_) {
            return 0.0f;
        }
        return OH_ArkUI_ListChildrenMainSizeOption_GetMainSize(childrenMainSizeOption_, index);
    }

private:
    ArkUI_NativeNodeAPI_1 *nodeApi_ = nullptr;
    std::shared_ptr<ArkUINodeAdapter> listAdapter_;
    ArkUI_ListChildrenMainSize *childrenMainSizeOption_ = nullptr;

    // 事件回调函数
    std::function<void(int32_t, int32_t)> onScrollIndexCallback_;
    std::function<void(const VisibleContentChange &)> onVisibleChangeCallback_;
    std::function<void()> onReachEndCallback_;
    std::function<void(float)> onScrollFrameBeginCallback_;
    std::function<void()> onWillScrollCallback_;
    std::function<void()> onDidScrollCallback_;

    // 事件注册状态
    bool isScrollIndexEventRegistered_ = false;
    bool isVisibleChangeEventRegistered_ = false;
    bool isWillScrollEventRegistered_ = false;
    bool isDidScrollEventRegistered_ = false;

    ScrollEventGuard scrollEventGuard_;
};

#endif // SCROLLABLE_COMPONENT_COMPONENTS_LIST_H
