/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components/text/text_theme.h"

#include "core/common/container.h"

namespace OHOS::Ace {
void TextTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<TextTheme>& theme) const
{
    RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_TEXT);
    if (!pattern) {
        LOGW("find pattern of text fail");
        return;
    }
    theme->textClockFontColor_ =
        pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color::BLACK)
            .BlendOpacity(pattern->GetAttr<double>(PATTERN_TEXT_COLOR_ALPHA, DEFAULT_TEXT_OPACITY));
    theme->textStyle_.SetTextColor(pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color::BLACK)
                                       .BlendOpacity(pattern->GetAttr<double>(PATTERN_TEXT_COLOR_ALPHA, 0.9)));
    theme->textStyle_.SetFontSize(pattern->GetAttr<Dimension>("text_font_size", 0.0_vp));
    theme->caretColor_ = pattern->GetAttr<Color>("text_caret_color", Color(0xff006cde));
    theme->textStyle_.SetLineSpacing(pattern->GetAttr<Dimension>("text_line_spacing", 0.0_vp));
    theme->textStyle_.SetFontWeight(static_cast<FontWeight>(pattern->GetAttr<double>("text_font_weight", 0.0)));
    theme->textStyle_.SetTextAlign(static_cast<TextAlign>(pattern->GetAttr<double>("text_align", 0.0)));
    theme->selectedColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_SELECTED, Color(0x33007dff));
    auto draggable = pattern->GetAttr<std::string>("draggable", "0");
    theme->draggable_ = StringUtils::StringToInt(draggable);
    auto dragBackgroundColor = pattern->GetAttr<Color>("drag_background_color", Color::WHITE);
    if (Container::CurrentColorMode() == ColorMode::DARK) {
        dragBackgroundColor = dragBackgroundColor.ChangeOpacity(DRAG_BACKGROUND_OPACITY);
    }
    theme->dragBackgroundColor_ = dragBackgroundColor;
    constexpr double childMinSize = 20.0;
    theme->linearSplitChildMinSize_ = pattern->GetAttr<double>(LINEAR_SPLIT_CHILD_MIN_SIZE, childMinSize);
    auto textShowHandle = pattern->GetAttr<std::string>("text_show_handle", "0");
    theme->isShowHandle_ = StringUtils::StringToInt(textShowHandle);
    auto textShowTranslate = pattern->GetAttr<std::string>("menu_translate_is_support", "0");
    theme->isShowTranslate_ = StringUtils::StringToInt(textShowTranslate);
    auto textShowSearch = pattern->GetAttr<std::string>("text_menu_search_is_support", "0");
    theme->isShowSearch_ = StringUtils::StringToInt(textShowSearch);
    auto disabledOpacity = pattern->GetAttr<double>("interactive_disable", URL_DISA_OPACITY);
    theme->urlDefaultColor_ = pattern->GetAttr<Color>("font_emphasize", Color(0xff007dff));
    theme->urlDisabledColor_ = theme->urlDefaultColor_.BlendOpacity(disabledOpacity);
    theme->urlHoverColor_ = pattern->GetAttr<Color>("interactive_hover", Color(0x33007dff));
    theme->urlPressColor_ = pattern->GetAttr<Color>("interactive_pressed", Color(0x19182431));
    theme->isTextFadeout_ = pattern->GetAttr<std::string>("text_fadeout_enable", "") == "true";
    theme->fadeoutWidth_ = pattern->GetAttr<Dimension>("text_fadeout_width", 16.0_vp);
    theme->marqueeStartPolicy_ = static_cast<MarqueeStartPolicy>(
        static_cast<int32_t>(pattern->GetAttr<double>("text_marquee_start_policy", 0.0)));
    auto textSupportCeliaAsk = pattern->GetAttr<std::string>("menu_celia_ask_is_support", "0");
    theme->isSupportAskCelia_ = StringUtils::StringToInt(textSupportCeliaAsk);
}
} // namespace OHOS::Ace
