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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_MODIFIER_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/modifier/modifier.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
class FontFamilyModifier : public PropertyModifier<std::vector<std::string>, LayoutProperty> {
public:
    FontFamilyModifier(const std::vector<std::string>& value)
        : PropertyModifier<std::vector<std::string>, LayoutProperty>(value)
    {
        ACE_DEFINE_MODIFIER_TASK(TextLayoutProperty, LayoutProperty, FontFamily);
    }
    ~FontFamilyModifier() override = default;
};
    
class FontWeightModifier : public PropertyModifier<FontWeight, LayoutProperty> {
public:
    FontWeightModifier(const FontWeight& value) : PropertyModifier<FontWeight, LayoutProperty>(value)
    {
        ACE_DEFINE_MODIFIER_TASK(TextLayoutProperty, LayoutProperty, FontWeight);
    }
    ~FontWeightModifier() override = default;
};

class ItalicFontStyleModifier : public PropertyModifier<ItalicFontStyle, LayoutProperty> {
public:
    ItalicFontStyleModifier(const ItalicFontStyle& value) : PropertyModifier<ItalicFontStyle, LayoutProperty>(value)
    {
        ACE_DEFINE_MODIFIER_TASK(TextLayoutProperty, LayoutProperty, ItalicFontStyle);
    }
    ~ItalicFontStyleModifier() override = default;
};

class FontSizeModifier : public PropertyModifier<Dimension, LayoutProperty> {
public:
    FontSizeModifier(const Dimension& value) : PropertyModifier<Dimension, LayoutProperty>(value)
    {
        ACE_DEFINE_MODIFIER_TASK(TextLayoutProperty, LayoutProperty, FontSize);
    }
    ~FontSizeModifier() override = default;
};

class FontColorModifier : public PropertyModifier<Color, LayoutProperty> {
public:
    FontColorModifier(const Color& value) : PropertyModifier<Color, LayoutProperty>(value)
    {
        ACE_DEFINE_MODIFIER_TASK(TextLayoutProperty, LayoutProperty, TextColor);
    }
    ~FontColorModifier() override = default;
};

class ContentModifier : public PropertyModifier<std::string, LayoutProperty> {
public:
    ContentModifier(const std::string& value) : PropertyModifier<std::string, LayoutProperty>(value)
    {
        ACE_DEFINE_MODIFIER_TASK(TextLayoutProperty, LayoutProperty, Content);
    }
    ~ContentModifier() override = default;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_MODIFIER_H