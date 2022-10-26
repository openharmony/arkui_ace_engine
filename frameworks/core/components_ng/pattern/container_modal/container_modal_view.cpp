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

#include "core/components_ng/pattern/container_modal/container_modal_view.h"

#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

/**
 * The structure of container_modal is designed as follows :
 * |--container_modal(stack)
 *   |--column
 *      |--container_modal_title(row)
 *          |--icon(image), label(text), [leftSplit, maxRecover, minimize, close](button)
 *      |--container_modal_content(stage)
 *          |--page
 *   |--container_modal_floating_title(row)
 *          |--icon(image), label(text), [leftSplit, maxRecover, minimize, close](button)
 */

RefPtr<FrameNode> ContainerModalView::Create(RefPtr<FrameNode>& content)
{
    auto containerModalNode = FrameNode::CreateFrameNode(
        "ContainerModal", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPattern>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));

    column->AddChild(BuildTitle(containerModalNode));
    column->AddChild(content);
    containerModalNode->AddChild(column);
    containerModalNode->AddChild(BuildTitle(containerModalNode, true));

    CHECK_NULL_RETURN(column->GetLayoutProperty(), nullptr);
    column->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    auto containerPattern = containerModalNode->GetPattern<ContainerModalPattern>();
    CHECK_NULL_RETURN(containerPattern, nullptr);
    containerModalNode->MarkModifyDone();
    containerPattern->InitContainerEvent();

    return containerModalNode;
}

RefPtr<FrameNode> ContainerModalView::BuildTitle(RefPtr<FrameNode>& containerNode, bool isFloatingTitle)
{
    auto containerTitleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto layoutProperty = containerTitleRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(CONTAINER_TITLE_HEIGHT)));
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    if (isFloatingTitle) {
        auto renderContext = containerTitleRow->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, nullptr);
        renderContext->UpdateBackgroundColor(CONTAINER_BACKGROUND_COLOR);
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    if (!isFloatingTitle) {
        // touch the title to move the floating window
        auto touchEventHub = containerTitleRow->GetOrCreateGestureEventHub();
        CHECK_NULL_RETURN(touchEventHub, nullptr);
        touchEventHub->SetTouchEvent([windowManager](TouchEventInfo& info) {
            if (windowManager) {
                windowManager->WindowStartMove();
            }
        });

        // click the title to move the floating window with the mouse
        auto mouseEventHub = containerTitleRow->GetOrCreateInputEventHub();
        CHECK_NULL_RETURN(mouseEventHub, nullptr);
        mouseEventHub->SetMouseEvent([windowManager](MouseInfo& info) {
            if (windowManager && info.GetButton() == MouseButton::LEFT_BUTTON &&
                info.GetAction() == MouseAction::PRESS) {
                windowManager->WindowStartMove();
            }
        });
    }

    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, nullptr);

    // create title icon
    ImageSourceInfo imageSourceInfo;
    auto titleIcon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    imageSourceInfo.SetSrc(themeConstants->GetMediaPath(pipeline->GetWindowManager()->GetAppIconId()));
    auto imageLayoutProperty = titleIcon->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(TITLE_ICON_SIZE), CalcLength(TITLE_ICON_SIZE)));
    MarginProperty margin = { CalcLength(TITLE_PADDING_START), CalcLength(TITLE_ELEMENT_MARGIN_HORIZONTAL) };
    imageLayoutProperty->UpdateMargin(margin);
    titleIcon->MarkModifyDone();

    // create title label
    auto titleLabel = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = titleLabel->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(themeConstants->GetString(pipeline->GetWindowManager()->GetAppLabelId()));
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateFontSize(TITLE_TEXT_FONT_SIZE);
    textLayoutProperty->UpdateTextColor(TITLE_TEXT_COLOR);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateFontWeight(FontWeight::W500);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    textLayoutProperty->UpdateLayoutWeight(1.0f);

    // add icon and label
    containerTitleRow->AddChild(titleIcon);
    containerTitleRow->AddChild(titleLabel);

    // add leftSplit / maxRecover / minimize / close button
    containerTitleRow->AddChild(BuildControlButton(InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT,
        [windowManager](GestureEvent& info) {
            if (windowManager) {
                LOGI("left split button clicked");
                windowManager->FireWindowSplitCallBack();
            }
        }));
    containerTitleRow->AddChild(BuildControlButton(InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE,
        [windowManager](GestureEvent& info) {
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
        }));
    containerTitleRow->AddChild(BuildControlButton(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE, [windowManager](GestureEvent& info) {
            if (windowManager) {
                LOGI("minimize button clicked");
                windowManager->WindowMinimize();
            }
        }));
    containerTitleRow->AddChild(BuildControlButton(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE, [windowManager](GestureEvent& info) {
            if (windowManager) {
                LOGI("close button clicked");
                windowManager->WindowClose();
            }
        }, true));

    return containerTitleRow;
}

RefPtr<FrameNode> ContainerModalView::BuildControlButton(
    InternalResource::ResourceId icon, GestureEventFunc&& clickCallback, bool isCloseButton)
{
    // button image icon
    ImageSourceInfo imageSourceInfo;
    auto imageIcon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    imageSourceInfo.SetResourceId(icon);
    auto imageLayoutProperty = imageIcon->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(TITLE_ICON_SIZE), CalcLength(TITLE_ICON_SIZE)));
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageIcon->MarkModifyDone();

    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(TITLE_BUTTON_BACKGROUND_COLOR);

    auto buttonPattern = AceType::DynamicCast<ButtonPattern>(buttonNode->GetPattern());
    CHECK_NULL_RETURN(buttonPattern, nullptr);
    buttonPattern->SetClickedColor(TITLE_BUTTON_CLICKED_COLOR);

    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    buttonEventHub->AddClickEvent(clickEvent);

    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, nullptr);
    buttonLayoutProperty->UpdateType(ButtonType::CIRCLE);
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TITLE_BUTTON_SIZE), CalcLength(TITLE_BUTTON_SIZE)));

    MarginProperty margin;
    margin.right = CalcLength(isCloseButton ? TITLE_PADDING_END : TITLE_ELEMENT_MARGIN_HORIZONTAL);
    buttonLayoutProperty->UpdateMargin(margin);
    buttonNode->MarkModifyDone();

    buttonNode->AddChild(imageIcon);
    return buttonNode;
}

} // namespace OHOS::Ace::NG
