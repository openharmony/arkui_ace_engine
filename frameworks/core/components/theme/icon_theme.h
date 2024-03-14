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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_ICON_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_ICON_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {
/**
 * IconTheme defines base icon. using IconTheme::Builder.
 */
class IconTheme : public virtual Theme {
    DECLARE_ACE_TYPE(IconTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<IconTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;

    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<IconTheme>& theme) const;
    };

    ~IconTheme() override = default;

    std::string GetIconPath(const InternalResource::ResourceId& resourceId) const;

protected:
    IconTheme() = default;

private:
    RefPtr<ThemeStyle> pattern_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_ICON_THEME_H
