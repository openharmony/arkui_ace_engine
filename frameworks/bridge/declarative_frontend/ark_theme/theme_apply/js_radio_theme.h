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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_RADIO_THEME_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_RADIO_THEME_H

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "core/components_ng/pattern/radio/radio_model.h"
#include "core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace::Framework {
class JSRadioTheme {
public:
    static void ApplyTheme()
    {
        // check whether we have Theme for id or not
        auto themeColors = JSThemeUtils::GetThemeColors();
        if (!themeColors) {
            // no need to apply custom theme colors
            return;
        }
        RadioModel::GetInstance()->SetCheckedBackgroundColor(themeColors->CompBackgroundEmphasize());
        RadioModel::GetInstance()->SetUncheckedBorderColor(themeColors->IconFourth());
        RadioModel::GetInstance()->SetIndicatorColor(themeColors->IconOnPrimary());
    }

    static bool ObtainCheckedBackgroundColor(Color &color)
    {
        if (auto themeColors = JSThemeUtils::GetThemeColors(); themeColors.has_value()) {
            color = themeColors->CompBackgroundEmphasize();
            return true;
        }
        return false;
    }

    static bool ObtainUncheckedBorderColor(Color &color)
    {
        if (auto themeColors = JSThemeUtils::GetThemeColors(); themeColors.has_value()) {
            color = themeColors->IconFourth();
            return true;
        }
        return false;
    }

    static bool ObtainIndicatorColor(Color &color)
    {
        if (auto themeColors = JSThemeUtils::GetThemeColors(); themeColors.has_value()) {
            color = themeColors->IconOnPrimary();
            return true;
        }
        return false;
    }
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_RADIO_THEME_H
