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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_THEME_TOKEN_THEME_WRAPPER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_THEME_TOKEN_THEME_WRAPPER_H

#include "ui/base/ace_type.h"
#include "ui/view/theme/theme.h"
#include "ui/view/theme/token_theme.h"

namespace OHOS::Ace {
class ACE_EXPORT TokenThemeWrapper : virtual public Theme {
    DECLARE_ACE_TYPE(TokenThemeWrapper, Theme);
public:
    TokenThemeWrapper() = default;
    virtual ~TokenThemeWrapper() = default;

    virtual void ApplyTokenTheme(const TokenTheme& theme) = 0;
};
} // namespace
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_VIEW_THEME_TOKEN_THEME_WRAPPER_H