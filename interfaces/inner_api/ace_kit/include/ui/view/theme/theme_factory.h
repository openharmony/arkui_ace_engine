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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_THEME_FACTORY_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_THEME_FACTORY_H

#include "ui/view/theme/theme_style.h"
#include "ui/view/frame_node.h"

namespace OHOS::Ace::Kit {

class ACE_FORCE_EXPORT ThemeFactory {
public:
    static bool CreateTheme(Ace::ThemeType type, BuildFunc func);
    static bool CreateCustomTheme(Ace::ThemeType type, BuildThemeWrapperFunc func);

    static RefPtr<ThemeStyle> GetThemeStyle(const std::string& patternName,
        std::optional<std::string> bundleName = std::nullopt,
        std::optional<std::string> moduleName = std::nullopt);

    static RefPtr<Ace::Theme> GetTheme(Ace::ThemeType type);

    template<typename T>
    static RefPtr<T> GetTheme()
    {
        return AceType::DynamicCast<T>(GetTheme(T::TypeId()));
    }

    static RefPtr<Ace::Theme> GetTheme(Ace::ThemeType type, int32_t themeScopeId);

    template<typename T>
    static RefPtr<T> GetTheme(int32_t themeScopeId)
    {
        return AceType::DynamicCast<T>(GetTheme(T::TypeId(), themeScopeId));
    }

    static int32_t GetThemeScopeId(RefPtr<FrameNode>& node);
};

} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_THEME_FACTORY_H
