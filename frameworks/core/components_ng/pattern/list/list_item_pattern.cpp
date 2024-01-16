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

#include "base/geometry/axis.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/list/list_item_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SWIPER_TH = 0.25f;
constexpr float SWIPER_SPEED_TH = 1200.f;
constexpr float SWIPE_RATIO = 0.6f;
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

void ListItemPattern::SetListItemDefaultAttributes(const RefPtr<FrameNode>& listItemNode)
{
    auto renderContext = listItemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = listItemNode->GetLayoutProperty<ListItemLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineContext::GetCurrentContext();
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
    auto listItemEventHub = host->GetEventHub<ListItemEventHub>();
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
    return false;
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
        host->RemoveChildAtIndex(startNodeIndex_);
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
        host->RemoveChildAtIndex(endNodeIndex_);
        if (startNodeIndex_ > endNodeIndex_) {
            startNodeIndex_--;
        }
        if (childNodeIndex_ > endNodeIndex_) {
            childNodeIndex_--;
        }
        endNodeIndex_ = -1;
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
    auto listItemEventHub = host->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    if (offsetChangeCallback) {
        listItemEventHub->SetOnOffsetChangeOffset(std::move(offsetChangeCallback));
    }
}

void ListItemPattern::CloseSwipeAction(OnFinishFunc&& onFinishCallback)
{
    onFinishEvent_ = onFinishCallback;
    SwiperReset(true);
}

void ListItemPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
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
    axis_ = axis;
    InitSwiperAction(true);
}

void ListItemPattern::InitSwiperAction(bool axisChanged)
{
    bool isPanInit = false;
    if (!panEvent_) {
        auto weak = AceType::WeakClaim(this);
        auto actionStartTask = [weak](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto listPattern = pattern->GetListFrameNode()->GetPattern<ListPattern>();
            CHECK_NULL_VOID(listPattern);
            if (!listPattern->CanReplaceSwiperItem()) {
                return;
            }
            pattern->HandleDragStart(info);
        };

        auto actionUpdateTask = [weak](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto listPattern = pattern->GetListFrameNode()->GetPattern<ListPattern>();
            CHECK_NULL_VOID(listPattern);
            if (!listPattern->IsCurrentSwiperItem(weak)) {
                return;
            }
            pattern->HandleDragUpdate(info);
        };

        auto actionEndTask = [weak](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto listPattern = pattern->GetListFrameNode()->GetPattern<ListPattern>();
            CHECK_NULL_VOID(listPattern);
            if (!listPattern->IsCurrentSwiperItem(weak)) {
                return;
            }
            pattern->HandleDragEnd(info);
        };
        GestureEventNoParameter actionCancelTask;
        panEvent_ = MakeRefPtr<PanEvent>(std::move(actionStartTask), std::move(actionUpdateTask),
            std::move(actionEndTask), std::move(actionCancelTask));
        isPanInit = true;
    }
    if (isPanInit || axisChanged) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetEventHub<EventHub>();
        CHECK_NULL_VOID(hub);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        PanDirection panDirection = {
            .type = axis_ == Axis::HORIZONTAL ? PanDirection::VERTICAL : PanDirection::HORIZONTAL,
        };
        gestureHub->AddPanEvent(panEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);

        startNodeSize_ = 0.0f;
        endNodeSize_ = 0.0f;
        float oldOffset = curOffset_;
        curOffset_ = 0.0f;
        FireSwipeActionOffsetChange(oldOffset, curOffset_);
    }
    if (!springController_) {
        springController_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    } else {
        springController_->Stop();
    }
}

void ListItemPattern::HandleDragStart(const GestureEvent& info)
{
    if (info.GetInputEventType() == InputEventType::AXIS) {
        return;
    }
    if (springController_ && !springController_->IsStopped()) {
        // clear stop listener before stop
        springController_->ClearStopListeners();
        springController_->Stop();
    }
    SetSwiperItemForList();
}

float ListItemPattern::CalculateFriction(float gamma)
{
    float ratio = SWIPE_RATIO;
    if (GreatOrEqual(gamma, 1.0)) {
        gamma = 1.0f;
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
    auto listItemEventHub = host->GetEventHub<ListItemEventHub>();
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
    auto listItemEventHub = host->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    auto offset = curOffset_;
    curOffset_ += delta;
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

void ListItemPattern::HandleDragUpdate(const GestureEvent& info)
{
    if (info.GetInputEventType() == InputEventType::AXIS) {
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

void ListItemPattern::StartSpringMotion(float start, float end, float velocity, bool isCloseSwipeAction)
{
    if (!springController_) {
        return;
    }

    float mass = SWIPE_SPRING_MASS;
    float stiffness = SWIPE_SPRING_STIFFNESS;
    float damping = SWIPE_SPRING_DAMPING;
    const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
        AceType::MakeRefPtr<SpringProperty>(mass, stiffness, damping);
    if (!springMotion_) {
        springMotion_ = AceType::MakeRefPtr<SpringMotion>(start, end, velocity, DEFAULT_OVER_SPRING_PROPERTY);
    } else {
        springMotion_->Reset(start, end, velocity, DEFAULT_OVER_SPRING_PROPERTY);
        springMotion_->ClearListeners();
    }
    springMotion_->AddListener([weakScroll = AceType::WeakClaim(this), start, end](double position) {
        auto listItem = weakScroll.Upgrade();
        CHECK_NULL_VOID(listItem);
        auto edgeEffect = listItem->GetEdgeEffect();
        if (edgeEffect == V2::SwipeEdgeEffect::None &&
            ((GreatNotEqual(end, start) && GreatOrEqual(position, end)) ||
            (LessNotEqual(end, start) && LessOrEqual(position, end)))) {
            listItem->springController_->ClearStopListeners();
            listItem->springController_->Stop();
            position = end;
        }
        listItem->UpdatePostion(position - listItem->curOffset_);
    });
    springController_->ClearStopListeners();
    springController_->PlayMotion(springMotion_);
    springController_->AddStopListener([weak = AceType::WeakClaim(this), isCloseSwipeAction]() {
        auto listItem = weak.Upgrade();
        CHECK_NULL_VOID(listItem);
        if (NearZero(listItem->curOffset_)) {
            listItem->ResetToItemChild();
            listItem->ResetNodeSize();
            listItem->FireSwipeActionOffsetChange(SWIPE_SPRING_MASS, listItem->curOffset_);
        }
        listItem->MarkDirtyNode();
        if (isCloseSwipeAction) {
            listItem->FireOnFinshEvent();
        }
    });
}

void ListItemPattern::DoDeleteAnimation(bool isRightDelete)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    float itemWidth = GetContentSize().CrossSize(axis_);

    AnimationOption option = AnimationOption();
    option.SetDuration(DELETE_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    option.SetFillMode(FillMode::FORWARDS);
    context->OpenImplicitAnimation(option, option.GetCurve(), nullptr);
    swiperIndex_ = ListItemSwipeIndex::SWIPER_ACTION;
    float oldOffset = curOffset_;
    curOffset_ = isRightDelete ? itemWidth : -itemWidth;
    FireSwipeActionOffsetChange(oldOffset, curOffset_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();
    context->CloseImplicitAnimation();
    FireSwipeActionStateChange(SwipeActionState::ACTIONING);
}

void ListItemPattern::FireSwipeActionOffsetChange(float oldOffset, float newOffset)
{
    if (NearEqual(oldOffset, newOffset)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    listItemEventHub->FireOffsetChangeEvent(Dimension(newOffset).ConvertToVp());
}

void ListItemPattern::FireSwipeActionStateChange(SwipeActionState newState)
{
    if (swipeActionState_ == newState) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    swipeActionState_ = newState;
    bool isStart = GreatNotEqual(curOffset_, 0.0);
    listItemEventHub->FireStateChangeEvent(newState, isStart);
}

void ListItemPattern::HandleDragEnd(const GestureEvent& info)
{
    if (info.GetInputEventType() == InputEventType::AXIS) {
        return;
    }

    auto listPattern = GetListFrameNode()->GetPattern<ListPattern>();
    CHECK_NULL_VOID(listPattern);
    listPattern->SetSwiperItemEnd(AceType::WeakClaim(this));

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    float end = 0.0f;
    float friction = GetFriction();
    float threshold = SWIPER_TH;
    float speedThreshold = SWIPER_SPEED_TH;
    bool reachRightSpeed = info.GetMainVelocity() > speedThreshold;
    bool reachLeftSpeed = -info.GetMainVelocity() > speedThreshold;
    auto startOnDelete = listItemEventHub->GetStartOnDelete();
    auto endOnDelete = listItemEventHub->GetEndOnDelete();

    if (swiperIndex_ != ListItemSwipeIndex::SWIPER_ACTION && hasStartDeleteArea_ && !HasStartNode() && startOnDelete &&
        GreatOrEqual(curOffset_, startDeleteAreaDistance_)) {
        DoDeleteAnimation(true);
        startOnDelete();
        return;
    } else if (hasStartDeleteArea_ && !HasStartNode()) {
        FireSwipeActionStateChange(SwipeActionState::COLLAPSED);
    }

    if (swiperIndex_ != ListItemSwipeIndex::SWIPER_ACTION && hasEndDeleteArea_ && !HasEndNode() && endOnDelete &&
        GreatOrEqual(-curOffset_, endDeleteAreaDistance_)) {
        DoDeleteAnimation(false);
        endOnDelete();
        return;
    } else if (hasEndDeleteArea_ && !HasEndNode()) {
        FireSwipeActionStateChange(SwipeActionState::COLLAPSED);
    }

    if (GreatNotEqual(curOffset_, 0.0) && HasStartNode()) {
        float width = startNodeSize_;
        if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD && reachLeftSpeed) {
            StartSpringMotion(curOffset_, 0, info.GetMainVelocity() * friction);
            FireSwipeActionStateChange(SwipeActionState::COLLAPSED);
            return;
        }
        if (swiperIndex_ != ListItemSwipeIndex::SWIPER_ACTION && hasStartDeleteArea_ && startOnDelete &&
            GreatOrEqual(curOffset_, width + startDeleteAreaDistance_)) {
            DoDeleteAnimation(true);
            startOnDelete();
            return;
        }
        if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD && width > 0 &&
            (curOffset_ > width * threshold || reachRightSpeed)) {
            swiperIndex_ = ListItemSwipeIndex::SWIPER_START;
            FireSwipeActionStateChange(SwipeActionState::EXPANDED);
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_START &&
                   (curOffset_ < width * (1 - threshold) || (reachLeftSpeed && curOffset_ < width))) {
            ResetToItemChild();
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_END ||
                   swiperIndex_ == ListItemSwipeIndex::SWIPER_ACTION) {
            ResetToItemChild();
        }
        end = width * static_cast<int32_t>(swiperIndex_);
    } else if (LessNotEqual(curOffset_, 0.0) && HasEndNode()) {
        float width = endNodeSize_;
        if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD && reachRightSpeed) {
            StartSpringMotion(curOffset_, 0, info.GetMainVelocity() * friction);
            FireSwipeActionStateChange(SwipeActionState::COLLAPSED);
            return;
        }
        if (swiperIndex_ != ListItemSwipeIndex::SWIPER_ACTION && hasEndDeleteArea_ && endOnDelete &&
            GreatOrEqual(-curOffset_, width + endDeleteAreaDistance_)) {
            DoDeleteAnimation(false);
            endOnDelete();
            return;
        }
        if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD && width > 0 &&
            (width * threshold < -curOffset_ || reachLeftSpeed)) {
            swiperIndex_ = ListItemSwipeIndex::SWIPER_END;
            FireSwipeActionStateChange(SwipeActionState::EXPANDED);
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_END &&
                   (-curOffset_ < width * (1 - threshold) || (reachRightSpeed && -curOffset_ < width))) {
            ResetToItemChild();
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_START ||
                   swiperIndex_ == ListItemSwipeIndex::SWIPER_ACTION) {
            ResetToItemChild();
        }
        end = width * static_cast<int32_t>(swiperIndex_);
    }
    StartSpringMotion(curOffset_, end, info.GetMainVelocity() * friction);
}

void ListItemPattern::SwiperReset(bool isCloseSwipeAction)
{
    if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD) {
        return;
    }
    ResetToItemChild();
    float velocity = 0.0f;
    if (springMotion_) {
        velocity = springMotion_->GetCurrentVelocity();
    }
    if (springController_ && !springController_->IsStopped()) {
        // clear stop listener before stop
        springController_->ClearStopListeners();
        springController_->Stop();
    }
    StartSpringMotion(curOffset_, 0.0f, velocity, isCloseSwipeAction);
}

void ListItemPattern::MarkIsSelected(bool isSelected)
{
    if (isSelected_ != isSelected) {
        isSelected_ = isSelected;
        auto eventHub = GetEventHub<ListItemEventHub>();
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

void ListItemPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("selectable", selectable_);
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, color);
    auto theme = pipeline->GetTheme<ListItemTheme>();
    CHECK_NULL_RETURN(theme, color);
    if (isSelected_) {
        auto eventHub = GetEventHub<ListItemEventHub>();
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
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto hoverTask = [weak = WeakClaim(this), host](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleHoverEvent(isHover, host);
        }
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void ListItemPattern::HandleHoverEvent(bool isHover, const RefPtr<NG::FrameNode>& itemNode)
{
    auto renderContext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineContext::GetCurrentContext();
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
    auto touchCallback = [weak = WeakClaim(this), host](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto touchType = info.GetTouches().front().GetTouchType();
        if (touchType == TouchType::DOWN || touchType == TouchType::UP) {
            pattern->HandlePressEvent(touchType == TouchType::DOWN, host);
        }
    };
    auto touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void ListItemPattern::HandlePressEvent(bool isPressed, const RefPtr<NG::FrameNode>& itemNode)
{
    auto renderContext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
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
    auto eventHub = host->GetEventHub<ListItemEventHub>();
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
        lastOpacity_ = enableOpacity_.value() * theme->GetItemDisabledAlpha();
    } else if (enableOpacity_.has_value() && userDefineOpacity == lastOpacity_) {
        lastOpacity_ = enableOpacity_.value();
        enableOpacity_.reset();
    } else {
        lastOpacity_ = userDefineOpacity;
    }
    renderContext->UpdateOpacity(lastOpacity_);
}

bool ListItemPattern::GetLayouted() const
{
    return isLayouted_;
}

float ListItemPattern::GetEstimateHeight(float estimateHeight) const
{
    if (!isLayouted_) {
        return estimateHeight;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, estimateHeight);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, estimateHeight);
    return GetMainAxisSize(geometryNode->GetMarginFrameSize(), axis_);
}
} // namespace OHOS::Ace::NG

