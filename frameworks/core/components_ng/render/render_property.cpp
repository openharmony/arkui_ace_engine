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

#include "core/components_ng/render/render_property.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
std::string ImageRepeatToString(ImageRepeat type)
{
    static const LinearEnumMapNode<ImageRepeat, std::string> toStringMap[] = {
        { ImageRepeat::NO_REPEAT, "ImageRepeat.NoRepeat" },
        { ImageRepeat::REPEAT_X, "ImageRepeat.X" },
        { ImageRepeat::REPEAT_Y, "ImageRepeat.Y" },
        { ImageRepeat::REPEAT, "ImageRepeat.XY" },
    };
    auto idx = BinarySearchFindIndex(toStringMap, ArraySize(toStringMap), type);
    if (idx >= 0) {
        return toStringMap[idx].value;
    }
    return "ImageRepeat.NoRepeat";
}

std::string BasicShapeTypeToString(BasicShapeType type)
{
    static const LinearEnumMapNode<BasicShapeType, std::string> toStringMap[] = {
        { BasicShapeType::NONE, "None" },
        { BasicShapeType::INSET, "Inset" },
        { BasicShapeType::CIRCLE, "Circle" },
        { BasicShapeType::ELLIPSE, "Ellipse" },
        { BasicShapeType::POLYGON, "Polygon" },
        { BasicShapeType::PATH, "Path" },
        { BasicShapeType::RECT, "Rect" },
    };
    auto idx = BinarySearchFindIndex(toStringMap, ArraySize(toStringMap), type);
    if (idx >= 0) {
        return toStringMap[idx].value;
    }
    return "";
}

std::string LinearGradientBlurDirection(GradientDirection direction)
{
        static const LinearEnumMapNode<GradientDirection, std::string> toStringMap[] = {
        { GradientDirection::LEFT, "LEFT" },
        { GradientDirection::TOP, "LEFT" },
        { GradientDirection::RIGHT, "RIGHT" },
        { GradientDirection::BOTTOM, "BOTTOM" },
        { GradientDirection::LEFT_TOP, "LEFT_TOP" },
        { GradientDirection::LEFT_BOTTOM, "LEFT_BOTTOM" },
        { GradientDirection::RIGHT_TOP, "RIGHT_TOP" },
        { GradientDirection::RIGHT_BOTTOM, "RIGHT_BOTTOM" },
        { GradientDirection::NONE, "NONE" },
        { GradientDirection::START_TO_END, "START_TO_END" },
        { GradientDirection::END_TO_START, "END_TO_START" },
    };
    auto idx = BinarySearchFindIndex(toStringMap, ArraySize(toStringMap), direction);
    if (idx >= 0) {
        return toStringMap[idx].value;
    }
    return "";
}
} // namespace

#define ACE_OFFSET_API_NINE_TO_JSON(name)                            \
    auto json##name = JsonUtil::Create(true);                        \
    if (prop##name.has_value()) {                                    \
        json##name->Put("x", prop##name->GetX().ToString().c_str()); \
        json##name->Put("y", prop##name->GetY().ToString().c_str()); \
    } else {                                                         \
        json##name->Put("x", "0.0px");                               \
        json##name->Put("y", "0.0px");                               \
    }

#define ACE_OFFSET_API_TEN_TO_JSON(name)                             \
    auto json##name = JsonUtil::Create(true);                        \
    if (prop##name.has_value()) {                                    \
        json##name->Put("x", prop##name->GetX().ToString().c_str()); \
        json##name->Put("y", prop##name->GetY().ToString().c_str()); \
    } else {                                                         \
        json##name->Put("x", "");                                    \
        json##name->Put("y", "");                                    \
    }

#define ACE_OFFSET_EDGES(name)                                                                                      \
auto json##name = JsonUtil::Create(true);                                                                           \
if (prop##name.has_value()) {                                                                                       \
    json##name->Put("left", prop##name->left.has_value() ? prop##name->left.value().ToString().c_str() : "");       \
    json##name->Put("top", prop##name->top.has_value() ? prop##name->top.value().ToString().c_str() : "");          \
    json##name->Put("right", prop##name->right.has_value() ? prop##name->right.value().ToString().c_str() : "");    \
    json##name->Put("bottom", prop##name->bottom.has_value() ? prop##name->bottom.value().ToString().c_str() : ""); \
}

void RenderPositionProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    ACE_OFFSET_API_TEN_TO_JSON(Position);
    json->PutExtAttr("position", jsonPosition, filter);

    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    // add version protection, null as default start from API 10 or higher
    if (context && context->GetMinPlatformVersion() > static_cast<int32_t>(PlatformVersion::VERSION_NINE)) {
        if (propOffsetEdges.has_value()) {
            ACE_OFFSET_EDGES(OffsetEdges);
            json->PutExtAttr("offset", jsonOffsetEdges, filter);
        } else {
            ACE_OFFSET_API_TEN_TO_JSON(Offset);
            json->PutExtAttr("offset", jsonOffset, filter);
        }

        ACE_OFFSET_API_TEN_TO_JSON(Anchor);
        json->PutExtAttr("markAnchor", jsonAnchor, filter);
    } else {
        ACE_OFFSET_API_NINE_TO_JSON(Offset);
        json->PutExtAttr("offset", jsonOffset, filter);

        ACE_OFFSET_API_NINE_TO_JSON(Anchor);
        json->PutExtAttr("markAnchor", jsonAnchor, filter);
    }
}

void GraphicsProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("grayscale", propFrontGrayScale.has_value() ? propFrontGrayScale->Value() : 0.0, filter);
    json->PutExtAttr("brightness", propFrontBrightness.has_value() ? propFrontBrightness->Value() : 1.0, filter);
    json->PutExtAttr("saturate", propFrontSaturate.has_value() ? propFrontSaturate->Value() : 1.0, filter);
    json->PutExtAttr("contrast", propFrontContrast.has_value() ? propFrontContrast->Value() : 1.0, filter);
    json->PutExtAttr("sepia", propFrontSepia.has_value() ? propFrontSepia->Value() : 0.0, filter);
    json->PutExtAttr("hueRotate", propFrontHueRotate.has_value() ? propFrontHueRotate.value() : 0.0, filter);
    json->PutExtAttr("colorBlend",
        propFrontColorBlend.has_value() ? propFrontColorBlend->ColorToString().c_str() : "", filter);
    json->PutExtAttr("blendMode",
        propBackBlendMode.has_value() ? static_cast<uint16_t>(propBackBlendMode.value()) : 0, filter);
    json->PutExtAttr("dynamicDimming", propDynamicDimDegree.has_value() ?
        static_cast<float_t>(propDynamicDimDegree.value()) : 1.0f, filter);
    auto jsonBgBrightness = JsonUtil::Create(true);
    jsonBgBrightness->Put(
        "dynamicLightUpRate", propDynamicLightUpRate.has_value() ? propDynamicLightUpRate.value() : 0.0);
    jsonBgBrightness->Put(
        "dynamicLightUpDegree", propDynamicLightUpDegree.has_value() ? propDynamicLightUpDegree.value() : 0.0);
    json->PutExtAttr("BackgroundBrightness", jsonBgBrightness, filter);
    auto jsonShadow = JsonUtil::Create(true);
    auto shadow = propBackShadow.value_or(Shadow());
    if (shadow.GetStyle() == ShadowStyle::OuterDefaultXS) {
        json->PutExtAttr("shadow", "ShadowStyle.OuterDefaultXS", filter);
    } else if (shadow.GetStyle() == ShadowStyle::OuterDefaultSM) {
        json->PutExtAttr("shadow", "ShadowStyle.OuterDefaultSM", filter);
    } else if (shadow.GetStyle() == ShadowStyle::OuterDefaultMD) {
        json->PutExtAttr("shadow", "ShadowStyle.OuterDefaultMD", filter);
    } else if (shadow.GetStyle() == ShadowStyle::OuterDefaultLG) {
        json->PutExtAttr("shadow", "ShadowStyle.OuterDefaultLG", filter);
    } else if (shadow.GetStyle() == ShadowStyle::OuterFloatingSM) {
        json->PutExtAttr("shadow", "ShadowStyle.OuterFloatingSM", filter);
    } else if (shadow.GetStyle() == ShadowStyle::OuterFloatingMD) {
        json->PutExtAttr("shadow", "ShadowStyle.OuterFloatingMD", filter);
    } else {
        jsonShadow->Put("radius", std::to_string(shadow.GetBlurRadius()).c_str());
        if (shadow.GetShadowColorStrategy() == ShadowColorStrategy::AVERAGE) {
            jsonShadow->Put("color", "ColoringStrategy.AVERAGE");
        } else if (shadow.GetShadowColorStrategy() == ShadowColorStrategy::PRIMARY) {
            jsonShadow->Put("color", "ColoringStrategy.PRIMARY");
        } else {
            jsonShadow->Put("color", shadow.GetColor().ColorToString().c_str());
        }
        jsonShadow->Put("offsetX", std::to_string(shadow.GetOffset().GetX()).c_str());
        jsonShadow->Put("offsetY", std::to_string(shadow.GetOffset().GetY()).c_str());
        jsonShadow->Put("type", std::to_string(static_cast<int32_t>(shadow.GetShadowType())).c_str());
        jsonShadow->Put("fill", std::to_string(shadow.GetIsFilled()).c_str());
        json->PutExtAttr("shadow", jsonShadow, filter);
    }
    if (propFrontInvert.has_value()) {
        if (propFrontInvert->index() == 0) {
            json->PutExtAttr("invert", std::get<float>(propFrontInvert.value()), filter);
        } else {
            InvertOption option = std::get<InvertOption>(propFrontInvert.value());
            auto jsonInvert = JsonUtil::Create(true);
            jsonInvert->Put("low", option.low_);
            jsonInvert->Put("high", option.high_);
            jsonInvert->Put("threshold", option.threshold_);
            jsonInvert->Put("thresholdRange", option.thresholdRange_);
            json->PutExtAttr("invert", jsonInvert, filter);
        }
    }
    if (propLinearGradientBlur.has_value()) {
        auto jsonLinearGradientBlur = JsonUtil::Create(true);
        std::string value = propLinearGradientBlur->blurRadius_.ToString();
        jsonLinearGradientBlur->Put("value", value.c_str());
        auto options = JsonUtil::Create(true);
        std::string direction = LinearGradientBlurDirection(propLinearGradientBlur->direction_);
        options->Put("direction", direction.c_str());
        auto fractionStops = JsonUtil::CreateArray(true);
        int size = static_cast<int>(propLinearGradientBlur->fractionStops_.size());
        for (auto i = 0; i < size; i++) {
            auto fraction = propLinearGradientBlur->fractionStops_[i];
            std::string stop = std::to_string(fraction.first) + "," + std::to_string(fraction.second);
            fractionStops->Put(std::to_string(i).c_str(), stop.c_str());
        }
        options->Put("fractionStops", fractionStops);
        jsonLinearGradientBlur->Put("options", options);
        json->Put("linearGradientBlur", jsonLinearGradientBlur);
    }
    if (propFgDynamicBrightnessOption.has_value()) {
        propFgDynamicBrightnessOption->ToJsonValue(json, filter, "foregroundBrightness");
    }
    if (propBgDynamicBrightnessOption.has_value()) {
        propBgDynamicBrightnessOption->ToJsonValue(json, filter, "backgroundBrightnessInternal");
    }
}

void BackgroundProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    std::string backgroundImage = "NONE";
    if (propBackgroundImage.has_value()) {
        backgroundImage = propBackgroundImage->GetSrc() + ", " +
                          ImageRepeatToString(propBackgroundImageRepeat.value_or(ImageRepeat::NO_REPEAT));
    }
    json->PutExtAttr("backgroundImage", backgroundImage.c_str(), filter);

    json->PutExtAttr("backgroundImageSize", !propBackgroundImageSize.has_value() ?
        "ImageSize.Auto" : propBackgroundImageSize->ToString().c_str(), filter);

    if (propBackgroundImagePosition.has_value()) {
        json->PutExtAttr("backgroundImagePosition", propBackgroundImagePosition->ToString().c_str(), filter);
    } else {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("x", 0.0);
        jsonValue->Put("y", 0.0);
        json->PutExtAttr("backgroundImagePosition", jsonValue, filter);
    }
    json->PutExtAttr("backdropBlur", (propBlurRadius.value_or(Dimension(0))).ConvertToPx(), filter);
    json->PutExtAttr("backgroundImageResizable",
        propBackgroundImageResizableSlice.value_or(ImageResizableSlice()).ToString().c_str(), filter);
    if (propSysOptions.has_value()) {
        auto jsonBackgroundSysOption = JsonUtil::Create(true);
        jsonBackgroundSysOption->Put("disableSystemAdaptation", propSysOptions->disableSystemAdaptation);
        json->PutExtAttr("backgroundSysOptions", jsonBackgroundSysOption, filter);
    }
}

void CustomBackgroundProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    std::string backgroundPixelMap = "NONE";
    if (propBackgroundPixelMap.has_value()) {
        backgroundPixelMap = std::to_string(propBackgroundPixelMap.value()->GetWidth()) + ", " +
                             std::to_string(propBackgroundPixelMap.value()->GetHeight());
    }
    json->PutExtAttr("backgroundPixelMap", backgroundPixelMap.c_str(), filter);
    json->PutExtAttr("backgroundAlign", propBackgroundAlign.value().ToString().c_str(), filter);
    json->PutExtAttr(
        "customBackgroundColor", propCustomBackgroundColor.value_or(Color::TRANSPARENT).ToString().c_str(), filter);
}

void ForegroundProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("blur", (propBlurRadius.value_or(Dimension(0))).ConvertToPx(), filter);
    auto jsonOption = JsonUtil::Create(true);
    jsonOption->Put("radius", std::to_string(propForegroundEffect.value_or(0.0f)).c_str());
    json->PutExtAttr("foregroundEffect", jsonOption, filter);
    if (propMotionBlur.has_value()) {
        auto motionBlur = JsonUtil::Create(true);
        motionBlur->Put("radius", propMotionBlur->radius);
        auto motionBlurAnchor = JsonUtil::Create(true);
        motionBlurAnchor->Put("x", propMotionBlur->anchor.x);
        motionBlurAnchor->Put("y", propMotionBlur->anchor.y);
        motionBlur->Put("anchor", motionBlurAnchor);
        json->Put("motionBlur", motionBlur);
    }
    if (propSysOptionsForBlur.has_value()) {
        auto jsonForegroundSysOption = JsonUtil::Create(true);
        jsonForegroundSysOption->Put("disableSystemAdaptation", propSysOptionsForBlur->disableSystemAdaptation);
        json->PutExtAttr("foregroundSysOptions", jsonForegroundSysOption, filter);
    }
}

void ClipProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (propClipShape.has_value()) {
        auto jsonClip = JsonUtil::Create(true);
        auto shape = propClipShape.value();
        auto shapeType = BasicShapeTypeToString(shape->GetBasicShapeType());
        if (!shapeType.empty()) {
            jsonClip->Put("shape", shapeType.c_str());
        }
        json->PutExtAttr("clip", jsonClip->ToString().c_str(), filter);
    } else {
        json->PutExtAttr("clip", propClipEdge.value_or(false) ? "true" : "false", filter);
    }

    auto jsonMask = JsonUtil::Create(true);
    if (propClipMask.has_value()) {
        auto shape = propClipMask.value();
        auto shapeType = BasicShapeTypeToString(shape->GetBasicShapeType());
        if (!shapeType.empty()) {
            jsonMask->Put("shape", shapeType.c_str());
        }
    }
    json->PutExtAttr("mask", jsonMask, filter);
}

void GradientProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (propLinearGradient.has_value()) {
        json->PutExtAttr("linearGradient", GradientJsonUtils::LinearGradientToJson(*propLinearGradient), filter);
    } else {
        json->PutExtAttr("linearGradient", JsonUtil::Create(true), filter);
    }

    if (propSweepGradient.has_value()) {
        json->PutExtAttr("sweepGradient", GradientJsonUtils::SweepGradientToJson(*propSweepGradient), filter);
    } else {
        json->PutExtAttr("sweepGradient", JsonUtil::Create(true), filter);
    }

    if (propRadialGradient.has_value()) {
        json->PutExtAttr("radialGradient", GradientJsonUtils::RadialGradientToJson(*propRadialGradient), filter);
    } else {
        json->PutExtAttr("radialGradient", JsonUtil::Create(true), filter);
    }
}

void TransformProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    const double halfDimension = 50.0;
    auto center = propTransformCenter.value_or(DimensionOffset(
        Dimension(halfDimension, DimensionUnit::PERCENT), Dimension(halfDimension, DimensionUnit::PERCENT)));
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto transformRotate = HasTransformRotate() ? GetTransformRotateValue() : DEFAULT_ROTATE_VEC;
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("x", std::to_string(transformRotate.x).c_str());
    jsonValue->Put("y", std::to_string(transformRotate.y).c_str());
    jsonValue->Put("z", std::to_string(transformRotate.z).c_str());
    jsonValue->Put("angle", std::to_string(transformRotate.w).c_str());
    jsonValue->Put("perspective", std::to_string(transformRotate.v).c_str());
    jsonValue->Put("centerX", center.GetX().ToString().c_str());
    jsonValue->Put("centerY", center.GetY().ToString().c_str());
    auto centerZ = center.GetZ().value_or(Dimension());
    jsonValue->Put("centerZ", centerZ.ToString().c_str());
    json->PutExtAttr("rotate", jsonValue, filter);

    if (propTransformScale.has_value()) {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("x", std::to_string(propTransformScale->x).c_str());
        jsonValue->Put("y", std::to_string(propTransformScale->y).c_str());
        jsonValue->Put("centerX", center.GetX().ToString().c_str());
        jsonValue->Put("centerY", center.GetY().ToString().c_str());
        json->PutExtAttr("scale", jsonValue, filter);
    } else {
        json->PutExtAttr("scale", JsonUtil::Create(true), filter);
    }

    if (propTransformTranslate.has_value()) {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("x", propTransformTranslate->x.ToString().c_str());
        jsonValue->Put("y", propTransformTranslate->y.ToString().c_str());
        jsonValue->Put("z", propTransformTranslate->z.ToString().c_str());
        json->PutExtAttr("translate", jsonValue, filter);
    } else {
        json->PutExtAttr("translate", JsonUtil::Create(true), filter);
    }
}

void BorderProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto jsonBorder = JsonUtil::Create(true);
    propBorderStyle.value_or(BorderStyleProperty()).ToJsonValue(json, jsonBorder, filter);
    propBorderColor.value_or(BorderColorProperty()).ToJsonValue(json, jsonBorder, filter);
    propBorderWidth.value_or(BorderWidthProperty()).ToJsonValue(json, jsonBorder, filter);
    propBorderRadius.value_or(BorderRadiusProperty()).ToJsonValue(json, jsonBorder, filter);
    propDashGap.value_or(BorderWidthProperty()).ToDashJsonValue(json, jsonBorder, filter, "dashGap");
    propDashWidth.value_or(BorderWidthProperty()).ToDashJsonValue(json, jsonBorder, filter, "dashWidth");

    json->PutExtAttr("border", jsonBorder->ToString().c_str(), filter);
}

void OuterBorderProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto jsonOutline = JsonUtil::Create(true);
    propOuterBorderStyle.value_or(BorderStyleProperty()).ToJsonValue(json, jsonOutline, filter, true);
    propOuterBorderColor.value_or(BorderColorProperty()).ToJsonValue(json, jsonOutline, filter, true);
    propOuterBorderWidth.value_or(BorderWidthProperty()).ToJsonValue(json, jsonOutline, filter, true);
    propOuterBorderRadius.value_or(BorderRadiusProperty()).ToJsonValue(json, jsonOutline, filter, true);
    json->PutExtAttr("outline", jsonOutline->ToString().c_str(), filter);
}

void PointLightProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto jsonLightIntensity = JsonUtil::Create(true);
    auto lightSourceJSON = JsonUtil::Create(true);
    std::vector<std::string> strings = {
        "IlluminatedType.NONE",
        "IlluminatedType.BORDER",
        "IlluminatedType.CONTENT",
        "IlluminatedType.BORDER_CONTENT",
        "IlluminatedType.BLOOM_BORDER",
        "IlluminatedType.BLOOM_BORDER_CONTENT"
    };
    jsonLightIntensity->Put("lightIntensity", propLightIntensity.has_value() ? propLightIntensity.value() : 0.0);
    if (propLightPosition && propLightIntensity && propLightColor) {
        lightSourceJSON->Put("color", propLightColor.value_or(Color::WHITE).ColorToString().c_str());
        jsonLightIntensity->Put("lightSource", lightSourceJSON);
    } else {
        jsonLightIntensity->Put("lightSource", "No light source");
    }
    auto iiluminatedString = strings.at(propLightIlluminated.value_or(0)).c_str();
    jsonLightIntensity->Put("illuminated", iiluminatedString);
    jsonLightIntensity->Put("bloom", std::to_string(propBloom.value_or(0.0f)).c_str());
    json->PutExtAttr("pointLight", jsonLightIntensity, filter);

    if (propLightPosition.has_value()) {
        auto jsonLightPosition = JsonUtil::Create(true);
        jsonLightPosition->Put("x", propLightPosition->x.ToString().c_str());
        jsonLightPosition->Put("y", propLightPosition->y.ToString().c_str());
        jsonLightPosition->Put("z", propLightPosition->z.ToString().c_str());
        json->PutExtAttr("LightPosition", jsonLightPosition, filter);
    } else {
        json->PutExtAttr("LightPosition", JsonUtil::Create(true), filter);
    }
}
} // namespace OHOS::Ace::NG
