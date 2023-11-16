/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/waterflow/water_flow_paint_method.h"

namespace OHOS::Ace::NG {
SizeF WaterFlowPattern::GetContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    return geometryNode->GetPaddingSize();
}

bool WaterFlowPattern::UpdateCurrentOffset(float delta, int32_t source)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<WaterFlowLayoutProperty>();
    if (layoutProperty->IsReverse()) {
        if (source != SCROLL_FROM_ANIMATION_SPRING) {
            delta = -delta;
        }
    }

    // check edgeEffect is not springEffect
    if (!HandleEdgeEffect(delta, source, GetContentSize(), layoutProperty->IsReverse())) {
        if (IsOutOfBoundary()) {
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        return false;
    }
    SetScrollSource(source);

    if (GetScrollEdgeEffect()) {
        // over scroll in drag update from normal to over scroll.
        float overScroll = 0.0f;
        if (layoutInfo_.itemStart_ && delta > 0) {
            overScroll = layoutInfo_.currentOffset_ + delta;
        }
        if (layoutInfo_.offsetEnd_ && delta < 0) {
            overScroll = GetMainContentSize() - (layoutInfo_.GetMaxMainHeight() + layoutInfo_.currentOffset_ - delta);
        }
        if (source == SCROLL_FROM_UPDATE) {
            auto friction = ScrollablePattern::CalculateFriction(std::abs(overScroll) / GetMainContentSize());
            delta *= friction;
        }
    } else {
        if (layoutInfo_.itemStart_ && delta > 0) {
            return false;
        }
        if (layoutInfo_.offsetEnd_ && delta < 0) {
            return false;
        }
    }

    layoutInfo_.prevOffset_ = layoutInfo_.currentOffset_;
    layoutInfo_.currentOffset_ += delta;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    FireAndCleanScrollingListener();
    return true;
};

bool WaterFlowPattern::IsScrollable() const
{
    return !(IsAtTop() && IsAtBottom() &&  !GetAlwaysEnabled());
}
bool WaterFlowPattern::IsAtTop() const
{
    return layoutInfo_.itemStart_;
};
bool WaterFlowPattern::IsAtBottom() const
{
    return layoutInfo_.offsetEnd_;
};
bool WaterFlowPattern::IsReverse() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->IsReverse();
}
OverScrollOffset WaterFlowPattern::GetOverScrollOffset(double delta) const
{
    OverScrollOffset offset = { 0, 0 };
    if (layoutInfo_.startIndex_ == 0) {
        auto startPos = layoutInfo_.currentOffset_;
        auto newStartPos = startPos + delta;
        if (startPos > 0 && newStartPos > 0) {
            offset.start = delta;
        }
        if (startPos > 0 && newStartPos <= 0) {
            offset.start = -startPos;
        }
        if (startPos <= 0 && newStartPos > 0) {
            offset.start = newStartPos;
        }
    }
    if (layoutInfo_.itemEnd_) {
        auto endPos = layoutInfo_.currentOffset_ + layoutInfo_.maxHeight_;
        auto newEndPos = endPos + delta;
        if (endPos < layoutInfo_.lastMainSize_ && newEndPos < layoutInfo_.lastMainSize_) {
            offset.end = delta;
        }
        if (endPos < layoutInfo_.lastMainSize_ && newEndPos >= layoutInfo_.lastMainSize_) {
            offset.end = layoutInfo_.lastMainSize_ - endPos;
        }
        if (endPos >= layoutInfo_.lastMainSize_ && newEndPos < layoutInfo_.lastMainSize_) {
            offset.end = newEndPos - layoutInfo_.lastMainSize_;
        }
    }
    return offset;
}

void WaterFlowPattern::UpdateScrollBarOffset() {};

RefPtr<LayoutAlgorithm> WaterFlowPattern::CreateLayoutAlgorithm()
{
    auto algorithm = AceType::MakeRefPtr<WaterFlowLayoutAlgorithm>(layoutInfo_);
    algorithm->SetCanOverScroll(CanOverScroll(GetScrollSource()));
    return algorithm;
}

RefPtr<NodePaintMethod> WaterFlowPattern::CreateNodePaintMethod()
{
    auto paint = MakeRefPtr<WaterFlowPaintMethod>();
    if (!contentModifier_) {
        contentModifier_ = AceType::MakeRefPtr<WaterFlowContentModifier>();
    }
    paint->SetContentModifier(contentModifier_);
    auto scrollEffect = GetScrollEdgeEffect();
    if (scrollEffect && scrollEffect->IsFadeEffect()) {
        paint->SetEdgeEffect(scrollEffect);
    }
    return paint;
}

void WaterFlowPattern::OnModifyDone()
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    // SetAxis for scroll event
    SetAxis(layoutProperty->GetAxis());
    if (!GetScrollableEvent()) {
        InitScrollableEvent();
    }
    SetEdgeEffect();
    SetAccessibilityAction();
}

bool WaterFlowPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = dirty->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<WaterFlowLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    auto layoutInfo = layoutAlgorithm->GetLayoutInfo();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto eventHub = host->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto onScroll = eventHub->GetOnScroll();
    if (onScroll) {
        FireOnScroll(layoutInfo.prevOffset_ - layoutInfo.currentOffset_, onScroll);
    }
    bool indexChanged =
        layoutInfo_.startIndex_ != layoutInfo.startIndex_ || layoutInfo_.endIndex_ != layoutInfo.endIndex_;
    if (indexChanged) {
        auto onScrollIndex = eventHub->GetOnScrollIndex();
        if (onScrollIndex) {
            onScrollIndex(layoutInfo.startIndex_, layoutInfo.endIndex_);
        }
    }
    if (layoutInfo.itemStart_ && !layoutInfo_.itemStart_) {
        auto onReachStart = eventHub->GetOnReachStart();
        if (onReachStart) {
            onReachStart();
        }
    }
    if (layoutInfo.offsetEnd_ && !layoutInfo_.offsetEnd_) {
        auto onReachEnd = eventHub->GetOnReachEnd();
        if (onReachEnd) {
            onReachEnd();
        }
    }
    OnScrollStop(eventHub->GetOnScrollStop(), false);

    layoutInfo_ = std::move(layoutInfo);
    layoutInfo_.UpdateStartIndex();

    CheckScrollable();

    auto property = host->GetLayoutProperty();
    CHECK_NULL_RETURN(host, false);
    return property->GetPaddingProperty() != nullptr;
}

void WaterFlowPattern::CheckScrollable()
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    SetScrollEnable(IsScrollable());
    if (!layoutProperty->GetScrollEnabled().value_or(IsScrollable())) {
        SetScrollEnable(false);
    }
}

void WaterFlowPattern::InitScrollableEvent()
{
    AddScrollEvent();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto scrollFrameBeginEvent = eventHub->GetOnScrollFrameBegin();
    SetScrollFrameBeginCallback(scrollFrameBeginEvent);
}

bool WaterFlowPattern::UpdateStartIndex(int32_t index)
{
    layoutInfo_.jumpIndex_ = index;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
}

int32_t WaterFlowPattern::GetRows() const
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);

    return layoutProperty->GetAxis() == Axis::VERTICAL ? layoutInfo_.GetMainCount() : layoutInfo_.GetCrossCount();
}

int32_t WaterFlowPattern::GetColumns() const
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);

    return layoutProperty->GetAxis() == Axis::VERTICAL ? layoutInfo_.GetCrossCount() : layoutInfo_.GetMainCount();
}

void WaterFlowPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->IsScrollable());
        pattern->ScrollPage(false);
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->IsScrollable());
        pattern->ScrollPage(true);
    });
}

void WaterFlowPattern::ScrollPage(bool reverse)
{
    CHECK_NULL_VOID(IsScrollable());

    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto mainContentSize = geometryNode->GetPaddingSize().MainSize(axis);

    UpdateCurrentOffset(reverse ? mainContentSize : -mainContentSize, SCROLL_FROM_JUMP);

    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
}

void WaterFlowPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("friction", GetFriction());
    auto edgeEffect = GetEdgeEffect();
    if (edgeEffect == EdgeEffect::SPRING) {
        json->Put("edgeEffect", "EdgeEffect.Spring");
    } else if (edgeEffect == EdgeEffect::FADE) {
        json->Put("edgeEffect", "EdgeEffect.Fade");
    } else {
        json->Put("edgeEffect", "EdgeEffect.None");
    }
}

std::string WaterFlowPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    jsonObj->Put("beginIndex", GetBeginIndex());
    Dimension dimension(GetStoredOffset());
    jsonObj->Put("offset", dimension.ConvertToVp());
    return jsonObj->ToString();
}

void WaterFlowPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    UpdateStartIndex(info->GetInt("beginIndex"));
    Dimension dimension(info->GetDouble("offset"), DimensionUnit::VP);
    SetRestoreOffset(dimension.ConvertToPx());
}

Rect WaterFlowPattern::GetItemRect(int32_t index) const
{
    if (index < 0 || index < layoutInfo_.startIndex_ || index > layoutInfo_.endIndex_) {
        return Rect();
    }
    index += layoutInfo_.footerIndex_ + 1;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, Rect());
    auto item = host->GetChildByIndex(index);
    CHECK_NULL_RETURN(item, Rect());
    auto itemGeometry = item->GetGeometryNode();
    CHECK_NULL_RETURN(itemGeometry, Rect());
    return Rect(itemGeometry->GetFrameRect().GetX(), itemGeometry->GetFrameRect().GetY(),
        itemGeometry->GetFrameRect().Width(), itemGeometry->GetFrameRect().Height());
}

void WaterFlowPattern::ScrollToIndex(int32_t index, bool /* smooth */, ScrollAlign /* align */)
{
    // move to layout algorithm
    if (index == LAST_ITEM) {
        index = layoutInfo_.childrenCount_ - 1;
    }
    StopAnimate();
    UpdateStartIndex(index);
    FireAndCleanScrollingListener();
}

bool WaterFlowPattern::IsOutOfBoundary(bool useCurrentDelta)
{
    bool outOfStart = layoutInfo_.itemStart_ && Positive(layoutInfo_.currentOffset_);
    bool outOfEnd = layoutInfo_.offsetEnd_ &&
                    LessNotEqual(layoutInfo_.currentOffset_ + layoutInfo_.maxHeight_, layoutInfo_.lastMainSize_);
    return outOfStart || outOfEnd;
}

void WaterFlowPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, 0.0);
        return pattern->layoutInfo_.currentOffset_;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, 0.0);
        if (pattern->GetAlwaysEnabled() &&
            GreatNotEqual(pattern->GetMainContentSize(), pattern->layoutInfo_.maxHeight_)) {
            return 0.0;
        }
        return pattern->GetMainContentSize() - pattern->layoutInfo_.maxHeight_;
    });
    scrollEffect->SetTrailingCallback([]() -> double { return 0.0; });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, 0.0);
        if (pattern->GetAlwaysEnabled() &&
            GreatNotEqual(pattern->GetMainContentSize(), pattern->layoutInfo_.maxHeight_)) {
            return 0.0;
        }
        return pattern->GetMainContentSize() - pattern->layoutInfo_.maxHeight_;
    });
    scrollEffect->SetInitTrailingCallback([]() -> double { return 0.0; });
}

void WaterFlowPattern::MarkDirtyNodeSelf()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void WaterFlowPattern::OnScrollEndCallback()
{
    scrollStop_ = true;
    MarkDirtyNodeSelf();
}

void WaterFlowPattern::OnAnimateStop()
{
    scrollStop_ = true;
    MarkDirtyNodeSelf();
}
} // namespace OHOS::Ace::NG
