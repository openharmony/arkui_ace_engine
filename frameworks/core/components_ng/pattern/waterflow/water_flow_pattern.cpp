/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_sw.h"
#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_algorithm.h"
#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_segmented_layout.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_info_base.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_pattern.h"
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
            auto friction = CalculateFriction(std::abs(overScroll) / GetMainContentSize());
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
    MarkScrollBarProxyDirty();
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
bool WaterFlowPattern::IsAtBottom(bool considerRepeat) const
{
    return considerRepeat ? (layoutInfo_->offsetEnd_ && layoutInfo_->repeatDifference_ == 0) : layoutInfo_->offsetEnd_;
};
bool WaterFlowPattern::IsAtTopWithDelta() const
{
    return layoutInfo_->IsAtTopWithDelta();
};
bool WaterFlowPattern::IsAtBottomWithDelta() const
{
    return layoutInfo_->IsAtBottomWithDelta();
};
bool WaterFlowPattern::IsReverse() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->IsReverse();
}
bool WaterFlowPattern::IsVerticalReverse() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->IsVerticalReverse();
}
OverScrollOffset WaterFlowPattern::GetOverScrollOffset(double delta) const
{
    return layoutInfo_->GetOverScrolledDelta(static_cast<float>(delta));
}

void WaterFlowPattern::UpdateScrollBarOffset()
{
    CheckScrollBarOff();
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    auto viewSize = geometryNode->GetFrameSize();
    float overScroll = 0.0f;
    if (Positive(layoutInfo_->Offset())) {
        overScroll = layoutInfo_->Offset();
    } else if (layoutInfo_->offsetEnd_) {
        overScroll = layoutInfo_->BottomFinalPos(GetMainContentSize()) - layoutInfo_->CurrentPos();
        overScroll = Positive(overScroll) ? overScroll : 0.0f;
    }
    HandleScrollBarOutBoundary(overScroll);
    UpdateScrollBarRegion(-layoutInfo_->Offset(), layoutInfo_->EstimateTotalHeight(),
        Size(viewSize.Width(), viewSize.Height()), Offset(0.0f, 0.0f));
};

void WaterFlowPattern::BeforeCreateLayoutWrapper()
{
    for (const auto& start : sectionChangeStartPos_) {
        OnSectionChanged(start);
    }
    sectionChangeStartPos_.clear();

    if (sections_ && layoutInfo_->segmentTails_.empty()) {
        layoutInfo_->InitSegments(sections_->GetSectionInfo(), 0);
    }

    if (sections_ || SystemProperties::WaterFlowUseSegmentedLayout()) {
        return;
    }
    auto footer = footer_.Upgrade();
    if (footer && footer->FrameCount() > 0) {
        layoutInfo_->footerIndex_ = 0;
    } else {
        layoutInfo_->ResetFooter();
    }
}

RefPtr<LayoutAlgorithm> WaterFlowPattern::CreateLayoutAlgorithm()
{
    if (targetIndex_.has_value()) {
        layoutInfo_->targetIndex_ = targetIndex_;
    }
    RefPtr<WaterFlowLayoutBase> algorithm;
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        auto sw = MakeRefPtr<WaterFlowLayoutSW>(DynamicCast<WaterFlowLayoutInfoSW>(layoutInfo_));
        sw->EnableSkip((AnimateStoped() && !IsOutOfBoundary(true)) || IsBackToTopRunning());
        algorithm = sw;
    } else if (sections_ || SystemProperties::WaterFlowUseSegmentedLayout()) {
        algorithm = MakeRefPtr<WaterFlowSegmentedLayout>(DynamicCast<WaterFlowLayoutInfo>(layoutInfo_));
    } else {
        algorithm = MakeRefPtr<WaterFlowLayoutAlgorithm>(DynamicCast<WaterFlowLayoutInfo>(layoutInfo_));
    }
    algorithm->SetCanOverScrollStart(CanOverScrollStart(GetScrollSource()));
    algorithm->SetCanOverScrollEnd(CanOverScrollEnd(GetScrollSource()) && (layoutInfo_->repeatDifference_ == 0));
    return algorithm;
}

RefPtr<NodePaintMethod> WaterFlowPattern::CreateNodePaintMethod()
{
    auto paint = MakeRefPtr<WaterFlowPaintMethod>(GetAxis() == Axis::HORIZONTAL, IsReverse(), IsVerticalReverse());
    if (!contentModifier_) {
        contentModifier_ = AceType::MakeRefPtr<WaterFlowContentModifier>();
    }
    paint->SetContentModifier(contentModifier_);

    paint->SetScrollBar(GetScrollBar());
    paint->SetScrollBarOverlayModifier(GetScrollBarOverlayModifier());

    auto scrollEffect = GetScrollEdgeEffect();
    if (scrollEffect && scrollEffect->IsFadeEffect()) {
        paint->SetEdgeEffect(scrollEffect);
    }
    UpdateFadingEdge(paint);
    return paint;
}

void WaterFlowPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto layoutProperty = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    // SetAxis for scroll event
    SetAxis(layoutProperty->GetAxis());
    if (!GetScrollableEvent()) {
        AddScrollEvent();
#ifdef SUPPORT_DIGITAL_CROWN
        SetDigitalCrownEvent();
#endif
    }
    SetEdgeEffect();

    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetScrollBarProperty()) {
        SetScrollBar(paintProperty->GetScrollBarProperty());
    }
    SetAccessibilityAction();
    Register2DragDropManager();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto overlayNode = host->GetOverlayNode();
    if (!overlayNode && paintProperty->GetFadingEdge().value_or(false)) {
        CreateAnalyzerOverlay(host);
    }
}

void WaterFlowPattern::TriggerModifyDone()
{
    OnModifyDone();
}

namespace {
// check if layout is misaligned after a scroll event
bool CheckMisalignment(const RefPtr<WaterFlowLayoutInfoBase>& info)
{
    if (info->IsMisaligned()) {
        info->Reset();
        return true;
    }
    return false;
}
} // namespace

void WaterFlowPattern::TriggerPostLayoutEvents()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(eventHub);
    float delta = layoutInfo_->GetDelta(prevOffset_);
    PrintOffsetLog(AceLogTag::ACE_WATERFLOW, host->GetId(), delta);
    FireObserverOnDidScroll(delta);
    auto onScroll = eventHub->GetOnScroll();
    if (onScroll) {
        FireOnScroll(delta, onScroll);
    }
    auto onDidScroll = eventHub->GetOnDidScroll();
    if (onDidScroll) {
        FireOnScroll(delta, onDidScroll);
    }
    auto onJSFrameNodeDidScroll = eventHub->GetJSFrameNodeOnDidScroll();
    if (onJSFrameNodeDidScroll) {
        FireOnScroll(delta, onJSFrameNodeDidScroll);
    }
    bool indexChanged = itemRange_.first != layoutInfo_->FirstIdx() || itemRange_.second != layoutInfo_->endIndex_;
    auto onScrollIndex = eventHub->GetOnScrollIndex();
    auto onJsFrameNodeScrollIndex = eventHub->GetJSFrameNodeOnWaterFlowScrollIndex();
    FireOnScrollIndex(indexChanged, onScrollIndex);
    FireOnScrollIndex(indexChanged, onJsFrameNodeScrollIndex);
    if (indexChanged) {
        host->OnAccessibilityEvent(
            AccessibilityEventType::SCROLLING_EVENT, layoutInfo_->FirstIdx(), layoutInfo_->endIndex_);
    }
    auto onReachStart = eventHub->GetOnReachStart();
    auto onJSFrameNodeReachStart = eventHub->GetJSFrameNodeOnReachStart();
    FireOnReachStart(onReachStart, onJSFrameNodeReachStart);
    auto onReachEnd = eventHub->GetOnReachEnd();
    auto onJSFrameNodeReachEnd = eventHub->GetJSFrameNodeOnReachEnd();
    FireOnReachEnd(onReachEnd, onJSFrameNodeReachEnd);
    OnScrollStop(eventHub->GetOnScrollStop(), eventHub->GetJSFrameNodeOnScrollStop());
}

void WaterFlowPattern::FireOnReachStart(const OnReachEvent& onReachStart, const OnReachEvent& onJSFrameNodeReachStart)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host && layoutInfo_->ReachStart(prevOffset_, !isInitialized_));
    FireObserverOnReachStart();
    CHECK_NULL_VOID(onReachStart || onJSFrameNodeReachStart);
    ACE_SCOPED_TRACE("OnReachStart, id:%d, tag:WaterFlow", static_cast<int32_t>(host->GetAccessibilityId()));
    if (onReachStart) {
        onReachStart();
    }
    if (onJSFrameNodeReachStart) {
        onJSFrameNodeReachStart();
    }
    AddEventsFiredInfo(ScrollableEventType::ON_REACH_START);
}

void WaterFlowPattern::FireOnReachEnd(const OnReachEvent& onReachEnd, const OnReachEvent& onJSFrameNodeReachEnd)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (layoutInfo_->ReachEnd(prevOffset_, false) && layoutInfo_->repeatDifference_ == 0) {
        FireObserverOnReachEnd();
        CHECK_NULL_VOID(onReachEnd || onJSFrameNodeReachEnd);
        ACE_SCOPED_TRACE("OnReachEnd, id:%d, tag:WaterFlow", static_cast<int32_t>(host->GetAccessibilityId()));
        if (onReachEnd) {
            onReachEnd();
        }
        if (onJSFrameNodeReachEnd) {
            onJSFrameNodeReachEnd();
        }
        AddEventsFiredInfo(ScrollableEventType::ON_REACH_END);
    } else if (!isInitialized_ && layoutInfo_->ReachEnd(prevOffset_, true)) {
        FireObserverOnReachEnd();
    }
}

void WaterFlowPattern::FireOnScrollIndex(bool indexChanged, const ScrollIndexFunc& onScrollIndex)
{
    CHECK_NULL_VOID(indexChanged);
    itemRange_ = { layoutInfo_->FirstIdx(), layoutInfo_->endIndex_ };
    CHECK_NULL_VOID(onScrollIndex);
    onScrollIndex(layoutInfo_->FirstIdx(), layoutInfo_->endIndex_);
}

bool WaterFlowPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    prevOffset_ += layoutInfo_->CalibrateOffset(); // adjust prevOffset_ to keep in sync with calibrated TotalOffset
    TriggerPostLayoutEvents();

    if (targetIndex_.has_value()) {
        ScrollToTargetIndex(targetIndex_.value());
        targetIndex_.reset();
    }
    layoutInfo_->UpdateStartIndex();
    prevOffset_ = layoutInfo_->Offset();
    layoutInfo_->jumpIndex_ = WaterFlowLayoutInfoBase::EMPTY_JUMP_INDEX;
    layoutInfo_->duringPositionCalc_ = false;
    layoutInfo_->targetIndex_.reset();
    layoutInfo_->extraOffset_.reset();
    UpdateScrollBarOffset();
    CheckScrollable();

    isInitialized_ = true;

    if (layoutInfo_->startIndex_ == 0 && CheckMisalignment(layoutInfo_)) {
        MarkDirtyNodeSelf();
    }

    if (layoutInfo_->isDataValid_) {
        GetHost()->ChildrenUpdatedFrom(-1);
    }
    layoutInfo_->isDataValid_ = true;

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
    auto extraOffset = GetExtraOffset();
    if (extraOffset.has_value()) {
        targetPosition += extraOffset.value();
        ResetExtraOffset();
    }
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
    layoutInfo_->repeatDifference_ = 0;
    layoutInfo_->firstRepeatCount_ = 0;
    layoutInfo_->childrenCount_ = 0;
    GetRepeatCountInfo(
        host, layoutInfo_->repeatDifference_, layoutInfo_->firstRepeatCount_, layoutInfo_->childrenCount_);
    auto childCount = layoutInfo_->GetChildrenCount();
    layoutInfo_->jumpIndex_ = (index == LAST_ITEM ? childCount - 1 : index);
    // if target index is footer, fix align because it will jump after fillViewport.
    if (layoutInfo_->footerIndex_ == 0 && layoutInfo_->jumpIndex_ == childCount - 1) {
        SetScrollAlign(ScrollAlign::END);
    }
    if (layoutInfo_->Mode() == LayoutMode::TOP_DOWN) {
        // distinguish scrollToLastIndex and scrollToEdge in top-down mode.
        layoutInfo_->jumpIndex_ = index;
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

void WaterFlowPattern::ScrollPage(bool reverse, bool smooth, AccessibilityScrollType scrollType)
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
    float distance = reverse ? mainContentSize : -mainContentSize;
    if (scrollType == AccessibilityScrollType::SCROLL_HALF) {
        distance = distance / 2.f;
    }
    if (smooth) {
        float position = layoutInfo_->Offset() + distance;
        ScrollablePattern::AnimateTo(-position, -1, nullptr, true, false, false);
    } else {
        UpdateCurrentOffset(distance, SCROLL_FROM_JUMP);
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

int32_t WaterFlowPattern::GetItemIndex(double x, double y) const
{
    for (int32_t index = layoutInfo_->FirstIdx(); index <= layoutInfo_->endIndex_; ++index) {
        Rect rect = GetItemRect(index);
        if (rect.IsInRegion({ x, y })) {
            return index;
        }
    }
    return -1;
}

RefPtr<WaterFlowSections> WaterFlowPattern::GetSections() const
{
    return sections_;
}

RefPtr<WaterFlowSections> WaterFlowPattern::GetOrCreateWaterFlowSections()
{
    if (sections_) {
        return sections_;
    }
    sections_ = AceType::MakeRefPtr<WaterFlowSections>();
    auto sectionChangeCallback = [weakPattern = WeakClaim(this)](int32_t start) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->layoutInfo_->NotifySectionChange(start);
    };
    auto callback = [weakPattern = WeakClaim(this)](int32_t start) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->AddSectionChangeStartPos(start);
    };
    sections_->SetOnDataChange(callback);
    sections_->SetNotifySectionChange(sectionChangeCallback);
    return sections_;
}

void WaterFlowPattern::OnSectionChanged(int32_t start)
{
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW && keepContentPosition_) {
        layoutInfo_->InitSegmentsForKeepPositionMode(
            sections_->GetSectionInfo(), sections_->GetPrevSectionInfo(), start);
    } else {
        layoutInfo_->InitSegments(sections_->GetSectionInfo(), start);
    }
}

void WaterFlowPattern::ResetSections()
{
    if (!sections_) {
        return;
    }
    sections_.Reset();
    layoutInfo_->Reset();
    sectionChangeStartPos_.clear();
    MarkDirtyNodeSelf();
}

void WaterFlowPattern::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset)
{
    SetScrollSource(SCROLL_FROM_JUMP);
    SetScrollAlign(align);
    StopAnimate();
    auto footer = footer_.Upgrade();
    const int32_t itemCnt = footer ? GetChildrenCount() - footer->FrameCount() : GetChildrenCount();
    if (index > WaterFlowLayoutInfoBase::EMPTY_JUMP_INDEX && index < itemCnt) {
        if (smooth) {
            SetExtraOffset(extraOffset);
            if (!ScrollToTargetIndex(index)) {
                targetIndex_ = index;
                layoutInfo_->duringPositionCalc_ = true;
                auto host = GetHost();
                CHECK_NULL_VOID(host);
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            }
        } else {
            UpdateStartIndex(index);
            layoutInfo_->duringPositionCalc_ = true;
            if (extraOffset.has_value()) {
                layoutInfo_->extraOffset_ = -extraOffset.value();
            }
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
    if (AnimateStoped()) {
        scrollStop_ = true;
    }
    CheckMisalignment(layoutInfo_);
    MarkDirtyNodeSelf();
}

void WaterFlowPattern::OnAnimateStop()
{
    if (!GetIsDragging() || GetScrollAbort()) {
        scrollStop_ = true;
    }
    CheckMisalignment(layoutInfo_);
    MarkDirtyNodeSelf();
}

void WaterFlowPattern::AnimateTo(
    float position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll, bool useTotalOffset)
{
    ScrollablePattern::AnimateTo(position, duration, curve, smooth, canOverScroll);
}

void WaterFlowPattern::ScrollTo(float position)
{
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
    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, needRender);
    needRender |= paintProperty->GetFadingEdge().value_or(false);
    needRender |= paintProperty->GetContentClip().has_value();
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
    if (prevFooter != footer) {
        if (!prevFooter) {
            host->AddChild(footer, 0);
            layoutInfo_->footerIndex_ = 0;
        } else if (!footer) {
            host->RemoveChild(prevFooter);
        } else {
            host->ReplaceChild(prevFooter, footer);
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    footer_ = footer;
    if (footer) {
        footer->SetActive(false);
    }
}

void WaterFlowPattern::SetLayoutMode(LayoutMode mode)
{
    if (!layoutInfo_ || mode != layoutInfo_->Mode()) {
        layoutInfo_ = WaterFlowLayoutInfoBase::Create(mode);
        MarkDirtyNodeSelf();
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

void WaterFlowPattern::NotifyDataChange(int32_t index, int32_t count)
{
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW && keepContentPosition_) {
        auto footer = footer_.Upgrade();
        if (footer && footer->FrameCount() > 0) {
            layoutInfo_->NotifyDataChange(index - 1, count);
        } else {
            layoutInfo_->NotifyDataChange(index, count);
        }
    }
}

ScopeFocusAlgorithm WaterFlowPattern::GetScopeFocusAlgorithm()
{
    return { layoutInfo_->axis_ == Axis::VERTICAL, true, ScopeType::OTHERS,
        [wp = WeakClaim(this)](
            FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) -> bool {
            auto self = wp.Upgrade();
            if (self) {
                nextFocusNode = self->GetNextFocusNode(step, currFocusNode);
            }
            return nextFocusNode.Upgrade() != currFocusNode.Upgrade();
        } };
}

WeakPtr<FocusHub> WaterFlowPattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    auto cur = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(cur, nullptr);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    int32_t curIdx = host->GetChildTrueIndex(cur->GetFrameNode());
    int32_t diff = 0;
    switch (step) {
        case FocusStep::DOWN:
        case FocusStep::DOWN_END:
        case FocusStep::RIGHT:
        case FocusStep::RIGHT_END:
        case FocusStep::TAB:
            diff = 1;
            break;
        case FocusStep::LEFT:
        case FocusStep::LEFT_END:
        case FocusStep::UP:
        case FocusStep::UP_END:
        case FocusStep::SHIFT_TAB:
            diff = -1;
            break;
        default:
            return currentFocusNode;
    }
    int32_t idx = curIdx + diff;
    int32_t footerOffset = layoutInfo_->footerIndex_ + 1; // 1 if footer present, 0 if not
    while (idx - footerOffset >= 0 && idx < GetChildrenCount()) {
        int32_t itemIdx = idx - footerOffset;
        if (itemIdx >= layoutInfo_->endIndex_ || itemIdx <= layoutInfo_->startIndex_) {
            ScrollToIndex(itemIdx, false, ScrollAlign::AUTO);
            host->SetActive();
            auto context = host->GetContext();
            if (context) {
                context->FlushUITaskWithSingleDirtyNode(host);
            }
        }
        auto next = host->GetChildByIndex(idx);
        CHECK_NULL_RETURN(next, nullptr);
        auto focus = next->GetHostNode()->GetFocusHub();
        if (focus && focus->IsFocusable()) {
            return focus;
        }
        idx += diff;
    }
    return nullptr;
}

std::function<bool(int32_t)> WaterFlowPattern::GetScrollIndexAbility()
{
    return [wp = WeakClaim(this)](int32_t index) -> bool {
        auto self = wp.Upgrade();
        CHECK_NULL_RETURN(self, false);
        if (index == FocusHub::SCROLL_TO_HEAD) {
            self->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
        } else if (index == FocusHub::SCROLL_TO_TAIL) {
            self->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
        } else {
            self->ScrollToIndex(index, false, ScrollAlign::AUTO);
        }
        return true;
    };
}

void WaterFlowPattern::DumpAdvanceInfo()
{
    auto property = GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(property);
    ScrollablePattern::DumpAdvanceInfo();
    if (layoutInfo_->Mode() == LayoutMode::SLIDING_WINDOW) {
        auto info = DynamicCast<WaterFlowLayoutInfoSW>(layoutInfo_);
        CHECK_NULL_VOID(info);
        DumpLog::GetInstance().AddDesc("footerHeight:" + std::to_string(info->footerHeight_));
    } else {
        auto info = DynamicCast<WaterFlowLayoutInfo>(layoutInfo_);
        CHECK_NULL_VOID(info);
        DumpLog::GetInstance().AddDesc("childrenCount:" + std::to_string(info->childrenCount_));
    }
    std::vector<std::string> scrollAlign = { "START", "CENTER", "END", "AUTO", "NONE" };

    DumpLog::GetInstance().AddDesc("offset:" + std::to_string(layoutInfo_->Offset()));
    DumpLog::GetInstance().AddDesc("prevOffset:" + std::to_string(prevOffset_));
    DumpLog::GetInstance().AddDesc("lastMainSize:" + std::to_string(layoutInfo_->lastMainSize_));
    DumpLog::GetInstance().AddDesc("maxHeight:" + std::to_string(layoutInfo_->GetContentHeight()));
    DumpLog::GetInstance().AddDesc("startIndex:" + std::to_string(layoutInfo_->startIndex_));
    DumpLog::GetInstance().AddDesc("endIndex:" + std::to_string(layoutInfo_->endIndex_));
    DumpLog::GetInstance().AddDesc("jumpIndex:" + std::to_string(layoutInfo_->jumpIndex_));

    DumpLog::GetInstance().AddDesc("RowsTemplate:", property->GetRowsTemplate()->c_str());
    DumpLog::GetInstance().AddDesc("ColumnsTemplate:", property->GetColumnsTemplate()->c_str());
    DumpLog::GetInstance().AddDesc(
        "CachedCount:" + std::to_string(property->GetCachedCount().value_or(layoutInfo_->defCachedCount_)));
    DumpLog::GetInstance().AddDesc("ScrollAlign:" + scrollAlign[static_cast<int32_t>(layoutInfo_->align_)]);

    property->IsReverse() ? DumpLog::GetInstance().AddDesc("isReverse:true")
                          : DumpLog::GetInstance().AddDesc("isReverse:false");
    layoutInfo_->itemStart_ ? DumpLog::GetInstance().AddDesc("itemStart:true")
                            : DumpLog::GetInstance().AddDesc("itemStart:false");
    layoutInfo_->itemEnd_ ? DumpLog::GetInstance().AddDesc("itemEnd:true")
                          : DumpLog::GetInstance().AddDesc("itemEnd:false");
    layoutInfo_->offsetEnd_ ? DumpLog::GetInstance().AddDesc("offsetEnd:true")
                            : DumpLog::GetInstance().AddDesc("offsetEnd:false");
    footer_.Upgrade() ? DumpLog::GetInstance().AddDesc("footer:true") : DumpLog::GetInstance().AddDesc("footer:false");

    property->GetItemMinSize().has_value()
        ? DumpLog::GetInstance().AddDesc("ItemMinSize:" + property->GetItemMinSize().value().ToString())
        : DumpLog::GetInstance().AddDesc("ItemMinSize:null");
    property->GetItemMaxSize().has_value()
        ? DumpLog::GetInstance().AddDesc("ItemMaxSize:" + property->GetItemMaxSize().value().ToString())
        : DumpLog::GetInstance().AddDesc("ItemMaxSize:null");
    layoutInfo_->Mode() == LayoutMode::TOP_DOWN ? DumpLog::GetInstance().AddDesc("Mode:TOP_DOWN")
                                                : DumpLog::GetInstance().AddDesc("Mode:SLIDING_WINDOW");

    if (sections_) {
        DumpInfoAddSections();
    }
}

void WaterFlowPattern::GetEventDumpInfo()
{
    ScrollablePattern::GetEventDumpInfo();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetOrCreateEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(hub);
    auto onScrollIndex = hub->GetOnScrollIndex();
    onScrollIndex ? DumpLog::GetInstance().AddDesc("hasOnScrollIndex: true")
                  : DumpLog::GetInstance().AddDesc("hasOnScrollIndex: false");
    auto onJSFrameNodeScrollIndex = hub->GetJSFrameNodeOnWaterFlowScrollIndex();
    onJSFrameNodeScrollIndex ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollIndex: true")
                             : DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollIndex: false");
}

void WaterFlowPattern::GetEventDumpInfo(std::unique_ptr<JsonValue>& json)
{
    ScrollablePattern::GetEventDumpInfo(json);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetOrCreateEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(hub);
    auto onScrollIndex = hub->GetOnScrollIndex();
    json->Put("hasOnScrollIndex", onScrollIndex ? "true" : "false");
    auto onJSFrameNodeScrollIndex = hub->GetJSFrameNodeOnWaterFlowScrollIndex();
    json->Put("hasFrameNodeOnScrollIndex", onJSFrameNodeScrollIndex ? "true" : "false");
}

void WaterFlowPattern::DumpInfoAddSections()
{
    DumpLog::GetInstance().AddDesc("-----------start print sections_------------");
    std::string res = std::string("");
    int32_t index = 0;
    for (const auto& section : sections_->GetSectionInfo()) {
        res.append("[section:" + std::to_string(index) + "]");
        res.append("{ itemCount:" + std::to_string(section.itemsCount) + " },")
            .append("{ crossCount:" + std::to_string(section.crossCount.value_or(1)) + " },")
            .append("{ columnsGap:" + section.columnsGap.value_or(Dimension(0.0)).ToString() + " },")
            .append("{ rowsGap:" + section.rowsGap.value_or(Dimension(0.0)).ToString() + " },")
            .append("{ margin:[" + section.margin.value_or(MarginProperty()).ToString() + " ]}");
        DumpLog::GetInstance().AddDesc(res);
        res.clear();
        index++;
    }
    DumpLog::GetInstance().AddDesc("-----------end print sections_------------");
}

SizeF WaterFlowPattern::GetChildrenExpandedSize()
{
    auto viewSize = GetViewSizeMinusPadding();
    auto axis = GetAxis();
    const float estimatedHeight = layoutInfo_->EstimateTotalHeight();

    if (axis == Axis::VERTICAL) {
        return {viewSize.Width(), estimatedHeight};
    }
    if (axis == Axis::HORIZONTAL) {
        return {estimatedHeight, viewSize.Height()};
    }
    return {};
}
} // namespace OHOS::Ace::NG