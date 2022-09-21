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
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {

constexpr Dimension DEFAULT_FONT_SIZE = 14.0_fp;
constexpr Dimension BUTTON_PADDING = 8.0_fp;

} // namespace

RefPtr<FrameNode> BubbleView::CreateBubbleNode(
    const std::string& tag, int32_t targetId, const RefPtr<PopupParam>& param)
{
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, tag));
    auto popupProp = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto popupPaintProp = popupNode->GetPaintProperty<BubbleRenderProperty>();
    auto useCustom = param->IsUseCustom();
    auto enableArrow = param->EnableArrow();
    auto message = param->GetMessage();
    auto primaryButton = param->GetPrimaryButtonProperties();
    auto secondaryButton = param->GetSecondaryButtonProperties();
    // Update props
    popupProp->UpdateUseCustom(useCustom);
    popupProp->UpdateEnableArrow(enableArrow);
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
    // TODO: onstateChange.
    // Create child
    RefPtr<FrameNode> child;
    if (useCustom) {
        LOGE("usecustom");
    } else if (primaryButton.showButton || secondaryButton.showButton) {
        child = CreateCombinedChild(param);
        popupPaintProp->UpdateAutoCancel(false);
    } else {
        child = CreateMessage(message);
    }
    // TODO: GridSystemManager is not completed, need to check later.
    child->MountToParent(popupNode);
    return popupNode;
}

RefPtr<FrameNode> BubbleView::CreateMessage(const std::string& message)
{
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateContent(message);
    layoutProperty->UpdateFontSize(DEFAULT_FONT_SIZE);
    // TODO: color is not correct now
    layoutProperty->UpdateTextColor(Color::BLUE);
    return textNode;
}

RefPtr<FrameNode> BubbleView::CreateCombinedChild(const RefPtr<PopupParam>& param)
{
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto message = BubbleView::CreateMessage(param->GetMessage());
    message->MountToParent(columnNode);
    auto buttonColumn = BubbleView::CreateButtons(param);
    buttonColumn->MountToParent(columnNode);
    return columnNode;
}

RefPtr<FrameNode> BubbleView::CreateButtons(const RefPtr<PopupParam>& param)
{
    auto rowNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto message = BubbleView::CreateMessage(param->GetMessage());
    message->MountToParent(rowNode);
    auto primaryButtonProp = param->GetPrimaryButtonProperties();
    auto primaryButton = BubbleView::CreateButton(primaryButtonProp);
    if (primaryButton) {
        primaryButton->MountToParent(rowNode);
    }
    auto secondaryButtonProp = param->GetSecondaryButtonProperties();
    auto secondaryButton = BubbleView::CreateButton(secondaryButtonProp);
    if (secondaryButton) {
        secondaryButton->MountToParent(rowNode);
    }
    return rowNode;
}

RefPtr<FrameNode> BubbleView::CreateButton(ButtonProperties& param)
{
    if (!param.showButton) {
        return nullptr;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto buttonTheme = themeManager->GetTheme<ButtonTheme>();
    CHECK_NULL_RETURN(buttonTheme, nullptr);
    auto buttonNode = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    auto buttonProp = AceType::DynamicCast<ButtonLayoutProperty>(buttonNode->GetLayoutProperty());
    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    buttonEventHub->SetTouchEvent(std::move(param.touchFunc));
    buttonProp->UpdateType(ButtonType::CAPSULE);
    PaddingProperty padding;
    padding.left = CalcLength(BUTTON_PADDING);
    padding.right = CalcLength(BUTTON_PADDING);
    buttonProp->UpdatePadding(padding);
    buttonProp->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(buttonTheme->GetHeight())));
    auto renderContext = buttonNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    }
    return buttonNode;
}

} // namespace OHOS::Ace::NG