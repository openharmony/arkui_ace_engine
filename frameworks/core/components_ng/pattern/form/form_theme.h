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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_THEME_H

#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace::NG {
/**
 * FormTheme defines color and styles of FormPattern. FormTheme should be built
 * using FormTheme::Builder.
 */
class FormTheme : public virtual Theme {
    DECLARE_ACE_TYPE(FormTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<FormTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<FormTheme> theme = AceType::Claim(new FormTheme());
            if (!themeConstants) {
                return theme;
            }

            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<FormTheme>& theme) const
        {
            RefPtr<ThemeStyle> formPattern = themeConstants->GetPatternByName(THEME_PATTERN_FORM);
            CHECK_NULL_VOID(formPattern);

            theme->unTrustBackgroundColor_ = formPattern->GetAttr<Color>("form_untrust_background_color", Color::RED);
        }
    };

    ~FormTheme() override = default;

    const Color& GetUnTrustBackgroundColor() const
    {
        return unTrustBackgroundColor_;
    }

protected:
    FormTheme() = default;

private:
    Color unTrustBackgroundColor_ = Color::BLUE;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_THEME_H
