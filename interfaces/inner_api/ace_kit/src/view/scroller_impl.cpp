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

#include "interfaces/inner_api/ace_kit/src/view/scroller_impl.h"

#include <functional>
#include <limits>
#include <type_traits>

#include "view/frame_node_impl.h"

#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_controller.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::Kit {

ScrollerImpl::ScrollerImpl(const RefPtr<Framework::JSScroller>& jsScroller) : jsScroller_(jsScroller) {}

void ScrollerImpl::AddObserver(const Observer& observer, int32_t id)
{
    ScrollerObserver scrollerObserver;
    scrollerObserver.onReachStartEvent = observer.onReachStartEvent;
    scrollerObserver.onReachEndEvent = observer.onReachEndEvent;
    scrollerObserver.onScrollStartEvent = observer.onScrollStartEvent;
    scrollerObserver.onScrollStopEvent = observer.onScrollStopEvent;
    scrollerObserver.onDidScrollEvent = observer.onDidScrollEvent;
    scrollerObserver.onScrollerAreaChangeEvent = observer.onScrollerAreaChangeEvent;
    scrollerObserver.onWillScrollEventEx = observer.onWillScrollEventEx;
    scrollerObserver.twoDimensionOnWillScrollEvent = observer.twoDimensionOnWillScrollEvent;
    jsScroller_->AddObserver(scrollerObserver, id);
}

void ScrollerImpl::RemoveObserver(int32_t id)
{
    jsScroller_->RemoveObserver(id);
}

double ScrollerImpl::GetCurrentOffsetX()
{
    RefPtr<ScrollControllerBase> scrollController = jsScroller_->GetController().Upgrade();
    if (!scrollController) {
        return 0.0;
    }
    return scrollController->GetCurrentOffset().GetX();
}

double ScrollerImpl::GetCurrentOffsetY()
{
    RefPtr<ScrollControllerBase> scrollController = jsScroller_->GetController().Upgrade();
    if (!scrollController) {
        return 0.0;
    }
    return scrollController->GetCurrentOffset().GetY();
}

RefPtr<NG::ScrollablePattern> GetScrollablePattern(const RefPtr<Framework::JSScroller>& jsScroller)
{
    auto controller = jsScroller->GetController().Upgrade();
    CHECK_NULL_RETURN(controller, nullptr);
    auto scrollableController = AceType::DynamicCast<NG::ScrollableController>(controller);
    CHECK_NULL_RETURN(scrollableController, nullptr);
    auto scrollablePattern = scrollableController->GetScrollPattern().Upgrade();
    return scrollablePattern;
}

bool ScrollerImpl::IsAtEnd()
{
    RefPtr<ScrollControllerBase> scrollController = jsScroller_->GetController().Upgrade();
    if (!scrollController) {
        return false;
    }
    return scrollController->IsAtEnd();
}

bool ScrollerImpl::IsAtStart()
{
    auto scrollablePattern = GetScrollablePattern(jsScroller_);
    if (!scrollablePattern) {
        return false;
    }
    return scrollablePattern->IsAtTop();
}

double GetScrollableOffsetY(const RefPtr<NG::ScrollablePattern>& pattern, const RefPtr<FrameNode>& node)
{
    auto scrollableNode = pattern->GetHost();
    CHECK_NULL_RETURN(scrollableNode, 0.0f);
    auto context = scrollableNode->GetRenderContext();
    CHECK_NULL_RETURN(context, 0.0f);
    auto offset = context->GetPaintRectWithTransform().GetOffset();
    auto parent = scrollableNode->GetAncestorNodeOfFrame(true);
    auto nodeImpl = AceType::DynamicCast<FrameNodeImpl>(node);
    while (parent && parent != nodeImpl->GetAceNode()) {
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, 0.0f);
        offset += renderContext->GetPaintRectWithTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return offset.GetY();
}

std::pair<int32_t, int32_t> startEndIndices(const RefPtr<NG::GridPattern>& pattern)
{
    const auto& gridLayoutInfo = pattern->GetGridLayoutInfo();
    return { gridLayoutInfo.startIndex_, gridLayoutInfo.endIndex_ };
}

std::pair<int32_t, int32_t> startEndIndices(const RefPtr<NG::ListPattern>& pattern)
{
    return { pattern->GetStartIndex(), pattern->GetEndIndex() };
}

std::pair<int32_t, int32_t> startEndIndices(const RefPtr<NG::ScrollPattern>& pattern)
{
    return { 0, 0 };
}

std::pair<int32_t, int32_t> startEndIndices(const RefPtr<NG::WaterFlowPattern>& pattern)
{
    return { pattern->GetBeginIndex(), pattern->GetEndIndex() };
}

enum class Edge {
    TOP,
    BOTTOM
};

template<typename T, Edge edge>
double GetContentEdge(const RefPtr<T>& pattern, const RefPtr<FrameNode>& node)
{
    const auto [startIndex, endIndex] = startEndIndices(pattern);
    APP_LOGD("[HDS_TABS] ScrollerImpl::GetContentEdge(): startIndex = %{public}d, endIndex = %{public}d",
        startIndex, endIndex);
    auto edgePosition = 0.0;
    const auto& rect = pattern->GetItemRect(startIndex);
    if constexpr (edge == Edge::TOP) {
        edgePosition = rect.Top();
    } else {
        edgePosition = rect.Bottom();
    }
    for (auto i = startIndex + 1; i <= endIndex; ++i) {
        const auto& rect = pattern->GetItemRect(i);
        if constexpr (edge == Edge::TOP) {
            if (const auto e = rect.Top(); e < edgePosition) {
                edgePosition = e;
            }
        } else {
            if (const auto e = rect.Bottom(); e > edgePosition) {
                edgePosition = e;
            }
        }
    }
    APP_LOGD("[HDS_TABS]  ScrollerImpl::GetContentEdge(): edge = %{public}f", edgePosition);
    edgePosition += GetScrollableOffsetY(pattern, node);
    return edgePosition;
}

template<Edge edge>
double GetContentEdge(const RefPtr<Framework::JSScroller>& jsScroller, const RefPtr<FrameNode>& node)
{
    APP_LOGD("[HDS_TABS] -> ScrollerImpl::GetEdge()");
    auto scrollablePattern = GetScrollablePattern(jsScroller);
    CHECK_NULL_RETURN(scrollablePattern, 0.0);

    auto gridPattern = AceType::DynamicCast<NG::GridPattern>(scrollablePattern);
    if (gridPattern) {
        APP_LOGD("[HDS_TABS]   ScrollerImpl::GetEdge(): GridPattern");
        return GetContentEdge<NG::GridPattern, edge>(gridPattern, node);
    }

    auto listPattern = AceType::DynamicCast<NG::ListPattern>(scrollablePattern);
    if (listPattern) {
        APP_LOGD("[HDS_TABS]   ScrollerImpl::GetEdge(): ListPattern");
        return GetContentEdge<NG::ListPattern, edge>(listPattern, node);
    }

    auto scrollPattern = AceType::DynamicCast<NG::ScrollPattern>(scrollablePattern);
    if (scrollPattern) {
        APP_LOGD("[HDS_TABS]   ScrollerImpl::GetEdge(): ScrollPattern");
        return GetContentEdge<NG::ScrollPattern, edge>(scrollPattern, node);
    }

    auto waterFlowPattern = AceType::DynamicCast<NG::WaterFlowPattern>(scrollablePattern);
    if (waterFlowPattern) {
        APP_LOGD("[HDS_TABS]   ScrollerImpl::GetEdge(): WaterFlowPattern");
        return GetContentEdge<NG::WaterFlowPattern, edge>(waterFlowPattern, node);
    }

    return 0.0;
}

template<Edge edge>
double GetScrollableEdge(const RefPtr<NG::ScrollablePattern>& pattern, const RefPtr<FrameNode>& node)
{
    auto edgePosition = 0.0;
    auto scrollableNode = pattern->GetHost();
    CHECK_NULL_RETURN(scrollableNode, edgePosition);
    auto geometryNode = scrollableNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, edgePosition);
    const auto& rect = geometryNode->GetFrameRect();
    if constexpr (edge != Edge::TOP) {
        edgePosition = rect.Bottom() - rect.Top();
    }
    APP_LOGD("[HDS_TABS]  ScrollerImpl::GetScrollableEdge(): edge = %{public}f", edgePosition);
    edgePosition += GetScrollableOffsetY(pattern, node);
    return edgePosition;
}

template<Edge edge>
double GetScrollableEdge(const RefPtr<Framework::JSScroller>& jsScroller, const RefPtr<FrameNode>& node)
{
    auto scrollablePattern = GetScrollablePattern(jsScroller);
    CHECK_NULL_RETURN(scrollablePattern, 0.0);
    return GetScrollableEdge<edge>(scrollablePattern, node);
}

double ScrollerImpl::GetContentTop(const RefPtr<FrameNode>& node)
{
    auto scrollablePattern = GetScrollablePattern(jsScroller_);
    CHECK_NULL_RETURN(scrollablePattern, 0.0);
    auto scrollPattern = AceType::DynamicCast<NG::ScrollPattern>(scrollablePattern);
    auto waterFlowPattern = AceType::DynamicCast<NG::WaterFlowPattern>(scrollablePattern);
    auto listPattern = AceType::DynamicCast<NG::ListPattern>(scrollablePattern);
    if (listPattern) {
        auto scrollableEdge = GetScrollableEdge<Edge::TOP>(jsScroller_, node);
        auto contentEdge = GetContentEdge<Edge::TOP>(jsScroller_, node);
        APP_LOGD("[HDS_TABS] scrollableEdge %{public}f contentEdge %{public}f", scrollableEdge, contentEdge);
        return std::max(scrollableEdge, contentEdge);
    }
    bool isNeedGetScrollableEdge = (waterFlowPattern && !waterFlowPattern->GetItemStart()) ||
        (!waterFlowPattern && !scrollPattern && !IsAtStart());
    if (isNeedGetScrollableEdge) {
        return GetScrollableEdge<Edge::TOP>(jsScroller_, node);
    }
    return GetContentEdge<Edge::TOP>(jsScroller_, node);
}

double ScrollerImpl::GetContentBottom(const RefPtr<FrameNode>& node)
{
    auto scrollablePattern = GetScrollablePattern(jsScroller_);
    CHECK_NULL_RETURN(scrollablePattern, 0.0);
    auto scrollPattern = AceType::DynamicCast<NG::ScrollPattern>(scrollablePattern);
    auto waterFlowPattern = AceType::DynamicCast<NG::WaterFlowPattern>(scrollablePattern);
    auto listPattern = AceType::DynamicCast<NG::ListPattern>(scrollablePattern);
    if (listPattern) {
        auto scrollableEdge = GetScrollableEdge<Edge::BOTTOM>(jsScroller_, node);
        auto contentEdge = GetContentEdge<Edge::BOTTOM>(jsScroller_, node);
        APP_LOGD("[HDS_TABS] scrollableEdge %{public}f contentEdge %{public}f", scrollableEdge, contentEdge);
        return std::min(scrollableEdge, contentEdge);
    }
    bool isNeedGetScrollableEdge = (waterFlowPattern && !waterFlowPattern->GetItemEnd()) ||
        (!waterFlowPattern && !scrollPattern && !IsAtEnd());
    if (isNeedGetScrollableEdge) {
        return GetScrollableEdge<Edge::BOTTOM>(jsScroller_, node);
    }
    return GetContentEdge<Edge::BOTTOM>(jsScroller_, node);
}

bool ScrollerImpl::AnimateTo(const Dimension& position, float duration,
    const RefPtr<Curve>& curve, bool smooth, bool canOverScroll)
{
    RefPtr<ScrollControllerBase> scrollController = jsScroller_->GetController().Upgrade();
    if (!scrollController) {
        return false;
    }
    return scrollController->AnimateTo(position, duration, curve, smooth, canOverScroll);
}

bool ScrollerImpl::operator==(const Ace::RefPtr<Scroller>& other) const
{
    auto impl = AceType::DynamicCast<Ace::Kit::ScrollerImpl>(other);
    CHECK_NULL_RETURN(impl, false);
    return jsScroller_ == impl->jsScroller_;
}

RefPtr<FrameNode> ScrollerImpl::GetBindingFrameNode()
{
    auto pattern = GetScrollablePattern(jsScroller_);
    CHECK_NULL_RETURN(pattern, nullptr);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto kitNode = host->GetKitNode();
    if (kitNode) {
        return kitNode;
    }

    kitNode = AceType::MakeRefPtr<FrameNodeImpl>(AceType::RawPtr(host));
    host->SetKitNode(kitNode);
    return kitNode;
}
} // namespace OHOS::Ace::Kit
