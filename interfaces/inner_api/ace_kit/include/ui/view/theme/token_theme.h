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
#include "ui/view/theme/token_colors.h"
#include "ui/resource/resource_object.h"

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

    void SetResObjs(std::vector<RefPtr<ResourceObject>>&& resObjs)
    {
        resObjs_ = std::move(resObjs);
    }

    const std::vector<RefPtr<ResourceObject>>& GetResObjs() const
    {
        return resObjs_;
    }
private:
    int32_t id_ { 0 };
    RefPtr<TokenColors> colors_;
    std::vector<RefPtr<ResourceObject>> resObjs_;
    ColorMode colorMode_ = ColorMode::COLOR_MODE_UNDEFINED;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_TOKEN_THEME_H