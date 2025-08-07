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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_TOKEN_THEME_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_TOKEN_THEME_H

#include "ui/base/ace_type.h"
#include "ui/resource/resource_object.h"
#include "ui/view/theme/token_colors.h"

namespace OHOS::Ace {

using TokenThemeScopeId = int32_t;

class ACE_FORCE_EXPORT TokenTheme : public virtual AceType {
    DECLARE_ACE_TYPE(TokenTheme, AceType);

public:
    explicit TokenTheme(int32_t id)
    {
        id_ = id;
    }
    virtual ~TokenTheme() = default;

    void SetColors(const RefPtr<TokenColors>& colors)
    {
        colors_ = colors;
    }

    void SetDarkColors(const RefPtr<TokenColors>& darkColors)
    {
        darkColors_ = darkColors;
    }

    const RefPtr<TokenColors>& Colors() const
    {
        return IsDark() ? darkColors_ : colors_;
    }

    void SetColorMode(const ColorMode& colorMode)
    {
        colorMode_ = colorMode;
        auto colors = IsDark() ? darkColors_ : colors_;
        if (colors) {
            colors->SetColorMode(colorMode);
        }
    }

    const ColorMode& GetColorMode() const
    {
        return colorMode_;
    }

    int32_t GetId() const
    {
        return id_;
    }

    void SetResObjs(std::vector<RefPtr<ResourceObject>>&& resObjs)
    {
        if (colors_) {
            colors_->SetResObjs(std::move(resObjs));
        }
    }

    void SetDarkResObjs(std::vector<RefPtr<ResourceObject>>&& darkResObjs)
    {
        if (darkColors_) {
            darkColors_->SetResObjs(std::move(darkResObjs));
        }
    }

    std::vector<RefPtr<ResourceObject>>& GetResObjs()
    {
        auto colors = IsDark() ? darkColors_ : colors_;
        if (colors) {
            resObjs = colors->GetResObjs();
        } else {
            resObjs.clear();
        }
        return resObjs;
    }

    static bool IsDarkMode();

private:
    int32_t id_ { 0 };
    RefPtr<TokenColors> colors_;
    RefPtr<TokenColors> darkColors_;
    ColorMode colorMode_ = ColorMode::COLOR_MODE_UNDEFINED;
    std::vector<RefPtr<ResourceObject>> resObjs;
    bool IsDark() const
    {
        if (colorMode_ == ColorMode::COLOR_MODE_UNDEFINED) {
            return IsDarkMode();
        }
        return colorMode_ == ColorMode::DARK;
    }
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_TOKEN_THEME_H
