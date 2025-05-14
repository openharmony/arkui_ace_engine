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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_THEME_STYLE_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_THEME_STYLE_H

#include <functional>
#include <string>

#include "ui/base/ace_type.h"
#include "ui/properties/color.h"
#include "ui/base/geometry/dimension.h"
#include "ui/base/referenced.h"
#include "ui/view/theme/theme.h"
#include "ui/view/theme/token_theme_wrapper.h"

namespace OHOS::Ace::Kit {

using BuildFunc = std::function<RefPtr<Ace::Theme>()>;
using BuildThemeWrapperFunc = std::function<RefPtr<Ace::TokenThemeWrapper>()>;
class ACE_FORCE_EXPORT ThemeStyle : public virtual AceType {
    DECLARE_ACE_TYPE(ThemeStyle, AceType);

public:
    ThemeStyle() = default;
    virtual ~ThemeStyle() = default;

    virtual void GetColorAttr(const std::string& attr, const Ace::Color& errorVal, Ace::Color& retVal) = 0;
    virtual void GetDimensionAttr(const std::string& attr, const Ace::Dimension& errorVal, Ace::Dimension& retVal) = 0;
    virtual void GetIntAttr(const std::string& attr, const int32_t& errorVal, int32_t& retVal) = 0;
    virtual void GetUintAttr(const std::string& attr, const uint32_t& errorVal, uint32_t& retVal) = 0;
    virtual void GetDoubleAttr(const std::string& attr, const double& errorVal, double& retVal) = 0;
    virtual void GetStringAttr(const std::string& attr, const std::string& errorVal, std::string& retVal) = 0;
};

} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_THEME_THEME_STYLE_H
