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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_THEME_THEME_STYLE_IMPL_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_THEME_THEME_STYLE_IMPL_H

#include "core/components/theme/theme_constants.h"

#include "ui/view/theme/theme_style.h"

namespace OHOS::Ace::Kit {
using AceThemeStyle = Ace::ThemeStyle;

class ThemeStyleImpl : public ThemeStyle {
    DECLARE_ACE_TYPE(ThemeStyleImpl, ThemeStyle);

public:
    ThemeStyleImpl(const RefPtr<AceThemeStyle>& themeStyle);
    ~ThemeStyleImpl();

    void GetColorAttr(const std::string& attr, const Ace::Color& errorVal, Ace::Color& retVal) override;
    void GetDimensionAttr(const std::string& attr, const Ace::Dimension& errorVal, Ace::Dimension& retVal) override;
    void GetIntAttr(const std::string& attr, const int32_t& errorVal, int32_t& retVal) override;
    void GetUintAttr(const std::string& attr, const uint32_t& errorVal, uint32_t& retVal) override;
    void GetDoubleAttr(const std::string& attr, const double& errorVal, double& retVal) override;
    void GetStringAttr(const std::string& attr, const std::string& errorVal, std::string& retVal) override;

private:
    RefPtr<AceThemeStyle> themeStyle_;
};

} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_THEME_THEME_STYLE_IMPL_H
