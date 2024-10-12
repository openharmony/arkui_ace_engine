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

#include "core/components/container_modal/container_modal_component.h"

#include "core/components/clip/clip_component.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/container_modal/container_modal_element.h"
#include "core/components/container_modal/render_container_modal.h"
#include "core/components/padding/padding_component.h"
#include "core/components/tween/tween_component.h"
#include "core/components_v2/inspector/inspector_composed_component.h"
#include "core/gestures/pan_gesture.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t ROOT_DECOR_BASE = 3100000;
constexpr int32_t TITLE_ROW = ROOT_DECOR_BASE;
constexpr int32_t FLOATING_TITLE_ROW = ROOT_DECOR_BASE + 1;
constexpr int32_t TITLE_LABEL = ROOT_DECOR_BASE + 2;
constexpr int32_t FLOATING_TITLE_LABEL = ROOT_DECOR_BASE + 3;
constexpr int32_t WINDOW_SPLIT_BUTTON = ROOT_DECOR_BASE + 4;
constexpr int32_t WINDOW_MAX_RECOVER_BUTTON = ROOT_DECOR_BASE + 6;
constexpr int32_t WINDOW_MINIMIZE_BUTTON = ROOT_DECOR_BASE + 8;
constexpr int32_t WINDOW_CLOSE_BUTTON = ROOT_DECOR_BASE + 10;
constexpr int32_t WINDOW_BUTTON_INVALID = ROOT_DECOR_BASE + 12;

const std::string SPLIT_LEFT_KEY = "container_modal_split_left_button";
const std::string MAXIMIZE_KEY = "container_modal_maximize_button";
const std::string MINIMIZE_KEY = "container_modal_minimize_button";
const std::string CLOSE_KEY = "container_modal_close_button";
}  // namespace

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

RefPtr<Component> ContainerModalComponent::BuildTitle()
{
    // build title box
    auto titleBox = AceType::MakeRefPtr<BoxComponent>();
    titleBox->SetHeight(CONTAINER_TITLE_HEIGHT);

    // BuildTitleChildren need this
    CreateAccessibilityNode(DOM_FLEX_ROW, TITLE_ROW, -1);

    auto titleChildrenRow =
        AceType::MakeRefPtr<RowComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, BuildTitleChildren(false));

    // handle touch move and mouse move
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    auto panGesture =
        AceType::MakeRefPtr<PanGesture>(DEFAULT_PAN_FINGER, panDirection, DEFAULT_PAN_DISTANCE.ConvertToPx());
    panGesture->SetOnActionStartId([contextWptr = context_](const GestureEvent&) {
        auto context = contextWptr.Upgrade();
        if (context) {
            LOGI("container window start move.");
            context->GetWindowManager()->WindowStartMove();
        }
    });
    titleBox->AddGesture(GesturePriority::Low, panGesture);
    titleBox->SetChild(titleChildrenRow);

    if (isDeclarative_) {
        return AceType::MakeRefPtr<DisplayComponent>(AceType::MakeRefPtr<V2::InspectorComposedComponent>(
            V2::InspectorComposedComponent::GenerateId(), V2::ROW_COMPONENT_TAG, titleBox));
    } else {
        return AceType::MakeRefPtr<DisplayComponent>(
            AceType::MakeRefPtr<ComposedComponent>(std::to_string(TITLE_ROW), DOM_FLEX_ROW, titleBox));
    }
}

RefPtr<Component> ContainerModalComponent::BuildFloatingTitle()
{
    // build floating title box
    auto titleDecoration = AceType::MakeRefPtr<Decoration>();
    titleDecoration->SetBackgroundColor(CONTAINER_BACKGROUND_COLOR);

    auto titleBox = AceType::MakeRefPtr<BoxComponent>();
    titleBox->SetHeight(CONTAINER_TITLE_HEIGHT);
    titleBox->SetBackDecoration(titleDecoration);

    CreateAccessibilityNode(DOM_FLEX_ROW, FLOATING_TITLE_ROW, -1);

    auto floatingTitleChildrenRow =
        AceType::MakeRefPtr<RowComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, BuildTitleChildren(true));
    titleBox->SetChild(floatingTitleChildrenRow);
    if (isDeclarative_) {
        return AceType::MakeRefPtr<TweenComponent>(
            "ContainerModal", AceType::MakeRefPtr<V2::InspectorComposedComponent>(
                                  V2::InspectorComposedComponent::GenerateId(), V2::ROW_COMPONENT_TAG, titleBox));
    } else {
        return AceType::MakeRefPtr<TweenComponent>("ContainerModal",
            AceType::MakeRefPtr<ComposedComponent>(std::to_string(FLOATING_TITLE_ROW), DOM_FLEX_ROW, titleBox));
    }
}

RefPtr<Component> ContainerModalComponent::BuildContent()
{
    auto contentBox = AceType::MakeRefPtr<BoxComponent>();
    contentBox->SetChild(GetChild());
    auto contentDecoration = AceType::MakeRefPtr<Decoration>();
    auto context = context_.Upgrade();
    if (context) {
        contentDecoration->SetBackgroundColor(context->GetAppBgColor());
    }
    contentBox->SetBackDecoration(contentDecoration);

    auto clip = AceType::MakeRefPtr<ClipComponent>(contentBox);
    clip->SetFlexWeight(1.0);
    return clip;
}

RefPtr<Component> ContainerModalComponent::BuildControlButton(
    InternalResource::ResourceId icon, std::function<void()>&& clickCallback, bool isFocus, bool isFloating)
{
    static std::unordered_map<InternalResource::ResourceId, std::pair<int32_t, std::string>> controlButtonIdMap = {
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT, { WINDOW_SPLIT_BUTTON, SPLIT_LEFT_KEY } },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_SPLIT_LEFT,
            { WINDOW_SPLIT_BUTTON, SPLIT_LEFT_KEY } },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_RECOVER, { WINDOW_MAX_RECOVER_BUTTON, MAXIMIZE_KEY } },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE, { WINDOW_MAX_RECOVER_BUTTON, MAXIMIZE_KEY } },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_RECOVER,
            { WINDOW_MAX_RECOVER_BUTTON, MAXIMIZE_KEY } },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MAXIMIZE,
            { WINDOW_MAX_RECOVER_BUTTON, MAXIMIZE_KEY } },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE, { WINDOW_MINIMIZE_BUTTON, MINIMIZE_KEY } },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MINIMIZE,
            { WINDOW_MINIMIZE_BUTTON, MINIMIZE_KEY } },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE, { WINDOW_CLOSE_BUTTON, CLOSE_KEY } },
        { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_CLOSE, { WINDOW_CLOSE_BUTTON, CLOSE_KEY } },
    };

    auto image = AceType::MakeRefPtr<ImageComponent>(icon);
    image->SetWidth(TITLE_ICON_SIZE);
    image->SetHeight(TITLE_ICON_SIZE);
    image->SetFocusable(false);
    std::list<RefPtr<Component>> btnChildren;
    btnChildren.emplace_back(image);

    auto button = AceType::MakeRefPtr<ButtonComponent>(btnChildren);
    button->SetWidth(TITLE_BUTTON_SIZE);
    button->SetHeight(TITLE_BUTTON_SIZE);
    button->SetType(ButtonType::CIRCLE);
    button->SetBackgroundColor(isFocus ? TITLE_BUTTON_BACKGROUND_COLOR : TITLE_BUTTON_BACKGROUND_COLOR_LOST_FOCUS);
    button->SetClickedColor(TITLE_BUTTON_CLICKED_COLOR);
    button->SetClickFunction(std::move(clickCallback));
    button->SetFocusable(false);
    std::string buttonKey = "";
    auto iter = controlButtonIdMap.find(icon);
    if (iter != controlButtonIdMap.end()) {
        buttonKey = (iter->second).second;
    }
    button->SetInspectorKey(buttonKey.c_str());
    if (!isDeclarative_) {
        auto buttonId = WINDOW_BUTTON_INVALID;
        auto iter = controlButtonIdMap.find(icon);
        if (iter != controlButtonIdMap.end()) {
            buttonId = isFloating ? (iter->second).first + 1 : (iter->second).first;
        }
        CreateAccessibilityNode(DOM_NODE_TAG_BUTTON, buttonId, isFloating ? FLOATING_TITLE_ROW : TITLE_ROW);
        return AceType::MakeRefPtr<ComposedComponent>(std::to_string(buttonId), DOM_NODE_TAG_BUTTON, button);
    } else {
        return AceType::MakeRefPtr<V2::InspectorComposedComponent>(
            V2::InspectorComposedComponent::GenerateId(), V2::BUTTON_COMPONENT_TAG, button);
    }
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

    Edge padding = Edge(CONTENT_PADDING, Dimension(0.0), CONTENT_PADDING, CONTENT_PADDING);
    containerBox->SetPadding(padding);
    containerBox->SetChild(stackComponent);
    SetChild(containerBox);
}

std::list<RefPtr<Component>> ContainerModalComponent::BuildTitleChildren(bool isFloating, bool isFocus,
    bool isFullWindow)
{
    // title icon
    if (!titleIcon_) {
        titleIcon_ = AceType::MakeRefPtr<ImageComponent>();
        titleIcon_->SetWidth(TITLE_ICON_SIZE);
        titleIcon_->SetHeight(TITLE_ICON_SIZE);
        titleIcon_->SetFocusable(false);
    }

    // title text
    if (!titleLabel_) {
        titleLabel_ = AceType::MakeRefPtr<TextComponent>("");
    }
    TextStyle style;
    style.SetFontSize(TITLE_TEXT_FONT_SIZE);
    style.SetMaxLines(1);
    style.SetTextColor(isFocus ? TITLE_TEXT_COLOR : TITLE_TEXT_COLOR_LOST_FOCUS);
    style.SetFontWeight(FontWeight::W500);
    style.SetAllowScale(false);
    style.SetTextOverflow(TextOverflow::ELLIPSIS);
    titleLabel_->SetTextStyle(style);
    titleLabel_->SetFlexWeight(1.0);

    CreateAccessibilityNode(DOM_NODE_TAG_TEXT, isFloating ? FLOATING_TITLE_LABEL : TITLE_LABEL,
        isFloating ? FLOATING_TITLE_ROW : TITLE_ROW);

    // title control button
    auto windowManager = context_.Upgrade()->GetWindowManager();
    auto leftSplitButton = isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT
                                   : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_SPLIT_LEFT;
    auto titleLeftSplitButton = BuildControlButton(leftSplitButton, [windowManager]() {
            if (windowManager) {
                LOGI("left split button clicked");
                windowManager->FireWindowSplitCallBack();
            }
        }, isFocus, isFloating);
    auto maxRecoverButton = isFloating && isFullWindow ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_RECOVER
                                                       : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE;
    if (!isFocus) {
        maxRecoverButton = isFloating && isFullWindow ?
            InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_RECOVER :
            InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MAXIMIZE;
    }
    auto titleMaximizeRecoverButton = BuildControlButton(maxRecoverButton, [windowManager]() {
            if (windowManager) {
                auto mode = windowManager->GetWindowMode();
                if (mode == WindowMode::WINDOW_MODE_FULLSCREEN) {
                    LOGI("recover button clicked");
                    windowManager->WindowRecover();
                } else {
                    LOGI("maximize button clicked");
                    windowManager->WindowMaximize();
                }
            }
        }, isFocus, isFloating);
    auto minimizeButton = isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE
                                  : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MINIMIZE;
    auto titleMinimizeButton = BuildControlButton(minimizeButton, [windowManager]() {
            if (windowManager) {
                LOGI("minimize button clicked");
                windowManager->WindowMinimize();
            }
        }, isFocus, isFloating);
    auto closeButton = isFocus ? InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE
                               : InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_CLOSE;
    auto titleCloseButton = BuildControlButton(closeButton, [windowManager]() {
            if (windowManager) {
                LOGI("close button clicked");
                windowManager->WindowClose();
            }
        }, isFocus, isFloating);
    std::list<RefPtr<Component>> titleChildren;
    titleChildren.emplace_back(SetPadding(titleIcon_, TITLE_PADDING_START, TITLE_ELEMENT_MARGIN_HORIZONTAL));
    if (isDeclarative_) {
        auto inspectorTitle = AceType::MakeRefPtr<V2::InspectorComposedComponent>(
            V2::InspectorComposedComponent::GenerateId(), V2::TEXT_COMPONENT_TAG, titleLabel_);
        inspectorTitle->MarkNeedUpdate();
        titleChildren.emplace_back(inspectorTitle);
    } else {
        titleChildren.emplace_back(AceType::MakeRefPtr<ComposedComponent>(
            isFloating ? std::to_string(FLOATING_TITLE_LABEL) : std::to_string(TITLE_LABEL), DOM_NODE_TAG_TEXT,
            titleLabel_));
    }
    auto rightPadding = SystemProperties::GetDeviceAccess() ? TITLE_ELEMENT_MARGIN_HORIZONTAL_ACCESS_DEVICE
                                                            : TITLE_ELEMENT_MARGIN_HORIZONTAL;
    if (!hideSplit_) {
        titleChildren.emplace_back(SetPadding(titleLeftSplitButton, ZERO_PADDING, rightPadding));
    }
    if (!hideMaximize_) {
        titleChildren.emplace_back(
            SetPadding(titleMaximizeRecoverButton, ZERO_PADDING, rightPadding));
    }
    if (!hideMinimize_) {
        titleChildren.emplace_back(SetPadding(titleMinimizeButton, ZERO_PADDING, rightPadding));
    }
    if (!hideClose_) {
        titleChildren.emplace_back(SetPadding(titleCloseButton, ZERO_PADDING, TITLE_PADDING_END));
    }
    return titleChildren;
}

void ContainerModalComponent::CreateAccessibilityNode(const std::string& tag, int32_t nodeId, int32_t parentNodeId)
{
    auto context = context_.Upgrade();
    if (context != nullptr && !isDeclarative_) {
        auto accessibilityManager = context->GetAccessibilityManager();
        if (accessibilityManager) {
            accessibilityManager->CreateAccessibilityNode(tag, nodeId, parentNodeId, -1);
        }
    }
}

} // namespace OHOS::Ace