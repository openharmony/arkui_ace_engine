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
#include "core/components_ng/pattern/container_picker/container_picker_layout_algorithm.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "core/components_ng/event/pan_event.h"
#include "core/components_ng/event/event_hub.h"
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

    void SetContentMainSize(float contentMainSize)
    {
        contentMainSize_ = contentMainSize;
    }

    void OnAttachToFrameNode() override;
    void OnModifyDone() override;

private:
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
    void CalcEndOffset(float& endOffset, double velocity);
    bool Play(double dragVelocity);
    void UpdateDragFRCSceneInfo(float speed, SceneStatus sceneStatus);
    void UpdateCurrentOffset(float offset);
    bool SpringCurveTailMoveProcess(bool useRebound, double& dragDelta);
    void SpringCurveTailEndProcess(bool useRebound, bool stopMove);
    double GetDragDeltaLessThanJumpInterval(
        double offsetY, float originalDragDelta, bool useRebound, float shiftDistance);
    void UpdateColumnChildPosition(double offsetY);
    bool IsLoop()
    {
        return true;
    }
    void CreateAnimation();
    void AttachNodeAnimatableProperty(const RefPtr<NodeAnimatablePropertyFloat>& property);
    void CreateSnapProperty();
    void CreateAnimation(double from, double to);
    void PickerMarkDirty(PropertyChangeFlag extraFlag);

    int32_t containerPickerId_ = -1;
    bool isDragging_ = false;
    bool isItemClickEventCreated_ = false;
    RefPtr<PanEvent> panEvent_;
    PanDirection panDirection_;
    bool isFirstAxisAction_ = true;
    std::vector<RefPtr<ScrollingListener>> scrollingListener_;
    int32_t currentIndex_ = 0;
    bool crossMatchChild_ = false;
    float currentDelta_ = 0.0f;
    float currentIndexOffset_ = 0.0f;
    float totalOffset_ = 0.0f; // indicates the offset of the actual layout
    float contentMainSize_ = 650.0f;
    float mainDeltaSum_ = 0.0f;

    ContainerPickerLayoutAlgorithm::PositionMap itemPosition_;

    bool animationCreated_ = false;
    double timeStart_ = 0.0;
    double timeEnd = 0.0;
    double scrollDelta_ = 0.0;
    double yLast_ = 0.0;
    double yOffset_ = 0.0;
    float lastAnimationScroll_ = 0.0f;
    int32_t showCount_= 7;

    RefPtr<NodeAnimatablePropertyFloat> scrollProperty_;
    RefPtr<NodeAnimatablePropertyFloat> aroundClickProperty_;
    RefPtr<NodeAnimatablePropertyFloat> snapOffsetProperty_;
    std::shared_ptr<AnimationUtils::Animation> animation_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_PATTERN_H
