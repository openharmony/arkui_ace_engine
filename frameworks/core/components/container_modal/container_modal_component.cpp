/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/container_modal/container_modal_component.h"

#include "core/components/box/box_component.h"
#include "core/components/button/button_component.h"
#include "core/components/clip/clip_component.h"
#include "core/components/container_modal/container_modal_element.h"
#include "core/components/container_modal/render_container_modal.h"
#include "core/components/flex/flex_component.h"
#include "core/components/flex/flex_item_component.h"
#include "core/components/image/image_component.h"
#include "core/components/padding/padding_component.h"
#include "core/components/text/text_component.h"
#include "core/components/tween/tween_component.h"

namespace OHOS::Ace {
namespace {

const Dimension CONTAINER_INNER_RADIUS = 14.0_vp;
const Dimension CONTAINER_OUTER_RADIUS = 16.0_vp;
const Dimension CONTAINER_BORDER_WIDTH = 1.0_vp;
const Dimension CONTAINER_TITLE_HEIGHT = 48.0_vp;
const Dimension TITLE_PADDING_START = 24.0_vp;
const Dimension TITLE_PADDING_END = 24.0_vp;
const Dimension ZERO_PADDING = 0.0_vp;
const Dimension TITLE_ELEMENT_MARGIN_HORIZONTAL = 16.0_vp;
const Dimension TITLE_ICON_SIZE = 20.0_vp;
const Dimension TITLE_BUTTON_SIZE = 24.0_vp;
const Dimension TITLE_TEXT_FONT_SIZE = 16.0_fp;
const Dimension CONTENT_MARGIN = 4.0_vp;
const Color CONTAINER_BACKGROUND_COLOR = Color(0xd6e4e5ed);
const Color CONTAINER_BORDER_COLOR = Color(0x33000000);
const Color TITLE_TEXT_COLOR = Color(0xe5000000);
const Color CONTENT_BACKGROUND_COLOR = Color(0xffffffff);
const Color TITLE_BUTTON_BACKGROUND_COLOR = Color(0x33000000);

} // namespace

RefPtr<Component> ContainerModalComponent::Create(
    const WeakPtr<PipelineContext>& context, const RefPtr<Component>& child)
{
    auto component = AceType::MakeRefPtr<ContainerModalComponent>(context);
    component->SetChild(child);
    component->BuildInnerChild();
    return component;
}

RefPtr<Element> ContainerModalComponent::CreateElement()
{
    return AceType::MakeRefPtr<ContainerModalElement>();
}

RefPtr<RenderNode> ContainerModalComponent::CreateRenderNode()
{
    return RenderContainerModal::Create();
}

RefPtr<Component> ContainerModalComponent::GetMaximizeRecoverButtonIcon() const
{
    if (!titleMaximizeRecoverButton_ || titleMaximizeRecoverButton_->GetChildren().empty()) {
        LOGE("tile maximize recover button is null");
        return nullptr;
    }
    return titleMaximizeRecoverButton_->GetChildren().front();
}

RefPtr<Component> ContainerModalComponent::BuildTitle()
{
    // build title box
    titleChildren_ = BuildTitleChildren();
    auto titleBox = AceType::MakeRefPtr<BoxComponent>();
    titleBox->SetHeight(CONTAINER_TITLE_HEIGHT);
    auto row = AceType::MakeRefPtr<RowComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, titleChildren_);

    // handle mouse move
    titleBox->SetOnMouseId([contextWptr = context_](MouseInfo& info) {
        auto context = contextWptr.Upgrade();
        if (context && info.GetButton() == MouseButton::LEFT_BUTTON && info.GetAction() == MouseAction::MOVE) {
            context->FireWindowStartMoveCallBack();
        }
    });

    // handle touch move
    titleBox->SetOnTouchMoveId([contextWptr = context_](const TouchEventInfo&) {
        auto context = contextWptr.Upgrade();
        if (context) {
            context->FireWindowStartMoveCallBack();
        }
    });
    titleBox->SetChild(row);
    auto display = AceType::MakeRefPtr<DisplayComponent>(titleBox);
    return display;
}

RefPtr<Component> ContainerModalComponent::BuildFloatingTitle()
{
    // build floating title box
    auto titleDecoration = AceType::MakeRefPtr<Decoration>();
    titleDecoration->SetBackgroundColor(CONTAINER_BACKGROUND_COLOR);

    auto titleBox = AceType::MakeRefPtr<BoxComponent>();
    titleBox->SetHeight(CONTAINER_TITLE_HEIGHT);
    titleBox->SetBackDecoration(titleDecoration);

    auto row = AceType::MakeRefPtr<RowComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, titleChildren_);
    titleBox->SetChild(row);
    auto tween = AceType::MakeRefPtr<TweenComponent>("ContainerModal", titleBox);
    return tween;
}

RefPtr<Component> ContainerModalComponent::BuildContent()
{
    auto contentBox = AceType::MakeRefPtr<BoxComponent>();
    contentBox->SetChild(GetChild());
    Border contentBorder;
    contentBorder.SetBorderRadius(Radius(CONTAINER_INNER_RADIUS));
    auto contentDecoration = AceType::MakeRefPtr<Decoration>();
    contentDecoration->SetBackgroundColor(CONTENT_BACKGROUND_COLOR);
    contentDecoration->SetBorder(contentBorder);
    contentBox->SetBackDecoration(contentDecoration);

    Edge margin;
    margin.SetLeft(CONTENT_MARGIN);
    margin.SetRight(CONTENT_MARGIN);
    contentBox->SetMargin(margin);

    // adaptive height
    contentBox->SetFlexWeight(1.0);
    return contentBox;
}

RefPtr<ButtonComponent> ContainerModalComponent::BuildControlButton(
    InternalResource::ResourceId icon, std::function<void()>&& clickCallback)
{
    auto image = AceType::MakeRefPtr<ImageComponent>(icon);
    image->SetWidth(TITLE_ICON_SIZE);
    image->SetHeight(TITLE_ICON_SIZE);
    std::list<RefPtr<Component>> btnChildren;
    btnChildren.emplace_back(image);

    auto button = AceType::MakeRefPtr<ButtonComponent>(btnChildren);
    button->SetWidth(TITLE_BUTTON_SIZE);
    button->SetHeight(TITLE_BUTTON_SIZE);
    button->SetType(ButtonType::CIRCLE);
    button->SetBackgroundColor(TITLE_BUTTON_BACKGROUND_COLOR);
    button->SetClickFunction(std::move(clickCallback));
    return button;
}

RefPtr<Component> ContainerModalComponent::SetPadding(
    const RefPtr<Component>& component, const Dimension& leftPadding, const Dimension& rightPadding)
{
    auto paddingComponent = AceType::MakeRefPtr<PaddingComponent>();
    paddingComponent->SetPaddingLeft(leftPadding);
    paddingComponent->SetPaddingRight(rightPadding);
    paddingComponent->SetPaddingTop((CONTAINER_TITLE_HEIGHT - TITLE_BUTTON_SIZE) / 2);
    paddingComponent->SetPaddingBottom((CONTAINER_TITLE_HEIGHT - TITLE_BUTTON_SIZE) / 2);
    paddingComponent->SetChild(component);
    return paddingComponent;
}

// Build ContainerModal FA structure
void ContainerModalComponent::BuildInnerChild()
{
    Border outerBorder;
    outerBorder.SetBorderRadius(Radius(CONTAINER_OUTER_RADIUS));
    outerBorder.SetColor(CONTAINER_BORDER_COLOR);
    outerBorder.SetWidth(CONTAINER_BORDER_WIDTH);
    auto containerDecoration = AceType::MakeRefPtr<Decoration>();
    containerDecoration->SetBackgroundColor(CONTAINER_BACKGROUND_COLOR);
    containerDecoration->SetBorder(outerBorder);

    auto column =
        AceType::MakeRefPtr<ColumnComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, std::list<RefPtr<Component>>());
    column->AppendChild(BuildTitle());
    column->AppendChild(BuildContent());
    std::list<RefPtr<Component>> stackChildren;
    stackChildren.emplace_back(column);
    stackChildren.emplace_back(BuildFloatingTitle());
    auto stackComponent = AceType::MakeRefPtr<StackComponent>(
        Alignment::TOP_LEFT, StackFit::INHERIT, Overflow::OBSERVABLE, stackChildren);

    auto containerBox = AceType::MakeRefPtr<BoxComponent>();
    containerBox->SetBackDecoration(containerDecoration);
    containerBox->SetFlex(BoxFlex::FLEX_X);
    containerBox->SetAlignment(Alignment::CENTER);

    // Use the bottom padding of the containerBox to replace the bottom margin of the contentBox.
    Edge padding;
    padding.SetBottom(CONTENT_MARGIN);
    containerBox->SetPadding(padding);
    containerBox->SetChild(stackComponent);
    SetChild(containerBox);
}

std::list<RefPtr<Component>> ContainerModalComponent::BuildTitleChildren()
{
    // title icon
    titleIcon_ = AceType::MakeRefPtr<ImageComponent>();
    titleIcon_->SetWidth(TITLE_ICON_SIZE);
    titleIcon_->SetHeight(TITLE_ICON_SIZE);

    // title text
    titleLabel_ = AceType::MakeRefPtr<TextComponent>("");
    TextStyle style;
    style.SetFontSize(TITLE_TEXT_FONT_SIZE);
    style.SetTextColor(TITLE_TEXT_COLOR);
    style.SetFontWeight(FontWeight::W500);
    style.SetAllowScale(false);
    titleLabel_->SetTextStyle(style);

    // title button
    auto contextWptr = context_;
    auto titleLeftSplitButton =
        BuildControlButton(InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT, [contextWptr]() {
            LOGI("left split button clicked");
            auto context = contextWptr.Upgrade();
            if (context) {
                context->FireWindowSplitCallBack();
            }
        });
    titleMaximizeRecoverButton_ =
        BuildControlButton(InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE, [contextWptr]() {
            auto context = contextWptr.Upgrade();
            if (context) {
                auto mode = context->FireWindowGetModeCallBack();
                if (mode == WindowMode::WINDOW_MODE_FULLSCREEN) {
                    LOGI("recover button clicked");
                    context->FireWindowRecoverCallBack();
                    context->ShowContainerTitle(true);
                } else {
                    LOGI("maximize button clicked");
                    context->FireWindowMaximizeCallBack();
                    context->ShowContainerTitle(false);
                }
            }
        });
    auto titleMinimizeButton =
        BuildControlButton(InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE, [contextWptr]() {
            auto context = contextWptr.Upgrade();
            if (context) {
                LOGI("minimize button clicked");
                context->FireWindowMinimizeCallBack();
            }
        });
    auto titleCloseButton =
        BuildControlButton(InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE, [contextWptr]() {
            auto context = contextWptr.Upgrade();
            if (context) {
                LOGI("close button clicked");
                context->FireWindowCloseCallBack();
            }
        });
    std::list<RefPtr<Component>> titleChildren;
    titleChildren.emplace_back(SetPadding(titleIcon_, TITLE_PADDING_START, TITLE_ELEMENT_MARGIN_HORIZONTAL));
    titleChildren.emplace_back(AceType::MakeRefPtr<FlexItemComponent>(1.0, 1.0, 0.0, titleLabel_));
    titleChildren.emplace_back(SetPadding(titleLeftSplitButton, ZERO_PADDING, TITLE_ELEMENT_MARGIN_HORIZONTAL));
    titleChildren.emplace_back(SetPadding(titleMaximizeRecoverButton_, ZERO_PADDING, TITLE_ELEMENT_MARGIN_HORIZONTAL));
    titleChildren.emplace_back(SetPadding(titleMinimizeButton, ZERO_PADDING, TITLE_ELEMENT_MARGIN_HORIZONTAL));
    titleChildren.emplace_back(SetPadding(titleCloseButton, ZERO_PADDING, TITLE_PADDING_END));
    return titleChildren;
}

} // namespace OHOS::Ace