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

#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"

#include "base/log/dump_log.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
    const std::string CONTAINER_PICKER_DRAG_SCENE = "container_picker_drag_scene";
    constexpr double MOVE_THRESHOLD = 2.0;
    constexpr int32_t CLICK_ANIMATION_DURATION = 300;
    constexpr uint32_t CUSTOM_SPRING_ANIMATION_DURATION = 1000;
    constexpr float DEFAULT_SPRING_RESPONSE = 0.416f;
    constexpr float DEFAULT_SPRING_DAMP = 0.99F;
    constexpr float ITEM_HEIGHT_PX = 40.0 * 3.25;
    constexpr int32_t VELOCITY_TRANS = 1000;
    constexpr float PICKER_SPEED_TH = 0.25f;
} // namespace

RefPtr<LayoutAlgorithm> ContainerPickerPattern::CreateLayoutAlgorithm()
{
    auto layoutAlgorithm = MakeRefPtr<ContainerPickerLayoutAlgorithm>();
    CHECK_NULL_RETURN(layoutAlgorithm, nullptr);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    layoutAlgorithm->SetTotalItemCount(host->TotalChildCount());
    layoutAlgorithm->SetCurrentDelta(currentDelta_);
    layoutAlgorithm->SetCurrentIndex(currentIndex_);
    layoutAlgorithm->SetItemsPosition(itemPosition_);
    totalOffset_ = currentIndexOffset_;
    return layoutAlgorithm;
}

bool ContainerPickerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }

    currentDelta_ = 0.0f;
    auto layoutAlgorithmWrapper = dirty->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto pickerAlgorithm = DynamicCast<ContainerPickerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(pickerAlgorithm, false);
    GetLayoutProperties(pickerAlgorithm);
    return false;
}

void ContainerPickerPattern::GetLayoutProperties(const RefPtr<ContainerPickerLayoutAlgorithm>& pickerAlgorithm)
{
    CHECK_NULL_VOID(pickerAlgorithm);
    itemPosition_ = std::move(pickerAlgorithm->GetItemPosition());
    contentMainSize_ = pickerAlgorithm->GetContentMainSize();
}

void ContainerPickerPattern::OnAttachToFrameNode()
{
    CreateAnimation();
    UpdatePanEvent();
}

void ContainerPickerPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    InitMouseAndPressEvent();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    containerPickerId_ = host->GetId();
}

void ContainerPickerPattern::OnAroundButtonClick(RefPtr<ContainerPickerEventParam> param)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    int32_t realIndex = 0;
    int32_t middleIndex = showCount_ / 2;
    for (auto& pos : itemPosition_) {
        if (param->itemNodeId == pos.second.node->GetId()) {
            break;
        }
        realIndex++;
    }

    if (static_cast<int32_t>(itemPosition_.size()) > middleIndex) {
        auto it = itemPosition_.begin();
        std::advance(it, middleIndex);
        PickerItemInfo middleItem = it->second;
        int32_t steps = realIndex - middleIndex;
        if (steps != 0) {
            if (animation_) {
                AnimationUtils::StopAnimation(animation_);
            }
            float distance = ITEM_HEIGHT_PX * steps;

            lastAnimationScroll_ = 0.0f;
            AnimationOption option;
            option.SetCurve(Curves::FAST_OUT_SLOW_IN);
            option.SetDuration(CLICK_ANIMATION_DURATION);
            aroundClickProperty_->Set(0.0);
            animation_ = AnimationUtils::StartAnimation(option, [weak = AceType::WeakClaim(this), distance]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->aroundClickProperty_->Set(distance);
            });
            auto pipeline = host->GetContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->RequestFrame();
        }
    }
}

RefPtr<ClickEvent> ContainerPickerPattern::CreateItemClickEventListener(RefPtr<ContainerPickerEventParam> param)
{
    auto clickEventHandler = [param, weak = WeakClaim(this)](const GestureEvent& /* info */) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnAroundButtonClick(param);
    };

    auto listener = AceType::MakeRefPtr<NG::ClickEvent>(clickEventHandler);
    return listener;
}

void ContainerPickerPattern::InitMouseAndPressEvent()
{
    if (isItemClickEventCreated_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    int32_t i = 0;
    for (const auto& child : host->GetChildren()) {
        RefPtr<FrameNode> childNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(childNode);
        RefPtr<ContainerPickerEventParam> param = MakeRefPtr<ContainerPickerEventParam>();
        param->itemIndex = i;
        param->itemNodeId = child->GetId();
        auto eventHub = childNode->GetEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        RefPtr<ClickEvent> clickListener = CreateItemClickEventListener(param);
        CHECK_NULL_VOID(clickListener);
        auto gesture = eventHub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gesture);
        gesture->AddClickEvent(clickListener);
        i++;
    }
    isItemClickEventCreated_ = true;
}

void ContainerPickerPattern::UpdatePanEvent()
{
    CHECK_NULL_VOID(!panEvent_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    AddPanEvent(gestureHub, ActionStartTask(), ActionUpdateTask(), ActionEndTask(), ActionCancelTask());
}

void ContainerPickerPattern::AddPanEvent(const RefPtr<GestureEventHub>& gestureHub, GestureEventFunc&& actionStart,
    GestureEventFunc&& actionUpdate, GestureEventFunc&& actionEnd, GestureEventNoParameter&& actionCancel)
{
    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }

    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStart), std::move(actionUpdate), std::move(actionEnd), std::move(actionCancel));

    PanDistanceMap distanceMap = {
        { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() }
    };
    panDirection_.type = PanDirection::VERTICAL;
    gestureHub->AddPanEvent(panEvent_, panDirection_, 1, distanceMap);
}

GestureEventFunc ContainerPickerPattern::ActionStartTask()
{
    return [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_CONTAINER_PICKER, "containerPicker drag start. SourceTool: %{public}d, id:%{public}d",
            info.GetSourceTool(), pattern->containerPickerId_);
        if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
            pattern->isFirstAxisAction_ = true;
            return;
        }
        pattern->FireAndCleanScrollingListener();
        pattern->HandleDragStart(info);
    };
}

GestureEventFunc ContainerPickerPattern::ActionUpdateTask()
{
    return [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto infoChecked = info;
        if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
            if (pattern->isFirstAxisAction_) {
                pattern->isFirstAxisAction_ = false;
            }
        } else {
            pattern->HandleDragUpdate(infoChecked);
        }
    };
}

GestureEventFunc ContainerPickerPattern::ActionEndTask()
{
    return [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TAG_LOGI(AceLogTag::ACE_CONTAINER_PICKER,
            "containerPicker drag end. Velocity: %{public}f px/s, SourceTool: %{public}d id:%{public}d",
            info.GetMainVelocity(), info.GetSourceTool(), pattern->containerPickerId_);
        if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
            return;
        }

        auto velocity = info.GetMainVelocity();
        pattern->HandleDragEnd(velocity, info.GetMainDelta());
    };
}

GestureEventNoParameter ContainerPickerPattern::ActionCancelTask()
{
    return [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            TAG_LOGI(AceLogTag::ACE_CONTAINER_PICKER, "containerPicker drag cancel id:%{public}d",
                pattern->containerPickerId_);
            pattern->HandleDragEnd(0.0);
        }
    };
}

void ContainerPickerPattern::HandleDragStart(const GestureEvent& info)
{
    UpdateDragFRCSceneInfo(info.GetMainVelocity(), SceneStatus::START);
    isDragging_ = true;
    mainDeltaSum_ = 0.0f;
    currentIndexOffset_ = 0.0f;
    totalOffset_ = 0.0f;

    yLast_ = info.GetGlobalPoint().GetY();
}

void ContainerPickerPattern::ProcessDelta(float& delta, float mainSize, float deltaSum)
{
    if (std::abs(delta) > mainSize) {
        delta = delta > 0 ? mainSize : -mainSize;
    }

    if ((std::abs(deltaSum + delta)) > mainSize) {
        delta = GreatNotEqual((deltaSum + delta), 0) ? (mainSize - deltaSum) : (-deltaSum - mainSize);
    }
}

void ContainerPickerPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto velocity = info.GetMainVelocity();
    UpdateDragFRCSceneInfo(velocity, SceneStatus::RUNNING);

    auto offsetY = info.GetGlobalPoint().GetY() +
        (info.GetInputEventType() == InputEventType::AXIS ? info.GetOffsetY() : 0.0);
    if (NearEqual(offsetY, yLast_, MOVE_THRESHOLD)) {
        return;
    }

    float mainDelta = static_cast<float>(info.GetMainDelta());
    ProcessDelta(mainDelta, contentMainSize_, mainDeltaSum_);
    mainDeltaSum_ += mainDelta;

    HandleScroll(mainDelta, SCROLL_FROM_UPDATE, NestedState::GESTURE, velocity);
    UpdateColumnChildPosition(offsetY);
}

void ContainerPickerPattern::HandleDragEnd(double dragVelocity, float mainDelta)
{
    UpdateDragFRCSceneInfo(dragVelocity, SceneStatus::END);
    isDragging_ = false;

    if (!IsLoop()) {
        // spring back
    }

    // Throw and slide
    if (Play(dragVelocity)) {
        return;
    }

    // Drag and slide
    if (!animationCreated_) {
        PickerMarkDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        return;
    }

    // Adjust the position to ensure it is centered.
    ContainerPickerDirection dir = GreatNotEqual(totalOffset_, 0.0) ?
        ContainerPickerDirection::UP : ContainerPickerDirection::DOWN;
    int32_t n = std::trunc(totalOffset_) / ITEM_HEIGHT_PX;
    float distance = std::abs(totalOffset_ - ITEM_HEIGHT_PX * n);
    float resetOffset = 0.0f;
    if (distance > (ITEM_HEIGHT_PX * 0.5f)) {
        resetOffset = (ITEM_HEIGHT_PX - distance) * (dir == ContainerPickerDirection::UP ? -1 : 1);
    } else if (distance < (ITEM_HEIGHT_PX * 0.5f)) {
        resetOffset = distance * (dir == ContainerPickerDirection::UP ? 1 : -1);
    }
    CreateAnimation(0.0, resetOffset);
}

void ContainerPickerPattern::CalcEndOffset(float& endOffset, double velocity)
{
    float defaultK = 1.5f;
    float defaultY = 0.75f;
    float a = 1.848f;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t optionItems = host->TotalChildCount();
    float maxItems = 60.0f;
    float realK = exp(-a * (1 - optionItems / maxItems));
    realK = std::min(realK, 1.0f) * defaultK;
    endOffset = realK / (4.2f * defaultY) * velocity * (1 - exp(-defaultY * CUSTOM_SPRING_ANIMATION_DURATION));

    // Adjust the position to ensure it is centered.
    float totalOffset = endOffset + totalOffset_;
    ContainerPickerDirection dir = GreatNotEqual(totalOffset_, 0.0) ?
        ContainerPickerDirection::UP : ContainerPickerDirection::DOWN;
    int32_t n = std::trunc(totalOffset) / ITEM_HEIGHT_PX;
    float distance = std::abs(totalOffset - ITEM_HEIGHT_PX * n);
    float resetOffset = 0.0f;
    if (distance > (ITEM_HEIGHT_PX * 0.5f)) {
        resetOffset = (ITEM_HEIGHT_PX - distance) * (dir == ContainerPickerDirection::UP ? 1 : -1);
    } else if (distance < (ITEM_HEIGHT_PX * 0.5f)) {
        resetOffset = distance * (dir == ContainerPickerDirection::UP ? -1 : 1);
    }
    endOffset += resetOffset;
}

bool ContainerPickerPattern::Play(double dragVelocity)
{
    if (std::abs(dragVelocity / VELOCITY_TRANS) < PICKER_SPEED_TH) {
        return false;
    }
    AnimationOption option;
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);
    if (!snapOffsetProperty_) {
        CreateSnapProperty();
    }
    lastAnimationScroll_ = 0.0f;
    float endOffset = 0.0f;
    CalcEndOffset(endOffset, dragVelocity);
    snapOffsetProperty_->Set(0.0f);
    snapOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    snapOffsetProperty_->AnimateWithVelocity(option, -endOffset,
        dragVelocity, [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
        });
    return true;
}

void ContainerPickerPattern::UpdateDragFRCSceneInfo(float speed, SceneStatus sceneStatus)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddFRCSceneInfo(CONTAINER_PICKER_DRAG_SCENE, speed, sceneStatus);
}

ScrollResult ContainerPickerPattern::HandleScroll(float offset, int32_t source, NestedState state, float velocity)
{
    UpdateCurrentOffset(offset);
    return { 0.0f, false };
}

bool ContainerPickerPattern::HandleScrollVelocity(float velocity, const RefPtr<NestableScrollContainer>& child)
{
    // To do
    return false;
}

void ContainerPickerPattern::OnScrollStartRecursive(
    WeakPtr<NestableScrollContainer> child, float position, float velocity)
{
    // To do
}

void ContainerPickerPattern::OnScrollEndRecursive(const std::optional<float>& velocity)
{
    // To do
}

void ContainerPickerPattern::UpdateCurrentOffset(float offset)
{
    currentDelta_ -= offset;
    currentIndexOffset_ += offset;
    PickerMarkDirty(PROPERTY_UPDATE_MEASURE_SELF);
}

bool ContainerPickerPattern::SpringCurveTailMoveProcess(bool useRebound, double& dragDelta)
{
    if (useRebound) {
        return false;
    }
    return false;
}

void ContainerPickerPattern::SpringCurveTailEndProcess(bool useRebound, bool stopMove)
{
    if (useRebound || !stopMove) {
        return;
    }
}

double ContainerPickerPattern::GetDragDeltaLessThanJumpInterval(
    double offsetY, float originalDragDelta, bool useRebound, float shiftDistance)
{
    double dragDelta = originalDragDelta + yOffset_;
    auto isOverScroll = useRebound;
    if (NearEqual(std::abs(dragDelta), std::abs(shiftDistance)) && !NearZero(dragDelta)) {
        dragDelta = std::abs(dragDelta) / dragDelta * std::abs(shiftDistance);
    }
    if ((std::abs(dragDelta) >= std::abs(shiftDistance)) && !isOverScroll) {
        int32_t shiftDistanceCount = static_cast<int32_t>(std::abs(dragDelta) / std::abs(shiftDistance));
        double additionalShift = dragDelta - shiftDistanceCount * shiftDistance;
        if (GreatNotEqual(std::abs(additionalShift), std::abs(dragDelta))) {
            additionalShift = dragDelta + shiftDistanceCount * shiftDistance;
        }
        for (int32_t i = 0; i < shiftDistanceCount; i++) {
            PickerMarkDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        }
        dragDelta = additionalShift;
    }
    return dragDelta;
}

void ContainerPickerPattern::UpdateColumnChildPosition(double offsetY)
{
    double dragDelta = offsetY - yLast_;
    ContainerPickerDirection dir = GreatNotEqual(dragDelta, 0.0) ?
        ContainerPickerDirection::DOWN : ContainerPickerDirection::UP;
    auto shiftDistance = (dir == ContainerPickerDirection::UP) ? -ITEM_HEIGHT_PX: ITEM_HEIGHT_PX;
    auto useRebound = !IsLoop();
    auto stopMove = SpringCurveTailMoveProcess(useRebound, dragDelta);

    dragDelta = GetDragDeltaLessThanJumpInterval(offsetY, dragDelta, useRebound, shiftDistance);
    yOffset_ = dragDelta;
    yLast_ = offsetY;
    PickerMarkDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    SpringCurveTailEndProcess(useRebound, stopMove);
}

void ContainerPickerPattern::CreateAnimation()
{
    CHECK_NULL_VOID(!animationCreated_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float value) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->currentDelta_ = value - pattern->lastAnimationScroll_;
        pattern->lastAnimationScroll_ = value;
        pattern->PickerMarkDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    };
    scrollProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    renderContext->AttachNodeAnimatableProperty(scrollProperty_);

    auto aroundClickCallback = [weak = AceType::WeakClaim(this)](float value) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->currentDelta_ = value - pattern->lastAnimationScroll_;
        pattern->lastAnimationScroll_ = value;
        pattern->PickerMarkDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    };
    aroundClickProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(aroundClickCallback));
    renderContext->AttachNodeAnimatableProperty(aroundClickProperty_);
    animationCreated_ = true;
}

void ContainerPickerPattern::AttachNodeAnimatableProperty(const RefPtr<NodeAnimatablePropertyFloat>& property)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->AttachNodeAnimatableProperty(property);
}

void ContainerPickerPattern::CreateSnapProperty()
{
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float position) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->currentDelta_ = position - pattern->lastAnimationScroll_;
        pattern->lastAnimationScroll_ = position;
        pattern->PickerMarkDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    };
    snapOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    AttachNodeAnimatableProperty(snapOffsetProperty_);
}

void ContainerPickerPattern::CreateAnimation(double from, double to)
{
    lastAnimationScroll_ = 0.0f;
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(CLICK_ANIMATION_DURATION);
    scrollProperty_->Set(from);
    auto host = GetHost();
    auto context = host? host->GetContextRefPtr(): nullptr;
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), to]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->scrollProperty_->Set(to);
    }, nullptr, nullptr, context);
}

void ContainerPickerPattern::PickerMarkDirty(PropertyChangeFlag extraFlag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(extraFlag);
}

} // namespace OHOS::Ace::NG
