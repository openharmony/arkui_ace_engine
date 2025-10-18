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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_PATTERN_H

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/pan_event.h"
#include "core/components_ng/pattern/container_picker/container_picker_event_hub.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_algorithm.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_utils.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "core/gestures/gesture_event.h"

namespace OHOS::Ace::NG {
class ContainerPickerEventParam : public virtual AceType {
    DECLARE_ACE_TYPE(ContainerPickerEventParam, AceType);

public:
    int32_t itemIndex = 0;
    int32_t itemNodeId = 0;
};

enum class ContainerPickerDirection {
    UP = 0,
    DOWN,
};

class ACE_EXPORT ContainerPickerPattern : public NestableScrollContainer {
    DECLARE_ACE_TYPE(ContainerPickerPattern, NestableScrollContainer);

public:
    ContainerPickerPattern() {};
    ~ContainerPickerPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ContainerPickerLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    void SetContentMainSize(float contentMainSize)
    {
        contentMainSize_ = contentMainSize;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<ContainerPickerEventHub>();
    }

    void SetSelectedIndex(int32_t index)
    {
        if (index < 0 || index >= totalItemCount_) {
            index = 0;
        }
        if (index != selectedIndex_) {
            targetIndex_ = index;
        }
    }

    const std::vector<int32_t>& GetOffScreenItems() const
    {
        return offScreenItemsIndex_;
    }

    void SetOffScreenItems(const std::vector<int32_t>& offScreenItemsIndex)
    {
        offScreenItemsIndex_ = offScreenItemsIndex;
    }

    LayoutConstraintF GetLayoutConstraint() const
    {
        return layoutConstraint_;
    }

    bool GetRequestLongPredict() const
    {
        return requestLongPredict_;
    }

    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void FireChangeEvent();
    void FireScrollStopEvent();
    bool SpringOverScroll(float offset);
    void UpdateCurrentOffset(float offset);

protected:
    bool ChildPreMeasureHelperEnabled() override
    {
        return true;
    }

    bool PostponedTaskForIgnoreEnabled() override
    {
        return true;
    }

    bool NeedCustomizeSafeAreaPadding() override
    {
        return true;
    }

    PaddingPropertyF CustomizeSafeAreaPadding(PaddingPropertyF safeAreaPadding, bool needRotate) override;

    bool ChildTentativelyLayouted() override
    {
        return true;
    }

    bool AccumulatingTerminateHelper(RectF& adjustingRect, ExpandEdges& totalExpand, bool fromSelf = false,
        LayoutSafeAreaType ignoreType = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM) override;

private:
    inline bool RunningTranslateAnimation() const;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    // NestableScrollContainer implementations
    Axis GetAxis() const override
    {
        return Axis::VERTICAL;
    }

    ScrollResult HandleScroll(
        float offset, int32_t source, NestedState state = NestedState::GESTURE, float velocity = 0.f) override;
    bool HandleScrollVelocity(float velocity, const RefPtr<NestableScrollContainer>& child = nullptr) override;
    void OnScrollStartRecursive(WeakPtr<NestableScrollContainer> child, float position, float velocity) override;
    void OnScrollEndRecursive(const std::optional<float>& velocity) override;

    ACE_DISALLOW_COPY_AND_MOVE(ContainerPickerPattern);

    void GetLayoutProperties(const RefPtr<ContainerPickerLayoutAlgorithm>& pickerAlgorithm);
    void OnAroundButtonClick(RefPtr<ContainerPickerEventParam> param);
    RefPtr<ClickEvent> CreateItemClickEventListener(RefPtr<ContainerPickerEventParam> param);
    void InitMouseAndPressEvent();
    void UpdatePanEvent();
    void AddPanEvent(const RefPtr<GestureEventHub>& gestureHub, GestureEventFunc&& actionStart,
        GestureEventFunc&& actionUpdate, GestureEventFunc&& actionEnd, GestureEventNoParameter&& actionCancel);
    GestureEventFunc ActionStartTask();
    GestureEventFunc ActionUpdateTask();
    GestureEventFunc ActionEndTask();
    GestureEventNoParameter ActionCancelTask();
    void HandleDragStart(const GestureEvent& info);
    void ProcessDelta(float& delta, float mainSize, float deltaSum);
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd(double dragVelocity, float mainDelta = 0.0f);
    void HandleTargetIndex();
    void CalcEndOffset(float& endOffset, double velocity);
    bool Play(double dragVelocity);
    void UpdateDragFRCSceneInfo(float speed, SceneStatus sceneStatus);
    bool IsOutOfBoundary(float mainOffset = 0.0f) const;
    bool IsOutOfStart(float mainOffset = 0.0f) const;
    bool IsOutOfEnd(float mainOffset = 0.0f) const;
    bool CheckDragOutOfBoundary();
    bool SpringCurveTailMoveProcess(bool useRebound, double& dragDelta);
    void SpringCurveTailEndProcess(bool useRebound, bool stopMove);
    double GetDragDeltaLessThanJumpInterval(
        double offsetY, float originalDragDelta, bool useRebound, float shiftDistance);
    void UpdateColumnChildPosition(double offsetY);
    bool IsLoop() const;
    void SetDefaultTextStyle() const;
    void SetDefaultTextStyle(RefPtr<FrameNode> node) const;
    void CreateAnimation();
    void AttachNodeAnimatableProperty(const RefPtr<NodeAnimatablePropertyFloat>& property);
    void CreateSnapProperty();
    void CreateSpringProperty();
    void CreateAnimation(double from, double to);
    void CreateTargetAnimation(int32_t targetIndex);
    void CreateSpringtAnimation(float delta);
    void PickerMarkDirty();
    void PostIdleTask(const RefPtr<FrameNode>& frameNode);
    void SwipeTo(int32_t index);
    void UpdateClipEdge();
    float ShortestDistanceBetweenCurrentAndTarget(int32_t targetIndex);
    std::pair<int32_t, PickerItemInfo> CalcCurrentMiddleItem() const;
    void CreateChildrenClickEvent(RefPtr<UINode>& host);
    RefPtr<TouchEventImpl> CreateItemTouchEventListener();
    void PlayInertialAnimation();
    void PlaySpringAnimation();
    void PlayTargetAnimation();
    void PlayResetAnimation();
    void StopInertialRollingAnimation();
    void StopSpringAnimation();
    void StopTargetAnimation();
    double GetCurrentTime() const;
    float CalculateResetOffset(float totalOffset);
    float CalculateMiddleLineOffset();
    void InitDefaultParams()
    {
        pickerItemHeight_ = static_cast<float>(PICKER_ITEM_HEIGHT.ConvertToPx());
        pickerDefaultHeight_ = static_cast<float>(PICKER_DEFAULT_HEIGHT.ConvertToPx());
        pickerHeightBeforeRotate_ = static_cast<float>(PICKER_HEIGHT_BEFORE_ROTATE.ConvertToPx());
        maxOverscrollOffset_ = static_cast<float>(MAX_OVERSCROLL_OFFSET.ConvertToPx());
    }

    RefPtr<PanEvent> panEvent_;
    PanDirection panDirection_;
    LayoutConstraintF layoutConstraint_;
    std::vector<RefPtr<ScrollingListener>> scrollingListener_;
    std::vector<int32_t> offScreenItemsIndex_;
    std::optional<int32_t> targetIndex_ = 0;

    ContainerPickerUtils::PositionMap itemPosition_;

    RefPtr<NodeAnimatablePropertyFloat> scrollProperty_;
    RefPtr<NodeAnimatablePropertyFloat> snapOffsetProperty_;

    std::shared_ptr<AnimationUtils::Animation> springAnimation_;
    std::shared_ptr<AnimationUtils::Animation> targetAnimation_;

    bool isFirstAxisAction_ = true;
    bool isDragging_ = false;
    bool isItemClickEventCreated_ = false;
    bool crossMatchChild_ = false;
    bool animationCreated_ = false;
    bool isTargetAnimationRunning_ = false;
    bool isSpringAnimationRunning_ = false;
    bool isInertialRollingAnimationRunning_ = false;
    bool requestLongPredict_ = true;
    bool isLoop_ = true;
    bool isNeedPlayInertialAnimation_ = false;
    bool clickBreak_ = false;
    bool touchBreak_ = false;
    bool animationBreak_ = false;

    int32_t containerPickerId_ = -1;
    int32_t displayCount_ = 7;
    int32_t totalItemCount_ = 0;
    int32_t selectedIndex_ = 0;

    double yLast_ = 0.0;
    double yOffset_ = 0.0;
    double dragStartTime_ = 0.0;
    double dragEndTime_ = 0.0;
    double dragVelocity_ = 0.0f;

    float lastAnimationScroll_ = 0.0f;
    float currentDelta_ = 0.0f;
    float currentOffset_ = 0.0f;
    float height_ = 0.0f;
    float contentMainSize_ = 0.0f;
    float mainDeltaSum_ = 0.0f;
    float springOffset_ = 0.0f;

    float pickerItemHeight_ = 0.0f;
    float pickerDefaultHeight_ = 0.0f;
    float pickerHeightBeforeRotate_ = 0.0f;
    float maxOverscrollOffset_ = 0.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_PATTERN_H
