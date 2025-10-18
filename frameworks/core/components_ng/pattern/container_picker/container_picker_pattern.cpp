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

#include <sys/time.h>

#include "base/log/dump_log.h"
#include "core/animation/spring_curve.h"
#include "core/components_ng/pattern/container_picker/container_picker_paint_method.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const std::string CONTAINER_PICKER_DRAG_SCENE = "container_picker_drag_scene";
constexpr double MOVE_THRESHOLD = 2.0;
constexpr float SPRING_DURATION = 600.0f;
constexpr float DEFAULT_SPRING_RESPONSE = 0.416f;
constexpr float DEFAULT_SPRING_DAMP = 0.99f;
constexpr float MIN_TIME = 1.0f;
constexpr float PICKER_SPEED_TH = 0.25f;
constexpr int32_t VELOCITY_TRANS = 1000;
constexpr int32_t DEFAULT_FONT_SIZE = 20;
constexpr int32_t CLICK_ANIMATION_DURATION = 300;
constexpr uint32_t CUSTOM_SPRING_ANIMATION_DURATION = 1000;
const std::string SPRING_PROPERTY_NAME = "spring";
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
    layoutAlgorithm->SetPickerHeight(pickerDefaultHeight_);
    layoutAlgorithm->SetItemHeight(pickerItemHeight_);
    layoutAlgorithm->SetPickerHeightBeforeRotate(pickerHeightBeforeRotate_);
    layoutAlgorithm->SetIsLoop(isLoop_);
    return layoutAlgorithm;
}

RefPtr<NodePaintMethod> ContainerPickerPattern::CreateNodePaintMethod()
{
    const auto props = GetLayoutProperty<ContainerPickerLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    auto safeAreaPaddingProperty = props->GetOrCreateSafeAreaPadding();
    auto paint = MakeRefPtr<ContainerPickerPaintMethod>();
    paint->SetSafeAreaPadding(safeAreaPaddingProperty);
    return paint;
}

PaddingPropertyF ContainerPickerPattern::CustomizeSafeAreaPadding(PaddingPropertyF safeAreaPadding, bool needRotate)
{
    if (!needRotate) {
        safeAreaPadding.top = std::nullopt;
        safeAreaPadding.bottom = std::nullopt;
    } else {
        safeAreaPadding.left = std::nullopt;
        safeAreaPadding.right = std::nullopt;
    }
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
    if (config.skipMeasure && config.skipLayout && !isNeedPlayInertialAnimation_) {
        return false;
    }

    FireChangeEvent();
    currentDelta_ = 0.0f;
    auto layoutAlgorithmWrapper = dirty->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto pickerAlgorithm = DynamicCast<ContainerPickerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(pickerAlgorithm, false);
    GetLayoutProperties(pickerAlgorithm);
    PostIdleTask(GetHost());
    SetDefaultTextStyle();
    SetDefaultAlignment();
    HandleTargetIndex();

    if (isNeedPlayInertialAnimation_) {
        PlayInertialAnimation();
    }
    return false;
}

float ContainerPickerPattern::ShortestDistanceBetweenCurrentAndTarget(int32_t targetIndex)
{
    if (totalItemCount_ <= 0) {
        return 0.0;
    }
    if (!isLoop_) {
        auto deltaIndex = targetIndex - selectedIndex_;
        return pickerItemHeight_ * deltaIndex;
    }
    float currentOffsetFromMiddle = CalculateMiddleLineOffset();
    auto downDelta = (targetIndex - selectedIndex_ + totalItemCount_) % totalItemCount_;
    auto upDelta = (selectedIndex_ - targetIndex + totalItemCount_) % totalItemCount_;
    return downDelta <= upDelta ? downDelta * pickerItemHeight_ - currentOffsetFromMiddle
                                : upDelta * pickerItemHeight_ * -1 + currentOffsetFromMiddle;
}

void ContainerPickerPattern::HandleTargetIndex()
{
    if (!targetIndex_.has_value()) {
        return;
    }
    if (targetIndex_.value() == selectedIndex_) {
        targetIndex_.reset();
        return;
    }
    if (isTargetAnimationRunning_) {	
        return;	
    }
    PlayTargetAnimation();
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
            auto offScreenItemsIndex = pattern->GetOffScreenItems();
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
            pattern->SetOffScreenItems(offScreenItemsIndex);
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
    offScreenItemsIndex_ = algo->GetOffScreenItems();
    contentMainSize_ = algo->GetContentMainSize();
    height_ = algo->GetHeight();
    crossMatchChild_ = algo->IsCrossMatchChild();
}

void ContainerPickerPattern::OnAttachToFrameNode()
{
    CreateAnimation();
    UpdatePanEvent();
    UpdateClipEdge();
    InitDefaultParams();
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

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    PickerMarkDirty();
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

void ContainerPickerPattern::SetDefaultAlignment() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    for (const auto& item : itemPosition_) {
        auto index = ContainerPickerUtils::GetLoopIndex(item.first, totalItemCount_);
        auto child = DynamicCast<FrameNode>(host->GetOrCreateChildByIndex(index));
        auto layoutProperty = child->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }
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
        if (tag == V2::JS_FOR_EACH_ETS_TAG || tag == V2::JS_SYNTAX_ITEM_ETS_TAG || tag == V2::JS_IF_ELSE_ETS_TAG) {
            CreateChildrenClickEvent(child);
        } else if (tag == V2::ROW_ETS_TAG || tag == V2::IMAGE_ETS_TAG || tag == V2::TEXT_ETS_TAG ||
                   tag == V2::SYMBOL_ETS_TAG) {
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
            if (pattern->isInertialRollingAnimationRunning_) {
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
    currentDelta_ = 0.0f;
    springOffset_ = 0.0f;

    yLast_ = info.GetGlobalPoint().GetY();
    dragStartTime_ = GetCurrentTime();

    StopSpringAnimation();
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

    HandleScroll(mainDelta, SCROLL_FROM_UPDATE, NestedState::GESTURE, velocity);
    UpdateColumnChildPosition(offsetY);
    dragEndTime_ = GetCurrentTime();
}

void ContainerPickerPattern::HandleDragEnd(double dragVelocity, float mainDelta)
{
    UpdateDragFRCSceneInfo(dragVelocity, SceneStatus::END);
    isDragging_ = false;

    if (CheckDragOutOfBoundary()) {
        // spring back
        return;
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
    float currentOffsetFromMiddle = CalculateMiddleLineOffset();
    float resetOffset = CalculateResetOffset(currentOffsetFromMiddle);
    CreateAnimation(0.0, resetOffset);
}

void ContainerPickerPattern::StopSpringAnimation()
{
    CHECK_NULL_VOID(springAnimation_);
    CHECK_NULL_VOID(isSpringAnimationRunning_);
    AnimationUtils::StopAnimation(springAnimation_);
    isSpringAnimationRunning_ = false;
}

void ContainerPickerPattern::ProcessDelta(float& delta, float mainSize, float deltaSum)
{
    if (GreatNotEqual(std::abs(delta), mainSize)) {
        delta = delta > 0 ? mainSize : -mainSize;
    }

    if (GreatNotEqual(std::abs(deltaSum + delta), mainSize)) {
        delta = GreatNotEqual((deltaSum + delta), 0) ? (mainSize - deltaSum) : (-deltaSum - mainSize);
    }
}

void ContainerPickerPattern::UpdateCurrentOffset(float offset)
{
    if (itemPosition_.empty()) {
        PickerMarkDirty();
        return;
    }
    if (!isLoop_ && isDragging_) {
        // handle over scroll
        if (SpringOverScroll(offset)) {
            return;
        }
    }
    mainDeltaSum_ += offset;
    currentDelta_ -= offset;
    PickerMarkDirty();
}

bool ContainerPickerPattern::IsOutOfBoundary(float mainOffset) const
{
    return IsOutOfStart(mainOffset) || IsOutOfEnd(mainOffset);
}

bool ContainerPickerPattern::IsOutOfStart(float mainOffset) const
{
    if (isLoop_ || itemPosition_.empty()) {
        return false;
    }

    auto startPos = itemPosition_.begin()->second.startPos;
    auto middlePos = height_ / HALF;
    return itemPosition_.begin()->first == 0 && GreatNotEqual(startPos + mainOffset, middlePos);
}

bool ContainerPickerPattern::IsOutOfEnd(float mainOffset) const
{
    if (isLoop_ || itemPosition_.empty()) {
        return false;
    }

    auto endPos = itemPosition_.rbegin()->second.endPos;
    auto middlePos = height_ / HALF;
    return itemPosition_.rbegin()->first == totalItemCount_ - 1 && LessNotEqual(endPos + mainOffset, middlePos);
}

bool ContainerPickerPattern::SpringOverScroll(float offset)
{
    bool outOfBounds = IsOutOfBoundary(offset);
    if (!outOfBounds) {
        springOffset_ = 0.0f;
        return false;
    }

    auto visibleSize = pickerHeightBeforeRotate_;
    auto currentRealOffset =
        springOffset_ * ContainerPickerUtils::CalculateFriction(std::abs(springOffset_ / visibleSize));
    auto delta = 0.0f;
    auto middlePos = height_ / HALF;
    if (IsOutOfBoundary()) {
        springOffset_ += offset;
    } else {
        if (offset > 0) {
            springOffset_ = itemPosition_.begin()->second.startPos - middlePos + offset;
        } else {
            springOffset_ = itemPosition_.rbegin()->second.endPos - middlePos + offset;
        }
        delta = offset - springOffset_;
    }
    if (std::abs(springOffset_) > visibleSize) {
        springOffset_ = springOffset_ > 0 ? visibleSize : -visibleSize;
    }
    auto realOffset = springOffset_ * ContainerPickerUtils::CalculateFriction(std::abs(springOffset_ / visibleSize));
    delta += (realOffset - currentRealOffset);
    currentDelta_ -= delta;
    mainDeltaSum_ += delta;
    PickerMarkDirty();
    return true;
}

bool ContainerPickerPattern::CheckDragOutOfBoundary()
{
    if (isLoop_) {
        return false;
    }
    if (IsOutOfBoundary()) {
        isDragging_ = false;
        PlaySpringAnimation();
        return true;
    }

    return false;
}

void ContainerPickerPattern::CreateSpringProperty()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->CreateAnimatablePropertyFloat(
        SPRING_PROPERTY_NAME, 0,
        [weak = AceType::WeakClaim(this)](float position) {
            auto picker = weak.Upgrade();
            CHECK_NULL_VOID(picker);
            auto positionDelta = static_cast<float>(position) - picker->mainDeltaSum_;
            picker->UpdateCurrentOffset(positionDelta);
        },
        PropertyUnit::PIXEL_POSITION);
}

void ContainerPickerPattern::PlaySpringAnimation()
{
    if (RunningTranslateAnimation()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mainSize = std::min(pickerDefaultHeight_, height_);
    if (LessOrEqual(mainSize, 0) || itemPosition_.empty()) {
        return;
    }

    auto middlePos = height_ / HALF;
    auto halfOfItemHeight = pickerItemHeight_ / HALF;
    auto leading = mainDeltaSum_ + middlePos - itemPosition_.rbegin()->second.endPos + halfOfItemHeight;
    auto trailing = mainDeltaSum_ + middlePos - itemPosition_.begin()->second.startPos - halfOfItemHeight;
    CreateSpringProperty();
    host->UpdateAnimatablePropertyFloat(SPRING_PROPERTY_NAME, mainDeltaSum_);
    auto delta = Negative(mainDeltaSum_) ? leading : trailing;

    CreateSpringAnimation(delta);
}

void ContainerPickerPattern::PlayTargetAnimation()
{
    float targetPos = ShortestDistanceBetweenCurrentAndTarget(targetIndex_.value_or(0));
    isTargetAnimationRunning_ = true;
    auto context = GetContext();
    if (context) {
        context->AddAfterLayoutTask([weak = WeakClaim(this), targetPos]() {
            auto picker = weak.Upgrade();
            CHECK_NULL_VOID(picker);
            picker->CreateTargetAnimation(targetPos);
        });
    }
    targetIndex_.reset();
}

inline bool ContainerPickerPattern::RunningTranslateAnimation() const
{
    // TODO 添加其他动画类型
    return isSpringAnimationRunning_;
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
    float currentOffsetFromMiddle = CalculateMiddleLineOffset();
    float totalOffset = endOffset + currentOffsetFromMiddle;
    float resetOffset = CalculateResetOffset(totalOffset);
    endOffset -= resetOffset;

    // handle over scroll
    if (!isLoop_) {
        auto maxOverScrollOffset = maxOverscrollOffset_;
        auto middlePos = height_ / HALF;
        auto currentMiddleItem =
            ContainerPickerUtils::CalcCurrentMiddleItem(itemPosition_, height_, totalItemCount_, isLoop_);
        if (GreatNotEqual(endOffset, 0.0f)) {
            auto distanceToTop =
                pickerItemHeight_ * currentMiddleItem.first + middlePos - currentMiddleItem.second.startPos;
            if (GreatNotEqual(endOffset, distanceToTop + maxOverScrollOffset)) {
                endOffset = distanceToTop + maxOverScrollOffset;
            }
            if (GreatNotEqual(endOffset, distanceToTop)) {
                mainDeltaSum_ = endOffset - distanceToTop;
            } else {
                mainDeltaSum_ = 0.0f;
            }
        }
        if (LessNotEqual(endOffset, 0.0f)) {
            auto distanceToBottom = pickerItemHeight_ * (totalItemCount_ - currentMiddleItem.first - 1) +
                                    currentMiddleItem.second.endPos - middlePos;
            if (GreatNotEqual(std::abs(endOffset), distanceToBottom + maxOverScrollOffset)) {
                endOffset = -distanceToBottom - maxOverScrollOffset;
            }
            if (GreatNotEqual(std::abs(endOffset), distanceToBottom)) {
                mainDeltaSum_ = endOffset + distanceToBottom;
            } else {
                mainDeltaSum_ = 0.0f;
            }
        }
    } else {
        mainDeltaSum_ = 0.0f;
    }
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

    isNeedPlayInertialAnimation_ = true;
    dragVelocity_ = dragVelocity;
    PickerMarkDirty();
    return true;
}

void ContainerPickerPattern::PlayInertialAnimation()
{
    AnimationOption option;
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);
    if (!snapOffsetProperty_) {
        CreateSnapProperty();
    }

    float endOffset = 0.0f;
    CalcEndOffset(endOffset, dragVelocity_);
    snapOffsetProperty_->Set(0.0f);
    snapOffsetProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    auto finishCallback = [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->animationBreak_) {
            pattern->lastAnimationScroll_ = 0.0f;
        }
        pattern->isInertialRollingAnimationRunning_ = false;
        if (!NearZero(pattern->mainDeltaSum_)) {
            pattern->PlaySpringAnimation();
        } else {
            pattern->FireScrollStopEvent();
        }
    };
    snapOffsetProperty_->AnimateWithVelocity(option, -endOffset, dragVelocity_, finishCallback);
    isNeedPlayInertialAnimation_ = false;
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
    auto shiftDistance = (dir == ContainerPickerDirection::UP) ? -pickerItemHeight_ : pickerItemHeight_;
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
        pattern->PickerMarkDirty();
    };
    scrollProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    renderContext->AttachNodeAnimatableProperty(scrollProperty_);
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
        pattern->isInertialRollingAnimationRunning_ = true;
        pattern->PickerMarkDirty();
    };
    snapOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    AttachNodeAnimatableProperty(snapOffsetProperty_);
}

void ContainerPickerPattern::CreateAnimation(double from, double to)
{
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
            pattern->lastAnimationScroll_ = 0.0f;
            pattern->FireScrollStopEvent();
        },
        nullptr, context);
}

void ContainerPickerPattern::CreateTargetAnimation(float delta)
{
    lastAnimationScroll_ = 0.0f;
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(CLICK_ANIMATION_DURATION);
    scrollProperty_->Set(0.0f);
    auto host = GetHost();
    auto context = host ? host->GetContextRefPtr() : nullptr;
    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(this), delta]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->scrollProperty_->Set(delta);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->isTargetAnimationRunning_ = false;
            pattern->FireScrollStopEvent();
        },
        nullptr, context);
}

void ContainerPickerPattern::CreateSpringAnimation(float delta)
{
    auto host = GetHost();
    auto context = host ? host->GetContextRefPtr() : nullptr;
    // spring curve: (velocity: 0.0, mass: 1.0, stiffness: 20.0, damping: 10.0)
    auto springCurve = MakeRefPtr<SpringCurve>(0.0f, 1.0f, 20.0f, 10.0f);
    AnimationOption option;
    option.SetCurve(springCurve);
    option.SetDuration(SPRING_DURATION);
    isSpringAnimationRunning_ = true;
    springAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), delta]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            host->UpdateAnimatablePropertyFloat(SPRING_PROPERTY_NAME, delta);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->isSpringAnimationRunning_ = false;
            pattern->FireScrollStopEvent();
        },
        nullptr, context);
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
    CHECK_NULL_VOID(snapOffsetProperty_);
    CHECK_NULL_VOID(isInertialRollingAnimationRunning_);

    isInertialRollingAnimationRunning_ = false;
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
    float currentOffsetFromMiddle = CalculateMiddleLineOffset();
    float resetOffset = CalculateResetOffset(currentOffsetFromMiddle);
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
    ContainerPickerDirection dir =
        LessOrEqual(totalOffset, 0.0f) ? ContainerPickerDirection::UP : ContainerPickerDirection::DOWN;
    int32_t n = std::trunc(totalOffset) / pickerItemHeight_;
    float distance = std::abs(totalOffset - pickerItemHeight_ * n);
    float resetOffset = 0.0f;
    if (GreatNotEqual(distance, pickerItemHeight_ * 0.5f)) {
        resetOffset = (pickerItemHeight_ - distance) * (dir == ContainerPickerDirection::UP ? 1 : -1);
    } else if (LessNotEqual(distance, pickerItemHeight_ * 0.5f)) {
        resetOffset = distance * (dir == ContainerPickerDirection::UP ? -1 : 1);
    }
    return resetOffset;
}

float ContainerPickerPattern::CalculateMiddleLineOffset()
{
    auto currentMiddleItem =
        ContainerPickerUtils::CalcCurrentMiddleItem(itemPosition_, height_, totalItemCount_, isLoop_);
    return (currentMiddleItem.second.startPos + currentMiddleItem.second.endPos) / HALF - height_ / HALF;
}

} // namespace OHOS::Ace::NG
