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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_RENDER_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_RENDER_PROPERTY_H

#include <string>

#include "core/components_ng/pattern/slider/slider_style.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
// PaintProperty are used to set render properties.
class SliderPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(SliderPaintProperty, PaintProperty)
public:
    SliderPaintProperty() = default;
    ~SliderPaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<SliderPaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->propSliderPaintStyle_ = CloneSliderPaintStyle();
        value->propSliderTipStyle_ = CloneSliderTipStyle();
        return value;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetSliderPaintStyle();
        ResetSliderTipStyle();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SliderTheme>();
        CHECK_NULL_VOID(theme);
        PaintProperty::ToJsonValue(json);
        auto jsonConstructor = JsonUtil::Create(true);
        jsonConstructor->Put("value", std::to_string(GetValue().value_or(0.0f)).c_str());
        jsonConstructor->Put("min", std::to_string(GetMin().value_or(0.0f)).c_str());
        jsonConstructor->Put("max", std::to_string(GetMax().value_or(100.0f)).c_str());
        jsonConstructor->Put("step", std::to_string(GetStep().value_or(1.0f)).c_str());
        jsonConstructor->Put("reverse", GetReverse().value_or(false) ? "true" : "false");
        jsonConstructor->Put("direction",
            (GetDirection().value_or(Axis::HORIZONTAL)) == Axis::VERTICAL ? "Axis.Vertical" : "Axis.Horizontal");
        json->Put("constructor", jsonConstructor);
        json->Put("blockColor", GetBlockColor().value_or(theme->GetBlockColor()).ColorToString().c_str());
        json->Put("trackColor", GetTrackBackgroundColor().value_or(theme->GetTrackBgColor()).ColorToString().c_str());
        json->Put("selectedColor", GetSelectColor().value_or(theme->GetTrackSelectedColor()).ColorToString().c_str());
        json->Put("showSteps", GetShowSteps().value_or(false) ? "true" : "false");
        json->Put("showTips", GetShowTips().value_or(false) ? "true" : "false");
        json->Put("blockBorderColor", GetBlockBorderColorValue(Color::TRANSPARENT).ColorToString().c_str());
        json->Put("blockBorderWidth", GetBlockBorderWidthValue(Dimension()).ToString().c_str());
        json->Put("stepColor", GetStepColorValue(theme->GetMarkerColor()).ColorToString().c_str());
        if (GetTrackBorderRadius().has_value()) {
            json->Put("trackBorderRadius", GetTrackBorderRadius().value().ToString().c_str());
        }
        static const std::array<std::string, 3> SLIDER_BLOCK_TYPE_TO_STRING = {
            "BlockStyleType.DEFAULT",
            "BlockStyleType.IMAGE",
            "BlockStyleType.SHAPE",
        };
        json->Put("blockType",
            SLIDER_BLOCK_TYPE_TO_STRING.at(static_cast<int>(GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT)))
                .c_str());
        json->Put("stepSize", GetStepSizeValue(theme->GetMarkerSize()).ToString().c_str());
        if (GetCustomContent().has_value()) {
            json->Put("content", GetCustomContent().value().c_str());
        }
    }

    SizeF GetBlockSizeValue(const SizeF& defaultValue)
    {
        auto& groupProperty = GetSliderPaintStyle();
        if (groupProperty) {
            if (groupProperty->HasBlockSize()) {
                return SizeF(groupProperty->GetBlockSizeValue().Width().ConvertToPx(),
                    groupProperty->GetBlockSizeValue().Height().ConvertToPx());
            }
        }
        return defaultValue;
    }

    ACE_DEFINE_PROPERTY_GROUP(SliderPaintStyle, SliderPaintStyle)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Value, float, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Min, float, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Max, float, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Step, float, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Reverse, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Direction, Axis, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockColor, Color, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, TrackBackgroundColor, Color, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, SelectColor, Color, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, ShowSteps, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockBorderColor, Color, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockBorderWidth, Dimension, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, StepColor, Color, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, TrackBorderRadius, Dimension, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        SliderPaintStyle, BlockType, SliderModel::BlockStyleType, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockImage, std::string, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockImageBundleName, std::string, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockImageModuleName, std::string, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockShape, RefPtr<BasicShape>, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, StepSize, Dimension, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, SliderMode, SliderModel::SliderMode, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_GROUP(SliderTipStyle, SliderTipStyle)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderTipStyle, ShowTips, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderTipStyle, Padding, Dimension, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderTipStyle, Content, std::string, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderTipStyle, FontSize, Dimension, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderTipStyle, TextColor, Color, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderTipStyle, TipColor, Color, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderTipStyle, CustomContent, std::string, PROPERTY_UPDATE_RENDER)
private:
    ACE_DISALLOW_COPY_AND_MOVE(SliderPaintProperty);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_RENDER_PROPERTY_H
