/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_PROPERTY_H

#include <string>

#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(TextLayoutProperty, LayoutProperty);

public:
    TextLayoutProperty() = default;

    ~TextLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<TextLayoutProperty>();
        Clone(value);
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetFontStyle();
        ResetTextLineStyle();
        ResetContent();
        ResetForegroundColor();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    void FromJson(const std::unique_ptr<JsonValue>& json) override;

    ACE_DEFINE_PROPERTY_GROUP(FontStyle, FontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, TextColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, TextShadow, Shadow, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, ItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, TextDecoration, TextDecoration, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, TextDecorationColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, TextDecorationStyle, TextDecorationStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, TextCase, TextCase, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, AdaptMinFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, AdaptMaxFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, LetterSpacing, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_GROUP(TextLineStyle, TextLineStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, LineHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, TextBaseline, TextBaseline, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, BaselineOffset, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, TextAlign, TextAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, TextOverflow, TextOverflow, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, MaxLines, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        TextLineStyle, HeightAdaptivePolicy, TextHeightAdaptivePolicy, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, TextIndent, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Content, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CopyOption, CopyOptions, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ForegroundColor, Color, PROPERTY_UPDATE_MEASURE_SELF);

    // for XTS inspector
    std::string InspectorGetTextFont() const
    {
        TextStyle font;
        if (GetFontFamily().has_value()) {
            font.SetFontFamilies(GetFontFamily().value());
        }
        if (GetFontSize().has_value()) {
            font.SetFontSize(GetFontSize().value());
        }
        if (GetItalicFontStyle().has_value()) {
            font.SetFontStyle(GetItalicFontStyle().value());
        }
        if (GetFontWeight().has_value()) {
            font.SetFontWeight(GetFontWeight().value());
        }
        return V2::GetTextStyleInJson(font);
    }
    std::string GetCopyOptionString() const;
    std::string GetFont() const;

protected:
    void Clone(RefPtr<LayoutProperty> property) const override
    {
        auto value = DynamicCast<TextLayoutProperty>(property);
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propFontStyle_ = CloneFontStyle();
        value->propTextLineStyle_ = CloneTextLineStyle();
        value->propContent_ = CloneContent();
        value->propForegroundColor_ = CloneForegroundColor();
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(TextLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_PROPERTY_H
