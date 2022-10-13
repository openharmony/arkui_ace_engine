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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_PAINT_PROPERTY_H

#include "core/components/common/properties/color.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/select/select_font_styles.h"
namespace OHOS::Ace::NG {
class SelectLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(SelectLayoutProperty, LayoutProperty)

public:
    SelectLayoutProperty() = default;

    ~SelectLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<SelectLayoutProperty>();
        paintProperty->UpdateLayoutProperty(this);
        paintProperty->propSelectFont_ = CloneSelectFont();
        paintProperty->propSelectSelectedOptionFont_ = CloneSelectSelectedOptionFont();
        paintProperty->propSelectOptionFont_ = CloneSelectOptionFont();
        
        return paintProperty;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetSelectFont();
        ResetSelectSelectedOptionFont();
        ResetSelectOptionFont();

    }

    ACE_DEFINE_PROPERTY_GROUP(SelectFont, SelectFontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectFont, SelectFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectFont, SelectTextColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectFont, SelectItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectFont, SelectFontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectFont, SelectFontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(SelectSelectedOptionFont, SelectedOptionFontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectSelectedOptionFont, SelectedOptionFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectSelectedOptionFont, SelectedOptionTextColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectSelectedOptionFont, SelectedOptionItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectSelectedOptionFont, SelectedOptionFontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectSelectedOptionFont, SelectedOptionFontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(SelectOptionFont, OptionFontFontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectOptionFont, OptionFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectOptionFont, OptionTextColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectOptionFont, OptionItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectOptionFont, OptionFontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SelectOptionFont, OptionFontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);

};

} // namespace OHOS::Ace::NG

#endif //FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_PAINT_PROPERTY_H