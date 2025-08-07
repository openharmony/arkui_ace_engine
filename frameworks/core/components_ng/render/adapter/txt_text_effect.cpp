/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/txt_text_effect.h"

#include <utility>

#include "text_effect.h"
#include "ui/base/utils/utils.h"

#include "base/utils/utf_helper.h"
#include "core/components/font/constants_converter.h"
#include "core/components_ng/render/adapter/txt_paragraph.h"

namespace OHOS::Ace::NG {
RefPtr<TextEffect> TextEffect::CreateTextEffect()
{
    return AceType::MakeRefPtr<TxtTextEffect>();
}

TxtTextEffect::TxtTextEffect()
{
#if !defined(PREVIEW)
    RSTextEffectFactoryCreator& creator = RSTextEffectFactoryCreator::GetInstance();
    textEffect_ = creator.CreateTextEffect(Rosen::TextEffectStrategy::FLIP);
#endif
}

int TxtTextEffect::UpdateEffectConfig(TextFlipDirection direction, bool enableBlur)
{
    CHECK_NULL_RETURN(textEffect_, -1);
    if (direction_ && direction_.value() == direction && enableBlur == enableBlur_) {
        return 0;
    }
    direction_ = direction;
    enableBlur_ = enableBlur;
    std::unordered_map<Rosen::TextEffectAttribute, std::string> txtConfig;
    txtConfig[Rosen::TextEffectAttribute::FLIP_DIRECTION] = StringUtils::ToString(direction);
    txtConfig[Rosen::TextEffectAttribute::BLUR_ENABLE] = enableBlur ? "true" : "false";
    return textEffect_->UpdateEffectConfig(txtConfig);
}

int TxtTextEffect::AppendTypography(const std::vector<RefPtr<Paragraph>>& paragraphs)
{
    CHECK_NULL_RETURN(textEffect_, -1);
    std::vector<Rosen::TypographyConfig> typographyConfigs;
    for (const auto& paragrah : paragraphs) {
        CHECK_NULL_RETURN(paragrah, -1);
        auto txtParagraph = DynamicCast<TxtParagraph>(paragrah);
        CHECK_NULL_RETURN(txtParagraph, -1);
        Rosen::TypographyConfig config;
        config.typography = txtParagraph->GetSharedParagraph();
        config.rawTextRange = std::pair(0, txtParagraph->GetParagraphText().size());
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE("TxtTextEffect::AppendTypography value:%s first:%d second:%d",
                UtfUtils::Str16DebugToStr8(txtParagraph->GetParagraphText()).c_str(),
                static_cast<int32_t>(config.rawTextRange.first), static_cast<int32_t>(config.rawTextRange.second));
        }
        typographyConfigs.emplace_back(config);
    }
    return textEffect_->AppendTypography(typographyConfigs);
}

void TxtTextEffect::RemoveTypography(const std::vector<RefPtr<Paragraph>>& paragraphs)
{
    CHECK_NULL_VOID(textEffect_);
    std::vector<Rosen::TypographyConfig> typographyConfigs;
    for (const auto& paragrah : paragraphs) {
        CHECK_NULL_VOID(paragrah);
        auto txtParagraph = DynamicCast<TxtParagraph>(paragrah);
        CHECK_NULL_VOID(txtParagraph);
        Rosen::TypographyConfig config;
        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE("TxtTextEffect::RemoveTypography value:%s ",
                UtfUtils::Str16DebugToStr8(txtParagraph->GetParagraphText()).c_str());
        }
        config.typography = txtParagraph->GetSharedParagraph();
        config.rawTextRange = std::pair(0, txtParagraph->GetParagraphText().size());
        typographyConfigs.emplace_back(config);
    }
    return textEffect_->RemoveTypography(typographyConfigs);
}

int TxtTextEffect::UpdateTypography(std::vector<std::pair<RefPtr<Paragraph>, RefPtr<Paragraph>>>& paragraphs)
{
    CHECK_NULL_RETURN(textEffect_, -1);
    std::vector<std::pair<Rosen::TypographyConfig, Rosen::TypographyConfig>> typographyConfigs;
    for (const auto& paragrah : paragraphs) {
        CHECK_NULL_RETURN(paragrah.first, -1);
        auto oldTxtParagraph = DynamicCast<TxtParagraph>(paragrah.first);
        CHECK_NULL_RETURN(oldTxtParagraph, -1);
        Rosen::TypographyConfig oldConfig;
        oldConfig.typography = oldTxtParagraph->GetSharedParagraph();
        oldConfig.rawTextRange = std::pair(0, oldTxtParagraph->GetParagraphText().size());

        CHECK_NULL_RETURN(paragrah.second, -1);
        auto newTxtParagraph = DynamicCast<TxtParagraph>(paragrah.second);
        CHECK_NULL_RETURN(newTxtParagraph, -1);
        Rosen::TypographyConfig newConfig;
        newConfig.typography = newTxtParagraph->GetSharedParagraph();
        newConfig.rawTextRange = std::pair(0, newTxtParagraph->GetParagraphText().size());

        if (SystemProperties::GetTextTraceEnabled()) {
            ACE_TEXT_SCOPED_TRACE("TxtTextEffect::RemoveTypography oldTxtParagraph:%s newTxtParagraph%s %d %d",
                UtfUtils::Str16DebugToStr8(oldTxtParagraph->GetParagraphText()).c_str(),
                UtfUtils::Str16DebugToStr8(newTxtParagraph->GetParagraphText()).c_str(),
                static_cast<int32_t>(newConfig.rawTextRange.first),
                static_cast<int32_t>(newConfig.rawTextRange.second));
        }

        typographyConfigs.emplace_back(std::make_pair(oldConfig, newConfig));
    }
    return textEffect_->UpdateTypography(typographyConfigs);
}

void TxtTextEffect::StartEffect(RSCanvas& canvas, double x, double y)
{
    CHECK_NULL_VOID(textEffect_);
    ACE_TEXT_SCOPED_TRACE("TxtTextEffect::StartEffect");
    textEffect_->StartEffect(&canvas, x, y);
}
void TxtTextEffect::StopEffect()
{
    CHECK_NULL_VOID(textEffect_);
    ACE_TEXT_SCOPED_TRACE("TxtTextEffect::StopEffect");
    textEffect_->StopEffect();
}

void TxtTextEffect::NoEffect(RSCanvas& canvas, double x, double y)
{
    CHECK_NULL_VOID(textEffect_);
    ACE_TEXT_SCOPED_TRACE("TxtTextEffect::NoEffect");
    textEffect_->NoEffect(&canvas, x, y);
}
} // namespace OHOS::Ace::NG
