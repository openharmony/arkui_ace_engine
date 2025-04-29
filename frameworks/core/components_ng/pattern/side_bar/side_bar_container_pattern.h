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
#include "core/components_ng/pattern/side_bar/side_bar_theme.h"

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
        layoutAlgorithm->SetPreSideBarWidth(preSidebarWidth_);
        layoutAlgorithm->SetRealSideBarHeight(realSideBarHeight_);
        layoutAlgorithm->SetRealDividerWidth(realDividerWidth_);
        layoutAlgorithm->SetControlButtonClick(isControlButtonClick_);
        auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
        if (layoutProperty) {
            layoutAlgorithm->SetSideBarContainerType(type_);
        }
        layoutAlgorithm->SetMinSideBarWidth(minSideBarWidth_);
        layoutAlgorithm->SetMaxSideBarWidth(maxSideBarWidth_);
        layoutAlgorithm->SetMinContentWidth(minContentWidth_);
        layoutAlgorithm->SetTypeUpdateWidth(typeUpdateWidth_);
        layoutAlgorithm->SetControlImageWidth(controlImageWidth_);
        layoutAlgorithm->SetControlImageHeight(controlImageHeight_);
        auto host = GetHost();
        auto sideBarContainerPattern = host->GetPattern<SideBarContainerPattern>();
        layoutAlgorithm->SetPattern(AceType::WeakClaim(AceType::RawPtr(sideBarContainerPattern)));
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
        SetAccessibilityEvent();
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

    void SetControlButtonClick(bool value)
    {
        isControlButtonClick_ = value;
    }

    void SetRightToLeftMode(bool value)
    {
        isRightToLeft_ = value;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        return { false, true, ScopeType::OTHERS };
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;
    void InitControlButtonTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitDividerMouseEvent(const RefPtr<InputEventHub>& inputHub);
    void UpdateSideBarPosition(float value);
    void SetMinSideBarWidth(float minSideBarWidth)
    {
        minSideBarWidth_ = minSideBarWidth;
    }
    void SetMaxSideBarWidth(float maxSideBarWidth)
    {
        maxSideBarWidth_ = maxSideBarWidth;
    }
    void SetMinContentWidth(float minContentWidth)
    {
        minContentWidth_ = minContentWidth;
    }
    void SetTypeUpdateWidth(float typeUpdateWidth)
    {
        typeUpdateWidth_ = typeUpdateWidth;
    }
    void GetControlImageSize(Dimension& width, Dimension& height);

    bool GetShowSideBar() const
    {
        return showSideBar_;
    }

    void SetImageInfo(ImageSourceInfo imageInfo)
    {
        imageInfo_ = imageInfo;
    }

    bool GetIsInDividerDrag() const
    {
        return isInDividerDrag_;
    }

    bool OnThemeScopeUpdate(int32_t themeScopeId) override;

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnModifyDone() override;
    void UpdateAnimDir();
    void DoAnimation();
    void CreateAnimation();
    void FireChangeEvent(bool isShow);
    void UpdateControlButtonIcon();
    void CreateAndMountNodes();
    void CreateAndMountDivider(const RefPtr<NG::FrameNode>& parentNode);
    void CreateAndMountControlButton(const RefPtr<NG::FrameNode>& parentNode);
    RefPtr<FrameNode> CreateControlButton(const RefPtr<SideBarTheme>& sideBarTheme);
    RefPtr<FrameNode> CreateControlImage(const RefPtr<SideBarTheme>& sideBarTheme,
        const RefPtr<FrameNode>& parentNode);
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragStart();
    void HandleDragUpdate(float xOffset);
    void HandleDragEnd();
    void FireSideBarWidthChangeEvent();
    void HandlePanEventEnd();
    void OnUpdateShowSideBar(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty);
    void OnUpdateShowControlButton(
        const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, const RefPtr<FrameNode>& host);
    void OnUpdateShowDivider(
        const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, const RefPtr<FrameNode>& host);
    void OnUpdateSideBarAndContent(const RefPtr<FrameNode>& host);
    void OnDividerMouseEvent(MouseInfo& info);
    void OnHover(bool isHover);
    void AddDividerHotZoneRect(const RefPtr<SideBarContainerLayoutAlgorithm>& layoutAlgorithm);
    SideBarPosition GetSideBarPositionWithRtl(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty);
    RefPtr<FrameNode> GetSideBarNode(const RefPtr<FrameNode>& host) const;
    RefPtr<FrameNode> GetFirstFrameNode(const RefPtr<UINode>& host) const;
    RefPtr<FrameNode> GetSideBarNodeOrFirstChild() const;
    RefPtr<FrameNode> GetControlButtonNode() const;
    RefPtr<FrameNode> GetContentNode(const RefPtr<FrameNode>& host) const;
    RefPtr<FrameNode> GetControlImageNode() const;
    RefPtr<FrameNode> GetDividerNode() const;
    std::optional<float> DimensionConvertToPx(const Dimension& value) const;
    Dimension ConvertPxToPercent(float value) const;
    void UpdateDividerShadow() const;
    void SetSideBarActive(bool isActive, bool onlyJsActive) const;
    void OnLanguageConfigurationUpdate() override;
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    void RegisterElementInfoCallBack(const RefPtr<FrameNode>& buttonNode);
    void SetAccessibilityEvent();
    void InitImageErrorCallback(const RefPtr<SideBarTheme>& sideBarTheme, const RefPtr<FrameNode>& imgNode);
    void SetMouseStyle(MouseFormat format);
    void UpdateSideBarToolBarManager(bool isShowDivider, float width);
    void UpdateSideBarColorToolBarManager(const Color& backgroudColor);
    void UpdateSideBarDividerToolBarManager(float dividerWidth);
    void UpdateSideBarStatus();

    void InitToolBarManager()
    {
        if (!toolbarManager_) {
            auto pipeline = GetHost()->GetContext();
            CHECK_NULL_VOID(pipeline);
            toolbarManager_ = pipeline->GetToolbarManager();
        }
    }

    RefPtr<InputEvent> hoverEvent_;
    RefPtr<InputEvent> dividerMouseEvent_;
    RefPtr<ClickEvent> controlButtonClickEvent_;
    RefPtr<InputEvent> controlButtonHoverEvent_;
    RefPtr<PanEvent> panEvent_;
    RefPtr<Animator> controller_;
    RefPtr<CurveAnimation<float>> rightToLeftAnimation_;
    RefPtr<CurveAnimation<float>> leftToRightAnimation_;
    RefPtr<PanEvent> dragEvent_;
    RefPtr<ToolbarManager> toolbarManager_;

    float currentOffset_ = 0.0f;
    float realDividerWidth_ = 0.0f;
    SideBarStatus sideBarStatus_ = SideBarStatus::SHOW;
    bool showSideBar_ = true;
    bool needInitRealSideBarWidth_ = true;
    RectF dragRect_;
    bool hasControlButton_ = false;
    SideBarAnimationDirection animDir_ = SideBarAnimationDirection::LTR;
    bool isControlButtonClick_ = false;
    bool hasInit_ = false;
    bool autoHide_ = false;
    bool inAnimation_ = false;
    bool isRightToLeft_ = false;
    bool isInDividerDrag_ = false;
    bool isDividerDraggable_ = true;
    bool userSetShowSideBar_ = true;

    Dimension realSideBarWidth_ = -1.0_vp;
    Dimension preSidebarWidth_;
    Dimension userSetSidebarWidth_;
    Dimension adjustMaxSideBarWidth_;
    Dimension adjustMinSideBarWidth_;
    SideBarContainerType type_ = SideBarContainerType::EMBED;
    float minContentWidth_ = -1.0f;
    float minSideBarWidth_ = -1.0f;
    float maxSideBarWidth_ = -1.0f;
    float typeUpdateWidth_ = 0.0f;
    float realSideBarHeight_ = 0.0f;
    Dimension controlImageWidth_;
    Dimension controlImageHeight_;

    ACE_DISALLOW_COPY_AND_MOVE(SideBarContainerPattern);

    RefPtr<LongPressEvent> longPressEvent_;
    GestureEventFunc longPressActionEnd_;
    RefPtr<FrameNode> dialogNode_;
    ImageSourceInfo imageInfo_;
    void InitLongPressEvent(const RefPtr<FrameNode>& buttonNode);
    void HandleLongPressEvent();
    void HandleLongPressActionEnd();
    void ShowDialogWithNode();
    bool isDialogShow_ = false;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_SIDE_BAR_CONTAINER_PATTERN_H
