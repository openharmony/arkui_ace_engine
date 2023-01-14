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

#include "core/components_ng/pattern/list/list_pattern.h"

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/animation/bilateral_spring_node.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CHAIN_ANIMATION_NODE_COUNT = 30;
constexpr Color SELECT_FILL_COLOR = Color(0x1A000000);
constexpr Color SELECT_STROKE_COLOR = Color(0x33FFFFFF);
constexpr Color ITEM_FILL_COLOR = Color(0x1A0A59f7);
} // namespace

void ListPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
}

void ListPattern::OnModifyDone()
{
    if (!isInitialized_) {
        jumpIndex_ = GetLayoutProperty<ListLayoutProperty>()->GetInitialIndex().value_or(0);
        isInitialized_ = true;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listLayoutProperty);
    auto axis = listLayoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    SetAxis(axis);
    if (!GetScrollableEvent()) {
        InitScrollableEvent();
    }

    SetEdgeEffect(listLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING));
    auto listPaintProperty = host->GetPaintProperty<ListPaintProperty>();
    SetScrollBar(listPaintProperty->GetBarDisplayMode().value_or(DisplayMode::OFF));
    SetChainAnimation(listLayoutProperty->GetChainAnimation().value_or(false));
    if (multiSelectable_ && !isMouseEventInit_) {
        InitMouseEvent();
    }
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID_NOLOG(focusHub);
    InitOnKeyEvent(focusHub);
}

bool ListPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    bool isJump = false;
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto listLayoutAlgorithm = DynamicCast<ListLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(listLayoutAlgorithm, false);
    itemPosition_ = listLayoutAlgorithm->GetItemPosition();
    maxListItemIndex_ = listLayoutAlgorithm->GetMaxListItemIndex();
    if (jumpIndex_) {
        estimateOffset_ = listLayoutAlgorithm->GetEstimateOffset();
        if (!itemPosition_.empty()) {
            currentOffset_ = itemPosition_.begin()->second.startPos;
        }
        isJump = true;
        jumpIndex_.reset();
    }
    auto finalOffset = listLayoutAlgorithm->GetCurrentOffset();
    spaceWidth_ = listLayoutAlgorithm->GetSpaceWidth();
    lastOffset_ = currentOffset_;
    currentOffset_ = currentOffset_ - finalOffset;
    currentDelta_ = 0.0f;
    startMainPos_ = listLayoutAlgorithm->GetStartPosition();
    endMainPos_ = listLayoutAlgorithm->GetEndPosition();
    itemGroupList_.swap(listLayoutAlgorithm->GetItemGroupList());
    auto lanesLayoutAlgorithm = DynamicCast<ListLanesLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    if (lanesLayoutAlgorithm) {
        lanesLayoutAlgorithm->SwapLanesItemRange(lanesItemRange_);
        lanes_ = lanesLayoutAlgorithm->GetLanes();
    }
    CheckScrollable();

    bool indexChanged =
        (startIndex_ != listLayoutAlgorithm->GetStartIndex()) || (endIndex_ != listLayoutAlgorithm->GetEndIndex());
    startIndex_ = listLayoutAlgorithm->GetStartIndex();
    endIndex_ = listLayoutAlgorithm->GetEndIndex();
    ProcessEvent(indexChanged, finalOffset, isJump);
    UpdateScrollBarOffset();

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    return (listLayoutProperty && listLayoutProperty->GetDivider().has_value());
}

void ListPattern::ProcessEvent(bool indexChanged, float finalOffset, bool isJump)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listEventHub = host->GetEventHub<ListEventHub>();
    CHECK_NULL_VOID(listEventHub);

    auto onScroll = listEventHub->GetOnScroll();
    if (onScroll && !NearZero(finalOffset) && !isJump) {
        auto source = GetScrollState();
        auto offsetPX = Dimension(finalOffset);
        auto offsetVP = Dimension(offsetPX.ConvertToVp(), DimensionUnit::VP);
        if (source == SCROLL_FROM_UPDATE) {
            onScroll(offsetVP, V2::ScrollState::SCROLL);
        } else if (source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING) {
            onScroll(offsetVP, V2::ScrollState::FLING);
        } else {
            onScroll(offsetVP, V2::ScrollState::IDLE);
        }
    }

    if (indexChanged) {
        auto onScrollIndex = listEventHub->GetOnScrollIndex();
        if (onScrollIndex) {
            onScrollIndex(startIndex_, endIndex_);
        }
    }

    auto onReachStart = listEventHub->GetOnReachStart();
    if (onReachStart && (startIndex_ == 0)) {
        float lastStartPos = startMainPos_ - (currentOffset_ - lastOffset_);
        bool scrollUpToStart = GreatNotEqual(lastStartPos, 0.0) && LessOrEqual(startMainPos_, 0.0);
        bool scrollDownToStart = LessNotEqual(lastStartPos, 0.0) && GreatOrEqual(startMainPos_, 0.0);
        bool jumpToStart = isJump && NearZero(startMainPos_);
        if (scrollUpToStart || scrollDownToStart || jumpToStart) {
            onReachStart();
        }
    }
    auto onReachEnd = listEventHub->GetOnReachEnd();
    if (onReachEnd && (endIndex_ == maxListItemIndex_)) {
        float lastEndPos = endMainPos_ - (currentOffset_ - lastOffset_);
        float mainSize = GetMainContentSize();
        bool scrollUpToEnd = GreatNotEqual(lastEndPos, mainSize) && LessOrEqual(endMainPos_, mainSize);
        bool scrollDownToEnd = LessNotEqual(lastEndPos, mainSize) && GreatOrEqual(endMainPos_, mainSize);
        bool jumpToEnd = isJump && NearEqual(endMainPos_, mainSize);
        if (scrollUpToEnd || scrollDownToEnd || jumpToEnd) {
            onReachEnd();
        }
    }

    if (scrollStop_) {
        auto onScrollStop = listEventHub->GetOnScrollStop();
        if (onScrollStop) {
            onScrollStop();
        }
        scrollStop_ = false;
    }
}

void ListPattern::CheckScrollable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    if (itemPosition_.empty()) {
        scrollable_ = false;
    } else {
        if ((itemPosition_.begin()->first == 0) && (itemPosition_.rbegin()->first == maxListItemIndex_)) {
            scrollable_ = GreatNotEqual((endMainPos_ - startMainPos_), GetMainContentSize());
        } else {
            scrollable_ = true;
        }
    }

    SetScrollEnable(scrollable_);
}

RefPtr<LayoutAlgorithm> ListPattern::CreateLayoutAlgorithm()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto listLayoutProperty = host->GetLayoutProperty<ListLayoutProperty>();
    RefPtr<ListLayoutAlgorithm> listLayoutAlgorithm;
    if (listLayoutProperty->HasLanes() || listLayoutProperty->HasLaneMinLength() ||
        listLayoutProperty->HasLaneMaxLength()) {
        auto lanesLayoutAlgorithm = MakeRefPtr<ListLanesLayoutAlgorithm>();
        if ((listLayoutProperty->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT) == 0) {
            lanesLayoutAlgorithm->SwapLanesItemRange(lanesItemRange_);
        }
        lanesLayoutAlgorithm->SetLanes(lanes_);
        listLayoutAlgorithm.Swap(lanesLayoutAlgorithm);
    } else {
        listLayoutAlgorithm.Swap(MakeRefPtr<ListLayoutAlgorithm>());
    }
    if (jumpIndex_) {
        listLayoutAlgorithm->SetIndex(jumpIndex_.value());
        listLayoutAlgorithm->SetIndexAlignment(scrollIndexAlignment_);
    }
    listLayoutAlgorithm->SetCurrentDelta(currentDelta_);
    listLayoutAlgorithm->SetItemsPosition(itemPosition_);
    if (IsOutOfBoundary(false)) {
        listLayoutAlgorithm->SetOverScrollFeature();
    }
    auto effect = listLayoutProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
    bool canOverScroll = (effect == EdgeEffect::SPRING) && !ScrollableIdle() && scrollState_ != SCROLL_FROM_BAR;
    listLayoutAlgorithm->SetCanOverScroll(canOverScroll);
    if (chainAdapter_) {
        listLayoutAlgorithm->SetChainOffsetCallback([weak = AceType::WeakClaim(this)](int32_t index) {
            auto list = weak.Upgrade();
            CHECK_NULL_RETURN(list, 0.0f);
            return list->GetChainDelta(index);
        });
        listLayoutAlgorithm->SetChainInterval(chainProperty_.Interval().ConvertToPx());
    }
    return listLayoutAlgorithm;
}

bool ListPattern::IsAtTop() const
{
    return (startIndex_ == 0) && NonNegative(startMainPos_);
}

bool ListPattern::IsAtBottom() const
{
    return endIndex_ == maxListItemIndex_ && LessOrEqual(endMainPos_, GetMainContentSize());
}

bool ListPattern::UpdateCurrentOffset(float offset, int32_t source)
{
    SetScrollState(source);
    // check edgeEffect is not springEffect
    if (!HandleEdgeEffect(offset, source, GetContentSize())) {
        return false;
    }
    currentDelta_ = currentDelta_ - offset;
    MarkDirtyNodeSelf();
    if (!IsOutOfBoundary() || !scrollable_) {
        return true;
    }

    // over scroll in drag update from normal to over scroll.
    float overScroll = 0.0f;
    // over scroll in drag update during over scroll.
    auto startPos = startMainPos_ - currentDelta_;
    if ((itemPosition_.begin()->first == 0) && Positive(startPos)) {
        overScroll = startPos;
    } else {
        overScroll = GetMainContentSize() - (endMainPos_ - currentDelta_);
    }

    if (scrollState_ == SCROLL_FROM_UPDATE) {
        // adjust offset.
        auto friction = CalculateFriction(std::abs(overScroll) / GetMainContentSize());
        currentDelta_ = currentDelta_ * friction;
    }
    return true;
}

void ListPattern::MarkDirtyNodeSelf()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    for (const auto& weak : itemGroupList_) {
        auto itemGroup = weak.Upgrade();
        if (!itemGroup) {
            continue;
        }
        auto layoutProperty = itemGroup->GetLayoutProperty();
        if (layoutProperty) {
            layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
        }
    }
}

void ListPattern::ProcessScrollEnd()
{
    SetScrollBarDriving(false);
    scrollStop_ = true;
    MarkDirtyNodeSelf();
}

float ListPattern::GetMainContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetPaddingSize().MainSize(GetAxis());
}

SizeF ListPattern::GetContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF());
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    return geometryNode->GetPaddingSize();
}

bool ListPattern::IsOutOfBoundary(bool useCurrentDelta)
{
    if (itemPosition_.empty()) {
        return false;
    }
    auto startPos = useCurrentDelta ? startMainPos_ - currentDelta_ : startMainPos_;
    auto endPos = useCurrentDelta ? endMainPos_ - currentDelta_ : endMainPos_;
    auto mainSize = GetMainContentSize();
    bool outOfStart = (startIndex_ == 0) && Positive(startPos) && GreatNotEqual(endPos, mainSize);
    bool outOfEnd = (endIndex_ == maxListItemIndex_) && LessNotEqual(endPos, mainSize) && Negative(startPos);
    return outOfStart || outOfEnd;
}

bool ListPattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        ProcessDragStart(offset);
        return true;
    }
    auto scrollBar = GetScrollBar();
    if (scrollBar && scrollBar->IsDriving()) {
        offset = scrollBar->CalcPatternOffset(offset);
        source = SCROLL_FROM_BAR;
    } else {
        ProcessDragUpdate(offset);
    }
    return UpdateCurrentOffset(offset, source);
}

void ListPattern::InitScrollableEvent()
{
    AddScrollEvent();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listEventHub = host->GetEventHub<ListEventHub>();
    auto onScrollBegin = listEventHub->GetOnScrollBegin();
    auto scrollableEvent = GetScrollableEvent();
    if (onScrollBegin && scrollableEvent) {
        scrollableEvent->SetScrollBeginCallback(std::move(onScrollBegin));
    }
}

void ListPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        CHECK_NULL_RETURN_NOLOG(list, 0.0);
        return list->startMainPos_ - list->currentDelta_;
    });
    scrollEffect->SetLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        return list->GetMainContentSize() - (list->endMainPos_ - list->startMainPos_);
    });
    scrollEffect->SetTrailingCallback([]() -> double { return 0.0; });
    scrollEffect->SetInitLeadingCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto list = weak.Upgrade();
        return list->GetMainContentSize() - (list->endMainPos_ - list->startMainPos_);
    });
    scrollEffect->SetInitTrailingCallback([]() -> double { return 0.0; });
}

void ListPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
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
        LOGD("Keycode is PgDn. Scroll to next page");
        ScrollPage(false);
        return true;
    }
    if (event.code == KeyCode::KEY_PAGE_UP) {
        LOGD("Keycode is PgDn. Scroll to next page");
        ScrollPage(true);
        return true;
    }
    if (event.IsDirectionalKey()) {
        HandleDirectionKey(event.code);
        return true;
    }
    return false;
}

bool ListPattern::HandleDirectionKey(KeyCode code)
{
    if ((GetAxis() == Axis::VERTICAL && code == KeyCode::KEY_DPAD_UP) ||
        (GetAxis() == Axis::HORIZONTAL && code == KeyCode::KEY_DPAD_LEFT)) {
        auto nextIndex = std::clamp(scrollIndex_ - 1, 0, maxListItemIndex_);
        if (nextIndex == scrollIndex_) {
            return false;
        }
        scrollIndex_ = nextIndex;
        LOGD("Scroll to next index: %{public}d", scrollIndex_);
        // Need to update: current selection
        ScrollToIndex(scrollIndex_, ScrollIndexAlignment::ALIGN_TOP);
        return true;
    }
    if ((GetAxis() == Axis::VERTICAL && code == KeyCode::KEY_DPAD_DOWN) ||
        (GetAxis() == Axis::HORIZONTAL && code == KeyCode::KEY_DPAD_RIGHT)) {
        auto nextIndex = std::clamp(scrollIndex_ + 1, 0, maxListItemIndex_);
        if (nextIndex == scrollIndex_) {
            return false;
        }
        scrollIndex_ = nextIndex;
        LOGD("Scroll to previous index: %{public}d", scrollIndex_);
        // Need to update: current selection
        ScrollToIndex(scrollIndex_, ScrollIndexAlignment::ALIGN_BUTTON);
        return true;
    }
    return false;
}

void ListPattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve)
{
    LOGI("AnimateTo:%f, duration:%f", position, duration);
    if (!animator_) {
        animator_ = AceType::MakeRefPtr<Animator>(PipelineBase::GetCurrentContext());
    }
    if (!animator_->IsStopped()) {
        animator_->Stop();
    }
    animator_->ClearInterpolators();

    auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(GetTotalOffset(), position, curve);
    animation->AddListener([weakScroll = AceType::WeakClaim(this)](float value) {
        auto list = weakScroll.Upgrade();
        CHECK_NULL_VOID_NOLOG(list);
        list->SetScrollState(SCROLL_FROM_JUMP);
        list->UpdateCurrentOffset(list->GetTotalOffset() - value, SCROLL_FROM_JUMP);
    });
    animator_->AddInterpolator(animation);
    animator_->SetDuration(static_cast<int32_t>(duration));
    animator_->Play();
}

void ListPattern::ScrollTo(float position)
{
    LOGI("ScrollTo:%{public}f", position);
    SetScrollState(SCROLL_FROM_JUMP);
    UpdateCurrentOffset(GetTotalOffset() - position, SCROLL_FROM_JUMP);
}

void ListPattern::ScrollToIndex(int32_t index, ScrollIndexAlignment align)
{
    LOGI("ScrollToIndex:%{public}d", index);
    if (index >= 0 && index <= maxListItemIndex_) {
        jumpIndex_ = index;
        scrollIndexAlignment_ = align;
        MarkDirtyNodeSelf();
    }
}

void ListPattern::ScrollToEdge(ScrollEdgeType scrollEdgeType)
{
    LOGI("ScrollToEdge:%{public}zu", scrollEdgeType);
    if (scrollEdgeType == ScrollEdgeType::SCROLL_TOP) {
        ScrollToIndex(0, ScrollIndexAlignment::ALIGN_TOP);
    } else if (scrollEdgeType == ScrollEdgeType::SCROLL_BOTTOM) {
        ScrollToIndex(maxListItemIndex_, ScrollIndexAlignment::ALIGN_BUTTON);
    }
}

bool ListPattern::ScrollPage(bool reverse)
{
    LOGI("ScrollPage:%{public}d", reverse);
    float distance = reverse ? GetMainContentSize() : -GetMainContentSize();
    SetScrollState(SCROLL_FROM_JUMP);
    UpdateCurrentOffset(distance, SCROLL_FROM_JUMP);
    return true;
}

Offset ListPattern::GetCurrentOffset() const
{
    if (GetAxis() == Axis::HORIZONTAL) {
        return {GetTotalOffset(), 0.0};
    }
    return {0.0, GetTotalOffset()};
}

void ListPattern::UpdateScrollBarOffset()
{
    if (itemPosition_.empty()) {
        return;
    }
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    SizeF ContentSize = GetContentSize();
    Size size(ContentSize.Width(), ContentSize.Height());
    float itemsSize = itemPosition_.rbegin()->second.endPos - itemPosition_.begin()->second.startPos + spaceWidth_;
    float currentOffset = itemsSize / itemPosition_.size() * itemPosition_.begin()->first - startMainPos_;
    Offset scrollOffset = { currentOffset, currentOffset }; // fit for w/h switched.
    auto estimatedHeight = itemsSize / itemPosition_.size() * (maxListItemIndex_ + 1);

    UpdateScrollBarRegion(currentOffset, estimatedHeight, size);
}

void ListPattern::SetChainAnimation(bool enable)
{
    if (!enable) {
        overSpringProperty_.Reset();
        chain_.Reset();
        chainAdapter_.Reset();
        return;
    }
    if (!chainAdapter_) {
        InitChainAnimation(CHAIN_ANIMATION_NODE_COUNT);
        overSpringProperty_ = SpringChainProperty::GetDefaultOverSpringProperty();
    }
}

void ListPattern::InitChainAnimation(int32_t nodeCount)
{
    chainAdapter_ = AceType::MakeRefPtr<BilateralSpringAdapter>();
    chain_ = AceType::MakeRefPtr<SimpleSpringChain>(chainAdapter_);
    chain_->SetFrameDelta(chainProperty_.FrameDelay());
    if (chainProperty_.StiffnessTransfer()) {
        chain_->SetStiffnessTransfer(AceType::MakeRefPtr<ExpParamTransfer>(chainProperty_.StiffnessCoefficient()));
    } else {
        chain_->SetStiffnessTransfer(AceType::MakeRefPtr<LinearParamTransfer>(chainProperty_.StiffnessCoefficient()));
    }
    if (chainProperty_.DampingTransfer()) {
        chain_->SetDampingTransfer(AceType::MakeRefPtr<ExpParamTransfer>(chainProperty_.DampingCoefficient()));
    } else {
        chain_->SetDampingTransfer(AceType::MakeRefPtr<LinearParamTransfer>(chainProperty_.DampingCoefficient()));
    }
    chain_->SetControlDamping(chainProperty_.ControlDamping());
    chain_->SetControlStiffness(chainProperty_.ControlStiffness());
    chain_->SetDecoration(chainProperty_.Interval().ConvertToPx());
    chain_->SetMinDecoration(chainProperty_.MinInterval().ConvertToPx());
    chain_->SetMaxDecoration(chainProperty_.MaxInterval().ConvertToPx());
    for (int32_t index = 0; index < nodeCount; index++) {
        auto node = AceType::MakeRefPtr<BilateralSpringNode>(PipelineBase::GetCurrentContext(), index, 0.0);
        node->AddUpdateListener(
            [weak = AceType::WeakClaim(this)](double value, double velocity) {
                auto list = weak.Upgrade();
                CHECK_NULL_VOID(list);
                list->MarkDirtyNodeSelf();
            });
        chainAdapter_->AddNode(node);
    }
    chainAdapter_->NotifyControlIndexChange();
}

float ListPattern::FlushChainAnimation(float dragOffset)
{
    if (!chain_ || !chainAdapter_) {
        return 0.0;
    }
    float deltaDistance = 0.0;
    bool needSetValue = false;
    auto scrollableEvent = GetScrollableEvent();
    bool overScroll = scrollableEvent && scrollableEvent->GetScrollable() &&
        scrollableEvent->GetScrollable()->IsSpringMotionRunning();
    if (chainOverScroll_ != overScroll) {
        if (overScroll) {
            if (overSpringProperty_ && overSpringProperty_->IsValid()) {
                chain_->SetControlStiffness(overSpringProperty_->Stiffness());
                chain_->SetControlDamping(overSpringProperty_->Damping());
            }
        } else {
            chain_->SetControlStiffness(chainProperty_.ControlStiffness());
            chain_->SetControlDamping(chainProperty_.ControlDamping());
        }
        chain_->OnControlNodeChange();
        chainOverScroll_ = overScroll;
    }
    chain_->FlushAnimation();
    if (dragStartIndexPending_ != dragStartIndex_) {
        deltaDistance = chainAdapter_->ResetControl(dragStartIndexPending_ - dragStartIndex_);
        dragStartIndex_ = dragStartIndexPending_;
        chainAdapter_->SetDeltaValue(-deltaDistance);
        needSetValue = true;
    }
    if (!NearZero(dragOffset)) {
        chainAdapter_->SetDeltaValue(dragOffset);
        needSetValue = true;
    }
    if (needSetValue) {
        chain_->SetValue(0.0);
    }
    return deltaDistance;
}

void ListPattern::ProcessDragStart(float startPosition)
{
    int32_t index = -1;
    for (auto & pos : itemPosition_) {
        if (startPosition <= pos.second.endPos) {
            index = pos.first;
            break;
        }
    }
    if (index == -1 && !itemPosition_.empty()) {
        index = itemPosition_.rbegin()->first + 1;
    }
    dragStartIndexPending_ = index;
}

void ListPattern::ProcessDragUpdate(float dragOffset)
{
    if (!chainAdapter_) {
        return;
    }

    if (NearZero(dragOffset)) {
        return;
    }

    float delta = FlushChainAnimation(-dragOffset);
    currentDelta_ += delta;
}

float ListPattern::GetChainDelta(int32_t index) const
{
    if (!chainAdapter_) {
        return 0.0f;
    }
    int32_t baseIndex = dragStartIndex_ - chainAdapter_->GetControlIndex();
    auto targetIndex = std::clamp(index - baseIndex, 0, CHAIN_ANIMATION_NODE_COUNT - 1);
    auto node = AceType::DynamicCast<BilateralSpringNode>(chainAdapter_->GetNode(targetIndex));
    CHECK_NULL_RETURN(node, 0.0f);
    return node->GetValue();
}

void ListPattern::InitMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mouseEventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(mouseEventHub);
    mouseEventHub->SetMouseEvent([weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEventWithoutKeyboard(info);
        }
    });
    isMouseEventInit_ = true;
}

void ListPattern::HandleMouseEventWithoutKeyboard(const MouseInfo& info)
{
    auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    if (info.GetButton() == MouseButton::LEFT_BUTTON) {
        if (info.GetAction() == MouseAction::PRESS) {
            mouseStartOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
            MultiSelectWithoutKeyboard(selectedZone);
        } else if (info.GetAction() == MouseAction::MOVE) {
            mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
            MultiSelectWithoutKeyboard(selectedZone);
        } else if (info.GetAction() == MouseAction::RELEASE) {
            mouseStartOffset_.Reset();
            mouseEndOffset_.Reset();
            ClearSelectedZone();
        }
    }
}

void ListPattern::MultiSelectWithoutKeyboard(const RectF& selectedZone)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<FrameNode>> childrens;
    host->GenerateOneDepthVisibleFrame(childrens);
    for (const auto& item : childrens) {
        auto itemPattern = item->GetPattern<ListItemPattern>();
        CHECK_NULL_VOID(itemPattern);
        if (!itemPattern->Selectable()) {
            continue;
        }

        auto itemGeometry = item->GetGeometryNode();
        CHECK_NULL_VOID(itemGeometry);
        auto context = item->GetRenderContext();
        CHECK_NULL_VOID(context);

        auto itemRect = itemGeometry->GetFrameRect();
        if (!selectedZone.IsIntersectWith(itemRect)) {
            itemPattern->MarkIsSelected(false);
            context->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        } else {
            itemPattern->MarkIsSelected(true);
            context->OnMouseSelectUpdate(true, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        }
    }

    auto hostContext = host->GetRenderContext();
    CHECK_NULL_VOID(hostContext);
    hostContext->UpdateMouseSelectWithRect(selectedZone, SELECT_FILL_COLOR, SELECT_STROKE_COLOR);
}

void ListPattern::ClearSelectedZone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostContext = host->GetRenderContext();
    CHECK_NULL_VOID(hostContext);
    hostContext->UpdateMouseSelectWithRect(RectF(), SELECT_FILL_COLOR, SELECT_STROKE_COLOR);
}

RectF ListPattern::ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset)
{
    RectF selectedZone;
    if (startOffset.GetX() <= endOffset.GetX()) {
        if (startOffset.GetY() <= endOffset.GetY()) {
            // bottom right
            selectedZone = RectF(startOffset.GetX(), startOffset.GetY(), endOffset.GetX() - startOffset.GetX(),
                endOffset.GetY() - startOffset.GetY());
        } else {
            // top right
            selectedZone = RectF(startOffset.GetX(), endOffset.GetY(), endOffset.GetX() - startOffset.GetX(),
                startOffset.GetY() - endOffset.GetY());
        }
    } else {
        if (startOffset.GetY() <= endOffset.GetY()) {
            // bottom left
            selectedZone = RectF(endOffset.GetX(), startOffset.GetY(), startOffset.GetX() - endOffset.GetX(),
                endOffset.GetY() - startOffset.GetY());
        } else {
            // top left
            selectedZone = RectF(endOffset.GetX(), endOffset.GetY(), startOffset.GetX() - endOffset.GetX(),
                startOffset.GetY() - endOffset.GetY());
        }
    }

    return selectedZone;
}
} // namespace OHOS::Ace::NG
