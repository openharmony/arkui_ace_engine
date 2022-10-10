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

    column->AddChild(BuildTitle());
    BuildContent(content);
    column->AddChild(content);
    containerModalNode->AddChild(column);
    containerModalNode->AddChild(BuildTitle(true));

    CHECK_NULL_RETURN(column->GetLayoutProperty(), nullptr);
    column->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);

    // update container modal padding and border
    auto layoutProperty = containerModalNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
    PaddingProperty padding = { CalcLength(CONTENT_PADDING), CalcLength(CONTENT_PADDING), std::nullopt,
        CalcLength(CONTENT_PADDING) };
    layoutProperty->UpdatePadding(padding);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(CONTAINER_BORDER_WIDTH);
    layoutProperty->UpdateBorderWidth(borderWidth);

    auto renderContext = containerModalNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(CONTAINER_BACKGROUND_COLOR);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(CONTAINER_OUTER_RADIUS);
    renderContext->UpdateBorderRadius(borderRadius);
    BorderColorProperty borderColor;
    borderColor.SetColor(CONTAINER_BORDER_COLOR);
    renderContext->UpdateBorderColor(borderColor);

    return containerModalNode;
}

RefPtr<FrameNode> ContainerModalView::BuildTitle(bool isFloatingTitle)
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
    if (!isFloatingTitle) {
        // touch the title to move the floating window
        auto touchEventHub = containerTitleRow->GetOrCreateGestureEventHub();
        CHECK_NULL_RETURN(touchEventHub, nullptr);
        touchEventHub->SetTouchEvent([pipeline](TouchEventInfo& info) {
            if (pipeline) {
                pipeline->FireWindowStartMoveCallBack();
            }
        });

        // click the title to move the floating window with the mouse
        auto mouseEventHub = containerTitleRow->GetOrCreateInputEventHub();
        CHECK_NULL_RETURN(mouseEventHub, nullptr);
        mouseEventHub->SetMouseEvent([pipeline](MouseInfo& info) {
            if (pipeline && info.GetButton() == MouseButton::LEFT_BUTTON && info.GetAction() == MouseAction::PRESS) {
                pipeline->FireWindowStartMoveCallBack();
            }
        });
    }

    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, nullptr);

    // create title icon
    ImageSourceInfo imageSourceInfo;
    auto titleIcon = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ImagePattern>());
    imageSourceInfo.SetSrc(themeConstants->GetMediaPath(pipeline->GetAppIconId()));
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
    textLayoutProperty->UpdateContent(themeConstants->GetString(pipeline->GetAppLabelId()));
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
    containerTitleRow->AddChild(BuildControlButton(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT, [pipeline](GestureEvent& info) {
            if (pipeline) {
                LOGI("left split button clicked");
                pipeline->FireWindowSplitCallBack();
            }
        }));
    containerTitleRow->AddChild(BuildControlButton(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_RECOVER, [pipeline](GestureEvent& info) {
            if (pipeline) {
                auto mode = pipeline->FireWindowGetModeCallBack();
                if (mode == WindowMode::WINDOW_MODE_FULLSCREEN) {
                    LOGI("recover button clicked");
                    pipeline->FireWindowRecoverCallBack();
                } else {
                    LOGI("maximize button clicked");
                    pipeline->FireWindowMaximizeCallBack();
                }
            }
        }));
    containerTitleRow->AddChild(BuildControlButton(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE, [pipeline](GestureEvent& info) {
            if (pipeline) {
                LOGI("minimize button clicked");
                pipeline->FireWindowMinimizeCallBack();
            }
        }));
    containerTitleRow->AddChild(
        BuildControlButton(InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE, [pipeline](GestureEvent& info) {
            if (pipeline) {
                LOGI("close button clicked");
                pipeline->FireWindowCloseCallBack();
            }
        }));

    return containerTitleRow;
}

void ContainerModalView::BuildContent(RefPtr<FrameNode>& content)
{
    CHECK_NULL_VOID(content);
    auto layoutProperty = content->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateLayoutWeight(1.0f);

    auto renderContext = content->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(CONTAINER_INNER_RADIUS);
    renderContext->UpdateBorderRadius(borderRadius);
    renderContext->SetClipToBounds(true);
}

RefPtr<FrameNode> ContainerModalView::BuildControlButton(
    InternalResource::ResourceId icon, GestureEventFunc&& clickCallback)
{
    // button image icon
    ImageSourceInfo imageSourceInfo;
    auto imageIcon = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ImagePattern>());
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

    // TODO set click color
    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    buttonEventHub->SetClickEvent(std::move(clickCallback));

    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, nullptr);
    buttonLayoutProperty->UpdateType(ButtonType::CIRCLE);
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TITLE_BUTTON_SIZE), CalcLength(TITLE_BUTTON_SIZE)));

    MarginProperty margin;
    margin.right = CalcLength(TITLE_ELEMENT_MARGIN_HORIZONTAL);
    buttonLayoutProperty->UpdateMargin(margin);

    buttonNode->AddChild(imageIcon);
    return buttonNode;
}

} // namespace OHOS::Ace::NG
