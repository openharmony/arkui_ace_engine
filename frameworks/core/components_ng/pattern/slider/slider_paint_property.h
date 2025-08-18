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

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/slider/slider_style.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
// PaintProperty are used to set render properties.
class SliderPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(SliderPaintProperty, PaintProperty);
public:
    SliderPaintProperty() = default;
    ~SliderPaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<SliderPaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->PaintProperty::UpdatePaintPropertyHost(DynamicCast<PaintProperty>(this));
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

    std::string ToJsonTrackBackgroundColor() const
    {
        Gradient colors;
        if (HasTrackBackgroundColor()) {
            colors = GetTrackBackgroundColor().value();
            if (GetTrackBackgroundIsResourceColor()) {
                return colors.GetColors()[0].GetLinearColor().ToColor().ColorToString();
            }
            return GradientToJson(colors);
        }
        auto host = GetHost();
        CHECK_NULL_RETURN(host, "");
        auto pipeline = host->GetContext();
        CHECK_NULL_RETURN(pipeline, "");
        auto theme = pipeline->GetTheme<SliderTheme>(host->GetThemeScopeId());
        CHECK_NULL_RETURN(theme, "");
        return theme->GetTrackBgColor().ColorToString();
    }

    std::string GradientToJson(Gradient colors) const
    {
        auto jsonArray = JsonUtil::CreateArray(true);
        for (size_t index = 0; index < colors.GetColors().size(); ++index) {
            auto gradientColor = colors.GetColors()[index];
            auto gradientColorJson = JsonUtil::Create(true);
            gradientColorJson->Put("color", gradientColor.GetLinearColor().ToColor().ColorToString().c_str());
            gradientColorJson->Put("offset", std::to_string(gradientColor.GetDimension().Value()).c_str());
            jsonArray->Put(std::to_string(index).c_str(), gradientColorJson);
        }
        return jsonArray->ToString();
    }

    std::string InteractionModeToJson() const
    {
        const std::array<std::string, 3> SLIDER_INTERACTION_MODE_TO_STRING = {
            "SliderInteraction.SLIDE_AND_CLICK",
            "SliderInteraction.SLIDE_ONLY",
            "SliderInteraction.SLIDE_AND_CLICK_UP",
        };
        auto interactionIndex =
            static_cast<size_t>(GetSliderInteractionModeValue(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK));
        if (interactionIndex < SLIDER_INTERACTION_MODE_TO_STRING.size()) {
            return SLIDER_INTERACTION_MODE_TO_STRING.at(interactionIndex);
        }
        return "";
    }

    std::string BlockTypeToJson() const
    {
        const std::array<std::string, 3> SLIDER_BLOCK_TYPE_TO_STRING = {
            "BlockStyleType.DEFAULT",
            "BlockStyleType.IMAGE",
            "BlockStyleType.SHAPE",
        };
        auto blockTypeIndex = static_cast<size_t>(GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT));
        if (blockTypeIndex < SLIDER_BLOCK_TYPE_TO_STRING.size()) {
            return SLIDER_BLOCK_TYPE_TO_STRING.at(blockTypeIndex);
        }
        return "";
    }

    std::string ToJsonSelectColor() const
    {
        if (HasSelectGradientColor()) {
            Gradient colors = GetSelectGradientColor().value();
            if (GetSelectIsResourceColorValue(false)) {
                return colors.GetColors()[0].GetLinearColor().ToColor().ColorToString();
            } else {
                return GradientToJson(colors);
            }
        }
        auto host = GetHost();
        CHECK_NULL_RETURN(host, "");
        auto pipeline = host->GetContext();
        CHECK_NULL_RETURN(pipeline, "");
        auto theme = pipeline->GetTheme<SliderTheme>(host->GetThemeScopeId());
        CHECK_NULL_RETURN(theme, "");
        return GetSelectColor().value_or(theme->GetTrackSelectedColor()).ColorToString();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            if (GetCustomContent().has_value()) {
                json->PutFixedAttr("content", GetCustomContent().value().c_str(), filter, FIXED_ATTR_CONTENT);
            }
            return;
        }
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<SliderTheme>(host->GetThemeScopeId());
        CHECK_NULL_VOID(theme);
        auto jsonConstructor = JsonUtil::Create(true);
        jsonConstructor->Put("value", std::to_string(GetValue().value_or(0.0f)).c_str());
        jsonConstructor->Put("min", std::to_string(GetMin().value_or(0.0f)).c_str());
        jsonConstructor->Put("max", std::to_string(GetMax().value_or(100.0f)).c_str());
        jsonConstructor->Put("step", std::to_string(GetStep().value_or(1.0f)).c_str());
        jsonConstructor->Put("reverse", GetReverse().value_or(false) ? "true" : "false");
        jsonConstructor->Put("direction",
            (GetDirection().value_or(Axis::HORIZONTAL)) == Axis::VERTICAL ? "Axis.Vertical" : "Axis.Horizontal");
        json->PutExtAttr("constructor", jsonConstructor, filter);
        json->PutExtAttr("blockColor",
            GetBlockColor().value_or(theme->GetBlockColor()).ColorToString().c_str(), filter);
        json->PutExtAttr("trackColor", ToJsonTrackBackgroundColor().c_str(), filter);
        json->PutExtAttr("selectedColor", ToJsonSelectColor().c_str(), filter);
        json->PutExtAttr("showSteps", GetShowSteps().value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("showTips", GetShowTips().value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("blockBorderColor",
            GetBlockBorderColorValue(Color::TRANSPARENT).ColorToString().c_str(), filter);
        json->PutExtAttr("blockBorderWidth", GetBlockBorderWidthValue(Dimension()).ToString().c_str(), filter);
        json->PutExtAttr("stepColor", GetStepColorValue(theme->GetMarkerColor()).ColorToString().c_str(), filter);
        if (GetTrackBorderRadius().has_value()) {
            json->PutExtAttr("trackBorderRadius", GetTrackBorderRadius().value().ToString().c_str(), filter);
        }
        if (GetSelectedBorderRadius().has_value()) {
            json->PutExtAttr("selectedBorderRadius", GetSelectedBorderRadius().value().ToString().c_str(), filter);
        }
        json->PutExtAttr("blockType", BlockTypeToJson().c_str(), filter);
        json->PutExtAttr("stepSize", GetStepSizeValue(theme->GetMarkerSize()).ToString().c_str(), filter);
        if (GetCustomContent().has_value()) {
            json->PutFixedAttr("content", GetCustomContent().value().c_str(), filter, FIXED_ATTR_CONTENT);
        }
        json->PutExtAttr("sliderInteractionMode", InteractionModeToJson().c_str(), filter);
        json->PutExtAttr("minResponsiveDistance",
            std::to_string(GetMinResponsiveDistance().value_or(0.0f)).c_str(), filter);
        auto slideRangeValues = GetValidSlideRange();
        if (slideRangeValues.has_value() && slideRangeValues.value()->HasValidValues()) {
            auto slideRange = JsonUtil::Create(true);
            slideRange->Put("from", std::to_string(slideRangeValues.value()->GetFromValue()).c_str());
            slideRange->Put("to", std::to_string(slideRangeValues.value()->GetToValue()).c_str());
            json->PutExtAttr("slideRange", slideRange, filter);
        }
        json->PutExtAttr("enableHapticFeedback", GetEnableHapticFeedback().value_or(true) ? "true" : "false", filter);
#ifdef SUPPORT_DIGITAL_CROWN
        static const std::array<std::string, 3> SLIDER_CROWN_SENSITIVITY_TO_STRING = {
            "CrownSensitivity.LOW",
            "CrownSensitivity.MEDIUM",
            "CrownSensitivity.HIGH",
        };
        json->PutExtAttr("digitalCrownSensitivity",
            SLIDER_CROWN_SENSITIVITY_TO_STRING
                .at(static_cast<int>(GetDigitalCrownSensitivityValue(CrownSensitivity::MEDIUM)))
                .c_str(),
            filter);
#endif
        auto sliderShowStepOptions = GetSliderShowStepOptions();
        if ((sliderShowStepOptions.has_value()) && (!sliderShowStepOptions.value().empty())) {
            auto stepOptions = JsonUtil::Create(true);
            for (auto option : sliderShowStepOptions.value()) {
                stepOptions->Put(std::to_string(option.first).c_str(), option.second.c_str());
            }
            json->PutExtAttr("sliderShowStepOptions", stepOptions, filter);
        }
    }

    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override
    {
        PaintProperty::ToTreeJson(json, config);
        json->Put(TreeKey::CONTENT, GetCustomContent().value_or("").c_str());
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

    float GetStepRatio()
    {
        float min = GetMin().value_or(0.0f);
        float max = GetMax().value_or(100.0f);
        float step = GetStep().value_or(1.0f);
        if (max == min) {
            return 0.0f;
        }
        return step / (max - min);
    }

    ACE_DEFINE_PROPERTY_GROUP(SliderPaintStyle, SliderPaintStyle)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Value, float, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Min, float, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Max, float, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Step, float, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, MinResponsiveDistance, float, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Reverse, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, Direction, Axis, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockColor, Color, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockColorSetByUser, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, TrackBackgroundColor, Gradient, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, TrackBackgroundColorSetByUser, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, TrackBackgroundIsResourceColor, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, SelectColor, Color, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, SelectColorSetByUser, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, SelectGradientColor, Gradient, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, SelectIsResourceColor, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, ShowSteps, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        SliderPaintStyle, SliderInteractionMode, SliderModel::SliderInteraction, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockBorderColor, Color, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockBorderColorSetByUser, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockBorderWidth, Dimension, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, StepColor, Color, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, StepColorSetByUser, bool, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, TrackBorderRadius, Dimension, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, SelectedBorderRadius, Dimension, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        SliderPaintStyle, BlockType, SliderModel::BlockStyleType, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockImage, std::string, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockImageBundleName, std::string, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockImageModuleName, std::string, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, BlockShape, RefPtr<BasicShape>, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, StepSize, Dimension, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, SliderMode, SliderModel::SliderMode, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        SliderPaintStyle, ValidSlideRange, RefPtr<SliderModel::SliderValidRange>, PROPERTY_UPDATE_RENDER)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SliderPaintStyle, EnableHapticFeedback, bool, PROPERTY_UPDATE_RENDER)
#ifdef SUPPORT_DIGITAL_CROWN
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        SliderPaintStyle, DigitalCrownSensitivity, CrownSensitivity, PROPERTY_UPDATE_RENDER)
#endif
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        SliderPaintStyle, SliderShowStepOptions, SliderModel::SliderShowStepOptions, PROPERTY_UPDATE_RENDER)
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
