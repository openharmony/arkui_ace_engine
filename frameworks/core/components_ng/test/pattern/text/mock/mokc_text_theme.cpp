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
#define private public
#define protected public
#include "core/components/common/properties/color.h"
#include "core/components/text/text_theme.h"
#include "core/components/theme/theme_manager_impl.h"

namespace OHOS::Ace {
ThemeManagerImpl::ThemeManagerImpl() = default;

RefPtr<Theme> ThemeManagerImpl::GetTheme(ThemeType type)
{
    RefPtr<TextTheme> theme = AceType::Claim(new TextTheme());
    theme->textStyle_.SetTextColor(Color::BLACK);
    theme->textStyle_.SetFontSize(Dimension(50));
    // Styles below do not need to get from ThemeConstants, directly set at here.
    theme->textStyle_.SetFontStyle(FontStyle::NORMAL);
    theme->textStyle_.SetFontWeight(FontWeight::NORMAL);
    theme->textStyle_.SetTextDecoration(TextDecoration::NONE);
    return theme;
}
} // namespace OHOS::Ace
