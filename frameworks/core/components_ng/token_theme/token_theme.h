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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_TOKEN_THEME_TOKEN_THEME_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_TOKEN_THEME_TOKEN_THEME_H

#include "base/memory/ace_type.h"
#include "core/components_ng/token_theme/token_colors.h"


namespace OHOS::Ace::NG {

using TokenThemeScopeId = int32_t;

class TokenTheme : public virtual AceType {
    DECLARE_ACE_TYPE(TokenTheme, AceType);
public:
    TokenTheme(int32_t id)
    {
        id_ = id;
    }
    virtual ~TokenTheme() = default;

    void SetColors(const RefPtr<TokenColors>& colors)
    {
        colors_ = colors;
    }

    const RefPtr<TokenColors>& Colors() const
    {
        return colors_;
    }

    void SetColorMode(ColorMode colorMode)
    {
        colorMode_ = colorMode;
    }

    ColorMode GetColorMode() const
    {
        return colorMode_;
    }

    int32_t GetId() const
    {
        return id_;
    }
private:
    int32_t id_;
    RefPtr<TokenColors> colors_;
    ColorMode colorMode_ = ColorMode::COLOR_MODE_UNDEFINED;
};

} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_TOKEN_THEME_TOKEN_THEME_H