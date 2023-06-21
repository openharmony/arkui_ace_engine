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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_SIDE_BAR_CONTAINER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_SIDE_BAR_CONTAINER_PATTERN_H

#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_event_hub.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_algorithm.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"

namespace OHOS::Ace::NG {

enum class SideBarAnimationDirection {
    LTR,
    RTL,
};
class SideBarContainerPattern : public Pattern {
    DECLARE_ACE_TYPE(SideBarContainerPattern, Pattern);

public:
    SideBarContainerPattern() = default;
    ~SideBarContainerPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SideBarContainerLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<SideBarContainerLayoutAlgorithm>();
        layoutAlgorithm->SetCurrentOffset(currentOffset_);
        layoutAlgorithm->SetSideBarStatus(sideBarStatus_);
        layoutAlgorithm->SetNeedInitRealSideBarWidth(needInitRealSideBarWidth_);
        layoutAlgorithm->SetRealSideBarWidth(realSideBarWidth_);
        layoutAlgorithm->SetRealDividerWidth(realDividerWidth_);
        auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
        if (layoutProperty) {
            layoutAlgorithm->SetSideBarContainerType(
                layoutProperty->GetSideBarContainerType().value_or(SideBarContainerType::EMBED));
        }
        return layoutAlgorithm;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SideBarContainerEventHub>();
    }

    void SetSideBarStatus(SideBarStatus sideBarStatus)
    {
        sideBarStatus_ = sideBarStatus;
        showSideBar_ = sideBarStatus_ == SideBarStatus::SHOW;
    }

    void SetHasControlButton(bool hasControlButton)
    {
        hasControlButton_ = hasControlButton;
    }

    bool HasControlButton() const
    {
        return hasControlButton_;
    }

    void MarkNeedInitRealSideBarWidth(bool value)
    {
        needInitRealSideBarWidth_ = value;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        return { false, true, ScopeType::OTHERS };
    }

    void InitControlButtonTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitDividerMouseEvent(const RefPtr<InputEventHub>& inputHub);
    void UpdateSideBarPosition(float value);

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void UpdateAnimDir();
    void DoAnimation();
    void DoSideBarAnimation();
    void CreateAnimation();
    void InitSideBar();
    void FireChangeEvent(bool isShow);
    void UpdateControlButtonIcon();
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragStart();
    void HandleDragUpdate(float xOffset);
    void HandleDragEnd();
    void HandlePanEventEnd();
    void UpdateResponseRegion(const RefPtr<SideBarContainerLayoutAlgorithm>& layoutAlgorithm);
    void OnUpdateShowSideBar(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty);
    void OnUpdateShowControlButton(
        const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, const RefPtr<FrameNode>& host);
    void OnUpdateShowDivider(
        const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, const RefPtr<FrameNode>& host);
    void OnHover(bool isHover);
    void AddDividerHotZoneRect(const RefPtr<SideBarContainerLayoutAlgorithm>& layoutAlgorithm);

    RefPtr<InputEvent> hoverEvent_;
    RefPtr<ClickEvent> controlButtonClickEvent_;
    RefPtr<PanEvent> panEvent_;
    RefPtr<Animator> controller_;
    RefPtr<CurveAnimation<float>> rightToLeftAnimation_;
    RefPtr<CurveAnimation<float>> leftToRightAnimation_;
    RefPtr<PanEvent> dragEvent_;

    float currentOffset_ = 0.0f;
    float realSideBarWidth_ = 0.0f;
    float realDividerWidth_ = 0.0f;
    SideBarStatus sideBarStatus_ = SideBarStatus::SHOW;
    bool showSideBar_ = true;
    bool needInitRealSideBarWidth_ = true;
    RectF dragRect_;
    float preSidebarWidth_ = 0.0f;
    bool hasControlButton_ = false;
    SideBarAnimationDirection animDir_ = SideBarAnimationDirection::LTR;

    ACE_DISALLOW_COPY_AND_MOVE(SideBarContainerPattern);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_SIDE_BAR_CONTAINER_PATTERN_H
