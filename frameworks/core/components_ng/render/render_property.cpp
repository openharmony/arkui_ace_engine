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

#include "core/components_ng/render/render_property.h"

#include "core/common/ace_application_info.h"
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
} // namespace

#define ACE_OFFSET_API_NINE_TO_JSON(name)                            \
    auto json##name = JsonUtil::Create(true);                        \
    if (prop##name.has_value()) {                                    \
        json##name->Put("x", prop##name->GetX().ToString().c_str()); \
        json##name->Put("y", prop##name->GetY().ToString().c_str()); \
    } else {                                                         \
        json##name->Put("x", "0.0px");                               \
        json##name->Put("y", "0.0px");                               \
    }                                                                \


#define ACE_OFFSET_API_TEN_TO_JSON(name)                             \
    auto json##name = JsonUtil::Create(true);                        \
    if (prop##name.has_value()) {                                    \
        json##name->Put("x", prop##name->GetX().ToString().c_str()); \
        json##name->Put("y", prop##name->GetY().ToString().c_str()); \
    } else {                                                         \
        json##name->Put("x", "");                                    \
        json##name->Put("y", "");                                    \
    }                                                                \

void RenderPositionProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    ACE_OFFSET_API_TEN_TO_JSON(Position);
    json->Put("position", jsonPosition);

    auto context = PipelineContext::GetCurrentContext();
    // add version protection, null as default start from API 10 or higher
    if (context && context->GetMinPlatformVersion() > static_cast<int32_t>(PlatformVersion::VERSION_NINE)) {
        ACE_OFFSET_API_TEN_TO_JSON(Offset);
        json->Put("offset", jsonOffset);

        ACE_OFFSET_API_TEN_TO_JSON(Anchor);
        json->Put("markAnchor", jsonAnchor);
    } else {
        ACE_OFFSET_API_NINE_TO_JSON(Offset);
        json->Put("offset", jsonOffset);

        ACE_OFFSET_API_NINE_TO_JSON(Anchor);
        json->Put("markAnchor", jsonAnchor);
    }
}

void GraphicsProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("grayscale", propFrontGrayScale.has_value() ? propFrontGrayScale->Value() : 0.0);
    json->Put("brightness", propFrontBrightness.has_value() ? propFrontBrightness->Value() : 1.0);
    json->Put("saturate", propFrontSaturate.has_value() ? propFrontSaturate->Value() : 1.0);
    json->Put("contrast", propFrontContrast.has_value() ? propFrontContrast->Value() : 1.0);
    json->Put("invert", propFrontInvert.has_value() ? propFrontInvert->Value() : 0.0);
    json->Put("sepia", propFrontSepia.has_value() ? propFrontSepia->Value() : 0.0);
    json->Put("hueRotate", propFrontHueRotate.has_value() ? propFrontHueRotate.value() : 0.0);
    json->Put("colorBlend", propFrontColorBlend.has_value() ? propFrontColorBlend->ColorToString().c_str() : "");

    auto jsonShadow = JsonUtil::Create(true);
    auto shadow = propBackShadow.value_or(Shadow());
    if (shadow.GetStyle() == ShadowStyle::OuterDefaultXS) {
        json->Put("shadow", "ShadowStyle.OuterDefaultXS");
    } else if (shadow.GetStyle() == ShadowStyle::OuterDefaultSM) {
        json->Put("shadow", "ShadowStyle.OuterDefaultSM");
    } else if (shadow.GetStyle() == ShadowStyle::OuterDefaultMD) {
        json->Put("shadow", "ShadowStyle.OuterDefaultMD");
    } else if (shadow.GetStyle() == ShadowStyle::OuterDefaultLG) {
        json->Put("shadow", "ShadowStyle.OuterDefaultLG");
    } else if (shadow.GetStyle() == ShadowStyle::OuterFloatingSM) {
        json->Put("shadow", "ShadowStyle.OuterFloatingSM");
    } else if (shadow.GetStyle() == ShadowStyle::OuterFloatingMD) {
        json->Put("shadow", "ShadowStyle.OuterFloatingMD");
    } else {
        jsonShadow->Put("radius", std::to_string(shadow.GetBlurRadius()).c_str());
        jsonShadow->Put("color", shadow.GetColor().ColorToString().c_str());
        jsonShadow->Put("offsetX", std::to_string(shadow.GetOffset().GetX()).c_str());
        jsonShadow->Put("offsetY", std::to_string(shadow.GetOffset().GetY()).c_str());
        jsonShadow->Put("type", std::to_string(static_cast<int32_t>(shadow.GetShadowType())).c_str());
        json->Put("shadow", jsonShadow);
    }
}

void BackgroundProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    std::string backgroundImage = "NONE";
    if (propBackgroundImage.has_value()) {
        backgroundImage = propBackgroundImage->GetSrc() + ", " +
                          ImageRepeatToString(propBackgroundImageRepeat.value_or(ImageRepeat::NO_REPEAT));
    }
    json->Put("backgroundImage", backgroundImage.c_str());

    json->Put("backgroundImageSize",
        !propBackgroundImageSize.has_value() ? "ImageSize.Auto" : propBackgroundImageSize->ToString().c_str());

    if (propBackgroundImagePosition.has_value()) {
        json->Put("backgroundImagePosition", propBackgroundImagePosition->ToString().c_str());
    } else {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("x", 0.0);
        jsonValue->Put("y", 0.0);
        json->Put("backgroundImagePosition", jsonValue);
    }
    json->Put("backdropBlur", (propBlurRadius.value_or(Dimension(0))).ConvertToPx());
}

void CustomBackgroundProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    std::string backgroundPixelMap = "NONE";
    if (propBackgroundPixelMap.has_value()) {
        backgroundPixelMap = std::to_string(propBackgroundPixelMap.value()->GetWidth()) + ", " +
                          std::to_string(propBackgroundPixelMap.value()->GetHeight());
    }
    json->Put("backgroundPixelMap", backgroundPixelMap.c_str());
    json->Put("backgroundAlign", propBackgroundAlign.value().ToString().c_str());
}

void ForegroundProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("blur", (propBlurRadius.value_or(Dimension(0))).ConvertToPx());
}

void ClipProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    if (propClipShape.has_value()) {
        auto jsonClip = JsonUtil::Create(true);
        auto shape = propClipShape.value();
        auto shapeType = BasicShapeTypeToString(shape->GetBasicShapeType());
        if (!shapeType.empty()) {
            jsonClip->Put("shape", shapeType.c_str());
        }
        json->Put("clip", jsonClip->ToString().c_str());
    } else {
        json->Put("clip", propClipEdge.value_or(false) ? "true" : "false");
    }

    auto jsonMask = JsonUtil::Create(true);
    if (propClipMask.has_value()) {
        auto shape = propClipMask.value();
        auto shapeType = BasicShapeTypeToString(shape->GetBasicShapeType());
        if (!shapeType.empty()) {
            jsonMask->Put("shape", shapeType.c_str());
        }
    }
    json->Put("mask", jsonMask);
}

void GradientProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    if (propLinearGradient.has_value()) {
        json->Put("linearGradient", propLinearGradient->LinearGradientToJson());
    } else {
        json->Put("linearGradient", JsonUtil::Create(true));
    }

    if (propSweepGradient.has_value()) {
        json->Put("sweepGradient", propSweepGradient->SweepGradientToJson());
    } else {
        json->Put("sweepGradient", JsonUtil::Create(true));
    }

    if (propRadialGradient.has_value()) {
        json->Put("radialGradient", propRadialGradient->RadialGradientToJson());
    } else {
        json->Put("radialGradient", JsonUtil::Create(true));
    }
}

void TransformProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    const double halfDimension = 50.0;
    auto center = propTransformCenter.value_or(DimensionOffset(
        Dimension(halfDimension, DimensionUnit::PERCENT), Dimension(halfDimension, DimensionUnit::PERCENT)));
    if (propTransformRotate.has_value()) {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("x", std::to_string(propTransformRotate->x).c_str());
        jsonValue->Put("y", std::to_string(propTransformRotate->y).c_str());
        jsonValue->Put("z", std::to_string(propTransformRotate->z).c_str());
        jsonValue->Put("angle", std::to_string(propTransformRotate->w).c_str());
        jsonValue->Put("perspective", std::to_string(propTransformRotate->v).c_str());
        jsonValue->Put("centerX", center.GetX().ToString().c_str());
        jsonValue->Put("centerY", center.GetY().ToString().c_str());
        if (center.GetZ().has_value()) {
            jsonValue->Put("centerZ", center.GetZ().value().ToString().c_str());
        } else {
            json->Put("centerZ", JsonUtil::Create(true));
        }
        json->Put("rotate", jsonValue);
    } else {
        json->Put("rotate", JsonUtil::Create(true));
    }

    if (propTransformScale.has_value()) {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("x", std::to_string(propTransformScale->x).c_str());
        jsonValue->Put("y", std::to_string(propTransformScale->y).c_str());
        jsonValue->Put("centerX", center.GetX().ToString().c_str());
        jsonValue->Put("centerY", center.GetY().ToString().c_str());
        json->Put("scale", jsonValue);
    } else {
        json->Put("scale", JsonUtil::Create(true));
    }

    if (propTransformTranslate.has_value()) {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("x", propTransformTranslate->x.ToString().c_str());
        jsonValue->Put("y", propTransformTranslate->y.ToString().c_str());
        jsonValue->Put("z", propTransformTranslate->z.ToString().c_str());
        json->Put("translate", jsonValue);
    } else {
        json->Put("translate", JsonUtil::Create(true));
    }
}

void BorderProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    auto jsonBorder = JsonUtil::Create(true);

    propBorderStyle.value_or(BorderStyleProperty()).ToJsonValue(json, jsonBorder);
    propBorderColor.value_or(BorderColorProperty()).ToJsonValue(json, jsonBorder);
    propBorderWidth.value_or(BorderWidthProperty()).ToJsonValue(json, jsonBorder);
    propBorderRadius.value_or(BorderRadiusProperty()).ToJsonValue(json, jsonBorder);

    json->Put("border", jsonBorder->ToString().c_str());
}
} // namespace OHOS::Ace::NG
