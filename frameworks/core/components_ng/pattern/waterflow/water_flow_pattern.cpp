/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_sw.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/water_flow_paint_method.h"
#include "core/components_ng/pattern/waterflow/water_flow_segmented_layout.h"

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

    // check edgeEffect is not springEffect
    if (!HandleEdgeEffect(delta, source, GetContentSize())) {
        if (IsOutOfBoundary()) {
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        return false;
    }
    SetScrollSource(source);
    FireAndCleanScrollingListener();
    if (GetScrollEdgeEffect()) {
        // over scroll in drag update from normal to over scroll.
        float overScroll = layoutInfo_->CalcOverScroll(GetMainContentSize(), delta);
        if (source == SCROLL_FROM_UPDATE) {
            auto friction = ScrollablePattern::CalculateFriction(std::abs(overScroll) / GetMainContentSize());
            delta *= friction;
        }
    } else {
        if (layoutInfo_->itemStart_ && delta > 0) {
            return false;
        }
        if (layoutInfo_->offsetEnd_ && delta < 0) {
            return false;
        }
        if (layoutInfo_->Mode() == LayoutMode::TOP_DOWN && GreatNotEqual(delta, 0.0f)) {
            // adjust top overScroll
            delta = std::min(delta, -layoutInfo_->Offset());
        }
    }
    delta = -FireOnWillScroll(-delta);
    layoutInfo_->UpdateOffset(delta);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
};

bool WaterFlowPattern::IsScrollable() const
{
    return !(IsAtTop() && IsAtBottom() && !GetAlwaysEnabled());
}
bool WaterFlowPattern::IsAtTop() const
{
    return layoutInfo_->itemStart_;
};
bool WaterFlowPattern::IsAtBottom() const
{
    return layoutInfo_->offsetEnd_;
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
    return layoutInfo_->GetOverScrolledDelta(static_cast<float>(delta));
}

void WaterFlowPattern::UpdateScrollBarOffset()
{
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        return;
    }
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    auto viewSize = geometryNode->GetFrameSize();
    auto overScroll = 0.0f;
    auto info = DynamicCast<WaterFlowLayoutInfo>(layoutInfo_);
    if (Positive(info->currentOffset_)) {
        overScroll = info->currentOffset_;
    } else {
        overScroll = GetMainContentSize() - (info->GetContentHeight() + info->currentOffset_);
        overScroll = Positive(overScroll) ? overScroll : 0.0f;
    }
    HandleScrollBarOutBoundary(overScroll);
    UpdateScrollBarRegion(
        -info->currentOffset_, info->GetContentHeight(), Size(viewSize.Width(), viewSize.Height()), Offset(0.0f, 0.0f));
};

RefPtr<LayoutAlgorithm> WaterFlowPattern::CreateLayoutAlgorithm()
{
    if (targetIndex_.has_value()) {
        layoutInfo_->targetIndex_ = targetIndex_;
    }
    RefPtr<WaterFlowLayoutBase> algorithm;
    if (sections_ || SystemProperties::WaterFlowUseSegmentedLayout()) {
        algorithm = MakeRefPtr<WaterFlowSegmentedLayout>(DynamicCast<WaterFlowLayoutInfo>(layoutInfo_));
    } else if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        algorithm = MakeRefPtr<WaterFlowLayoutSW>(layoutInfo_);
    } else {
        int32_t footerIndex = -1;
        auto footer = footer_.Upgrade();
        if (footer) {
            int32_t count = footer->FrameCount();
            if (count > 0) {
                footerIndex = 0;
            }
        }
        layoutInfo_->footerIndex_ = footerIndex;
        algorithm = MakeRefPtr<WaterFlowLayoutAlgorithm>(DynamicCast<WaterFlowLayoutInfo>(layoutInfo_));
    }
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

    paint->SetScrollBar(GetScrollBar());
    CreateScrollBarOverlayModifier();
    paint->SetScrollBarOverlayModifier(GetScrollBarOverlayModifier());

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
        AddScrollEvent();
    }
    SetEdgeEffect();

    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        SetScrollBar(DisplayMode::OFF);
    } else if (paintProperty->GetScrollBarProperty()) {
        SetScrollBar(paintProperty->GetScrollBarProperty());
    }
    SetAccessibilityAction();
    Register2DragDropManager();
}

void WaterFlowPattern::TriggerModifyDone()
{
    OnModifyDone();
}

bool WaterFlowPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = dirty->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<WaterFlowLayoutBase>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto eventHub = host->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto onScroll = eventHub->GetOnScroll();
    float delta = layoutInfo_->GetDelta(prevOffset_);
    PrintOffsetLog(AceLogTag::ACE_WATERFLOW, host->GetId(), delta);
    if (onScroll) {
        FireOnScroll(delta, onScroll);
    }
    auto onDidScroll = eventHub->GetOnDidScroll();
    if (onDidScroll) {
        FireOnScroll(delta, onDidScroll);
    }
    bool indexChanged = itemRange_.first != layoutInfo_->FirstIdx() || itemRange_.second != layoutInfo_->endIndex_;
    if (indexChanged) {
        auto onScrollIndex = eventHub->GetOnScrollIndex();
        itemRange_ = { layoutInfo_->FirstIdx(), layoutInfo_->endIndex_ };
        if (onScrollIndex) {
            onScrollIndex(layoutInfo_->FirstIdx(), layoutInfo_->endIndex_);
        }
    }
    auto onReachStart = eventHub->GetOnReachStart();
    if (onReachStart && layoutInfo_->ReachStart(prevOffset_, !isInitialized_)) {
        onReachStart();
    }
    auto onReachEnd = eventHub->GetOnReachEnd();
    if (onReachEnd && layoutInfo_->ReachEnd(prevOffset_)) {
        onReachEnd();
    }
    OnScrollStop(eventHub->GetOnScrollStop());

    if (targetIndex_.has_value()) {
        ScrollToTargetIndex(targetIndex_.value());
        targetIndex_.reset();
    }
    layoutInfo_->UpdateStartIndex();
    prevOffset_ = layoutInfo_->Offset();
    layoutInfo_->jumpIndex_ = EMPTY_JUMP_INDEX;
    layoutInfo_->targetIndex_.reset();
    UpdateScrollBarOffset();
    CheckScrollable();

    isInitialized_ = true;

    return NeedRender();
}

bool WaterFlowPattern::ScrollToTargetIndex(int32_t index)
{
    if (index == LAST_ITEM) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto totalItemCount = host->TotalChildCount();
        index = totalItemCount - 1;
    }
    auto crossIndex = layoutInfo_->GetCrossIndex(index);
    if (crossIndex == -1) {
        return false;
    }
    float targetPosition = layoutInfo_->CalcTargetPosition(index, crossIndex);
    ScrollablePattern::AnimateTo(targetPosition, -1, nullptr, true);
    return true;
}

void WaterFlowPattern::CheckScrollable()
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    SetScrollEnabled(IsScrollable());
    if (!layoutProperty->GetScrollEnabled().value_or(IsScrollable())) {
        SetScrollEnabled(false);
    }
}

bool WaterFlowPattern::UpdateStartIndex(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto childCount = host->GetTotalChildCount();
    layoutInfo_->jumpIndex_ = (index == LAST_ITEM ? childCount - 1 : index);
    //if target index is footer, fix align because it will jump after fillViewport.
    if (layoutInfo_->footerIndex_ == 0 && layoutInfo_->jumpIndex_ == childCount - 1) {
        SetScrollAlign(ScrollAlign::END);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
}

int32_t WaterFlowPattern::GetRows() const
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);

    return layoutProperty->GetAxis() == Axis::VERTICAL ? layoutInfo_->GetMainCount() : layoutInfo_->GetCrossCount();
}

int32_t WaterFlowPattern::GetColumns() const
{
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);

    return layoutProperty->GetAxis() == Axis::VERTICAL ? layoutInfo_->GetCrossCount() : layoutInfo_->GetMainCount();
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

void WaterFlowPattern::ScrollPage(bool reverse, bool smooth)
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
    if (smooth) {
        float distance = reverse ? mainContentSize : -mainContentSize;
        float position = layoutInfo_->Offset() + distance;
        ScrollablePattern::AnimateTo(-position, -1, nullptr, true);
    } else {
        UpdateCurrentOffset(reverse ? mainContentSize : -mainContentSize, SCROLL_FROM_JUMP);
    }
    // AccessibilityEventType::SCROLL_END
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
    SetScrollAlign(ScrollAlign::START);
}

Rect WaterFlowPattern::GetItemRect(int32_t index) const
{
    if (index < 0 || index < layoutInfo_->startIndex_ || index > layoutInfo_->endIndex_) {
        return Rect();
    }
    index += layoutInfo_->footerIndex_ + 1;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, Rect());
    auto item = host->GetChildByIndex(index);
    CHECK_NULL_RETURN(item, Rect());
    auto itemGeometry = item->GetGeometryNode();
    CHECK_NULL_RETURN(itemGeometry, Rect());
    return Rect(itemGeometry->GetFrameRect().GetX(), itemGeometry->GetFrameRect().GetY(),
        itemGeometry->GetFrameRect().Width(), itemGeometry->GetFrameRect().Height());
}

RefPtr<WaterFlowSections> WaterFlowPattern::GetSections() const
{
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        return nullptr;
    }
    return sections_;
}

RefPtr<WaterFlowSections> WaterFlowPattern::GetOrCreateWaterFlowSections()
{
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        return nullptr;
    }
    if (sections_) {
        return sections_;
    }
    sections_ = AceType::MakeRefPtr<WaterFlowSections>();
    auto callback = [weakPattern = WeakClaim(this)](int32_t start) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->AddBuildFinishCallBack([weakPattern, start]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnSectionChanged(start);
        });
        context->RequestFrame();
    };
    auto callbackNow = [weakPattern = WeakClaim(this)](int32_t start) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnSectionChangedNow(start);
    };
    sections_->SetOnDataChange(callback);
    sections_->SetOnDataChangeNow(callbackNow);
    return sections_;
}

void WaterFlowPattern::OnSectionChanged(int32_t start)
{
    // SlidingWindow mode should never reach this callback
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        return;
    }
    auto info = DynamicCast<WaterFlowLayoutInfo>(layoutInfo_);
    CHECK_NULL_VOID(info);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t childUpdateIdx = host->GetChildrenUpdated();
    if (childUpdateIdx > -1 && info->GetSegment(childUpdateIdx - 1) == start && sections_->IsSpecialUpdate()) {
        // optimize adding or removing children in the last section. Prevent complete reset of that section.
        ++start;
    }
    info->InitSegments(sections_->GetSectionInfo(), start);
    info->margins_.clear();

    MarkDirtyNodeSelf();
}

void WaterFlowPattern::OnSectionChangedNow(int32_t start)
{
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        return;
    }
    auto info = DynamicCast<WaterFlowLayoutInfo>(layoutInfo_);
    CHECK_NULL_VOID(info);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t childUpdateIdx = host->GetChildrenUpdated();
    if (sections_->IsSpecialUpdateCAPI(childUpdateIdx)) {
        start += sections_->GetSectionInfo().size();
    }
    info->InitSegments(sections_->GetSectionInfo(), start);
    info->margins_.clear();
    MarkDirtyNodeSelf();
}

void WaterFlowPattern::ResetSections()
{
    sections_.Reset();
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        return;
    }
    layoutInfo_->Reset();
    MarkDirtyNodeSelf();
}

void WaterFlowPattern::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align)
{
    SetScrollSource(SCROLL_FROM_JUMP);
    SetScrollAlign(align);
    StopAnimate();
    if ((index >= 0) || (index == LAST_ITEM)) {
        if (smooth) {
            if (!ScrollToTargetIndex(index)) {
                targetIndex_ = index;
                auto host = GetHost();
                CHECK_NULL_VOID(host);
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            }
        } else {
            UpdateStartIndex(index);
        }
    }
    FireAndCleanScrollingListener();
}

bool WaterFlowPattern::IsOutOfBoundary(bool useCurrentDelta)
{
    return layoutInfo_->OutOfBounds();
}

void WaterFlowPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, 0.0);
        return pattern->layoutInfo_->CurrentPos();
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, 0.0);
        return pattern->layoutInfo_->BottomFinalPos(pattern->GetMainContentSize());
    });
    scrollEffect->SetTrailingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, 0.0);
        return pattern->layoutInfo_->TopFinalPos();
    });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, 0.0);
        return pattern->layoutInfo_->BottomFinalPos(pattern->GetMainContentSize());
    });
    scrollEffect->SetInitTrailingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, 0.0);
        return pattern->layoutInfo_->TopFinalPos();
    });
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

void WaterFlowPattern::AnimateTo(
    float position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll)
{
    if (layoutInfo_->Mode() == WaterFlowLayoutMode::SLIDING_WINDOW) {
        return;
    }
    ScrollablePattern::AnimateTo(position, duration, curve, smooth, canOverScroll);
}

void WaterFlowPattern::ScrollTo(float position)
{
    if (layoutInfo_->Mode() == WaterFlowLayoutMode::SLIDING_WINDOW) {
        return;
    }
    ScrollablePattern::ScrollTo(position);
}

bool WaterFlowPattern::NeedRender()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto size = geometryNode->GetPaddingSize();

    auto needRender = lastSize_ != size;
    lastSize_ = size;

    auto property = host->GetLayoutProperty();
    CHECK_NULL_RETURN(host, false);
    needRender = property->GetPaddingProperty() != nullptr || needRender;
    return needRender;
}

void WaterFlowPattern::ResetLayoutInfo()
{
    layoutInfo_->Reset();
    if (sections_) {
        layoutInfo_->InitSegments(sections_->GetSectionInfo(), 0);
    }
}

void WaterFlowPattern::AddFooter(const RefPtr<NG::UINode>& footer)
{
    // assume this is always before other children are modified, because it's called during State update.
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto prevFooter = footer_.Upgrade();
    if (!prevFooter) {
        host->AddChild(footer);
        layoutInfo_->footerIndex_ = 0;
    } else {
        host->ReplaceChild(prevFooter, footer);
    }
    footer_ = footer;
    footer->SetActive(false);
}

void WaterFlowPattern::SetLayoutMode(LayoutMode mode)
{
    if (!layoutInfo_ || mode != layoutInfo_->Mode()) {
        layoutInfo_ = WaterFlowLayoutInfoBase::Create(mode);
    }
    // footer index only set during first AddFooter call
    if (footer_.Upgrade()) {
        layoutInfo_->footerIndex_ = 0;
    }
}

int32_t WaterFlowPattern::GetChildrenCount() const
{
    auto host = GetHost();
    if (host) {
        return host->GetTotalChildCount();
    }
    return 0;
}
} // namespace OHOS::Ace::NG
