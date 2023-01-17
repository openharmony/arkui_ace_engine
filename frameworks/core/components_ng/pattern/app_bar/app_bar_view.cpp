/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/app_bar/app_bar_view.h"

#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {

const Dimension APP_BAR_HEIGHT = 56.0_vp;
const Dimension SHARE_IMAGE_SIZE = 24.0_vp;
const Dimension MARGIN_TEXT = -8.0_vp;
const Dimension MARGIN_BUTTON = 12.0_vp;
const Dimension DEFAULT_CORNER_RADIUS_S = 18.0_vp;
const Color COLOR_PRIMARY = Color(0xe5000000);
const Color CLICK_EFFECT_COLOR = Color(0x19000000);
const Color COLOR_APP_BAR_BG = Color(0xffffffff);
const std::string BUNDLE_NAME = "com.ohos.hag.famanager";
const std::string ABILITY_NAME = "FaPanelAbility";
const std::string FA_BUNDLE_NAME = "com.js.timer1.hmservice";
const std::string FA_ABILITY_NAME = "MainAbility";
const std::string FA_MODULE_NAME = "entry";
const std::string FA_HOST_PKG_NAME = "com.js.timer1.hmservice";

} // namespace

RefPtr<FrameNode> AppBarView::Create(RefPtr<FrameNode>& content)
{
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    column->AddChild(BuildBarTitle());
    column->AddChild(content);
    return column;
}

RefPtr<FrameNode> AppBarView::BuildBarTitle()
{
    auto appBarRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto layoutProperty = appBarRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(APP_BAR_HEIGHT)));
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    auto renderContext = appBarRow->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(COLOR_APP_BAR_BG);

    // create title label
    auto titleLabel = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = titleLabel->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, nullptr);

    textLayoutProperty->UpdateContent(themeConstants->GetString(pipeline->GetAppLabelId()));
    textLayoutProperty->UpdateMaxLines(2);
    textLayoutProperty->UpdateFontSize(Dimension(20, DimensionUnit::FP));
    textLayoutProperty->UpdateTextColor(COLOR_PRIMARY);
    textLayoutProperty->UpdateFontWeight(FontWeight::W500);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    textLayoutProperty->UpdateLayoutWeight(1.0f);

    MarginProperty margin;
    margin.left = CalcLength(MARGIN_TEXT);
    textLayoutProperty->UpdateMargin(margin);

    appBarRow->AddChild(
        BuildShareButton(InternalResource::ResourceId::APP_BAR_BACK_SVG, [pipeline](GestureEvent& info) {
            if (pipeline) {
                pipeline->CallRouterBackToPopPage();
            }
        }));
    appBarRow->AddChild(titleLabel);
    appBarRow->AddChild(BuildShareButton(InternalResource::ResourceId::APP_BAR_FA_SVG, [pipeline](GestureEvent& info) {
        if (pipeline) {
            pipeline->FireSharePanelCallback(
                FA_BUNDLE_NAME, FA_ABILITY_NAME, FA_MODULE_NAME, FA_HOST_PKG_NAME, BUNDLE_NAME, ABILITY_NAME);
        }
    }));

    return appBarRow;
}

RefPtr<FrameNode> AppBarView::BuildShareButton(InternalResource::ResourceId icon, GestureEventFunc&& clickCallback)
{
    // button image icon
    ImageSourceInfo imageSourceInfo;
    auto imageIcon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageFocus = imageIcon->GetFocusHub();
    if (imageFocus) {
        imageFocus->SetFocusable(false);
    }
    imageSourceInfo.SetResourceId(icon);
    auto imageLayoutProperty = imageIcon->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SHARE_IMAGE_SIZE), CalcLength(SHARE_IMAGE_SIZE)));
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageIcon->MarkModifyDone();

    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    auto buttonFocus = buttonNode->GetFocusHub();
    if (buttonFocus) {
        buttonFocus->SetFocusable(false);
    }
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(DEFAULT_CORNER_RADIUS_S);
    renderContext->UpdateBorderRadius(borderRadius);
    renderContext->SetClipToBounds(true);

    auto buttonPattern = AceType::DynamicCast<ButtonPattern>(buttonNode->GetPattern());
    CHECK_NULL_RETURN(buttonPattern, nullptr);
    buttonPattern->SetClickedColor(CLICK_EFFECT_COLOR);

    auto buttonEventHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    buttonEventHub->AddClickEvent(clickEvent);

    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, nullptr);
    buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SHARE_IMAGE_SIZE * 2), CalcLength(SHARE_IMAGE_SIZE * 2)));
    MarginProperty margin;
    margin.left = CalcLength(MARGIN_BUTTON);
    margin.right = CalcLength(MARGIN_BUTTON);
    buttonLayoutProperty->UpdateMargin(margin);
    buttonNode->MarkModifyDone();

    buttonNode->AddChild(imageIcon);
    return buttonNode;
}

} // namespace OHOS::Ace::NG
