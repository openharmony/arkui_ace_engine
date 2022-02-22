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

#include "core/components/box/box_element.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/container_modal/render_container_modal.h"
#include "core/components/flex/flex_element.h"
#include "core/components/flex/flex_item_element.h"

namespace OHOS::Ace {
namespace {

constexpr uint32_t COLUMN_CHILD_NUM = 2;
constexpr uint32_t TITLE_POPUP_TIME = 500;     // 500ms
constexpr double TITLE_POPUP_DISTANCE = 100.0; // 100px

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
    auto contentBox = AceType::DynamicCast<BoxElement>(column->GetLastChild());
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

void ContainerModalElement::ShowTitle(bool isShow)
{
    auto containerBox = AceType::DynamicCast<BoxElement>(GetFirstChild());
    if (!containerBox) {
        LOGE("ContainerModalElement showTitle failed, container box element is null!");
        return;
    }
    auto containerRenderBox = AceType::DynamicCast<RenderBox>(containerBox->GetRenderNode());
    if (containerRenderBox) {
        auto containerDecoration = AceType::MakeRefPtr<Decoration>();
        Edge padding = Edge();
        if (isShow) {
            Border outerBorder;
            outerBorder.SetBorderRadius(Radius(CONTAINER_OUTER_RADIUS));
            outerBorder.SetColor(CONTAINER_BORDER_COLOR);
            outerBorder.SetWidth(CONTAINER_BORDER_WIDTH);
            containerDecoration->SetBackgroundColor(CONTAINER_BACKGROUND_COLOR);
            containerDecoration->SetBorder(outerBorder);
            padding = Edge(CONTENT_PADDING, Dimension(0.0), CONTENT_PADDING, CONTENT_PADDING);
        }
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

    auto contentRenderBox = AceType::DynamicCast<RenderBox>(column->GetLastChild()->GetRenderNode());
    if (contentRenderBox) {
        auto contentDecoration = AceType::MakeRefPtr<Decoration>();
        contentDecoration->SetBackgroundColor(CONTENT_BACKGROUND_COLOR);
        if (isShow) {
            Border contentBorder;
            contentBorder.SetBorderRadius(Radius(CONTAINER_INNER_RADIUS));
            contentDecoration->SetBorder(contentBorder);
        }
        contentRenderBox->SetBackDecoration(contentDecoration);
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

    // hide floating title anyway.
    if (renderDisplay_) {
        renderDisplay_->UpdateVisibleType(VisibleType::GONE);
    }
}

void ContainerModalElement::PerformBuild()
{
    SoleChildElement::PerformBuild();
    if (!controller_) {
        controller_ = AceType::MakeRefPtr<Animator>(context_);
        controller_->SetDuration(TITLE_POPUP_TIME);
        controller_->SetFillMode(FillMode::FORWARDS);
        auto translateY = AceType::MakeRefPtr<CurveAnimation<DimensionOffset>>(
            DimensionOffset(Dimension(), Dimension(-TITLE_POPUP_DISTANCE)), DimensionOffset(Dimension(), Dimension()),
            Curves::FRICTION);
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

        auto tween = AceType::DynamicCast<TweenElement>(stackElement->GetLastChild());
        if (!tween) {
            LOGE("ContainerModalElement PerformBuild failed, tween element is null.");
            return;
        }
        auto display = AceType::DynamicCast<DisplayElement>(tween->GetFirstChild());
        if (display && !renderDisplay_) {
            renderDisplay_ = AceType::DynamicCast<RenderDisplay>(display->GetRenderNode());
            if (renderDisplay_) {
                renderDisplay_->UpdateVisibleType(VisibleType::GONE);
            }
        }
        tween->SetController(controller_);
        tween->SetOption(option);
        tween->ApplyKeyframes();
    }
}

void ContainerModalElement::Update()
{
    RenderElement::Update();

    const auto container = AceType::DynamicCast<ContainerModalComponent>(component_);
    if (!container) {
        LOGE("ContainerModalElement update failed, container modal component is null.");
        return;
    }
    auto containerBox = AceType::DynamicCast<BoxComponent>(container->GetChild());
    if (!containerBox) {
        LOGE("ContainerModalElement update failed, container box component is null.");
        return;
    }

    // touch top to pop-up title bar.
    containerBox->SetOnTouchMoveId([week = WeakClaim(this)](const TouchEventInfo& info) {
        auto containerElement = week.Upgrade();
        if (!containerElement || !containerElement->CanShowFloatingTitle()) {
            return;
        }
        if (info.GetChangedTouches().begin()->GetGlobalLocation().GetY() <= TITLE_POPUP_DISTANCE) {
            containerElement->renderDisplay_->UpdateVisibleType(VisibleType::VISIBLE);
            containerElement->controller_->Forward();
        }
    });

    // mouse move top to pop-up title bar.
    containerBox->SetOnMouseId([week = WeakClaim(this)](MouseInfo& info) {
        auto containerElement = week.Upgrade();
        if (!containerElement || !containerElement->CanShowFloatingTitle()) {
            return;
        }
        if (info.GetAction() == MouseAction::MOVE && info.GetLocalLocation().GetY() <= TITLE_POPUP_DISTANCE) {
            containerElement->renderDisplay_->UpdateVisibleType(VisibleType::VISIBLE);
            containerElement->controller_->Forward();
        }
    });
}

bool ContainerModalElement::CanShowFloatingTitle()
{
    auto context = context_.Upgrade();
    if (!context || !renderDisplay_ || !controller_) {
        LOGI("Show floating title failed, context, renderDisplay_ or controller is null.");
        return false;
    }
    auto mode = context->FireWindowGetModeCallBack();
    if (mode != WindowMode::WINDOW_MODE_FULLSCREEN && mode != WindowMode::WINDOW_MODE_SPLIT_PRIMARY) {
        LOGI("Window is not full screen or split primary, can not show floating title.");
        return false;
    }
    if (renderDisplay_->GetVisibleType() == VisibleType::VISIBLE) {
        LOGI("Floating tittle is visible now, no need to show again.");
        return false;
    }
    return true;
}

} // namespace OHOS::Ace