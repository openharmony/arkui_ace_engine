/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/side_bar/render_side_bar_container.h"

#include "core/components/image/image_component.h"
#include "core/components/image/render_image.h"
#include "core/gestures/sequenced_recognizer.h"
#include "core/pipeline/base/position_layout_utils.h"

namespace OHOS::Ace {

namespace {

constexpr int32_t DEFAULT_FINGERS = 1;
constexpr int32_t DEFAULT_DURATION = 50;
constexpr int32_t DEFAULT_DISTANCE = 0;
constexpr int32_t DEFAULT_MIX_CHILDREN_SIZE = 3;
constexpr Dimension DEFAULT_DRAG_REGION = 20.0_vp;

} // namespace

void RenderSideBarContainer::CorrectWidth(const Dimension& width, const Dimension& minWidth, const Dimension& maxWidth)
{
    if (ConvertWidthToVp(minWidth) > ConvertWidthToVp(maxWidth)) {
        LOGE("the minSideBarWidth or maxSideBarWidth is illegal, use default value");
    } else {
        minSidebarWidth_ = minWidth;
        maxSidebarWidth_ = maxWidth;
    }

    if (ConvertWidthToVp(width) < ConvertWidthToVp(minSidebarWidth_)) {
        if (sideBar_->GetSideBarWidth().Unit() == DimensionUnit::PERCENT) {
            sidebarWidth_ = ConvertWidthToPercent(minSidebarWidth_);
            return;
        }

        sidebarWidth_ = minSidebarWidth_;
        return;
    }

    if (ConvertWidthToVp(width) > ConvertWidthToVp(maxSidebarWidth_)) {
        if (sideBar_->GetSideBarWidth().Unit() == DimensionUnit::PERCENT) {
            sidebarWidth_ = ConvertWidthToPercent(maxSidebarWidth_);
            return;
        }

        sidebarWidth_ = maxSidebarWidth_;
        return;
    }

    if (sideBar_->GetSideBarWidth().Unit() == DimensionUnit::PERCENT) {
        sidebarWidth_ = ConvertWidthToPercent(width);
        return;
    }

    sidebarWidth_ = width;
}

void RenderSideBarContainer::Initialize()
{
    customSidebarWidth_ = sideBar_->GetSideBarWidth();
    sidebarWidth_ = sideBar_->GetSideBarWidth();
    if (sideBar_->GetSideBarMinWidth() > sideBar_->GetSideBarMaxWidth()) {
        LOGW("the minSideBarWidth or maxSideBarWidth is illegal, use default value");
    } else {
        minSidebarWidth_ = sideBar_->GetSideBarMinWidth();
        maxSidebarWidth_ = sideBar_->GetSideBarMaxWidth();
    }
    status_ = sideBar_->GetSideBarStatus();
    pendingStatus_ = status_;
    curPosition_ = -sidebarWidth_;
    InitializeDragAndAnimation();
    isInitialized_ = true;
}

void RenderSideBarContainer::Update(const RefPtr<Component>& component)
{
    sideBar_ = AceType::DynamicCast<SideBarContainerComponent>(component);
    if (!sideBar_) {
        return;
    }

    if ((sideBar_->GetIsShow() && status_ != SideStatus::SHOW && showSideBar_ != sideBar_->GetIsShow()) ||
        (!sideBar_->GetIsShow() && status_ == SideStatus::SHOW && showSideBar_ != sideBar_->GetIsShow())) {
        DoSideBarAnimation();
    }
    showSideBar_ = sideBar_->GetIsShow();
    if (sideBar_->GetSideBarContainerType() == SideBarContainerType::EMBED) {
        style_ = "SideBarContainerType.Embed";
    } else {
        style_ = "SideBarContainerType.Overlay";
    }
    buttonLeft_ = sideBar_->GetButtonLeft();
    buttonTop_ = sideBar_->GetButtonTop();
    buttonWidth_ = sideBar_->GetButtonWidth();
    buttonHeight_ = sideBar_->GetButtonHeight();
    iconShow_ = sideBar_->GetShowIcon();
    iconHidden_ = sideBar_->GetHiddenIcon();
    iconSwitch_ = sideBar_->GetSwitchIcon();
    showControlButton_ = sideBar_->GetShowControlButton();
    autoHide_ = sideBar_->GetAutoHide();

    if (isInitialized_ && sideBarPosition_ != sideBar_->GetSideBarPositon()) {
        animationController_->SetSideBarPositon(sideBar_->GetSideBarPositon());
    }

    sideBarPosition_ = sideBar_->GetSideBarPositon();

    exceptRegion_.SetRect(PipelineBase::Vp2PxWithCurrentDensity(sideBar_->GetButtonLeft()),
        PipelineBase::Vp2PxWithCurrentDensity(
            sideBar_->GetButtonTop()), PipelineBase::Vp2PxWithCurrentDensity(sideBar_->GetButtonWidth()),
        PipelineBase::Vp2PxWithCurrentDensity(sideBar_->GetButtonHeight()));

    if (!isInitialized_) {
        Initialize();
    } else {
        auto width = sidebarWidth_;
        auto customSidebarWidthVP = ConvertWidthToVp(customSidebarWidth_);
        auto sidebarWidthVP = ConvertWidthToVp(sideBar_->GetSideBarWidth());
        if (sideBar_->IsSideBarwidthDefined() && customSidebarWidthVP != sidebarWidthVP) {
            customSidebarWidth_ = sideBar_->GetSideBarWidth();
            width = customSidebarWidth_;
        }
        CorrectWidth(width, sideBar_->GetSideBarMinWidth(), sideBar_->GetSideBarMaxWidth());
    }

    auto weak = AceType::WeakClaim(this);
    sideBar_->SetClickedFunction([weak] {
        auto container = weak.Upgrade();
        if (container) {
            container->DoSideBarAnimation();
        }
    });

    RenderStack::Update(component);
}

void RenderSideBarContainer::InitializeDragAndAnimation()
{
    // update drag recognizer.
    auto context = GetContext();
    auto weak = AceType::WeakClaim(this);
    PanDirection panDirection = { .type = PanDirection::HORIZONTAL };
    auto longPressRecognizer =
        AceType::MakeRefPtr<LongPressRecognizer>(context, DEFAULT_DURATION, DEFAULT_FINGERS, false);
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(context, DEFAULT_FINGERS, panDirection, DEFAULT_DISTANCE);
    panRecognizer->SetOnActionStart([weak](const GestureEvent& info) {
        auto container = weak.Upgrade();
        if (container) {
            container->HandleDragStart();
        }
    });
    panRecognizer->SetOnActionUpdate([weak](const GestureEvent& info) {
        auto container = weak.Upgrade();
        if (container) {
            container->HandleDragUpdate(info.GetOffsetX());
        }
    });
    panRecognizer->SetOnActionEnd([weak](const GestureEvent& info) {
        auto container = weak.Upgrade();
        if (container) {
            container->HandleDragEnd();
        }
    });
    panRecognizer->SetOnActionCancel([weak](const GestureEvent& info) {
        auto container = weak.Upgrade();
        if (container) {
            container->HandleDragEnd();
        }
    });
    std::vector<RefPtr<GestureRecognizer>> recognizers { longPressRecognizer, panRecognizer };
    dragRecognizer_ = AceType::MakeRefPtr<OHOS::Ace::SequencedRecognizer>(GetContext(), recognizers);
    dragRecognizer_->SetIsExternalGesture(true);
    animationController_ = AceType::MakeRefPtr<SideBarAnimationController>(GetContext());
    animationController_->SetRenderSideBarContainer(weak);
    animationController_->SetSideBarPositon(sideBarPosition_);
}

void RenderSideBarContainer::OnStatusChanged(RenderStatus renderStatus)
{
    if (renderStatus == RenderStatus::FOCUS) {
        isFocus_ = true;
    } else if (renderStatus == RenderStatus::BLUR) {
        isFocus_ = false;
    }
}

void RenderSideBarContainer::UpdateElementPosition(double offset)
{
    curPosition_ = Dimension(PipelineBase::Px2VpWithCurrentDensity(offset), DimensionUnit::VP);
    SetChildrenStatus();
}

double RenderSideBarContainer::GetSidebarWidth() const
{
    return ConvertWidthToVp(sidebarWidth_).ConvertToPx();
}

double RenderSideBarContainer::GetSlidePosition() const
{
    return curPosition_.ConvertToPx();
}

bool RenderSideBarContainer::TouchTest(const Point& globalPoint, const Point& parentLocalPoint,
    const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (GetDisableTouchEvent() || IsDisabled()) {
        return false;
    }

    if (status_ != SideStatus::SHOW) {
        return RenderNode::TouchTest(globalPoint, parentLocalPoint, touchRestrict, result);
    }

    auto sidebarWidthVp = ConvertWidthToVp(sidebarWidth_);
    auto paintRect = GetPaintRect();
    auto exceptRegion = Rect(paintRect.GetOffset() + exceptRegion_.GetOffset(), exceptRegion_.GetSize());
    auto layoutSize = GetLayoutSize();
    auto layoutSizeWithVP =  Dimension(Dimension(layoutSize.Width()).ConvertToVp(), DimensionUnit::VP);
    bool isSideBarStart = sideBarPosition_ == SideBarPosition::START;
    auto sidbarDrag = (isSideBarStart ? sidebarWidthVp : (layoutSizeWithVP - sidebarWidthVp)) - DEFAULT_DRAG_REGION;
    auto dragRect = Rect(paintRect.GetOffset() + Offset(NormalizeToPx(sidbarDrag), 0),
        Size(2 * DEFAULT_DRAG_REGION.ConvertToPx(), paintRect.Height()));
    auto touchRect = GetTransformRect(dragRect);
    auto point = GetTransformPoint(parentLocalPoint);
    if (touchRect.IsInRegion(point) && !GetTransformRect(exceptRegion).IsInRegion(point)) {
        const auto localPoint = point - GetPaintRect().GetOffset();
        const auto coordinateOffset = globalPoint - localPoint;
        dragRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(dragRecognizer_);
        return true;
    }

    return RenderNode::TouchTest(globalPoint, parentLocalPoint, touchRestrict, result);
}

void RenderSideBarContainer::DoSideBarAnimation()
{
    if (!animationController_) {
        return;
    }

    if (isFocus_) {
        auto context = GetContext().Upgrade();
        if (context) {
            context->CancelFocusAnimation();
        }
    }

    animationController_->SetAnimationStopCallback([weak = AceType::WeakClaim(this)]() {
        auto container = weak.Upgrade();
        if (container) {
            container->isAnimation_ = false;
            container->status_ = container->pendingStatus_;
            if (container->sideBar_->GetOnChange()) {
                (*container->sideBar_->GetOnChange())(container->status_ == SideStatus::SHOW);
            }
            container->UpdateRenderImage();
        }
    });
    if (status_ == SideStatus::SHOW) {
        pendingStatus_ = SideStatus::HIDDEN;
    } else {
        pendingStatus_ = SideStatus::SHOW;
    }

    isAnimation_ = true;
    animationController_->PlaySideBarContainerToAnimation(pendingStatus_);
    status_ = SideStatus::CHANGING;
    UpdateRenderImage();
}

Dimension RenderSideBarContainer::ConvertWidthToVp(const Dimension& width) const
{
    if (width.Unit() == DimensionUnit::PERCENT) {
        auto layoutSize = GetLayoutSize();
        double value = PipelineBase::Px2VpWithCurrentDensity(width.Value() * layoutSize.Width());
        return Dimension(value, DimensionUnit::VP);
    }

    return Dimension(width.ConvertToVp(), DimensionUnit::VP);
}

Dimension RenderSideBarContainer::ConvertWidthToPercent(const Dimension& width) const
{
    if (width.Unit() == DimensionUnit::PERCENT) {
        return width;
    }

    auto percentValue = 0.0;
    if (NearZero(GetLayoutSize().Width())) {
        return Dimension(percentValue, DimensionUnit::PERCENT);
    }

    switch (width.Unit()) {
        case DimensionUnit::VP:
            percentValue = width.ConvertToPx() / GetLayoutSize().Width();
            break;
        case DimensionUnit::PX:
            percentValue = width.Value() / GetLayoutSize().Width();
            break;
        default:
            break;
    }

    return Dimension(percentValue, DimensionUnit::PERCENT);
}

void RenderSideBarContainer::PerformLayout()
{
    Size maxSize = GetLayoutParam().GetMaxSize();
    auto children = GetChildren();
    if (children.empty()) {
        SetLayoutSize(maxSize);
        return;
    }

    if (children.size() < DEFAULT_MIX_CHILDREN_SIZE) {
        return;
    }

    if (sideBar_->GetSideBarWidth().Unit() == DimensionUnit::PERCENT &&
        sidebarWidth_.Unit() != DimensionUnit::PERCENT) {
        CorrectWidth(sideBar_->GetSideBarWidth(), minSidebarWidth_, maxSidebarWidth_);
    }

    auto begin = children.begin();
    RefPtr<RenderNode>& imageBox = *(++(++begin));
    LayoutParam innerLayout;
    innerLayout.SetMaxSize(GetLayoutParam().GetMaxSize());
    imageBox->Layout(innerLayout);
    auto box = imageBox->GetFirstChild();
    renderImage_ = box ? box->GetFirstChild() : nullptr;

    DetermineStackSize(true);

    auto layoutParam = GetLayoutParam();
    layoutParam.SetMaxSize(GetLayoutSize());
    SetLayoutParam(layoutParam);

    for (const auto& item : children) {
        if (item->GetIsPercentSize()) {
            innerLayout.SetMaxSize(GetLayoutSize());
            item->Layout(innerLayout);
        }
    }

    SetChildrenStatus();
    PlaceChildren();
}

void RenderSideBarContainer::PlaceChildren()
{
    for (const auto& item : GetChildren()) {
        auto positionedItem = AceType::DynamicCast<RenderPositioned>(item);
        if (!positionedItem) {
            if (item->GetPositionType() == PositionType::PTABSOLUTE) {
                auto itemOffset = PositionLayoutUtils::GetAbsoluteOffset(Claim(this), item);
                item->SetAbsolutePosition(itemOffset);
                continue;
            }
            item->SetPosition(GetNonPositionedChildOffset(item->GetLayoutSize()));
            continue;
        }
        Offset offset = GetPositionedChildOffset(positionedItem);
        positionedItem->SetPosition(offset);
    }
}

void RenderSideBarContainer::SetChildrenStatus()
{
    auto layoutSize = GetLayoutSize();
    if (!layoutSize.IsValid()) {
        LOGW("SetChildrenStatus: Layout size is invalid.");
        return;
    }

    auto sideBarWidthVP = ConvertWidthToVp(sidebarWidth_);
    bool isSideBarStart = sideBarPosition_ == SideBarPosition::START;

    if (status_ == SideStatus::SHOW) {
        curPosition_ = isSideBarStart ? 0.0_vp : -sideBarWidthVP;

        if (ConvertWidthToVp(sidebarWidth_) < ConvertWidthToVp(minSidebarWidth_) && autoHide_) {
            DoSideBarAnimation();
        }
    }

    static Dimension miniWidthToHide = 520.0_vp;
    auto autoHide = layoutSize.Width() <= miniWidthToHide.ConvertToPx();

    if (status_ == SideStatus::AUTO) {
        if (autoHide) {
            status_ = SideStatus::HIDDEN;
        } else {
            curPosition_ = isSideBarStart ? 0.0_vp : -sideBarWidthVP;
            status_ = SideStatus::SHOW;
        }
    }
    if (status_ == SideStatus::HIDDEN) {
        curPosition_ = isSideBarStart ? -sideBarWidthVP : 0.0_vp;
    }

    LayoutChildren();
}

void RenderSideBarContainer::LayoutChildren()
{
    auto children = GetChildren();
    auto begin = children.begin();
    RefPtr<RenderNode>& content = *begin;
    RefPtr<RenderNode>& sideBar = *(++begin);

    auto sideBarWidthVP = ConvertWidthToVp(sidebarWidth_);
    auto layoutSize = GetLayoutSize();
    auto layoutSizeWithVP =  Dimension(Dimension(layoutSize.Width()).ConvertToVp(), DimensionUnit::VP);
    bool isSideBarStart = sideBarPosition_ == SideBarPosition::START;
    auto curPositionVP = ConvertWidthToVp(curPosition_);

    if (sideBar_->GetSideBarContainerType() == SideBarContainerType::EMBED) {
        if (isSideBarStart) {
            content->SetLeft(sideBarWidthVP + curPositionVP);
            auto fixedSize = layoutSize.MinusWidth((sideBarWidthVP + curPositionVP).ConvertToPx());
            content->Layout(LayoutParam(fixedSize, Size()));
        } else {
            content->SetLeft(Dimension(0));
            auto fixedSize = layoutSize.MinusWidth((-curPositionVP).ConvertToPx());
            content->Layout(LayoutParam(fixedSize, Size()));
        }
    } else {
        content->SetLeft(Dimension(0));
        content->Layout(LayoutParam(layoutSize, Size()));
    }
    if (isSideBarStart) {
        sideBar->SetLeft(curPositionVP);
    } else {
        sideBar->SetLeft(layoutSizeWithVP + curPositionVP);
    }
    auto fixedSize = Size(sideBarWidthVP.ConvertToPx(), layoutSize.Height());
    sideBar->Layout(LayoutParam(fixedSize, fixedSize));
    MarkNeedRender();
}

void RenderSideBarContainer::UpdateRenderImage()
{
    auto renderImage = DynamicCast<RenderImage>(renderImage_.Upgrade());
    if (!renderImage) {
        LOGE("sidebar control button image error");
        return;
    }
    auto imageComponent = AceType::MakeRefPtr<ImageComponent>();
    if (status_ == SideStatus::SHOW) {
        if (sideBar_->GetShowIcon().empty()) {
            imageComponent->SetResourceId(InternalResource::ResourceId::SIDE_BAR);
        } else {
            imageComponent->SetSrc(sideBar_->GetShowIcon());
        }
    }
    if (status_ == SideStatus::HIDDEN) {
        if (sideBar_->GetHiddenIcon().empty()) {
            imageComponent->SetResourceId(InternalResource::ResourceId::SIDE_BAR);
        } else {
            imageComponent->SetSrc(sideBar_->GetHiddenIcon());
        }
    }
    if (status_ == SideStatus::CHANGING) {
        if (sideBar_->GetSwitchIcon().empty()) {
            imageComponent->SetResourceId(InternalResource::ResourceId::SIDE_BAR);
        } else {
            imageComponent->SetSrc(sideBar_->GetSwitchIcon());
        }
    }
    imageComponent->SetUseSkiaSvg(false);
    imageComponent->SetImageFit(ImageFit::FILL);
    renderImage->Update(imageComponent);
}

void RenderSideBarContainer::HandleDragUpdate(double xOffset)
{
    if (isAnimation_) {
        return;
    }
    if (status_ != SideStatus::SHOW) {
        return;
    }
    bool isSideBarWidthUnitPercent = sidebarWidth_.Unit() == DimensionUnit::PERCENT;
    bool isSideBarStart = sideBarPosition_ == SideBarPosition::START;
    auto sideBarLine = ConvertWidthToVp(preSidebarWidth_).ConvertToPx() + (isSideBarStart ? xOffset : -xOffset);
    auto minValue = ConvertWidthToVp(minSidebarWidth_).ConvertToPx();
    auto maxValue = ConvertWidthToVp(maxSidebarWidth_).ConvertToPx();
    if (sideBarLine > minValue && sideBarLine < maxValue) {
        if (isSideBarWidthUnitPercent) {
            sidebarWidth_ = ConvertWidthToPercent(
                Dimension(PipelineBase::Px2VpWithCurrentDensity(sideBarLine), DimensionUnit::VP));
        } else {
            sidebarWidth_ = Dimension(PipelineBase::Px2VpWithCurrentDensity(sideBarLine), DimensionUnit::VP);
        }

        SetChildrenStatus();
        return;
    }
    if (sideBarLine >= maxValue) {
        sidebarWidth_ = isSideBarWidthUnitPercent ? ConvertWidthToPercent(maxSidebarWidth_) : maxSidebarWidth_;
        SetChildrenStatus();
        return;
    }
    if (sideBarLine > minValue - DEFAULT_DRAG_REGION.ConvertToPx()) {
        sidebarWidth_ = isSideBarWidthUnitPercent ? ConvertWidthToPercent(minSidebarWidth_) : minSidebarWidth_;
        SetChildrenStatus();
        return;
    }
    sidebarWidth_ = isSideBarWidthUnitPercent ? ConvertWidthToPercent(minSidebarWidth_) : minSidebarWidth_;
    if (autoHide_) {
        DoSideBarAnimation();
    }
}

void RenderSideBarContainer::HandleDragStart()
{
    if (isAnimation_) {
        return;
    }
    if (status_ != SideStatus::SHOW) {
        return;
    }
    preSidebarWidth_ = sidebarWidth_;
}

void RenderSideBarContainer::HandleDragEnd()
{
    if (isAnimation_) {
        return;
    }
    if (status_ != SideStatus::SHOW) {
        return;
    }
    preSidebarWidth_ = sidebarWidth_;
}

} // namespace OHOS::Ace
