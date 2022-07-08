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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text/text_paragraph.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(TextLayoutProperty, LayoutProperty);

public:
    TextLayoutProperty() = default;

    ~TextLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<TextLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propTextParagraph_ = CloneTextParagraph();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetTextParagraph();
    }

    ACE_DEFINE_CLASS_PROPERTY_GROUP(TextParagraph, TextParagraph);
    ACE_DEFINE_CLASS_PROPERTY(TextParagraph, Content, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_CLASS_PROPERTY(TextParagraph, FontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_CLASS_PROPERTY(TextParagraph, TextColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_CLASS_PROPERTY(TextParagraph, ItalicFontStyle, ItalicFontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_CLASS_PROPERTY(TextParagraph, FontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_CLASS_PROPERTY(TextParagraph, FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_CLASS_PROPERTY(TextParagraph, LineHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_CLASS_PROPERTY(TextParagraph, TextBaseline, TextBaseline, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_CLASS_PROPERTY(TextParagraph, BaselineOffset, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_CLASS_PROPERTY(TextParagraph, TextAlign, TextAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_CLASS_PROPERTY(TextParagraph, MaxLines, uint32_t, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(TextLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_PROPERTY_H
