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

#include "core/components/option/option_component.h"

#include "core/components/option/option_element.h"
#include "core/components/option/render_option.h"

namespace OHOS::Ace {
namespace {

constexpr uint32_t SELECT_OPTION_TEXT_LINES = 2;
constexpr double MIN_TEXT_SIZE_TV = 14.0;
constexpr double MIN_TEXT_SIZE_PHONE = 9.0;

} // namespace

OptionComponent::OptionComponent(const RefPtr<SelectTheme>& theme)
{
    if (theme) {
        theme_ = theme->clone();
        theme_->SetFontWeight(FontWeight::W400);
    }
}

void OptionComponent::InitTheme(const RefPtr<ThemeManager>& themeManager)
{
    if (!themeManager) {
        return;
    }
    auto selectTheme = themeManager->GetTheme<SelectTheme>();
    if (!selectTheme) {
        return;
    }
    theme_ = selectTheme->clone();
    theme_->SetFontWeight(FontWeight::W400);
}

bool OptionComponent::Initialize(const RefPtr<AccessibilityManager>& manager)
{
    if (customComponent_) {
        ClearChildren();
        AppendChild(customComponent_);
        return true;
    }

    if (!text_ || value_.empty()) {
        LOGW("can not initialize now, text null or value empty.");
        return false;
    }

    ClearChildren();

    if (icon_) {
        icon_->SetImageFit(ImageFit::SCALE_DOWN);
        icon_->SetAlignment((SystemProperties::GetDeviceType() == DeviceType::TV ?
            Alignment::CENTER : Alignment::CENTER_LEFT));
        icon_->SetWidth(24.0_vp); // icon is only for phone which is fixes size 24dp*24dp
        icon_->SetHeight(24.0_vp);
        AppendChild(icon_);
    }

    auto container = Container::Current();
    if (!container) {
        return false;
    }
    auto context = container->GetPipelineContext();
    if (!context) {
        return false;
    }
    TextStyle textStyle;
    if (context->GetIsDeclarative()) {
        if (GetSelected()) {
            textStyle = GetSelectedTextStyle();
            text_->SetTextStyle(textStyle);
        } else {
            textStyle = GetTextStyle();
            text_->SetTextStyle(textStyle);
        }
        textStyle.SetFontSize(GetFontSize());
        textStyle.SetTextDecoration(GetTextDecoration());
        text_->SetData(value_);
    } else {
        textStyle = text_->GetTextStyle();
        std::vector<std::string> fontFamilies;
        StringUtils::StringSplitter(GetFontFamily(), ',', fontFamilies);
        if (!fontFamilies.empty()) {
            textStyle.SetFontFamilies(fontFamilies);
        }
        textStyle.SetFontSize(GetFontSize());
        textStyle.SetFontWeight(GetFontWeight());
        textStyle.SetTextDecoration(GetTextDecoration());
        if (GetDisabled() && theme_) {
            textStyle.SetTextColor(theme_->GetFocusedTextDisableColor());
        } else if (GetSelected() && theme_) {
            textStyle.SetTextColor(theme_->GetSelectedColorText());
        } else {
            textStyle.SetTextColor(GetFontColor());
        }
    }
    textStyle.SetAllowScale(IsAllowScale());
    double minFontSize = (SystemProperties::GetDeviceType() == DeviceType::TV ?
        MIN_TEXT_SIZE_TV : MIN_TEXT_SIZE_PHONE);
    textStyle.SetAdaptTextSize(textStyle.GetFontSize(), Dimension(minFontSize, DimensionUnit::FP));
    if (SystemProperties::GetDeviceType() == DeviceType::TV) {
        textStyle.SetTextAlign(TextAlign::CENTER);
    } else if (GetTextDirection() == TextDirection::RTL) {
        textStyle.SetTextAlign(TextAlign::RIGHT);
    } else {
        textStyle.SetTextAlign(TextAlign::LEFT);
    }
    // use single line, do not change line.
    textStyle.SetMaxLines(SELECT_OPTION_TEXT_LINES);
    textStyle.SetTextOverflow(TextOverflow::ELLIPSIS);
    text_->SetTextStyle(textStyle);
    text_->SetFocusColor(textStyle.GetTextColor());
    AppendChild(text_);
    SetNode((!manager ? nullptr
                  : manager->CreateAccessibilityNode("option", StringUtils::StringToInt(GetId()), GetParentId(), -1)));
#if defined(PREVIEW)
    if (node_) {
        node_->SetAttr(GetAttr());
        node_->SetStyle(GetStyle());
    }
#endif
    return true;
}

void OptionComponent::CheckOptionModify()
{
    if (!text_) {
        LOGE("text is null of option component.");
        return;
    }
    if (!modifiedCallback_) {
        return;
    }
    if (text_->GetData() == lastText_) {
        return;
    }
    modifiedCallback_(GetIndex());
    lastText_ = text_->GetData();
}

RefPtr<RenderNode> OptionComponent::CreateRenderNode()
{
    return RenderOption::Create();
}

RefPtr<Element> OptionComponent::CreateElement()
{
    return AceType::MakeRefPtr<OptionElement>();
}

} // namespace OHOS::Ace
