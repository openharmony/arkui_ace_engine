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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/data_panel/data_panel_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
struct DataPanelShadow {
    bool isShadowVisible = true;
    double radius = 5.0;
    double offsetX = 5.0;
    double offsetY = 5.0;
    std::vector<Gradient> colors;
    bool operator==(const DataPanelShadow& rhs) const
    {
        return radius == rhs.radius && offsetX == rhs.offsetX && offsetY == rhs.offsetY && colors == rhs.colors &&
               isShadowVisible == rhs.isShadowVisible;
    }
};
class DataPanelPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(DataPanelPaintProperty, PaintProperty)

public:
    DataPanelPaintProperty() = default;
    ~DataPanelPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<DataPanelPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propValues_ = CloneValues();
        paintProperty->propMax_ = CloneMax();
        paintProperty->propDataPanelType_ = CloneDataPanelType();
        paintProperty->propEffect_ = CloneEffect();

        paintProperty->propValueColors_ = CloneValueColors();
        paintProperty->propTrackBackground_ = CloneTrackBackground();
        paintProperty->propStrokeWidth_ = CloneStrokeWidth();
        paintProperty->propShadowOption_ = CloneShadowOption();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetValues();
        ResetMax();
        ResetDataPanelType();
        ResetEffect();
        ResetValueColors();
        ResetTrackBackground();
        ResetStrokeWidth();
        ResetShadowOption();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            ToJsonValueColors(json, filter);
            ToJsonTrackShadow(json, filter);
            return;
        }
        auto jsonDashArray = JsonUtil::CreateArray(true);
        for (size_t i = 0; i < propValues_.value().size(); ++i) {
            auto index = std::to_string(i);
            double value = propValues_.value()[i];
            jsonDashArray->Put(index.c_str(), value);
        }
        bool closeEffect = false;
        if (propEffect_.has_value()) {
            closeEffect = !propEffect_.value();
        }
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<DataPanelTheme>();
        json->PutExtAttr("max", std::to_string(propMax_.value_or(100)).c_str(), filter);
        json->PutExtAttr("closeEffect", closeEffect ? "true" : "false", filter);
        json->PutExtAttr("type", propDataPanelType_ == 1 ? "DataPanelType.Line" : "DataPanelType.Circle", filter);
        json->PutExtAttr("values", jsonDashArray, filter);
        json->PutExtAttr("trackBackgroundColor",
            GetTrackBackground().value_or(theme->GetBackgroundColor()).ColorToString().c_str(), filter);
        json->PutExtAttr("strokeWidth",
            GetStrokeWidth().value_or(theme->GetThickness()).ToString().c_str(), filter);

        ToJsonValueColors(json, filter);
        ToJsonTrackShadow(json, filter);
    }

    void ToJsonValueColors(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        std::vector<Gradient> valueColors;
        if (propValueColors_.has_value()) {
            valueColors = propValueColors_.value();
        } else {
            auto pipelineContext = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto theme = pipelineContext->GetTheme<DataPanelTheme>();
            auto colors = theme->GetColorsArray();
            for (const auto& item : colors) {
                Gradient gradient;
                CreateGradient(item, gradient);
                valueColors.emplace_back(gradient);
            }
        }

        auto valueColorsJosnArray = JsonUtil::CreateArray(true);
        for (size_t i = 0; i < valueColors.size(); ++i) {
            Gradient gradientItem = valueColors[i];
            auto gradientItemJsonArray = JsonUtil::CreateArray(true);
            for (size_t index = 0; index < gradientItem.GetColors().size(); ++index) {
                auto gradientColor = gradientItem.GetColors()[index];
                auto gradientColorJosn = JsonUtil::Create(true);
                gradientColorJosn->Put("color", gradientColor.GetLinearColor().ToColor().ColorToString().c_str());
                gradientColorJosn->Put("offset", std::to_string(gradientColor.GetDimension().Value()).c_str());
                gradientItemJsonArray->Put(std::to_string(index).c_str(), gradientColorJosn);
            }
            valueColorsJosnArray->Put(std::to_string(i).c_str(), gradientItemJsonArray);
        }
        json->PutExtAttr("valueColors", valueColorsJosnArray, filter);
    }

    void ToJsonTrackShadow(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<DataPanelTheme>();
        DataPanelShadow trackShadow;
        if (propShadowOption_.has_value()) {
            trackShadow.radius = propShadowOption_.value().radius;
            trackShadow.offsetX = propShadowOption_.value().offsetX;
            trackShadow.offsetY = propShadowOption_.value().offsetY;
            trackShadow.colors = propShadowOption_.value().colors;
            trackShadow.isShadowVisible = propShadowOption_.value().isShadowVisible;
        } else {
            trackShadow.radius = theme->GetTrackShadowRadius().ConvertToVp();
            trackShadow.offsetX = theme->GetTrackShadowOffsetX().ConvertToVp();
            trackShadow.offsetY = theme->GetTrackShadowOffsetY().ConvertToVp();
        }

        if (!trackShadow.isShadowVisible) {
            json->PutExtAttr("trackShadow", "null", filter);
            return;
        }

        if (trackShadow.colors.size() == 0) {
            if (propValueColors_.has_value() && (propValueColors_.value().size() != 0)) {
                trackShadow.colors = propValueColors_.value();
            } else {
                auto colors = theme->GetColorsArray();
                for (const auto& item : colors) {
                    Gradient gradient;
                    CreateGradient(item, gradient);
                    trackShadow.colors.emplace_back(gradient);
                }
            }
        }
        auto shadowOptionJson = JsonUtil::Create(true);
        shadowOptionJson->Put("radius", std::to_string(trackShadow.radius).c_str());
        shadowOptionJson->Put("offsetX", std::to_string(trackShadow.offsetX).c_str());
        shadowOptionJson->Put("offsetY", std::to_string(trackShadow.offsetY).c_str());

        auto colorsJosnArray = JsonUtil::CreateArray(true);
        for (size_t i = 0; i < trackShadow.colors.size(); ++i) {
            Gradient gradientItem = trackShadow.colors[i];
            auto gradientItemJsonArray = JsonUtil::CreateArray(true);
            for (size_t index = 0; index < gradientItem.GetColors().size(); ++index) {
                auto gradientColor = gradientItem.GetColors()[index];
                auto gradientColorJosn = JsonUtil::Create(true);
                gradientColorJosn->Put("color", gradientColor.GetLinearColor().ToColor().ColorToString().c_str());
                gradientColorJosn->Put("offset", std::to_string(gradientColor.GetDimension().Value()).c_str());
                gradientItemJsonArray->Put(std::to_string(index).c_str(), gradientColorJosn);
            }
            colorsJosnArray->Put(std::to_string(i).c_str(), gradientItemJsonArray);
        }
        shadowOptionJson->Put("colors", colorsJosnArray);
        json->PutExtAttr("trackShadow", shadowOptionJson, filter);
    }

    void CreateGradient(const std::pair<Color, Color>& itemParam, Gradient& gradient) const
    {
        GradientColor gradientColorStart;
        gradientColorStart.SetLinearColor(LinearColor(itemParam.first));
        gradientColorStart.SetDimension(Dimension(0.0));
        gradient.AddColor(gradientColorStart);
        GradientColor gradientColorEnd;
        gradientColorEnd.SetLinearColor(LinearColor(itemParam.second));
        gradientColorEnd.SetDimension(Dimension(1.0));
        gradient.AddColor(gradientColorEnd);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Values, std::vector<double>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Max, double, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DataPanelType, size_t, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Effect, bool, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ValueColors, std::vector<Gradient>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TrackBackground, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShadowOption, DataPanelShadow, PROPERTY_UPDATE_RENDER);

    ACE_DISALLOW_COPY_AND_MOVE(DataPanelPaintProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATA_PANEL_DATA_PANEL_PAINT_PROPERTY_H
