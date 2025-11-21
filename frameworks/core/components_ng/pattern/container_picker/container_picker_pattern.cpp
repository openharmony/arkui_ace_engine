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

#include "adapter/ohos/entrance/picker/picker_haptic_factory.h"
#include "base/log/dump_log.h"
#include "core/animation/spring_curve.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/container_picker/container_picker_paint_method.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const std::string CONTAINER_PICKER_DRAG_SCENE = "container_picker_drag_scene";
constexpr double MOVE_THRESHOLD = 2.0;
constexpr float SPRING_DURATION = 600.0f;
constexpr float SPRING_CURVE_VELOCITY = 0.0f;
constexpr float SPRING_CURVE_MASS = 1.0f;
constexpr float SPRING_CURVE_STIFFNESS = 20.0f;
constexpr float SPRING_CURVE_DAMPING = 10.0f;
constexpr float DEFAULT_SPRING_RESPONSE = 0.416f;
constexpr float DEFAULT_SPRING_DAMP = 0.99f;
constexpr float MIN_TIME = 1.0f;
constexpr float POSITIVE = 1.0f;
constexpr float NEGATIVE = -1.0f;
constexpr float PICKER_SPEED_TH = 0.25f;
constexpr int32_t VELOCITY_TRANS = 1000;
constexpr int32_t DEFAULT_FONT_SIZE = 20;
constexpr int32_t CLICK_ANIMATION_DURATION = 300;
constexpr int32_t DELTA_INDEX_1 = 1;
constexpr int32_t DELTA_INDEX_2 = 2;
constexpr int32_t DELTA_INDEX_3 = 3;
constexpr uint32_t CUSTOM_SPRING_ANIMATION_DURATION = 1000;
} // namespace

RefPtr<LayoutAlgorithm> ContainerPickerPattern::CreateLayoutAlgorithm()
{
    auto layoutAlgorithm = MakeRefPtr<ContainerPickerLayoutAlgorithm>();
    CHECK_NULL_RETURN(layoutAlgorithm, nullptr);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    totalItemCount_ = host->TotalChildCount();
    isLoop_ = IsLoop();

    layoutAlgorithm->SetTotalItemCount(host->TotalChildCount());
    layoutAlgorithm->SetPrevTotalItemCount(prevTotalItemCount_);
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

    currentDelta_ = 0.0f;
    auto layoutAlgorithmWrapper = dirty->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto pickerAlgorithm = DynamicCast<ContainerPickerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(pickerAlgorithm, false);
    GetLayoutProperties(pickerAlgorithm);
    FireChangeEvent();
    PostIdleTask(GetHost());
    SetDefaultTextStyle(false);
    HandleTargetIndex();

    if (isNeedPlayInertialAnimation_) {
        PlayInertialAnimation();
    }

    if (isModified_) {
        isModified_ = false;
        return true;
    } else {
        return false;
    }
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
    return downDelta <= upDelta ? downDelta * pickerItemHeight_ + currentOffsetFromMiddle
                                : upDelta * pickerItemHeight_ * NEGATIVE - currentOffsetFromMiddle;
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
    if (isAnimationRunning_) {
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
    topPadding_ = algo->GetTopPadding();
    crossMatchChild_ = algo->IsCrossMatchChild();
    prevTotalItemCount_ = algo->GetTotalItemCount();
    auto contentCrossSize = algo->GetContentCrossSize();
    if (!NearEqual(contentCrossSize, contentCrossSize_)) {
        contentCrossSize_ = contentCrossSize;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void ContainerPickerPattern::OnAttachToFrameNode()
{
    CreateScrollProperty();
    UpdatePanEvent();
    UpdateClipEdge();
    InitDefaultParams();
    InitAreaChangeEvent();
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
    InitOrRefreshHapticController();
    SetAccessibilityAction();
    InitDisabled();

    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    PickerMarkDirty();
}

void ContainerPickerPattern::InitDisabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (!eventHub->IsEnabled()) {
        renderContext->UpdateOpacity(DISABLE_ALPHA);
    } else {
        renderContext->UpdateOpacity(1.0);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void ContainerPickerPattern::FireChangeEvent()
{
    auto currentMiddleItem =
        ContainerPickerUtils::CalcCurrentMiddleItem(itemPosition_, height_, totalItemCount_, isLoop_);
    auto newSelectedIndex = currentMiddleItem.first;
    if (newSelectedIndex != selectedIndex_) {
        selectedIndex_ = newSelectedIndex;
        auto pickerEventHub = GetEventHub<ContainerPickerEventHub>();
        CHECK_NULL_VOID(pickerEventHub);
        pickerEventHub->FireChangeEvent(selectedIndex_);
    }
}

void ContainerPickerPattern::FireScrollStopEvent()
{
    auto pickerEventHub = GetEventHub<ContainerPickerEventHub>();
    CHECK_NULL_VOID(pickerEventHub);
    if (animationBreak_) {
        return;
    }
    pickerEventHub->FireScrollStopEvent(selectedIndex_);
}

void ContainerPickerPattern::FireAnimationEndEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetUserTextValue(GetTextOfCurrentChild());
    accessibilityProperty->SetAccessibilityText(GetTextOfCurrentChild());
    host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE);
    FireScrollStopEvent();
    ForceResetWithoutAnimation();
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

void ContainerPickerPattern::SetDefaultTextStyle(bool isUpdateTextStyle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<ContainerPickerTheme>();
    CHECK_NULL_VOID(theme);
    Color defaultColor = theme->GetFontColor();
    for (const auto& item : itemPosition_) {
        auto index = ContainerPickerUtils::GetLoopIndex(item.first, totalItemCount_);
        auto child = DynamicCast<FrameNode>(host->GetOrCreateChildByIndex(index));
        if (isUpdateTextStyle) {
            UpdateDefaultTextStyle(child, defaultColor);
        } else {
            SetDefaultTextStyle(child, defaultColor);
        }
    }
}

void ContainerPickerPattern::SetDefaultTextStyle(RefPtr<FrameNode> node, Color defaultColor)
{
    CHECK_NULL_VOID(node);
    if (node->GetTag() == V2::TEXT_ETS_TAG) {
        auto textLayoutProperty = node->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (!textLayoutProperty->GetFontSize().has_value()) {
            textLayoutProperty->UpdateFontSize(Dimension(DEFAULT_FONT_SIZE, DimensionUnit::FP));
            isModified_ = true;
        }
        if (!textLayoutProperty->GetTextColor().has_value()) {
            textLayoutProperty->UpdateTextColor(defaultColor);
            isModified_ = true;
            isUseDefaultFontColor_ = true;
        }

        if (isModified_) {
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
            SetDefaultTextStyle(childNode, defaultColor);
        }
    }
}

void ContainerPickerPattern::UpdateDefaultTextStyle(RefPtr<FrameNode> node, Color defaultColor)
{
    CHECK_NULL_VOID(node);
    if (node->GetTag() == V2::TEXT_ETS_TAG) {
        auto textLayoutProperty = node->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (isUseDefaultFontColor_) {
            textLayoutProperty->UpdateTextColor(defaultColor);
        }
    } else {
        auto& children = node->GetChildren();
        for (const auto& child : children) {
            if (!child) {
                continue;
            }
            auto childNode = DynamicCast<FrameNode>(child);
            UpdateDefaultTextStyle(childNode, defaultColor);
        }
    }
}

void ContainerPickerPattern::SwipeTo(int32_t targetIndex)
{
    // If animation is still running, stop it before play new animation.
    if (selectedIndex_ == targetIndex || isAnimationRunning_) {
        return;
    }

    targetIndex_ = targetIndex;
    PickerMarkDirty();
}

void ContainerPickerPattern::OnAroundButtonClick(float offsetY)
{
    if (clickBreak_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto middlePos = height_ / HALF + topPadding_;
    auto delta = offsetY - middlePos;
    auto halfOfMiddleItem = pickerItemHeight_ / HALF;
    auto direction = Positive(delta) ? POSITIVE : NEGATIVE;
    int32_t deltaIndex = 0;
    if (GreatNotEqual(std::abs(delta), height_ / HALF)) {
        // click out of visiable area
        return;
    } else if (LessOrEqual(std::abs(delta), halfOfMiddleItem)) {
        // click at middle item
        return;
    } else if (LessOrEqual(std::abs(delta), halfOfMiddleItem + firstAdjacentItemHeight_)) {
        deltaIndex = DELTA_INDEX_1 * direction;
    } else if (LessOrEqual(std::abs(delta), halfOfMiddleItem + firstAdjacentItemHeight_ + secondAdjacentItemHeight_)) {
        deltaIndex = DELTA_INDEX_2 * direction;
    } else if (LessOrEqual(std::abs(delta), halfOfMiddleItem + firstAdjacentItemHeight_ + secondAdjacentItemHeight_ +
                                                thirdAdjacentItemHeight_)) {
        deltaIndex = DELTA_INDEX_3 * direction;
    } else {
        // click within visiable area but there is no item
        return;
    }
    auto targetIndex = selectedIndex_ + deltaIndex;
    if (!isLoop_ && (targetIndex < 0 || targetIndex >= totalItemCount_)) {
        return;
    }
    SwipeTo(ContainerPickerUtils::GetLoopIndex(targetIndex, totalItemCount_));
}

RefPtr<ClickEvent> ContainerPickerPattern::CreateItemClickEventListener()
{
    auto clickEventHandler = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnAroundButtonClick(info.GetLocalLocation().GetY());
    };

    auto listener = AceType::MakeRefPtr<NG::ClickEvent>(clickEventHandler);
    return listener;
}

void ContainerPickerPattern::CreateChildrenClickEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    RefPtr<ClickEvent> clickListener = CreateItemClickEventListener();
    CHECK_NULL_VOID(clickListener);
    auto gesture = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    gesture->AddClickEvent(clickListener);
}

RefPtr<TouchEventImpl> ContainerPickerPattern::CreateItemTouchEventListener()
{
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetTouches().empty()) {
            return;
        }

        pattern->isAllowPlayHaptic_ = (info.GetSourceTool() == SourceTool::MOUSE) ? false : true;

        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            if (pattern->isAnimationRunning_) {
                pattern->touchBreak_ = true;
                pattern->clickBreak_ = true;
                pattern->StopAnimation();
            } else {
                pattern->animationBreak_ = false;
                pattern->clickBreak_ = false;
            }
            pattern->mainDeltaSum_ = 0.0f;
            pattern->currentDelta_ = 0.0f;
            pattern->springOffset_ = 0.0f;
            pattern->lastAnimationScroll_ = 0.0f;
        }

        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            pattern->touchBreak_ = false;
            if (pattern->animationBreak_) {
                pattern->PlayResetAnimation();
                pattern->yOffset_ = 0.0;
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

    CreateChildrenClickEvent();
    isItemClickEventCreated_ = true;
}

std::string ContainerPickerPattern::GetTextOfCurrentChild()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto currentChild = host->GetOrCreateChildByIndex(selectedIndex_, false, true);
    CHECK_NULL_RETURN(currentChild, "");
    auto childNode = currentChild->GetHostNode();
    CHECK_NULL_RETURN(childNode, "");
    auto childAccessibilityProperty = childNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(childAccessibilityProperty, "");
    auto childText = childAccessibilityProperty->GetGroupPreferAccessibilityText(true);
    return childText;
}

void ContainerPickerPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityGroup(true);
    accessibilityProperty->SetUserTextValue(GetTextOfCurrentChild());
    accessibilityProperty->SetAccessibilityText(GetTextOfCurrentChild());
    accessibilityProperty->SetAccessibilityCustomRole("TextPicker");
    accessibilityProperty->SetSpecificSupportActionCallback(
        [weakPtr = WeakClaim(this), accessibilityPtr = WeakClaim(RawPtr(accessibilityProperty))]() {
            const auto& pattern = weakPtr.Upgrade();
            CHECK_NULL_VOID(pattern);
            const auto& accessibilityProperty = accessibilityPtr.Upgrade();
            CHECK_NULL_VOID(accessibilityProperty);
            if (pattern->IsLoop()) {
                accessibilityProperty->AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
                accessibilityProperty->AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
            } else {
                if (pattern->GetSelectedIndex() > 0) {
                    accessibilityProperty->AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
                }

                if (pattern->GetSelectedIndex() < pattern->GetTotalCount() - 1) {
                    accessibilityProperty->AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
                }
            }
        });

    accessibilityProperty->SetActionScrollForward(
        [weakPtr = WeakClaim(this), accessibility = WeakClaim(RawPtr(accessibilityProperty))]() {
            const auto& pattern = weakPtr.Upgrade();
            CHECK_NULL_VOID(pattern);
            const auto& accessibilityProperty = accessibility.Upgrade();
            CHECK_NULL_VOID(accessibilityProperty);
            if (!accessibilityProperty->IsScrollable()) {
                return;
            }
            pattern->ShowNext();
        });

    accessibilityProperty->SetActionScrollBackward(
        [weakPtr = WeakClaim(this), accessibility = WeakClaim(RawPtr(accessibilityProperty))]() {
            const auto& pattern = weakPtr.Upgrade();
            CHECK_NULL_VOID(pattern);
            const auto& accessibilityProperty = accessibility.Upgrade();
            CHECK_NULL_VOID(accessibilityProperty);
            if (!accessibilityProperty->IsScrollable()) {
                return;
            }
            pattern->ShowPrevious();
        });
}

void ContainerPickerPattern::ShowNext()
{
    auto targetIndex = selectedIndex_ + 1;
    if (!isLoop_ && (targetIndex < 0 || targetIndex >= totalItemCount_)) {
        return;
    }
    SwipeTo(ContainerPickerUtils::GetLoopIndex(targetIndex, totalItemCount_));
}

void ContainerPickerPattern::ShowPrevious()
{
    auto targetIndex = selectedIndex_ - 1;
    if (!isLoop_ && (targetIndex < 0 || targetIndex >= totalItemCount_)) {
        return;
    }
    SwipeTo(ContainerPickerUtils::GetLoopIndex(targetIndex, totalItemCount_));
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
        pattern->HandleDragUpdate(info);
        pattern->dragVelocity_ = info.GetMainVelocity();
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
            pattern->HandleDragEnd(pattern->dragVelocity_);
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
    StopAnimation();
    if (IsAxisAnimationRunning()) {
        StopAxisAnimation();
    }

    yLast_ = info.GetLocalLocation().GetY();
    dragStartTime_ = GetCurrentTime();
}

void ContainerPickerPattern::HandleDragUpdate(const GestureEvent& info)
{
    isAllowPlayHaptic_ = (info.GetSourceTool() == SourceTool::MOUSE) ? false : true;
    float mainDelta = static_cast<float>(info.GetMainDelta());
    if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
        auto dir = Positive(mainDelta) ? POSITIVE : NEGATIVE;
        mainDelta = GreatNotEqual(std::abs(mainDelta), pickerItemHeight_) ? pickerItemHeight_ * dir : mainDelta;
        if (totalItemCount_ == 0) {
            return;
        }
        if (!axisAnimator_) {
            InitAxisAnimator();
        }
        axisAnimator_->OnAxis(mainDelta, currentPos_);
        return;
    }

    auto velocity = info.GetMainVelocity();
    UpdateDragFRCSceneInfo(velocity, SceneStatus::RUNNING);
    animationBreak_ = false;

    auto offsetY =
        info.GetLocalLocation().GetY() + (info.GetInputEventType() == InputEventType::AXIS ? info.GetOffsetY() : 0.0);
    if (NearEqual(offsetY, yLast_, MOVE_THRESHOLD)) {
        StopHapticController();
        return;
    }

    HandleScroll(mainDelta, SCROLL_FROM_UPDATE, NestedState::GESTURE, velocity);
    UpdateColumnChildPosition(offsetY);
    dragEndTime_ = GetCurrentTime();
}

void ContainerPickerPattern::HandleDragEnd(double dragVelocity, float mainDelta)
{
    StopHapticController();
    UpdateDragFRCSceneInfo(dragVelocity, SceneStatus::END);
    isDragging_ = false;

    if (CheckDragOutOfBoundary()) {
        // spring back
        return;
    }

    if (IsAxisAnimationRunning()) {
        return;
    }

    // Throw and slide
    if (Play(dragVelocity_)) {
        return;
    }

    yOffset_ = 0.0;
    yLast_ = 0.0;

    // Drag and slide
    if (!animationCreated_) {
        PickerMarkDirty();
        return;
    }

    // Adjust the position to ensure it is centered.
    float currentOffsetFromMiddle = CalculateMiddleLineOffset();
    float resetOffset = CalculateResetOffset(currentOffsetFromMiddle);
    CreateTargetAnimation(resetOffset);
}

void ContainerPickerPattern::UpdateCurrentOffset(float offset)
{
    if (itemPosition_.empty()) {
        PickerMarkDirty();
        return;
    }
    if (!isLoop_ && (isDragging_ || IsAxisAnimationRunning())) {
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

void ContainerPickerPattern::PlaySpringAnimation()
{
    if (!scrollProperty_) {
        CreateScrollProperty();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mainSize = std::min(pickerDefaultHeight_, height_);
    if (LessOrEqual(mainSize, 0) || itemPosition_.empty()) {
        return;
    }

    auto currentOffsetFromMiddle = CalculateMiddleLineOffset();
    CreateSpringAnimation(currentOffsetFromMiddle);
}

void ContainerPickerPattern::PlayTargetAnimation()
{
    if (!scrollProperty_) {
        CreateScrollProperty();
    }
    int32_t targetIndex = targetIndex_.value_or(0);
    if (targetIndex < 0 || targetIndex >= totalItemCount_) {
        targetIndex = 0;
    }
    float targetPos = ShortestDistanceBetweenCurrentAndTarget(targetIndex);
    CreateTargetAnimation(targetPos);
    targetIndex_.reset();
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
    PickerMarkDirty();
    return true;
}

void ContainerPickerPattern::PlayInertialAnimation()
{
    if (!scrollProperty_) {
        CreateScrollProperty();
    }
    AnimationOption option;
    option.SetDuration(CUSTOM_SPRING_ANIMATION_DURATION);
    auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(DEFAULT_SPRING_RESPONSE, DEFAULT_SPRING_DAMP, 0.0f);
    option.SetCurve(curve);

    float endOffset = 0.0f;
    CalcEndOffset(endOffset, dragVelocity_);
    scrollProperty_->Set(0.0f);
    scrollProperty_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    isAnimationRunning_ = true;
    animationBreak_ = false;
    auto host = GetHost();
    auto context = host ? host->GetContextRefPtr() : nullptr;
    scrollAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), endOffset]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->scrollProperty_->Set(-endOffset);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (!pattern->animationBreak_) {
                pattern->lastAnimationScroll_ = 0.0f;
            }
            pattern->isAnimationRunning_ = false;
            if (!NearZero(pattern->mainDeltaSum_)) {
                pattern->PlaySpringAnimation();
            } else {
                pattern->FireAnimationEndEvent();
            }
            pattern->StopHapticController();
        },
        nullptr, context);
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
    auto isOverScroll = useRebound && IsOutOfBoundary(offsetY);
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
            InnerHandleScroll(LessNotEqual(dragDelta, 0.0));
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

void ContainerPickerPattern::CreateScrollProperty()
{
    CHECK_NULL_VOID(!animationCreated_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float value) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsAxisAnimationRunning()) {
            return;
        }
        pattern->currentDelta_ = value - pattern->lastAnimationScroll_;
        pattern->lastAnimationScroll_ = value;
        pattern->PickerMarkDirty();
        pattern->UpdateColumnChildPosition(value);
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

void ContainerPickerPattern::CreateTargetAnimation(float delta)
{
    if (IsAxisAnimationRunning()) {
        return;
    }
    animationBreak_ = false;
    lastAnimationScroll_ = 0.0f;
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(CLICK_ANIMATION_DURATION);
    scrollProperty_->Set(0.0f);
    auto host = GetHost();
    auto context = host ? host->GetContextRefPtr() : nullptr;
    isAnimationRunning_ = true;
    scrollAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), delta]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->scrollProperty_->Set(delta);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->isAnimationRunning_ = false;
            pattern->lastAnimationScroll_ = 0.0f;
            pattern->yOffset_ = 0.0;
            pattern->yLast_ = 0.0;
            pattern->FireAnimationEndEvent();
            pattern->StopHapticController();
        },
        nullptr, context);
}

void ContainerPickerPattern::CreateSpringAnimation(float delta)
{
    animationBreak_ = false;
    auto host = GetHost();
    auto context = host ? host->GetContextRefPtr() : nullptr;
    auto springCurve =
        MakeRefPtr<SpringCurve>(SPRING_CURVE_VELOCITY, SPRING_CURVE_MASS, SPRING_CURVE_STIFFNESS, SPRING_CURVE_DAMPING);
    AnimationOption option;
    option.SetCurve(springCurve);
    option.SetDuration(SPRING_DURATION);
    isAnimationRunning_ = true;
    scrollProperty_->Set(0.0f);
    scrollAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), delta]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->scrollProperty_->Set(delta);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->isAnimationRunning_ = false;
            pattern->lastAnimationScroll_ = 0.0f;
            pattern->yOffset_ = 0.0;
            pattern->yLast_ = 0.0;
            pattern->FireAnimationEndEvent();
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

void ContainerPickerPattern::StopAnimation()
{
    CHECK_NULL_VOID(isAnimationRunning_);
    CHECK_NULL_VOID(scrollProperty_);
    CHECK_NULL_VOID(scrollAnimation_);

    animationBreak_ = true;
    AnimationUtils::StopAnimation(scrollAnimation_);
    isAnimationRunning_ = false;
    lastAnimationScroll_ = 0.0f;
    yOffset_ = 0.0;
    yLast_ = 0.0;
}

void ContainerPickerPattern::PlayResetAnimation()
{
    float currentOffsetFromMiddle = CalculateMiddleLineOffset();
    float resetOffset = CalculateResetOffset(currentOffsetFromMiddle);
    if (std::abs(resetOffset) >= (pickerItemHeight_ * 0.5f)) {
        InnerHandleScroll(LessNotEqual(resetOffset, 0.0));
    }
    CreateTargetAnimation(resetOffset);
}

void ContainerPickerPattern::ForceResetWithoutAnimation()
{
    float currentOffsetFromMiddle = CalculateMiddleLineOffset();
    currentDelta_ = CalculateResetOffset(currentOffsetFromMiddle);
    PickerMarkDirty();
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
        resetOffset = (pickerItemHeight_ - distance) * (dir == ContainerPickerDirection::UP ? POSITIVE : NEGATIVE);
    } else if (LessNotEqual(distance, pickerItemHeight_ * 0.5f)) {
        resetOffset = distance * (dir == ContainerPickerDirection::UP ? NEGATIVE : POSITIVE);
    }
    return resetOffset;
}

float ContainerPickerPattern::CalculateMiddleLineOffset()
{
    auto currentMiddleItem =
        ContainerPickerUtils::CalcCurrentMiddleItem(itemPosition_, height_, totalItemCount_, isLoop_);
    return (currentMiddleItem.second.startPos + currentMiddleItem.second.endPos - height_) / HALF;
}

bool ContainerPickerPattern::IsEnableHaptic() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto props = GetLayoutProperty<ContainerPickerLayoutProperty>();
    CHECK_NULL_RETURN(props, true);
    return props->GetEnableHapticFeedbackValue(true);
}

void ContainerPickerPattern::InitOrRefreshHapticController()
{
    if (IsEnableHaptic() && !hapticController_) {
        TAG_LOGI(AceLogTag::ACE_CONTAINER_PICKER, "init haptic controller");
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        context->AddAfterLayoutTask([weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->hapticController_ = PickerAudioHapticFactory::GetInstance();
        });
    } else if (!IsEnableHaptic() && hapticController_) {
        TAG_LOGI(AceLogTag::ACE_CONTAINER_PICKER, "stop haptic controller");
        hapticController_->Stop();
    }
    isEnableHaptic_ = IsEnableHaptic();
}

void ContainerPickerPattern::StopHapticController()
{
    if (hapticController_) {
        hapticController_->Stop();
    }
}

void ContainerPickerPattern::PlayHaptic(float offset)
{
    if (isEnableHaptic_ && hapticController_ && isAllowPlayHaptic_) {
        hapticController_->HandleDelta(offset);
    }
}

bool ContainerPickerPattern::InnerHandleScroll(bool isDown)
{
    if (totalItemCount_ == 0) {
        return false;
    }

    if (isEnableHaptic_ && hapticController_ && isAllowPlayHaptic_) {
        hapticController_->PlayOnce();
    }

    if (!IsLoop() && ((isDown && targetIndex_ == totalItemCount_ - 1) || (!isDown && targetIndex_ == 0))) {
        return false;
    }
    return true;
}

void ContainerPickerPattern::OnColorConfigurationUpdate()
{
    SetDefaultTextStyle(true);

    if (SystemProperties::ConfigChangePerform()) {
        // Proactively trigger PickerIndicatorStyle drawing.
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void ContainerPickerPattern::UpdateDividerWidthWithResObj(const RefPtr<ResourceObject>& resObj)
{
    auto pickerNode = GetHost();
    CHECK_NULL_VOID(pickerNode);
    auto property = pickerNode->GetLayoutPropertyPtr<ContainerPickerLayoutProperty>();
    CHECK_NULL_VOID(property);

    CalcDimension strokeWidth;
    if (resObj && ResourceParseUtils::ParseResDimensionVp(resObj, strokeWidth)) {
        property->UpdateIndicatorDividerWidth(strokeWidth);
    } else {
        auto context = pickerNode->GetContext();
        CHECK_NULL_VOID(context);
        auto theme = context->GetTheme<ContainerPickerTheme>();
        CHECK_NULL_VOID(theme);
        property->UpdateIndicatorDividerWidth(theme->GetStrokeWidth());
    }
}

void ContainerPickerPattern::UpdateDividerColorWithResObj(const RefPtr<ResourceObject>& resObj)
{
    auto pickerNode = GetHost();
    CHECK_NULL_VOID(pickerNode);
    auto property = pickerNode->GetLayoutPropertyPtr<ContainerPickerLayoutProperty>();
    CHECK_NULL_VOID(property);

    Color color;
    if (resObj && ResourceParseUtils::ParseResColor(resObj, color)) {
        property->UpdateIndicatorDividerColor(color);
    } else {
        auto context = pickerNode->GetContext();
        CHECK_NULL_VOID(context);
        auto theme = context->GetTheme<ContainerPickerTheme>();
        CHECK_NULL_VOID(theme);
        property->UpdateIndicatorDividerColor(theme->GetIndicatorDividerColor());
    }
}

void ContainerPickerPattern::UpdateStartMarginWithResObj(const RefPtr<ResourceObject>& resObj)
{
    auto pickerNode = GetHost();
    CHECK_NULL_VOID(pickerNode);
    auto property = pickerNode->GetLayoutPropertyPtr<ContainerPickerLayoutProperty>();
    CHECK_NULL_VOID(property);

    CalcDimension startMargin;
    if (resObj && ResourceParseUtils::ParseResDimensionVp(resObj, startMargin)) {
        property->UpdateIndicatorStartMargin(startMargin);
    } else {
        property->UpdateIndicatorStartMargin(Dimension());
    }
}

void ContainerPickerPattern::UpdateEndMarginWithResObj(const RefPtr<ResourceObject>& resObj)
{
    auto pickerNode = GetHost();
    CHECK_NULL_VOID(pickerNode);
    auto property = pickerNode->GetLayoutPropertyPtr<ContainerPickerLayoutProperty>();
    CHECK_NULL_VOID(property);

    CalcDimension endMargin;
    if (resObj && ResourceParseUtils::ParseResDimensionVp(resObj, endMargin)) {
        property->UpdateIndicatorEndMargin(endMargin);
    } else {
        property->UpdateIndicatorEndMargin(Dimension());
    }
}

void ContainerPickerPattern::UpdateBackgroundColorWithResObj(const RefPtr<ResourceObject>& resObj)
{
    auto pickerNode = GetHost();
    CHECK_NULL_VOID(pickerNode);
    auto property = pickerNode->GetLayoutPropertyPtr<ContainerPickerLayoutProperty>();
    CHECK_NULL_VOID(property);

    Color color;
    if (resObj && ResourceParseUtils::ParseResColor(resObj, color)) {
        property->UpdateIndicatorBackgroundColor(color);
    } else {
        auto context = pickerNode->GetContext();
        CHECK_NULL_VOID(context);
        auto theme = context->GetTheme<ContainerPickerTheme>();
        CHECK_NULL_VOID(theme);
        property->UpdateIndicatorBackgroundColor(theme->GetIndicatorBackgroundColor());
    }
}

void ContainerPickerPattern::UpdateBorderRadiusWithResObj(const RefPtr<ResourceObject>& resObj)
{
    auto pickerNode = GetHost();
    CHECK_NULL_VOID(pickerNode);
    auto property = pickerNode->GetLayoutPropertyPtr<ContainerPickerLayoutProperty>();
    CHECK_NULL_VOID(property);

    PickerIndicatorStyle style = GetIndicatorStyleVal();
    if (style.borderRadius->HasResources()) {
        style.borderRadius->ReloadResources();
        NG::BorderRadiusProperty& borderRadiusValue = style.borderRadius.value();
        property->UpdateIndicatorBorderRadius(borderRadiusValue);
    } else if (style.borderRadiusResObj) {
        CalcDimension calcDimension;
        ResourceParseUtils::ParseResDimensionVpNG(style.borderRadiusResObj, calcDimension);
        if (GreatOrEqual(calcDimension.Value(), 0.0f)) {
            NG::BorderRadiusProperty borderRadiusValue = NG::BorderRadiusProperty(calcDimension);
            property->UpdateIndicatorBorderRadius(borderRadiusValue);
        }
    } else {
        property->UpdateIndicatorBorderRadius(BorderRadiusProperty(DEFAULT_RADIUS));
    }
}

void ContainerPickerPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->SetFocusable(true);
    focusHub->SetFocusStyleType(FocusStyleType::CUSTOM_REGION);

    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);

    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        if (pattern) {
            return pattern->OnKeyEvent(event);
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool ContainerPickerPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }

    if (event.code == KeyCode::KEY_DPAD_UP || event.code == KeyCode::KEY_DPAD_DOWN) {
        return HandleDirectionKey(event.code);
    }
    return false;
}

bool ContainerPickerPattern::HandleDirectionKey(KeyCode code)
{
    bool result = true;
    if (totalItemCount_ == 0) {
        return false;
    }
    switch (code) {
        case KeyCode::KEY_DPAD_UP: {
            int32_t totalCountAndIndex = totalItemCount_ + selectedIndex_ - 1;
            int32_t upIndex = (totalCountAndIndex ? totalCountAndIndex : 0) % totalItemCount_;
            SwipeTo(upIndex);
            selectedIndex_ = upIndex;
            FireScrollStopEvent();
            break;
        }

        case KeyCode::KEY_DPAD_DOWN: {
            int32_t downIndex = (totalItemCount_ + selectedIndex_ + 1) % totalItemCount_;
            SwipeTo(downIndex);
            selectedIndex_ = downIndex;
            FireScrollStopEvent();
            break;
        }

        default:
            result = false;
            break;
    }
    return result;
}

void ContainerPickerPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameRect = geometryNode->GetFrameRect();

    float paintRectWidth = frameRect.Width() - FOCUS_DEFAULT_STROCK_WIDTH.ConvertToPx();
    float paintRectHeight = PICKER_ITEM_HEIGHT.ConvertToPx() - FOCUS_DEFAULT_STROCK_WIDTH.ConvertToPx();
    float offsetX = FOCUS_DEFAULT_STROCK_WIDTH.ConvertToPx() / 2;
    float offsetY = frameRect.Height() / 2 - paintRectHeight / 2;
    paintRect.SetRect(RectF(offsetX, offsetY, paintRectWidth, paintRectHeight));

    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, static_cast<RSScalar>(DEFAULT_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(DEFAULT_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, static_cast<RSScalar>(DEFAULT_RADIUS.ConvertToPx()),
        static_cast<RSScalar>(DEFAULT_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
        static_cast<RSScalar>(DEFAULT_RADIUS.ConvertToPx()), static_cast<RSScalar>(DEFAULT_RADIUS.ConvertToPx()));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
        static_cast<RSScalar>(DEFAULT_RADIUS.ConvertToPx()), static_cast<RSScalar>(DEFAULT_RADIUS.ConvertToPx()));
}

void ContainerPickerPattern::InitAreaChangeEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    OnAreaChangedFunc onAreaChangedFunc = [pickerNodeWk = WeakPtr<FrameNode>(host)](const RectF& /* oldRect */,
                                              const OffsetF& /* oldOrigin */, const RectF& /* rect */,
                                              const OffsetF& /* origin */) {
        auto pickerNode = pickerNodeWk.Upgrade();
        CHECK_NULL_VOID(pickerNode);
        pickerNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        pickerNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    };
    eventHub->AddInnerOnAreaChangedCallback(host->GetId(), std::move(onAreaChangedFunc));
}

void ContainerPickerPattern::InitAxisAnimator()
{
    CHECK_NULL_VOID(!axisAnimator_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    auto axisAnimationCallback = [weak = WeakClaim(this)](float offset) {
        auto scrollable = weak.Upgrade();
        CHECK_NULL_VOID(scrollable);
        scrollable->UpdateDragFRCSceneInfo(0.0f, SceneStatus::RUNNING);
        scrollable->ProcessScrollMotion(offset);
    };
    auto axisAnimationStartCallback = [weak = WeakClaim(this)](float position) {
        auto scrollable = weak.Upgrade();
        CHECK_NULL_VOID(scrollable);
        scrollable->UpdateDragFRCSceneInfo(0.0f, SceneStatus::START);
        scrollable->ProcessScrollMotionStart();
    };
    auto axisAnimationFinishCallback = [weak = WeakClaim(this)]() {
        auto scrollable = weak.Upgrade();
        CHECK_NULL_VOID(scrollable);
        scrollable->UpdateDragFRCSceneInfo(0.0f, SceneStatus::END);
        scrollable->HandleDragEnd(0, 0);
    };
    axisAnimator_ = AceType::MakeRefPtr<AxisAnimator>(std::move(axisAnimationCallback),
        std::move(axisAnimationStartCallback), std::move(axisAnimationFinishCallback));
    axisAnimator_->Initialize(pipeline);
}

void ContainerPickerPattern::StopAxisAnimation()
{
    CHECK_NULL_VOID(axisAnimator_);
    axisAnimator_->StopAxisAnimation();
}

void ContainerPickerPattern::ProcessScrollMotionStart()
{
    mainDeltaSum_ = 0.0f;
    currentDelta_ = 0.0f;
    springOffset_ = 0.0f;
    StopAnimation();
}

void ContainerPickerPattern::ProcessScrollMotion(double position)
{
    dragVelocity_ = 0.0f;
    auto mainDelta = position - currentPos_;
    HandleScroll(mainDelta, SCROLL_FROM_AXIS, NestedState::GESTURE, 0.0f);
    currentPos_ = position;
    PickerMarkDirty();
}

} // namespace OHOS::Ace::NG
