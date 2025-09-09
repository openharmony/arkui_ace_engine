/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_REFRESH_PATTERN_H

#include <string>

#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/geometry/ng/offset_t.h"
#include "frameworks/base/memory/referenced.h"
#include "frameworks/base/utils/noncopyable.h"
#include "frameworks/core/components_ng/base/frame_scene_status.h"
#include "frameworks/core/components_ng/pattern/list/list_layout_property.h"
#include "frameworks/core/components_ng/pattern/pattern.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_accessibility_property.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_animation_state.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_event_hub.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_layout_algorithm.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_layout_property.h"
#include "frameworks/core/components_ng/pattern/refresh/refresh_theme_ng.h"
#include "frameworks/core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "frameworks/core/components_ng/pattern/scrollable/scrollable_coordination_event.h"
#include "frameworks/core/components_ng/pattern/text/text_layout_property.h"
#include "frameworks/core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class RefreshPattern : public NestableScrollContainer {
    DECLARE_ACE_TYPE(RefreshPattern, NestableScrollContainer);

public:
    RefreshPattern() = default;
    ~RefreshPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<RefreshLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<RefreshEventHub>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<RefreshAccessibilityProperty>();
    }

    bool IsRefreshing() const
    {
        return isRefreshing_;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    float GetScrollOffsetValue() const
    {
        return scrollOffset_;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    void OnModifyDone() override;
    void InitCoordinationEvent(RefPtr<ScrollableCoordinationEvent>& coordinationEvent);
    void AddCustomBuilderNode(const RefPtr<NG::UINode>& builder);
    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    void OnColorModeChange(uint32_t colorMode) override;

    Axis GetAxis() const override
    {
        return Axis::VERTICAL;
    }

    bool ChildPreMeasureHelperEnabled() override
    {
        return true;
    }

    bool PostponedTaskForIgnoreEnabled() override
    {
        return true;
    }

    ScrollResult HandleScroll(
        float offset, int32_t source, NestedState state = NestedState::GESTURE, float velocity = 0.f) override;

    bool HandleScrollVelocity(float velocity, const RefPtr<NestableScrollContainer>& child = nullptr) override;

    void OnScrollEndRecursive(const std::optional<float>& velocity) override;

    void OnScrollStartRecursive(WeakPtr<NestableScrollContainer> child, float position, float velocity = 0.f) override;
    void OnColorConfigurationUpdate() override;

    bool NestedScrollOutOfBoundary() override
    {
        return !NearZero(scrollOffset_);
    }

    bool IsEnableMatchParent() override
    {
        return true;
    }

    bool IsEnableFix() override
    {
        return true;
    }

    bool IsEnableChildrenMatchParent() override
    {
        return true;
    }

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void InitPanEvent(const RefPtr<FrameNode>& host);
    void HandleDragStart(bool isDrag = true, float mainSpeed = 0.0f);
    ScrollResult HandleDragUpdate(float delta, float mainSpeed = 0.0f);
    void HandleDragEnd(float speed);
    void HandleDragCancel();
    float CalculatePullDownRatio();
    float GetMaxPullDownDistance();
    void TriggerStatusChange(RefreshStatus newStatus);
    void OnAttachToFrameNode() override;
    void OnAttachToFrameNodeMultiThread();
    void OnAttachToMainTree() override;
    void OnAttachToMainTreeMultiThread();
    float GetFollowRatio();
    void HandleCustomBuilderDragUpdateStage();
    void SetAccessibilityAction(const RefPtr<FrameNode>& host);
    void InitOnKeyEvent(const RefPtr<FrameNode>& host);
    bool OnKeyEvent(const KeyEvent& event);
    void QuickEndFresh();
    void QuickStartFresh();
    void UpdateRefreshStatus(RefreshStatus newStatus);
    void UpdateFirstChildPlacement();
    void UpdateLoadingProgressTranslate(float loadingOffset);
    void UpdateLoadingProgressStatus(RefreshAnimationState state, float followToRecycleRatio = 0.0f);
    void UpdateBuilderHeight(float builderHeight);
    void InitOffsetProperty();
    void SpeedTriggerAnimation(float speed);
    void SpeedAnimationFinish();
    void SwitchToFinish();
    void InitChildNode(const RefPtr<FrameNode>& host);
    void InitProgressNode(const RefPtr<FrameNode>& host);
    void QuickFirstChildAppear();
    void QuickFirstChildDisappear();
    float GetLoadingVisibleHeight();
    void UpdateScrollTransition(const RefPtr<FrameNode>& host, float scrollOffset);
    RefreshAnimationState GetLoadingProgressStatus();
    void RefreshStatusChangeEffect(bool refreshingProp);
    float GetTargetOffset();
    void ResetAnimation();
    void FireOnOffsetChange(float value);
    void FireOnStepOffsetChange(float value);
    void UpdateDragFRCSceneInfo(const std::string& scene, float speed, SceneStatus sceneStatus);
    void InitProgressColumn();
    void UpdateLoadingTextOpacity(float opacity);
    void BeginTrailingTrace();
    void EndTrailingTrace();
    float GetLoadingProgressOpacity();
    float GetLoadingTextOpacity();
    Color GetLoadingProgressColor();
    void DumpInfo() override;
    void DumpSimplifyInfo(std::shared_ptr<JsonValue>& json) override {}
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    RefreshStatus refreshStatus_ = RefreshStatus::INACTIVE;
    RefPtr<PanEvent> panEvent_;
    float scrollOffset_ = 0.0f;
    float lastScrollOffset_ = 0.0f;
    bool isSourceFromAnimation_ = false;
    bool isRefreshing_ = false;
    bool isKeyEventRegisted_ = false;
    bool hasLoadingText_ = false;
    bool isRemoveCustomBuilder_ = false;
    bool isTextNodeChanged_ = false;
    RefPtr<FrameNode> progressChild_;
    RefPtr<FrameNode> loadingTextNode_;
    RefPtr<FrameNode> columnNode_;
    RefPtr<FrameNode> customBuilder_;
    bool isCustomBuilderExist_ = false;
    float builderMeasureBaseHeight_ = 0.0f;
    Dimension refreshOffset_ = 64.0_vp;
    bool pullToRefresh_ = true;
    RefPtr<NodeAnimatablePropertyFloat> offsetProperty_;
    std::shared_ptr<AnimationUtils::Animation> animation_;
    std::optional<float> ratio_;
    bool hasBeginTrailingTrace_ = false;
    // API version 10
    void InitLowVersionOffset();
    void UpdateChild();
    void HandleDragStartLowVersion();
    void HandleDragUpdateLowVersion(float delta);
    void HandleDragEndLowVersion();
    void LoadingProgressRefreshingAnimation(bool isDrag);
    void LoadingProgressExit();
    void UpdateLoadingProgress();
    void CustomBuilderRefreshingAnimation(bool isDrag);
    void CustomBuilderExit();
    void UpdateCustomBuilderProperty();
    void HandleCustomBuilderDragEndStage();
    void UpdateLoadingMarginTop(float top);
    float GetScrollOffset(float delta);
    Dimension GetTriggerRefreshDisTance();

    float triggerLoadingDistance_ = 0.0f;
    float customBuilderOffset_ = 0.0f;
    RefPtr<NodeAnimatablePropertyFloat> lowVersionOffset_;
    ACE_DISALLOW_COPY_AND_MOVE(RefreshPattern);
    Dimension loadingProgressSizeTheme_ = 32.0_vp;
    Dimension triggerLoadingDistanceTheme_ = 16.0_vp;
    bool isHigherVersion_ = true;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_PATTERN_H
