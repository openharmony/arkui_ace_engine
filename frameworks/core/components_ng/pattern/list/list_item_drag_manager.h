/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_DRAG_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_DRAG_MANAGER_H

#include "base/memory/ace_type.h"
#include "base/geometry/ng/vector.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/for_each_base_node.h"

namespace OHOS::Ace::NG {

class RenderContext;

enum class ListItemDragState {
    IDLE,
    LONG_PRESS,
    DRAGGING,
};
class ListItemDragManager : public AceType {
    DECLARE_ACE_TYPE(ListItemDragManager, AceType)

public:
    struct ScaleResult {
        bool needMove;
        float scale;
    };
    ListItemDragManager(RefPtr<FrameNode> host, RefPtr<ForEachBaseNode> forEach)
    {
        frameNode_ = host;
        forEachNode_ = forEach;
        listNode_ = GetListFrameNode();
    }
    ~ListItemDragManager() override = default;

    RefPtr<FrameNode> GetHost() const
    {
        return frameNode_.Upgrade();
    }

    void InitDragDropEvent();
    void DeInitDragDropEvent();
    void SetIsNeedDividerAnimation(bool isNeedDividerAnimation);

private:
    void HandleOnItemLongPress(const GestureEvent& info);
    void HandleOnItemDragStart(const GestureEvent& info);
    void HandleOnItemDragUpdate(const GestureEvent& info);
    void HandleOnItemDragEnd(const GestureEvent& info);
    void HandleOnItemDragCancel();
    void HandleZIndexAndPosition();
    void HandleBackShadow();
    void HandleTransformScale();
    void HandleDragEndAnimation();
    void HandleScrollCallback();
    void HandleSwapAnimation(int32_t from, int32_t to);
    void SetNearbyNodeScale(RefPtr<FrameNode> node, float scale);
    ScaleResult ScaleAxisNearItem(int32_t index, const RectF& rect, const OffsetF& delta, Axis axis);
    void ScaleDiagonalItem(int32_t index, const RectF& rect, const OffsetF& delta);
    void HandleAutoScroll(int32_t index, const PointF& point, const RectF& frameRect);
    void SetPosition(const OffsetF& offset);
    void ResetPrevScaleNode();
    int32_t ScaleNearItem(int32_t index, const RectF& rect, const OffsetF& delta);
    int32_t CalcMainNearIndex(const int32_t index, const OffsetF& delta);
    int32_t CalcCrossNearIndex(const int32_t index, const OffsetF& delta);
    int32_t CalcDiagonalIndex(const int32_t mainNearIndex, const OffsetF& delta);
    int32_t GetIndex() const;
    int32_t GetLanes() const;
    bool IsInHotZone(int32_t index, const RectF& frameRect) const;
    bool IsNeedMove(const RectF& nearRect, const RectF& rect, Axis axis, float axisDelta);
    RefPtr<FrameNode> GetListFrameNode() const;
    OffsetF GetParentPaddingOffset();
    
    OffsetF dragOffset_;
    WeakPtr<FrameNode> frameNode_;
    WeakPtr<ForEachBaseNode> forEachNode_;
    WeakPtr<FrameNode> listNode_;

    std::map<WeakPtr<RenderContext>, VectorF> scaleNode_;
    std::map<WeakPtr<RenderContext>, VectorF> prevScaleNode_;
    Axis axis_ = Axis::VERTICAL;
    int32_t totalCount_ = -1;
    int32_t lanes_ = 1;
    bool isStackFromEnd_ = false;
    bool isRtl_ = false;
    bool scrolling_ = false;
    bool isDragAnimationStopped_ = true;
    OffsetF realOffset_;

    int32_t fromIndex_ = -1;

    VectorF prevScale_{ 1.f, 1.f };
    Shadow prevShadow_;
    int32_t prevZIndex_ = 0;
    ListItemDragState dragState_ = ListItemDragState::IDLE;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_ITEM_DRAG_MANAGER_H
