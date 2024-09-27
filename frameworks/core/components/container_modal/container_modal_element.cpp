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

#include "core/components/container_modal/container_modal_element.h"

#include "core/components/clip/clip_element.h"
#include "core/components/clip/render_clip.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/padding/render_padding.h"

namespace OHOS::Ace {
namespace {

constexpr uint32_t COLUMN_CHILD_NUM = 2;
constexpr uint32_t TITLE_POSITION = 1;
constexpr uint32_t SPLIT_BUTTON_POSITION = 2;
constexpr uint32_t TITLE_POPUP_TIME = 200;        // 200ms
constexpr double MOUSE_MOVE_POPUP_DISTANCE = 5.0; // 5.0px
constexpr double MOVE_POPUP_DISTANCE_X = 10.0;    // 10.0px
constexpr double MOVE_POPUP_DISTANCE_Y = 20.0;    // 20.0px
constexpr double TITLE_POPUP_DISTANCE = 37.0;     // 37vp height of title

} // namespace

RefPtr<StackElement> ContainerModalElement::GetStackElement() const
{
    auto containerBox = AceType::DynamicCast<BoxElement>(GetFirstChild());
    if (!containerBox) {
        LOGE("Get stack element failed, container box element is null!");
        return {};
    }

    // The first stack is not what we need.
    auto stackElement = AceType::DynamicCast<StackElement>(containerBox->GetFirstChild());
    if (!stackElement) {
        LOGE("Get stack element failed, stack element is null!");
        return {};
    }

    auto column = AceType::DynamicCast<ColumnElement>(stackElement->GetFirstChild());
    if (!column || column->GetChildren().size() != COLUMN_CHILD_NUM) {
        // column should have 2 children, title and content.
        LOGE("Get stack element failed, column is null or child size error!");
        return {};
    }

    // Get second child : content
    auto clip = AceType::DynamicCast<ClipElement>(column->GetLastChild());
    if (!clip) {
        LOGE("Get stack element failed, clip element is null!");
        return {};
    }

    auto contentBox = AceType::DynamicCast<BoxElement>(clip->GetFirstChild());
    if (!contentBox) {
        LOGE("Get stack element failed, content box element is null!");
        return {};
    }

    auto stack = contentBox->GetFirstChild();
    if (!stack || !AceType::InstanceOf<StackElement>(stack)) {
        LOGE("Get stack element failed, stack is null or type error!");
        return {};
    }

    return AceType::DynamicCast<StackElement>(stack);
}

RefPtr<OverlayElement> ContainerModalElement::GetOverlayElement() const
{
    auto stack = GetStackElement();
    if (!stack) {
        LOGE("Get overlay element failed, stack element is null");
        return {};
    }

    for (const auto& child : stack->GetChildren()) {
        if (child && AceType::InstanceOf<OverlayElement>(child)) {
            return AceType::DynamicCast<OverlayElement>(child);
        }
    }
    LOGE("Get overlay element failed, all children of stack element do not meet the requirements");
    return {};
}

RefPtr<StageElement> ContainerModalElement::GetStageElement() const
{
    auto stack = GetStackElement();
    if (!stack) {
        LOGE("Get stage element failed, stack element is null");
        return {};
    }
    for (const auto& child : stack->GetChildren()) {
        if (child && AceType::InstanceOf<StageElement>(child)) {
            return AceType::DynamicCast<StageElement>(child);
        }
    }
    LOGE("Get stage element failed, all children of stack element do not meet the requirements");
    return {};
}

void ContainerModalElement::ShowTitle(bool isShow, bool hasDeco, bool needUpdate)
{
    auto containerBox = AceType::DynamicCast<BoxElement>(GetFirstChild());
    if (!containerBox) {
        LOGE("ContainerModalElement showTitle failed, container box element is null!");
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("ContainerModalElement showTitle failed, context is null.");
        return;
    }
    windowMode_ = context->GetWindowManager()->GetWindowMode();
    hasDeco_ = hasDeco;
    TAG_LOGI(AceLogTag::ACE_APPBAR, "ShowTitle isShow: %{public}d, windowMode: %{public}d, hasDeco: %{public}d",
        isShow, windowMode_, hasDeco_);
    if (!hasDeco_) {
        isShow = false;
    }

    // full screen need to hide border and padding.
    auto containerRenderBox = AceType::DynamicCast<RenderBox>(containerBox->GetRenderNode());
    if (containerRenderBox) {
        auto containerDecoration = containerRenderBox->GetBackDecoration();
        Edge padding = Edge();
        Border outerBorder = Border();
        if (isShow) {
            outerBorder.SetBorderRadius(Radius(CONTAINER_OUTER_RADIUS));
            outerBorder.SetColor(CONTAINER_BORDER_COLOR);
            outerBorder.SetWidth(CONTAINER_BORDER_WIDTH);
            padding = Edge(CONTENT_PADDING, Dimension(0.0), CONTENT_PADDING, CONTENT_PADDING);
        }
        containerDecoration->SetBorder(outerBorder);
        containerRenderBox->SetBackDecoration(containerDecoration);
        containerRenderBox->SetPadding(padding);
    }

    auto stackElement = AceType::DynamicCast<StackElement>(containerBox->GetFirstChild());
    if (!stackElement) {
        LOGE("ContainerModalElement showTitle failed, stack element is null!");
        return;
    }

    auto column = AceType::DynamicCast<ColumnElement>(stackElement->GetFirstChild());
    if (!column || column->GetChildren().size() != COLUMN_CHILD_NUM) {
        // column should have 2 children, title and content.
        LOGE("ContainerModalElement showTitle failed, column  element is null or children size error!");
        return;
    }

    // full screen need to hide content border radius.
    auto clip = AceType::DynamicCast<ClipElement>(column->GetLastChild());
    if (!clip) {
        LOGE("ContainerModalElement showTitle failed, clip element is null!");
        return;
    }
    if (!contentBox_) {
        contentBox_ = AceType::DynamicCast<BoxElement>(clip->GetFirstChild());
    }
    auto renderClip = AceType::DynamicCast<RenderClip>(clip->GetRenderNode());
    if (renderClip) {
        isShow ? renderClip->SetClipRadius(Radius(CONTAINER_INNER_RADIUS)) : renderClip->SetClipRadius(Radius(0.0));
    }

    // Get first child : title
    auto display = AceType::DynamicCast<DisplayElement>(column->GetFirstChild());
    if (!display) {
        LOGE("ContainerModalElement showTitle failed,, display element is null.");
        return;
    }
    auto renderDisplay = AceType::DynamicCast<RenderDisplay>(display->GetRenderNode());
    if (renderDisplay) {
        renderDisplay->UpdateVisibleType(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
    }
    ChangeFloatingTitleIcon();

    // hide floating title anyway.
    if (floatingTitleDisplay_) {
        floatingTitleDisplay_->UpdateVisibleType(VisibleType::GONE);
    }
}

void ContainerModalElement::PerformBuild()
{
    SoleChildElement::PerformBuild();
    if (!controller_) {
        controller_ = CREATE_ANIMATOR(context_);
        controller_->SetDuration(TITLE_POPUP_TIME);
        controller_->SetFillMode(FillMode::FORWARDS);
        auto translateY = AceType::MakeRefPtr<CurveAnimation<DimensionOffset>>(
            DimensionOffset(Dimension(), Dimension(-TITLE_POPUP_DISTANCE * density_)),
            DimensionOffset(Dimension(), Dimension()), Curves::FRICTION);
        TweenOption option;
        option.SetTranslateAnimations(AnimationType::TRANSLATE_Y, translateY);
        auto containerBox = AceType::DynamicCast<BoxElement>(GetFirstChild());
        if (!containerBox) {
            LOGE("ContainerModalElement PerformBuild failed, container box element is null!");
            return;
        }

        auto stackElement = AceType::DynamicCast<StackElement>(containerBox->GetFirstChild());
        if (!stackElement) {
            LOGE("ContainerModalElement PerformBuild failed, stack element is null!");
            return;
        }
        auto column = AceType::DynamicCast<ColumnElement>(stackElement->GetFirstChild());
        if (!column || column->GetChildren().size() != COLUMN_CHILD_NUM) {
            // column should have 2 children, title and content.
            LOGE("ContainerModalElement PerformBuild failed, column  element is null or children size error!");
            return;
        }

        auto titleDisplay = AceType::DynamicCast<DisplayElement>(column->GetFirstChild());
        if (titleDisplay && titleDisplay->GetFirstChild()) {
            titleBox_ = AceType::DynamicCast<BoxElement>(titleDisplay->GetFirstChild()->GetFirstChild());
        }

        auto tween = AceType::DynamicCast<TweenElement>(stackElement->GetLastChild());
        if (!tween) {
            LOGE("ContainerModalElement PerformBuild failed, tween element is null.");
            return;
        }
        if (tween->GetContentElement()) {
            floatingTitleBox_ = AceType::DynamicCast<BoxElement>(tween->GetContentElement()->GetFirstChild());
        }

        auto display = AceType::DynamicCast<DisplayElement>(tween->GetFirstChild());
        if (display && !floatingTitleDisplay_) {
            floatingTitleDisplay_ = AceType::DynamicCast<RenderDisplay>(display->GetRenderNode());
            if (floatingTitleDisplay_) {
                floatingTitleDisplay_->UpdateVisibleType(VisibleType::GONE);
            }
        }
        tween->SetController(controller_);
        tween->SetOption(option);
        tween->ApplyKeyframes();
    }

    ChangeTitleIcon();

    // The first time it starts up, it needs to hide title if mode as follows.
    windowMode_ = context_.Upgrade()->GetWindowManager()->GetWindowMode();
    ShowTitle(windowMode_ == WindowMode::WINDOW_MODE_FLOATING, hasDeco_);
}

void ContainerModalElement::FlushReload()
{
    auto containerBox = AceType::DynamicCast<BoxElement>(GetFirstChild());
    if (!containerBox) {
        LOGE("ContainerModalElement WindowFocus failed, container box element is null!");
        return;
    }
    auto containerRenderBox = AceType::DynamicCast<RenderBox>(containerBox->GetRenderNode());
    if (containerRenderBox) {
        auto containerDecoration = containerRenderBox->GetBackDecoration();
        containerDecoration->SetBackgroundColor(
            windowFocus_ ? CONTAINER_BACKGROUND_COLOR : CONTAINER_BACKGROUND_COLOR_LOST_FOCUS);
        auto border = containerDecoration->GetBorder();
        border.SetColor(windowFocus_ ? CONTAINER_BORDER_COLOR : CONTAINER_BORDER_COLOR_LOST_FOCUS);
        containerDecoration->SetBorder(border);
        containerRenderBox->SetBackDecoration(containerDecoration);
    }
    if (windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN || windowMode_ == WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
        windowMode_ == WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
        ChangeFloatingTitleIcon(windowFocus_);
        return;
    }
    ChangeTitleIcon(windowFocus_);
}

void ContainerModalElement::Update()
{
    RenderElement::Update();

    containerModalComponent_ = AceType::DynamicCast<ContainerModalComponent>(component_);
    if (!containerModalComponent_) {
        LOGE("ContainerModalElement update failed, container modal component is null.");
        return;
    }
    auto containerBox = AceType::DynamicCast<BoxComponent>(containerModalComponent_->GetChild());
    if (!containerBox) {
        LOGE("ContainerModalElement update failed, container box component is null.");
        return;
    }
    auto context = context_.Upgrade();
    if (context) {
        density_ = (float)context->GetDensity();
    }

    containerBox->SetOnTouchDownId([weak = WeakClaim(this), context = context_](const TouchEventInfo& info) {
        auto containerElement = weak.Upgrade();
        auto pipeline = context.Upgrade();
        if (!pipeline || !containerElement || !containerElement->hasDeco_) {
            return;
        }
        auto viewScale = pipeline->GetViewScale();
        if (info.GetChangedTouches().begin()->GetGlobalLocation().GetY() * viewScale <=
            (TITLE_POPUP_DISTANCE * containerElement->density_)) {
            containerElement->moveX_ = info.GetChangedTouches().begin()->GetGlobalLocation().GetX() * viewScale;
            containerElement->moveY_ = info.GetChangedTouches().begin()->GetGlobalLocation().GetY() * viewScale;
            return;
        }

        // touch other area to hide floating title
        if (containerElement->CanHideFloatingTitle()) {
            containerElement->controller_->AddStopListener([weak] {
                auto container = weak.Upgrade();
                if (container && container->floatingTitleDisplay_) {
                    container->floatingTitleDisplay_->UpdateVisibleType(VisibleType::GONE);
                }
            });
            containerElement->controller_->Backward();
        }
    });

    // touch top to pop-up title bar.
    containerBox->SetOnTouchMoveId([weak = WeakClaim(this), context = context_](const TouchEventInfo& info) {
        auto containerElement = weak.Upgrade();
        auto pipeline = context.Upgrade();
        if (!pipeline || !containerElement || !containerElement->hasDeco_ ||
            !containerElement->CanShowFloatingTitle()) {
            return;
        }
        auto viewScale = pipeline->GetViewScale();
        if (info.GetChangedTouches().begin()->GetGlobalLocation().GetY() * viewScale >
            (TITLE_POPUP_DISTANCE * containerElement->density_)) {
            return;
        }
        auto deltaMoveX =
            fabs(info.GetChangedTouches().begin()->GetGlobalLocation().GetX() * viewScale - containerElement->moveX_);
        auto deltaMoveY =
            info.GetChangedTouches().begin()->GetGlobalLocation().GetY() * viewScale - containerElement->moveY_;
        if (deltaMoveX <= MOVE_POPUP_DISTANCE_X && deltaMoveY >= MOVE_POPUP_DISTANCE_Y) {
            containerElement->floatingTitleDisplay_->UpdateVisibleType(VisibleType::VISIBLE);
            containerElement->controller_->ClearStopListeners();
            containerElement->controller_->AddStopListener([weak] {
                auto container = weak.Upgrade();
                container->SetTitleAccessibilityNodeOffset();
            });
            containerElement->controller_->Forward();
        }
    });

    // mouse move top to pop up title bar and move other area to hide title bar.
    containerBox->SetOnMouseId([weak = WeakClaim(this), context = context_](MouseInfo& info) {
        auto containerElement = weak.Upgrade();
        auto pipeline = context.Upgrade();
        if (!pipeline || !containerElement || !containerElement->hasDeco_ || info.GetAction() != MouseAction::MOVE) {
            return;
        }
        auto viewScale = pipeline->GetViewScale();
        if (info.GetLocalLocation().GetY() * viewScale <= MOUSE_MOVE_POPUP_DISTANCE &&
            containerElement->CanShowFloatingTitle()) {
            containerElement->floatingTitleDisplay_->UpdateVisibleType(VisibleType::VISIBLE);
            containerElement->controller_->ClearStopListeners();
            containerElement->controller_->AddStopListener([weak] {
                auto container = weak.Upgrade();
                container->SetTitleAccessibilityNodeOffset();
            });
            containerElement->controller_->Forward();
        }
        if (info.GetLocalLocation().GetY() * viewScale > (TITLE_POPUP_DISTANCE * containerElement->density_) &&
            containerElement->CanHideFloatingTitle()) {
            containerElement->controller_->AddStopListener([weak] {
                auto container = weak.Upgrade();
                if (container && container->floatingTitleDisplay_) {
                    container->floatingTitleDisplay_->UpdateVisibleType(VisibleType::GONE);
                }
            });
            containerElement->controller_->Backward();
        }
    });
}

bool ContainerModalElement::CanShowFloatingTitle()
{
    if (!floatingTitleDisplay_ || !controller_) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "Show floating title failed, floatingTitleDisplay or controller is null.");
        return false;
    }
    if (windowMode_ != WindowMode::WINDOW_MODE_FULLSCREEN && windowMode_ != WindowMode::WINDOW_MODE_SPLIT_PRIMARY &&
        windowMode_ != WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "Window is not full screen or split screen, can not show floating title.");
        return false;
    }
    if (floatingTitleDisplay_->GetVisible()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "Floating tittle is visible now, no need to show again.");
        return false;
    }
    return true;
}

bool ContainerModalElement::CanHideFloatingTitle()
{
    if (!floatingTitleDisplay_ || !controller_) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "Hide floating title failed, floatingTitleDisplay or controller is null.");
        return false;
    }
    if (!floatingTitleDisplay_->GetVisible()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "Hide floating title failed, title is not visible.");
        return false;
    }
    return true;
}

void ContainerModalElement::ChangeFloatingTitleIcon(bool isFocus)
{
    if (!floatingTitleBox_ || !containerModalComponent_) {
        LOGE("ChangeFloatingTitleIcon failed.");
        return;
    }
    auto renderFloatingTitleBox = AceType::DynamicCast<RenderBox>(floatingTitleBox_->GetRenderNode());
    if (!renderFloatingTitleBox) {
        LOGE("ChangeFloatingTitleIcon failed, render floating title box is null.");
        return;
    }
    auto backDecoration = renderFloatingTitleBox->GetBackDecoration();
    backDecoration->SetBackgroundColor(isFocus ? CONTAINER_BACKGROUND_COLOR : CONTAINER_BACKGROUND_COLOR_LOST_FOCUS);
    renderFloatingTitleBox->SetBackDecoration(backDecoration);

    auto rowElement = AceType::DynamicCast<RowElement>(floatingTitleBox_->GetFirstChild());
    if (!rowElement) {
        LOGE("ChangeFloatingTitleIcon failed, row element is null.");
        return;
    }
    RefPtr<RenderPadding> splitButton = nullptr;
    if (!containerModalComponent_->GetSplitButtonHide()) {
        auto renderRow = AceType::DynamicCast<RenderFlex>(rowElement->GetRenderNode());
        if (!renderRow) {
            LOGE("ChangeFloatingTitleIcon failed, renderRow is null.");
            return;
        }
        auto iterator = renderRow->GetChildren().begin();
        std::advance(iterator, SPLIT_BUTTON_POSITION);
        splitButton = AceType::DynamicCast<RenderPadding>(*iterator);
    }

    auto floatingTitleChildrenRow = AceType::MakeRefPtr<RowComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER,
        containerModalComponent_->BuildTitleChildren(true, isFocus, windowMode_ == WindowMode::WINDOW_MODE_FULLSCREEN));
    floatingTitleChildrenRow->SetUpdateType(UpdateType::REBUILD);
    rowElement->SetUpdateComponent(floatingTitleChildrenRow);

    if (splitButton) {
        splitButton->SetHidden(windowMode_ == WindowMode::WINDOW_MODE_SPLIT_PRIMARY);
    }
}

void ContainerModalElement::ChangeTitleIcon(bool isFocus)
{
    if (!titleBox_ || !containerModalComponent_) {
        LOGE("ChangeTitleIcon failed.");
        return;
    }
    auto rowElement = AceType::DynamicCast<RowElement>(titleBox_->GetFirstChild());
    if (!rowElement) {
        LOGE("ChangeTitleIcon failed, row element is null.");
        return;
    }
    auto titleChildrenRow = AceType::MakeRefPtr<RowComponent>(
        FlexAlign::FLEX_START, FlexAlign::CENTER, containerModalComponent_->BuildTitleChildren(false, isFocus));
    titleChildrenRow->SetUpdateType(UpdateType::REBUILD);
    rowElement->SetUpdateComponent(titleChildrenRow);
}

void ContainerModalElement::WindowFocus(bool isFocus)
{
    windowFocus_ = isFocus;
    FlushReload();
}

void ContainerModalElement::SetAppBgColor(const Color& color)
{
    if (!contentBox_) {
        LOGE("SetAppBgColor failed, contentBox_ is nullptr.");
        return;
    }
    auto renderContentBox = AceType::DynamicCast<RenderBox>(contentBox_->GetRenderNode());
    if (!renderContentBox) {
        LOGE("SetAppBgColor failed, renderContentBox is nullptr.");
        return;
    }
    auto backDecoration = renderContentBox->GetBackDecoration();
    backDecoration->SetBackgroundColor(color);
    renderContentBox->SetBackDecoration(backDecoration);
}

void ContainerModalElement::SetTitleButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose)
{
    if (!titleBox_ || !floatingTitleBox_ || !containerModalComponent_) {
        LOGE("titleBox_  floatingTitleBox_ or containerModalComponent_ is null.");
        return;
    }
    auto rowElement = AceType::DynamicCast<RowElement>(titleBox_->GetFirstChild());
    if (!rowElement) {
        LOGE("row element is null.");
        return;
    }
    auto floatingRowElement = AceType::DynamicCast<RowElement>(floatingTitleBox_->GetFirstChild());
    if (!floatingRowElement) {
        LOGE("floating row element is null.");
        return;
    }
    containerModalComponent_->SetTitleButtonHide(hideSplit, hideMaximize, hideMinimize, hideClose);

    auto titleChildrenRow = AceType::MakeRefPtr<RowComponent>(
        FlexAlign::FLEX_START, FlexAlign::CENTER, containerModalComponent_->BuildTitleChildren(false, windowFocus_));
    titleChildrenRow->SetUpdateType(UpdateType::REBUILD);
    rowElement->SetUpdateComponent(titleChildrenRow);

    auto floatingTitleChildrenRow = AceType::MakeRefPtr<RowComponent>(
        FlexAlign::FLEX_START, FlexAlign::CENTER, containerModalComponent_->BuildTitleChildren(true, windowFocus_));
    floatingTitleChildrenRow->SetUpdateType(UpdateType::REBUILD);
    floatingRowElement->SetUpdateComponent(floatingTitleChildrenRow);
}

void ContainerModalElement::SetAppTitle(const std::string& title)
{
    CHECK_NULL_VOID(containerModalComponent_);
    auto textComponent = containerModalComponent_->GetTitleLabel();
    CHECK_NULL_VOID(textComponent);
    if (textComponent->GetData() == title) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "set same title, skip, title is %{public}s", title.c_str());
        return;
    }
    textComponent->SetData(title);
    bool isFloatingTitle = windowMode_ != WindowMode::WINDOW_MODE_FLOATING;
    auto renderTitle = GetTitleRender(isFloatingTitle);
    CHECK_NULL_VOID(renderTitle);
    renderTitle->Update(textComponent);
    renderTitle->MarkNeedRender();
    TAG_LOGI(AceLogTag::ACE_APPBAR,
        "set app title successfully, title:%{public}s, isFloatingTitle:%{public}d",
        title.c_str(), static_cast<int>(isFloatingTitle));
}

void ContainerModalElement::SetAppIcon(const RefPtr<PixelMap>& icon)
{
    CHECK_NULL_VOID(containerModalComponent_);
    auto imageComponent = containerModalComponent_->GetTitleIcon();
    CHECK_NULL_VOID(imageComponent);
    imageComponent->SetSrc("");
    imageComponent->SetPixmap(icon);
    bool isFloatingTitle = windowMode_ != WindowMode::WINDOW_MODE_FLOATING;
    auto renderIcon = GetIconRender(isFloatingTitle);
    CHECK_NULL_VOID(renderIcon);
    renderIcon->Update(imageComponent);
    renderIcon->MarkNeedRender();
    TAG_LOGI(AceLogTag::ACE_APPBAR,
        "set app icon successfully, isFloatingTitle:%{public}d",
        static_cast<int>(isFloatingTitle));
}

RefPtr<RenderText> ContainerModalElement::GetTitleRender(bool isFloatingTitle)
{
    auto titleBoxElement = isFloatingTitle ? floatingTitleBox_ : titleBox_;
    CHECK_NULL_RETURN(titleBoxElement, nullptr);
    auto rowElement = AceType::DynamicCast<RowElement>(titleBoxElement->GetFirstChild());
    CHECK_NULL_RETURN(rowElement, nullptr);
    auto renderRow = AceType::DynamicCast<RenderFlex>(rowElement->GetRenderNode());
    CHECK_NULL_RETURN(renderRow, nullptr);
    const auto& children = renderRow->GetChildren();
    if (children.size() <= TITLE_POSITION) {
        TAG_LOGW(AceLogTag::ACE_APPBAR, "row children size is wrong");
        return nullptr;
    }
    auto iterator = renderRow->GetChildren().begin();
    std::advance(iterator, TITLE_POSITION);
    auto title = AceType::DynamicCast<RenderText>(*iterator);
    return title;
}

RefPtr<RenderImage> ContainerModalElement::GetIconRender(bool isFloatingTitle)
{
    auto titleBoxElement = isFloatingTitle ? floatingTitleBox_ : titleBox_;
    CHECK_NULL_RETURN(titleBoxElement, nullptr);
    auto rowElement = AceType::DynamicCast<RowElement>(titleBoxElement->GetFirstChild());
    CHECK_NULL_RETURN(rowElement, nullptr);
    auto renderRow = AceType::DynamicCast<RenderFlex>(rowElement->GetRenderNode());
    CHECK_NULL_RETURN(renderRow, nullptr);
    auto renderPadding = AceType::DynamicCast<RenderPadding>(renderRow->GetFirstChild());
    CHECK_NULL_RETURN(renderPadding, nullptr);
    auto icon = AceType::DynamicCast<RenderImage>(renderPadding->GetFirstChild());
    return icon;
}

void ContainerModalElement::SetTitleAccessibilityNodeOffset()
{
    CHECK_NULL_VOID(floatingTitleBox_);
    auto floatingTitleBoxRender = AceType::DynamicCast<RenderBox>(floatingTitleBox_->GetRenderNode());
    if (floatingTitleBoxRender) {
        auto accessibilityNode = floatingTitleBoxRender->GetAccessibilityNode().Upgrade();
        if (accessibilityNode) {
            Offset globalOffset =
                (floatingTitleBoxRender->GetGlobalOffsetExternal() + floatingTitleBoxRender->GetMargin().GetOffset()) *
                floatingTitleBoxRender->GetContext().Upgrade()->GetViewScale();
            Offset transformOffset(
                globalOffset.GetX() - accessibilityNode->GetLeft(), globalOffset.GetY() - accessibilityNode->GetTop());
            accessibilityNode->AddOffsetForChildren(transformOffset);
        }
    }
}

} // namespace OHOS::Ace
