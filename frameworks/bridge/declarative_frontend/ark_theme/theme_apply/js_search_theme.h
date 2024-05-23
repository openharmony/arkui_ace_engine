/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_SEARCH_THEME_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_SEARCH_THEME_H

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "core/components_ng/pattern/search/search_model.h"
#include "core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace::Framework {
class JSSeacrhTheme {
public:
    static void ApplyTheme()
    {
        // check whether we have Theme for id or not
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors) {
            // no need to apply custom theme colors
            return;
        }
        SearchModel::GetInstance()->SetTextColor(themeColors.value().FontPrimary());
        SearchModel::GetInstance()->SetPlaceholderColor(themeColors.value().FontSecondary());
        SearchModel::GetInstance()->SetSearchIconColor(themeColors.value().IconSecondary());
        SearchModel::GetInstance()->SetCaretColor(themeColors.value().Brand());
        SearchModel::GetInstance()->SetCancelIconColor(themeColors.value().IconSecondary());
        SearchModel::GetInstance()->SetSearchButtonFontColor(themeColors.value().FontEmphasize());
        Color selectedColor = themeColors.value().Brand();
        // Alpha = 255 means opaque
        if (selectedColor.GetAlpha() == JSThemeUtils::DEFAULT_ALPHA) {
            // Default setting of 20% opacity
            selectedColor = selectedColor.ChangeOpacity(JSThemeUtils::DEFAULT_OPACITY);
        }
        SearchModel::GetInstance()->SetSelectedBackgroundColor(selectedColor);
        ViewAbstractModel::GetInstance()->SetBackgroundColor(themeColors.value().CompBackgroundTertiary());
    }

    static bool ObtainCancelIconColor(Color &color)
    {
        if (auto themeColors = JSThemeUtils::GetThemeColors(); themeColors.has_value()) {
            color = themeColors->IconSecondary();
            return true;
        }
        return false;
    }

    static bool ObtainSearchButtonFontColor(Color &color)
    {
        if (auto themeColors = JSThemeUtils::GetThemeColors(); themeColors.has_value()) {
            color = themeColors->FontEmphasize();
            return true;
        }
        return false;
    }
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_SEARCH_THEME_H