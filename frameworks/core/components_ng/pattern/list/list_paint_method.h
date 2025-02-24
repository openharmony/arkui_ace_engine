/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_METHOD_H

#include "core/components_ng/pattern/list/list_content_modifier.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_method.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
struct DividerInfo {
    float constrainStrokeWidth = 0.0f;
    float mainSize = 0.0f;
    float crossSize = 0.0f;
    float mainPadding = 0.0f;
    float crossPadding = 0.0f;
    float startMargin = 0.0f;
    float endMargin = 0.0f;
    float space = 0.0f;
    float laneGutter = 0.0f;
    int32_t lanes = 1;
    int32_t totalItemCount = 0;
    Color color = Color::TRANSPARENT;
    bool isVertical = true;
};

class ACE_EXPORT ListPaintMethod : public ScrollablePaintMethod {
    DECLARE_ACE_TYPE(ListPaintMethod, ScrollablePaintMethod)
public:
    using PositionMap = ListLayoutAlgorithm::PositionMap;
    ListPaintMethod(const V2::ItemDivider& divider, bool vertical, bool isReverse, int32_t lanes, float space)
        : ScrollablePaintMethod(vertical, isReverse), divider_(divider), lanes_(lanes), space_(space)
    {}
    ~ListPaintMethod() override = default;

    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        return listContentModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

    void UpdateDividerList(const DividerInfo& dividerInfo, bool clip);

    ListDivider HandleDividerList(int32_t index, bool lastIsGroup, int32_t laneIdx, const DividerInfo& dividerInfo);
    ListDivider HandleLastLineIndex(int32_t index, int32_t laneIdx, const DividerInfo& dividerInfo);

    void PaintEdgeEffect(PaintWrapper* paintWrapper, RSCanvas& canvas);

    void SetScrollBar(WeakPtr<ScrollBar>&& scrollBar)
    {
        scrollBar_ = scrollBar;
    }

    void SetEdgeEffect(WeakPtr<ScrollEdgeEffect>&& edgeEffect)
    {
        edgeEffect_ = edgeEffect;
    }

    void SetTotalItemCount(int32_t totalItemCount)
    {
        totalItemCount_ = totalItemCount;
    }

    void SetDirection(bool isRTL)
    {
        isRTL_ = isRTL;
    }

    void SetContentModifier(const RefPtr<ListContentModifier>& modify)
    {
        listContentModifier_ = modify;
    }

    void SetLaneIdx(int32_t idx)
    {
        initLaneIdx_ = idx;
    }

    void SetItemsPosition(const PositionMap& positionMap, const PositionMap& cachedPositionMap,
        const std::set<int32_t>& pressedItem, bool showCached, bool clip)
    {
        itemPosition_ = positionMap;
        if (showCached || clip) {
            for (auto& [index, pos] : cachedPositionMap) {
                itemPosition_[index] = pos;
            }
        }
        if (!pressedItem.empty()) {
            for (auto& child : itemPosition_) {
                if (pressedItem.find(child.second.id) != pressedItem.end()) {
                    child.second.isPressed = true;
                }
            }
        }
    }

    void SetLaneGutter(float laneGutter)
    {
        laneGutter_ = laneGutter;
    }

    float GetLaneGutter()
    {
        return laneGutter_;
    }

    void SetScrollBarOverlayModifier(WeakPtr<ScrollBarOverlayModifier>&& scrollBarOverlayModifier)
    {
        scrollBarOverlayModifier_ = scrollBarOverlayModifier;
    }

    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override
    {
        return scrollBarOverlayModifier_.Upgrade();
    }

    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override;

    void SetAdjustOffset(float adjustOffset)
    {
        adjustOffset_ = adjustOffset;
    }

private:
    V2::ItemDivider divider_;
    int32_t lanes_ = 1;
    int32_t initLaneIdx_ = 0;
    int32_t totalItemCount_ = 0;
    float space_;
    float laneGutter_ = 0.0f;
    PositionMap itemPosition_;
    float adjustOffset_ = 0.0f;
    RefPtr<ListContentModifier> listContentModifier_;

    WeakPtr<ScrollBar> scrollBar_;
    WeakPtr<ScrollEdgeEffect> edgeEffect_;
    WeakPtr<ScrollBarOverlayModifier> scrollBarOverlayModifier_;
    bool isRTL_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_METHOD_H