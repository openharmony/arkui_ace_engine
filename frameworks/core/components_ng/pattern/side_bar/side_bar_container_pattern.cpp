/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t SLIDE_TRANSLATE_DURATION = 400;
constexpr float RATIO_NEGATIVE = -1.0f;
constexpr float RATIO_ZERO = 0.0f;
constexpr Dimension DEFAULT_DRAG_REGION = 20.0_vp;
constexpr Dimension DEFAULT_MIN_SIDE_BAR_WIDTH = 200.0_vp;
constexpr Dimension DEFAULT_MAX_SIDE_BAR_WIDTH = 280.0_vp;
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

void SideBarContainerPattern::OnModifyDone()
{
    CreateAnimation();
    InitSideBar();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    InitDragEvent(gestureHub);

    auto layoutProperty = host->GetLayoutProperty<SideBarContainerLayoutProperty>();
    OnUpdateShowSideBar(layoutProperty);
    OnUpdateShowControlButton(layoutProperty, host);
}

void SideBarContainerPattern::InitDragEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (dragEvent_) {
        return;
    }

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragStart();
        }
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragUpdate(static_cast<float>(info.GetOffsetX()));
        }
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd();
        }
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd();
        }
    };

    dragEvent_ = MakeRefPtr<DragEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::HORIZONTAL };
    gestureHub->AddDragEvent(dragEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
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
        controller_ = AceType::MakeRefPtr<Animator>(host->GetContext());
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
    if (controlButtonClickEvent_) {
        return;
    }
    auto clickTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->DoSideBarAnimation();
        }
    };
    controlButtonClickEvent_ = MakeRefPtr<ClickEvent>(std::move(clickTask));
    gestureHub->AddClickEvent(controlButtonClickEvent_);
}

void SideBarContainerPattern::DoSideBarAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (!controller_ || !leftToRightAnimation_ || !rightToLeftAnimation_) {
        LOGE("DoSideBarAnimation: Animator or animation is null.");
        return;
    }

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

    if (sideBarStatus_ == SideBarStatus::HIDDEN) {
        controller_->AddInterpolator(isSideBarStart ? leftToRightAnimation_ : rightToLeftAnimation_);
        controller_->AddStopListener([weak]() {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->SetSideBarStatus(SideBarStatus::SHOW);
                pattern->FireChangeEvent(true);
                pattern->UpdateControlButtonIcon();
            }
        });
    } else {
        controller_->AddInterpolator(isSideBarStart ? rightToLeftAnimation_ : leftToRightAnimation_);
        controller_->AddStopListener([weak]() {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->SetSideBarStatus(SideBarStatus::HIDDEN);
                pattern->FireChangeEvent(false);
                pattern->UpdateControlButtonIcon();
            }
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

    currentOffset_ = value * realSideBarWidth_;
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

    switch (sideBarStatus_) {
        case SideBarStatus::SHOW:
            if (layoutProperty->GetControlButtonShowIconStr().has_value()) {
                imgSourceInfo.SetSrc(layoutProperty->GetControlButtonShowIconStr().value());
            } else {
                imgSourceInfo.SetResourceId(InternalResource::ResourceId::SIDE_BAR);
            }
            break;
        case SideBarStatus::HIDDEN:
            if (layoutProperty->GetControlButtonHiddenIconStr().has_value()) {
                imgSourceInfo.SetSrc(layoutProperty->GetControlButtonHiddenIconStr().value());
            } else {
                imgSourceInfo.SetResourceId(InternalResource::ResourceId::SIDE_BAR);
            }
            break;
        case SideBarStatus::CHANGING:
            if (layoutProperty->GetControlButtonSwitchingIconStr().has_value()) {
                imgSourceInfo.SetSrc(layoutProperty->GetControlButtonSwitchingIconStr().value());
            } else {
                imgSourceInfo.SetResourceId(InternalResource::ResourceId::SIDE_BAR);
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

    realSideBarWidth_ = layoutAlgorithm->GetRealSideBarWidth();
    auto dragRegionHeight = layoutAlgorithm->GetRealSideBarHeight();
    auto dragRectOffset = layoutAlgorithm->GetSideBarOffset();

    auto sideBarPosition = layoutProperty->GetSideBarPosition().value_or(SideBarPosition::START);
    if (sideBarPosition == SideBarPosition::START) {
        dragRectOffset.SetX(dragRectOffset.GetX() + realSideBarWidth_ - halfDragRegionWidth);
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

    if (sideBarLine > maxSideBarWidthPx) {
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
        DoSideBarAnimation();
    }
}

void SideBarContainerPattern::HandleDragEnd()
{
    if (sideBarStatus_ != SideBarStatus::SHOW) {
        return;
    }

    preSidebarWidth_ = realSideBarWidth_;
}

} // namespace OHOS::Ace::NG
