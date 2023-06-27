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

#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"

#include "base/mousestyle/mouse_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_theme.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t DEFAULT_MIN_CHILDREN_SIZE = 3;
constexpr int32_t SLIDE_TRANSLATE_DURATION = 400;
constexpr int32_t DIVIDER_HOT_ZONE_HORIZONTAL_PADDING_NUM = 2;
constexpr float RATIO_NEGATIVE = -1.0f;
constexpr float RATIO_ZERO = 0.0f;
constexpr float DEFAULT_HALF = 2.0f;
constexpr Dimension DEFAULT_DRAG_REGION = 20.0_vp;
constexpr Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;
constexpr int32_t SIDEBAR_DURATION = 500;
const RefPtr<CubicCurve> SIDEBAR_CURVE = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.2f, 0.1f, 1.0f);
constexpr Dimension DEFAULT_DIVIDER_STROKE_WIDTH = 1.0_vp;
constexpr Dimension DEFAULT_DIVIDER_START_MARGIN = 0.0_vp;
constexpr Dimension DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING = 2.0_vp;
constexpr Color DEFAULT_DIVIDER_COLOR = Color(0x08000000);
constexpr float HOVER_OPACITY = 0.05f;
constexpr float PRESS_OPACITY = 0.1f;
} // namespace

void SideBarContainerPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void SideBarContainerPattern::OnUpdateShowSideBar(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty)
{
    CHECK_NULL_VOID(layoutProperty);

    auto newShowSideBar = layoutProperty->GetShowSideBar().value_or(true);
    if (newShowSideBar != showSideBar_) {
        SetSideBarStatus(newShowSideBar ? SideBarStatus::SHOW : SideBarStatus::HIDDEN);
        FireChangeEvent(newShowSideBar);
    }
}

void SideBarContainerPattern::OnUpdateShowControlButton(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(host);

    auto showControlButton = layoutProperty->GetShowControlButton().value_or(true);

    auto children = host->GetChildren();
    if (children.empty()) {
        LOGE("OnUpdateShowControlButton: children is empty.");
        return;
    }

    auto controlButtonNode = children.back();
    if (controlButtonNode->GetTag() != V2::IMAGE_ETS_TAG || !AceType::InstanceOf<FrameNode>(controlButtonNode)) {
        LOGE("OnUpdateShowControlButton: Get control button failed.");
        return;
    }

    auto imgFrameNode = AceType::DynamicCast<FrameNode>(controlButtonNode);
    auto imageLayoutProperty = imgFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);

    imageLayoutProperty->UpdateVisibility(showControlButton ? VisibleType::VISIBLE : VisibleType::GONE);
    imgFrameNode->MarkModifyDone();
}

void SideBarContainerPattern::OnUpdateShowDivider(
    const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(host);

    auto dividerColor = layoutProperty->GetDividerColor().value_or(DEFAULT_DIVIDER_COLOR);
    auto dividerStrokeWidth = layoutProperty->GetDividerStrokeWidth().value_or(DEFAULT_DIVIDER_STROKE_WIDTH);

    auto children = host->GetChildren();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE) {
        LOGE("OnUpdateShowDivider: children's size is less than 3.");
        return;
    }

    auto begin = children.rbegin();
    auto dividerNode = *(++begin);
    CHECK_NULL_VOID(dividerNode);
    if (dividerNode->GetTag() != V2::DIVIDER_ETS_TAG || !AceType::InstanceOf<FrameNode>(dividerNode)) {
        LOGE("OnUpdateShowDivider: Get divider failed.");
        return;
    }

    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(dividerNode);
    CHECK_NULL_VOID(dividerFrameNode);
    auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(dividerColor);

    auto dividerLayoutProperty = dividerFrameNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateStrokeWidth(dividerStrokeWidth);
    dividerFrameNode->MarkModifyDone();
}

void SideBarContainerPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    InitSideBar();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    InitPanEvent(gestureHub);

    auto layoutProperty = host->GetLayoutProperty<SideBarContainerLayoutProperty>();
    OnUpdateShowSideBar(layoutProperty);
    OnUpdateShowControlButton(layoutProperty, host);
    OnUpdateShowDivider(layoutProperty, host);
}

void SideBarContainerPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID_NOLOG(!dragEvent_);

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleDragStart();
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleDragUpdate(static_cast<float>(info.GetOffsetX()));
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleDragEnd();
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleDragEnd();
    };

    if (dragEvent_) {
        gestureHub->RemovePanEvent(dragEvent_);
    }

    dragEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::HORIZONTAL };
    gestureHub->AddPanEvent(dragEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void SideBarContainerPattern::InitSideBar()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto layoutProperty = host->GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto showSideBar = layoutProperty->GetShowSideBar().value_or(true);
    sideBarStatus_ = showSideBar ? SideBarStatus::SHOW : SideBarStatus::HIDDEN;
}

void SideBarContainerPattern::CreateAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (!controller_) {
        controller_ = CREATE_ANIMATOR(host->GetContext());
    }

    auto weak = AceType::WeakClaim(this);
    if (!rightToLeftAnimation_) {
        rightToLeftAnimation_ =
            AceType::MakeRefPtr<CurveAnimation<float>>(RATIO_ZERO, RATIO_NEGATIVE, Curves::FRICTION);
        rightToLeftAnimation_->AddListener(Animation<float>::ValueCallback([weak](float value) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->UpdateSideBarPosition(value);
            }
        }));
    }

    if (!leftToRightAnimation_) {
        leftToRightAnimation_ =
            AceType::MakeRefPtr<CurveAnimation<float>>(RATIO_NEGATIVE, RATIO_ZERO, Curves::FRICTION);
        leftToRightAnimation_->AddListener(Animation<float>::ValueCallback([weak](float value) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->UpdateSideBarPosition(value);
            }
        }));
    }
}

void SideBarContainerPattern::InitControlButtonTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID_NOLOG(!controlButtonClickEvent_);

    auto clickTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->DoAnimation();
    };
    controlButtonClickEvent_ = MakeRefPtr<ClickEvent>(std::move(clickTask));
    gestureHub->AddClickEvent(controlButtonClickEvent_);
}

void SideBarContainerPattern::InitControlButtonMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    CHECK_NULL_VOID_NOLOG(!controlButtonHoverEvent_);

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnControlButtonHover(isHover);
        }
    };
    controlButtonHoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(controlButtonHoverEvent_);
    inputHub->SetMouseEvent([weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    });
}

void SideBarContainerPattern::UpdateAnimDir()
{
    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sideBarPosition = layoutProperty->GetSideBarPosition().value_or(SideBarPosition::START);

    switch (sideBarStatus_) {
        case SideBarStatus::HIDDEN:
            if (sideBarPosition == SideBarPosition::START) {
                animDir_ = SideBarAnimationDirection::LTR;
            } else {
                animDir_ = SideBarAnimationDirection::RTL;
            }
            break;
        case SideBarStatus::SHOW:
            if (sideBarPosition == SideBarPosition::START) {
                animDir_ = SideBarAnimationDirection::RTL;
            } else {
                animDir_ = SideBarAnimationDirection::LTR;
            }
            break;
        default:
            break;
    }
}

void SideBarContainerPattern::DoAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    UpdateAnimDir();

    AnimationOption option = AnimationOption();
    option.SetDuration(SIDEBAR_DURATION);
    option.SetCurve(SIDEBAR_CURVE);
    option.SetFillMode(FillMode::FORWARDS);

    auto sideBarStatus = sideBarStatus_;
    sideBarStatus_ = SideBarStatus::CHANGING;
    UpdateControlButtonIcon();

    // fire before animation to include user changes in onChange event
    FireChangeEvent(sideBarStatus == SideBarStatus::HIDDEN);

    auto weak = AceType::WeakClaim(this);
    auto context = PipelineContext::GetCurrentContext();
    context->OpenImplicitAnimation(option, option.GetCurve(), [weak, sideBarStatus]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (sideBarStatus == SideBarStatus::HIDDEN) {
                pattern->SetSideBarStatus(SideBarStatus::SHOW);
                pattern->UpdateControlButtonIcon();
            } else {
                pattern->SetSideBarStatus(SideBarStatus::HIDDEN);
                pattern->UpdateControlButtonIcon();
            }
        }
    });
    if (animDir_ == SideBarAnimationDirection::LTR) {
        currentOffset_ = 0.0f + realDividerWidth_;
    } else {
        currentOffset_ = -realSideBarWidth_ - realDividerWidth_;
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();
    context->CloseImplicitAnimation();
}

void SideBarContainerPattern::HandlePanEventEnd()
{
    if (sideBarStatus_ == SideBarStatus::HIDDEN) {
        DoAnimation();
    }
}

void SideBarContainerPattern::DoSideBarAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    CHECK_NULL_VOID(controller_);
    CHECK_NULL_VOID(leftToRightAnimation_);
    CHECK_NULL_VOID(rightToLeftAnimation_);

    if (!controller_->IsStopped()) {
        controller_->Stop();
    }

    auto weak = AceType::WeakClaim(this);
    controller_->ClearStopListeners();
    controller_->ClearInterpolators();
    controller_->SetDuration(SLIDE_TRANSLATE_DURATION);

    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sideBarPosition = layoutProperty->GetSideBarPosition().value_or(SideBarPosition::START);
    bool isSideBarStart = sideBarPosition == SideBarPosition::START;

    FireChangeEvent(sideBarStatus_ == SideBarStatus::HIDDEN);
    if (sideBarStatus_ == SideBarStatus::HIDDEN) {
        controller_->AddInterpolator(isSideBarStart ? leftToRightAnimation_ : rightToLeftAnimation_);
        controller_->AddStopListener([weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(pattern);
            pattern->SetSideBarStatus(SideBarStatus::SHOW);
            pattern->UpdateControlButtonIcon();
        });
    } else {
        controller_->AddInterpolator(isSideBarStart ? rightToLeftAnimation_ : leftToRightAnimation_);
        controller_->AddStopListener([weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(pattern);
            pattern->SetSideBarStatus(SideBarStatus::HIDDEN);
            pattern->UpdateControlButtonIcon();
        });
    }
    controller_->Play();
    UpdateControlButtonIcon();
}

void SideBarContainerPattern::UpdateSideBarPosition(float value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (sideBarStatus_ != SideBarStatus::CHANGING) {
        sideBarStatus_ = SideBarStatus::CHANGING;
        UpdateControlButtonIcon();
    }

    currentOffset_ = value * (realSideBarWidth_ + realDividerWidth_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SideBarContainerPattern::FireChangeEvent(bool isShow)
{
    auto sideBarContainerEventHub = GetEventHub<SideBarContainerEventHub>();
    CHECK_NULL_VOID(sideBarContainerEventHub);

    sideBarContainerEventHub->FireChangeEvent(isShow);
}

void SideBarContainerPattern::UpdateControlButtonIcon()
{
    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto children = host->GetChildren();
    if (children.empty()) {
        LOGE("UpdateControlButtonIcon: children is empty.");
        return;
    }

    auto controlButtonNode = children.back();
    if (controlButtonNode->GetTag() != V2::IMAGE_ETS_TAG || !AceType::InstanceOf<FrameNode>(controlButtonNode)) {
        LOGE("UpdateControlButtonIcon: Get control button failed.");
        return;
    }

    auto imgFrameNode = AceType::DynamicCast<FrameNode>(controlButtonNode);
    auto imgRenderContext = imgFrameNode->GetRenderContext();
    auto imageLayoutProperty = imgFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imgSourceInfo = imageLayoutProperty->GetImageSourceInfoValue();

    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto sideBarTheme = context->GetTheme<SideBarTheme>();
    CHECK_NULL_VOID(sideBarTheme);
    Color controlButtonColor = sideBarTheme->GetControlImageColor();

    switch (sideBarStatus_) {
        case SideBarStatus::SHOW:
            if (layoutProperty->GetControlButtonShowIconStr().has_value()) {
                imgSourceInfo.SetSrc(layoutProperty->GetControlButtonShowIconStr().value());
            } else {
                imgSourceInfo.SetResourceId(InternalResource::ResourceId::SIDE_BAR);
                imgSourceInfo.SetFillColor(controlButtonColor);
            }
            break;
        case SideBarStatus::HIDDEN:
            if (layoutProperty->GetControlButtonHiddenIconStr().has_value()) {
                imgSourceInfo.SetSrc(layoutProperty->GetControlButtonHiddenIconStr().value());
            } else {
                imgSourceInfo.SetResourceId(InternalResource::ResourceId::SIDE_BAR);
                imgSourceInfo.SetFillColor(controlButtonColor);
            }
            break;
        case SideBarStatus::CHANGING:
            if (layoutProperty->GetControlButtonSwitchingIconStr().has_value()) {
                imgSourceInfo.SetSrc(layoutProperty->GetControlButtonSwitchingIconStr().value());
            } else {
                imgSourceInfo.SetResourceId(InternalResource::ResourceId::SIDE_BAR);
                imgSourceInfo.SetFillColor(controlButtonColor);
            }
            break;
        default:
            break;
    }

    imageLayoutProperty->UpdateImageSourceInfo(imgSourceInfo);
    imgFrameNode->MarkModifyDone();
}

bool SideBarContainerPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<SideBarContainerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);

    UpdateResponseRegion(layoutAlgorithm);
    AddDividerHotZoneRect(layoutAlgorithm);

    if (needInitRealSideBarWidth_) {
        needInitRealSideBarWidth_ = false;
    }

    return false;
}

void SideBarContainerPattern::UpdateResponseRegion(const RefPtr<SideBarContainerLayoutAlgorithm>& layoutAlgorithm)
{
    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto scaleProperty = constraint->scaleProperty;
    auto halfDragRegionWidth = ConvertToPx(DEFAULT_DRAG_REGION, scaleProperty).value_or(0);
    auto dragRegionWidth = halfDragRegionWidth * 2;

    CHECK_NULL_VOID(layoutAlgorithm);
    realDividerWidth_ = layoutAlgorithm->GetRealDividerWidth();
    auto halfRealDividerWidth = 0.0f;
    if (realDividerWidth_ > 0.0f) {
        halfRealDividerWidth = realDividerWidth_ / DEFAULT_HALF;
    }
    halfDragRegionWidth += halfRealDividerWidth;
    dragRegionWidth += realDividerWidth_;
    realSideBarWidth_ = layoutAlgorithm->GetRealSideBarWidth();
    auto dragRegionHeight = layoutAlgorithm->GetRealSideBarHeight();
    auto dragRectOffset = layoutAlgorithm->GetSideBarOffset();

    auto sideBarPosition = layoutProperty->GetSideBarPosition().value_or(SideBarPosition::START);
    if (sideBarPosition == SideBarPosition::START) {
        dragRectOffset.SetX(dragRectOffset.GetX() + halfRealDividerWidth + realSideBarWidth_ - halfDragRegionWidth);
    } else {
        dragRectOffset.SetX(dragRectOffset.GetX() - halfDragRegionWidth);
    }

    dragRect_.SetOffset(dragRectOffset);
    dragRect_.SetSize(SizeF(dragRegionWidth, dragRegionHeight));

    auto eventHub = GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);

    gestureEventHub->MarkResponseRegion(true);
    std::vector<DimensionRect> responseRegion;
    DimensionOffset responseOffset(dragRectOffset);
    DimensionRect responseRect(Dimension(dragRect_.Width(), DimensionUnit::PX),
        Dimension(dragRect_.Height(), DimensionUnit::PX), responseOffset);
    responseRegion.emplace_back(responseRect);
    gestureEventHub->SetResponseRegion(responseRegion);
}

void SideBarContainerPattern::AddDividerHotZoneRect(const RefPtr<SideBarContainerLayoutAlgorithm>& layoutAlgorithm)
{
    CHECK_NULL_VOID(layoutAlgorithm);
    if (realDividerWidth_ <= 0.0f) {
        return;
    }

    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto dividerStartMagin = layoutProperty->GetDividerStartMargin().value_or(DEFAULT_DIVIDER_START_MARGIN);

    OffsetF hotZoneOffset;
    hotZoneOffset.SetX(-DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING.ConvertToPx());
    hotZoneOffset.SetY(-dividerStartMagin.ConvertToPx());
    SizeF hotZoneSize;
    hotZoneSize.SetWidth(realDividerWidth_ +
        DIVIDER_HOT_ZONE_HORIZONTAL_PADDING_NUM * DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING.ConvertToPx());
    hotZoneSize.SetHeight(layoutAlgorithm->GetRealSideBarHeight());

    DimensionRect hotZoneRegion;
    hotZoneRegion.SetSize(DimensionSize(Dimension(hotZoneSize.Width()), Dimension(hotZoneSize.Height())));
    hotZoneRegion.SetOffset(DimensionOffset(Dimension(hotZoneOffset.GetX()), Dimension(hotZoneOffset.GetY())));

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    if (children.size() < DEFAULT_MIN_CHILDREN_SIZE) {
        LOGE("AddDividerHotZoneRect: children's size is less than 3.");
        return;
    }

    auto begin = children.rbegin();
    auto dividerNode = *(++begin);
    CHECK_NULL_VOID(dividerNode);
    if (dividerNode->GetTag() != V2::DIVIDER_ETS_TAG || !AceType::InstanceOf<FrameNode>(dividerNode)) {
        LOGE("AddDividerHotZoneRect: Get divider failed.");
        return;
    }

    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(dividerNode);
    CHECK_NULL_VOID(dividerFrameNode);
    dividerFrameNode->AddHotZoneRect(hotZoneRegion);
}

void SideBarContainerPattern::HandleDragStart()
{
    if (sideBarStatus_ != SideBarStatus::SHOW) {
        return;
    }

    preSidebarWidth_ = realSideBarWidth_;
}

void SideBarContainerPattern::HandleDragUpdate(float xOffset)
{
    if (sideBarStatus_ != SideBarStatus::SHOW) {
        return;
    }

    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto minSideBarWidth = layoutProperty->GetMinSideBarWidth().value_or(DEFAULT_MIN_SIDE_BAR_WIDTH);
    auto maxSideBarWidth = layoutProperty->GetMaxSideBarWidth().value_or(DEFAULT_MAX_SIDE_BAR_WIDTH);
    if (minSideBarWidth > maxSideBarWidth) {
        minSideBarWidth = DEFAULT_MIN_SIDE_BAR_WIDTH;
        maxSideBarWidth = DEFAULT_MAX_SIDE_BAR_WIDTH;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto frameSize = geometryNode->GetFrameSize();
    auto parentWidth = frameSize.Width();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto scaleProperty = constraint->scaleProperty;
    auto minSideBarWidthPx = ConvertToPx(minSideBarWidth, scaleProperty, parentWidth).value_or(0);
    auto maxSideBarWidthPx = ConvertToPx(maxSideBarWidth, scaleProperty, parentWidth).value_or(0);

    auto sideBarPosition = layoutProperty->GetSideBarPosition().value_or(SideBarPosition::START);
    bool isSideBarStart = sideBarPosition == SideBarPosition::START;

    auto sideBarLine = preSidebarWidth_ + (isSideBarStart ? xOffset : -xOffset);

    if (sideBarLine > minSideBarWidthPx && sideBarLine < maxSideBarWidthPx) {
        realSideBarWidth_ = sideBarLine;
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    if (sideBarLine >= maxSideBarWidthPx) {
        realSideBarWidth_ = maxSideBarWidthPx;
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }

    auto halfDragRegionWidth = dragRect_.Width() / 2;
    if (sideBarLine > minSideBarWidthPx - halfDragRegionWidth) {
        realSideBarWidth_ = minSideBarWidthPx;
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }
    realSideBarWidth_ = minSideBarWidthPx;

    auto autoHide_ = layoutProperty->GetAutoHide().value_or(true);
    if (autoHide_) {
        DoAnimation();
    }
}

void SideBarContainerPattern::HandleDragEnd()
{
    if (sideBarStatus_ != SideBarStatus::SHOW) {
        return;
    }

    preSidebarWidth_ = realSideBarWidth_;
}

void SideBarContainerPattern::InitDividerMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    CHECK_NULL_VOID(inputHub);
    CHECK_NULL_VOID_NOLOG(!hoverEvent_);

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnHover(isHover);
        }
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void SideBarContainerPattern::OnHover(bool isHover)
{
    auto layoutProperty = GetLayoutProperty<SideBarContainerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto dividerStrokeWidth = layoutProperty->GetDividerStrokeWidth().value_or(DEFAULT_DIVIDER_STROKE_WIDTH);
    if (dividerStrokeWidth.Value() <= 0.0f) {
        return;
    }

    MouseFormat format = isHover ? MouseFormat::RESIZE_LEFT_RIGHT : MouseFormat::DEFAULT;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowId = pipeline->GetWindowId();
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    int32_t currentPointerStyle = 0;
    mouseStyle->GetPointerStyle(windowId, currentPointerStyle);
    if (currentPointerStyle != static_cast<int32_t>(format)) {
        mouseStyle->SetPointerStyle(windowId, format);
    }
}

void SideBarContainerPattern::OnControlButtonHover(bool isHover)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto children = host->GetChildren();
    if (children.empty()) {
        LOGE("UpdateControlButtonIcon: children is empty.");
        return;
    }

    auto controlButtonNode = children.back();
    if (controlButtonNode->GetTag() != V2::IMAGE_ETS_TAG || !AceType::InstanceOf<FrameNode>(controlButtonNode)) {
        LOGE("UpdateControlButtonIcon: Get control button failed.");
        return;
    }

    isControlButtonHover_ = isHover;
    auto imgFrameNode = AceType::DynamicCast<FrameNode>(controlButtonNode);
    CHECK_NULL_VOID(imgFrameNode);
    auto imgRenderContext = imgFrameNode->GetRenderContext();
    CHECK_NULL_VOID(imgRenderContext);
    if (isHover) {
        DoControlButtonHoverAnimation(imgRenderContext, 0.0f, HOVER_OPACITY, HOVER_DURATION, Curves::FRICTION);
    } else {
        DoControlButtonHoverAnimation(imgRenderContext, HOVER_OPACITY, 0.0f, HOVER_DURATION, Curves::FRICTION);
    }
}

void SideBarContainerPattern::DoControlButtonHoverAnimation(RefPtr<RenderContext>& renderContext, float startOpacity,
    float endOpacity, int32_t duration, const RefPtr<Curve>& curve)
{
    Color colorFrom = Color::FromRGBO(0, 0, 0, startOpacity);
    Color colorTo = Color::FromRGBO(0, 0, 0, endOpacity);
    Color highlightStart = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(colorFrom);
    Color highlightEnd = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(colorTo);
    renderContext->OnBackgroundColorUpdate(highlightStart);
    AnimationOption option = AnimationOption();
    option.SetDuration(duration);
    option.SetCurve(curve);
    AnimationUtils::Animate(
        option, [renderContext, highlightEnd]() { renderContext->OnBackgroundColorUpdate(highlightEnd); });
}

void SideBarContainerPattern::HandleMouseEvent(const MouseInfo& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto children = host->GetChildren();
    if (children.empty()) {
        LOGE("UpdateControlButtonIcon: children is empty.");
        return;
    }

    auto controlButtonNode = children.back();
    if (controlButtonNode->GetTag() != V2::IMAGE_ETS_TAG || !AceType::InstanceOf<FrameNode>(controlButtonNode)) {
        LOGE("UpdateControlButtonIcon: Get control button failed.");
        return;
    }

    auto imgFrameNode = AceType::DynamicCast<FrameNode>(controlButtonNode);
    CHECK_NULL_VOID(imgFrameNode);
    auto imgRenderContext = imgFrameNode->GetRenderContext();
    CHECK_NULL_VOID(imgRenderContext);
    if ((info.GetButton() != MouseButton::LEFT_BUTTON) || (!isControlButtonHover_)) {
        return;
    }
    if (info.GetAction() == MouseAction::PRESS) {
        DoControlButtonHoverAnimation(imgRenderContext, HOVER_OPACITY, PRESS_OPACITY, PRESS_DURATION, Curves::SHARP);
    } else if (info.GetAction() == MouseAction::RELEASE) {
        DoControlButtonHoverAnimation(imgRenderContext, PRESS_OPACITY, HOVER_OPACITY, PRESS_DURATION, Curves::SHARP);
    }
}
} // namespace OHOS::Ace::NG
