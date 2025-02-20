/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PAINT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class TextFieldPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(TextFieldPaintProperty, PaintProperty)
public:
    TextFieldPaintProperty() = default;
    ~TextFieldPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<TextFieldPaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->UpdatePaintPropertyHost(DynamicCast<PaintProperty>(this));
        value->propPlaceholderColor_ = ClonePlaceholderColor();
        value->propInputStyle_ = CloneInputStyle();
        value->propCursorColor_ = CloneCursorColor();
        value->propCursorWidth_ = CloneCursorWidth();
        value->propSelectedBackgroundColor_ = CloneSelectedBackgroundColor();
        value->propBackgroundColor_ = CloneBackgroundColor();
        return value;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetPlaceholderColor();
        ResetCursorColor();
        ResetCursorWidth();
        ResetSelectedBackgroundColor();
        ResetInputStyle();
        ResetBackgroundColor();
        ResetPressBgColor();
        ResetHoverBgColor();
        ResetTextColorFlagByUser();
        ResetCaretColorFlagByUser();
        ResetPlaceholderColorFlagByUser();
        ResetBorderRadiusFlagByUser();
        ResetBorderColorFlagByUser();
        ResetBorderWidthFlagByUser();
        ResetBorderStyleFlagByUser();
        ResetPaddingByUser();
        ResetMarginByUser();
    }

    void ResetUserProperties()
    {
        ResetBackgroundColor();
        ResetTextColorFlagByUser();
        ResetCaretColorFlagByUser();
        ResetPlaceholderColorFlagByUser();
        ResetBorderRadiusFlagByUser();
        ResetBorderColorFlagByUser();
        ResetBorderWidthFlagByUser();
        ResetBorderStyleFlagByUser();
        ResetPaddingByUser();
        ResetMarginByUser();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void FromJson(const std::unique_ptr<JsonValue>& json) override;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PlaceholderColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CursorColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CursorWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectedBackgroundColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(InputStyle, InputStyle, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PressBgColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HoverBgColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FirstHandleInfo, HandleInfoNG, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SecondHandleInfo, HandleInfoNG, PROPERTY_UPDATE_RENDER);
    // used to record values setted by developer
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextColorFlagByUser, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CaretColorFlagByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PlaceholderColorFlagByUser, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BorderRadiusFlagByUser, BorderRadiusProperty, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BorderColorFlagByUser, BorderColorProperty, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BorderWidthFlagByUser, BorderWidthProperty, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BorderStyleFlagByUser, BorderStyleProperty, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PaddingByUser, PaddingProperty, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MarginByUser, MarginProperty, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PreviewTextStart, int32_t, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PreviewTextEnd, int32_t, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PreviewTextStyle, std::string, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(InnerBorderWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(InnerBorderColor, Color, PROPERTY_UPDATE_RENDER);

private:
    ACE_DISALLOW_COPY_AND_MOVE(TextFieldPaintProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PROPERTY_H
