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
#include "core/components_ng/pattern/list/list_item_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SWIPER_TH = 0.25f;
constexpr float SWIPER_SPEED_TH = 1200.f;
constexpr float SWIPE_RATIO = 0.6f;
constexpr float SWIPE_SPRING_MASS = 1.f;
constexpr float SWIPE_SPRING_STIFFNESS = 228.f;
constexpr float SWIPE_SPRING_DAMPING = 30.f;
constexpr int32_t DELETE_ANIMATION_DURATION = 400;
} // namespace

RefPtr<LayoutAlgorithm> ListItemPattern::CreateLayoutAlgorithm()
{
    if (!HasStartNode() && !HasEndNode()) {
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
        }
    } else if (HasStartNode()) {
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
        }
    } else if (HasEndNode()) {
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

void ListItemPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    if (HasStartNode() || HasEndNode()) {
        auto axis = GetAxis();
        bool axisChanged = axis_ != axis;
        axis_ = axis;
        InitSwiperAction(axisChanged);
        return;
    }
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

void ListItemPattern::InitSwiperAction(bool axisChanged)
{
    bool isPanInit = false;
    if (!panEvent_) {
        auto weak = AceType::WeakClaim(this);
        auto actionStartTask = [weak](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleDragStart(info);
        };

        auto actionUpdateTask = [weak](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleDragUpdate(info);
        };

        auto actionEndTask = [weak](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
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
        float distance = static_cast<float>(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP).ConvertToPx());
        gestureHub->AddPanEvent(panEvent_, panDirection, 1, distance);

        startNodeSize_ = 0.0f;
        endNodeSize_ = 0.0f;
        curOffset_ = 0.0f;
    }
    if (!springController_) {
        springController_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
    }
}

void ListItemPattern::HandleDragStart(const GestureEvent& info)
{
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
    return ratio * std::pow(1.0 - gamma, SQUARE);
}

float ListItemPattern::GetFriction()
{
    if (GreatNotEqual(curOffset_, 0.0f)) {
        float width = startNodeSize_;
        float itemWidth = GetContentSize().CrossSize(axis_);
        if (hasStartDeleteArea_) {
            if (width + startDeleteAreaDistance_ < curOffset_) {
                return CalculateFriction(
                    (curOffset_ - width - startDeleteAreaDistance_) / (itemWidth - width));
            }
            return 1.0f;
        }
        if (width < curOffset_) {
            return CalculateFriction((curOffset_ - width) / (itemWidth - width));
        }
    } else if (LessNotEqual(curOffset_, 0.0f)) {
        float width = endNodeSize_;
        float itemWidth = GetContentSize().CrossSize(axis_);
        if (hasEndDeleteArea_) {
            if (width + endDeleteAreaDistance_ < -curOffset_) {
                return CalculateFriction(
                    (-curOffset_ - width - endDeleteAreaDistance_) / (itemWidth - width));
            }
            return 1.0f;
        }
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
    if (Positive(startNodeSize_) && hasStartDeleteArea_) {
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
    if (Positive(endNodeSize_) && hasEndDeleteArea_) {
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
    float offset = curOffset_;
    curOffset_ += delta;
    ChangeDeleteAreaStage();
    auto edgeEffect = GetEdgeEffect();
    if (edgeEffect == V2::SwipeEdgeEffect::None) {
        if (Positive(startNodeSize_)) {
            if (hasStartDeleteArea_ && GreatNotEqual(curOffset_, startNodeSize_ + startDeleteAreaDistance_)) {
                curOffset_ = startNodeSize_ + startDeleteAreaDistance_;
            } else if (!hasStartDeleteArea_ && GreatNotEqual(curOffset_, startNodeSize_)) {
                curOffset_ = startNodeSize_;
            }
        }
        if (Positive(endNodeSize_)) {
            if (hasEndDeleteArea_ && GreatNotEqual(-curOffset_, endNodeSize_ + endDeleteAreaDistance_)) {
                curOffset_ = -endNodeSize_ - endDeleteAreaDistance_;
            } else if (!hasEndDeleteArea_ && GreatNotEqual(-curOffset_, endNodeSize_)) {
                curOffset_ = -endNodeSize_;
            }
        }
        if ((Negative(curOffset_) && !HasEndNode()) || (Positive(curOffset_) && !HasStartNode())) {
            curOffset_ = 0.0f;
        }
    }
    if (!NearEqual(offset, curOffset_)) {
        MarkDirtyNode();
    }
}

void ListItemPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto layoutProperty = GetLayoutProperty<ListItemLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    hasStartDeleteArea_ = false;
    hasEndDeleteArea_ = false;
    float itemWidth = GetContentSize().CrossSize(axis_);
    float movableDistance = 0.0f;

    if (GreatNotEqual(curOffset_, 0.0) && HasStartNode()) {
        movableDistance = itemWidth - startNodeSize_;
        startDeleteAreaDistance_ = static_cast<float>(
            layoutProperty->GetStartDeleteAreaDistance().value_or(Dimension(0, DimensionUnit::VP)).ConvertToPx());
        if (GreatNotEqual(startDeleteAreaDistance_, 0.0) && LessNotEqual(startDeleteAreaDistance_, movableDistance)) {
            hasStartDeleteArea_ = true;
        }
    } else if (LessNotEqual(curOffset_, 0.0) && HasEndNode()) {
        movableDistance = itemWidth - endNodeSize_;
        endDeleteAreaDistance_ = static_cast<float>(
            layoutProperty->GetEndDeleteAreaDistance().value_or(Dimension(0, DimensionUnit::VP)).ConvertToPx());
        if (GreatNotEqual(endDeleteAreaDistance_, 0.0) && LessNotEqual(endDeleteAreaDistance_, movableDistance)) {
            hasEndDeleteArea_ = true;
        }
    }
    float delta = info.GetMainDelta();
    delta *= GetFriction();
    UpdatePostion(delta);
}

void ListItemPattern::StartSpringMotion(float start, float end, float velocity)
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
    springController_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto listItem = weak.Upgrade();
        CHECK_NULL_VOID(listItem);
        listItem->MarkDirtyNode();
    });
}

void ListItemPattern::DoDeleteAnimation(const GestureEvent& info, const OnDeleteEvent& onDelete, bool isRightDelete)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    float itemWidth = GetContentSize().CrossSize(axis_);
    float friction = GetFriction();

    AnimationOption option = AnimationOption();
    option.SetDuration(DELETE_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    option.SetFillMode(FillMode::FORWARDS);
    context->OpenImplicitAnimation(option, option.GetCurve(),
        [weak = AceType::WeakClaim(this), onDelete = onDelete, info = info, friction = friction,
            renderContext = renderContext, isRightDelete = isRightDelete]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            onDelete();
            float end = 0.0f;
            if (isRightDelete) {
                pattern->swiperIndex_ = ListItemSwipeIndex::SWIPER_START;
                end = pattern->startNodeSize_ * static_cast<int32_t>(pattern->swiperIndex_);
            } else {
                pattern->swiperIndex_ = ListItemSwipeIndex::SWIPER_END;
                end = pattern->endNodeSize_ * static_cast<int32_t>(pattern->swiperIndex_);
            }
            pattern->StartSpringMotion(pattern->curOffset_, end, info.GetMainVelocity() * friction);
        });
    curOffset_ = isRightDelete ? itemWidth : -itemWidth;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();
    context->CloseImplicitAnimation();
}

void ListItemPattern::HandleDragEnd(const GestureEvent& info)
{
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

    if (GreatNotEqual(curOffset_, 0.0) && HasStartNode()) {
        float width = startNodeSize_;
        if (hasStartDeleteArea_ && startOnDelete && GreatOrEqual(curOffset_, width + startDeleteAreaDistance_)) {
            if (!useStartDefaultDeleteAnimation_) {
                startOnDelete();
            } else {
                DoDeleteAnimation(info, startOnDelete, true);
                return;
            }
        }
        if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD && (curOffset_ > width * threshold || reachRightSpeed)) {
            swiperIndex_ = ListItemSwipeIndex::SWIPER_START;
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_START &&
            (curOffset_ < width * (1 - threshold) || (reachLeftSpeed && curOffset_ < width))) {
            swiperIndex_ = ListItemSwipeIndex::ITEM_CHILD;
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_END) {
            swiperIndex_ = ListItemSwipeIndex::ITEM_CHILD;
        }
        end = width * static_cast<int32_t>(swiperIndex_);
    } else if (LessNotEqual(curOffset_, 0.0) && HasEndNode()) {
        float width = endNodeSize_;
        if (hasEndDeleteArea_ && endOnDelete && GreatOrEqual(-curOffset_, width + endDeleteAreaDistance_)) {
            if (!useEndDefaultDeleteAnimation_) {
                endOnDelete();
            } else {
                DoDeleteAnimation(info, endOnDelete, false);
                return;
            }
        }
        if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD && (width * threshold < -curOffset_ || reachLeftSpeed)) {
            swiperIndex_ = ListItemSwipeIndex::SWIPER_END;
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_END &&
            (-curOffset_ < width * (1 - threshold) || (reachRightSpeed && -curOffset_ < width))) {
            swiperIndex_ = ListItemSwipeIndex::ITEM_CHILD;
        } else if (swiperIndex_ == ListItemSwipeIndex::SWIPER_START) {
            swiperIndex_ = ListItemSwipeIndex::ITEM_CHILD;
        }
        end = width * static_cast<int32_t>(swiperIndex_);
    }
    StartSpringMotion(curOffset_, end, info.GetMainVelocity() * friction);
}

void ListItemPattern::SwiperReset()
{
    if (swiperIndex_ == ListItemSwipeIndex::ITEM_CHILD) {
        return;
    }
    swiperIndex_ = ListItemSwipeIndex::ITEM_CHILD;
    float velocity = 0.0f;
    if (springMotion_) {
        velocity = springMotion_->GetCurrentVelocity();
    }
    if (springController_ && !springController_->IsStopped()) {
        // clear stop listener before stop
        springController_->ClearStopListeners();
        springController_->Stop();
    }
    StartSpringMotion(curOffset_, 0.0f, velocity);
}

void ListItemPattern::MarkIsSelected(bool isSelected)
{
    if (isSelected_ != isSelected) {
        isSelected_ = isSelected;
        auto eventHub = GetEventHub<ListItemEventHub>();
        auto onSelect = eventHub->GetOnSelect();
        if (onSelect) {
            onSelect(isSelected);
        }
        auto host = GetHost();
        CHECK_NULL_VOID_NOLOG(host);
        if (isSelected) {
            host->OnAccessibilityEvent(AccessibilityEventType::SELECTED);
        } else {
            host->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
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
        pattern->MarkIsSelected(true);
    });

    listItemAccessibilityProperty->SetActionClearSelection([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->Selectable()) {
            return;
        }
        pattern->MarkIsSelected(false);
    });
}
} // namespace OHOS::Ace::NG
