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

#include <sys/time.h>
#include "base/log/dump_log.h"
#include "core/components_ng/pattern/container_picker/container_picker_paint_method.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const std::string CONTAINER_PICKER_DRAG_SCENE = "container_picker_drag_scene";
constexpr double MOVE_THRESHOLD = 2.0;
constexpr int32_t CLICK_ANIMATION_DURATION = 300;
constexpr uint32_t CUSTOM_SPRING_ANIMATION_DURATION = 1000;
constexpr float DEFAULT_SPRING_RESPONSE = 0.416f;
constexpr float DEFAULT_SPRING_DAMP = 0.99f;
constexpr float ITEM_HEIGHT_PX = 40.0 * 3.25;
constexpr int32_t VELOCITY_TRANS = 1000;
constexpr float PICKER_SPEED_TH = 0.25f;
constexpr int32_t DEFAULT_FONT_SIZE = 20;
constexpr float MIN_TIME = 1.0f;
} // namespace

RefPtr<LayoutAlgorithm> ContainerPickerPattern::CreateLayoutAlgorithm()
{
    auto layoutAlgorithm = MakeRefPtr<ContainerPickerLayoutAlgorithm>();
    CHECK_NULL_RETURN(layoutAlgorithm, nullptr);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    layoutAlgorithm->SetTotalItemCount(host->TotalChildCount());
    layoutAlgorithm->SetCurrentDelta(currentDelta_);
    layoutAlgorithm->SetSelectedIndex(selectedIndex_);
    layoutAlgorithm->SetItemPosition(itemPosition_);
    layoutAlgorithm->SetContentMainSize(contentMainSize_);
    layoutAlgorithm->SetHeight(height_);
    layoutAlgorithm->SetIsLoop(isLoop_);
    return layoutAlgorithm;
}

RefPtr<NodePaintMethod> ContainerPickerPattern::CreateNodePaintMethod()
{
    auto paint = MakeRefPtr<ContainerPickerPaintMethod>();
    return paint;
}

PaddingPropertyF ContainerPickerPattern::CustomizeSafeAreaPadding(PaddingPropertyF safeAreaPadding, bool needRotate)
{
    safeAreaPadding.top = std::nullopt;
    safeAreaPadding.bottom = std::nullopt;
    return safeAreaPadding;
}

bool ContainerPickerPattern::AccumulatingTerminateHelper(
    RectF& adjustingRect, ExpandEdges& totalExpand, bool fromSelf, LayoutSafeAreaType ignoreType)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (host->IsScrollableAxisInsensitive()) {
        return false;
    }
    auto expandFromPicker =
        host->GetAccumulatedSafeAreaExpand(false, { .type = ignoreType, .edges = LAYOUT_SAFE_AREA_EDGE_HORIZONTAL });
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto frameRect = geometryNode->GetFrameRect();
    totalExpand = totalExpand.Plus(AdjacentExpandToRect(adjustingRect, expandFromPicker, frameRect));
    return true;
}

bool ContainerPickerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout && !isNeedStartInertialAnimation_) {
        return false;
    }

    FireChangeEvent();
    dragOffset_ += currentDelta_;
    currentDelta_ = 0.0f;
    auto layoutAlgorithmWrapper = dirty->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto pickerAlgorithm = DynamicCast<ContainerPickerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(pickerAlgorithm, false);
    GetLayoutProperties(pickerAlgorithm);
    PostIdleTask(GetHost());
    SetDefaultTextStyle();
    HandleTargetIndex(dirty, pickerAlgorithm);

    if (isNeedStartInertialAnimation_) {
        StartInertialAnimation();
    }
    return false;
}

float ContainerPickerPattern::ShortestDistanceBetweenCurrentAndTarget()
{
    int32_t targetIndex = targetIndex_.value();
    if (!isLoop_) {
        auto deltaIndex = targetIndex - selectedIndex_;
        return PICKER_ITEM_DEFAULT_HEIGHT * deltaIndex;
    }
    auto forwardDelta = (targetIndex - selectedIndex_ + totalItemCount_) % totalItemCount_;
    auto backwardDelta = (selectedIndex_ - targetIndex + totalItemCount_) % totalItemCount_;
    return forwardDelta <= backwardDelta ? forwardDelta * PICKER_ITEM_DEFAULT_HEIGHT
                                         : backwardDelta * PICKER_ITEM_DEFAULT_HEIGHT * -1;
}

void ContainerPickerPattern::HandleTargetIndex(
    const RefPtr<LayoutWrapper>& dirty, const RefPtr<ContainerPickerLayoutAlgorithm>& algo)
{
    if (!targetIndex_.has_value()) {
        return;
    }
    if (targetIndex_.value() == selectedIndex_) {
        targetIndex_.reset();
        return;
    }
    auto props = GetLayoutProperty<ContainerPickerLayoutProperty>();
    CHECK_NULL_VOID(props);
    if (isTargetAnimationRunning_) {
        return;
    }
    float targetPos = ShortestDistanceBetweenCurrentAndTarget();
    isTargetAnimationRunning_ = true;
    runningTargetIndex_ = targetIndex_;
    auto context = GetContext();
    if (context) {
        context->AddAfterLayoutTask([weak = WeakClaim(this), targetPos]() {
            auto picker = weak.Upgrade();
            CHECK_NULL_VOID(picker);
            picker->CreateSwipeToTargetAnimation(0.0, targetPos);
        });
    }
    targetIndex_.reset();
}

void ContainerPickerPattern::PostIdleTask(const RefPtr<FrameNode>& frameNode)
{
    if (offScreenItemsIndex_.empty()) {
        return;
    }
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddPredictTask(
        [weak = WeakClaim(RawPtr(frameNode))](int64_t deadline, bool canUseLongPredictTask) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
            CHECK_NULL_VOID(pattern);
            if (!canUseLongPredictTask || !pattern->GetRequestLongPredict()) {
                pattern->PostIdleTask(frameNode);
                return;
            }
            auto offScreenItemsIndex = pattern->GetOffScreemItems();
            for (auto it = offScreenItemsIndex.begin(); it != offScreenItemsIndex.end();) {
                if (GetSysTimestamp() > deadline) {
                    break;
                }
                ACE_SCOPED_TRACE("Picker cached self index: %d", *it);
                auto wrapper = frameNode->GetOrCreateChildByIndex(*it, false, true);
                if (!wrapper) {
                    it = offScreenItemsIndex.erase(it);
                    continue;
                }
                auto childNode = wrapper->GetHostNode();
                if (childNode && childNode->GetGeometryNode()) {
                    childNode->GetGeometryNode()->SetParentLayoutConstraint(pattern->GetLayoutConstraint());
                    FrameNode::ProcessOffscreenNode(childNode);
                }
                it = offScreenItemsIndex.erase(it);
            }
            pattern->SetOffScreemItems(offScreenItemsIndex);
            if (!offScreenItemsIndex.empty()) {
                pattern->PostIdleTask(frameNode);
            }
        });
}

void ContainerPickerPattern::GetLayoutProperties(const RefPtr<ContainerPickerLayoutAlgorithm>& algo)
{
    CHECK_NULL_VOID(algo);
    layoutConstraint_ = algo->GetLayoutConstraint();
    itemPosition_ = std::move(algo->GetItemPosition());
    currentOffset_ -= algo->GetCurrentOffset();
    offScreenItemsIndex_ = algo->GetOffScreemItems();
    contentMainSize_ = algo->GetContentMainSize();
    height_ = algo->GetHeight();
    crossMatchChild_ = algo->IsCrossMatchChild();
}

void ContainerPickerPattern::OnAttachToFrameNode()
{
    CreateAnimation();
    UpdatePanEvent();
    UpdateClipEdge();
}

void ContainerPickerPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    InitMouseAndPressEvent();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    containerPickerId_ = host->GetId();
    totalItemCount_ = host->TotalChildCount();
    isLoop_ = IsLoop();
    host->MarkDirtyNode((crossMatchChild_ ? PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD : PROPERTY_UPDATE_MEASURE_SELF) |
                        PROPERTY_UPDATE_RENDER);
}

void ContainerPickerPattern::FireChangeEvent()
{
    auto currentMiddleItem =
        ContainerPickerUtils::CalcCurrentMiddleItem(itemPosition_, height_, totalItemCount_, isLoop_);
    auto newSelectedIndex_ = currentMiddleItem.first;
    if (newSelectedIndex_ != selectedIndex_) {
        selectedIndex_ = newSelectedIndex_;
        auto pickerEventHub = GetEventHub<ContainerPickerEventHub>();
        CHECK_NULL_VOID(pickerEventHub);
        pickerEventHub->FireChangeEvent(selectedIndex_);
    }
}

void ContainerPickerPattern::FireScrollStopEvent()
{
    auto pickerEventHub = GetEventHub<ContainerPickerEventHub>();
    CHECK_NULL_VOID(pickerEventHub);
    pickerEventHub->FireScrollStopEvent(selectedIndex_);
}

void ContainerPickerPattern::UpdateClipEdge()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateClipEdge(true);
}

bool ContainerPickerPattern::IsLoop() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (displayCount_ >= totalItemCount_) {
        return false;
    }
    auto props = GetLayoutProperty<ContainerPickerLayoutProperty>();
    CHECK_NULL_RETURN(props, true);
    return props->GetCanLoopValue(true);
}

void ContainerPickerPattern::SetDefaultTextStyle() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    for (const auto& item : itemPosition_) {
        auto index = ContainerPickerUtils::GetLoopIndex(item.first, totalItemCount_);
        auto child = DynamicCast<FrameNode>(host->GetOrCreateChildByIndex(index));
        SetDefaultTextStyle(child);
    }
}

void ContainerPickerPattern::SetDefaultTextStyle(RefPtr<FrameNode> node) const
{
    CHECK_NULL_VOID(node);
    if (node->GetTag() == V2::TEXT_ETS_TAG) {
        auto textLayoutProperty = node->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        bool modified = false;
        if (!textLayoutProperty->GetFontSize().has_value()) {
            textLayoutProperty->UpdateFontSize(Dimension(DEFAULT_FONT_SIZE, DimensionUnit::FP));
            modified = true;
        }
        if (!textLayoutProperty->GetTextColor().has_value()) {
            textLayoutProperty->UpdateTextColor(Color::FromString("#66182431"));
            modified = true;
        }

        if (modified) {
            node->MarkModifyDone();
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    } else {
        auto& children = node->GetChildren();
        for (const auto& child : children) {
            if (!child) {
                continue;
            }
            auto childNode = DynamicCast<FrameNode>(child);
            SetDefaultTextStyle(childNode);
        }
    }
}

void ContainerPickerPattern::SwipeTo(int32_t targetIndex)
{
    // If animation is still running, stop it before play new animation.
    if (selectedIndex_ == targetIndex || isTargetAnimationRunning_) {
        return;
    }

    targetIndex_ = targetIndex;
    PickerMarkDirty();
}

void ContainerPickerPattern::OnAroundButtonClick(RefPtr<ContainerPickerEventParam> param)
{
    if (clickBreak_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    for (auto& pos : itemPosition_) {
        if (param->itemNodeId == pos.second.node->GetId()) {
            int32_t realIndex = ContainerPickerUtils::GetLoopIndex(pos.first, totalItemCount_);
            SwipeTo(realIndex);
            break;
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

void ContainerPickerPattern::CreateChildrenClickEvent(RefPtr<UINode>& host)
{
    CHECK_NULL_VOID(host);
    const auto& children = host->GetChildren();
    for (auto child : children) {
        auto tag = child->GetTag();
        if (tag == V2::JS_FOR_EACH_ETS_TAG || tag == V2::JS_SYNTAX_ITEM_ETS_TAG) {
            CreateChildrenClickEvent(child);
        } else if (tag == V2::ROW_ETS_TAG || tag == V2::IMAGE_ETS_TAG ||
                   tag == V2::TEXT_ETS_TAG || tag == V2::SYMBOL_ETS_TAG) {
            RefPtr<ContainerPickerEventParam> param = MakeRefPtr<ContainerPickerEventParam>();
            param->itemNodeId = child->GetId();
            RefPtr<FrameNode> childNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(childNode);
            auto eventHub = childNode->GetEventHub<EventHub>();
            CHECK_NULL_VOID(eventHub);
            RefPtr<ClickEvent> clickListener = CreateItemClickEventListener(param);
            CHECK_NULL_VOID(clickListener);
            auto gesture = eventHub->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(gesture);
            gesture->AddClickEvent(clickListener);
        } else {
            TAG_LOGI(AceLogTag::ACE_CONTAINER_PICKER,
                "CreateChildrenClickEvent does not support this type of the node. id: %{public}d, tag: %{public}s",
                host->GetId(), tag.c_str());
        }
    }
}

RefPtr<TouchEventImpl> ContainerPickerPattern::CreateItemTouchEventListener()
{
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetTouches().empty()) {
            return;
        }

        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            if (pattern->isInertialRolling) {
                pattern->touchBreak_ = true;
                pattern->animationBreak_ = true;
                pattern->clickBreak_ = true;
                pattern->StopInertialRollingAnimation();
            } else {
                pattern->animationBreak_ = false;
                pattern->clickBreak_ = false;
            }
        }

        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            pattern->touchBreak_ = false;
            if (pattern->animationBreak_) {
                pattern->PlayResetAnimation();
            }
        }
    };
    auto listener = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    return listener;
}

void ContainerPickerPattern::InitMouseAndPressEvent()
{
    if (isItemClickEventCreated_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto pickerEventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(pickerEventHub);
    RefPtr<TouchEventImpl> touchListener = CreateItemTouchEventListener();
    CHECK_NULL_VOID(touchListener);
    auto pickerGesture = pickerEventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(pickerGesture);
    pickerGesture->AddTouchEvent(touchListener);

    auto uiNode = AceType::DynamicCast<UINode>(host);
    CreateChildrenClickEvent(uiNode);
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

    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
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

    yLast_ = info.GetGlobalPoint().GetY();
    dragStartTime_ = GetCurrentTime();

    dragOffset_ = 0.0f;
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
    animationBreak_ = false;

    auto offsetY =
        info.GetGlobalPoint().GetY() + (info.GetInputEventType() == InputEventType::AXIS ? info.GetOffsetY() : 0.0);
    if (NearEqual(offsetY, yLast_, MOVE_THRESHOLD)) {
        return;
    }

    float mainDelta = static_cast<float>(info.GetMainDelta());
    ProcessDelta(mainDelta, contentMainSize_, mainDeltaSum_);
    mainDeltaSum_ += mainDelta;
    currentDelta_ -= mainDelta;

    HandleScroll(mainDelta, SCROLL_FROM_UPDATE, NestedState::GESTURE, velocity);
    UpdateColumnChildPosition(offsetY);
    dragEndTime_ = GetCurrentTime();
}

void ContainerPickerPattern::HandleDragEnd(double dragVelocity, float mainDelta)
{
    UpdateDragFRCSceneInfo(dragVelocity, SceneStatus::END);
    isDragging_ = false;

    if (!isLoop_) {
        // spring back
    }

    // Throw and slide
    if (Play(dragVelocity)) {
        return;
    }

    // Drag and slide
    if (!animationCreated_) {
        PickerMarkDirty();
        return;
    }

    // Adjust the position to ensure it is centered.
    dragOffsetForAnimation_ += dragOffset_;
    float totalOffset = (-animationOffset_) + (-dragOffsetForAnimation_);
    float resetOffset = CalculateResetOffset(totalOffset);
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
    float totalOffset = endOffset + (-animationOffset_) + (-dragOffsetForAnimation_);
    float resetOffset = CalculateResetOffset(totalOffset);
    endOffset -= resetOffset;
}

bool ContainerPickerPattern::Play(double dragVelocity)
{
    auto timeDiff = dragEndTime_ - dragStartTime_;
    if (timeDiff < MIN_TIME) {
        return false;
    }

    if (std::abs(dragVelocity / VELOCITY_TRANS) < PICKER_SPEED_TH) {
        return false;
    }

    isNeedStartInertialAnimation_ = true;
    dragVelocity_ = dragVelocity;
    PickerMarkDirty();
    return true;
}

void ContainerPickerPattern::StartInertialAnimation()
{
    AnimationOption option;
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);
    if (!snapOffsetProperty_) {
        CreateSnapProperty();
    }

    float endOffset = 0.0f;
    dragOffsetForAnimation_ += dragOffset_;
    CalcEndOffset(endOffset, dragVelocity_);
    snapOffsetProperty_->Set(0.0f);
    snapOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    auto finishCallback = [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->animationBreak_) {
            pattern->dragOffsetForAnimation_ = 0.0f;
            pattern->lastAnimationScroll_ = 0.0f;
            pattern->animationOffset_ = 0.0f;
        }
        pattern->isInertialRolling = false;
    };
    snapOffsetProperty_->AnimateWithVelocity(option, -endOffset, dragVelocity_, finishCallback);
    isNeedStartInertialAnimation_ = false;
}

void ContainerPickerPattern::UpdateDragFRCSceneInfo(float speed, SceneStatus sceneStatus)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddFRCSceneInfo(CONTAINER_PICKER_DRAG_SCENE, speed, sceneStatus);
}

ScrollResult ContainerPickerPattern::HandleScroll(float offset, int32_t source, NestedState state, float velocity)
{
    PickerMarkDirty();
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
            PickerMarkDirty();
        }
        dragDelta = additionalShift;
    }
    return dragDelta;
}

void ContainerPickerPattern::UpdateColumnChildPosition(double offsetY)
{
    double dragDelta = offsetY - yLast_;
    ContainerPickerDirection dir =
        GreatNotEqual(dragDelta, 0.0) ? ContainerPickerDirection::DOWN : ContainerPickerDirection::UP;
    auto shiftDistance = (dir == ContainerPickerDirection::UP) ? -ITEM_HEIGHT_PX : ITEM_HEIGHT_PX;
    auto useRebound = !isLoop_;
    auto stopMove = SpringCurveTailMoveProcess(useRebound, dragDelta);

    dragDelta = GetDragDeltaLessThanJumpInterval(offsetY, dragDelta, useRebound, shiftDistance);
    yOffset_ = dragDelta;
    yLast_ = offsetY;
    PickerMarkDirty();
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
        pattern->animationOffset_ = value;
        pattern->PickerMarkDirty();
    };
    scrollProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    renderContext->AttachNodeAnimatableProperty(scrollProperty_);

    auto aroundClickCallback = [weak = AceType::WeakClaim(this)](float value) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->currentDelta_ = value - pattern->lastAnimationScroll_;
        pattern->lastAnimationScroll_ = value;
        pattern->animationOffset_ = value;
        pattern->PickerMarkDirty();
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
        if (pattern->touchBreak_) {
            return;
        }
        pattern->currentDelta_ = position - pattern->lastAnimationScroll_;
        pattern->lastAnimationScroll_ = position;
        pattern->animationOffset_ += pattern->currentDelta_;
        pattern->isInertialRolling = true;
        pattern->PickerMarkDirty();
    };
    snapOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    AttachNodeAnimatableProperty(snapOffsetProperty_);
}

void ContainerPickerPattern::CreateAnimation(double from, double to)
{
    dragOffsetForAnimation_ += dragOffset_;
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(CLICK_ANIMATION_DURATION);
    scrollProperty_->Set(from);
    auto host = GetHost();
    auto context = host ? host->GetContextRefPtr() : nullptr;
    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(this), to]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->scrollProperty_->Set(to);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->dragOffsetForAnimation_ = 0.0f;
            pattern->lastAnimationScroll_ = 0.0f;
            pattern->animationOffset_ = 0.0f;
            pattern->FireScrollStopEvent();
        }, nullptr, context);
}

void ContainerPickerPattern::CreateSwipeToTargetAnimation(double from, double to)
{
    lastAnimationScroll_ = 0.0f;
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(CLICK_ANIMATION_DURATION);
    scrollProperty_->Set(from);
    auto host = GetHost();
    auto context = host ? host->GetContextRefPtr() : nullptr;
    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(this), to]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->scrollProperty_->Set(to);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->dragOffsetForAnimation_ = 0.0f;
            pattern->lastAnimationScroll_ = 0.0f;
            pattern->animationOffset_ = 0.0f;
            pattern->FireScrollStopEvent();
            pattern->isTargetAnimationRunning_ = false;
        }, nullptr, context);
}

void ContainerPickerPattern::PickerMarkDirty()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!crossMatchChild_) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
}

void ContainerPickerPattern::StopInertialRollingAnimation()
{
    isInertialRolling = false;
    AnimationOption option;
    option.SetCurve(Curves::LINEAR);
    option.SetDuration(0);
    option.SetDelay(0);
    auto host = GetHost();
    auto context = host ? host->GetContextRefPtr() : nullptr;

    AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->snapOffsetProperty_->Set(0.0f);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->lastAnimationScroll_ = 0.0f;
        });
}

void ContainerPickerPattern::PlayResetAnimation()
{
    float totalOffset = (-animationOffset_) + (-dragOffsetForAnimation_);
    float resetOffset = CalculateResetOffset(totalOffset);
    CreateAnimation(0.0f, resetOffset);
}

double ContainerPickerPattern::GetCurrentTime() const
{
    struct timeval tv {};
    int32_t result = gettimeofday(&tv, nullptr);
    if (result != 0) {
        return 0.0;
    }

    double sec = static_cast<double>(tv.tv_sec);
    double msec = static_cast<double>(tv.tv_usec / 1000.0); // usec / 1000 is msec
    return (sec * 1000 + msec);                             // sec * 1000 is msec
}

float ContainerPickerPattern::CalculateResetOffset(float totalOffset)
{
    ContainerPickerDirection dir = GreatNotEqual(animationOffset_ + dragOffsetForAnimation_, 0.0f) ?
        ContainerPickerDirection::UP : ContainerPickerDirection::DOWN;
    int32_t n = std::trunc(totalOffset) / ITEM_HEIGHT_PX;
    float distance = std::abs(totalOffset - ITEM_HEIGHT_PX * n);
    float resetOffset = 0.0f;
    if (GreatNotEqual(distance, ITEM_HEIGHT_PX * 0.5f)) {
        resetOffset = (ITEM_HEIGHT_PX - distance) * (dir == ContainerPickerDirection::UP ? 1 : -1);
    } else if (LessNotEqual(distance, ITEM_HEIGHT_PX * 0.5f)) {
        resetOffset = distance * (dir == ContainerPickerDirection::UP ? -1 : 1);
    }
    return resetOffset;
}

} // namespace OHOS::Ace::NG
