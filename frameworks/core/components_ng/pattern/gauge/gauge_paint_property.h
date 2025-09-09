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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_PAINT_PROPERTY_H

#include "core/common/container.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"
#include "core/components_ng/render/paint_property.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {
using ColorStopArray = std::vector<std::pair<Color, Dimension>>;
enum class GaugeType : int32_t {
    TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT = 0,
    TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT = 1,
    TYPE_CIRCULAR_MONOCHROME = 2,
};

struct GaugeShadowOptions {
    bool isShadowVisible = true;
    float radius = DEFAULT_GAUGE_SHADOW_RADIUS;
    float offsetX = DEFAULT_GAUGE_SHADOW_OFFSETX;
    float offsetY = DEFAULT_GAUGE_SHADOW_OFFSETY;
    bool operator==(const GaugeShadowOptions& rhs) const
    {
        return radius == rhs.radius && offsetX == rhs.offsetX && offsetY == rhs.offsetY &&
               isShadowVisible == rhs.isShadowVisible;
    }
    using UpdateFunc = std::function<void(const RefPtr<ResourceObject>&, GaugeShadowOptions&)>;
    void AddResource(const std::string& key, const RefPtr<ResourceObject>& resObj, UpdateFunc&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resMap_[key] = { resObj, std::move(updateFunc) };
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.obj, *this);
        }
    }

private:
    struct ResourceUpdater {
        RefPtr<ResourceObject> obj;
        UpdateFunc updateFunc;
    };

    std::unordered_map<std::string, ResourceUpdater> resMap_;
};
class GaugePaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(GaugePaintProperty, PaintProperty);

public:
    GaugePaintProperty() = default;
    ~GaugePaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<GaugePaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propValue_ = CloneValue();
        paintProperty->propMin_ = CloneMin();
        paintProperty->propMax_ = CloneMax();
        paintProperty->propStartAngle_ = CloneStartAngle();
        paintProperty->propEndAngle_ = CloneEndAngle();
        paintProperty->propColors_ = CloneColors();
        paintProperty->propGradientColors_ = CloneGradientColors();
        paintProperty->propValues_ = CloneValues();
        paintProperty->propStrokeWidth_ = CloneStrokeWidth();
        paintProperty->propGaugeType_ = CloneGaugeType();
        paintProperty->propShadowOptions_ = CloneShadowOptions();
        paintProperty->propIsShowIndicator_ = CloneIsShowIndicator();
        paintProperty->propIndicatorIconSourceInfo_ = CloneIndicatorIconSourceInfo();
        paintProperty->propIndicatorSpace_ = CloneIndicatorSpace();
        paintProperty->propIndicatorChange_ = CloneIndicatorChange();
        paintProperty->propIsSensitive_ = CloneIsSensitive();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetValue();
        ResetMin();
        ResetMax();
        ResetStartAngle();
        ResetEndAngle();
        ResetColors();
        ResetGradientColors();
        ResetValues();
        ResetStrokeWidth();
        ResetGaugeType();
        ResetShadowOptions();
        ResetIsShowIndicator();
        ResetIndicatorIconSourceInfo();
        ResetIndicatorSpace();
        ResetIsSensitive();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                ToJsonColor(json, filter);
                ToJsonIndicator(json, filter);
                ToJsonTrackShadow(json, filter);
            }
            return;
        }
        json->PutExtAttr("value", StringUtils::DoubleToString(propValue_.value_or(0)).c_str(), filter);
        json->PutExtAttr("max", StringUtils::DoubleToString(propMax_.value_or(100)).c_str(), filter);
        json->PutExtAttr("min", StringUtils::DoubleToString(propMin_.value_or(0)).c_str(), filter);
        json->PutExtAttr("startAngle", StringUtils::DoubleToString(propStartAngle_.value_or(0)).c_str(), filter);
        json->PutExtAttr("endAngle", StringUtils::DoubleToString(propEndAngle_.value_or(360)).c_str(), filter);
        json->PutExtAttr("isSensitive", std::to_string(GetIsSensitive().value_or(false)).c_str(), filter);
        json->PutExtAttr("privacySensitive", GetIsSensitive().value_or(false)? "true": "false", filter);
        if (propStrokeWidth_.has_value()) {
            json->PutExtAttr("strokeWidth", propStrokeWidth_.value().ToString().c_str(), filter);
        } else {
            json->PutExtAttr("strokeWidth", "", filter);
        }

        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            auto jsonColors = JsonUtil::CreateArray(true);
            if (propColors_.has_value() && propColors_.has_value()) {
                for (size_t i = 0; i < propValues_.value().size(); i++) {
                    auto jsonObject = JsonUtil::CreateArray(true);
                    jsonObject->Put("0", propColors_.value()[i].ColorToString().c_str());
                    jsonObject->Put("1", propValues_.value()[i]);
                    auto index = std::to_string(i);
                    jsonColors->Put(index.c_str(), jsonObject);
                }
            }
            json->PutExtAttr("colors", jsonColors->ToString().c_str(), filter);
        } else {
            ToJsonColor(json, filter);
            ToJsonIndicator(json, filter);
            ToJsonTrackShadow(json, filter);
        }
    }

    void ToJsonColor(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        if (!propGaugeType_.has_value()) {
            auto jsonColor = JsonUtil::CreateArray(true);
            for (size_t j = 0; j < GAUGE_DEFAULT_COLOR.size(); j++) {
                jsonColor->Put(std::to_string(j).c_str(), GAUGE_DEFAULT_COLOR[j].ColorToString().c_str());
            }
            json->PutExtAttr("colors", jsonColor->ToString().c_str(), filter);
            return;
        }

        if (propGaugeType_.value() == GaugeType::TYPE_CIRCULAR_MONOCHROME) {
            if (propGradientColors_.has_value()) {
                json->PutExtAttr("colors",
                    propGradientColors_.value().at(0).at(0).first.ColorToString().c_str(), filter);
            }
            return;
        }

        if (propGaugeType_.value() == GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT) {
            if (propGradientColors_.has_value()) {
                auto jsonColor = JsonUtil::CreateArray(true);
                auto colorStopArray = propGradientColors_.value().at(0);
                for (size_t j = 0; j < colorStopArray.size(); j++) {
                    auto jsonColorObject = JsonUtil::CreateArray(true);
                    jsonColorObject->Put("0", colorStopArray[j].first.ColorToString().c_str());
                    jsonColorObject->Put("1", std::to_string(colorStopArray[j].second.Value()).c_str());
                    auto indexStr = std::to_string(j);
                    jsonColor->Put(indexStr.c_str(), jsonColorObject);
                }
                json->PutExtAttr("colors", jsonColor->ToString().c_str(), filter);
            }
            return;
        }
        ToJsonColorHasValue(json, filter);
    }

    void ToJsonColorHasValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        auto jsonGradientColors = JsonUtil::CreateArray(true);
        if (propGradientColors_.has_value() && propValues_.has_value() &&
            (propGradientColors_.value().size() == propValues_.value().size())) {
            for (size_t i = 0; i < propValues_.value().size(); i++) {
                auto jsonObject = JsonUtil::CreateArray(true);
                auto jsonColor = JsonUtil::CreateArray(true);
                auto colorStopArray = propGradientColors_.value()[i];
                for (size_t j = 0; j < colorStopArray.size(); j++) {
                    auto jsonColorObject = JsonUtil::CreateArray(true);
                    jsonColorObject->Put("0", colorStopArray[j].first.ColorToString().c_str());
                    jsonColorObject->Put("1", std::to_string(colorStopArray[j].second.Value()).c_str());
                    auto indexStr = std::to_string(j);
                    jsonColor->Put(indexStr.c_str(), jsonColorObject);
                }
                jsonObject->Put("0", jsonColor);
                jsonObject->Put("1", propValues_.value()[i]);
                auto index = std::to_string(i);
                jsonGradientColors->Put(index.c_str(), jsonObject);
            }
        }
        json->PutExtAttr("colors", jsonGradientColors->ToString().c_str(), filter);
    }

    void ToJsonIndicator(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        if (!propIsShowIndicator_.value_or(true)) {
            json->PutExtAttr("indicator", "null", filter);
            return;
        }
        auto indicatorJsonValue = JsonUtil::Create(true);
        if (propIndicatorIconSourceInfo_.has_value()) {
            indicatorJsonValue->Put("icon", propIndicatorIconSourceInfo_.value().GetSrc().c_str());
        } else {
            indicatorJsonValue->Put("icon", "SystemStyle");
        }

        if (propIndicatorSpace_.has_value()) {
            indicatorJsonValue->Put("space", propIndicatorSpace_.value().ToString().c_str());
        } else {
            indicatorJsonValue->Put("space", INDICATOR_DISTANCE_TO_TOP.ToString().c_str());
        }
        json->PutExtAttr("indicator", indicatorJsonValue, filter);
    }

    void ToJsonTrackShadow(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        GaugeShadowOptions trackShadow;
        if (propShadowOptions_.has_value()) {
            trackShadow.radius = propShadowOptions_.value().radius;
            trackShadow.offsetX = propShadowOptions_.value().offsetX;
            trackShadow.offsetY = propShadowOptions_.value().offsetY;
            trackShadow.isShadowVisible = propShadowOptions_.value().isShadowVisible;
        } else {
            trackShadow.radius = DEFAULT_GAUGE_SHADOW_RADIUS;
            trackShadow.offsetX = DEFAULT_GAUGE_SHADOW_OFFSETX;
            trackShadow.offsetY = DEFAULT_GAUGE_SHADOW_OFFSETY;
        }

        if (!trackShadow.isShadowVisible) {
            json->PutExtAttr("trackShadow", "null", filter);
            return;
        }

        auto shadowOptionJson = JsonUtil::Create(true);
        shadowOptionJson->Put("radius", std::to_string(trackShadow.radius).c_str());
        shadowOptionJson->Put("offsetX", std::to_string(trackShadow.offsetX).c_str());
        shadowOptionJson->Put("offsetY", std::to_string(trackShadow.offsetY).c_str());

        json->PutExtAttr("trackShadow", shadowOptionJson, filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, float, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Min, float, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Max, float, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartAngle, float, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndAngle, float, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GaugeType, GaugeType, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Colors, std::vector<Color>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GradientColors, std::vector<ColorStopArray>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Values, std::vector<float>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShadowOptions, GaugeShadowOptions, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowIndicator, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorIconSourceInfo, ImageSourceInfo, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorSpace, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorChange, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsSensitive, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UseJsLinearGradient, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UseSpecialDefaultIndicator, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(GradientColorsInit, std::vector<ColorStopArray>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ColorModeInit, int, PROPERTY_UPDATE_RENDER);
    ACE_DISALLOW_COPY_AND_MOVE(GaugePaintProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_PAINT_PROPERTY_H
