/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_PROPERTY_H

#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RichEditorLayoutProperty : public TextLayoutProperty {
    DECLARE_ACE_TYPE(RichEditorLayoutProperty, TextLayoutProperty);

public:
    RichEditorLayoutProperty();
    ~RichEditorLayoutProperty() override;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorLayoutProperty);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PreviewTextStyle, std::string, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayMode, DisplayMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollBarColor, Color, PROPERTY_UPDATE_RENDER);

    // placeholder
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Placeholder, std::u16string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_GROUP(PlaceholderFontStyle, FontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderFontStyle, FontSize, PlaceholderFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderFontStyle, TextColor, PlaceholderTextColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderFontStyle, ItalicFontStyle, PlaceholderItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderFontStyle, FontWeight, PlaceholderFontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderFontStyle, FontFamily, PlaceholderFontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        TextLayoutProperty::ToJsonValue(json, filter);
        json->PutExtAttr("fontColor", GetTextColor().value_or(Color::BLACK).ColorToString().c_str(), filter);
    }

    void UpdateScrollBarColor(const std::optional<Color>& color)
    {
        if (color.has_value()) {
            auto& value = color.value();
            auto hasColor = propScrollBarColor_.has_value();
            auto scrollBarColor = propScrollBarColor_.value_or(Color());
            CHECK_NULL_VOID(!hasColor || scrollBarColor != value ||
                scrollBarColor.GetResourceId() != value.GetResourceId());
            propScrollBarColor_ = value;
            UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
            return;
        }
        if (HasScrollBarColor()) {
            ResetScrollBarColor();
            UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
        }
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_LAYOUT_PROPERTY_H
