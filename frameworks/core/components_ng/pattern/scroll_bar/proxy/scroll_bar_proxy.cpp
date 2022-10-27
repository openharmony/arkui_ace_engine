/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"

#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SCROLL_FROM_BAR = 6; // Source type of scroll.

bool CheckScrollable(const RefPtr<Pattern>& pattern)
{
    return AceType::InstanceOf<ScrollPattern>(pattern);
    // TO DO for grid list waterflow
}

float GetScrollableDistance(RefPtr<Pattern> pattern)
{
    auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
    if (scrollPattern) {
        return scrollPattern->GetScrollableDistance();
    }
    // TO DO for grid list waterflow
    return 0.0f;
}

float GetScrollOffset(RefPtr<Pattern> pattern)
{
    auto scrollPattern = AceType::DynamicCast<ScrollPattern>(pattern);
    if (scrollPattern) {
        LOGE("hhh GetScrollOffset 111");
        return scrollPattern->GetCurrentPosition();
    }
    LOGE("hhh GetScrollOffset 222");
    // TO DO for grid list waterflow
    return 0.0f;
}

}

void ScrollBarProxy::RegisterScrollableNode(const ScrollableNodeInfo& scrollableNode)
{
    if (std::find(scrollableNodes_.begin(), scrollableNodes_.end(), scrollableNode) != scrollableNodes_.end()) {
        LOGE("scrollable node is already exist.");
        return;
    }
    scrollableNodes_.emplace_back(scrollableNode);
}

void ScrollBarProxy::RegisterScrollBar(const WeakPtr<ScrollBarPattern>& scrollBar)
{
    if (std::find(scrollBars_.begin(), scrollBars_.end(), scrollBar) != scrollBars_.end()) {
        LOGE("scroll bar is already exist.");
        return;
    }
    scrollBars_.emplace_back(scrollBar);
}

void ScrollBarProxy::UnRegisterScrollableNode(const WeakPtr<Pattern>& scrollableNode)
{
    auto iter = std::find_if(scrollableNodes_.begin(), scrollableNodes_.end(),
        [&scrollableNode](const ScrollableNodeInfo& info) { return scrollableNode == info.scrollableNode; });
    if (iter != scrollableNodes_.end()) {
        scrollableNodes_.erase(iter);
    }
}

void ScrollBarProxy::UnRegisterScrollBar(const WeakPtr<ScrollBarPattern>& scrollBar)
{
    auto iter = std::find(scrollBars_.begin(), scrollBars_.end(), scrollBar);
    if (iter != scrollBars_.end()) {
        scrollBars_.erase(iter);
    }
}

void ScrollBarProxy::NotifyScrollableNode(float distance, const WeakPtr<ScrollBarPattern>& weakScrollBar) const
{
    // auto scrollBar = AceType::DynamicCast<ScrollBarPattern>(weakScrollBar.Upgrade());
    auto scrollBar = weakScrollBar.Upgrade();
    if (!scrollBar) {
        LOGE("ScrollBar has been released.");
        return;
    }
    float controlDistance = scrollBar->GetScrollableDistance();

    for (const auto& [weakScrollableNode, onPositionChanged] : scrollableNodes_) {
        if (onPositionChanged == nullptr) {
            LOGE("hhh ScrollBarProxy::NotifyScrollableNode onPositionChanged is nullptr");
            continue;
        }
        auto scrollable = weakScrollableNode.Upgrade();
        if (!scrollable || !CheckScrollable(scrollable)) {
            LOGE("Node is not scrollable node.");
            LOGE("hhh Node is not scrollable node.");
            continue;
        }

        float value = 0.0f;
        float scrollableDistance = GetScrollableDistance(scrollable);;
        if (!NearZero(controlDistance)) {
            value = distance * scrollableDistance / controlDistance;
        } else {
            LOGW("scroll bar scrollable distance is zero");
            LOGE("hhh Node is not scrollable node.");
        }
        LOGE("hhh ScrollBarProxy::NotifyScrollableNode distance:%{public}lf, value:%{public}lf, scrollableDistance:%{public}lf, controlDistance:%{public}lf",
            distance, value, scrollableDistance, controlDistance);
        onPositionChanged(value, SCROLL_FROM_BAR);
    }
}

void ScrollBarProxy::NotifyScrollBar(const WeakPtr<Pattern>& weakScrollableNode) const
{
    LOGE("hhh ScrollBarProxy::NotifyScrollBar");
    auto scrollable = weakScrollableNode.Upgrade();
    if (!scrollable || !CheckScrollable(scrollable)) {
        LOGE("Node is not scrollable node.");
        return;
    }

    float controlDistance = GetScrollableDistance(scrollable);
    float scrollOffset = -GetScrollOffset(scrollable); // scroll bar direction is reverse
    LOGE("hhh controlDistance:%{public}lf, scrollOffset:%{public}lf", controlDistance, scrollOffset);

    for (const auto& weakScrollBar : scrollBars_) {
        auto scrollBar = weakScrollBar.Upgrade();
        if (!scrollBar) {
            LOGE("ScrollBar is released.");
            continue;
        }

        float scrollBarOffset = 0.0f;
        float scrollableDistance = scrollBar->GetScrollableDistance();
        if (!NearZero(controlDistance)) {
            scrollBarOffset = scrollOffset * scrollableDistance / controlDistance;
        } else {
            LOGW("scroll bar scrollable distance is zero");
        }
        LOGE("hhh scrollBar:%{public}p scrollBarOffset:%{public}lf, scrollableDistance:%{public}lf",
            (void*)&*scrollBar, scrollBarOffset, scrollableDistance);
        scrollBar->SetCurrentPosition(scrollBarOffset);
    }
}

void ScrollBarProxy::StartScrollBarAnimator() const
{
    for (const auto& weakScrollBar : scrollBars_) {
        auto scrollBar = weakScrollBar.Upgrade();
        if (!scrollBar) {
            LOGE("ScrollBar is released.");
            continue;
        }
        if (scrollBar->GetDisplayMode() == DisplayMode::AUTO) {
            scrollBar->StartAnimator();
        }
    }
}

void ScrollBarProxy::StopScrollBarAnimator() const
{
    for (const auto& weakScrollBar : scrollBars_) {
        auto scrollBar = weakScrollBar.Upgrade();
        if (!scrollBar) {
            LOGE("ScrollBar is released.");
            continue;
        }
        scrollBar->StopAnimator();
    }
}

// Axis ScrollBarProxy::GetScrollableAxis(const RefPtr<Pattern>& node) const
// {
//     auto scrollPattern = AceType::DynamicCast<ScrollPattern>(node);
//     if (scrollPattern) {
//         return scrollPattern->GetAxis();
//     }
//     // auto renderGridScroll = AceType::DynamicCast<Grid>(node);
//     // if (renderGridScroll) {
//     //     return renderGridScroll->GetAxis();
//     // }
//     // auto renderList = AceType::DynamicCast<V2::RenderList>(node);
//     // if (renderList) {
//     //     return renderList->GetAxis();
//     // }
//     // auto renderWaterFlow = AceType::DynamicCast<V2::RenderWaterFlow>(node);
//     // if (renderWaterFlow) {
//     //     return renderWaterFlow->GetAxis();
//     // }
//     return Axis::NONE;
// }

// Size ScrollBarProxy::GetScrollableChildSize(
//     const RefPtr<Pattern>& scrollable, const Size& scrollableChildSize, Axis scrollBarAxis) const
// {
//     Size result = scrollableChildSize;
//     auto scrollPattern = AceType::DynamicCast<ScrollPattern>(scrollable);
//     if (scrollPattern) {
//         scrollBarAxis == Axis::VERTICAL ? result.SetHeight(scrollPattern->GetEstimatedHeight())
//                                         : result.SetWidth(scrollPattern->GetEstimatedHeight());
//         return result;
//     }
//     // auto renderGridScroll = AceType::DynamicCast<V2::RenderGridScroll>(scrollable);
//     // if (renderGridScroll) {
//     //     scrollBarAxis == Axis::VERTICAL ? result.SetHeight(renderGridScroll->GetEstimatedHeight())
//     //                                     : result.SetWidth(renderGridScroll->GetEstimatedHeight());
//     //     return result;
//     // }
//     // auto renderList = AceType::DynamicCast<V2::RenderList>(scrollable);
//     // if (renderList) {
//     //     scrollBarAxis == Axis::VERTICAL ? result.SetHeight(renderList->GetRealMainSize())
//     //                                     : result.SetWidth(renderList->GetRealMainSize());
//     //     return result;
//     // }
//     // auto renderWaterFlow = AceType::DynamicCast<V2::RenderWaterFlow>(scrollable);
//     // if (renderWaterFlow) {
//     //     scrollBarAxis == Axis::VERTICAL ? result.SetHeight(renderWaterFlow->GetEstimatedHeight())
//     //                                     : result.SetWidth(renderWaterFlow->GetEstimatedHeight());
//     //     return result;
//     // }
//     return result;
// }

// void ScrollBarProxy::AdjustParam(const RefPtr<Pattern>& scrollable, Axis scrollBarAxis, Axis& scrollableAxis,
//     Size& scrollableChildSize, Offset& scrollableChildPosition) const
// {
//     auto renderScroll = AceType::DynamicCast<RenderScroll>(scrollable);
//     if (renderScroll) {
//         scrollBarAxis == Axis::VERTICAL ? scrollableChildSize.SetHeight(renderScroll->GetEstimatedHeight())
//                                         : scrollableChildSize.SetWidth(renderScroll->GetEstimatedHeight());
//         scrollableAxis = renderScroll->GetAxis();
//         scrollableChildPosition = renderScroll->GetLastOffset();
//         return;
//     }

//     // auto renderGridScroll = AceType::DynamicCast<GridPattern>(scrollable);
//     // if (renderGridScroll) {
//     //     scrollBarAxis == Axis::VERTICAL ? scrollableChildSize.SetHeight(renderGridScroll->GetEstimatedHeight())
//     //                                     : scrollableChildSize.SetWidth(renderGridScroll->GetEstimatedHeight());
//     //     scrollableAxis = renderGridScroll->GetAxis();
//     //     scrollableChildPosition = renderGridScroll->GetLastOffset();
//     //     return;
//     // }

//     // auto renderList = AceType::DynamicCast<V2::RenderList>(scrollable);
//     // if (renderList) {
//     //     scrollBarAxis == Axis::VERTICAL ? scrollableChildSize.SetHeight(renderList->GetRealMainSize())
//     //                                     : scrollableChildSize.SetWidth(renderList->GetRealMainSize());
//     //     scrollableAxis = renderList->GetAxis();
//     //     scrollableChildPosition = renderList->GetCurrentOffset();
//     // }

//     // auto renderWaterFlow = AceType::DynamicCast<V2::RenderWaterFlow>(scrollable);
//     // if (renderWaterFlow) {
//     //     scrollBarAxis == Axis::VERTICAL ? scrollableChildSize.SetHeight(renderWaterFlow->GetEstimatedHeight())
//     //                                     : scrollableChildSize.SetWidth(renderWaterFlow->GetEstimatedHeight());
//     //     scrollableAxis = renderWaterFlow->GetAxis();
//     //     scrollableChildPosition = renderWaterFlow->GetLastOffset();
//     //     return;
//     // }
// }

} // namespace OHOS::Ace::NG