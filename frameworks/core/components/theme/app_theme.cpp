/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/theme/app_theme.h"

namespace OHOS::Ace {

RefPtr<AppTheme> AppTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<AppTheme> theme = AceType::Claim(new AppTheme());
    if (!themeConstants) {
        return theme;
    }
    auto themeStyle = themeConstants->GetThemeStyle();
    if (!themeStyle) {
        return theme;
    }

    theme->backgroundColor_ = themeStyle->GetAttr<Color>(THEME_ATTR_BG_COLOR, Color::WHITE);
    auto color = themeStyle->GetAttr<Color>("focus_color", Color());
    if (color != Color(0xff000000)) {
        theme->focusColor_ = color;
    }

    auto hoverColor = themeStyle->GetAttr<Color>(THEME_ATTR_HOVER_COLOR, Color::FromRGBO(0, 0, 0, 0.05));
    if (hoverColor != Color(0xff000000)) {
        theme->hoverHighlightEnd_ = hoverColor;
    }
    return theme;
}
} // namespace OHOS::Ace
