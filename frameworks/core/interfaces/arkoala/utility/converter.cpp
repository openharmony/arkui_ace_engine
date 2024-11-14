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

#include "converter.h"
#include "reverse_converter.h"
#include "core/components/theme/shadow_theme.h"
#include "core/interfaces/arkoala/utility/validators.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::NG {
std::optional<double> FloatToDouble(const std::optional<float>& src)
{
    return src ? std::optional(static_cast<double>(src.value())) : std::nullopt;
}
}
namespace OHOS::Ace::NG::Converter {
void AssignGradientColors(Gradient *gradient,
    const Array_Tuple_ResourceColor_Number *colors)
{
    for (int32_t i = 0; i < colors->length; i++) {
        auto color = OptConvert<Color>(colors->array[i].value0);
        auto position = Convert<float>(colors->array[i].value1);
        if (color.has_value()) {
            NG::GradientColor gradientColor;
            gradientColor.SetColor(color.value());
            gradientColor.SetHasValue(true);
            gradientColor.SetDimension(CalcDimension(position * Converter::PERCENT_100, DimensionUnit::PERCENT));
            gradient->AddColor(gradientColor);
        }
    }
}

void AssignLinearGradientDirection(std::shared_ptr<OHOS::Ace::NG::LinearGradient> linear,
    const GradientDirection &direction)
{
    switch (direction) {
        case GradientDirection::LEFT:
            linear->linearX = NG::GradientDirection::LEFT;
            break;
        case GradientDirection::RIGHT:
            linear->linearX = NG::GradientDirection::RIGHT;
            break;
        case GradientDirection::TOP:
            linear->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::BOTTOM:
            linear->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::LEFT_TOP:
            linear->linearX = NG::GradientDirection::LEFT;
            linear->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::LEFT_BOTTOM:
            linear->linearX = NG::GradientDirection::LEFT;
            linear->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::RIGHT_TOP:
            linear->linearX = NG::GradientDirection::RIGHT;
            linear->linearY = NG::GradientDirection::TOP;
            break;
        case GradientDirection::RIGHT_BOTTOM:
            linear->linearX = NG::GradientDirection::RIGHT;
            linear->linearY = NG::GradientDirection::BOTTOM;
            break;
        case GradientDirection::NONE:
        case GradientDirection::START_TO_END:
        case GradientDirection::END_TO_START:
        default:
            break;
    }
}

void AssignArkValue(Ark_Resource& dst, const Ark_Length& src)
{
    dst.id = ArkValue<Ark_Number>(src.resource);
    dst.type = ArkValue<Opt_Number>(static_cast<Ark_Int32>(NodeModifier::ResourceType::FLOAT));
    dst.params = ArkValue<Opt_Array_String>();
}

void AssignArkValue(Ark_TouchObject& touch, const OHOS::Ace::TouchLocationInfo& info)
{
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    Offset screenOffset = info.GetScreenLocation();

    touch.displayX.tag = Ark_Tag::ARK_TAG_FLOAT32;
    touch.displayX.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
    touch.displayY.tag = Ark_Tag::ARK_TAG_FLOAT32;
    touch.displayY.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));

    touch.id.tag = Ark_Tag::ARK_TAG_INT32;
    touch.id.i32 = static_cast<int32_t>(info.GetTouchDeviceId());

    touch.screenX.tag = Ark_Tag::ARK_TAG_FLOAT32;
    touch.screenX.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    touch.screenY.tag = Ark_Tag::ARK_TAG_FLOAT32;
    touch.screenY.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));

    touch.type = static_cast<Ark_TouchType>(info.GetTouchType());

    touch.windowX.tag = Ark_Tag::ARK_TAG_FLOAT32;
    touch.windowX.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    touch.windowY.tag = Ark_Tag::ARK_TAG_FLOAT32;
    touch.windowY.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));

    touch.x.tag = Ark_Tag::ARK_TAG_FLOAT32;
    touch.x.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    touch.y.tag = Ark_Tag::ARK_TAG_FLOAT32;
    touch.y.f32 = static_cast<float>(
        PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
}

void AssignArkValue(Ark_ClickEvent& onClick, const OHOS::Ace::GestureEvent& info)
{
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    Offset screenOffset = info.GetScreenLocation();

    onClick.axisHorizontal = ArkValue<Opt_Number>();
    onClick.axisVertical = ArkValue<Opt_Number>();
    onClick.displayX = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
    onClick.displayY = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));

    onClick.pressure = ArkValue<Ark_Number>(0.0f);

    onClick.screenX = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    onClick.screenY = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));

    onClick.source = static_cast<Ark_SourceType>(info.GetSourceDevice());

    onClick.sourceTool = static_cast<Ark_SourceTool>(0);
    onClick.deviceId = ArkValue<Opt_Number>();
    onClick.target.area.globalPosition.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
    onClick.target.area.globalPosition.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;
    onClick.target.area.position.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
    onClick.target.area.position.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;
    onClick.target.area.height = ArkValue<Ark_Length>(0);
    onClick.target.area.width = ArkValue<Ark_Length>(0);

    onClick.tiltX = ArkValue<Ark_Number>(0);
    onClick.tiltY = ArkValue<Ark_Number>(0);

    onClick.timestamp = ArkValue<Ark_Number>(
        static_cast<float>(info.GetTimeStamp().time_since_epoch().count()));

    onClick.windowX = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    onClick.windowY = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));

    onClick.x = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    onClick.y = ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
}

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
    constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;

    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

ResourceConverter::ResourceConverter(const Ark_Resource& resource)
{
    if (resource.id.tag == ARK_TAG_INT32) {
        id_ = resource.id.i32;
        type_ = static_cast<NodeModifier::ResourceType>(OptConvert<int>(resource.type).value_or(0));
        bundleName_ = Convert<std::string>(resource.bundleName);
        moduleName_ = Convert<std::string>(resource.moduleName);
        if (resource.params.tag != ARK_TAG_UNDEFINED) {
            for (int i = 0; i < resource.params.value.length; i++) {
                params_.emplace_back(resource.params.value.array[i].chars);
            }
        }

        themeConstants_ = NodeModifier::GetThemeConstants(nullptr, bundleName_.c_str(), moduleName_.c_str());
    } else {
        LOGE("ResourceConverter illegal id tag: id.tag = %{public}d", resource.id.tag);
    }
}

std::optional<std::string> ResourceConverter::ToString()
{
    std::optional<std::string> result;
    CHECK_NULL_RETURN(themeConstants_, result);

    switch (type_) {
        case NodeModifier::ResourceType::STRING:
            if (id_ != -1) {
                result = themeConstants_->GetString(id_);
            } else if (!params_.empty()) {
                result = themeConstants_->GetStringByName(params_.front());
            } else {
                LOGE("Unknown resource value OHOS::Ace::NG::Converter::ResourceConverter");
            }
            break;

        case NodeModifier::ResourceType::RAWFILE:
            if (params_.size() > 0) {
                result = themeConstants_->GetRawfile(params_[0]);
            }
            break;

        case NodeModifier::ResourceType::MEDIA:
            if (id_ != -1) {
                result = themeConstants_->GetMediaPath(id_);
            } else if (params_.size() > 0) {
                result = themeConstants_->GetMediaPathByName(params_[0]);
            }
            break;

        default:
            break;
    }
    return result;
}

std::optional<StringArray> ResourceConverter::ToStringArray()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == NodeModifier::ResourceType::STRARRAY) {
        if (id_ != -1) {
            return themeConstants_->GetStringArray(id_);
        } else if (params_.size() > 0) {
            return themeConstants_->GetStringArrayByName(params_.front());
        } else {
            LOGE("Unknown STRARRAY value OHOS::Ace::NG::Converter::ResourceConverter");
        }
    }
    return std::nullopt;
}

std::optional<StringArray> ResourceConverter::ToFontFamilies()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == NodeModifier::ResourceType::STRING) {
        std::optional<std::string> str;
        if (id_ != -1) {
            str = themeConstants_->GetString(id_);
        } else if (!params_.empty()) {
            str = themeConstants_->GetStringByName(params_.front());
        } else {
            LOGE("ResourceConverter::ToFontFamilies Unknown resource value");
        }
        if (str.has_value()) {
            return Framework::ConvertStrToFontFamilies(str.value());
        }
    } else if (type_ == NodeModifier::ResourceType::STRARRAY) {
        LOGE("ResourceConverter::ToFontFamilies Support of ResourceType::STRARRAY type is not implemented");
    } else {
        LOGE("ResourceConverter::ToFontFamilies Resource type is not supported");
    }
    return std::nullopt;
}

std::optional<Dimension> ResourceConverter::ToDimension()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == NodeModifier::ResourceType::FLOAT) {
        if (id_ == -1 && !params_.empty()) {
            return themeConstants_->GetDimensionByName(params_.front());
        }
        if (id_ != -1) {
            return themeConstants_->GetDimension(id_);
        }
        LOGE("ResourceConverter::ToDimension Unknown resource value");
    }
    return std::nullopt;
}

std::optional<CalcLength> ResourceConverter::ToCalcLength()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == NodeModifier::ResourceType::STRING) {
        if (id_ != -1) {
            return CalcLength(themeConstants_->GetString(id_));
        }
        if (!params_.empty()) {
            return CalcLength(themeConstants_->GetStringByName(params_.front()));
        }
        LOGE("ResourceConverter::ToCalcLength Unknown resource value");
        return std::nullopt;
    }
    auto dimOpt = ToDimension();
    return dimOpt ? std::make_optional(CalcLength(*dimOpt)) : std::nullopt;
}

std::optional<float> ResourceConverter::ToFloat()
{
    std::optional<float> optFloat = std::nullopt;
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == NodeModifier::ResourceType::FLOAT) {
        if (id_ == -1 && params_.size() > 0) {
            optFloat = static_cast<float>(themeConstants_->GetDoubleByName(params_[0]));
        } else {
            optFloat = static_cast<float>(themeConstants_->GetDouble(id_));
        }
    }
    return optFloat;
}

std::optional<int32_t> ResourceConverter::ToInt()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == NodeModifier::ResourceType::INTEGER) {
        return themeConstants_->GetInt(id_);
    }
    return std::nullopt;
}

std::optional<uint32_t> ResourceConverter::ToSymbol()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (id_ == -1 && !params_.empty()) {
        return themeConstants_->GetSymbolByName(params_.front().c_str());
    }
    return std::nullopt;
}

std::optional<Color> ResourceConverter::ToColor()
{
    std::optional<Color> result;
    CHECK_NULL_RETURN(themeConstants_, result);
    if (id_ == -1 && params_.size() > 0) {
        result = themeConstants_->GetColorByName(params_[0]);
        return result;
    }

    switch (type_) {
        case NodeModifier::ResourceType::STRING: {
            Color color;
            if (Color::ParseColorString(themeConstants_->GetString(id_), color)) {
                result = color;
            }
            break;
        }

        case NodeModifier::ResourceType::INTEGER:
            result = Color(ColorAlphaAdapt(themeConstants_->GetInt(id_)));
            break;

        case NodeModifier::ResourceType::COLOR:
            result = themeConstants_->GetColor(id_);
            break;

        default:
            break;
    }

    return result;
}

template<>
Shadow Convert(const Ark_ShadowOptions& src)
{
    Shadow shadow;

    auto radius = Converter::OptConvert<float>(src.radius);
    if (radius) {
        shadow.SetBlurRadius(radius.value());
    }

    auto shadowType = Converter::OptConvert<ShadowType>(src.type);
    if (shadowType) {
        shadow.SetShadowType(shadowType.value());
    }

    auto color = Converter::OptConvert<Color>(src.color);
    if (color) {
        shadow.SetColor(color.value());
    }

    auto colorStrategy = Converter::OptConvert<ShadowColorStrategy>(src.color);
    if (colorStrategy) {
        shadow.SetShadowColorStrategy(colorStrategy.value());
    }

    auto offsetX = Converter::OptConvert<float>(src.offsetX);
    if (offsetX) {
        shadow.SetOffsetX(offsetX.value());
    }

    auto offsetY = Converter::OptConvert<float>(src.offsetY);
    if (offsetY) {
        shadow.SetOffsetY(offsetY.value());
    }

    auto fill = Converter::OptConvert<bool>(src.fill);
    if (fill) {
        shadow.SetIsFilled(fill.value());
    }

    return shadow;
}

template<>
std::vector<Shadow> Convert(const Ark_ShadowOptions& src)
{
    return { Convert<Shadow>(src) };
}

template<>
StringArray Convert(const Ark_String& src)
{
    auto familiesStr = Convert<std::string>(src);
    return Framework::ConvertStrToFontFamilies(familiesStr);
}

template<>
StringArray Convert(const std::string& src)
{
    return Framework::ConvertStrToFontFamilies(src);
}

template<>
Font Convert(const Ark_Font& src)
{
    Font font;
    auto fontFamilies = OptConvert<std::vector<std::string>>(src.family);
    if (fontFamilies) {
        font.fontFamilies = fontFamilies.value();
    }
    auto fontSize = OptConvert<Dimension>(src.size);
    if (fontSize) {
        Validator::ValidatePositive(fontSize);
        Validator::ValidateNonPercent(fontSize);
        font.fontSize = fontSize;
    }
    auto weight = OptConvert<FontWeight>(src.weight);
    if (weight) {
        font.fontWeight = weight;
    }
    font.fontStyle = OptConvert<OHOS::Ace::FontStyle>(src.style);
    return font;
}

template<>
CaretStyle Convert(const Ark_CaretStyle& src)
{
    CaretStyle caretStyle;
    caretStyle.color = OptConvert<Color> (src.color);
    caretStyle.width = OptConvert<Dimension> (src.width);
    return caretStyle;
}

template<>
TextDecorationOptions Convert(const Ark_TextDecorationOptions& src)
{
    TextDecorationOptions options;
    options.textDecoration = OptConvert<TextDecoration>(src.type);
    options.color = OptConvert<Color>(src.color);
    options.textDecorationStyle = OptConvert<TextDecorationStyle>(src.style);
    return options;
}

template<>
ListItemIndex Convert(const Ark_VisibleListContentInfo& src)
{
    auto itemIndex = ListItemIndex{.index = Convert<int32_t>(src.index)}; // a struct is initialized by default
    auto itemGroupArea = OptConvert<ListItemGroupArea>(src.itemGroupArea);
    if (itemGroupArea.has_value()) {
        itemIndex.area = static_cast<int32_t>(itemGroupArea.value());
    }
    auto indexInGroup = OptConvert<int32_t>(src.itemIndexInGroup);
    if (indexInGroup.has_value()) {
        itemIndex.indexInGroup = indexInGroup.value();
    }
    return itemIndex;
}

template<>
std::pair<Dimension, Dimension> Convert(const Ark_LengthConstrain& src)
{
    auto minLength = Convert<Dimension>(src.minLength);
    auto maxLength = Convert<Dimension>(src.maxLength);
    return {minLength, maxLength};
}

template<>
ItemDragInfo Convert(const Ark_ItemDragInfo& src)
{
    ItemDragInfo itemDragInfo;
    itemDragInfo.SetX(Convert<float>(src.x));
    itemDragInfo.SetY(Convert<float>(src.y));
    return itemDragInfo;
}

template<>
void AssignCast(std::optional<FontWeight>& dst, const Ark_Number& src)
{
    auto intVal = src.tag == Ark_Tag::ARK_TAG_INT32 ? src.i32 : static_cast<int32_t>(src.f32);
    if (intVal >= 0) {
        auto strVal = std::to_string(intVal);
        if (auto [parseOk, val] = StringUtils::ParseFontWeight(strVal); parseOk) {
            dst = val;
        }
    }
}

template<>
void AssignCast(std::optional<FontWeight>& dst, const Ark_String& src)
{
    if (auto [parseOk, val] = StringUtils::ParseFontWeight(src.chars); parseOk) {
        dst = val;
    }
}

template<>
RefPtr<Curve> Convert(const Ark_String& src)
{
    return Framework::CreateCurve(Converter::Convert<std::string>(src), false);
}

template<>
RefPtr<Curve> Convert(const Ark_Curve& src)
{
    return Framework::CreateCurve(src, false);
}

template<>
RefPtr<Curve> Convert(const Ark_ICurve& src)
{
    LOGE("Convert [Ark_ICurve] to [RefPtr<Curve>] is not supported");
    return nullptr;
}

template<>
RefPtr<FrameRateRange> Convert(const Ark_ExpectedFrameRateRange& src)
{
    int32_t fRRmin = Converter::Convert<int32_t>(src.min);
    int32_t fRRmax = Converter::Convert<int32_t>(src.max);
    int32_t fRRExpected = Converter::Convert<int32_t>(src.expected);

    return AceType::MakeRefPtr<FrameRateRange>(fRRmin, fRRmax, fRRExpected);
}

template<>
void AssignCast(std::optional<float>& dst, const Ark_String& src)
{
    auto value = Convert<std::string>(src);
    double result;
    if (StringUtils::StringToDouble(value, result)) {
        dst = result;
    }
}

template<>
Dimension Convert(const Ark_Length& src)
{
    if (src.type == Ark_Tag::ARK_TAG_RESOURCE) {
        auto resource = ArkValue<Ark_Resource>(src);
        ResourceConverter converter(resource);
        return converter.ToDimension().value_or(Dimension());
    } else {
        auto unit = static_cast<OHOS::Ace::DimensionUnit>(src.unit);
        auto value = src.value;
        if (unit == OHOS::Ace::DimensionUnit::PERCENT) {
            value /= 100.0f; // percent is normalized [0..1]
        }
        return Dimension(value, unit);
    }
}

template<>
Dimension Convert(const Ark_LengthMetrics& src)
{
    auto unit = OptConvert<DimensionUnit>(src.unit).value_or(DimensionUnit::VP);
    auto value = Convert<float>(src.value);
    if (unit == DimensionUnit::PERCENT) {
        value /= 100.0f; // percent is normalized [0..1]
    }
    return Dimension(value, unit);
}

template<>
DimensionRect Convert(const Ark_Rectangle &src)
{
    DimensionRect dst;
    if (auto dim = OptConvert<Dimension>(src.width); dim) {
        Validator::ValidateNonNegative(dim);
        if (dim) {
            dst.SetWidth(*dim);
        }
    }
    if (auto dim = OptConvert<Dimension>(src.height); dim) {
        Validator::ValidateNonNegative(dim);
        if (dim) {
            dst.SetHeight(*dim);
        }
    }
    auto offset = dst.GetOffset();
    if (auto dim = OptConvert<Dimension>(src.x); dim) {
        offset.SetX(*dim);
    }
    if (auto dim = OptConvert<Dimension>(src.y); dim) {
        offset.SetY(*dim);
    }
    dst.SetOffset(offset);
    return dst;
}

template<>
PaddingProperty Convert(const Ark_Padding& src)
{
    PaddingProperty padding;
    padding.left = Converter::OptConvert<CalcLength>(src.left);
    padding.top = Converter::OptConvert<CalcLength>(src.top);
    padding.right = Converter::OptConvert<CalcLength>(src.right);
    padding.bottom = Converter::OptConvert<CalcLength>(src.bottom);
    return padding;
}

template<>
PaddingProperty Convert(const Ark_LocalizedPadding& src)
{
    return PaddingProperty {
        .top = Converter::OptConvert<CalcLength>(src.top),
        .bottom = Converter::OptConvert<CalcLength>(src.bottom),
        .start = Converter::OptConvert<CalcLength>(src.start),
        .end = Converter::OptConvert<CalcLength>(src.end)
    };
}

template<>
AnimateParam Convert(const Ark_AnimateParam& src)
{
    AnimateParam option;
    option.duration = Converter::OptConvert<int32_t>(src.duration);
    option.delay = Converter::OptConvert<int32_t>(src.delay);
    option.iterations = Converter::OptConvert<int32_t>(src.iterations);
    option.tempo = Converter::OptConvert<float>(src.tempo);
    option.direction = Converter::OptConvert<AnimationDirection>(src.playMode);
    option.finishCallbackType = Converter::OptConvert<FinishCallbackType>(src.finishCallbackType);
    option.curve = Converter::OptConvert<RefPtr<Curve>>(src.curve);
    option.frameRateRange = Converter::OptConvert<RefPtr<FrameRateRange>>(src.expectedFrameRateRange);
    return option;
}

template<>
BorderColorProperty Convert(const Ark_EdgeColors& src)
{
    BorderColorProperty dst;
    dst.leftColor = OptConvert<Color>(src.left);
    dst.topColor = OptConvert<Color>(src.top);
    dst.rightColor = OptConvert<Color>(src.right);
    dst.bottomColor = OptConvert<Color>(src.bottom);
    dst.multiValued = true;
    return dst;
}

template<>
BorderRadiusProperty Convert(const Ark_BorderRadiuses& src)
{
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Converter::OptConvert<Dimension>(src.topLeft);
    Validator::ValidateNonNegative(borderRadius.radiusTopLeft);
    borderRadius.radiusTopRight = Converter::OptConvert<Dimension>(src.topRight);
    Validator::ValidateNonNegative(borderRadius.radiusTopRight);
    borderRadius.radiusBottomLeft = Converter::OptConvert<Dimension>(src.bottomLeft);
    Validator::ValidateNonNegative(borderRadius.radiusBottomLeft);
    borderRadius.radiusBottomRight = Converter::OptConvert<Dimension>(src.bottomRight);
    Validator::ValidateNonNegative(borderRadius.radiusBottomRight);
    borderRadius.multiValued = true;
    return borderRadius;
}

template<>
BorderRadiusProperty Convert(const Ark_Length& src)
{
    BorderRadiusProperty dst;
    dst.multiValued = false;
    if (auto radius = Converter::Convert<Dimension>(src); !radius.IsNegative()) {
        dst.SetRadius(radius);
    }
    return dst;
}

template<>
BorderWidthProperty Convert(const Ark_Length& src)
{
    BorderWidthProperty dst;
    if (auto width = Converter::Convert<Dimension>(src); !width.IsNegative()) {
        dst.SetBorderWidth(width);
        dst.multiValued = false;
    }
    return dst;
}

template<>
BorderWidthProperty Convert(const Ark_EdgeWidths& src)
{
    BorderWidthProperty widthProperty;
    widthProperty.topDimen = Converter::OptConvert<Dimension>(src.top);
    Validator::ValidateNonNegative(widthProperty.topDimen);
    widthProperty.leftDimen = Converter::OptConvert<Dimension>(src.left);
    Validator::ValidateNonNegative(widthProperty.leftDimen);
    widthProperty.bottomDimen = Converter::OptConvert<Dimension>(src.bottom);
    Validator::ValidateNonNegative(widthProperty.bottomDimen);
    widthProperty.rightDimen = Converter::OptConvert<Dimension>(src.right);
    Validator::ValidateNonNegative(widthProperty.rightDimen);
    widthProperty.multiValued = true;
    return widthProperty;
}

template<>
BorderWidthProperty Convert(const Ark_LengthMetrics& src)
{
    BorderWidthProperty dst;
    LOGE("Convert [Ark_LengthMetrics] to [BorderWidthProperty] is not implemented yet");
    return dst;
}

template<>
CalcLength Convert(const Ark_Length& src)
{
    if (src.type == Ark_Tag::ARK_TAG_RESOURCE) {
        auto resource = ArkValue<Ark_Resource>(src);
        ResourceConverter converter(resource);
        return converter.ToCalcLength().value_or(CalcLength());
    }
    return CalcLength(Convert<Dimension>(src));
}

template<>
CalcLength Convert(const Ark_LengthMetrics& src)
{
    return CalcLength(Convert<Dimension>(src));
}

template<>
void AssignCast(std::optional<Color>& dst, const Ark_String& src)
{
    Color result;
    auto color = Convert<std::string>(src);
    if (Color::ParseColorString(color, result)) {
        dst = result;
    }
}

template<>
TextBackgroundStyle Convert(const Ark_TextBackgroundStyle& src)
{
    TextBackgroundStyle dst;
    dst.backgroundColor = Converter::OptConvert<Color>(src.color);
    dst.backgroundRadius = Converter::OptConvert<NG::BorderRadiusProperty>(src.radius);
    if (dst.backgroundRadius.has_value()) {
        Validator::ValidateNonPercent(dst.backgroundRadius->radiusTopLeft);
        Validator::ValidateNonPercent(dst.backgroundRadius->radiusTopRight);
        Validator::ValidateNonPercent(dst.backgroundRadius->radiusBottomLeft);
        Validator::ValidateNonPercent(dst.backgroundRadius->radiusBottomRight);
    }
    return dst;
}

template<>
PickerTextStyle Convert(const Ark_PickerTextStyle& src)
{
    PickerTextStyle style;
    style.textColor = OptConvert<Color>(src.color);
    auto font = OptConvert<Font>(src.font);
    if (font.has_value()) {
        style.fontSize = font->fontSize;
        style.fontFamily = font->fontFamilies;
        style.fontWeight = font->fontWeight;
        style.fontStyle = font->fontStyle;
    }
    return style;
}

template<>
void AssignTo(std::optional<BorderColorProperty> &dst, const Ark_ResourceColor& src)
{
    if (auto colorOpt = OptConvert<Color>(src); colorOpt) {
        if (!dst) {
            dst = BorderColorProperty();
        }
        dst->SetColor(*colorOpt);
    }
}

template<>
void AssignCast(std::optional<Shadow>& dst, const Ark_ShadowStyle& src)
{
    auto colorMode = SystemProperties::GetColorMode();
    ShadowStyle shadowStyle = Converter::OptConvert<ShadowStyle>(src).value_or(ShadowStyle::None);
    if (shadowStyle == ShadowStyle::None) {
        return;
    }

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);

    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    if (!shadowTheme) {
        return;
    }

    dst = shadowTheme->GetShadow(shadowStyle, colorMode);
}

template<>
void AssignCast(std::optional<SymbolData>& dst, const Ark_Resource& src)
{
    ResourceConverter converter(src);
    if (!dst) {
        dst = SymbolData();
    }
    dst->symbol = converter.ToSymbol();
}

template<>
void AssignCast(std::optional<UserUnderlineColor>& dst, const Ark_UnderlineColor& src)
{
    dst = UserUnderlineColor();
    dst->typing = Converter::OptConvert<Color>(src.typing);
    dst->normal = Converter::OptConvert<Color>(src.normal);
    dst->error = Converter::OptConvert<Color>(src.error);
    dst->disable = Converter::OptConvert<Color>(src.disable);
}
} // namespace OHOS::Ace::NG::Converter
