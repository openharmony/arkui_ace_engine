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

#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

#include "core/common/container.h"

namespace OHOS::Ace::NG {
void RichEditorTheme::Builder::ParsePatternColor(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<RichEditorTheme>& theme) const
{
    CHECK_NULL_VOID(theme);
    RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_RICH_EDITOR);
    CHECK_NULL_VOID(pattern);
    auto dragBackgroundColor = pattern->GetAttr<Color>("drag_background_color", Color::WHITE);
    if (Container::CurrentColorMode() == ColorMode::DARK) {
        dragBackgroundColor = dragBackgroundColor.ChangeOpacity(DRAG_BACKGROUND_OPACITY);
    }
    theme->dragBackgroundColor_ = dragBackgroundColor;
    theme->placeholderColor_ = pattern->GetAttr<Color>("tips_text_color", Color(0x99000000));
    theme->caretColor_ = pattern->GetAttr<Color>("caret_color", Color(0xff007dff));
    theme->selectedBackgroundColor_ = pattern->GetAttr<Color>("selected_background_color", Color(0xff007dff));
    theme->previewUnderlineColor_ = pattern->GetAttr<Color>("preview_underline_color", Color(0xff007dff));
    theme->popIconColor_ = pattern->GetAttr<Color>("pop_icon_color", Color(0x99000000));
    theme->menuTitleColor_ = pattern->GetAttr<Color>("menu_title_color", Color(0x99000000));
    theme->menuTextColor_ = pattern->GetAttr<Color>("menu_text_color", Color(0x99000000));
    theme->menuIconColor_ = pattern->GetAttr<Color>("menu_icon_color", Color(0x99000000));
    theme->urlDefaultColor_ = pattern->GetAttr<Color>("font_emphasize", Color(0xff007dff));
    auto disabledOpacity = pattern->GetAttr<double>("interactive_disable", URL_DISA_OPACITY);
    theme->urlDisabledColor_ = theme->urlDefaultColor_.BlendOpacity(disabledOpacity);
    theme->urlHoverColor_ = pattern->GetAttr<Color>("interactive_hover", Color(0x0C182431));
    theme->urlPressColor_ = pattern->GetAttr<Color>("interactive_pressed", Color(0x19182431));
    theme->bgColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR, Color::WHITE);
}
} // namespace OHOS::Ace::NG
