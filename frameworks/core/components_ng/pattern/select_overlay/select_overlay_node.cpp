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

#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"

#include <cstdint>
#include <functional>
#include <optional>

#include "base/geometry/dimension.h"
#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/property.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

constexpr char BUTTON_COPY_ALL[] = "textoverlay.select_all";
constexpr char BUTTON_CUT[] = "textoverlay.cut";
constexpr char BUTTON_COPY[] = "textoverlay.copy";
constexpr char BUTTON_PASTE[] = "textoverlay.paste";

RefPtr<FrameNode> BuildButton(const std::string& data, const std::function<void()>& callback, int32_t overlayId)
{
    auto button = FrameNode::GetOrCreateFrameNode("SelectMenuButton", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto text = FrameNode::GetOrCreateFrameNode("SelectMenuButtonText", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = text->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(data);
    text->MountToParent(button);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, button);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(textOverlayTheme, button);
    auto textStyle = textOverlayTheme->GetMenuButtonTextStyle();
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(textStyle.GetTextColor());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
    text->MarkModifyDone();

    auto buttonLayoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    const auto& padding = textOverlayTheme->GetMenuButtonPadding();
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    buttonLayoutProperty->UpdatePadding({ left, right, top, bottom });
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        { std::nullopt, CalcLength(textOverlayTheme->GetMenuButtonHeight()) });
    button->GetRenderContext()->UpdateBackgroundColor(textOverlayTheme->GetMenuBackgroundColor());

    button->GetOrCreateGestureEventHub()->SetClickEvent([callback, overlayId](GestureEvent& /*info*/) {
        if (callback) {
            callback();
        }
        // close text overlay.
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetSelectOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DestroySelectOverlay(overlayId);
    });
    button->MarkModifyDone();
    return button;
}

} // namespace

SelectOverlayNode::SelectOverlayNode(const std::shared_ptr<SelectOverlayInfo>& info)
    : FrameNode("SelectOverlay", ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<SelectOverlayPattern>(info))
{}

RefPtr<SelectOverlayNode> SelectOverlayNode::CreateSelectOverlayNode(const std::shared_ptr<SelectOverlayInfo>& info)
{
    auto selectOverlayNode = AceType::MakeRefPtr<SelectOverlayNode>(info);
    selectOverlayNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(selectOverlayNode);
    selectOverlayNode->CreateToolBar();
    selectOverlayNode->UpdateToolBar(true);
    return selectOverlayNode;
}

void SelectOverlayNode::CreateToolBar()
{
    auto info = GetPattern<SelectOverlayPattern>()->GetSelectOverlayInfo();
    selectMenu_ = FrameNode::GetOrCreateFrameNode("SelectMenu", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    selectMenu_->GetLayoutProperty<LinearLayoutProperty>()->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    selectMenu_->GetRenderContext()->UpdateBackgroundColor(textOverlayTheme->GetMenuBackgroundColor());

    const auto& border = textOverlayTheme->GetMenuBorder();
    auto borderWidth = Dimension(border.Left().GetWidth().ConvertToPx());
    selectMenu_->GetLayoutProperty()->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth });
    auto borderRadius = textOverlayTheme->GetMenuToolbarHeight() / 2.0f;
    selectMenu_->GetRenderContext()->UpdateBorderRadius({ borderRadius, borderRadius, borderRadius, borderRadius });
    auto borderColor = border.Left().GetColor();
    selectMenu_->GetRenderContext()->UpdateBorderColor({ borderColor, borderColor, borderColor, borderColor });
    auto borderStyle = border.Left().GetBorderStyle();
    selectMenu_->GetRenderContext()->UpdateBorderStyle({ borderStyle, borderStyle, borderStyle, borderStyle });

    const auto& padding = textOverlayTheme->GetMenuPadding();
    auto left = CalcLength(padding.Left().ConvertToPx());
    auto right = CalcLength(padding.Right().ConvertToPx());
    auto top = CalcLength(padding.Top().ConvertToPx());
    auto bottom = CalcLength(padding.Bottom().ConvertToPx());
    selectMenu_->GetLayoutProperty()->UpdatePadding({ left, right, top, bottom });

    selectMenu_->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        { std::nullopt, CalcLength(textOverlayTheme->GetMenuToolbarHeight()) });

    if (info->menuInfo.menuIsShow) {
        selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    } else {
        selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    }
    selectMenu_->GetRenderContext()->UpdateBackShadow(ShadowConfig::DefaultShadowM);
    selectMenu_->MountToParent(Claim(this));
    selectMenu_->GetOrCreateGestureEventHub()->MarkResponseRegion(true);
    selectMenu_->MarkModifyDone();
}

void SelectOverlayNode::UpdateToolBar(bool menuItemChanged)
{
    auto info = GetPattern<SelectOverlayPattern>()->GetSelectOverlayInfo();
    if (menuItemChanged) {
        selectMenu_->Clean();
        if (info->menuInfo.showCopy) {
            auto button = BuildButton(
                Localization::GetInstance()->GetEntryLetters(BUTTON_COPY), info->menuCallback.onCopy, GetId());
            button->MountToParent(selectMenu_);
        }
        if (info->menuInfo.showCopyAll) {
            auto button = BuildButton(
                Localization::GetInstance()->GetEntryLetters(BUTTON_COPY_ALL), info->menuCallback.onSelectAll, GetId());
            button->MountToParent(selectMenu_);
        }
        if (info->menuInfo.showCut) {
            auto button = BuildButton(
                Localization::GetInstance()->GetEntryLetters(BUTTON_CUT), info->menuCallback.onCut, GetId());
            button->MountToParent(selectMenu_);
        }
        if (info->menuInfo.showPaste) {
            auto button = BuildButton(
                Localization::GetInstance()->GetEntryLetters(BUTTON_PASTE), info->menuCallback.onPaste, GetId());
            button->MountToParent(selectMenu_);
        }
    }
    if (info->menuInfo.menuDisable) {
        selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    } else if (info->menuInfo.menuIsShow) {
        selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    } else {
        selectMenu_->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    }
    selectMenu_->MarkModifyDone();
    MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

} // namespace OHOS::Ace::NG