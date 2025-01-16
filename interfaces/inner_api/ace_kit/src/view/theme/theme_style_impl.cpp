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

#include "interfaces/inner_api/ace_kit/src/view/theme/theme_style_impl.h"

namespace OHOS::Ace::Kit {
ThemeStyleImpl::ThemeStyleImpl(const RefPtr<AceThemeStyle>& themeStyle) : themeStyle_(themeStyle)
{}

ThemeStyleImpl::~ThemeStyleImpl()
{
    themeStyle_.Reset();
}

void ThemeStyleImpl::GetColorAttr(const std::string& attr, const Ace::Color& errorVal, Ace::Color& retVal)
{
    retVal = themeStyle_->GetAttr<Ace::Color>(attr, errorVal);
}

void ThemeStyleImpl::GetDimensionAttr(const std::string& attr, const Ace::Dimension& errorVal, Ace::Dimension& retVal)
{
    retVal = themeStyle_->GetAttr<Ace::Dimension>(attr, errorVal);
}

void ThemeStyleImpl::GetIntAttr(const std::string& attr, const int32_t& errorVal, int32_t& retVal)
{
    retVal = themeStyle_->GetAttr<int32_t>(attr, errorVal);
}

void ThemeStyleImpl::GetUintAttr(const std::string& attr, const uint32_t& errorVal, uint32_t& retVal)
{
    retVal = themeStyle_->GetAttr<uint32_t>(attr, errorVal);
}

void ThemeStyleImpl::GetDoubleAttr(const std::string& attr, const double& errorVal, double& retVal)
{
    retVal = themeStyle_->GetAttr<double>(attr, errorVal);
}

void ThemeStyleImpl::GetStringAttr(const std::string& attr, const std::string& errorVal, std::string& retVal)
{
    retVal = themeStyle_->GetAttr<std::string>(attr, errorVal);
}

} // namespace OHOS::Ace::Kit
