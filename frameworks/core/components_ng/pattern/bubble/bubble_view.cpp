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
#include "core/components_ng/pattern/bubble/bubble_view.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {

constexpr Dimension DEFAULT_FONT_SIZE = 14.0_fp;
constexpr Dimension BUTTON_PADDING = 8.0_fp;
constexpr Dimension BUTTON_ZERO_PADDING = 0.0_fp;

} // namespace

RefPtr<FrameNode> BubbleView::CreateBubbleNode(
    const std::string& targetTag, int32_t targetId, const RefPtr<PopupParam>& param)
{
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto popupProp = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto popupPaintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    auto useCustom = param->IsUseCustom();

    // onstateChange.
    auto bubbleHub = popupNode->GetEventHub<BubbleEventHub>();
    if (bubbleHub) {
        bubbleHub->SetOnStateChange(param->GetOnStateChange());
    }

    auto message = param->GetMessage();
    auto primaryButton = param->GetPrimaryButtonProperties();
    auto secondaryButton = param->GetSecondaryButtonProperties();
    // Update props
    popupProp->UpdateUseCustom(useCustom);
    popupProp->UpdateEnableArrow(param->EnableArrow());
    popupProp->UpdatePlacement(param->GetPlacement());
    if (param->GetArrowOffset().has_value()) {
        popupPaintProp->UpdateArrowOffset(param->GetArrowOffset().value());
    }
    if (param->IsMaskColorSetted()) {
        popupPaintProp->UpdateMaskColor(param->GetMaskColor());
    }
    if (param->IsBackgroundColorSetted()) {
        popupPaintProp->UpdateBackgroundColor(param->GetBackgroundColor());
    }
    popupPaintProp->UpdateAutoCancel(!param->HasAction());
    popupPaintProp->UpdatePlacement(param->GetPlacement());

    // Create child
    RefPtr<FrameNode> child;
    if (useCustom) {
        LOGI("CreateBubbleNode, UseCustom");
    } else if (primaryButton.showButton || secondaryButton.showButton) {
        child = CreateCombinedChild(param, popupId, targetId);
        popupPaintProp->UpdateAutoCancel(false);
    } else {
        child = CreateMessage(message, useCustom);
    }
    // TODO: GridSystemManager is not completed, need to check later.
    child->MountToParent(popupNode);
    return popupNode;
}
RefPtr<FrameNode> BubbleView::CreateCustomBubbleNode(
    const std::string& targetTag, int32_t targetId, const RefPtr<UINode>& customNode, const RefPtr<PopupParam>& param)
{
    LOGD("customNode = %{public}p", AceType::RawPtr(customNode));
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto bubbleHub = popupNode->GetEventHub<BubbleEventHub>();
    if (bubbleHub) {
        bubbleHub->SetOnStateChange(param->GetOnStateChange());
    }
    // update bubble props
    auto layoutProps = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    layoutProps->UpdateUseCustom(param->IsUseCustom());
    layoutProps->UpdateEnableArrow(param->EnableArrow());
    layoutProps->UpdatePlacement(param->GetPlacement());
    auto popupPaintProps = popupNode->GetPaintProperty<BubbleRenderProperty>();
    popupPaintProps->UpdateUseCustom(param->IsUseCustom());
    popupPaintProps->UpdateEnableArrow(param->EnableArrow());
    if (param->GetArrowOffset().has_value()) {
        popupPaintProps->UpdateArrowOffset(param->GetArrowOffset().value());
    }
    if (param->IsMaskColorSetted()) {
        popupPaintProps->UpdateMaskColor(param->GetMaskColor());
    }
    if (param->IsBackgroundColorSetted()) {
        popupPaintProps->UpdateBackgroundColor(param->GetBackgroundColor());
    }
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    customNode->MountToParent(columnNode);
    auto renderContext = columnNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    }
    popupPaintProps->UpdateAutoCancel(!param->HasAction());
    popupPaintProps->UpdatePlacement(param->GetPlacement());
    columnNode->MountToParent(popupNode);
    return popupNode;
}

void BubbleView::UpdatePopupParam(int32_t popupId, const RefPtr<PopupParam>& param, const RefPtr<FrameNode>& targetNode)
{
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    auto popupProp = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto popupPaintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    auto message = param->GetMessage();
    auto primaryButton = param->GetPrimaryButtonProperties();
    auto secondaryButton = param->GetSecondaryButtonProperties();

    // Update layout props
    popupProp->UpdateUseCustom(param->IsUseCustom());
    popupProp->UpdateEnableArrow(param->EnableArrow());
    popupProp->UpdatePlacement(param->GetPlacement());
    // Update paint props
    if (param->GetArrowOffset().has_value()) {
        popupPaintProp->UpdateArrowOffset(param->GetArrowOffset().value());
    }
    if (param->IsMaskColorSetted()) {
        popupPaintProp->UpdateMaskColor(param->GetMaskColor());
    }
    if (param->IsBackgroundColorSetted()) {
        popupPaintProp->UpdateBackgroundColor(param->GetBackgroundColor());
    }
    popupPaintProp->UpdateAutoCancel(!param->HasAction());
    popupPaintProp->UpdatePlacement(param->GetPlacement());
    popupPaintProp->UpdateUseCustom(param->IsUseCustom());
}

RefPtr<FrameNode> BubbleView::CreateMessage(const std::string& message, bool IsUseCustom)
{
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateContent(message);
    layoutProperty->UpdateFontSize(DEFAULT_FONT_SIZE);
    if (IsUseCustom) {
        layoutProperty->UpdateTextColor(Color::BLACK);
    } else {
        layoutProperty->UpdateTextColor(Color::WHITE);
    }
    textNode->MarkModifyDone();
    return textNode;
}

RefPtr<FrameNode> BubbleView::CreateCombinedChild(const RefPtr<PopupParam>& param, int32_t popupId, int32_t targetId)
{
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto layoutProps = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    layoutProps->UpdateMainAxisAlign(FlexAlign::FLEX_START); // mainAxisAlign
    layoutProps->UpdateCrossAxisAlign(FlexAlign::FLEX_END);  // crossAxisAlign
    auto message = BubbleView::CreateMessage(param->GetMessage(), param->IsUseCustom());
    message->MountToParent(columnNode);
    auto buttonRow = BubbleView::CreateButtons(param, popupId, targetId);
    buttonRow->MountToParent(columnNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto popupTheme = themeManager->GetTheme<PopupTheme>();
    CHECK_NULL_RETURN(popupTheme, nullptr);
    auto padding = popupTheme->GetPadding();
    PaddingProperty columnPadding;
    columnPadding.left = CalcLength(padding.Left());
    columnPadding.right = CalcLength(padding.Right());
    columnPadding.top = CalcLength(padding.Top());
    columnPadding.bottom = CalcLength(padding.Bottom());
    layoutProps->UpdatePadding(columnPadding);

    columnNode->MarkModifyDone();
    return columnNode;
}

RefPtr<FrameNode> BubbleView::CreateButtons(const RefPtr<PopupParam>& param, int32_t popupId, int32_t targetId)
{
    auto rowId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, rowId, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto layoutProps = rowNode->GetLayoutProperty<LinearLayoutProperty>();
    layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
    auto primaryButtonProp = param->GetPrimaryButtonProperties();
    auto primaryButton = BubbleView::CreateButton(primaryButtonProp, popupId, targetId, param);
    if (primaryButton) {
        primaryButton->MountToParent(rowNode);
        primaryButton->MarkModifyDone();
    }
    auto secondaryButtonProp = param->GetSecondaryButtonProperties();
    auto secondaryButton = BubbleView::CreateButton(secondaryButtonProp, popupId, targetId, param);
    if (secondaryButton) {
        secondaryButton->MountToParent(rowNode);
        secondaryButton->MarkModifyDone();
    }

    rowNode->MarkModifyDone();
    return rowNode;
}

RefPtr<FrameNode> BubbleView::CreateButton(
    ButtonProperties& buttonParam, int32_t popupId, int32_t targetId, const RefPtr<PopupParam>& param)
{
    if (!buttonParam.showButton) {
        return nullptr;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto buttonTheme = pipelineContext->GetTheme<ButtonTheme>();
    CHECK_NULL_RETURN(buttonTheme, nullptr);
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, buttonId, AceType::MakeRefPtr<ButtonPattern>());
    auto buttonProp = AceType::DynamicCast<ButtonLayoutProperty>(buttonNode->GetLayoutProperty());
    auto isUseCustom = param->IsUseCustom();
    auto isShow = param->IsShow();
    auto buttonTextNode = BubbleView::CreateMessage(buttonParam.value, isUseCustom);
    buttonTextNode->MountToParent(buttonNode);

    PaddingProperty buttonPadding;
    buttonPadding.left = CalcLength(BUTTON_PADDING);
    buttonPadding.right = CalcLength(BUTTON_PADDING);
    buttonPadding.top = CalcLength(BUTTON_ZERO_PADDING);
    buttonPadding.bottom = CalcLength(BUTTON_ZERO_PADDING);
    buttonProp->UpdatePadding(buttonPadding);
    buttonProp->UpdateType(ButtonType::CAPSULE);
    buttonProp->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(buttonTheme->GetHeight())));
    auto renderContext = buttonNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    }

    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    buttonEventHub->AddClickEvent(buttonParam.action);
    auto popupNode = FrameNode::GetFrameNode(V2::POPUP_ETS_TAG, popupId);
    auto closeCallback = [popupNode, targetId, isShow](GestureEvent& /* info */) {
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineContext);
        auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
        CHECK_NULL_VOID(context);
        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto popupInfo = overlayManager->GetPopupInfo(targetId);
        popupInfo.markNeedUpdate = true;
        popupInfo.popupId = -1;
        popupInfo.markNeedUpdate = isShow;
        overlayManager->UpdatePopupNode(targetId, popupInfo);
    };
    buttonEventHub->AddClickEvent(AceType::MakeRefPtr<ClickEvent>(closeCallback));

    return buttonNode;
}

} // namespace OHOS::Ace::NG