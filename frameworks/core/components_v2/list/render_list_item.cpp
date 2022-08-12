/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_v2/list/render_list_item.h"

#include "core/components/box/box_component.h"
#include "core/components/box/render_box.h"
#include "core/components/button/button_component.h"
#include "core/components/image/image_component.h"
#include "core/components_v2/list/render_list.h"

namespace OHOS::Ace::V2 {
namespace {

constexpr Dimension ICON_WIDTH = 24.0_px;
constexpr Dimension BUTTON_WIDTH = 72.0_px;
constexpr double SWIPER_TH = 0.25;
constexpr double SWIPER_SPEED_TH = 1200;

} // namespace

RefPtr<RenderNode> RenderListItem::Create()
{
    return AceType::MakeRefPtr<RenderListItem>();
}

void RenderListItem::Update(const RefPtr<Component>& component)
{
    auto item = AceType::DynamicCast<ListItemComponent>(component);
    if (!item) {
        LOGW("Not ListItemComponent, nothing to do");
        return;
    }

    component_ = item;
    SetEditMode(false);

    if (IsDeletable()) {
        CreateDeleteButton();
    } else {
        button_.Reset();
    }

    onSelectId_ = item->GetOnSelectId();
    selectable_ = item->GetSelectable();
    borderRadius_ = item->GetBorderRadius();
    edgeEffect_ = item->GetEdgeEffect();

    if (item->GetSwiperEndComponent() || item->GetSwiperEndComponent()) {
        InitDragRecognizer();
    } else {
        dragDetector_.Reset();
        springController_.Reset();
    }

    MarkNeedLayout();
}

void RenderListItem::Paint(RenderContext& context, const Offset& offset)
{
    if (swiperStart_) {
        PaintChild(swiperStart_, context, offset);
    }
    if (swiperEnd_) {
        PaintChild(swiperEnd_, context, offset);
    }
    if (child_) {
        PaintChild(child_, context, offset);
    }
    if (button_ && editMode_) {
        PaintChild(button_, context, offset);
    }
}

void RenderListItem::PerfLayoutSwiperMode()
{
    child_ = GetItemChildRnderNode();
    if (!child_) {
        return;
    }
    const auto& layoutParam = GetLayoutParam();
    child_->Layout(layoutParam);
    const auto& childSize = child_->GetLayoutSize();
    double maxHeight = childSize.Height();

    if (GreatNotEqual(curOffset_, 0.0)) {
        swiperEnd_.Reset();
        auto swiperStart = GetSwiperStartRnderNode();
        if (swiperStart) {
            Size startSize = startSize_;
            if (!swiperStart_) {
                swiperStart->Layout(LayoutParam(layoutParam.GetMaxSize(), Size()));
                startSize_ = swiperStart->GetLayoutSize();
                startSize = startSize_;
            } else if (GreatNotEqual(curOffset_, startSize_.Width())) {
                Size maxSize(curOffset_, layoutParam.GetMaxSize().Height());
                swiperStart->Layout(LayoutParam(maxSize, Size(curOffset_, 0.0)));
                startSize = swiperStart->GetLayoutSize();
            }
            maxHeight = std::max(maxHeight, startSize.Height());
            double startPos = curOffset_ - startSize.Width();
            swiperStart->SetPosition(Offset(startPos, (maxHeight - startSize.Height()) / 2)); /* 2:averages */
        }
        swiperStart_ = swiperStart;
    } else {
        swiperStart_.Reset();
        auto swiperEnd = GetSwiperEndRnderNode();
        if (swiperEnd) {
            Size endSize = endSize_;
            if (!swiperEnd_) {
                swiperEnd->Layout(LayoutParam(layoutParam.GetMaxSize(), Size()));
                endSize_ = swiperEnd->GetLayoutSize();
                endSize = endSize_;
            } else if (GreatNotEqual(-curOffset_, endSize_.Width())) {
                Size maxSize(-curOffset_, layoutParam.GetMaxSize().Height());
                swiperEnd->Layout(LayoutParam(maxSize, Size(-curOffset_, 0.0)));
                endSize = swiperEnd->GetLayoutSize();
            }
            maxHeight = std::max(maxHeight, endSize.Height());
            double startPos = childSize.Width() + curOffset_;
            swiperEnd->SetPosition(Offset(startPos, (maxHeight - endSize.Height()) / 2)); /* 2:averages */
        }
        swiperEnd_ = swiperEnd;
    }
    child_->SetPosition(Offset(curOffset_, (maxHeight - childSize.Height()) / 2)); /* 2:averages */
    SetLayoutSize(layoutParam.Constrain(Size(childSize.Width(), maxHeight)));
}

void RenderListItem::PerformLayout()
{
    if (!NearZero(curOffset_)) {
        PerfLayoutSwiperMode();
        return;
    }
    swiperStart_.Reset();
    swiperEnd_.Reset();

    const auto& layoutParam = GetLayoutParam();
    Size childLayoutSize;
    Size buttonLayoutSize;

    if (button_ && editMode_) {
        button_->Layout(LayoutParam(layoutParam.GetMaxSize(), Size()));
        buttonLayoutSize = button_->GetLayoutSize();
    }

    child_ = GetItemChildRnderNode();
    if (child_) {
        auto maxSize = layoutParam.GetMaxSize();
        auto minSize = layoutParam.GetMinSize();
        if (!NearEqual(maxSize.Width(), Size::INFINITE_SIZE)) {
            maxSize.SetWidth(std::max(maxSize.Width() - buttonLayoutSize.Width(), 0.0));
            minSize.SetWidth(std::min(minSize.Width(), maxSize.Width()));
        }

        child_->Layout(LayoutParam(maxSize, minSize));
        childLayoutSize = child_->GetLayoutSize();
    }

    double width = childLayoutSize.Width() + buttonLayoutSize.Width();
    double height = std::max(childLayoutSize.Height(), buttonLayoutSize.Height());

    if (child_) {
        child_->SetPosition(Offset(0.0, (height - childLayoutSize.Height()) / 2.0));
    }

    if (button_ && editMode_) {
        button_->SetPosition(Offset(childLayoutSize.Width(), (height - buttonLayoutSize.Height()) / 2.0));
    }

    SetLayoutSize(layoutParam.Constrain(Size(width, height)));
}

void RenderListItem::SetEditMode(bool editMode)
{
    if (editMode_ == editMode) {
        return;
    }

    editMode_ = editMode;
    if (!button_) {
        return;
    }

    if (editMode_) {
        AddChild(button_);
    } else {
        RemoveChild(button_);
    }
}

void RenderListItem::CreateDeleteButton()
{
    if (!button_) {
        auto imageComponent = AceType::MakeRefPtr<ImageComponent>(InternalResource::ResourceId::CLOSE_SVG);
        imageComponent->SetImageSourceSize({ ICON_WIDTH, ICON_WIDTH });
        imageComponent->SetFitMaxSize(true);

        auto buttonComponent = AceType::MakeRefPtr<ButtonComponent>(std::list<RefPtr<Component>>());
        buttonComponent->SetType(ButtonType::ICON);
        buttonComponent->SetWidth(BUTTON_WIDTH);
        buttonComponent->SetHeight(BUTTON_WIDTH);

        buttonComponent->SetClickFunction([weak = AceType::WeakClaim(this)] {
            auto spThis = weak.Upgrade();
            if (spThis) {
                ResumeEventCallback(spThis, &RenderListItem::GetOnDeleteClick, spThis);
            }
        });

        auto button = buttonComponent->CreateRenderNode();
        button->Attach(context_);
        button->Update(buttonComponent);
        auto image = imageComponent->CreateRenderNode();
        image->Attach(context_);
        image->Update(imageComponent);

        auto boxComponent = AceType::MakeRefPtr<BoxComponent>();
        boxComponent->SetEnableDebugBoundary(true);
        auto buttonBox = boxComponent->CreateRenderNode();
        buttonBox->Attach(context_);
        buttonBox->Update(boxComponent);
        
        button->AddChild(buttonBox);
        buttonBox->AddChild(image);
        button_ = button;
    }
}

void RenderListItem::UpdateTouchRect()
{
    RenderNode::UpdateTouchRect();
    if (button_ && IsResponseRegion()) {
        auto buttonTouchRect = button_->GetPaintRect();
        std::vector<Rect> touchRectList;
        for (auto& region : responseRegion_) {
            double x = GetPxValue(touchRect_.Width(), region.GetOffset().GetX());
            double y = GetPxValue(touchRect_.Height(), region.GetOffset().GetY());
            double width = GetPxValue(buttonTouchRect.Width(), region.GetWidth());
            double height = GetPxValue(buttonTouchRect.Height(), region.GetHeight());
            Rect responseRegion(buttonTouchRect.GetOffset().GetX() + x,
                buttonTouchRect.GetOffset().GetY() + y, width, height);
            touchRectList.emplace_back(responseRegion);
        }
        button_->ChangeTouchRectList(touchRectList);
    }
}

void RenderListItem::InitDragRecognizer()
{
    auto weak = AceType::WeakClaim(this);
    if (!dragDetector_) {
        dragDetector_ = AceType::MakeRefPtr<HorizontalDragRecognizer>();
    }
    if (!dragDetector_) {
        return;
    }

    dragDetector_->SetOnDragStart([weak](const DragStartInfo& info) {
        auto client = weak.Upgrade();
        if (client) {
            client->HandleDragStart(info);
        }
    });

    dragDetector_->SetOnDragUpdate([weak](const DragUpdateInfo& info) {
        auto client = weak.Upgrade();
        if (client) {
            client->HandleDragUpdate(info);
        }
    });

    dragDetector_->SetOnDragEnd([weak](const DragEndInfo& info) {
        auto client = weak.Upgrade();
        if (client) {
            client->HandleDragEnd(info);
        }
    });

    
    if (!springController_) {
        springController_ = AceType::MakeRefPtr<Animator>(context_);
    }
}

void RenderListItem::HandleDragStart(const DragStartInfo& info)
{
    if (springController_ && !springController_->IsStopped()) {
        // clear stop listener before stop
        springController_->ClearStopListeners();
        springController_->Stop();
    }
}

static double CalculateFriction(double gamma)
{
    constexpr double SCROLL_RATIO = 0.72;
    if (GreatOrEqual(gamma, 1.0)) {
        gamma = 1.0;
    }
    return SCROLL_RATIO * std::pow(1.0 - gamma, SQUARE);
}

double RenderListItem::GetFriction()
{
    if (GreatNotEqual(curOffset_, 0.0)) {
        double width =  swiperStart_ ? startSize_.Width() : 0.0;
        double itemWidth = child_->GetLayoutSize().Width();
        if (width < curOffset_) {
            return CalculateFriction((curOffset_ - width) / (itemWidth - width));
        }
    } else if (LessNotEqual(curOffset_, 0.0)) {
        double width = swiperEnd_ ? endSize_.Width() : 0.0;
        double itemWidth = child_->GetLayoutSize().Width();
        if (width < -curOffset_) {
            return CalculateFriction((-curOffset_ - width) / (itemWidth - width));
        }
    }
    return 1.0;
}

void RenderListItem::UpdatePostion(double delta)
{
    double offset = curOffset_;
    curOffset_ += delta;
    if (edgeEffect_ == SwipeEdgeEffect::None) {
        if (swiperStart_ && GreatNotEqual(curOffset_, startSize_.Width())) {
            curOffset_ = startSize_.Width();
        } else if (swiperEnd_ && GreatNotEqual(-curOffset_, endSize_.Width())) {
            curOffset_ = -endSize_.Width();
        }
        if (Negative(curOffset_) && !GetSwiperEndRnderNode()) {
            curOffset_ = 0.0;
        } else if (Positive(curOffset_) && !GetSwiperStartRnderNode()) {
            curOffset_ = 0.0;
        }
    }
    if (!NearEqual(offset, curOffset_)) {
        MarkNeedLayout();
    }
}

void RenderListItem::HandleDragUpdate(const DragUpdateInfo& info)
{
    double delta = info.GetMainDelta();
    delta *= GetFriction();
    UpdatePostion(delta);
}

void RenderListItem::StartSpringMotion(double start, double end, double velocity)
{
    if (!springController_) {
        return;
    }

    constexpr double SPRING_SCROLL_MASS = 1;
    constexpr double SPRING_SCROLL_STIFFNESS = 228;
    constexpr double SPRING_SCROLL_DAMPING = 30;
    const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
    AceType::MakeRefPtr<SpringProperty>(SPRING_SCROLL_MASS, SPRING_SCROLL_STIFFNESS, SPRING_SCROLL_DAMPING);

    springMotion_ = AceType::MakeRefPtr<SpringMotion>(start, end, velocity, DEFAULT_OVER_SPRING_PROPERTY);
    springMotion_->AddListener([weakScroll = AceType::WeakClaim(this), start, end](double position) {
        auto listItem = weakScroll.Upgrade();
        if (listItem) {
            if (listItem->edgeEffect_ == SwipeEdgeEffect::None &&
                ((GreatNotEqual(end, start) && GreatOrEqual(position, end)) ||
                (LessNotEqual(end, start) && LessOrEqual(position, end)))) {
                listItem->springController_->ClearStopListeners();
                listItem->springController_->Stop();
                position = end;
            }
            listItem->UpdatePostion(position - listItem->curOffset_);
        }
    });
    springController_->ClearStopListeners();
    springController_->PlayMotion(springMotion_);
    springController_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto listItem = weak.Upgrade();
        if (listItem) {
            listItem->MarkNeedLayout(true);
        }
    });
}

void RenderListItem::HandleDragEnd(const DragEndInfo& info)
{
    double end = 0;
    double friction = GetFriction();
    bool reachRightSpeed = info.GetMainVelocity() > SWIPER_SPEED_TH;
    bool reachLeftSpeed = -info.GetMainVelocity() > SWIPER_SPEED_TH;
    if (GreatNotEqual(curOffset_, 0.0) && swiperStart_) {
        double width = startSize_.Width();
        if (currPage_ == 0 && (curOffset_ > width * SWIPER_TH || reachRightSpeed)) {
            currPage_ = 1;
        } else if (currPage_ == 1 && (curOffset_ < width * (1 - SWIPER_TH) || reachLeftSpeed)) {
            currPage_ = 0;
        } else if (currPage_ < 0) {
            currPage_ = 0;
        }
        end = width * currPage_;
    } else if (LessNotEqual(curOffset_, 0.0) && swiperEnd_) {
        double width = endSize_.Width();
        if (currPage_ == 0 && (width * SWIPER_TH < -curOffset_ || reachLeftSpeed)) {
            currPage_ = -1;
        } else if (currPage_ == -1 && (-curOffset_ < width * (1 - SWIPER_TH) || reachRightSpeed)) {
            currPage_ = 0;
        } else if (currPage_ > 0) {
            currPage_ = 0;
        }
        end = width * currPage_;
    }
    StartSpringMotion(curOffset_, end, info.GetMainVelocity() * friction);
}

void RenderListItem::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (IsDisabled()) {
        return;
    }

    RefPtr<RenderNode> parent = GetParent().Upgrade();
    RefPtr<RenderList> renderList = AceType::DynamicCast<RenderList>(parent);
    if (!renderList || !renderList->GetDirection()) {
        return;
    }

    if (dragDetector_ && (GetSwiperStartRnderNode() || GetSwiperEndRnderNode())) {
        dragDetector_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(dragDetector_);
    }
}

} // namespace OHOS::Ace::V2
