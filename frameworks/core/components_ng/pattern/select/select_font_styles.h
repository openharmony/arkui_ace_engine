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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_SELECT_FONT_STYLES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_SELECT_FONT_STYLES_H

#include "core/components/common/properties/text_style.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

struct SelectFontStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectTextColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectItalicFontStyle, Ace::FontStyle);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectFontWeight, FontWeight);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectFontFamily, std::vector<std::string>);
};

struct SelectedOptionFontStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedOptionFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedOptionTextColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedOptionItalicFontStyle, Ace::FontStyle);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedOptionFontWeight, FontWeight);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedOptionFontFamily, std::vector<std::string>);
};

struct OptionFontFontStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OptionFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OptionTextColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OptionItalicFontStyle, Ace::FontStyle);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OptionFontWeight, FontWeight);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OptionFontFamily, std::vector<std::string>);
};

} // namespace OHOS::Ace::NG

#endif