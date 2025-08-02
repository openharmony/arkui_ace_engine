/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/list/list_item_pattern.h"

#include "base/log/dump_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/list/list_item_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/common/container.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SWIPER_TH = 0.25f;
constexpr float NEW_SWIPER_TH = 0.5f;
constexpr float SWIPER_SPEED_TH = 1500.f;
constexpr float SWIPE_RATIO = 0.6f;
constexpr float NEW_SWIPE_RATIO = 1.848f;
constexpr float SWIPE_SPRING_MASS = 1.f;
constexpr float SWIPE_SPRING_STIFFNESS = 228.f;
constexpr float SWIPE_SPRING_DAMPING = 30.f;
constexpr int32_t DELETE_ANIMATION_DURATION = 400;
constexpr Color ITEM_FILL_COLOR = Color(0x1A0A59f7);
} // namespace

void ListItemPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (listItemStyle_ == V2::ListItemStyle::CARD) {
        SetListItemDefaultAttributes(host);
    }
}

void ListItemPattern::OnColorConfigurationUpdate()
{
    if (listItemStyle_ != V2::ListItemStyle::CARD) {
        return;
    }
    auto listItemNode = GetHost();
    CHECK_NULL_VOID(listItemNode);
    auto renderContext = listItemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = listItemNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto listItemTheme = pipeline->GetTheme<ListItemTheme>();
    CHECK_NULL_VOID(listItemTheme);

    renderContext->UpdateBackgroundColor(listItemTheme->GetItemDefaultColor());
}

void ListItemPattern::SetListItemDefaultAttributes(const RefPtr<FrameNode>& listItemNode)
{
    auto renderContext = listItemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = listItemNode->GetLayoutProperty<ListItemLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto listItemTheme = pipeline->GetTheme<ListItemTheme>();
    CHECK_NULL_VOID(listItemTheme);

    renderContext->UpdateBackgroundColor(listItemTheme->GetItemDefaultColor());

    PaddingProperty itemPadding;
    itemPadding.left = CalcLength(listItemTheme->GetItemDefaultLeftPadding());
    itemPadding.right = CalcLength(listItemTheme->GetItemDefaultRightPadding());
    layoutProperty->UpdatePadding(itemPadding);

    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(listItemTheme->GetItemDefaultHeight())));
    renderContext->UpdateBorderRadius(listItemTheme->GetItemDefaultBorderRadius());
}

RefPtr<LayoutAlgorithm> ListItemPattern::CreateLayoutAlgorithm()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto listItemEventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_RETURN(listItemEventHub, nullptr);
    if (!HasStartNode() && !HasEndNode() && !listItemEventHub->GetStartOnDelete() &&
        !listItemEventHub->GetEndOnDelete()) {
        return MakeRefPtr<BoxLayoutAlgorithm>();
    }
    auto layoutAlgorithm = MakeRefPtr<ListItemLayoutAlgorithm>(startNodeIndex_, endNodeIndex_, childNodeIndex_);
    layoutAlgorithm->SetAxis(axis_);
    layoutAlgorithm->SetStartNodeSize(startNodeSize_);
    layoutAlgorithm->SetEndNodeSize(endNodeSize_);
    layoutAlgorithm->SetCurOffset(curOffset_);
    layoutAlgorithm->SetHasStartDeleteArea(hasStartDeleteArea_);
    layoutAlgorithm->SetHasEndDeleteArea(hasEndDeleteArea_);
    if (swipeActionState_ == SwipeActionState::ACTIONING && !isSpringMotionRunning_) {
        layoutAlgorithm->SetCanUpdateCurOffset();
        layoutAlgorithm->SetItemChildCrossSize(GetContentSize().CrossSize(axis_));
    }
    return layoutAlgorithm;
}

bool ListItemPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    isLayouted_ = true;
    if (!HasStartNode() && !HasEndNode()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<ListItemLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    startNodeSize_ = layoutAlgorithm->GetStartNodeSize();
    endNodeSize_ = layoutAlgorithm->GetEndNodeSize();
    if (axis_ != GetAxis()) {
        ChangeAxis(GetAxis());
    } else if (layoutAlgorithm->GetCurOffsetUpdated()) {
        float newOffset = layoutAlgorithm->GetCurOffset();
        FireSwipeActionOffsetChange(curOffset_, newOffset);
        curOffset_ = newOffset;
    }
    if (pendingSwipeFunc_) {
        pendingSwipeFunc_();
        pendingSwipeFunc_ = nullptr;
    }
    return false;
}

void ListItemPattern::OnRecycle()
{
    if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD) {
        return;
    }
    FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
    if (springController_ && !springController_->IsStopped()) {
        // clear stop listener before stop
        springController_->ClearStopListeners();
        springController_->Stop();
    }
    startNodeSize_ = 0.0f;
    endNodeSize_ = 0.0f;
    float oldOffset = curOffset_;
    curOffset_ = 0.0f;
    FireSwipeActionOffsetChange(oldOffset, curOffset_);
    MarkDirtyNode();
}

void ListItemPattern::SetStartNode(const RefPtr<NG::UINode>& startNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (startNode) {
        if (!HasStartNode()) {
            host->AddChild(startNode);
            startNodeIndex_ = host->GetChildIndexById(startNode->GetId());
            if (childNodeIndex_ >= startNodeIndex_) {
                childNodeIndex_++;
            }
            if (endNodeIndex_ >= startNodeIndex_) {
                endNodeIndex_++;
            }
        } else {
            host->ReplaceChild(host->GetChildAtIndex(startNodeIndex_), startNode);
            host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        }
    } else if (HasStartNode()) {
        if (NonNegative(curOffset_)) {
            curOffset_ = 0.0f;
            isDragging_ = false;
        }
        host->RemoveChildAtIndex(startNodeIndex_);
        host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        if (endNodeIndex_ > startNodeIndex_) {
            endNodeIndex_--;
        }
        if (childNodeIndex_ > startNodeIndex_) {
            childNodeIndex_--;
        }
        startNodeIndex_ = -1;
    }
}

void ListItemPattern::SetEndNode(const RefPtr<NG::UINode>& endNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (endNode) {
        if (!HasEndNode()) {
            host->AddChild(endNode);
            endNodeIndex_ = host->GetChildIndexById(endNode->GetId());
            if (childNodeIndex_ >= endNodeIndex_) {
                childNodeIndex_++;
            }
            if (startNodeIndex_ >= endNodeIndex_) {
                startNodeIndex_++;
            }
        } else {
            host->ReplaceChild(host->GetChildAtIndex(endNodeIndex_), endNode);
            host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        }
    } else if (HasEndNode()) {
        if (NonPositive(curOffset_)) {
            curOffset_ = 0.0f;
            isDragging_ = false;
        }
        host->RemoveChildAtIndex(endNodeIndex_);
        host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        if (startNodeIndex_ > endNodeIndex_) {
            startNodeIndex_--;
        }
        if (childNodeIndex_ > endNodeIndex_) {
            childNodeIndex_--;
        }
        endNodeIndex_ = -1;
    }
}

void ListItemPattern::OnDidPop()
{
    if (endNodeIndex_ >= 0 && endNodeIndex_ < childNodeIndex_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto childNode = host->GetChildAtIndex(childNodeIndex_);
        CHECK_NULL_VOID(childNode);
        auto endNode = host->GetChildAtIndex(endNodeIndex_);
        CHECK_NULL_VOID(endNode);
        endNode->MovePosition(-1);
        endNodeIndex_ = host->GetChildIndexById(endNode->GetId());
        childNodeIndex_--;
    }
}

SizeF ListItemPattern::GetContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, {});
    return geometryNode->GetPaddingSize();
}

RefPtr<FrameNode> ListItemPattern::GetListFrameNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
    while (parent && (!frameNode || (parent->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG))) {
        parent = parent->GetParent();
        frameNode = AceType::DynamicCast<FrameNode>(parent);
    }
    return frameNode;
}

RefPtr<FrameNode> ListItemPattern::GetParentFrameNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
    while (parent && !frameNode) {
        parent = parent->GetParent();
        frameNode = AceType::DynamicCast<FrameNode>(parent);
    }
    return frameNode;
}

Axis ListItemPattern::GetAxis() const
{
    auto frameNode = GetListFrameNode();
    CHECK_NULL_RETURN(frameNode, Axis::VERTICAL);
    auto layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, Axis::VERTICAL);
    return layoutProperty->GetListDirection().value_or(Axis::VERTICAL);
}

void ListItemPattern::SetSwiperItemForList()
{
    auto frameNode = GetListFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(listPattern);
    listPattern->SetSwiperItem(AceType::WeakClaim(this));
}

void ListItemPattern::SetOffsetChangeCallBack(OnOffsetChangeFunc&& offsetChangeCallback)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    listItemEventHub->SetOnOffsetChangeOffset(std::move(offsetChangeCallback));
}

void ListItemPattern::CloseSwipeAction(OnFinishFunc&& onFinishCallback)
{
    onFinishEvent_ = onFinishCallback;
    ResetSwipeStatus(true);
}

void ListItemPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    InitOnFocusEvent();
    Pattern::OnModifyDone();
    InitListItemCardStyleForList();
    if (!listItemEventHub->HasStateStyle(UI_STATE_SELECTED)) {
        auto context = host->GetRenderContext();
        CHECK_NULL_VOID(context);
        context->BlendBgColor(GetBlendGgColor());
    }
    if (HasStartNode() || HasEndNode() || listItemEventHub->GetStartOnDelete() || listItemEventHub->GetEndOnDelete()) {
        auto axis = GetAxis();
        bool axisChanged = axis_ != axis;
        axis_ = axis;
        InitSwiperAction(axisChanged);
        return;
    }
    auto gestureHub = listItemEventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->RemovePanEvent(panEvent_);
    panEvent_.Reset();
    springController_.Reset();
    SetAccessibilityAction();
}

V2::SwipeEdgeEffect ListItemPattern::GetEdgeEffect()
{
    auto layoutProperty = GetLayoutProperty<ListItemLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, V2::SwipeEdgeEffect::Spring);
    return layoutProperty->GetEdgeEffect().value_or(V2::SwipeEdgeEffect::Spring);
}

void ListItemPattern::MarkDirtyNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (LessOrEqual(curOffset_, startNodeSize_) && LessOrEqual(-curOffset_, endNodeSize_)) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        return;
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ListItemPattern::ChangeAxis(Axis axis)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    axis_ = axis;
    if (HasStartNode() || HasEndNode() || listItemEventHub->GetStartOnDelete() || listItemEventHub->GetEndOnDelete()) {
        InitSwiperAction(true);
    }
}

void ListItemPattern::InitSwiperAction(bool axisChanged)
{
    bool isPanInit = false;
    if (!panEvent_) {
        auto weak = AceType::WeakClaim(this);
        auto actionStartTask = [weak](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto frameNode = pattern->GetListFrameNode();
            CHECK_NULL_VOID(frameNode);
            auto listPattern = frameNode->GetPattern<ListPattern>();
            CHECK_NULL_VOID(listPattern);
            if (!listPattern->CanReplaceSwiperItem()) {
                return;
            }
            pattern->HandleDragStart(info);
        };

        auto actionUpdateTask = [weak](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto frameNode = pattern->GetListFrameNode();
            CHECK_NULL_VOID(frameNode);
            auto listPattern = frameNode->GetPattern<ListPattern>();
            CHECK_NULL_VOID(listPattern);
            if (!listPattern->IsCurrentSwiperItem(weak) || !pattern->isDragging_) {
                return;
            }
            pattern->HandleDragUpdate(info);
        };

        auto actionEndTask = [weak](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto frameNode = pattern->GetListFrameNode();
            CHECK_NULL_VOID(frameNode);
            auto listPattern = frameNode->GetPattern<ListPattern>();
            CHECK_NULL_VOID(listPattern);
            if (!listPattern->IsCurrentSwiperItem(weak) || !pattern->isDragging_) {
                return;
            }
            pattern->HandleDragEnd(info);
        };

        auto actionCancelTask = [weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto frameNode = pattern->GetListFrameNode();
            CHECK_NULL_VOID(frameNode);
            auto listPattern = frameNode->GetPattern<ListPattern>();
            CHECK_NULL_VOID(listPattern);
            if (!listPattern->IsCurrentSwiperItem(weak) || !pattern->isDragging_) {
                return;
            }
            GestureEvent info;
            pattern->HandleDragEnd(info);
        };
        panEvent_ = MakeRefPtr<PanEvent>(std::move(actionStartTask), std::move(actionUpdateTask),
            std::move(actionEndTask), std::move(actionCancelTask));
        isPanInit = true;
    }
    if (isPanInit || axisChanged) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetOrCreateEventHub<EventHub>();
        CHECK_NULL_VOID(hub);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        PanDirection panDirection = {
            .type = axis_ == Axis::HORIZONTAL ? PanDirection::VERTICAL : PanDirection::HORIZONTAL,
        };
        PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
            { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
        gestureHub->AddPanEvent(panEvent_, panDirection, 1, distanceMap);

        startNodeSize_ = 0.0f;
        endNodeSize_ = 0.0f;
        float oldOffset = curOffset_;
        curOffset_ = 0.0f;
        FireSwipeActionOffsetChange(oldOffset, curOffset_);
    }
    if (!springController_) {
        springController_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    } else if (axisChanged) {
        springController_->Stop();
    }
}

void ListItemPattern::HandleDragStart(const GestureEvent& info)
{
    if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
        return;
    }
    if (springController_ && !springController_->IsStopped()) {
        // clear stop listener before stop
        springController_->ClearStopListeners();
        springController_->Stop();
    }
    isDragging_ = true;
    isSpringMotionRunning_ = false;
    SetSwiperItemForList();
}

float ListItemPattern::CalculateFriction(float gamma)
{
    float ratio = SWIPE_RATIO;
    if (GreatOrEqual(gamma, 1.0)) {
        gamma = 1.0f;
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        ratio = NEW_SWIPE_RATIO;
        return exp(-ratio * gamma);
    }
    float result = ratio * std::pow(1.0 - gamma, SQUARE);
    if (!std::isnan(result) && LessNotEqual(result, 1.0f)) {
        return result;
    }
    return 1.0f;
}

float ListItemPattern::GetFriction()
{
    if (GreatNotEqual(curOffset_, 0.0f)) {
        float width = startNodeSize_;
        float itemWidth = GetContentSize().CrossSize(axis_);
        if (width < curOffset_) {
            return CalculateFriction((curOffset_ - width) / (itemWidth - width));
        }
    } else if (LessNotEqual(curOffset_, 0.0f)) {
        float width = endNodeSize_;
        float itemWidth = GetContentSize().CrossSize(axis_);
        if (width < -curOffset_) {
            return CalculateFriction((-curOffset_ - width) / (itemWidth - width));
        }
    }
    return 1.0f;
}

void ListItemPattern::ChangeDeleteAreaStage()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    auto enterStartDeleteArea = listItemEventHub->GetOnEnterStartDeleteArea();
    auto enterEndDeleteArea = listItemEventHub->GetOnEnterEndDeleteArea();
    auto exitStartDeleteArea = listItemEventHub->GetOnExitStartDeleteArea();
    auto exitEndDeleteArea = listItemEventHub->GetOnExitEndDeleteArea();
    if (Positive(curOffset_) && hasStartDeleteArea_) {
        if (GreatOrEqual(curOffset_, startNodeSize_ + startDeleteAreaDistance_)) {
            if (!inStartDeleteArea_) {
                inStartDeleteArea_ = true;
                if (enterStartDeleteArea) {
                    enterStartDeleteArea();
                }
            }
        } else {
            if (inStartDeleteArea_) {
                inStartDeleteArea_ = false;
                if (exitStartDeleteArea) {
                    exitStartDeleteArea();
                }
            }
        }
    }
    if (Negative(curOffset_) && hasEndDeleteArea_) {
        if (GreatNotEqual(-curOffset_, endNodeSize_ + endDeleteAreaDistance_)) {
            if (!inEndDeleteArea_) {
                inEndDeleteArea_ = true;
                if (enterEndDeleteArea) {
                    enterEndDeleteArea();
                }
            }
        } else {
            if (inEndDeleteArea_) {
                inEndDeleteArea_ = false;
                if (exitEndDeleteArea) {
                    exitEndDeleteArea();
                }
            }
        }
    }
}

void ListItemPattern::UpdatePostion(float delta)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    auto offset = curOffset_;
    IsRTLAndVertical() ? curOffset_ -= delta : curOffset_ += delta;
    ChangeDeleteAreaStage();
    auto edgeEffect = GetEdgeEffect();
    if (edgeEffect == V2::SwipeEdgeEffect::None) {
        if (hasStartDeleteArea_) {
            if (Positive(startNodeSize_) && GreatNotEqual(curOffset_, startNodeSize_ + startDeleteAreaDistance_)) {
                curOffset_ = startNodeSize_ + startDeleteAreaDistance_;
            } else if (startNodeSize_ == 0 && GreatNotEqual(curOffset_, startDeleteAreaDistance_)) {
                curOffset_ = startDeleteAreaDistance_;
            }
        }
        if (hasEndDeleteArea_) {
            if (Positive(endNodeSize_) && GreatNotEqual(-curOffset_, endNodeSize_ + endDeleteAreaDistance_)) {
                curOffset_ = -endNodeSize_ - endDeleteAreaDistance_;
            } else if (endNodeSize_ == 0 && GreatNotEqual(-curOffset_, endDeleteAreaDistance_)) {
                curOffset_ = -endDeleteAreaDistance_;
            }
        }
        if (Positive(startNodeSize_) && GreatNotEqual(curOffset_, startNodeSize_) && !hasStartDeleteArea_) {
            curOffset_ = startNodeSize_;
        } else if (Positive(endNodeSize_) && GreatNotEqual(-curOffset_, endNodeSize_) && !hasEndDeleteArea_) {
            curOffset_ = -endNodeSize_;
        }
        if ((Negative(curOffset_) && !HasEndNode() && !listItemEventHub->GetEndOnDelete()) ||
            (Positive(curOffset_) && !HasStartNode() && !listItemEventHub->GetStartOnDelete())) {
            curOffset_ = 0.0f;
        }
    }
    if (!NearEqual(offset, curOffset_)) {
        MarkDirtyNode();
        FireSwipeActionOffsetChange(offset, curOffset_);
    }
}

bool ListItemPattern::IsRTLAndVertical() const
{
    auto layoutProperty = GetLayoutProperty<ListItemLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
    if (layoutDirection == TextDirection::RTL && axis_ == Axis::VERTICAL) {
        return true;
    } else {
        return false;
    }
}

void ListItemPattern::HandleDragUpdate(const GestureEvent& info)
{
    if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
        return;
    }
    auto layoutProperty = GetLayoutProperty<ListItemLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    hasStartDeleteArea_ = false;
    hasEndDeleteArea_ = false;
    float itemWidth = GetContentSize().CrossSize(axis_);
    float maxDeleteArea = 0.0f;

    if (GreatNotEqual(curOffset_, 0.0)) {
        maxDeleteArea = itemWidth - startNodeSize_;
        startDeleteAreaDistance_ = static_cast<float>(
            layoutProperty->GetStartDeleteAreaDistance().value_or(Dimension(0, DimensionUnit::VP)).ConvertToPx());
        if (GreatNotEqual(startDeleteAreaDistance_, 0.0) && LessNotEqual(startDeleteAreaDistance_, maxDeleteArea)) {
            hasStartDeleteArea_ = true;
        }
    } else if (LessNotEqual(curOffset_, 0.0)) {
        maxDeleteArea = itemWidth - endNodeSize_;
        endDeleteAreaDistance_ = static_cast<float>(
            layoutProperty->GetEndDeleteAreaDistance().value_or(Dimension(0, DimensionUnit::VP)).ConvertToPx());
        if (GreatNotEqual(endDeleteAreaDistance_, 0.0) && LessNotEqual(endDeleteAreaDistance_, maxDeleteArea)) {
            hasEndDeleteArea_ = true;
        }
    }
    float delta = info.GetMainDelta();
    delta *= GetFriction();
    UpdatePostion(delta);
}

void ListItemPattern::StartSpringMotion(float start, float end, float velocity, bool trigOnFinishEvent)
{
    if (!springController_) {
        return;
    }
    const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
        AceType::MakeRefPtr<SpringProperty>(SWIPE_SPRING_MASS, SWIPE_SPRING_STIFFNESS, SWIPE_SPRING_DAMPING);
    if (!springMotion_) {
        springMotion_ = AceType::MakeRefPtr<SpringMotion>(start, end, velocity, DEFAULT_OVER_SPRING_PROPERTY);
    } else {
        springMotion_->Reset(start, end, velocity, DEFAULT_OVER_SPRING_PROPERTY);
        springMotion_->ClearListeners();
    }
    // 10000.0f: use a large value to mask the determination of speed threshold
    springMotion_->SetVelocityAccuracy(10000.0f);
    springMotion_->AddListener([weakScroll = AceType::WeakClaim(this), start, end](double position) {
        auto listItem = weakScroll.Upgrade();
        CHECK_NULL_VOID(listItem);
        if (listItem->GetEdgeEffect() == V2::SwipeEdgeEffect::None &&
            ((GreatNotEqual(end, start) && GreatOrEqual(position, end)) ||
            (LessNotEqual(end, start) && LessOrEqual(position, end)))) {
            listItem->springController_->ClearStopListeners();
            listItem->springController_->Stop();
            position = end;
        }
        if (NearEqual(position, listItem->curOffset_, 1.0) && !listItem->isSpringMotionRunning_) {
            listItem->isSpringMotionRunning_ = true;
            AceAsyncTraceBeginCommercial(0, TRAILING_ANIMATION);
        }
        float delta = listItem->IsRTLAndVertical() ? listItem->curOffset_ - position : position - listItem->curOffset_;
        listItem->UpdatePostion(delta);
    });
    springController_->ClearStopListeners();
    springController_->PlayMotion(springMotion_);
    springController_->AddStopListener([weak = AceType::WeakClaim(this), trigOnFinishEvent]() {
        auto listItem = weak.Upgrade();
        CHECK_NULL_VOID(listItem);
        if (NearZero(listItem->curOffset_)) {
            listItem->FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
            listItem->ResetNodeSize();
            listItem->FireSwipeActionOffsetChange(SWIPE_SPRING_MASS, listItem->curOffset_);
        }
        if (listItem->isSpringMotionRunning_) {
            listItem->isSpringMotionRunning_ = false;
            AceAsyncTraceEndCommercial(0, TRAILING_ANIMATION);
        }
        listItem->MarkDirtyNode();
        if (trigOnFinishEvent) {
            listItem->FireOnFinishEvent();
        }
    });
}

void ListItemPattern::DoDeleteAnimation(bool isStartDelete)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    float itemWidth = GetContentSize().CrossSize(axis_);

    AnimationOption option = AnimationOption();
    option.SetDuration(DELETE_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    option.SetFillMode(FillMode::FORWARDS);
    context->OpenImplicitAnimation(option, option.GetCurve(), nullptr);
    float oldOffset = curOffset_;
    curOffset_ = isStartDelete ? itemWidth : -itemWidth;
    FireSwipeActionOffsetChange(oldOffset, curOffset_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();
    context->CloseImplicitAnimation();
    FireSwipeActionStateChange(ListItemSwipeIndex::SWIPER_ACTION);
}

void ListItemPattern::FireSwipeActionOffsetChange(float oldOffset, float newOffset)
{
    if (NearEqual(oldOffset, newOffset)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    listItemEventHub->FireOffsetChangeEvent(Dimension(newOffset).ConvertToVp());
}

void ListItemPattern::FireSwipeActionStateChange(ListItemSwipeIndex newSwiperIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_LIST, "ListItem:%{public}d swiperIndex origin:%{public}d, new:%{public}d, "
        "curPos:%{public}f", host->GetId(), swiperIndex_, newSwiperIndex, curOffset_);
    if (newSwiperIndex == swiperIndex_) {
        return;
    }
    auto oldState = swipeActionState_;
    auto listItemEventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);

    bool trigStart = GreatNotEqual(curOffset_, 0.0f);
    switch (newSwiperIndex) {
        case ListItemSwipeIndex::SWIPER_START:
        case ListItemSwipeIndex::SWIPER_END:
            swipeActionState_ = SwipeActionState::EXPANDED;
            break;
        case ListItemSwipeIndex::SWIPER_ACTION:
            swipeActionState_ = SwipeActionState::ACTIONING;
            break;
        case ListItemSwipeIndex::ITEM_CHILD:
        default:
            if (swiperIndex_ == ListItemSwipeIndex::SWIPER_START) {
                trigStart = true;
            } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_END) {
                trigStart = false;
            }
            swipeActionState_ = SwipeActionState::COLLAPSED;
    }
    if (swipeActionState_ != oldState) {
        if (swipeActionState_ == SwipeActionState::COLLAPSED) {
            host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        }
        if (swipeActionState_ == SwipeActionState::EXPANDED) {
            host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        }
    }
    swiperIndex_ = newSwiperIndex;
    listItemEventHub->FireStateChangeEvent(swipeActionState_, trigStart);
    UpdateClickJudgeCallback();
}

void ListItemPattern::UpdateClickJudgeCallback()
{
    auto frameNode = GetListFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(listPattern);
    auto scrollableEvent = listPattern->GetScrollableEvent();
    CHECK_NULL_VOID(scrollableEvent);
    if (swipeActionState_ == SwipeActionState::COLLAPSED) {
        TAG_LOGI(AceLogTag::ACE_LIST, "List:%{public}d RemoveClickJudgeCallback", frameNode->GetId());
        scrollableEvent->SetClickJudgeCallback(nullptr);
    } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        auto clickJudgeCallback = [weak = WeakClaim(this)](const PointF& localPoint) -> bool {
            auto item = weak.Upgrade();
            CHECK_NULL_RETURN(item, false);
            if (item->swipeActionState_ == SwipeActionState::COLLAPSED) {
                return false;
            }
            return item->ClickJudge(localPoint);
        };
        TAG_LOGI(AceLogTag::ACE_LIST, "List:%{public}d AddClickJudgeCallback", frameNode->GetId());
        scrollableEvent->SetClickJudgeCallback(clickJudgeCallback);
    }
}

void ListItemPattern::HandleDragEnd(const GestureEvent& info)
{
    if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
        return;
    }

    auto listPattern = GetListFrameNode()->GetPattern<ListPattern>();
    CHECK_NULL_VOID(listPattern);
    listPattern->SetSwiperItemEnd(AceType::WeakClaim(this));

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    auto startOnDelete = listItemEventHub->GetStartOnDelete();
    auto endOnDelete = listItemEventHub->GetEndOnDelete();
    float end = 0.0f;
    float friction = GetFriction();
    float threshold = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE) ? NEW_SWIPER_TH : SWIPER_TH;
    float velocity = IsRTLAndVertical() ? -info.GetMainVelocity() : info.GetMainVelocity();
    bool reachRightSpeed = velocity > SWIPER_SPEED_TH;
    bool reachLeftSpeed = -velocity > SWIPER_SPEED_TH;
    isDragging_ = false;

    TAG_LOGI(AceLogTag::ACE_LIST, "ListItem:%{public}d HandleDragEnd, velocity:%{public}f, curPos:%{public}f",
        host->GetId(), velocity, curOffset_);
    if (swiperIndex_ != ListItemSwipeIndex::SWIPER_ACTION && hasStartDeleteArea_ && !HasStartNode() && startOnDelete &&
        GreatOrEqual(curOffset_, startDeleteAreaDistance_) && swiperIndex_ != ListItemSwipeIndex::SWIPER_END) {
        DoDeleteAnimation(true);
        startOnDelete();
        return;
    } else if (hasStartDeleteArea_ && !HasStartNode()) {
        FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
    }

    if (swiperIndex_ != ListItemSwipeIndex::SWIPER_ACTION && hasEndDeleteArea_ && !HasEndNode() && endOnDelete &&
        GreatOrEqual(-curOffset_, endDeleteAreaDistance_) && swiperIndex_ != ListItemSwipeIndex::SWIPER_START) {
        DoDeleteAnimation(false);
        endOnDelete();
        return;
    } else if (hasEndDeleteArea_ && !HasEndNode()) {
        FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
    }

    if ((GreatNotEqual(curOffset_, 0.0) || !HasEndNode()) && HasStartNode()) {
        float width = startNodeSize_;
        if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD && reachLeftSpeed) {
            StartSpringMotion(curOffset_, 0, velocity * friction);
            FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
            return;
        }
        if (swiperIndex_ != ListItemSwipeIndex::SWIPER_ACTION && swiperIndex_ != ListItemSwipeIndex::SWIPER_END &&
            GreatOrEqual(curOffset_, width + startDeleteAreaDistance_) && hasStartDeleteArea_ && startOnDelete) {
            DoDeleteAnimation(true);
            startOnDelete();
            return;
        }
        if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD && width > 0 &&
            (curOffset_ > width * threshold || reachRightSpeed)) {
            FireSwipeActionStateChange(ListItemSwipeIndex::SWIPER_START);
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_START && (curOffset_ < width *
                  (1 - threshold) || (reachLeftSpeed && curOffset_ < width))) {
            FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_END ||
                   swiperIndex_ == ListItemSwipeIndex::SWIPER_ACTION) {
            FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
        }
        end = width * static_cast<int32_t>(swiperIndex_);
    } else if ((LessNotEqual(curOffset_, 0.0) || !HasStartNode()) && HasEndNode()) {
        float width = endNodeSize_;
        if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD && reachRightSpeed) {
            StartSpringMotion(curOffset_, 0, velocity * friction);
            FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
            return;
        }
        if (swiperIndex_ != ListItemSwipeIndex::SWIPER_ACTION && swiperIndex_ != ListItemSwipeIndex::SWIPER_START &&
            GreatOrEqual(-curOffset_, width + endDeleteAreaDistance_) && hasEndDeleteArea_ && endOnDelete) {
            DoDeleteAnimation(false);
            endOnDelete();
            return;
        }
        if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD && width > 0 &&
            (width * threshold < -curOffset_ || reachLeftSpeed)) {
            FireSwipeActionStateChange(ListItemSwipeIndex::SWIPER_END);
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_END && (-curOffset_ < width *
                  (1 - threshold) || (reachRightSpeed && -curOffset_ < width))) {
            FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_START ||
                   swiperIndex_ == ListItemSwipeIndex::SWIPER_ACTION) {
            FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
        }
        end = width * static_cast<int32_t>(swiperIndex_);
    }
    StartSpringMotion(curOffset_, end, velocity * friction);
}

void ListItemPattern::ResetSwipeStatus(bool calledByUser)
{
    if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD) {
        return;
    }
    FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
    float velocity = 0.0f;
    if (springMotion_) {
        velocity = springMotion_->GetCurrentVelocity();
    }
    if (springController_ && !springController_->IsStopped()) {
        // clear stop listener before stop
        springController_->ClearStopListeners();
        springController_->Stop();
    }
    StartSpringMotion(curOffset_, 0.0f, velocity, calledByUser);
}

void ListItemPattern::MarkIsSelected(bool isSelected)
{
    if (isSelected_ != isSelected) {
        isSelected_ = isSelected;
        auto eventHub = GetOrCreateEventHub<ListItemEventHub>();
        eventHub->FireSelectChangeEvent(isSelected);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (isSelected) {
            eventHub->UpdateCurrentUIState(UI_STATE_SELECTED);
            host->OnAccessibilityEvent(AccessibilityEventType::SELECTED);
        } else {
            eventHub->ResetCurrentUIState(UI_STATE_SELECTED);
            host->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
        }
        if (!eventHub->HasStateStyle(UI_STATE_SELECTED)) {
            auto context = host->GetRenderContext();
            CHECK_NULL_VOID(context);
            context->BlendBgColor(GetBlendGgColor());
        }
    }
}

void ListItemPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    json->PutFixedAttr("selectable", selectable_, filter, FIXED_ATTR_SELECTABLE);
    json->PutExtAttr("selected", isSelected_, filter);
}

void ListItemPattern::SwipeCommon(ListItemSwipeIndex targetState)
{
    bool isForward = (targetState == ListItemSwipeIndex::SWIPER_END);
    ListItemSwipeIndex checkPosition = targetState;
    ListItemSwipeIndex oppositePosition = isForward ? ListItemSwipeIndex::SWIPER_START : ListItemSwipeIndex::SWIPER_END;
    float collapsedOffset = isForward ? -1.0f : 1.0f;

    auto itemPosition = GetSwiperIndex();
    if (itemPosition == checkPosition) {
        return;
    }

    if (GetSwipeActionState() == SwipeActionState::COLLAPSED) {
        curOffset_ = collapsedOffset;
        MarkDirtyNode();
        pendingSwipeFunc_ = [weakPtr = WeakClaim(this), targetState]() {
            const auto& pattern = weakPtr.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireSwipeActionStateChange(targetState);

            float targetOffset =
                (targetState == ListItemSwipeIndex::SWIPER_END) ? -(pattern->endNodeSize_) : pattern->startNodeSize_;
            pattern->StartSpringMotion(pattern->curOffset_, targetOffset, 0.0f, true);
        };
    }

    if (itemPosition == oppositePosition) {
        FireSwipeActionStateChange(ListItemSwipeIndex::ITEM_CHILD);
        StartSpringMotion(curOffset_, 0.0f, 0.0f, true);
    }
}

void ListItemPattern::SwipeForward()
{
    SwipeCommon(ListItemSwipeIndex::SWIPER_END);
}

void ListItemPattern::SwipeBackward()
{
    SwipeCommon(ListItemSwipeIndex::SWIPER_START);
}

SwipeActionState ListItemPattern::GetSwipeActionState()
{
    return swipeActionState_;
}

void ListItemPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemAccessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(listItemAccessibilityProperty);
    listItemAccessibilityProperty->SetActionSelect([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->Selectable()) {
            return;
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetRenderContext();
        CHECK_NULL_VOID(context);
        context->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
        pattern->MarkIsSelected(true);
        context->OnMouseSelectUpdate(true, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
    });

    listItemAccessibilityProperty->SetActionClearSelection([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->Selectable()) {
            return;
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetRenderContext();
        CHECK_NULL_VOID(context);
        pattern->MarkIsSelected(false);
        context->OnMouseSelectUpdate(false, ITEM_FILL_COLOR, ITEM_FILL_COLOR);
    });
    
    listItemAccessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_EQUAL_VOID(pattern->Selectable(), false);
        pattern->SwipeForward();
    });

    listItemAccessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_EQUAL_VOID(pattern->Selectable(), false);
        pattern->SwipeBackward();
    });
}

void ListItemPattern::InitListItemCardStyleForList()
{
    if (listItemStyle_ == V2::ListItemStyle::CARD) {
        UpdateListItemAlignToCenter();
        InitHoverEvent();
        InitPressEvent();
        InitDisableEvent();
    }
}

void ListItemPattern::SetListItemStyle(V2::ListItemStyle style)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (listItemStyle_ == V2::ListItemStyle::NONE && style == V2::ListItemStyle::CARD) {
        listItemStyle_ = style;
        SetListItemDefaultAttributes(host);
        InitListItemCardStyleForList();
    }
}

void ListItemPattern::UpdateListItemAlignToCenter()
{
    auto frameNode = GetListFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->HasListItemAlign()) {
        layoutProperty->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    }
}

Color ListItemPattern::GetBlendGgColor()
{
    Color color = Color::TRANSPARENT;
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, color);
    auto theme = pipeline->GetTheme<ListItemTheme>();
    CHECK_NULL_RETURN(theme, color);
    if (isSelected_) {
        auto eventHub = GetOrCreateEventHub<ListItemEventHub>();
        CHECK_NULL_RETURN(eventHub, color);
        if (!eventHub->HasStateStyle(UI_STATE_SELECTED)) {
            color = theme->GetItemSelectedColor();
        }
    }
    if (isPressed_) {
        color = color.BlendColor(theme->GetItemPressColor());
    } else if (isHover_) {
        color = color.BlendColor(theme->GetItemHoverColor());
    }
    return color;
}

void ListItemPattern::InitHoverEvent()
{
    if (hoverEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleHoverEvent(isHover, pattern->GetHost());
        }
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void ListItemPattern::HandleHoverEvent(bool isHover, const RefPtr<NG::FrameNode>& itemNode)
{
    auto renderContext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ListItemTheme>();
    CHECK_NULL_VOID(theme);

    isHover_ = isHover;
    auto hoverColor = GetBlendGgColor();
    AnimationUtils::BlendBgColorAnimation(
        renderContext, hoverColor, theme->GetHoverAnimationDuration(), Curves::FRICTION);
}

void ListItemPattern::InitPressEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto touchType = info.GetTouches().front().GetTouchType();
        if (touchType == TouchType::DOWN || touchType == TouchType::UP || touchType == TouchType::CANCEL) {
            pattern->HandlePressEvent(touchType == TouchType::DOWN, pattern->GetHost());
        }
    };
    auto touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void ListItemPattern::HandlePressEvent(bool isPressed, const RefPtr<NG::FrameNode>& itemNode)
{
    auto renderContext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ListItemTheme>();
    CHECK_NULL_VOID(theme);
    auto duration = isHover_ ? theme->GetHoverToPressAnimationDuration() : theme->GetHoverAnimationDuration();
    isPressed_ = isPressed;
    Color color = GetBlendGgColor();
    AnimationUtils::BlendBgColorAnimation(renderContext, color, duration, Curves::SHARP);
}

void ListItemPattern::InitDisableEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ListItemTheme>();
    CHECK_NULL_VOID(theme);
    auto userDefineOpacity = renderContext->GetOpacityValue(1.0);

    if (!eventHub->IsDeveloperEnabled()) {
        if (selectable_) {
            selectable_ = false;
        }
        enableOpacity_ = renderContext->GetOpacityValue(1.0);
        renderContext->UpdateOpacity(theme->GetItemDisabledAlpha());
    } else {
        if (enableOpacity_.has_value()) {
            renderContext->UpdateOpacity(enableOpacity_.value());
        } else {
            renderContext->UpdateOpacity(userDefineOpacity);
        }
    }
}

bool ListItemPattern::GetLayouted() const
{
    return isLayouted_;
}

void ListItemPattern::DumpAdvanceInfo()
{
    DumpLog::GetInstance().AddDesc("indexInList:" + std::to_string(indexInList_));
    DumpLog::GetInstance().AddDesc("indexInListItemGroup:" + std::to_string(indexInListItemGroup_));
    DumpLog::GetInstance().AddDesc("swiperAction.startNodeIndex:" + std::to_string(startNodeIndex_));
    DumpLog::GetInstance().AddDesc("swiperAction.endNodeIndex:" + std::to_string(endNodeIndex_));
    DumpLog::GetInstance().AddDesc("swiperAction.childNodeIndex:" + std::to_string(childNodeIndex_));
    DumpLog::GetInstance().AddDesc("curOffset:" + std::to_string(curOffset_));
    DumpLog::GetInstance().AddDesc("startNodeSize:" + std::to_string(startNodeSize_));
    DumpLog::GetInstance().AddDesc("endNodeSize:" + std::to_string(endNodeSize_));
    DumpLog::GetInstance().AddDesc("startDeleteAreaDistance:" + std::to_string(startDeleteAreaDistance_));
    DumpLog::GetInstance().AddDesc("endDeleteAreaDistance:" + std::to_string(endDeleteAreaDistance_));
    switch (swipeActionState_) {
        case SwipeActionState::COLLAPSED:
            DumpLog::GetInstance().AddDesc("SwipeActionState::COLLAPSED");
            break;
        case SwipeActionState::EXPANDED:
            DumpLog::GetInstance().AddDesc("SwipeActionState::EXPANDED");
            break;
        case SwipeActionState::ACTIONING:
            DumpLog::GetInstance().AddDesc("SwipeActionState::ACTIONING");
            break;
    }
    hasStartDeleteArea_ ? DumpLog::GetInstance().AddDesc("hasStartDeleteArea:true")
                     : DumpLog::GetInstance().AddDesc("hasStartDeleteArea:false");
    hasEndDeleteArea_ ? DumpLog::GetInstance().AddDesc("hasEndDeleteArea:true")
                     : DumpLog::GetInstance().AddDesc("hasEndDeleteArea:false");
    inStartDeleteArea_ ? DumpLog::GetInstance().AddDesc("inStartDeleteArea:true")
                     : DumpLog::GetInstance().AddDesc("inStartDeleteArea:false");
    inEndDeleteArea_ ? DumpLog::GetInstance().AddDesc("inEndDeleteArea:true")
                     : DumpLog::GetInstance().AddDesc("inEndDeleteArea:false");
    selectable_ ? DumpLog::GetInstance().AddDesc("selectable:true")
                : DumpLog::GetInstance().AddDesc("selectable:false");
    isSelected_ ? DumpLog::GetInstance().AddDesc("isSelected:true")
                : DumpLog::GetInstance().AddDesc("isSelected:false");
    isHover_ ? DumpLog::GetInstance().AddDesc("isHover:true")
                : DumpLog::GetInstance().AddDesc("isHover:false");
    isPressed_ ? DumpLog::GetInstance().AddDesc("isPressed:true")
                : DumpLog::GetInstance().AddDesc("isPressed:false");
    isLayouted_ ? DumpLog::GetInstance().AddDesc("isLayouted:true")
                : DumpLog::GetInstance().AddDesc("isLayouted:false");
    if (enableOpacity_.has_value()) {
        enableOpacity_.value() ? DumpLog::GetInstance().AddDesc("enableOpacity:true")
                            : DumpLog::GetInstance().AddDesc("enableOpacity:false");
    } else {
        DumpLog::GetInstance().AddDesc("enableOpacity:null");
    }
}

float ListItemPattern::GetEstimateHeight(float estimateHeight, Axis axis) const
{
    auto layoutProperty = GetLayoutProperty<ListItemLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    auto visible = layoutProperty->GetVisibility().value_or(VisibleType::VISIBLE);
    if (visible == VisibleType::GONE) {
        return 0.0f;
    }
    if (!isLayouted_) {
        return estimateHeight;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, estimateHeight);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, estimateHeight);
    return GetMainAxisSize(geometryNode->GetMarginFrameSize(), axis);
}

bool ListItemPattern::ClickJudgeVertical(const SizeF& size, double xOffset, double yOffset)
{
    if (yOffset < 0 || yOffset > size.Height()) {
        return true;
    }
    if (!IsRTLAndVertical()) {
        if (startNodeSize_ && xOffset > 0 && xOffset < startNodeSize_) {
            return false;
        } else if (endNodeSize_ && xOffset > size.Width() - endNodeSize_ && xOffset < size.Width()) {
            return false;
        }
    } else {
        if (endNodeSize_ && xOffset > 0 && xOffset < endNodeSize_) {
            return false;
        } else if (startNodeSize_ && xOffset > size.Width() - startNodeSize_ && xOffset < size.Width()) {
            return false;
        }
    }
    return true;
}

bool ListItemPattern::ClickJudge(const PointF& localPoint)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto offset = geometryNode->GetFrameOffset();
    if (indexInListItemGroup_ != -1) {
        auto parentFrameNode = GetParentFrameNode();
        CHECK_NULL_RETURN(parentFrameNode, false);
        auto parentGeometryNode = parentFrameNode->GetGeometryNode();
        CHECK_NULL_RETURN(parentGeometryNode, false);
        auto parentOffset = parentGeometryNode->GetFrameOffset();
        offset = offset + parentOffset;
    }
    auto size = geometryNode->GetFrameSize();
    auto xOffset = localPoint.GetX() - offset.GetX();
    auto yOffset = localPoint.GetY() - offset.GetY();
    if (GetAxis() == Axis::VERTICAL) {
        return ClickJudgeVertical(size, xOffset, yOffset);
    } else {
        if (xOffset > 0 && xOffset < size.Width()) {
            if (startNodeSize_ && yOffset > 0 && yOffset < startNodeSize_) {
                return false;
            } else if (endNodeSize_ && yOffset > size.Height() - endNodeSize_ && yOffset < size.Height()) {
                return false;
            }
        }
    }
    return true;
}

void ListItemPattern::OnDetachFromMainTree()
{
    auto frameNode = GetListFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(listPattern);
    listPattern->SetSwiperItemEnd(AceType::WeakClaim(this));
    swipeActionState_ = SwipeActionState::COLLAPSED;
}

bool ListItemPattern::RenderCustomChild(int64_t deadline)
{
    if (shallowBuilder_ && !shallowBuilder_->IsExecuteDeepRenderDone()) {
        if (GetSysTimestamp() > deadline) {
            return false;
        }
        shallowBuilder_->ExecuteDeepRender();
        shallowBuilder_.Reset();
    }
    return true;
}

void ListItemPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("indexInList", indexInList_);
    json->Put("indexInListItemGroup", indexInListItemGroup_);
    json->Put("swiperAction.startNodeIndex", startNodeIndex_);
    json->Put("swiperAction.endNodeIndex", endNodeIndex_);
    json->Put("swiperAction.childNodeIndex", childNodeIndex_);
    json->Put("curOffset", curOffset_);
    json->Put("startNodeSize", startNodeSize_);
    json->Put("endNodeSize", endNodeSize_);
    json->Put("startDeleteAreaDistance", startDeleteAreaDistance_);
    json->Put("endDeleteAreaDistance", endDeleteAreaDistance_);

    switch (swipeActionState_) {
        case SwipeActionState::COLLAPSED:
            json->Put("SwipeActionState", "COLLAPSED");
            break;
        case SwipeActionState::EXPANDED:
            json->Put("SwipeActionState", "EXPANDED");
            break;
        case SwipeActionState::ACTIONING:
            json->Put("SwipeActionState", "ACTIONING");
            break;
    }
    json->Put("hasStartDeleteArea", hasStartDeleteArea_);
    json->Put("hasEndDeleteArea", hasEndDeleteArea_);
    json->Put("inStartDeleteArea", inStartDeleteArea_);
    json->Put("inEndDeleteArea", inEndDeleteArea_);
    json->Put("selectable", selectable_);
    json->Put("isSelected", isSelected_);
    json->Put("isHover", isHover_);
    json->Put("isPressed", isPressed_);
    json->Put("isLayouted", isLayouted_);
    json->Put("hasStartDeleteArea", hasStartDeleteArea_);
    if (enableOpacity_.has_value()) {
        json->Put("enableOpacity", enableOpacity_.value() ? "true:" : "false");
    }
}

void ListItemPattern::InitOnFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetOnFocusInternal([weak = WeakClaim(this)](FocusReason reason) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusEvent();
        }
    });
}

void ListItemPattern::HandleFocusEvent()
{
    auto list = GetListFrameNode();
    CHECK_NULL_VOID(list);
    int32_t groupIndex = GetIndexInListItemGroup();
    auto pattern = list->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFocusIndex(GetIndexInList());
    if (groupIndex >= 0) {
        pattern->SetGroupFocusIndex(groupIndex);
    } else {
        pattern->ResetGroupFocusIndex();
    }
}

bool ListItemPattern::FindHeadOrTailChild(const RefPtr<FocusHub>& childFocus, FocusStep step, WeakPtr<FocusHub>& target)
{
    CHECK_NULL_RETURN(childFocus, false);
    // Support moving focus to the first item of the List when pressing HOME
    // and to the last item of the List when pressing END.
    auto isHome = step == FocusStep::LEFT_END || step == FocusStep::UP_END;
    auto isEnd = step == FocusStep::RIGHT_END || step == FocusStep::DOWN_END;
    bool isFindTailOrHead = false;
    if (isHome) {
        isFindTailOrHead = childFocus->AnyChildFocusHub([&target](const RefPtr<FocusHub>& node) {
            auto headNode = node->GetHeadOrTailChild(true);
            if (headNode) {
                target = headNode;
                return true;
            }
            return false;
        });
    } else if (isEnd) {
        isFindTailOrHead = childFocus->AnyChildFocusHub(
            [&target](const RefPtr<FocusHub>& node) {
                auto tailNode = node->GetHeadOrTailChild(false);
                if (tailNode) {
                    target = tailNode;
                    return true;
                }
                return false;
            },
            true);
    }
    return isFindTailOrHead;
}
} // namespace OHOS::Ace::NG
