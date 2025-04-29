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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_BLUR_STYLE_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_BLUR_STYLE_THEME_H

#include "core/components/common/properties/blur_parameter.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

enum class BlurStyle;
enum class ThemeColorMode;

class BlurStyleTheme : public virtual Theme {
    DECLARE_ACE_TYPE(BlurStyleTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;
        RefPtr<BlurStyleTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;
    };
    BlurStyleTheme() = default;
    ~BlurStyleTheme() override = default;
    std::optional<BlurParameter> GetBlurParameter(BlurStyle style, ThemeColorMode colorMode);
    void SetThemeStyle(const RefPtr<ThemeStyle>& themeStyle);

private:
    static uint32_t GetKeyOfBlurStyle(BlurStyle style, ThemeColorMode colorMode);
    BlurParameter ParseBlurParam(const RefPtr<ThemeStyle>& themeStyle, const std::string& name, bool isDark) const;

    const static std::unordered_map<BlurStyle, std::string> validBlurStyles_;
    RefPtr<ThemeStyle> themeStyle_;
    std::unordered_map<uint32_t, BlurParameter> blurParams_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_BLUR_STYLE_THEME_H
