/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/list/list_pattern.h"
#include <cstdint>
#include <optional>
#include <unistd.h>

#include "base/geometry/rect.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/list/list_theme.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/base/distributed_ui.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/list/list_height_offset_calculator.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension CHAIN_INTERVAL_DEFAULT = 20.0_vp;
constexpr double CHAIN_SPRING_MASS = 1.0;
constexpr double CHAIN_SPRING_DAMPING = 30.0;
constexpr double CHAIN_SPRING_STIFFNESS = 228;
constexpr float DEFAULT_MIN_SPACE_SCALE = 0.75f;
constexpr float DEFAULT_MAX_SPACE_SCALE = 2.0f;
constexpr int DEFAULT_HEADER_VALUE = 2;
constexpr int DEFAULT_FOOTER_VALUE = 3;
#ifdef SUPPORT_DIGITAL_CROWN
constexpr const char* HAPTIC_STRENGTH1 = "watchhaptic.feedback.crown.strength3";
#endif
} // namespace

void ListPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listLayoutProperty);
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    if (axis != GetAxis()) {
        needReEstimateOffset_ = true;
        SetAxis(axis);
        ChangeAxis(GetHost());
    }
    if (!GetScrollableEvent()) {
        AddScrollEvent();
        auto scrollableEvent = GetScrollableEvent();
        CHECK_NULL_VOID(scrollableEvent);
        scrollable_ = scrollableEvent->GetScrollable();
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

    SetChainAnimation();
    if (multiSelectable_ && !isMouseEventInit_) {
        InitMouseEvent();
    }
    if (!multiSelectable_ && isMouseEventInit_) {
        UninitMouseEvent();
    }
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
    Register2DragDropManager();
    SetAccessibilityAction();
    auto fadingEdge = GetFadingEdge(paintProperty);
    auto overlayNode = host->GetOverlayNode();
    if (!overlayNode && fadingEdge) {
        CreateAnalyzerOverlay(host);
    }
}

bool ListPattern::GetFadingEdge(RefPtr<ScrollablePaintProperty>& paintProperty)
{
    auto defaultFadingEdge = false;
    if (!paintProperty->HasDefaultFadingEdge()) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto context = host->GetContextRefPtr();
        CHECK_NULL_RETURN(context, false);
        auto listTheme = context->GetTheme<ListTheme>();
        CHECK_NULL_RETURN(listTheme, false);
        defaultFadingEdge = GetAxis() == Axis::VERTICAL ? listTheme->GetFadingEdge()
                                                        : false;
        paintProperty->UpdateDefaultFadingEdge(defaultFadingEdge);
    } else {
        defaultFadingEdge = paintProperty->GetDefaultFadingEdge().value_or(false);
    }
    auto fadingEdge = paintProperty->GetFadingEdge().value_or(defaultFadingEdge);
    return fadingEdge;
}

void ListPattern::ChangeAxis(RefPtr<UINode> node)
{
    CHECK_NULL_VOID(node);
    auto children = node->GetChildren();
    for (const auto& child : children) {
        if (AceType::InstanceOf<FrameNode>(child)) {
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(frameNode);
            auto listItemPattern = frameNode->GetPattern<ListItemPattern>();
            if (listItemPattern) {
                listItemPattern->ChangeAxis(GetAxis());
                continue;
            }
            auto listItemGroupPattern = frameNode->GetPattern<ListItemGroupPattern>();
            if (listItemGroupPattern) {
                listItemGroupPattern->ResetLayoutedInfo();
                frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
                ChangeAxis(child);
            }
        } else {
            ChangeAxis(child);
        }
    }
}

bool ListPattern::HandleTargetIndex(bool isJump)
{
    if (isJump) {
        MarkDirtyNodeSelf();
        return true;
    }
    auto iter = itemPosition_.find(targetIndex_.value());
    if (iter == itemPosition_.end()) {
        ResetExtraOffset();
    } else if (!isLayoutListForFocus_) {
        // isLayoutListForFocus_ is true means only do Layout and do NOT call AnimateToTarget.
        AnimateToTarget(targetIndex_.value(), targetIndexInGroup_, scrollAlign_);
    }

    // AniamteToTarget does not need to update endIndex and startIndex in the first frame.
    targetIndex_.reset();
    targetIndexInGroup_.reset();
    isLayoutListForFocus_.reset();
    return false;
}

bool ListPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto listLayoutAlgorithm = DynamicCast<ListLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(listLayoutAlgorithm, false);
    itemPosition_ = listLayoutAlgorithm->GetItemPosition();
    cachedItemPosition_ = listLayoutAlgorithm->GetCachedItemPosition();
    laneIdx4Divider_ = listLayoutAlgorithm->GetLaneIdx4Divider();
    maxListItemIndex_ = listLayoutAlgorithm->GetMaxListItemIndex();
    spaceWidth_ = listLayoutAlgorithm->GetSpaceWidth();
    auto predictSnapOffset = listLayoutAlgorithm->GetPredictSnapOffset();
    auto predictSnapEndPos = listLayoutAlgorithm->GetPredictSnapEndPosition();
    bool isJump = listLayoutAlgorithm->NeedEstimateOffset();
    auto lanesLayoutAlgorithm = DynamicCast<ListLanesLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    isStackFromEnd_ = listLayoutAlgorithm->GetStackFromEnd();
    if (lanesLayoutAlgorithm) {
        lanesLayoutAlgorithm->SwapLanesItemRange(lanesItemRange_);
        if (lanesLayoutAlgorithm->GetLanes() != lanes_) {
            needReEstimateOffset_ = true;
            auto item = swiperItem_.Upgrade();
            if (item) {
                item->ResetSwipeStatus();
            }
        }
        lanes_ = lanesLayoutAlgorithm->GetLanes();
        laneGutter_ = lanesLayoutAlgorithm->GetLaneGutter();
    } else {
        lanes_ = listLayoutAlgorithm->GetLanes();
    }
    float relativeOffset = UpdateTotalOffset(listLayoutAlgorithm, isJump);
    bool isNeedUpdateIndex = targetIndex_ ? HandleTargetIndex(isJump) : true;
    if (predictSnapOffset.has_value()) {
        if (scrollable_ && !(NearZero(predictSnapOffset.value()) && NearZero(scrollSnapVelocity_)) &&
            (!AnimateRunning() || lastSnapTargetIndex_.has_value())) {
            StartListSnapAnimation(predictSnapOffset.value(), scrollSnapVelocity_);
            if (snapTrigOnScrollStart_) {
                FireOnScrollStart();
            } else {
                scrollStop_ = false;
            }
        } else if (!snapTrigOnScrollStart_) {
            OnAnimateStop();
        }
        scrollSnapVelocity_ = 0.0f;
        predictSnapOffset_.reset();
        ResetLastSnapTargetIndex();
        snapTrigOnScrollStart_ = false;
    }
    if (predictSnapEndPos.has_value() && predictSnapEndPos_.has_value() &&
        !NearEqual(predictSnapEndPos.value(), predictSnapEndPos_.value())) {
        if (scrollable_) {
            scrollable_->UpdateScrollSnapEndWithOffset(predictSnapEndPos.value() - predictSnapEndPos_.value());
        }
    }
    predictSnapEndPos_ = predictSnapEndPos;

    if (isScrollEnd_) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        // AccessibilityEventType::SCROLL_END
        isScrollEnd_ = false;
    }
    currentDelta_ = 0.0f;
    isNeedCheckOffset_ = false;
    prevStartOffset_ = startMainPos_;
    prevEndOffset_ = endMainPos_ - contentMainSize_ + contentEndOffset_;
    contentMainSize_ = listLayoutAlgorithm->GetContentMainSize();
    contentStartOffset_ = listLayoutAlgorithm->GetContentStartOffset();
    contentEndOffset_ = listLayoutAlgorithm->GetContentEndOffset();
    startMainPos_ = listLayoutAlgorithm->GetStartPosition();
    endMainPos_ = listLayoutAlgorithm->GetEndPosition();
    crossMatchChild_ = listLayoutAlgorithm->IsCrossMatchChild();
    auto endOffset = endMainPos_ - contentMainSize_ + contentEndOffset_;
    CheckScrollable();
    if (centerIndex_ != listLayoutAlgorithm->GetMidIndex(AceType::RawPtr(dirty))) {
        OnMidIndexChanged();
    }
    bool indexChanged = false;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (isNeedUpdateIndex) {
            indexChanged = (startIndex_ != listLayoutAlgorithm->GetStartIndex()) ||
                           (endIndex_ != listLayoutAlgorithm->GetEndIndex()) ||
                           (centerIndex_ != listLayoutAlgorithm->GetMidIndex(AceType::RawPtr(dirty)));
        }
    } else {
        indexChanged =
            (startIndex_ != listLayoutAlgorithm->GetStartIndex()) || (endIndex_ != listLayoutAlgorithm->GetEndIndex());
    }
    startIndexChanged_ = startIndex_ != listLayoutAlgorithm->GetStartIndex();
    endIndexChanged_ = endIndex_ != listLayoutAlgorithm->GetEndIndex();
    if (indexChanged) {
        startIndex_ = listLayoutAlgorithm->GetStartIndex();
        endIndex_ = listLayoutAlgorithm->GetEndIndex();
        centerIndex_ = listLayoutAlgorithm->GetMidIndex(AceType::RawPtr(dirty));
    }
    ProcessEvent(indexChanged, relativeOffset, isJump);
    HandleScrollBarOutBoundary();
    UpdateScrollBarOffset();
    if (config.frameSizeChange) {
        if (GetScrollBar() != nullptr) {
            GetScrollBar()->ScheduleDisappearDelayTask();
        }
    }
    bool sizeDiminished =
        !chainAnimation_ && IsOutOfBoundary(false) && (endOffset + relativeOffset - prevEndOffset_ < -0.1f);
    CheckRestartSpring(sizeDiminished);

    DrivenRender(dirty);

    SetScrollSource(SCROLL_FROM_NONE);
    isInitialized_ = true;
    MarkSelectedItems();
    UpdateListDirectionInCardStyle();
    snapTrigByScrollBar_ = false;
    return true;
}

void ListPattern::UpdateListDirectionInCardStyle()
{
    if (isNeedToUpdateListDirection_) {
        auto layoutProperty = GetLayoutProperty<ListLayoutProperty>();
        layoutProperty->UpdateListDirection(Axis::VERTICAL);
        isNeedToUpdateListDirection_ = false;
    }
}

ScrollAlign ListPattern::GetInitialScrollAlign() const
{
    auto snapAlign = GetScrollSnapAlign();
    if (snapAlign == ScrollSnapAlign::CENTER) {
        return ScrollAlign::CENTER;
    } else if (isStackFromEnd_ && snapAlign == ScrollSnapAlign::START) {
        return ScrollAlign::END;
    }
    return ScrollAlign::START;
}

float ListPattern::CalculateTargetPos(float startPos, float endPos)
{
    float topOffset = startPos;
    float bottomOffset = endPos - contentMainSize_;
    if (!IsScrollSnapAlignCenter()) {
        topOffset -= contentStartOffset_;
        bottomOffset += contentEndOffset_;
    }
    if (GreatOrEqual(topOffset, 0.0f) && LessOrEqual(bottomOffset, 0.0f)) {
        return 0.0f;
    }
    if ((NearEqual(topOffset, 0.0f) && GreatNotEqual(bottomOffset, 0.0f)) ||
        (LessNotEqual(topOffset, 0.0f) && NearEqual(bottomOffset, 0.0f))) {
        return 0.0f;
    }
    if (LessNotEqual(topOffset, 0.0f) && GreatNotEqual(bottomOffset, 0.0f)) {
        if (GreatOrEqual(std::abs(topOffset), std::abs(bottomOffset))) {
            return bottomOffset;
        } else {
            return topOffset;
        }
    }
    if (GreatNotEqual(std::abs(topOffset), std::abs(bottomOffset))) {
        return bottomOffset;
    } else if (LessNotEqual(std::abs(topOffset), std::abs(bottomOffset))) {
        return topOffset;
    } else {
        if (LessNotEqual(topOffset, 0.0f)) {
            return topOffset;
        } else {
            return bottomOffset;
        }
    }
    return 0.0f;
}

RefPtr<NodePaintMethod> ListPattern::CreateNodePaintMethod()
{
    auto listLayoutProperty = GetLayoutProperty<ListLayoutProperty>();
    V2::ItemDivider divider;
    if (!chainAnimation_ && listLayoutProperty->HasDivider()) {
        divider = listLayoutProperty->GetDivider().value();
    }
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    auto layoutDirection = listLayoutProperty->GetNonAutoLayoutDirection();
    auto drawVertical = (axis == Axis::HORIZONTAL);
    auto drawDirection = (layoutDirection == TextDirection::RTL);
    auto paint = MakeRefPtr<ListPaintMethod>(divider, drawVertical, drawDirection, lanes_, spaceWidth_);
    if (drawDirection) {
        paint->SetDirection(true);
    }
    paint->SetScrollBar(GetScrollBar());
    paint->SetScrollBarOverlayModifier(GetScrollBarOverlayModifier());
    paint->SetTotalItemCount(maxListItemIndex_ + 1);
    auto scrollEffect = GetScrollEdgeEffect();
    if (scrollEffect && scrollEffect->IsFadeEffect()) {
        paint->SetEdgeEffect(scrollEffect);
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, paint);
    const auto& geometryNode = host->GetGeometryNode();
    auto renderContext = host->GetRenderContext();
    if (!listContentModifier_) {
        CHECK_NULL_RETURN(renderContext, paint);
        auto size = renderContext->GetPaintRectWithoutTransform().GetSize();
        auto& padding = geometryNode->GetPadding();
        if (padding) {
            size.MinusPadding(*padding->left, *padding->right, *padding->top, *padding->bottom);
        }
        OffsetF offset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset();
        listContentModifier_ = AceType::MakeRefPtr<ListContentModifier>(offset, size);
    }
    listContentModifier_->SetIsNeedDividerAnimation(isNeedDividerAnimation_);
    paint->SetLaneGutter(laneGutter_);
    bool showCached = listLayoutProperty->GetShowCachedItemsValue(false);
    bool clip = !renderContext || renderContext->GetClipEdge().value_or(true);
    paint->SetItemsPosition(itemPosition_, cachedItemPosition_, pressedItem_, showCached, clip);
    paint->SetLaneIdx(laneIdx4Divider_);
    paint->SetContentModifier(listContentModifier_);
    paint->SetAdjustOffset(geometryNode->GetParentAdjust().GetOffset().GetY());
    UpdateFadingEdge(paint);
    return paint;
}

bool ListPattern::UpdateStartListItemIndex()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    CHECK_EQUAL_RETURN(host->GetChildTrueTotalCount(), 0, false);
    auto startWrapper = host->GetOrCreateChildByIndex(startIndex_);
    int32_t startArea = -1;
    int32_t startItemIndexInGroup = -1;
    bool startFlagChanged = (startInfo_.index != startIndex_);
    bool startIsGroup = startWrapper && startWrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (startIsGroup) {
        auto startPattern = startWrapper->GetHostNode()->GetPattern<ListItemGroupPattern>();
        VisibleContentInfo startGroupInfo = startPattern->GetStartListItemIndex();
        startFlagChanged = startFlagChanged || (startInfo_.area != startGroupInfo.area) ||
                           (startInfo_.indexInGroup != startGroupInfo.indexInGroup);
        startArea = startGroupInfo.area;
        startItemIndexInGroup = startGroupInfo.indexInGroup;
        if (startFlagChanged) {
            VisibleContentInfo endGroupInfo = startPattern->GetEndListItemIndex();
            int32_t endItemIndexInGroup = endGroupInfo.indexInGroup;
            startWrapper->GetHostNode()->OnAccessibilityEvent(
                AccessibilityEventType::SCROLLING_EVENT, startItemIndexInGroup, endItemIndexInGroup);
        }
    }
    startInfo_ = { startIndex_, startArea, startItemIndexInGroup };
    return startFlagChanged;
}

bool ListPattern::UpdateEndListItemIndex()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    CHECK_EQUAL_RETURN(host->GetChildTrueTotalCount(), 0, false);
    auto endWrapper = host->GetOrCreateChildByIndex(endIndex_);
    int32_t endArea = -1;
    int32_t endItemIndexInGroup = -1;
    bool endFlagChanged = (endInfo_.index != endIndex_);
    bool endIsGroup = endWrapper && endWrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
    if (endIsGroup) {
        auto endPattern = endWrapper->GetHostNode()->GetPattern<ListItemGroupPattern>();
        VisibleContentInfo endGroupInfo = endPattern->GetEndListItemIndex();
        endFlagChanged = endFlagChanged || (endInfo_.area != endGroupInfo.area) ||
                         (endInfo_.indexInGroup != endGroupInfo.indexInGroup);
        endArea = endGroupInfo.area;
        endItemIndexInGroup = endGroupInfo.indexInGroup;
        if (endFlagChanged) {
            VisibleContentInfo startGroupInfo = endPattern->GetStartListItemIndex();
            int32_t startItemIndexInGroup = startGroupInfo.indexInGroup;
            endWrapper->GetHostNode()->OnAccessibilityEvent(
                AccessibilityEventType::SCROLLING_EVENT, startItemIndexInGroup, endItemIndexInGroup);
        }
    }
    endInfo_ = { endIndex_, endArea, endItemIndexInGroup };
    return endFlagChanged;
}

void ListPattern::ProcessEvent(bool indexChanged, float finalOffset, bool isJump)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listEventHub = host->GetOrCreateEventHub<ListEventHub>();
    CHECK_NULL_VOID(listEventHub);
    paintStateFlag_ = !NearZero(finalOffset) && !isJump;
    isFramePaintStateValid_ = true;
    auto onScroll = listEventHub->GetOnScroll();
    PrintOffsetLog(AceLogTag::ACE_LIST, host->GetId(), finalOffset);
    if (onScroll) {
        FireOnScrollWithVersionCheck(finalOffset, onScroll);
    }
    FireObserverOnDidScroll(finalOffset);
    auto onDidScroll = listEventHub->GetOnDidScroll();
    if (onDidScroll) {
        FireOnScroll(finalOffset, onDidScroll);
    }
    auto onJSFrameNodeDidScroll = listEventHub->GetJSFrameNodeOnDidScroll();
    if (onJSFrameNodeDidScroll) {
        FireOnScroll(finalOffset, onJSFrameNodeDidScroll);
    }
    auto onScrollIndex = listEventHub->GetOnScrollIndex();
    auto onJSFrameNodeScrollIndex = listEventHub->GetJSFrameNodeOnListScrollIndex();
    FireOnScrollIndex(indexChanged, onScrollIndex);
    FireOnScrollIndex(indexChanged, onJSFrameNodeScrollIndex);
    if (startIndexChanged_ || endIndexChanged_) {
        host->OnAccessibilityEvent(AccessibilityEventType::SCROLLING_EVENT, startIndex_, endIndex_);
    }
    OnScrollVisibleContentChange(listEventHub, indexChanged);
    auto onReachStart = listEventHub->GetOnReachStart();
    auto onJSFrameNodeReachStart = listEventHub->GetJSFrameNodeOnReachStart();
    FireOnReachStart(onReachStart, onJSFrameNodeReachStart);
    auto onReachEnd = listEventHub->GetOnReachEnd();
    auto onJSFrameNodeReachEnd = listEventHub->GetJSFrameNodeOnReachEnd();
    FireOnReachEnd(onReachEnd, onJSFrameNodeReachEnd);
    OnScrollStop(listEventHub->GetOnScrollStop(), listEventHub->GetJSFrameNodeOnScrollStop());
}

void ListPattern::FireOnScrollWithVersionCheck(float finalOffset, OnScrollEvent& onScroll)
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        FireOnScroll(finalOffset, onScroll);
    } else {
        if (!NearZero(finalOffset)) {
            auto offsetPX = Dimension(finalOffset);
            auto offsetVP = Dimension(offsetPX.ConvertToVp(), DimensionUnit::VP);
            auto source = GetScrollSource();
            if (source == SCROLL_FROM_AXIS || source == SCROLL_FROM_BAR || source == SCROLL_FROM_ANIMATION_CONTROLLER) {
                source = SCROLL_FROM_NONE;
            }
            onScroll(offsetVP, GetScrollState(source));
        }
    }
}

void ListPattern::FireOnReachStart(const OnReachEvent& onReachStart, const OnReachEvent& onJSFrameNodeReachStart)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (startIndex_ == 0) {
        bool scrollUpToStart =
            GreatNotEqual(prevStartOffset_, contentStartOffset_) && LessOrEqual(startMainPos_, contentStartOffset_);
        bool scrollDownToStart =
            (startIndexChanged_ || LessNotEqual(prevStartOffset_, contentStartOffset_) || !isInitialized_) &&
            GreatOrEqual(startMainPos_, contentStartOffset_);
        if (scrollUpToStart || scrollDownToStart) {
            FireObserverOnReachStart();
            ReportOnItemListEvent("onReachStart");
            CHECK_NULL_VOID(onReachStart || onJSFrameNodeReachStart);
            ACE_SCOPED_TRACE("OnReachStart, scrollUpToStart:%u, scrollDownToStart:%u, id:%d, tag:List",
                scrollUpToStart, scrollDownToStart, static_cast<int32_t>(host->GetAccessibilityId()));
            if (onReachStart) {
                onReachStart();
            }
            if (onJSFrameNodeReachStart) {
                onJSFrameNodeReachStart();
            }
            AddEventsFiredInfo(ScrollableEventType::ON_REACH_START);
        }
    }
}

void ListPattern::FireOnReachEnd(const OnReachEvent& onReachEnd, const OnReachEvent& onJSFrameNodeReachEnd)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (endIndex_ == GetMaxIndexByRepeat()) {
        float endOffset = endMainPos_ - contentMainSize_ + contentEndOffset_;
        // deltaOffset passes through multiple items also needs to fire reachEnd
        bool scrollUpToEnd =
            (endIndexChanged_ || (Positive(prevEndOffset_) || !isInitialized_)) && NonPositive(endOffset);
        bool scrollDownToEnd = Negative(prevEndOffset_) && NonNegative(endOffset);
        auto scrollSource = GetScrollSource();
        if (scrollUpToEnd || (scrollDownToEnd && scrollSource != SCROLL_FROM_NONE)) {
            FireObserverOnReachEnd();
            ReportOnItemListEvent("onReachEnd");
            CHECK_NULL_VOID(onReachEnd || onJSFrameNodeReachEnd);
            ACE_SCOPED_TRACE("OnReachEnd, scrollUpToEnd:%u, scrollDownToEnd:%u, scrollSource:%d, id:%d, tag:List",
                scrollUpToEnd, scrollDownToEnd, scrollSource, static_cast<int32_t>(host->GetAccessibilityId()));
            if (onReachEnd) {
                onReachEnd();
            }
            if (onJSFrameNodeReachEnd) {
                onJSFrameNodeReachEnd();
            }
            AddEventsFiredInfo(ScrollableEventType::ON_REACH_END);
        }
    }
}

void ListPattern::FireOnScrollIndex(bool indexChanged, const OnScrollIndexEvent& onScrollIndex)
{
    CHECK_NULL_VOID(indexChanged && onScrollIndex);
    int32_t startIndex = startIndex_ == -1 ? 0 : startIndex_;
    int32_t endIndex = endIndex_ == -1 ? 0 : endIndex_;
    onScrollIndex(startIndex, endIndex, centerIndex_);
    ReportOnItemListScrollEvent("onScrollIndex", startIndex, endIndex);
}

void ListPattern::DrivenRender(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    auto listPaintProperty = host->GetPaintProperty<ScrollablePaintProperty>();
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    auto stickyStyle = listLayoutProperty->GetStickyStyle().value_or(V2::StickyStyle::NONE);
    bool barNeedPaint = GetScrollBar() ? GetScrollBar()->NeedPaint() : false;
    auto chainAnimation = listLayoutProperty->GetChainAnimation().value_or(false);
    bool drivenRender = !(axis != Axis::VERTICAL || stickyStyle != V2::StickyStyle::NONE || barNeedPaint ||
                          chainAnimation || !isScrollable_);

    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->MarkDrivenRender(drivenRender);
    if (drivenRender && isFramePaintStateValid_) {
        // Mark items
        int32_t indexStep = 0;
        int32_t startIndex = itemPosition_.empty() ? 0 : itemPosition_.begin()->first;
        for (auto& pos : itemPosition_) {
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos.first + itemStartIndex_);
            CHECK_NULL_VOID(wrapper);
            auto itemHost = wrapper->GetHostNode();
            CHECK_NULL_VOID(itemHost);
            auto itemRenderContext = itemHost->GetRenderContext();
            CHECK_NULL_VOID(itemRenderContext);
            itemRenderContext->MarkDrivenRenderItemIndex(startIndex + indexStep);
            indexStep++;
        }
        renderContext->MarkDrivenRenderFramePaintState(paintStateFlag_);
        isFramePaintStateValid_ = false;
    }
}

void ListPattern::CheckScrollable()
{
    auto listProperty = GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listProperty);
    auto lastScrollable = isScrollable_;
    if (itemPosition_.empty()) {
        isScrollable_ = false;
    } else {
        if ((itemPosition_.begin()->first == 0) && (itemPosition_.rbegin()->first == maxListItemIndex_) &&
            !IsScrollSnapAlignCenter()) {
            isScrollable_ = GetAlwaysEnabled() || GreatNotEqual(endMainPos_ - startMainPos_,
                contentMainSize_ - contentStartOffset_ - contentEndOffset_);
        } else {
            isScrollable_ = true;
        }
    }
    if (chainAnimation_ && lastScrollable && !isScrollable_) {
        ACE_SCOPED_TRACE("Scrollable List changes to un-scrollable, reset chainAnimation");
        chainAnimation_.Reset();
    }
    if (!chainAnimation_ && !lastScrollable && isScrollable_) {
        SetChainAnimation();
    }
    SetScrollEnabled(isScrollable_);

    if (!listProperty->GetScrollEnabled().value_or(isScrollable_)) {
        SetScrollEnabled(false);
    }
}

RefPtr<LayoutAlgorithm> ListPattern::CreateLayoutAlgorithm()
{
    auto listLayoutProperty = GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listLayoutProperty, nullptr);
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm;
    if (listLayoutProperty->HasLanes() || listLayoutProperty->HasLaneMinLength() ||
        listLayoutProperty->HasLaneMaxLength()) {
        auto lanesLayoutAlgorithm = MakeRefPtr<ListLanesLayoutAlgorithm>();
        RefreshLanesItemRange();
        lanesLayoutAlgorithm->SwapLanesItemRange(lanesItemRange_);
        lanesLayoutAlgorithm->SetLanes(lanes_);
        listLayoutAlgorithm.Swap(lanesLayoutAlgorithm);
    } else {
        listLayoutAlgorithm.Swap(MakeRefPtr<ListLayoutAlgorithm>());
    }
    if (!posMap_) {
        posMap_ = MakeRefPtr<ListPositionMap>();
    }

    SetLayoutAlgorithmParams(listLayoutAlgorithm, listLayoutProperty);

    auto pipeline = GetContext();
    if (pipeline && pipeline->GetPixelRoundMode() == PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE) {
        listLayoutAlgorithm->SetIsRoundingMode();
    }
    return listLayoutAlgorithm;
}

void ListPattern::SetLayoutAlgorithmParams(
    const RefPtr<ListLayoutAlgorithm>& listLayoutAlgorithm, const RefPtr<ListLayoutProperty>& listLayoutProperty)
{
    CHECK_NULL_VOID(listLayoutAlgorithm);
    CHECK_NULL_VOID(listLayoutProperty);
    if (childrenSize_) {
        listLayoutAlgorithm->SetListChildrenMainSize(childrenSize_);
        listLayoutAlgorithm->SetListPositionMap(posMap_);
    }
    SetLayoutAlgorithmJumpAlign(listLayoutAlgorithm, listLayoutProperty);
    if (targetIndex_) {
        listLayoutAlgorithm->SetTargetIndex(targetIndex_.value());
        listLayoutAlgorithm->SetIndexAlignment(scrollAlign_);
    }
    if (jumpIndexInGroup_) {
        listLayoutAlgorithm->SetIndexInGroup(jumpIndexInGroup_.value());
        jumpIndexInGroup_.reset();
    }
    if (targetIndexInGroup_) {
        listLayoutAlgorithm->SetTargetIndexInGroup(targetIndexInGroup_.value());
    }
    SetLayoutAlgorithmSnapParam(listLayoutAlgorithm);
    listLayoutAlgorithm->SetCurrentDelta(currentDelta_);
    listLayoutAlgorithm->SetIsNeedCheckOffset(isNeedCheckOffset_);
    listLayoutAlgorithm->SetItemsPosition(itemPosition_);
    listLayoutAlgorithm->SetPrevContentMainSize(contentMainSize_);
    listLayoutAlgorithm->SetPrevContentStartOffset(contentStartOffset_);
    listLayoutAlgorithm->SetPrevContentEndOffset(contentEndOffset_);
    if (IsOutOfBoundary(false) && GetScrollSource() != SCROLL_FROM_AXIS) {
        listLayoutAlgorithm->SetOverScrollFeature();
    }
    listLayoutAlgorithm->SetIsSpringEffect(IsScrollableSpringEffect());
    listLayoutAlgorithm->SetCanOverScrollStart(CanOverScrollStart(GetScrollSource()) && IsAtTop());
    listLayoutAlgorithm->SetCanOverScrollEnd(CanOverScrollEnd(GetScrollSource()) && IsAtBottom(true));
    if (chainAnimation_ && GetEffectEdge() == EffectEdge::ALL) {
        SetChainAnimationLayoutAlgorithm(listLayoutAlgorithm, listLayoutProperty);
        SetChainAnimationToPosMap();
    }
}

void ListPattern::SetChainAnimationToPosMap()
{
    CHECK_NULL_VOID(posMap_);
    posMap_->SetChainOffsetCallback([weak = AceType::WeakClaim(this)](int32_t index) {
        auto list = weak.Upgrade();
        CHECK_NULL_RETURN(list, 0.0f);
        return list->GetChainDelta(index);
    });
}

void ListPattern::SetChainAnimationLayoutAlgorithm(
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm, const RefPtr<ListLayoutProperty>& listLayoutProperty)
{
    CHECK_NULL_VOID(listLayoutAlgorithm);
    CHECK_NULL_VOID(listLayoutProperty);
    listLayoutAlgorithm->SetChainOffsetCallback([weak = AceType::WeakClaim(this)](int32_t index) {
        auto list = weak.Upgrade();
        CHECK_NULL_RETURN(list, 0.0f);
        return list->GetChainDelta(index);
    });
    if (chainAnimation_ && chainAnimation_->HasSpaceDelta() && !itemPosition_.empty()) {
        auto res = GetOutBoundaryOffset(currentDelta_, false);
        if ((NearZero(res.start) || !CanOverScrollStart(GetScrollSource())) &&
            (NearZero(res.end) || !CanOverScrollEnd(GetScrollSource()))) {
            chainAnimation_->ResetSpaceDelta();
        }
    }
    if (!listLayoutProperty->GetSpace().has_value() && chainAnimation_) {
        float chainInterval = CHAIN_INTERVAL_DEFAULT.ConvertToPx();
        auto pipeline = GetContext();
        if (pipeline && pipeline->GetPixelRoundMode() == PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE) {
            chainInterval = Round(chainInterval);
        }
        listLayoutAlgorithm->SetChainInterval(chainInterval);
    }
}

void ListPattern::SetLayoutAlgorithmJumpAlign(
    const RefPtr<ListLayoutAlgorithm>& listLayoutAlgorithm, const RefPtr<ListLayoutProperty>& listLayoutProperty)
{
    CHECK_NULL_VOID(listLayoutAlgorithm);
    CHECK_NULL_VOID(listLayoutProperty);
    bool needUseInitialIndex = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN) ?
        !isInitialized_ && !jumpIndex_ : !isInitialized_;
    if (needUseInitialIndex) {
        isStackFromEnd_ = listLayoutProperty->GetStackFromEnd().value_or(false);
        int32_t defaultInitialIndex = isStackFromEnd_ ? ListLayoutAlgorithm::LAST_ITEM : 0;
        jumpIndex_ = listLayoutProperty->GetInitialIndex().value_or(defaultInitialIndex);
        if (NeedScrollSnapAlignEffect()) {
            scrollAlign_ = GetInitialScrollAlign();
        } else if (isStackFromEnd_) {
            scrollAlign_ = ScrollAlign::END;
        }
    }
    if (jumpIndex_) {
        listLayoutAlgorithm->SetIndex(jumpIndex_.value());
        listLayoutAlgorithm->SetIndexAlignment(scrollAlign_);
        jumpIndex_.reset();
    }
}

void ListPattern::SetLayoutAlgorithmSnapParam(const RefPtr<ListLayoutAlgorithm>& listLayoutAlgorithm)
{
    CHECK_NULL_VOID(listLayoutAlgorithm);
    if (predictSnapOffset_.has_value()) {
        listLayoutAlgorithm->SetPredictSnapOffset(predictSnapOffset_.value());
        listLayoutAlgorithm->SetScrollSnapVelocity(scrollSnapVelocity_);
    }
    listLayoutAlgorithm->SetTotalOffset(GetTotalOffset());
    if (scrollable_) {
        auto snapOffset = scrollable_->GetPredictSnapOffset();
        if (snapOffset) {
            predictSnapEndPos_ = GetTotalOffset() - snapOffset.value() + currentDelta_;
        } else {
            predictSnapEndPos_.reset();
        }
    }
    if (predictSnapEndPos_.has_value()) {
        listLayoutAlgorithm->SetPredictSnapEndPosition(predictSnapEndPos_.value());
    }
}

bool ListPattern::IsScrollSnapAlignCenter() const
{
    auto snapAlign = GetScrollSnapAlign();
    return snapAlign == ScrollSnapAlign::CENTER;
}

bool ListPattern::NeedScrollSnapAlignEffect() const
{
    auto snapAlign = GetScrollSnapAlign();
    return snapAlign != ScrollSnapAlign::NONE;
}

ScrollSnapAlign ListPattern::GetScrollSnapAlign() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, ScrollSnapAlign::NONE);
    auto listProperty = host->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listProperty, ScrollSnapAlign::NONE);
    return listProperty->GetScrollSnapAlign().value_or(ScrollSnapAlign::NONE);
}

bool ListPattern::IsAtTop() const
{
    bool groupAtStart = true;
    bool groupAtEnd = true;
    GetListItemGroupEdge(groupAtStart, groupAtEnd);
    int32_t startIndex = startIndex_;
    float startMainPos = startMainPos_;
    float endMainPos = endMainPos_;
    auto contentMainSize = contentMainSize_ - contentEndOffset_ - contentStartOffset_;
    if (GreatNotEqual(contentMainSize, endMainPos - startMainPos) && isStackFromEnd_) {
        startMainPos = endMainPos - contentMainSize;
    }
    return (startIndex == 0 && groupAtStart) &&
           NonNegative(startMainPos - currentDelta_ + GetChainDelta(0) - contentStartOffset_);
}

bool ListPattern::IsAtBottom(bool considerRepeat) const
{
    bool groupAtStart = true;
    bool groupAtEnd = true;
    GetListItemGroupEdge(groupAtStart, groupAtEnd);
    int32_t endIndex = endIndex_;
    float endMainPos = endMainPos_;
    float startMainPos = startMainPos_;
    auto contentMainSize = contentMainSize_ - contentEndOffset_ - contentStartOffset_;
    if (GreatNotEqual(contentMainSize, endMainPos - startMainPos) && !isStackFromEnd_) {
        endMainPos = startMainPos + contentMainSize;
    }
    auto maxListItemIndex = considerRepeat ? GetMaxIndexByRepeat() : maxListItemIndex_;
    return (endIndex == maxListItemIndex && groupAtEnd) &&
           LessOrEqual(endMainPos - currentDelta_ + GetChainDelta(endIndex), contentMainSize_ - contentEndOffset_);
}

void ListPattern::GetListItemGroupEdge(bool& groupAtStart, bool& groupAtEnd) const
{
    if (itemPosition_.empty()) {
        return;
    }
    if (startIndex_ == 0 && itemPosition_.begin()->second.isGroup) {
        auto& groupInfo = itemPosition_.begin()->second.groupInfo;
        groupAtStart = groupInfo && groupInfo.value().atStart;
    }
    if (endIndex_ == maxListItemIndex_ && itemPosition_.rbegin()->second.isGroup) {
        auto& groupInfo = itemPosition_.rbegin()->second.groupInfo;
        groupAtEnd = groupInfo && groupInfo.value().atEnd;
    }
}

float ListPattern::GetOffsetWithLimit(float offset) const
{
    auto currentOffset = GetTotalOffset() + contentStartOffset_;
    if (Positive(offset)) {
        return std::min(currentOffset, offset);
    } else if (Negative(offset)) {
        auto remainHeight = GetTotalHeight() - currentOffset;
        return std::max(offset, -remainHeight);
    }
    return 0;
}

OverScrollOffset ListPattern::GetOverScrollOffset(double delta) const
{
    OverScrollOffset offset = { 0, 0 };
    bool groupAtStart = true;
    bool groupAtEnd = true;
    GetListItemGroupEdge(groupAtStart, groupAtEnd);

    int32_t startIndex = startIndex_;
    float startMainPos = startMainPos_;
    int32_t endIndex = endIndex_;
    float endMainPos = endMainPos_;
    if (startIndex == 0 && groupAtStart) {
        offset.start = GetStartOverScrollOffset(delta, startMainPos);
    }
    if (endIndex == GetMaxIndexByRepeat() && groupAtEnd) {
        offset.end = GetEndOverScrollOffset(delta, endMainPos, startMainPos);
    }
    return offset;
}

float ListPattern::GetStartOverScrollOffset(float offset, float startMainPos) const
{
    float startOffset = 0.0f;
    float ChainDelta = chainAnimation_ ? chainAnimation_->GetValuePredict(0, -offset) : 0.f;
    auto startPos = startMainPos + ChainDelta - currentDelta_;
    auto contentStartPos = contentStartOffset_;
    auto contentMainSize = contentMainSize_ - contentEndOffset_ - contentStartOffset_;
    if (GreatNotEqual(contentMainSize, endMainPos_ - startMainPos_) && isStackFromEnd_) {
        contentStartPos = contentMainSize - endMainPos_ + startMainPos_;
    }
    auto newStartPos = startPos + offset;
    if (startPos > contentStartPos && newStartPos > contentStartPos) {
        startOffset = offset;
    }
    if (startPos > contentStartPos && newStartPos <= contentStartPos) {
        startOffset = contentStartPos - startPos;
    }
    if (startPos <= contentStartPos && newStartPos > contentStartPos) {
        startOffset = newStartPos - contentStartPos;
    }
    return startOffset;
}

float ListPattern::GetEndOverScrollOffset(float offset, float endMainPos, float startMainPos) const
{
    float endOffset = 0.0f;
    float ChainDelta = chainAnimation_ ? chainAnimation_->GetValuePredict(maxListItemIndex_, -offset) : 0.f;
    auto endPos = endMainPos + ChainDelta - currentDelta_;
    auto contentEndPos = contentMainSize_ - contentEndOffset_;
    auto contentMainSize = contentMainSize_ - contentEndOffset_ - contentStartOffset_;
    if (GreatNotEqual(contentMainSize, endMainPos - startMainPos) && !isStackFromEnd_) {
        endPos = startMainPos + contentMainSize;
    }
    auto newEndPos = endPos + offset;
    if (endPos < contentEndPos && newEndPos < contentEndPos) {
        endOffset = offset;
    }
    if (endPos < contentEndPos && newEndPos >= contentEndPos) {
        endOffset = contentEndPos - endPos;
    }
    if (endPos >= contentEndPos && newEndPos < contentEndPos) {
        endOffset = newEndPos - contentEndPos;
    }
    return endOffset;
}

OverScrollOffset ListPattern::GetOutBoundaryOffset(float delta, bool useChainDelta) const
{
    OverScrollOffset offset = { 0, 0 };
    bool groupAtStart = true;
    bool groupAtEnd = true;
    GetListItemGroupEdge(groupAtStart, groupAtEnd);

    int32_t startIndex = startIndex_;
    float startMainPos = startMainPos_;
    int32_t endIndex = endIndex_;
    float endMainPos = endMainPos_;
    if (startIndex == 0 && groupAtStart) {
        auto startChainDelta = useChainDelta ? GetChainDelta(0) : 0.0f;
        auto contentMainSize = contentMainSize_ - contentEndOffset_ - contentStartOffset_;
        if (endIndex_ == maxListItemIndex_ && GreatNotEqual(contentMainSize, endMainPos - startMainPos) &&
            isStackFromEnd_) {
            startMainPos = endMainPos - contentMainSize;
        }
        offset.start = startMainPos - delta + startChainDelta - contentStartOffset_;
        offset.start = std::max(offset.start, 0.0);
    }
    if (endIndex >= maxListItemIndex_ && groupAtEnd) {
        auto endChainDelta = useChainDelta ? GetChainDelta(endIndex) : 0.0f;
        endMainPos = endMainPos + endChainDelta;
        auto contentMainSize = contentMainSize_ - contentEndOffset_ - contentStartOffset_;
        if (startIndex_ == 0 && GreatNotEqual(contentMainSize, endMainPos - startMainPos)) {
            endMainPos = startMainPos + contentMainSize;
        }
        offset.end = contentMainSize_ - contentEndOffset_ - (endMainPos - delta);
        offset.end = std::max(offset.end, 0.0);
    }
    return offset;
}

bool ListPattern::UpdateCurrentOffset(float offset, int32_t source)
{
    // check edgeEffect is not springEffect
    if (!jumpIndex_.has_value() && !targetIndex_.has_value() && !HandleEdgeEffect(offset, source, GetContentSize())) {
        if (IsOutOfBoundary(false)) {
            MarkDirtyNodeSelf();
        }
        return false;
    }

    SetScrollSource(source);
    FireAndCleanScrollingListener();
    auto lastDelta = currentDelta_;
    currentDelta_ = currentDelta_ - offset;
    if (source == SCROLL_FROM_BAR || source == SCROLL_FROM_BAR_FLING || source == SCROLL_FROM_STATUSBAR) {
        isNeedCheckOffset_ = true;
    }
    if (!NearZero(offset)) {
        MarkDirtyNodeSelf();
    }
    if (itemPosition_.empty() || !IsOutOfBoundary() || !isScrollable_) {
        auto userOffset = FireOnWillScroll(currentDelta_ - lastDelta);
        currentDelta_ = lastDelta + userOffset;
        return true;
    }

    if (source == SCROLL_FROM_UPDATE || source == SCROLL_FROM_CROWN) {
        auto res = GetOutBoundaryOffset(currentDelta_);
        // over scroll in drag update from normal to over scroll.
        float overScroll = std::max(res.start, res.end);
        // adjust offset.
        auto friction = GetScrollUpdateFriction(overScroll);
        offset = offset * friction;
        currentDelta_ = lastDelta - offset;
    }

    auto userOffset = FireOnWillScroll(currentDelta_ - lastDelta);
    currentDelta_ = lastDelta + userOffset;
    MarkScrollBarProxyDirty();
    return true;
}

void ListPattern::MarkDirtyNodeSelf()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!crossMatchChild_) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
}

void ListPattern::OnScrollEndCallback()
{
    if (AnimateStoped()) {
        scrollStop_ = true;
        MarkDirtyNodeSelf();
    }
}

SizeF ListPattern::GetContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, SizeF());
    auto size = renderContext->GetPaintRectWithoutTransform().GetSize();
    auto& padding = geometryNode->GetPadding();
    if (padding) {
        size.MinusPadding(*padding->left, *padding->right, *padding->top, *padding->bottom);
    }
    return size;
}

bool ListPattern::IsOutOfBoundary(bool useCurrentDelta)
{
    if (itemPosition_.empty()) {
        return false;
    }
    auto currentDelta = useCurrentDelta ? currentDelta_ : 0.0f;
    auto res = GetOutBoundaryOffset(currentDelta);
    // over scroll in drag update from normal to over scroll.
    return Positive(res.start) || Positive(res.end);
}

bool ListPattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        auto item = swiperItem_.Upgrade();
        if (item) {
            item->ResetSwipeStatus();
        }
        FireOnScrollStart();
        return true;
    }
    ProcessDragUpdate(offset, source);
    return UpdateCurrentOffset(offset, source);
}

bool ListPattern::StartSnapAnimation(SnapAnimationOptions snapAnimationOptions)
{
    auto snapDirection = snapAnimationOptions.snapDirection;
    auto listProperty = GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listProperty, false);
    auto scrollSnapAlign = listProperty->GetScrollSnapAlign().value_or(ScrollSnapAlign::NONE);
    CHECK_NULL_RETURN(scrollSnapAlign != ScrollSnapAlign::NONE, false);
    if (snapDirection != SnapDirection::NONE) {
        return ScrollToSnapIndex(snapDirection, scrollSnapAlign);
    }
    if (!IsScrolling()) {
        snapTrigOnScrollStart_ = true;
    }
    predictSnapOffset_ = snapAnimationOptions.snapDelta;
    scrollSnapVelocity_ = snapAnimationOptions.animationVelocity;
    snapTrigByScrollBar_ = snapAnimationOptions.fromScrollBar;
    predictSnapEndPos_.reset();
    MarkDirtyNodeSelf();
    return true;
}

bool ListPattern::ScrollToSnapIndex(SnapDirection snapDirection, ScrollSnapAlign scrollSnapAlign)
{
    ScrollAlign align = ScrollAlign::NONE;
    auto anchorIndex = startIndex_;
    switch (scrollSnapAlign) {
        case ScrollSnapAlign::NONE:
            return false;
        case ScrollSnapAlign::START:
            align = ScrollAlign::START;
            anchorIndex = GetStartIndexExcludeStartOffset();
            break;
        case ScrollSnapAlign::CENTER:
            align = ScrollAlign::CENTER;
            anchorIndex = centerIndex_;
            break;
        case ScrollSnapAlign::END:
            align = ScrollAlign::END;
            anchorIndex = GetEndIndexExcludeEndOffset();
            break;
    }
    if (snapDirection == SnapDirection::FORWARD) {
        if (!lastSnapTargetIndex_.has_value()) {
            if (align == ScrollAlign::START) {
                auto isAligned = GreatOrEqual(itemPosition_[anchorIndex].startPos, contentStartOffset_);
                lastSnapTargetIndex_ = isAligned ? anchorIndex - 1 : anchorIndex;
            } else if (align == ScrollAlign::END) {
                lastSnapTargetIndex_ = anchorIndex - 1;
            } else {
                auto item = itemPosition_[anchorIndex];
                auto itemCenterPos = (item.startPos + item.endPos) / 2;
                lastSnapTargetIndex_ =
                    GreatOrEqual(itemCenterPos, contentMainSize_ / 2) ? anchorIndex - 1 : anchorIndex;
            }
        } else {
            lastSnapTargetIndex_ = lastSnapTargetIndex_.value() - 1;
        }
    } else if (snapDirection == SnapDirection::BACKWARD) {
        if (!lastSnapTargetIndex_.has_value()) {
            if (align == ScrollAlign::START) {
                lastSnapTargetIndex_ = anchorIndex + 1;
            } else if (align == ScrollAlign::END) {
                auto isAligned = LessOrEqual(itemPosition_[anchorIndex].endPos, contentMainSize_ - contentEndOffset_);
                lastSnapTargetIndex_ = isAligned ? anchorIndex + 1 : anchorIndex;
            } else {
                auto item = itemPosition_[anchorIndex];
                auto itemCenterPos = (item.startPos + item.endPos) / 2;
                lastSnapTargetIndex_ = LessOrEqual(itemCenterPos, contentMainSize_ / 2) ? anchorIndex + 1 : anchorIndex;
            }
        } else {
            lastSnapTargetIndex_ = lastSnapTargetIndex_.value() + 1;
        }
    }
    lastSnapTargetIndex_ = std::max(lastSnapTargetIndex_.value(), 0);
    lastSnapTargetIndex_ = std::min(lastSnapTargetIndex_.value(), maxListItemIndex_);
    ScrollToIndex(lastSnapTargetIndex_.value(), true, align);
    return true;
}

int32_t ListPattern::GetEndIndexExcludeEndOffset()
{
    auto endPos = contentMainSize_ - contentEndOffset_;
    auto iter = itemPosition_.rbegin();
    while (iter != itemPosition_.rend() && GreatOrEqual(iter->second.startPos, endPos)) {
        iter++;
    }
    return iter->first;
}

int32_t ListPattern::GetStartIndexExcludeStartOffset()
{
    auto iter = itemPosition_.begin();
    while (iter != itemPosition_.end() && LessOrEqual(iter->second.endPos, contentStartOffset_)) {
        iter++;
    }
    return iter->first;
}

void ListPattern::StartListSnapAnimation(float scrollSnapDelta, float scrollSnapVelocity)
{
    CHECK_NULL_VOID(scrollable_);
    scrollable_->StartListSnapAnimation(scrollSnapDelta, scrollSnapVelocity, snapTrigByScrollBar_);
}

void ListPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        CHECK_NULL_RETURN(list, 0.0);
        return list->startMainPos_ - list->currentDelta_;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        auto endPos = list->endMainPos_;
        auto startPos = list->startMainPos_;
        float leading = list->contentMainSize_ - (endPos - startPos) - list->contentEndOffset_;
        if (list->isStackFromEnd_) {
            return leading;
        }
        return (list->startIndex_ == 0) ? std::min(leading, list->contentStartOffset_) : leading;
    });
    scrollEffect->SetTrailingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        CHECK_NULL_RETURN(list, 0.0);
        auto startMainPos = list->startMainPos_;
        auto endMainPos = list->endMainPos_;
        auto contentMainSize = list->contentMainSize_ - list->contentEndOffset_ - list->contentStartOffset_;
        if (list->startIndex_ == 0 && GreatNotEqual(contentMainSize, endMainPos - startMainPos) &&
            list->isStackFromEnd_) {
            return contentMainSize - endMainPos + startMainPos;
        }
        return list->contentStartOffset_;
    });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        auto endPos = list->endMainPos_;
        auto startPos = list->startMainPos_;
        float leading = list->contentMainSize_ - (endPos - startPos) - list->contentEndOffset_;
        if (list->isStackFromEnd_) {
            return leading;
        }
        return (list->startIndex_ == 0) ? std::min(leading, list->contentStartOffset_) : leading;
    });
    scrollEffect->SetInitTrailingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        CHECK_NULL_RETURN(list, 0.0);
        auto startMainPos = list->startMainPos_;
        auto endMainPos = list->endMainPos_;
        auto contentMainSize = list->contentMainSize_ - list->contentEndOffset_ - list->contentStartOffset_;
        if (list->startIndex_ == 0 && GreatNotEqual(contentMainSize, endMainPos - startMainPos) &&
            list->isStackFromEnd_) {
            return contentMainSize - endMainPos + startMainPos;
        }
        return list->contentStartOffset_;
    });
}

void ListPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool ListPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_PAGE_DOWN) {
        ScrollPage(false);
        return true;
    }
    if (event.code == KeyCode::KEY_PAGE_UP) {
        ScrollPage(true);
        return true;
    }
    return HandleDirectionKey(event);
}

bool ListPattern::HandleDirectionKey(const KeyEvent& event)
{
    return false;
}

WeakPtr<FocusHub> ListPattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    auto curFocus = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocus, nullptr);
    auto curFrame = curFocus->GetFrameNode();
    CHECK_NULL_RETURN(curFrame, nullptr);
    auto curPattern = curFrame->GetPattern();
    CHECK_NULL_RETURN(curPattern, nullptr);
    auto curItemPattern = AceType::DynamicCast<ListItemPattern>(curPattern);
    auto curIndex = -1;
    auto curIndexInGroup = -1;
    if (!curItemPattern) {
        auto parentNode = curFrame->GetParentFrameNode();
        CHECK_NULL_RETURN(parentNode, nullptr);
        auto parentPattern = AceType::DynamicCast<ListItemGroupPattern>(parentNode->GetPattern());
        CHECK_NULL_RETURN(parentPattern, nullptr);
        if (parentPattern->GetHeader() == curFrame) {
            curIndex = parentPattern->GetIndexInList();
            curIndexInGroup = -1;
        } else if (parentPattern->GetFooter() == curFrame) {
            curIndex = parentPattern->GetIndexInList();
            curIndexInGroup = parentPattern->GetTotalItemCount();
        } else {
            return nullptr;
        }
    } else {
        curIndex = curItemPattern->GetIndexInList();
        curIndexInGroup = curItemPattern->GetIndexInListItemGroup();
    }

    auto listProperty = GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listProperty, nullptr);
    auto isVertical = listProperty->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL;
    auto curListItemGroupPara = GetListItemGroupParameter(curFrame);
    if (curIndex < 0 || curIndex > maxListItemIndex_) {
        return nullptr;
    }

    auto moveStep = 0;
    auto nextIndex = curIndex;
    auto nextIndexInGroup = curIndexInGroup;
    if (lanes_ <= 1) {
        if ((isVertical && step == FocusStep::UP_END) || (!isVertical && step == FocusStep::LEFT_END)) {
            moveStep = 1;
            nextIndex = 0;
            nextIndexInGroup = -1;
        } else if ((isVertical && step == FocusStep::DOWN_END) || (!isVertical && step == FocusStep::RIGHT_END)) {
            moveStep = -1;
            nextIndex = maxListItemIndex_;
            nextIndexInGroup = -1;
        } else if ((isVertical && (step == FocusStep::DOWN)) || (!isVertical && step == FocusStep::RIGHT) ||
                   (step == FocusStep::TAB)) {
            moveStep = 1;
            if ((curIndexInGroup == -1 && !curListItemGroupPara.hasHeader) ||
                (curIndexInGroup == curListItemGroupPara.itemEndIndex && !curListItemGroupPara.hasFooter) ||
                (curIndexInGroup > curListItemGroupPara.itemEndIndex)) {
                nextIndex = curIndex + moveStep;
                nextIndexInGroup = -1;
            } else {
                nextIndexInGroup = curIndexInGroup + moveStep;
            }
        } else if ((isVertical && step == FocusStep::UP) || (!isVertical && step == FocusStep::LEFT) ||
                   (step == FocusStep::SHIFT_TAB)) {
            moveStep = -1;
            if (curIndexInGroup == 0 && curListItemGroupPara.hasHeader) {
                nextIndexInGroup = -1;
            } else if ((curIndexInGroup == -1) || (curIndexInGroup <= 0)) {
                nextIndex = curIndex + moveStep;
                nextIndexInGroup = -1;
            } else {
                nextIndexInGroup = curIndexInGroup + moveStep;
            }
        }
    } else {
        if ((step == FocusStep::UP_END) || (step == FocusStep::LEFT_END)) {
            moveStep = 1;
            nextIndex = 0;
            nextIndexInGroup = -1;
        } else if ((step == FocusStep::DOWN_END) || (step == FocusStep::RIGHT_END)) {
            moveStep = -1;
            nextIndex = maxListItemIndex_;
            nextIndexInGroup = -1;
        } else if ((isVertical && (step == FocusStep::DOWN)) || (!isVertical && step == FocusStep::RIGHT)) {
            if (curIndexInGroup == -1) {
                moveStep = lanes_;
                nextIndex = GetNextLineFocusIndex(curIndex);
                nextIndexInGroup = -1;
            } else {
                moveStep = curListItemGroupPara.lanes;
                nextIndexInGroup = curIndexInGroup + moveStep;
                VerifyFocusIndex(nextIndex, nextIndexInGroup, curListItemGroupPara);
            }
        } else if ((isVertical && step == FocusStep::UP) || (!isVertical && step == FocusStep::LEFT)) {
            if (curIndexInGroup == -1) {
                moveStep = -lanes_;
                nextIndex = curIndex + moveStep;
                nextIndexInGroup = -1;
            } else {
                moveStep = -curListItemGroupPara.lanes;
                nextIndexInGroup = curIndexInGroup + moveStep;
                VerifyFocusIndex(nextIndex, nextIndexInGroup, curListItemGroupPara);
            }
        } else if ((isVertical && (step == FocusStep::RIGHT)) || (!isVertical && step == FocusStep::DOWN)) {
            moveStep = 1;
            if (((curIndexInGroup == -1) && ((curIndex - (lanes_ - 1)) % lanes_ != 0)) ||
                ((curIndexInGroup != -1) &&
                    ((curIndexInGroup - (curListItemGroupPara.lanes - 1)) % curListItemGroupPara.lanes == 0))) {
                nextIndex = curIndex + moveStep;
                nextIndexInGroup = -1;
            } else if ((curIndexInGroup != -1) &&
                       ((curIndexInGroup - (curListItemGroupPara.lanes - 1)) % curListItemGroupPara.lanes != 0)) {
                nextIndexInGroup = curIndexInGroup + moveStep;
            }
        } else if ((isVertical && step == FocusStep::LEFT) || (!isVertical && step == FocusStep::UP)) {
            moveStep = -1;
            if (((curIndexInGroup == -1) && (curIndex % lanes_ != 0)) ||
                ((curIndexInGroup != -1) && (curIndexInGroup % curListItemGroupPara.lanes == 0))) {
                nextIndex = curIndex + moveStep;
                nextIndexInGroup = -1;
            } else if ((curIndexInGroup != -1) && (curIndexInGroup % curListItemGroupPara.lanes != 0)) {
                nextIndexInGroup = curIndexInGroup + moveStep;
            }
        } else if (step == FocusStep::TAB) {
            moveStep = 1;
            if ((curIndexInGroup == -1) || (curIndexInGroup >= curListItemGroupPara.itemEndIndex)) {
                nextIndex = curIndex + moveStep;
                nextIndexInGroup = -1;
            } else {
                nextIndexInGroup = curIndexInGroup + moveStep;
            }
        } else if (step == FocusStep::SHIFT_TAB) {
            moveStep = -1;
            if ((curIndexInGroup == -1) || (curIndexInGroup <= 0)) {
                nextIndex = curIndex + moveStep;
                nextIndexInGroup = -1;
            } else {
                nextIndexInGroup = curIndexInGroup + moveStep;
            }
        }
    }
    while (nextIndex >= 0 && nextIndex <= maxListItemIndex_) {
        if ((nextIndex == curIndex) && (curIndexInGroup == nextIndexInGroup)) {
            return nullptr;
        }
        auto nextFocusNode =
            ScrollAndFindFocusNode(nextIndex, curIndex, nextIndexInGroup, curIndexInGroup, moveStep, step);
        if (nextFocusNode.Upgrade()) {
            return nextFocusNode;
        }
        if (nextIndexInGroup > -1) {
            nextIndexInGroup += moveStep;
        } else {
            nextIndex += moveStep;
        }
    }
    return nullptr;
}

void ListPattern::VerifyFocusIndex(int32_t& nextIndex, int32_t& nextIndexInGroup, const ListItemGroupPara& param)
{
    if (nextIndexInGroup < 0) {
        nextIndex--;
        nextIndexInGroup = -1;
    } else if (nextIndexInGroup > param.itemEndIndex) {
        if (param.lanes > 1 &&
            nextIndexInGroup <= param.itemEndIndex + param.lanes - param.itemEndIndex % param.lanes - 1) {
            nextIndexInGroup = param.itemEndIndex;
        } else {
            nextIndex++;
            nextIndexInGroup = -1;
        }
    }
}

int32_t ListPattern::GetNextLineFocusIndex(int32_t currIndex)
{
    int32_t nextIndex = currIndex + lanes_;
    if (nextIndex <= maxListItemIndex_) {
        return nextIndex;
    }
    auto it1 = itemPosition_.find(currIndex);
    if (it1 == itemPosition_.end()) {
        return nextIndex;
    }
    auto it2 = itemPosition_.find(maxListItemIndex_);
    if (it2 == itemPosition_.end()) {
        return maxListItemIndex_;
    }
    if (NearEqual(it1->second.startPos, it2->second.startPos)) {
        return nextIndex;
    }
    return maxListItemIndex_;
}

WeakPtr<FocusHub> ListPattern::GetChildFocusNodeByIndex(int32_t tarMainIndex, int32_t tarGroupIndex)
{
    auto listFrame = GetHost();
    CHECK_NULL_RETURN(listFrame, nullptr);
    auto listFocus = listFrame->GetFocusHub();
    CHECK_NULL_RETURN(listFocus, nullptr);
    WeakPtr<FocusHub> target;
    listFocus->AnyChildFocusHub([&target, tarMainIndex, tarGroupIndex](const RefPtr<FocusHub>& childFocus) {
        if (!childFocus->IsFocusable()) {
            return false;
        }
        auto childFrame = childFocus->GetFrameNode();
        if (!childFrame) {
            return false;
        }
        auto childPattern = childFrame->GetPattern();
        if (!childPattern) {
            return false;
        }
        auto childItemPattern = AceType::DynamicCast<ListItemPattern>(childPattern);
        if (!childItemPattern) {
            auto parentNode = childFrame->GetParentFrameNode();
            CHECK_NULL_RETURN(parentNode, false);
            auto parentPattern = AceType::DynamicCast<ListItemGroupPattern>(parentNode->GetPattern());
            CHECK_NULL_RETURN(parentPattern, false);
            if (parentPattern->GetIndexInList() == tarMainIndex) {
                if ((parentPattern->GetHeader() == childFrame && tarGroupIndex == -1) ||
                    (parentPattern->GetFooter() == childFrame && tarGroupIndex == parentPattern->GetTotalItemCount())) {
                    target = childFocus;
                    return true;
                }
            }
            return false;
        }
        auto curIndex = childItemPattern->GetIndexInList();
        auto curIndexInGroup = childItemPattern->GetIndexInListItemGroup();
        if (curIndex == tarMainIndex && curIndexInGroup == tarGroupIndex) {
            target = childFocus;
            return true;
        }
        return false;
    });
    return target;
}

bool ListPattern::ScrollToNode(const RefPtr<FrameNode>& focusFrameNode)
{
    CHECK_NULL_RETURN(focusFrameNode, false);
    auto focusPattern = focusFrameNode->GetPattern<ListItemPattern>();
    CHECK_NULL_RETURN(focusPattern, false);
    auto curIndex = focusPattern->GetIndexInList();
    ScrollToIndex(curIndex, smooth_, GetScrollToNodeAlign());
    auto pipeline = GetContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }
    return true;
}

ScrollOffsetAbility ListPattern::GetScrollOffsetAbility()
{
    return {
        [wp = WeakClaim(this)](float moveOffset) -> bool {
            auto pattern = wp.Upgrade();
            CHECK_NULL_RETURN(pattern, false);
            pattern->ScrollBy(-moveOffset);
            return true;
        },
        GetAxis(),
        IsScrollSnapAlignCenter() ? 0 : contentStartOffset_,
        IsScrollSnapAlignCenter() ? 0 : contentEndOffset_,
    };
}

std::function<bool(int32_t)> ListPattern::GetScrollIndexAbility()
{
    return [wp = WeakClaim(this)](int32_t index) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (index == FocusHub::SCROLL_TO_HEAD) {
            pattern->ScrollToIndex(0, false, ScrollAlign::START);
        } else if (index == FocusHub::SCROLL_TO_TAIL) {
            pattern->ScrollToIndex(ListLayoutAlgorithm::LAST_ITEM, false, ScrollAlign::END);
        } else {
            pattern->ScrollToIndex(index, false, ScrollAlign::AUTO);
        }
        return true;
    };
}

WeakPtr<FocusHub> ListPattern::ScrollAndFindFocusNode(int32_t nextIndex, int32_t curIndex, int32_t& nextIndexInGroup,
    int32_t curIndexInGroup, int32_t moveStep, FocusStep step)
{
    bool isScrollIndex = ScrollListForFocus(nextIndex, curIndex, nextIndexInGroup);
    bool needFindNextFocusNode = ScrollListItemGroupForFocus(
        nextIndex, curIndex, nextIndexInGroup, curIndexInGroup, moveStep, step, isScrollIndex);

    return needFindNextFocusNode ? GetChildFocusNodeByIndex(nextIndex, nextIndexInGroup) : nullptr;
}

bool ListPattern::ScrollListForFocus(int32_t nextIndex, int32_t curIndex, int32_t nextIndexInGroup)
{
    auto isScrollIndex = false;
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, isScrollIndex);
    if (nextIndex < startIndex_ && nextIndexInGroup == -1) {
        isScrollIndex = true;
        ScrollToIndex(nextIndex, false, ScrollAlign::START);
        pipeline->FlushUITasks();
    } else if (nextIndex > endIndex_ && nextIndexInGroup == -1) {
        isScrollIndex = true;
        ScrollToIndex(nextIndex, false, ScrollAlign::END);
        pipeline->FlushUITasks();
    } else if (nextIndexInGroup == -1 && HandleDisplayedChildFocus(nextIndex, curIndex)) {
        isScrollIndex = true;
        pipeline->FlushUITasks();
    }
    return isScrollIndex;
}

bool ListPattern::HandleDisplayedChildFocus(int32_t nextIndex, int32_t curIndex)
{
    auto iter = itemPosition_.find(nextIndex);
    if (iter == itemPosition_.end()) {
        return false;
    }
    float targetPos = 0.0f;
    float startPos = iter->second.startPos;
    float endPos = iter->second.endPos;
    ScrollAlign align = ScrollAlign::AUTO;
    if (iter->second.isGroup) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto itemGroupWrapper = host->GetChildByIndex(nextIndex);
        CHECK_NULL_RETURN(itemGroupWrapper, false);
        auto itemGroup = itemGroupWrapper->GetHostNode();
        CHECK_NULL_RETURN(itemGroup, false);
        auto groupPattern = itemGroup->GetPattern<ListItemGroupPattern>();
        CHECK_NULL_RETURN(groupPattern, false);
        int32_t indexInGroup = nextIndex < curIndex ? groupPattern->GetEndIndexInGroup() : 0;
        if (!GetListItemGroupAnimatePosWithIndexInGroup(nextIndex, indexInGroup, startPos, align, targetPos)) {
            targetPos = startPos;
        }
    } else {
        GetListItemAnimatePos(startPos, endPos, align, targetPos);
    }
    if (Positive(targetPos)) {
        ScrollToIndex(nextIndex, false, ScrollAlign::END);
        return iter->second.isGroup;
    } else if (Negative(targetPos)) {
        ScrollToIndex(nextIndex, false, ScrollAlign::START);
        return iter->second.isGroup;
    }
    return false;
}

ScrollAlign ListPattern::CalcAlignForFocusToGroupItem(int32_t moveStep, FocusStep step) const
{
    // Extract method only for ScrollListItemGroupForFocus.
    ScrollAlign scrollAlign = ScrollAlign::END;
    if ((step == FocusStep::UP_END) || (step == FocusStep::LEFT_END) || (step == FocusStep::DOWN_END) ||
        (step == FocusStep::RIGHT_END)) {
        scrollAlign = moveStep < 0 ? ScrollAlign::END : ScrollAlign::START;
    } else {
        scrollAlign = moveStep < 0 ? ScrollAlign::START : ScrollAlign::END;
    }
    return scrollAlign;
}

int32_t ListPattern::CalcNextIndexInGroup(int32_t nextIndex, int32_t curIndex, int32_t curIndexInGroup,
    int32_t moveStep, ListItemGroupPara& nextListItemGroupPara) const
{
    // Extract method only for ScrollListItemGroupForFocus.
    int32_t nextIndexInGroup = -1;
    if (nextIndex != curIndex) {
        nextIndexInGroup = moveStep < 0 ? nextListItemGroupPara.itemEndIndex : 0;
    }
    if (moveStep == -1) {
        if (curIndexInGroup == -1 && nextListItemGroupPara.hasFooter) {
            nextIndexInGroup = nextListItemGroupPara.itemEndIndex + 1;
        }
    } else if (moveStep == 1) {
        if (!nextListItemGroupPara.hasHeader) {
            nextIndexInGroup = 0;
        } else {
            nextIndexInGroup = -1;
        }
    }
    return nextIndexInGroup;
}

bool ListPattern::ScrollListItemGroupForFocus(int32_t nextIndex, int32_t curIndex, int32_t& nextIndexInGroup,
    int32_t curIndexInGroup, int32_t moveStep, FocusStep step, bool isScrollIndex)
{
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, true);
    RefPtr<FrameNode> nextIndexNode;
    auto isNextInGroup = IsListItemGroup(nextIndex, nextIndexNode);
    if (!isNextInGroup || !nextIndexNode) {
        nextIndexInGroup = -1;
        return true;
    }
    auto nextListItemGroupPara = GetListItemGroupParameter(nextIndexNode);
    if (nextIndexInGroup == -1) {
        nextIndexInGroup = CalcNextIndexInGroup(nextIndex, curIndex, curIndexInGroup, moveStep, nextListItemGroupPara);
        if ((nextIndexInGroup < nextListItemGroupPara.displayStartIndex) ||
            (nextIndexInGroup > nextListItemGroupPara.displayEndIndex) || (isScrollIndex)) {
            ScrollAlign align = CalcAlignForFocusToGroupItem(moveStep, step);
            ScrollToItemInGroup(nextIndex, nextIndexInGroup, false, align);
            pipeline->FlushUITasks();
        }
    } else if (nextIndexInGroup > nextListItemGroupPara.itemEndIndex) {
        if (nextListItemGroupPara.hasFooter) {
            ScrollToIndex(nextIndex, false, ScrollAlign::END);
            pipeline->FlushUITasks();
        } else {
            nextIndexInGroup = -1;
            return false;
        }
    } else if ((nextIndexInGroup < curIndexInGroup) && (nextIndexInGroup < nextListItemGroupPara.displayStartIndex)) {
        ScrollToItemInGroup(nextIndex, nextIndexInGroup, false, ScrollAlign::START);
        pipeline->FlushUITasks();
    } else if ((nextIndexInGroup > curIndexInGroup) && (nextIndexInGroup > nextListItemGroupPara.displayEndIndex)) {
        ScrollToItemInGroup(nextIndex, nextIndexInGroup, false, ScrollAlign::END);
        pipeline->FlushUITasks();
    }
    return true;
}

void ListPattern::OnAnimateStop()
{
    if (!GetIsDragging() || GetScrollAbort()) {
        scrollStop_ = true;
        MarkDirtyNodeSelf();
        isScrollEnd_ = true;
    }
    scrollTarget_.reset();
}

void ListPattern::ScrollTo(float position)
{
    StopAnimate();
    jumpIndex_.reset();
    targetIndex_.reset();
    currentDelta_ = 0.0f;
    UpdateCurrentOffset(GetTotalOffset() - position, SCROLL_FROM_JUMP);
    MarkDirtyNodeSelf();
    isScrollEnd_ = true;
}

void ListPattern::ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset)
{
    SetScrollSource(SCROLL_FROM_JUMP);
    // When snap align scrolling with the mouse wheel, do not interrupt the animation.
    if (!smooth && !lastSnapTargetIndex_.has_value()) {
        StopAnimate();
        targetIndex_.reset();
        targetIndexInGroup_.reset();
    }
    if (index >= 0 || index == ListLayoutAlgorithm::LAST_ITEM) {
        currentDelta_ = 0.0f;
        smooth_ = smooth;
        if (smooth_) {
            SetExtraOffset(extraOffset);
            if (!AnimateToTarget(index, std::nullopt, align)) {
                targetIndex_ = index;
                scrollAlign_ = align;
            }
        } else {
            if (extraOffset.has_value()) {
                currentDelta_ = extraOffset.value();
            }
            jumpIndex_ = index;
            scrollAlign_ = align;
            jumpIndexInGroup_.reset();
        }
        MarkDirtyNodeSelf();
    }
    isScrollEnd_ = true;
    FireAndCleanScrollingListener();
}

bool ListPattern::CheckTargetValid(int32_t index, int32_t indexInGroup)
{
    auto host = GetHost();
    auto totalItemCount = host->GetTotalChildCount();
    if ((index < 0) || (index >= totalItemCount)) {
        return false;
    }
    auto groupWrapper = host->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(groupWrapper, false);
    if (groupWrapper->GetHostTag() != V2::LIST_ITEM_GROUP_ETS_TAG) {
        return false;
    }
    auto groupNode = groupWrapper->GetHostNode();
    CHECK_NULL_RETURN(groupNode, false);
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(groupPattern, false);
    auto groupItemCount = groupWrapper->GetTotalChildCount() - groupPattern->GetItemStartIndex();
    if ((indexInGroup < 0) || (indexInGroup >= groupItemCount)) {
        return false;
    }
    return true;
}

void ListPattern::ScrollToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align)
{
    SetScrollSource(SCROLL_FROM_JUMP);
    if (!smooth) {
        StopAnimate();
        targetIndex_.reset();
        targetIndexInGroup_.reset();
    }
    if (index >= 0 || index == ListLayoutAlgorithm::LAST_ITEM) {
        currentDelta_ = 0.0f;
        smooth_ = smooth;
        if (smooth_) {
            if (!AnimateToTarget(index, indexInGroup, align) && CheckTargetValid(index, indexInGroup)) {
                targetIndex_ = index;
                currentDelta_ = 0;
                targetIndexInGroup_ = indexInGroup;
                scrollAlign_ = align;
            }
        } else {
            jumpIndex_ = index;
            jumpIndexInGroup_ = indexInGroup;
            scrollAlign_ = align;
        }
        MarkDirtyNodeSelf();
    }
    isScrollEnd_ = true;
    FireAndCleanScrollingListener();
}

bool ListPattern::GetListItemAnimatePos(float startPos, float endPos, ScrollAlign align, float& targetPos)
{
    switch (align) {
        case ScrollAlign::START:
        case ScrollAlign::NONE:
            targetPos = startPos;
            if (!IsScrollSnapAlignCenter() || childrenSize_) {
                targetPos -= contentStartOffset_;
            }
            break;
        case ScrollAlign::CENTER:
            targetPos = (endPos + startPos) / 2.0f - contentMainSize_ / 2.0f;
            break;
        case ScrollAlign::END:
            targetPos = endPos - contentMainSize_;
            if (!IsScrollSnapAlignCenter() || childrenSize_) {
                targetPos += contentEndOffset_;
            }
            break;
        case ScrollAlign::AUTO:
            targetPos = CalculateTargetPos(startPos, endPos);
            break;
    }
    return true;
}

bool ListPattern::GetListItemGroupAnimatePosWithoutIndexInGroup(
    int32_t index, float startPos, float endPos, ScrollAlign align, float& targetPos)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto groupWrapper = host->GetChildByIndex(index);
    CHECK_NULL_RETURN(groupWrapper, false);
    auto groupNode = groupWrapper->GetHostNode();
    CHECK_NULL_RETURN(groupNode, false);
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(groupPattern, false);
    auto groupLayoutProperty = groupNode->GetLayoutProperty<ListItemGroupLayoutProperty>();
    CHECK_NULL_RETURN(groupLayoutProperty, false);
    auto visible = groupLayoutProperty->GetVisibility().value_or(VisibleType::VISIBLE);

    switch (align) {
        case ScrollAlign::START:
        case ScrollAlign::NONE:
            if (visible != VisibleType::GONE && !groupPattern->IsDisplayStart()) {
                return false;
            }
            targetPos = startPos;
            if (!IsScrollSnapAlignCenter() || childrenSize_) {
                targetPos -= contentStartOffset_;
            }
            break;
        case ScrollAlign::CENTER:
            if (visible != VisibleType::GONE && (!groupPattern->IsDisplayStart() || !groupPattern->IsDisplayEnd())) {
                return false;
            }
            targetPos = (endPos + startPos) / 2.0f - contentMainSize_ / 2.0f;
            break;
        case ScrollAlign::END:
            if (visible != VisibleType::GONE && !groupPattern->IsDisplayEnd()) {
                return false;
            }
            targetPos = endPos - contentMainSize_;
            if (!IsScrollSnapAlignCenter() || childrenSize_) {
                targetPos += contentEndOffset_;
            }
            break;
        case ScrollAlign::AUTO:
            if (targetIndex_.has_value()) {
                targetPos = CalculateTargetPos(startPos, endPos);
                return true;
            }
            return false;
    }

    return true;
}

bool ListPattern::GetListItemGroupAnimatePosWithIndexInGroup(
    int32_t index, int32_t indexInGroup, float startPos, ScrollAlign align, float& targetPos)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto groupWrapper = host->GetChildByIndex(index);
    CHECK_NULL_RETURN(groupWrapper, false);
    auto groupNode = groupWrapper->GetHostNode();
    CHECK_NULL_RETURN(groupNode, false);
    auto groupPattern = groupNode->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(groupPattern, false);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listLayoutProperty, false);
    auto stickyStyle = listLayoutProperty->GetStickyStyle().value_or(V2::StickyStyle::NONE);
    auto itemsPosInGroup = groupPattern->GetItemPosition();
    auto it = itemsPosInGroup.find(indexInGroup);
    if (it == itemsPosInGroup.end()) {
        return false;
    }
    auto axis = GetAxis();
    std::optional<float> padding;
    std::optional<float> margin;
    if (axis == Axis::HORIZONTAL) {
        padding = IsReverse() ? groupWrapper->GetGeometryNode()->GetPadding()->right
                              : groupWrapper->GetGeometryNode()->GetPadding()->left;
        margin = IsReverse() ? groupWrapper->GetGeometryNode()->GetMargin()->right
                             : groupWrapper->GetGeometryNode()->GetMargin()->left;
    } else {
        padding = groupWrapper->GetGeometryNode()->GetPadding()->top;
        margin = groupWrapper->GetGeometryNode()->GetMargin()->top;
    }
    auto marginValue = margin.value_or(0.f);
    auto paddingValue = padding.value_or(0.f);
    if (align == ScrollAlign::CENTER) {
        targetPos = paddingValue + marginValue + startPos + (it->second.startPos + it->second.endPos) / 2.0f -
                    contentMainSize_ / 2.0f;
    } else {
        float itemStartPos = paddingValue + marginValue + startPos + it->second.startPos;
        float itemEndPos = paddingValue + marginValue + startPos + it->second.endPos;
        if (stickyStyle == V2::StickyStyle::HEADER || stickyStyle == V2::StickyStyle::BOTH) {
            itemStartPos -= groupPattern->GetHeaderMainSize();
        }
        if (stickyStyle == V2::StickyStyle::FOOTER || stickyStyle == V2::StickyStyle::BOTH) {
            itemEndPos += groupPattern->GetFooterMainSize();
        }
        if (align == ScrollAlign::AUTO) {
            targetPos = CalculateTargetPos(itemStartPos, itemEndPos);
        } else {
            if (!IsScrollSnapAlignCenter() || childrenSize_) {
                itemStartPos -= contentStartOffset_;
                itemEndPos += contentEndOffset_;
            }
            targetPos = align == ScrollAlign::END ? itemEndPos - contentMainSize_ : itemStartPos;
        }
    }
    return true;
}

bool ListPattern::AnimateToTarget(int32_t index, std::optional<int32_t> indexInGroup, ScrollAlign align)
{
    auto iter = itemPosition_.find(index);
    if (iter == itemPosition_.end()) {
        return false;
    }
    float targetPos = 0.0f;
    if (iter->second.isGroup) {
        if (indexInGroup.has_value()) {
            if (!GetListItemGroupAnimatePosWithIndexInGroup(index, indexInGroup.value(), iter->second.startPos,
                align, targetPos)) {
                return false;
            }
        } else {
            if (!GetListItemGroupAnimatePosWithoutIndexInGroup(index, iter->second.startPos, iter->second.endPos,
                align, targetPos)) {
                return false;
            }
        }
    } else {
        if (indexInGroup.has_value()) {
            return false;
        }
        GetListItemAnimatePos(iter->second.startPos, iter->second.endPos, align, targetPos);
    }
    float extraOffset = 0.0f;
    if (GetExtraOffset().has_value()) {
        extraOffset = GetExtraOffset().value();
        targetPos += extraOffset;
        ResetExtraOffset();
    }
    if (lastSnapTargetIndex_.has_value()) {
        if ((Positive(targetPos) && IsAtBottom()) || (Negative(targetPos) && IsAtTop())) {
            ResetLastSnapTargetIndex();
            return true;
        }
    }
    if (!NearZero(targetPos)) {
        AnimateTo(targetPos + currentOffset_, -1, nullptr, true, false, false);
        if (predictSnapOffset_.has_value() && AnimateRunning()) {
            scrollSnapVelocity_ = 0.0f;
            predictSnapOffset_.reset();
            snapTrigOnScrollStart_ = false;
        }
        if (!indexInGroup.has_value()) {
            scrollTarget_ = { index, extraOffset, align, targetPos + currentOffset_ };
        }
    }
    return true;
}

void ListPattern::ScrollPage(bool reverse, bool smooth, AccessibilityScrollType scrollType)
{
    float distance = reverse ? contentMainSize_ : -contentMainSize_;
    if (scrollType == AccessibilityScrollType::SCROLL_HALF) {
        distance = distance / 2.f;
    }
    if (smooth) {
        float position = -GetTotalOffset() + distance;
        AnimateTo(-position, -1, nullptr, true, false, false);
    } else {
        StopAnimate();
        UpdateCurrentOffset(distance, SCROLL_FROM_JUMP);
        isScrollEnd_ = true;
    }
}

void ListPattern::ScrollBy(float offset)
{
    StopAnimate();
    UpdateCurrentOffset(-offset, SCROLL_FROM_JUMP);
    isScrollEnd_ = true;
}

Offset ListPattern::GetCurrentOffset() const
{
    if (GetAxis() == Axis::HORIZONTAL) {
        return { GetTotalOffset(), 0.0 };
    }
    return { 0.0, GetTotalOffset() };
}

void ListPattern::HandleScrollBarOutBoundary()
{
    if (itemPosition_.empty()) {
        return;
    }
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    if (!isScrollable_) {
        ScrollablePattern::HandleScrollBarOutBoundary(0);
        return;
    }
    auto res = GetOutBoundaryOffset(0.0f);
    float overScroll = std::max(res.start, res.end);
    ScrollablePattern::HandleScrollBarOutBoundary(overScroll);
}

Rect ListPattern::GetItemRect(int32_t index) const
{
    if (index < 0 || index < startIndex_ || index > endIndex_) {
        return Rect();
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, Rect());
    auto item = host->GetChildByIndex(index + itemStartIndex_);
    CHECK_NULL_RETURN(item, Rect());
    auto itemGeometry = item->GetGeometryNode();
    CHECK_NULL_RETURN(itemGeometry, Rect());
    return Rect(itemGeometry->GetFrameRect().GetX(), itemGeometry->GetFrameRect().GetY(),
        itemGeometry->GetFrameRect().Width(), itemGeometry->GetFrameRect().Height());
}

int32_t ListPattern::GetItemIndex(double x, double y) const
{
    for (int32_t index = startIndex_; index <= endIndex_; ++index) {
        Rect rect = GetItemRect(index);
        if (rect.IsInRegion({x, y})) {
            return index;
        }
    }
    return -1;
}

ListItemIndex ListPattern::GetItemIndexInGroup(double x, double y) const
{
    ListItemIndex itemIndex = { -1, -1, -1 };

    auto host = GetHost();
    CHECK_NULL_RETURN(host, itemIndex);
    for (int32_t index = startIndex_; index <= endIndex_; ++index) {
        auto item = host->GetChildByIndex(index);
        if (!AceType::InstanceOf<FrameNode>(item)) {
            continue;
        }
        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        auto groupItemPattern  = itemFrameNode->GetPattern<ListItemGroupPattern>();
        if (groupItemPattern) {
            if (GetGroupItemIndex(x, y, itemFrameNode, index, itemIndex)) {
                return itemIndex;
            }
        } else {
            Rect rect = GetItemRect(index);
            if (rect.IsInRegion({x, y})) {
                itemIndex.index = index;
                return itemIndex;
            }
        }
    }
    return itemIndex;
}

bool ListPattern::GetGroupItemIndex(double x, double y, RefPtr<FrameNode> itemFrameNode,
    int32_t& index, ListItemIndex& itemIndex) const
{
    auto groupItemPattern = itemFrameNode->GetPattern<ListItemGroupPattern>();
    Rect rect = GetItemRect(index);
    if (groupItemPattern && rect.IsInRegion({x, y})) {
        itemIndex.index = index;
        for (int32_t groupIndex = groupItemPattern->GetDisplayStartIndexInGroup();
            groupIndex <= groupItemPattern->GetDisplayEndIndexInGroup(); ++groupIndex) {
            Rect groupRect = GetItemRectInGroup(index, groupIndex);
            if (groupRect.IsInRegion({x, y})) {
                itemIndex.index = index;
                itemIndex.area = 1; // item area
                itemIndex.indexInGroup = groupIndex;
                return true;
            }
        }

        int32_t areaValue = 0;
        if (GetAxis() == Axis::VERTICAL) {
            areaValue = ProcessAreaVertical(x, y, rect, index, groupItemPattern);
        } else {
            areaValue = ProcessAreaHorizontal(x, y, rect, index, groupItemPattern);
        }
        if (areaValue != -1) {
            itemIndex.index = index;
            itemIndex.area = areaValue;
            itemIndex.indexInGroup = -1;
            return true;
        }
    }

    return false;
}

int32_t ListPattern::ProcessAreaVertical(double& x, double& y, Rect& groupRect, int32_t& index,
    RefPtr<ListItemGroupPattern> groupItemPattern) const
{
    if (groupItemPattern->GetTotalItemCount() > 0) { // has item
        Rect firstRect = GetItemRectInGroup(index, 0); //first item Rect
        Rect endRect = GetItemRectInGroup(index, groupItemPattern->GetDisplayEndIndexInGroup()); //end item Rect

        if (groupItemPattern->IsHasHeader() && LessOrEqual(y, firstRect.Top()) && GreatOrEqual(y, groupRect.Top())) {
            return  DEFAULT_HEADER_VALUE;
        }

        if (groupItemPattern->IsHasFooter() && GreatOrEqual(y, endRect.Bottom()) &&
            LessOrEqual(y, groupRect.Bottom())) {
            return  DEFAULT_FOOTER_VALUE;
        }
    } else if (groupItemPattern->IsHasHeader() || groupItemPattern->IsHasFooter()) {
        float headerHeight = groupItemPattern->GetHeaderMainSize();
        float footerHeight = groupItemPattern->GetFooterMainSize();
        float topPaddng = groupItemPattern->GetHost()->GetGeometryNode()->GetPadding()->top.value_or(0.0f);
        float bottomPaddng = groupItemPattern->GetHost()->GetGeometryNode()->GetPadding()->bottom.value_or(0.0f);
        if (LessOrEqual(y, groupRect.Top() + headerHeight + topPaddng)  && GreatOrEqual(y, groupRect.Top())) { //header
            return  DEFAULT_HEADER_VALUE;
        } else if (GreatOrEqual(y, groupRect.Bottom() - footerHeight - bottomPaddng) &&
            LessOrEqual(y, groupRect.Bottom())) {
            return  DEFAULT_FOOTER_VALUE;
        }
    } else if (GreatOrEqual(y, groupRect.Top())  && LessOrEqual(y, groupRect.Bottom())) {
        return  0;
    }

    return -1;
}

int32_t ListPattern::ProcessAreaHorizontal(double& x, double& y, Rect& groupRect, int32_t& index,
    RefPtr<ListItemGroupPattern> groupItemPattern) const
{
    if (groupItemPattern->GetTotalItemCount() > 0) { // has item
        Rect firstRect = GetItemRectInGroup(index, 0); //first item Rect
        Rect endRect = GetItemRectInGroup(index, groupItemPattern->GetDisplayEndIndexInGroup()); //end item Rect

        if (groupItemPattern->IsHasHeader() && LessOrEqual(x, firstRect.Left()) && GreatOrEqual(x, groupRect.Left())) {
            return  DEFAULT_HEADER_VALUE;
        }

        if (groupItemPattern->IsHasFooter() && GreatOrEqual(x, endRect.Right()) && LessOrEqual(x, groupRect.Right())) {
            return  DEFAULT_FOOTER_VALUE;
        }
    } else if (groupItemPattern->IsHasHeader() || groupItemPattern->IsHasFooter()) {
        float headerHeight = groupItemPattern->GetHeaderMainSize();
        float footerHeight = groupItemPattern->GetFooterMainSize();
        float leftPaddng = groupItemPattern->GetHost()->GetGeometryNode()->GetPadding()->left.value_or(0.0f);
        float rightPaddng = groupItemPattern->GetHost()->GetGeometryNode()->GetPadding()->right.value_or(0.0f);
        if (LessOrEqual(x, groupRect.Left() + headerHeight + leftPaddng)  && GreatOrEqual(x, groupRect.Left())) {
            return  DEFAULT_HEADER_VALUE;
        } else if (GreatOrEqual(x, groupRect.Right() - footerHeight - rightPaddng) &&
            LessOrEqual(x, groupRect.Right())) {
            return  DEFAULT_FOOTER_VALUE;
        }
    } else if (GreatOrEqual(x, groupRect.Left())  && LessOrEqual(x, groupRect.Right())) {
        return  0;
    }

    return -1;
}

Rect ListPattern::GetItemRectInGroup(int32_t index, int32_t indexInGroup) const
{
    if (index < 0 || indexInGroup < 0 || index < startIndex_ || index > endIndex_) {
        return Rect();
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, Rect());
    auto itemGroupWrapper = host->GetChildByIndex(index);
    CHECK_NULL_RETURN(itemGroupWrapper, Rect());
    auto itemGroup = itemGroupWrapper->GetHostNode();
    CHECK_NULL_RETURN(itemGroup, Rect());
    if (!(itemGroup->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG)) {
        return Rect();
    }
    auto itemGroupGeometry = itemGroup->GetGeometryNode();
    CHECK_NULL_RETURN(itemGroupGeometry, Rect());
    auto groupPattern = itemGroup->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(groupPattern, Rect());
    if (indexInGroup < groupPattern->GetDisplayStartIndexInGroup() ||
        indexInGroup > groupPattern->GetDisplayEndIndexInGroup()) {
        return Rect();
    }
    auto groupItem = itemGroup->GetChildByIndex(indexInGroup + groupPattern->GetItemStartIndex());
    CHECK_NULL_RETURN(groupItem, Rect());
    auto groupItemGeometry = groupItem->GetGeometryNode();
    CHECK_NULL_RETURN(groupItemGeometry, Rect());
    return Rect(itemGroupGeometry->GetFrameRect().GetX() + groupItemGeometry->GetFrameRect().GetX(),
        itemGroupGeometry->GetFrameRect().GetY() + groupItemGeometry->GetFrameRect().GetY(),
        groupItemGeometry->GetFrameRect().Width(), groupItemGeometry->GetFrameRect().Height());
}

bool ListPattern::CalculateJumpOffset()
{
    for (const auto& pos : itemPosition_) {
        if (pos.second.groupInfo && !pos.second.groupInfo.value().atStart) {
            continue;
        }
        ListPositionInfo info = posMap_->GetPositionInfo(pos.first);
        if (!Negative(info.mainSize)) {
            currentOffset_ = info.mainPos - pos.second.startPos;
            return true;
        }
    }
    return false;
}

float ListPattern::UpdateTotalOffset(const RefPtr<ListLayoutAlgorithm>& listLayoutAlgorithm, bool isJump)
{
    float relativeOffset = listLayoutAlgorithm->GetCurrentOffset();
    float prevOffset = currentOffset_;
    if (childrenSize_) {
        listTotalHeight_ = posMap_->GetTotalHeight();
        currentOffset_ = itemPosition_.empty() ? 0.0f :
            posMap_->GetPos(itemPosition_.begin()->first, itemPosition_.begin()->second.startPos);
    } else {
        if (isJump && !needReEstimateOffset_) {
            if (CalculateJumpOffset()) {
                relativeOffset = 0.0f;
            } else {
                needReEstimateOffset_ = true;
            }
        }
        if (needReEstimateOffset_) {
            posMap_->ClearPosMap();
            auto calculate = ListHeightOffsetCalculator(itemPosition_, spaceWidth_, lanes_, GetAxis(), itemStartIndex_);
            calculate.SetPosMap(posMap_, true);
            calculate.GetEstimateHeightAndOffset(GetHost());
            currentOffset_ = calculate.GetEstimateOffset();
            relativeOffset = 0;
            needReEstimateOffset_ = false;
        }
        CalculateCurrentOffset(relativeOffset, listLayoutAlgorithm->GetRecycledItemPosition());
    }
    CheckAndUpdateAnimateTo(relativeOffset, prevOffset);
    
    return currentOffset_ - prevOffset;
}

void ListPattern::CheckAndUpdateAnimateTo(float relativeOffset, float prevOffset)
{
    if (!scrollTarget_) {
        return;
    }
    auto& target = scrollTarget_.value();
    auto posInfo = posMap_->GetPositionInfo(target.index);
    if (Negative(posInfo.mainPos)) {
        return;
    }
    float startPos = posInfo.mainPos - currentOffset_;
    float targetPos = 0.0f;
    GetListItemAnimatePos(startPos + target.extraOffset, startPos + posInfo.mainSize + target.extraOffset,
        target.align, targetPos);
    targetPos += currentOffset_;
    const float epsilon = 0.1f;
    if (!NearEqual(relativeOffset + prevOffset, currentOffset_, epsilon) ||
        !NearEqual(target.targetOffset, targetPos, epsilon)) {
        target.targetOffset = targetPos;
        if (NearEqual(currentOffset_, targetPos)) {
            StopAnimate();
        } else {
            AnimateTo(targetPos, -1, nullptr, true, false, false);
        }
    }
}

void ListPattern::CalculateCurrentOffset(float delta, const ListLayoutAlgorithm::PositionMap& recycledItemPosition)
{
    posMap_->UpdateTotalCount(maxListItemIndex_ + 1);
    if (itemPosition_.empty()) {
        return;
    }
    auto itemPos = itemPosition_;
    for (auto& [index, pos] : recycledItemPosition) {
        itemPos.try_emplace(index, pos);
    }
    float startPos = itemPos.begin()->second.startPos;
    int32_t startIndex = itemPos.begin()->first;
    auto& groupInfo = itemPos.begin()->second.groupInfo;
    bool groupAtStart = (!groupInfo || groupInfo.value().atStart);
    if (startIndex == 0 && groupAtStart) {
        // startPos has a small accuracy error.
        currentOffset_ = NearZero(startPos) ? 0.0f : -startPos;
        UpdatePosMap(itemPos);
        return;
    }
    currentOffset_ += delta;
    auto res = posMap_->GetStartIndexAndPos();
    if (res.first >= 0) {
        auto iter = itemPos.lower_bound(res.first);
        // skip same line for lanes
        if (iter->first == res.first && iter != itemPos.end()) {
            do {
                startPos = iter->second.startPos;
                iter++;
            } while (iter != itemPos.end() && NearEqual(iter->second.startPos, startPos));
        }
        if (iter != itemPos.end()) {
            groupAtStart = iter->second.groupInfo ? iter->second.groupInfo.value().atStart : true;
            startPos = iter->second.startPos;
            posMap_->UpdatePosMapStart(delta, currentOffset_, spaceWidth_, iter->first, startPos, groupAtStart);
        }
    }
    UpdatePosMap(itemPos);
}

void ListPattern::UpdatePosMap(const ListLayoutAlgorithm::PositionMap& itemPos)
{
    for (auto& [index, pos] : itemPos) {
        float height = pos.endPos - pos.startPos;
        if (pos.groupInfo) {
            bool groupAtStart = pos.groupInfo.value().atStart;
            if (groupAtStart) {
                posMap_->UpdatePos(index, { currentOffset_ + pos.startPos, height, pos.isGroup });
            } else {
                posMap_->UpdatePosWithCheck(index, { currentOffset_ + pos.startPos, height, pos.isGroup });
            }
        } else {
            posMap_->UpdatePos(index, { currentOffset_ + pos.startPos, height, pos.isGroup });
        }
    }
    auto& endGroupInfo = itemPos.rbegin()->second.groupInfo;
    bool groupAtEnd = (!endGroupInfo || endGroupInfo.value().atEnd);
    posMap_->UpdatePosMapEnd(itemPos.rbegin()->first, spaceWidth_, groupAtEnd);
}

void ListPattern::UpdateChildPosInfo(int32_t index, float delta, float sizeChange)
{
    if (itemPosition_.find(index) == itemPosition_.end()) {
        return;
    }
    auto posInfo = posMap_->GetPositionInfo(index);
    auto prevPosInfo = posMap_->GetPositionInfo(index - 1);
    delta = isStackFromEnd_ ? -(delta + sizeChange) : delta;
    if (Negative(prevPosInfo.mainPos)) {
        posMap_->UpdatePos(index, {posInfo.mainPos + delta, posInfo.mainSize + sizeChange, posInfo.isGroup});
    }
    if (index == GetStartIndex()) {
        sizeChange += delta;
        float startPos = itemPosition_.begin()->second.startPos;
        auto iter = itemPosition_.begin();
        while (iter != itemPosition_.end() && NearEqual(startPos, iter->second.startPos)) {
            iter->second.startPos += delta;
            iter++;
        }
    }
    if (index == GetEndIndex()) {
        float endPos = itemPosition_.rbegin()->second.endPos;
        auto iter = itemPosition_.rbegin();
        while (iter != itemPosition_.rend() && NearEqual(endPos, iter->second.endPos)) {
            iter->second.endPos += sizeChange;
            iter++;
        }
    }
    CalculateCurrentOffset(0.0f, ListLayoutAlgorithm::PositionMap());
}

void ListPattern::UpdateScrollBarOffset()
{
    CheckScrollBarOff();
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& geometryNode = host->GetGeometryNode();
    auto frameSize = geometryNode->GetFrameSize();
    Size size(frameSize.Width(), frameSize.Height());
    if (itemPosition_.empty()) {
        UpdateScrollBarRegion(0.f, 0.f, size, Offset(0.0f, 0.0f));
        return;
    }
    float currentOffset = 0.0f;
    float estimatedHeight = 0.0f;
    if (childrenSize_) {
        currentOffset = currentOffset_;
        estimatedHeight = listTotalHeight_;
    } else {
        auto calculate = ListHeightOffsetCalculator(itemPosition_, spaceWidth_, lanes_, GetAxis(), itemStartIndex_);
        calculate.SetPosMap(posMap_);
        calculate.GetEstimateHeightAndOffset(GetHost());
        currentOffset = calculate.GetEstimateOffset();
        estimatedHeight = calculate.GetEstimateHeight();
    }
    if (GetAlwaysEnabled()) {
        estimatedHeight = estimatedHeight - spaceWidth_;
    }

    // calculate padding offset of list
    auto layoutPriority = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutPriority);
    auto padding = layoutPriority->CreatePaddingAndBorder();
    auto paddingMain = GetAxis() == Axis::VERTICAL ? padding.Height() : padding.Width();

    auto mainSize = GetAxis() == Axis::VERTICAL ? size.Height() : size.Width();
    if (IsNeedAddContentOffset(LessOrEqual(estimatedHeight + paddingMain, mainSize))) {
        currentOffset += contentStartOffset_;
        estimatedHeight += contentStartOffset_ + contentEndOffset_;
    }

    UpdateScrollBarRegion(currentOffset, estimatedHeight + paddingMain, size, Offset(0.0f, 0.0f));
}

float ListPattern::GetTotalHeight() const
{
    auto currentOffset = GetTotalOffset();
    if (endIndex_ >= maxListItemIndex_) {
        return currentOffset + endMainPos_ + contentEndOffset_;
    }
    if (itemPosition_.empty()) {
        return 0.0f;
    }
    int32_t remainCount = maxListItemIndex_ - endIndex_;
    float itemsSize = itemPosition_.rbegin()->second.endPos - itemPosition_.begin()->second.startPos + spaceWidth_;
    float remainOffset = itemsSize / itemPosition_.size() * remainCount - spaceWidth_;
    return currentOffset + endMainPos_ + remainOffset + contentEndOffset_;
}

void ListPattern::TriggerModifyDone()
{
    OnModifyDone();
}

void ListPattern::SetChainAnimationCallback()
{
    CHECK_NULL_VOID(chainAnimation_);
    chainAnimation_->SetAnimationCallback([weak = AceType::WeakClaim(this)]() {
        auto list = weak.Upgrade();
        CHECK_NULL_VOID(list);
        list->MarkDirtyNodeSelf();
    });
    auto scrollEffect = AceType::DynamicCast<ScrollSpringEffect>(GetScrollEdgeEffect());
    CHECK_NULL_VOID(scrollEffect);
    scrollEffect->SetOnWillStartSpringCallback([weak = AceType::WeakClaim(this)]() {
        auto list = weak.Upgrade();
        CHECK_NULL_VOID(list);
        if (!list->dragFromSpring_ && list->chainAnimation_) {
            auto delta = list->chainAnimation_->SetControlIndex(list->IsAtTop() ? 0 : list->maxListItemIndex_);
            list->currentDelta_ -= delta;
            list->dragFromSpring_ = true;
        }
    });
}

void ListPattern::SetChainAnimation()
{
    auto listLayoutProperty = GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listLayoutProperty);
    auto edgeEffect = GetEdgeEffect();
    int32_t lanes = std::max(listLayoutProperty->GetLanes().value_or(1), 1);
    bool autoLanes = listLayoutProperty->HasLaneMinLength() || listLayoutProperty->HasLaneMaxLength();
    bool animation = listLayoutProperty->GetChainAnimation().value_or(false);
    bool enable = edgeEffect == EdgeEffect::SPRING && lanes == 1 && !autoLanes && animation;
    if (!enable || GetEffectEdge() != EffectEdge::ALL) {
        chainAnimation_.Reset();
        return;
    }
    auto space = listLayoutProperty->GetSpace().value_or(CHAIN_INTERVAL_DEFAULT).ConvertToPx();
    if (Negative(space)) {
        space = CHAIN_INTERVAL_DEFAULT.ConvertToPx();
    }
    if (!chainAnimation_ || (chainAnimation_ && space != chainAnimation_->GetSpace())) {
        springProperty_ =
            AceType::MakeRefPtr<SpringProperty>(CHAIN_SPRING_MASS, CHAIN_SPRING_STIFFNESS, CHAIN_SPRING_DAMPING);
        if (chainAnimationOptions_.has_value()) {
            float maxSpace = chainAnimationOptions_.value().maxSpace.ConvertToPx();
            float minSpace = chainAnimationOptions_.value().minSpace.ConvertToPx();
            minSpace = Negative(minSpace) ? 0.0f : minSpace;
            minSpace = GreatNotEqual(minSpace, space) ? space : minSpace;
            maxSpace = LessNotEqual(maxSpace, space) ? space : maxSpace;
            springProperty_->SetStiffness(chainAnimationOptions_.value().stiffness);
            springProperty_->SetDamping(chainAnimationOptions_.value().damping);
            chainAnimation_ = AceType::MakeRefPtr<ChainAnimation>(space, maxSpace, minSpace, springProperty_);
            auto conductivity = chainAnimationOptions_.value().conductivity;
            if (LessNotEqual(conductivity, 0) || GreatNotEqual(conductivity, 1)) {
                conductivity = ChainAnimation::DEFAULT_CONDUCTIVITY;
            }
            chainAnimation_->SetConductivity(conductivity);
            auto intensity = chainAnimationOptions_.value().intensity;
            if (LessNotEqual(intensity, 0) || GreatNotEqual(intensity, 1)) {
                intensity = ChainAnimation::DEFAULT_INTENSITY;
            }
            chainAnimation_->SetIntensity(intensity);
            auto effect = chainAnimationOptions_.value().edgeEffect;
            chainAnimation_->SetEdgeEffect(effect == 1 ? ChainEdgeEffect::STRETCH : ChainEdgeEffect::DEFAULT);
        } else {
            auto minSpace = space * DEFAULT_MIN_SPACE_SCALE;
            auto maxSpace = space * DEFAULT_MAX_SPACE_SCALE;
            chainAnimation_ = AceType::MakeRefPtr<ChainAnimation>(space, maxSpace, minSpace, springProperty_);
        }
        SetChainAnimationCallback();
    }
}

void ListPattern::SetChainAnimationOptions(const ChainAnimationOptions& options)
{
    chainAnimationOptions_ = options;
    if (chainAnimation_) {
        auto listLayoutProperty = GetLayoutProperty<ListLayoutProperty>();
        CHECK_NULL_VOID(listLayoutProperty);
        auto space = listLayoutProperty->GetSpace().value_or(CHAIN_INTERVAL_DEFAULT).ConvertToPx();
        if (Negative(space)) {
            space = CHAIN_INTERVAL_DEFAULT.ConvertToPx();
        }
        float maxSpace = options.maxSpace.ConvertToPx();
        float minSpace = options.minSpace.ConvertToPx();
        minSpace = Negative(minSpace) ? 0.0f : minSpace;
        minSpace = GreatNotEqual(minSpace, space) ? space : minSpace;
        maxSpace = LessNotEqual(maxSpace, space) ? space : maxSpace;
        chainAnimation_->SetSpace(space, maxSpace, minSpace);
        auto conductivity = chainAnimationOptions_.value().conductivity;
        if (LessNotEqual(conductivity, 0) || GreatNotEqual(conductivity, 1)) {
            conductivity = ChainAnimation::DEFAULT_CONDUCTIVITY;
        }
        chainAnimation_->SetConductivity(conductivity);
        auto intensity = chainAnimationOptions_.value().intensity;
        if (LessNotEqual(intensity, 0) || GreatNotEqual(intensity, 1)) {
            intensity = ChainAnimation::DEFAULT_INTENSITY;
        }
        chainAnimation_->SetIntensity(intensity);
        auto effect = options.edgeEffect;
        chainAnimation_->SetEdgeEffect(effect == 1 ? ChainEdgeEffect::STRETCH : ChainEdgeEffect::DEFAULT);
    }
    if (springProperty_) {
        springProperty_->SetStiffness(chainAnimationOptions_.value().stiffness);
        springProperty_->SetDamping(chainAnimationOptions_.value().damping);
    }
}

void ListPattern::OnTouchDown(const TouchEventInfo& info)
{
    ScrollablePattern::OnTouchDown(info);
    auto& touches = info.GetTouches();
    if (touches.empty()) {
        return;
    }
    auto offset = touches.front().GetLocalLocation();
    float startPosition = GetAxis() == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
    ProcessDragStart(startPosition);
}

void ListPattern::ProcessDragStart(float startPosition)
{
    CHECK_NULL_VOID(chainAnimation_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto globalOffset = host->GetTransformRelativeOffset();
    int32_t index = -1;
    auto offset = startPosition - GetMainAxisOffset(globalOffset, GetAxis());
    auto it = std::find_if(
        itemPosition_.begin(), itemPosition_.end(), [offset](auto pos) { return offset <= pos.second.endPos; });
    if (it != itemPosition_.end()) {
        index = it->first;
    } else if (!itemPosition_.empty()) {
        index = itemPosition_.rbegin()->first + 1;
    }
    dragFromSpring_ = false;
    float delta = chainAnimation_->SetControlIndex(index);
    currentDelta_ -= delta;
    chainAnimation_->SetMaxIndex(maxListItemIndex_);
}

void ListPattern::ProcessDragUpdate(float dragOffset, int32_t source)
{
    CHECK_NULL_VOID(chainAnimation_);
    if (source == SCROLL_FROM_BAR || source == SCROLL_FROM_AXIS || source == SCROLL_FROM_BAR_FLING) {
        return;
    }
    if (NeedScrollSnapAlignEffect()) {
        auto delta = 0.0f;
        if (chainAnimation_->GetControlIndex() < startIndex_ - 1) {
            delta = chainAnimation_->SetControlIndex(std::max(startIndex_ - 1, 0));
        }
        if (chainAnimation_->GetControlIndex() > endIndex_ + 1) {
            delta = chainAnimation_->SetControlIndex(std::min(endIndex_ + 1, maxListItemIndex_));
        }
        if (!NearZero(delta)) {
            auto scrollableEvent = GetScrollableEvent();
            CHECK_NULL_VOID(scrollableEvent);
            auto scrollable = scrollableEvent->GetScrollable();
            CHECK_NULL_VOID(scrollable);
            scrollable->UpdateScrollSnapStartOffset(delta);
            currentDelta_ -= delta;
        }
    }
    float overOffset = 0.0f;
    if (!itemPosition_.empty()) {
        auto res = GetOutBoundaryOffset(0.0f, true);
        overOffset = std::max(res.start, res.end);
        if (!NearZero(res.end)) {
            overOffset = -overOffset;
        }
    }
    if (source == SCROLL_FROM_UPDATE && !NearZero(overOffset)) {
        dragOffset = 0.0f;
    }
    chainAnimation_->SetDelta(-dragOffset, overOffset);
    if (source == SCROLL_FROM_UPDATE && GetCanOverScroll()) {
        float tempDelta = currentDelta_;
        currentDelta_ -= dragOffset;
        bool isAtEdge = IsAtTop() || IsAtBottom(true);
        currentDelta_ = tempDelta;
        SetCanOverScroll(isAtEdge);
    }
}

float ListPattern::GetChainDelta(int32_t index) const
{
    CHECK_NULL_RETURN(chainAnimation_, 0.0f);
    float chainDelta = chainAnimation_->GetValue(index);
    auto pipeline = GetContext();
    if (pipeline && pipeline->GetPixelRoundMode() == PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE) {
        chainDelta = Round(chainDelta);
    }
    return chainDelta;
}

void ListPattern::MultiSelectWithoutKeyboard(const RectF& selectedZone)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> childrens;
    host->GenerateOneDepthVisibleFrame(childrens);
    for (const auto& item : childrens) {
        if (item->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
            auto itemGroupPattern = item->GetPattern<ListItemGroupPattern>();
            CHECK_NULL_VOID(itemGroupPattern);
            auto itemGroupGeometry = item->GetGeometryNode();
            CHECK_NULL_VOID(itemGroupGeometry);
            auto itemGroupRect = itemGroupGeometry->GetFrameRect();
            if (!selectedZone.IsIntersectWith(itemGroupRect)) {
                continue;
            }
            HandleCardModeSelectedEvent(selectedZone, item, itemGroupRect.GetOffset());
            continue;
        }
        auto itemPattern = item->GetPattern<ListItemPattern>();
        CHECK_NULL_VOID(itemPattern);
        if (!itemPattern->Selectable()) {
            continue;
        }

        auto itemGeometry = item->GetGeometryNode();
        CHECK_NULL_VOID(itemGeometry);

        auto itemRect = itemGeometry->GetFrameRect();
        if (!selectedZone.IsIntersectWith(itemRect)) {
            itemPattern->MarkIsSelected(false);
        } else {
            itemPattern->MarkIsSelected(true);
        }
    }

    DrawSelectedZone(selectedZone);
}

void ListPattern::HandleCardModeSelectedEvent(
    const RectF& selectedZone, const RefPtr<FrameNode>& itemGroupNode, const OffsetF& groupOffset)
{
    CHECK_NULL_VOID(itemGroupNode);
    std::list<RefPtr<FrameNode>> childrens;
    itemGroupNode->GenerateOneDepthVisibleFrame(childrens);
    for (const auto& item : childrens) {
        auto itemPattern = item->GetPattern<ListItemPattern>();
        if (!itemPattern) {
            continue;
        }
        if (!itemPattern->Selectable()) {
            continue;
        }
        auto itemGeometry = item->GetGeometryNode();
        CHECK_NULL_VOID(itemGeometry);
        auto context = item->GetRenderContext();
        CHECK_NULL_VOID(context);
        auto itemRect = itemGeometry->GetFrameRect();
        RectF itemRectInGroup(itemRect.GetX() + groupOffset.GetX(),
            itemRect.GetY() + groupOffset.GetY(), itemRect.Width(), itemRect.Height());
        if (!selectedZone.IsIntersectWith(itemRectInGroup)) {
            itemPattern->MarkIsSelected(false);
        } else {
            itemPattern->MarkIsSelected(true);
        }
    }
}

void ListPattern::ClearMultiSelect()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> children;
    host->GenerateOneDepthAllFrame(children);
    for (const auto& child : children) {
        if (!child) {
            continue;
        }
        auto itemPattern = child->GetPattern<ListItemPattern>();
        if (itemPattern) {
            itemPattern->MarkIsSelected(false);
            continue;
        }
        auto itemGroupPattern = child->GetPattern<ListItemGroupPattern>();
        if (itemGroupPattern) {
            std::list<RefPtr<FrameNode>> itemChildren;
            child->GenerateOneDepthAllFrame(itemChildren);
            for (const auto& item : itemChildren) {
                if (!item) {
                    continue;
                }
                itemPattern = item->GetPattern<ListItemPattern>();
                if (itemPattern) {
                    itemPattern->MarkIsSelected(false);
                }
            }
        }
    }

    ClearSelectedZone();
}

bool ListPattern::IsItemSelected(float offsetX, float offsetY)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto node = host->FindChildByPosition(offsetX, offsetY);
    CHECK_NULL_RETURN(node, false);
    auto itemPattern = node->GetPattern<ListItemPattern>();
    if (itemPattern) {
        return itemPattern->IsSelected();
    }
    auto itemGroupPattern = node->GetPattern<ListItemGroupPattern>();
    if (itemGroupPattern) {
        auto itemNode = node->FindChildByPosition(offsetX, offsetY);
        CHECK_NULL_RETURN(itemNode, false);
        itemPattern = itemNode->GetPattern<ListItemPattern>();
        CHECK_NULL_RETURN(itemPattern, false);
        return itemPattern->IsSelected();
    }
    return false;
}

void ListPattern::SetSwiperItem(WeakPtr<ListItemPattern> swiperItem)
{
    // swiper item only can be replaced when no other items be dragged
    if (canReplaceSwiperItem_) {
        if (swiperItem != swiperItem_) {
            auto item = swiperItem_.Upgrade();
            if (item) {
                item->ResetSwipeStatus();
            }
            swiperItem_ = std::move(swiperItem);
        }
        canReplaceSwiperItem_ = false;
    }
    FireAndCleanScrollingListener();
}

int32_t ListPattern::GetItemIndexByPosition(float xOffset, float yOffset)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, GetStartIndex());
    auto listProperty = GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listProperty, GetStartIndex());
    auto globalOffset = host->GetTransformRelativeOffset();
    float relativeX = xOffset - globalOffset.GetX();
    float relativeY = yOffset - globalOffset.GetY();
    float mainOffset = GetAxis() == Axis::VERTICAL ? relativeY : relativeX;
    float crossOffset = GetAxis() == Axis::VERTICAL ? relativeX : relativeY;
    float mainSize = GetMainAxisSize(GetContentSize(), GetAxis());
    float crossSize = GetCrossAxisSize(GetContentSize(), GetAxis());
    if (TextDirection::RTL == listProperty->GetNonAutoLayoutDirection()) {
        if (Axis::VERTICAL == GetAxis()) {
            crossOffset = crossSize - crossOffset;
        } else {
            mainOffset = mainSize - mainOffset;
        }
    }
    int32_t lanesOffset = 0;
    if (lanes_ > 1 && !NearZero(crossSize + laneGutter_)) {
        lanesOffset = static_cast<int32_t>(crossOffset / ((crossSize + laneGutter_) / lanes_));
    }
    for (auto& pos : itemPosition_) {
        if (mainOffset <= pos.second.endPos + spaceWidth_ / 2) { /* 2:half */
            return std::min(pos.first + lanesOffset, maxListItemIndex_ + 1);
        }
    }
    if (!itemPosition_.empty()) {
        return itemPosition_.rbegin()->first + 1;
    }
    return 0;
}

void ListPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    ScrollablePattern::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("multiSelectable", multiSelectable_, filter);
    json->PutExtAttr("startIndex", startIndex_, filter);
    if (!itemPosition_.empty()) {
        json->PutExtAttr("itemStartPos", itemPosition_.begin()->second.startPos, filter);
    }
    json->PutExtAttr("maintainVisibleContentPosition", maintainVisibleContentPosition_, filter);
    auto nestedScrollOptions = JsonUtil::Create(true);
    auto nestedScroll = GetNestedScroll();
    nestedScrollOptions->Put("scrollForward", nestedScroll.GetNestedScrollModeStr(nestedScroll.forward).c_str());
    nestedScrollOptions->Put("scrollBackward", nestedScroll.GetNestedScrollModeStr(nestedScroll.backward).c_str());
    json->PutExtAttr("nestedScroll", nestedScrollOptions, filter);
}

void ListPattern::FromJson(const std::unique_ptr<JsonValue>& json)
{
    ScrollToIndex(json->GetInt("startIndex"));
    if (json->Contains("itemStartPos")) {
        ScrollBy(-json->GetDouble("itemStartPos"));
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->UpdateClipEdge(true);
    ScrollablePattern::FromJson(json);
}

ListItemGroupPara ListPattern::GetListItemGroupParameter(const RefPtr<FrameNode>& node)
{
    ListItemGroupPara listItemGroupPara = { -1, -1, -1, -1 };
    auto curFrameParent = node->GetParent();
    auto curFrameParentNode = AceType::DynamicCast<FrameNode>(curFrameParent);
    while (curFrameParent && (!curFrameParentNode)) {
        curFrameParent = curFrameParent->GetParent();
        curFrameParentNode = AceType::DynamicCast<FrameNode>(curFrameParent);
    }
    CHECK_NULL_RETURN(curFrameParentNode, listItemGroupPara);
    if (curFrameParent->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
        auto itemGroupPattern = curFrameParentNode->GetPattern<ListItemGroupPattern>();
        CHECK_NULL_RETURN(itemGroupPattern, listItemGroupPara);
        listItemGroupPara.displayEndIndex = itemGroupPattern->GetDisplayEndIndexInGroup();
        listItemGroupPara.displayStartIndex = itemGroupPattern->GetDisplayStartIndexInGroup();
        listItemGroupPara.lanes = itemGroupPattern->GetLanesInGroup();
        listItemGroupPara.itemEndIndex = itemGroupPattern->GetEndIndexInGroup();
        listItemGroupPara.hasHeader = itemGroupPattern->IsHasHeader();
        listItemGroupPara.hasFooter = itemGroupPattern->IsHasFooter();
    }
    return listItemGroupPara;
}

bool ListPattern::IsListItemGroup(int32_t listIndex, RefPtr<FrameNode>& node)
{
    auto listFrame = GetHost();
    CHECK_NULL_RETURN(listFrame, false);
    auto listFocus = listFrame->GetFocusHub();
    CHECK_NULL_RETURN(listFocus, false);
    bool isItemGroup = false;
    listFocus->AnyChildFocusHub([&isItemGroup, &node, listIndex](const RefPtr<FocusHub>& childFocus) {
        if (!childFocus->IsFocusable()) {
            return false;
        }
        if (auto childFrame = childFocus->GetFrameNode()) {
            if (auto childPattern = AceType::DynamicCast<ListItemPattern>(childFrame->GetPattern())) {
                auto curIndex = childPattern->GetIndexInList();
                auto curIndexInGroup = childPattern->GetIndexInListItemGroup();
                if (curIndex == listIndex) {
                    node = childFrame;
                    isItemGroup = curIndexInGroup > -1;
                    return true;
                }
            }
        }
        return false;
    });
    return isItemGroup;
}

void ListPattern::RefreshLanesItemRange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto updatePos = host->GetChildrenUpdated();
    if (updatePos == -1) {
        return;
    }
    host->ChildrenUpdatedFrom(-1);
    if (updatePos == 0) {
        lanesItemRange_.clear();
        return;
    }
    for (auto it = lanesItemRange_.begin(); it != lanesItemRange_.end();) {
        if (it->second < updatePos) {
            it++;
        } else if (it->first >= updatePos) {
            it = lanesItemRange_.erase(it);
        } else {
            it->second = updatePos - 1;
            it++;
        }
    }
}

std::string ListPattern::ProvideRestoreInfo()
{
    return std::to_string(startIndex_);
}

void ListPattern::CloseAllSwipeActions(OnFinishFunc&& onFinishCallback)
{
    auto item = swiperItem_.Upgrade();
    if (item) {
        return item->CloseSwipeAction(std::move(onFinishCallback));
    }
}

void ListPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    jumpIndex_ = StringUtils::StringToInt(restoreInfo);
}

void ListPattern::DumpAdvanceInfo()
{
    ScrollablePattern::DumpAdvanceInfo();
    DumpLog::GetInstance().AddDesc("maxListItemIndex:" + std::to_string(maxListItemIndex_));
    DumpLog::GetInstance().AddDesc("startIndex:" + std::to_string(startIndex_));
    DumpLog::GetInstance().AddDesc("endIndex:" + std::to_string(endIndex_));
    DumpLog::GetInstance().AddDesc("centerIndex:" + std::to_string(centerIndex_));
    DumpLog::GetInstance().AddDesc("startMainPos:" + std::to_string(startMainPos_));
    DumpLog::GetInstance().AddDesc("endMainPos:" + std::to_string(endMainPos_));
    DumpLog::GetInstance().AddDesc("currentOffset:" + std::to_string(currentOffset_));
    DumpLog::GetInstance().AddDesc("contentMainSize:" + std::to_string(contentMainSize_));
    DumpLog::GetInstance().AddDesc("contentStartOffset:" + std::to_string(contentStartOffset_));
    DumpLog::GetInstance().AddDesc("contentEndOffset:" + std::to_string(contentEndOffset_));
    DumpLog::GetInstance().AddDesc("currentDelta:" + std::to_string(currentDelta_));
    DumpLog::GetInstance().AddDesc("stackFromEnd:" + std::to_string(isStackFromEnd_));
    crossMatchChild_ ? DumpLog::GetInstance().AddDesc("crossMatchChild:true")
                     : DumpLog::GetInstance().AddDesc("crossMatchChild:false");
    smooth_ ? DumpLog::GetInstance().AddDesc("smooth:true") : DumpLog::GetInstance().AddDesc("smooth:false");
    if (jumpIndex_.has_value()) {
        DumpLog::GetInstance().AddDesc("jumpIndex:" + std::to_string(jumpIndex_.value()));
    } else {
        DumpLog::GetInstance().AddDesc("jumpIndex:null");
    }
    if (jumpIndexInGroup_.has_value()) {
        DumpLog::GetInstance().AddDesc("jumpIndexInGroup:" + std::to_string(jumpIndexInGroup_.value()));
    } else {
        DumpLog::GetInstance().AddDesc("jumpIndexInGroup:null");
    }
    if (targetIndex_.has_value()) {
        DumpLog::GetInstance().AddDesc("targetIndex:" + std::to_string(targetIndex_.value()));
    } else {
        DumpLog::GetInstance().AddDesc("targetIndex:null");
    }
    if (predictSnapOffset_.has_value()) {
        DumpLog::GetInstance().AddDesc("predictSnapOffset:" + std::to_string(predictSnapOffset_.value()));
    } else {
        DumpLog::GetInstance().AddDesc("predictSnapOffset:null");
    }
    if (predictSnapEndPos_.has_value()) {
        DumpLog::GetInstance().AddDesc("predictSnapEndPos:" + std::to_string(predictSnapEndPos_.value()));
    } else {
        DumpLog::GetInstance().AddDesc("predictSnapEndPos:null");
    }
    // DumpLog::GetInstance().AddDesc("scrollAlign:%{public}d", scrollAlign_);
    paintStateFlag_ ? DumpLog::GetInstance().AddDesc("paintStateFlag:true")
                    : DumpLog::GetInstance().AddDesc("paintStateFlag:false");
    isFramePaintStateValid_ ? DumpLog::GetInstance().AddDesc("isFramePaintStateValid:true")
                            : DumpLog::GetInstance().AddDesc("isFramePaintStateValid:false");
    for (auto item : itemPosition_) {
        DumpLog::GetInstance().AddDesc("------------------------------------------");
        DumpLog::GetInstance().AddDesc("itemPosition.first:" + std::to_string(item.first));
        DumpLog::GetInstance().AddDesc("startPos:" + std::to_string(item.second.startPos));
        DumpLog::GetInstance().AddDesc("endPos:" + std::to_string(item.second.endPos));
        DumpLog::GetInstance().AddDesc("isGroup:" + std::to_string(item.second.isGroup));
    }
    DumpLog::GetInstance().AddDesc("------------------------------------------");
    scrollStop_ ? DumpLog::GetInstance().AddDesc("scrollStop:true")
                : DumpLog::GetInstance().AddDesc("scrollStop:false");
    for (auto item : lanesItemRange_) {
        DumpLog::GetInstance().AddDesc("------------------------------------------");
        DumpLog::GetInstance().AddDesc("lanesItemRange.first:" + std::to_string(item.first));
        DumpLog::GetInstance().AddDesc("lanesItemRange.second:" + std::to_string(item.second));
    }
    DumpLog::GetInstance().AddDesc("------------------------------------------");
    DumpLog::GetInstance().AddDesc("lanes:" + std::to_string(lanes_));
    DumpLog::GetInstance().AddDesc("laneGutter:" + std::to_string(laneGutter_));
    dragFromSpring_ ? DumpLog::GetInstance().AddDesc("dragFromSpring:true")
                    : DumpLog::GetInstance().AddDesc("dragFromSpring:false");
    isScrollEnd_ ? DumpLog::GetInstance().AddDesc("isScrollEnd:true")
                 : DumpLog::GetInstance().AddDesc("isScrollEnd:false");
    IsAtTop() ? DumpLog::GetInstance().AddDesc("IsAtTop:true") : DumpLog::GetInstance().AddDesc("IsAtTop:false");
    IsAtBottom() ? DumpLog::GetInstance().AddDesc("IsAtBottom:true")
                 : DumpLog::GetInstance().AddDesc("IsAtBottom:false");
}

void ListPattern::GetEventDumpInfo()
{
    ScrollablePattern::GetEventDumpInfo();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetOrCreateEventHub<ListEventHub>();
    CHECK_NULL_VOID(hub);
    auto onScrollIndex = hub->GetOnScrollIndex();
    onScrollIndex ? DumpLog::GetInstance().AddDesc("hasOnScrollIndex: true")
                  : DumpLog::GetInstance().AddDesc("hasOnScrollIndex: false");
    auto onJSFrameNodeScrollIndex = hub->GetJSFrameNodeOnListScrollIndex();
    onJSFrameNodeScrollIndex ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollIndex: true")
                             : DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollIndex: false");
    auto onScrollVisibleContentChange = hub->GetOnScrollVisibleContentChange();
    onScrollVisibleContentChange ? DumpLog::GetInstance().AddDesc("hasOnScrollVisibleContentChange: true")
                                 : DumpLog::GetInstance().AddDesc("hasOnScrollVisibleContentChange: false");
    auto onJSFrameNodeScrollVisibleContentChange = hub->GetJSFrameNodeOnScrollVisibleContentChange();
    onJSFrameNodeScrollVisibleContentChange
        ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollVisibleContentChange: true")
        : DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollVisibleContentChange: false");
}

void ListPattern::GetEventDumpInfo(std::unique_ptr<JsonValue>& json)
{
    ScrollablePattern::GetEventDumpInfo(json);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetOrCreateEventHub<ListEventHub>();
    CHECK_NULL_VOID(hub);
    auto onScrollIndex = hub->GetOnScrollIndex();
    json->Put("hasOnScrollIndex", onScrollIndex ? "true" : "false");
    auto onJSFrameNodeScrollIndex = hub->GetJSFrameNodeOnListScrollIndex();
    json->Put("hasFrameNodeOnScrollIndex", onJSFrameNodeScrollIndex ? "true" : "false");

    auto onScrollVisibleContentChange = hub->GetOnScrollVisibleContentChange();
    json->Put("hasOnScrollVisibleContentChange", onScrollVisibleContentChange ? "true" : "false");
    auto onJSFrameNodeScrollVisibleContentChange = hub->GetJSFrameNodeOnScrollVisibleContentChange();
    json->Put("hasFrameNodeOnScrollVisibleContentChange", onJSFrameNodeScrollVisibleContentChange ? "true" : "false");
}

DisplayMode ListPattern::GetDefaultScrollBarDisplayMode() const
{
    auto defaultDisplayMode = DisplayMode::OFF;
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        defaultDisplayMode = DisplayMode::AUTO;
    }
    return defaultDisplayMode;
}

std::vector<RefPtr<FrameNode>> ListPattern::GetVisibleSelectedItems()
{
    std::vector<RefPtr<FrameNode>> children;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, children);
    for (int32_t index = startIndex_; index <= endIndex_; ++index) {
        auto item = host->GetChildByIndex(index + itemStartIndex_);
        if (!AceType::InstanceOf<FrameNode>(item)) {
            continue;
        }
        auto itemFrameNode = AceType::DynamicCast<FrameNode>(item);
        auto itemPattern = itemFrameNode->GetPattern<ListItemPattern>();
        if (!itemPattern) {
            continue;
        }
        if (!itemPattern->IsSelected()) {
            continue;
        }
        children.emplace_back(itemFrameNode);
    }
    return children;
}

RefPtr<ListChildrenMainSize> ListPattern::GetOrCreateListChildrenMainSize()
{
    if (childrenSize_) {
        return childrenSize_;
    }
    childrenSize_ = AceType::MakeRefPtr<ListChildrenMainSize>();
    auto callback = [weakPattern = WeakClaim(this)](std::tuple<int32_t, int32_t, int32_t> change, ListChangeFlag flag) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto context = pattern->GetContext();
        CHECK_NULL_VOID(context);
        context->AddBuildFinishCallBack([weakPattern, change, flag]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnChildrenSizeChanged(change, flag);
        });
        context->RequestFrame();
    };
    childrenSize_->SetOnDataChange(callback);
    auto pipeline = GetContext();
    if (pipeline && pipeline->GetPixelRoundMode() == PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE) {
        childrenSize_->SetIsRoundingMode();
    }
    return childrenSize_;
}

void ListPattern::OnChildrenSizeChanged(std::tuple<int32_t, int32_t, int32_t> change, ListChangeFlag flag)
{
    if (!posMap_) {
        posMap_ = MakeRefPtr<ListPositionMap>();
    }
    posMap_->MarkDirty(flag);
    MarkDirtyNodeSelf();
}

void ListPattern::SetListChildrenMainSize(float defaultSize, const std::vector<float>& mainSize)
{
    childrenSize_ = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, defaultSize);
    OnChildrenSizeChanged({ -1, -1, -1 }, LIST_UPDATE_CHILD_SIZE);
    auto pipeline = GetContext();
    if (pipeline && pipeline->GetPixelRoundMode() == PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE) {
        childrenSize_->SetIsRoundingMode();
    }
}

void ListPattern::ResetChildrenSize()
{
    if (childrenSize_) {
        childrenSize_ = nullptr;
        MarkDirtyNodeSelf();
        OnChildrenSizeChanged({ -1, -1, -1 }, LIST_UPDATE_CHILD_SIZE);
    }
}

void ListPattern::OnScrollVisibleContentChange(const RefPtr<ListEventHub>& listEventHub, bool indexChanged)
{
    CHECK_NULL_VOID(listEventHub);
    bool startChanged = UpdateStartListItemIndex();
    bool endChanged = UpdateEndListItemIndex();
    auto onScrollVisibleContentChange = listEventHub->GetOnScrollVisibleContentChange();
    auto OnJSFrameNodeScrollVisibleContentChange = listEventHub->GetJSFrameNodeOnScrollVisibleContentChange();
    if (onScrollVisibleContentChange) {
        if (indexChanged || startChanged || endChanged) {
            onScrollVisibleContentChange(startInfo_, endInfo_);
            ReportOnItemListScrollEvent("onScrollVisibleContentChange", startInfo_.index, endInfo_.index);
        }
    }
    if (OnJSFrameNodeScrollVisibleContentChange) {
        if (indexChanged || startChanged || endChanged) {
            OnJSFrameNodeScrollVisibleContentChange(startInfo_, endInfo_);
        }
    }
}

float ListPattern::GetScrollUpdateFriction(float overScroll)
{
    return ScrollablePattern::CalculateFriction(std::abs(overScroll) / contentMainSize_);
}

void ListPattern::NotifyDataChange(int32_t index, int32_t count)
{
    if (!maintainVisibleContentPosition_ || itemPosition_.empty() || count == 0) {
        return;
    }
    if (index == 0 && count > 0 && IsBackToTopRunning()) {
        SetUseTotalOffset(false);
    }
    auto startIndex = itemPosition_.begin()->first;
    auto endIndex = itemPosition_.rbegin()->first;
    if (!CheckDataChangeOutOfStart(index, count, startIndex, endIndex)) {
        return;
    }
    count = !isStackFromEnd_ ? std::max(count, index - startIndex) : - std::max(count, endIndex - index);
    int32_t mod = 0;
    if (count < 0 && lanes_ > 1 && !(itemPosition_.begin()->second.isGroup)) {
        mod = -count % lanes_;
    }
    auto prevPosMap = std::move(itemPosition_);
    for (auto &pos : prevPosMap) {
        if (mod > 0) {
            mod--;
        } else {
            itemPosition_[pos.first + count] = pos.second;
        }
    }
    needReEstimateOffset_ = true;
}

bool ListPattern::CheckDataChangeOutOfStart(int32_t index, int32_t count, int32_t startIndex, int32_t endIndex)
{
    if (((count > 0 && index > startIndex) || (count < 0 && index >= startIndex)) && !isStackFromEnd_) {
        return false;
    }
    if (((count > 0 && index < endIndex) || (count < 0 && index <= endIndex)) && isStackFromEnd_) {
        return false;
    }
    return true;
}

void ListPattern::CreatePositionInfo(std::unique_ptr<JsonValue>& json)
{
    std::unique_ptr<JsonValue> children = JsonUtil::CreateArray(true);
    for (auto item : itemPosition_) {
        std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
        child->Put("itemPosition.first", std::to_string(item.first).c_str());
        child->Put("startPos", std::to_string(item.second.startPos).c_str());
        child->Put("endPos", std::to_string(item.second.endPos).c_str());
        child->Put("isGroup", std::to_string(item.second.isGroup).c_str());
        children->Put(child);
    }
    json->Put("itemPosition", children);
}

void ListPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    ScrollablePattern::DumpAdvanceInfo(json);
    json->Put("maxListItemIndex", maxListItemIndex_);
    json->Put("startIndex", startIndex_);
    json->Put("endIndex", endIndex_);
    json->Put("centerIndex", centerIndex_);
    json->Put("startMainPos", startMainPos_);
    json->Put("endMainPos", endMainPos_);
    json->Put("currentOffset", currentOffset_);
    json->Put("contentMainSize", contentMainSize_);
    json->Put("contentStartOffset", contentStartOffset_);
    json->Put("contentEndOffset", contentEndOffset_);
    json->Put("currentDelta", currentDelta_);
    json->Put("crossMatchChild", crossMatchChild_);
    json->Put("smooth", smooth_);
    json->Put("jumpIndex", jumpIndex_.has_value() ? std::to_string(jumpIndex_.value()).c_str() : "null");
    json->Put(
        "jumpIndexInGroup", jumpIndexInGroup_.has_value() ? std::to_string(jumpIndexInGroup_.value()).c_str() : "null");
    json->Put("targetIndex", targetIndex_.has_value() ? std::to_string(targetIndex_.value()).c_str() : "null");
    json->Put("predictSnapOffset",
        predictSnapOffset_.has_value() ? std::to_string(predictSnapOffset_.value()).c_str() : "null");
    json->Put("predictSnapEndPos",
        predictSnapEndPos_.has_value() ? std::to_string(predictSnapEndPos_.value()).c_str() : "null");
    json->Put("paintStateFlag", paintStateFlag_);
    json->Put("isFramePaintStateValid", isFramePaintStateValid_);
    CreatePositionInfo(json);
    json->Put("scrollStop", scrollStop_);
    std::unique_ptr<JsonValue> lanesChildrenArray = JsonUtil::CreateArray(true);
    for (auto item : lanesItemRange_) {
        std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
        child->Put("lanesItemRange.first", std::to_string(item.first).c_str());
        child->Put("lanesItemRange.second", std::to_string(item.second).c_str());
        lanesChildrenArray->Put(child);
    }
    json->Put("lanesItemRange", lanesChildrenArray);
    json->Put("lanes", std::to_string(lanes_).c_str());
    json->Put("laneGutter", std::to_string(laneGutter_).c_str());
    json->Put("dragFromSpring", dragFromSpring_);
    json->Put("isScrollEnd", isScrollEnd_);
    json->Put("IsAtTop", IsAtTop());
    json->Put("IsAtBottom", IsAtBottom());
}

SizeF ListPattern::GetChildrenExpandedSize()
{
    auto viewSize = GetViewSizeMinusPadding();
    auto axis = GetAxis();
    float estimatedHeight = 0.0f;
    if (childrenSize_) {
        estimatedHeight = listTotalHeight_;
    } else if (!itemPosition_.empty()) {
        auto calculate = ListHeightOffsetCalculator(itemPosition_, spaceWidth_, lanes_, axis, itemStartIndex_);
        calculate.SetPosMap(posMap_);
        calculate.GetEstimateHeightAndOffset(GetHost());
        estimatedHeight = calculate.GetEstimateHeight();
    }

    if (axis == Axis::VERTICAL) {
        return SizeF(viewSize.Width(), estimatedHeight);
    } else if (axis == Axis::HORIZONTAL) {
        return SizeF(estimatedHeight, viewSize.Height());
    }
    return SizeF();
}

bool ListPattern::LayoutItemInGroupForFocus(int32_t indexInList, int32_t nextIndexInGroup, int32_t curIndexInGroup,
    ListItemGroupPara listItemGroupPara, int32_t maxListItemIndex)
{
    // nextIndexInGroup = -1 indicates the current position is Header; nextIndexInGroup = maxListItemIndex indicates the
    // current position is Footer.
    // Header and Footer will always be laid out, directly return true.
    if (nextIndexInGroup == -1 || nextIndexInGroup == maxListItemIndex) {
        return true;
    }
    ScrollAlign align = ScrollAlign::AUTO;
    // The second "||" condition indicates that currently only the footer or header is displayed,
    // without displaying any ListItems.
    if ((nextIndexInGroup < curIndexInGroup && nextIndexInGroup < listItemGroupPara.displayStartIndex) ||
        (nextIndexInGroup < curIndexInGroup &&
            listItemGroupPara.displayStartIndex == listItemGroupPara.displayEndIndex)) {
        align = ScrollAlign::START;
    } else if ((nextIndexInGroup > curIndexInGroup && nextIndexInGroup > listItemGroupPara.displayEndIndex) ||
               (nextIndexInGroup > curIndexInGroup &&
                   listItemGroupPara.displayStartIndex == listItemGroupPara.displayEndIndex)) {
        align = ScrollAlign::END;
    } else {
        return true;
    }

    if (!IsLayout(indexInList, nextIndexInGroup, align)) {
        // Do the Layout for indexInList
        isLayoutListForFocus_ = true;
        targetIndex_ = indexInList;
        targetIndexInGroup_ = nextIndexInGroup;
        scrollAlign_ = align;
        auto pipeline = GetContext();
        CHECK_NULL_RETURN(pipeline, false);
        MarkDirtyNodeSelf();
        pipeline->FlushUITasks();
        return false;
    }
    return true;
}

bool ListPattern::LayoutListForFocus(int32_t nextIndex, int32_t curIndex)
{
    if (!IsLayout(nextIndex, std::nullopt, ScrollAlign::AUTO)) {
        isLayoutListForFocus_ = true;
        targetIndex_ = nextIndex;
        if (nextIndex < startIndex_) {
            scrollAlign_ = ScrollAlign::START;
        } else if (nextIndex > endIndex_) {
            scrollAlign_ = ScrollAlign::END;
        }
        auto pipeline = GetContext();
        CHECK_NULL_RETURN(pipeline, false);
        MarkDirtyNodeSelf();
        pipeline->FlushUITasks();
        return false;
    }

    return true;
}

bool ListPattern::IsLayout(int32_t index, std::optional<int32_t> indexInGroup, ScrollAlign align)
{
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto iter = itemPosition_.find(index);
    if (iter == itemPosition_.end()) {
        return false;
    }
    float targetPos = 0.0f;
    if (iter->second.isGroup) {
        if (indexInGroup.has_value()) {
            if (!GetListItemGroupAnimatePosWithIndexInGroup(
                index, indexInGroup.value(), iter->second.startPos, align, targetPos)) {
                return false;
            }
        } else {
            if (!GetListItemGroupAnimatePosWithoutIndexInGroup(
                index, iter->second.startPos, iter->second.endPos, align, targetPos)) {
                return false;
            }
        }
    }
    return true;
}

int32_t ListPattern::GetNextMoveStepForMultiLanes(
    int32_t curIndex, FocusStep focusStep, bool isVertical, int32_t& nextIndex)
{
    // Only for DetermineMultiLaneStep.
    // In mixed layout scenarios(List include ListItem and ListItemGroup), when increment nextIndex, if during the loop
    // a ListItemGroup is encountered, move to this ListItemGroup directly.

    // Check if focusStep is within a valid range.
    bool isDown = true;
    if ((isVertical && (focusStep == FocusStep::DOWN)) || (!isVertical && focusStep == FocusStep::RIGHT)) {
        isDown = true;
    } else if ((isVertical && focusStep == FocusStep::UP) || (!isVertical && focusStep == FocusStep::LEFT)) {
        isDown = false;
    } else {
        return -1;
    }

    // Determine moveStep and loop range based on focusStep.
    int32_t moveStep = isDown ? lanes_ : -lanes_;
    int32_t loopStart = isDown ? curIndex + 1 : curIndex - 1;
    int32_t loopEnd = isDown ? curIndex + lanes_ - 1 : curIndex - lanes_ + 1;
    int32_t loopStep = isDown ? 1 : -1;

    for (int32_t loopIndex = loopStart; loopStep > 0 ? loopIndex <= loopEnd : loopIndex >= loopEnd;
        loopIndex += loopStep) {
        // Check if the index exists in itemPosition_ and cachedItemPosition_.
        auto it = itemPosition_.find(loopIndex);
        auto itCache = cachedItemPosition_.find(loopIndex);
        if (it == itemPosition_.end() && itCache == cachedItemPosition_.end()) {
            LayoutListForFocus(loopIndex, curIndex);
            it = itemPosition_.find(loopIndex);
            itCache = cachedItemPosition_.find(loopIndex);
            if (it == itemPosition_.end() && itCache == cachedItemPosition_.end()) {
                continue;
            }
        }

        // Check if the index corresponds to a ListItemGroup.
        if ((it != itemPosition_.end() && it->second.isGroup) ||
            (itCache != cachedItemPosition_.end() && itCache->second.isGroup)) {
            nextIndex = loopIndex;
            return (focusStep == FocusStep::DOWN || focusStep == FocusStep::RIGHT) ? 1 : -1;
        }
    }
    nextIndex = curIndex + moveStep;
    return moveStep;
}

WeakPtr<FocusHub> ListPattern::GetNextFocusNodeInList(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    auto curFocus = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocus, nullptr);
    auto curFrame = curFocus->GetFrameNode();
    CHECK_NULL_RETURN(curFrame, nullptr);
    auto curPattern = curFrame->GetPattern();
    CHECK_NULL_RETURN(curPattern, nullptr);
    auto curIndex = GetCurrentFocusIndex(curPattern);

    int32_t moveStep = 0;
    int32_t nextIndex = curIndex;
    auto listProperty = GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listProperty, nullptr);
    auto isVertical = listProperty->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL;

    AdjustFocusStepForRtl(step, isVertical);

    if (lanes_ <= 1) {
        DetermineSingleLaneStep(step, isVertical, curIndex, moveStep, nextIndex);
    } else {
        DetermineMultiLaneStep(step, isVertical, curIndex, moveStep, nextIndex);
    }

    bool loopFlag = true;
    while (nextIndex >= 0 && nextIndex <= maxListItemIndex_) {
        if (nextIndex == curIndex) {
            return nullptr;
        }
        LayoutListForFocus(nextIndex, curIndex);
        auto nextFocusNode = FindChildFocusNodeByIndex(nextIndex, step);
        if (nextFocusNode.Upgrade()) {
            // Scroll and display the ListItem.
            if (IsListItem(nextFocusNode)) {
                AdjustScrollPosition(nextIndex, curIndex);
            }
            return nextFocusNode;
        }
        nextIndex += moveStep;
        HandleIndexToBounds(nextIndex, loopFlag);
    }

    return nullptr;
}

bool ListPattern::IsListItemGroupByIndex(int32_t index)
{
    auto list = GetHost();
    CHECK_NULL_RETURN(list, false);
    auto layoutWapper = list->GetChildByIndex(index);
    CHECK_NULL_RETURN(layoutWapper, false);
    auto frameNode = layoutWapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    return frameNode && frameNode->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
}

WeakPtr<FocusHub> ListPattern::FindChildFocusNodeByIndex(int32_t tarMainIndex, const FocusStep& step)
{
    // Only for GetNextFocusNodeInList.
    auto listFrame = GetHost();
    CHECK_NULL_RETURN(listFrame, nullptr);
    auto listFocus = listFrame->GetFocusHub();
    CHECK_NULL_RETURN(listFocus, nullptr);
    WeakPtr<FocusHub> target;
    listFocus->AnyChildFocusHub([&target, tarMainIndex, step](const RefPtr<FocusHub>& childFocus) {
        if (!childFocus->IsFocusable()) {
            return false;
        }
        auto childFrame = childFocus->GetFrameNode();
        if (!childFrame) {
            return false;
        }
        auto childPattern = childFrame->GetPattern();
        if (!childPattern) {
            return false;
        }
        auto childItemPattern = AceType::DynamicCast<ListItemPattern>(childPattern);
        if (!childItemPattern) {
            auto childItemGroupPattern = AceType::DynamicCast<ListItemGroupPattern>(childPattern);
            CHECK_NULL_RETURN(childItemGroupPattern, false);

            if (childItemGroupPattern->GetIndexInList() == tarMainIndex) {
                auto isFindTailOrHead = childItemGroupPattern->FindHeadOrTailChild(childFocus, step, target);
                if (!isFindTailOrHead) {
                    target = childFocus;
                }
                return true;
            }
            return false;
        }
        auto curIndex = childItemPattern->GetIndexInList();
        if (curIndex == tarMainIndex) {
            target = childFocus;
            return true;
        }
        return false;
    });
    return target;
}

void ListPattern::DetermineSingleLaneStep(
    FocusStep step, bool isVertical, int32_t curIndex, int32_t& moveStep, int32_t& nextIndex)
{
    // Only for GetNextFocusNodeInList
    if (step == FocusStep::UP_END || step == FocusStep::LEFT_END) {
        moveStep = 1;
        nextIndex = 0;
    } else if (step == FocusStep::DOWN_END || step == FocusStep::RIGHT_END) {
        moveStep = -1;
        nextIndex = maxListItemIndex_;
    } else if ((isVertical && (step == FocusStep::DOWN)) || (!isVertical && step == FocusStep::RIGHT) ||
               (step == FocusStep::TAB)) {
        moveStep = 1;
        nextIndex = curIndex + moveStep;
    } else if ((isVertical && step == FocusStep::UP) || (!isVertical && step == FocusStep::LEFT) ||
               (step == FocusStep::SHIFT_TAB)) {
        moveStep = -1;
        nextIndex = curIndex + moveStep;
    }
}

void ListPattern::DetermineMultiLaneStep(
    FocusStep step, bool isVertical, int32_t curIndex, int32_t& moveStep, int32_t& nextIndex)
{
    // Only for GetNextFocusNodeInList.

    if ((step == FocusStep::UP_END) || (step == FocusStep::LEFT_END)) {
        moveStep = 1;
        nextIndex = 0;
    } else if ((step == FocusStep::DOWN_END) || (step == FocusStep::RIGHT_END)) {
        moveStep = -1;
        nextIndex = maxListItemIndex_;
    } else if ((isVertical && (step == FocusStep::DOWN)) || (!isVertical && step == FocusStep::RIGHT)) {
        if (IsListItemGroupByIndex(curIndex)) {
            // If the current item is a ListItemGroupPattern, the moveStep must be 1.
            moveStep = 1;
            nextIndex = nextIndex + moveStep;
        } else {
            // If the current item is a ListItem, the moveStep needs to be determined.
            // In the next step, sequentially check up to lanes-1. If a ListItemGroup is encountered, move only one
            // step. Otherwise, proceed according to the lanes.
            moveStep = GetNextMoveStepForMultiLanes(curIndex, step, isVertical, nextIndex);
        }
        nextIndex = AdjustNextIndexForEdgeRow(nextIndex, moveStep, curIndex);
    } else if ((isVertical && step == FocusStep::UP) || (!isVertical && step == FocusStep::LEFT)) {
        if (IsListItemGroupByIndex(curIndex)) {
            // If the current item is a ListItemGroupPattern, the moveStep must be 1.
            moveStep = -1;
            nextIndex = curIndex + moveStep;
        } else {
            moveStep = GetNextMoveStepForMultiLanes(curIndex, step, isVertical, nextIndex);
        }
    } else if ((isVertical && (step == FocusStep::RIGHT)) || (!isVertical && step == FocusStep::DOWN)) {
        moveStep = 1;
        nextIndex = GetCrossAxisNextIndex(curIndex, isVertical, moveStep, step);
    } else if ((isVertical && step == FocusStep::LEFT) || (!isVertical && step == FocusStep::UP)) {
        moveStep = -1;
        nextIndex = GetCrossAxisNextIndex(curIndex, isVertical, moveStep, step);
    } else if (step == FocusStep::TAB) {
        moveStep = 1;
        nextIndex = curIndex + 1;
    } else if (step == FocusStep::SHIFT_TAB) {
        moveStep = -1;
        nextIndex = curIndex - 1;
    }
}

int32_t ListPattern::GetCurrentFocusIndex(const RefPtr<Pattern>& curPattern)
{
    auto curItemPattern = AceType::DynamicCast<ListItemPattern>(curPattern);
    if (!curItemPattern) {
        auto curItemGroupPattern = AceType::DynamicCast<ListItemGroupPattern>(curPattern);
        CHECK_NULL_RETURN(curItemGroupPattern, -1);
        return curItemGroupPattern->GetIndexInList();
    }
    return curItemPattern->GetIndexInList();
}

void ListPattern::AdjustFocusStepForRtl(FocusStep& step, bool isVertical)
{
    auto listLayoutProperty = GetLayoutProperty<ListLayoutProperty>();
    bool isRtl = false;
    if (listLayoutProperty) {
        isRtl = TextDirection::RTL == listLayoutProperty->GetNonAutoLayoutDirection();
    }

    // FocusStep LEFT/RIGH reverse flag
    bool reverseHorizontal = false;
    // FocusStep UP/DOWN reverse flag
    bool reverseVertical = false;

    if ((!isRtl && !isVertical && isStackFromEnd_)) {
        reverseVertical = true;
    } else if ((!isRtl && isVertical && isStackFromEnd_) || (isRtl && !isStackFromEnd_)) {
        reverseHorizontal = true;
    } else if (isRtl && !isVertical && isStackFromEnd_) {
        reverseHorizontal = true;
        reverseVertical = true;
    }

    if (reverseHorizontal) {
        if (step == FocusStep::LEFT) {
            step = FocusStep::RIGHT;
        } else if (step == FocusStep::RIGHT) {
            step = FocusStep::LEFT;
        }
    }

    if (reverseVertical) {
        if (step == FocusStep::UP) {
            step = FocusStep::DOWN;
        } else if (step == FocusStep::DOWN) {
            step = FocusStep::UP;
        }
    }
}

bool ListPattern::IsListItem(const WeakPtr<FocusHub>& focusNode)
{
    // Determine if it is a list item.
    auto focusHub = focusNode.Upgrade();
    CHECK_NULL_RETURN(focusHub, false);
    auto frameNode = focusHub->GetFrameNode();
    return frameNode &&
           (frameNode->GetTag() == V2::LIST_ITEM_ETS_TAG || frameNode->GetTag() == V2::ARC_LIST_ITEM_ETS_TAG);
}

void ListPattern::AdjustScrollPosition(int32_t nextIndex, int32_t curIndex)
{
    // Only for GetNextFocusNodeInList
    // Adjust the scroll position.
    if (nextIndex < startIndex_) {
        ScrollToIndex(nextIndex, false, ScrollAlign::START);
    } else if (nextIndex > endIndex_) {
        ScrollToIndex(nextIndex, false, ScrollAlign::END);
    } else {
        HandleDisplayedChildFocus(nextIndex, curIndex);
    }
}

void ListPattern::HandleIndexToBounds(int32_t& nextIndex, bool& loopFlag)
{
    // Only for GetNextFocusNodeInList.
    // Handle boundary conditions.
    if ((nextIndex < 0 || nextIndex > maxListItemIndex_) && loopFlag) {
        loopFlag = false; // Single loop protection.
        nextIndex = (nextIndex < 0) ? 0 : maxListItemIndex_;
    }
}

int32_t ListPattern::GetCrossAxisNextIndex(int32_t curIndex, bool isVertical, int32_t moveStep, FocusStep step)
{
    // Only for DetermineMultiLaneStep
    int32_t nextIndex = curIndex + moveStep;
    const bool isForward = (isVertical && step == FocusStep::RIGHT) || (!isVertical && step == FocusStep::DOWN);
    const bool isBackward = (isVertical && step == FocusStep::LEFT) || (!isVertical && step == FocusStep::UP);

    if (!isForward && !isBackward) {
        return nextIndex;
    }

    const bool isGroup = IsListItemGroupByIndex(curIndex);
    if (isGroup) {
        // Currently at a group or the last column, do not move.
        return curIndex;
    }

    // Check if the next position is a group or in the same column.
    const ListItemInfo* curPos = GetPosition(curIndex);
    const ListItemInfo* nextPos = GetPosition(nextIndex);
    if (NextPositionBlocksMove(curPos, nextPos, isVertical)) {
        return curIndex;
    }
    return nextIndex;
}

const ListItemInfo* ListPattern::GetPosition(int32_t index) const
{
    // Only for GetCrossAxisNextIndex
    auto it = itemPosition_.find(index);
    if (it != itemPosition_.end()) {
        return &it->second;
    }
    auto cachedIt = cachedItemPosition_.find(index);
    return (cachedIt != cachedItemPosition_.end()) ? &cachedIt->second : nullptr;
}

bool ListPattern::NextPositionBlocksMove(const ListItemInfo* curPos, const ListItemInfo* nextPos, bool isVertical) const
{
    // Only for GetCrossAxisNextIndex, determine if the next position blocks movement.

    if (!nextPos) {
        // No position information, allow movement (or handle externally).
        return false;
    }
    if (nextPos->isGroup) {
        // The next position is a group, block the movement.
        return true;
    }

    // Check if the current and next positions are in the same column.
    // If the endPos and startPos of two items are the same, it indicates they are in the same row or column, allowing
    // focus movement; otherwise, it is considered to have reached the first column (row) or the last column (row),
    // disallowing focus movement.
    return curPos && (!NearEqual(curPos->endPos, nextPos->endPos) && !NearEqual(curPos->startPos, nextPos->startPos));
}

int32_t ListPattern::AdjustNextIndexForEdgeRow(int32_t nextIndex, int32_t moveStep, int32_t curIndex)
{
    // Only for DetermineMultiLaneStep
    if (nextIndex >= maxListItemIndex_ && moveStep == lanes_) {
        auto row = maxListItemIndex_ / lanes_;
        auto curRow = curIndex / lanes_;
        if (curRow == row - 1) {
            return maxListItemIndex_;
        }
    }
    return nextIndex;
}

ScopeFocusAlgorithm ListPattern::GetScopeFocusAlgorithm()
{
    auto property = GetLayoutProperty<ListLayoutProperty>();
    if (!property) {
        return {};
    }
    return ScopeFocusAlgorithm(property->GetListDirection().value_or(Axis::VERTICAL) == Axis::VERTICAL, true,
        ScopeType::OTHERS,
        [wp = WeakClaim(this)](
            FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) -> bool {
            auto list = wp.Upgrade();
            if (list) {
                nextFocusNode = list->GetNextFocusNodeInList(step, currFocusNode);
            }
            LOGI("acefocus ListPattern::GetScopeFocusAlgorithm return: %{public}d",
                nextFocusNode.Upgrade() != currFocusNode.Upgrade());
            return nextFocusNode.Upgrade() != currFocusNode.Upgrade();
        });
}

void ListPattern::OnMidIndexChanged()
{
#ifdef SUPPORT_DIGITAL_CROWN
    if (!GetCrownEventDragging()) {
        return;
    }
    VibratorUtils::StartVibraFeedback(HAPTIC_STRENGTH1);
#endif
}

void ListPattern::ReportOnItemListEvent(const std::string& event)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::string value = std::string("List.") + event;
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", value);
    TAG_LOGI(AceLogTag::ACE_LIST, "nodeId:[%{public}d] List reportComponentChangeEvent %{public}s", host->GetId(),
        event.c_str());
}

void ListPattern::ReportOnItemListScrollEvent(const std::string& event, int32_t startindex, int32_t endindex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::string value = std::string("List.") + event;

    auto params = JsonUtil::Create();
    CHECK_NULL_VOID(params);
    params->Put("StartX", startindex);
    params->Put("StartY", endindex);

    auto eventData = JsonUtil::Create();
    CHECK_NULL_VOID(eventData);
    eventData->Put("name", value.c_str());
    eventData->Put("params", params);

    auto json = JsonUtil::Create();
    CHECK_NULL_VOID(json);
    json->Put("nodeId", host->GetId());
    json->Put("event", eventData);

    auto result = JsonUtil::Create();
    CHECK_NULL_VOID(result);
    result->Put("result", json);

    UiSessionManager::GetInstance()->ReportComponentChangeEvent("result", result->ToString());
    TAG_LOGI(AceLogTag::ACE_LIST,
        "nodeId:[%{public}d] List reportComponentChangeEvent %{public}s startindex:%{public}d endindex:%{public}d",
        host->GetId(), event.c_str(), startindex, endindex);
}

int32_t ListPattern::OnInjectionEvent(const std::string& command)
{
    TAG_LOGI(AceLogTag::ACE_LIST, "OnInjectionEvent command: %{public}s", command.c_str());

    std::string ret = ScrollablePattern::ParseCommand(command);
    if (ret == "scrollForward") {
        ScrollPage(true);
    } else if (ret == "scrollBackward") {
        ScrollPage(false);
    } else {
        return RET_FAILED;
    }
    return RET_SUCCESS;
}

} // namespace OHOS::Ace::NG
