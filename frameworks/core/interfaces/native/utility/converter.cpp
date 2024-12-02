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
#include "core/interfaces/native/utility/validators.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace {
    constexpr int32_t NUM_0 = 0;
    constexpr int32_t NUM_1 = 1;
    constexpr int32_t NUM_2 = 2;
    constexpr int32_t NUM_3 = 3;
    constexpr int32_t NUM_4 = 4;
    constexpr int32_t STD_TM_START_YEAR = 1900;
} // namespace

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

void stubCall(const Ark_Int32 _) {}
void stubHoldRelease(Ark_Int32 _) {}

void AssignArkValue(Ark_Length& dst, const std::string& src)
{
    char *suffixPtr = nullptr;
    dst.type = ARK_TAG_FLOAT32;
    dst.value = std::strtof(src.c_str(), &suffixPtr);
    dst.unit = -NUM_1;
    if (!suffixPtr || suffixPtr == src.c_str()) { return; }
    if (suffixPtr[NUM_0] == '\0' || (suffixPtr[NUM_0] == 'v' && suffixPtr[NUM_1] == 'p')) {
        dst.unit = NUM_1;
    } else if (suffixPtr[NUM_0] == '%') {
        dst.unit = NUM_3;
    } else if (suffixPtr[NUM_0] == 'p' && suffixPtr[NUM_1] == 'x') {
        dst.unit = NUM_0;
    } else if (suffixPtr[NUM_0] == 'l' && suffixPtr[NUM_1] == 'p' && suffixPtr[NUM_2] == 'x') {
        dst.unit = NUM_4;
    } else if (suffixPtr[NUM_0] == 'f' && suffixPtr[NUM_1] == 'p') {
        dst.unit = NUM_2;
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

    onClick.preventDefault = {
        { 0, stubHoldRelease, stubHoldRelease },
        stubCall,
    };
}

void AssignArkValue(Ark_Date& dst, const PickerDate& src)
{
    const auto start = PickerDate(1970, 1, 1);
    const auto end = PickerDate(2100, 12, 31);
    const int64_t SEC_TO_MILLISEC = 1000;
    auto date = src;
    if (src.GetYear() < start.GetYear() || src.GetYear() > end.GetYear()) {
        date = start;
    } else if (src.GetMonth() < start.GetMonth() || src.GetMonth() > end.GetMonth()) {
        date = start;
    } else if (src.GetDay() < start.GetDay() || src.GetDay() > PickerDate::GetMaxDay(src.GetYear(), src.GetMonth())) {
        date = start;
    }
    std::tm tm {};
    tm.tm_year = date.GetYear() - STD_TM_START_YEAR; // tm_year is years since 1900
    tm.tm_mon = date.GetMonth() - 1; // tm_mon from 0 to 11
    tm.tm_mday = date.GetDay();
    time_t time = std::mktime(&tm);
    dst = reinterpret_cast<Ark_Date>(time * SEC_TO_MILLISEC);
}

void AssignArkValue(Ark_ImageError& dst, const LoadImageFailEvent& src)
{
    dst.componentWidth = Converter::ArkValue<Ark_Number>(src.GetComponentWidth());
    dst.componentHeight = Converter::ArkValue<Ark_Number>(src.GetComponentHeight());
    dst.message = Converter::ArkValue<Ark_String>(src.GetErrorMessage());
}

void AssignArkValue(Ark_ImageLoadResult& dst, const LoadImageSuccessEvent& src)
{
    dst.width = Converter::ArkValue<Ark_Number>(src.GetWidth());
    dst.height = Converter::ArkValue<Ark_Number>(src.GetHeight());
    dst.componentWidth = Converter::ArkValue<Ark_Number>(src.GetComponentWidth());
    dst.componentHeight = Converter::ArkValue<Ark_Number>(src.GetComponentHeight());
    dst.loadingStatus = Converter::ArkValue<Ark_Number>(src.GetLoadingStatus());
    dst.contentWidth = Converter::ArkValue<Ark_Number>(src.GetContentWidth());
    dst.contentHeight = Converter::ArkValue<Ark_Number>(src.GetContentHeight());
    dst.contentOffsetX = Converter::ArkValue<Ark_Number>(src.GetContentOffsetX());
    dst.contentOffsetY = Converter::ArkValue<Ark_Number>(src.GetContentOffsetY());
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
            if (!params_.empty()) {
                result = themeConstants_->GetRawfile(params_.front());
            }
            break;

        case NodeModifier::ResourceType::MEDIA:
            if (id_ != -1) {
                result = themeConstants_->GetMediaPath(id_);
            } else if (!params_.empty()) {
                result = themeConstants_->GetMediaPathByName(params_.front());
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
        return ToStringArray();
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
SelectionOptions Convert(const Ark_SelectionOptions& options)
{
    SelectionOptions selectionOptions;
    auto menuPolicy = OptConvert<MenuPolicy>(options.menuPolicy);
    if (menuPolicy) {
        selectionOptions.menuPolicy = *menuPolicy;
    }
    return selectionOptions;
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
std::u16string Convert(const Ark_String& src)
{
    auto str8 =  Converter::Convert<std::string>(src);
    return UtfUtils::Str8ToStr16(str8);
}

template<>
std::vector<Shadow> Convert(const Ark_ShadowOptions& src)
{
    return { Convert<Shadow>(src) };
}

template<>
Dimension Convert(const Ark_String& src)
{
    auto str = Convert<std::string>(src);
    return Dimension::FromString(str);
}

template<>
CalcDimension Convert(const Ark_Length& src)
{
    return Convert<Dimension>(src);
}

template<>
CalcDimension Convert(const Ark_String& src)
{
    auto str = Convert<std::string>(src);
    if (!str.empty()) {
        char firstChar = str[0];
        if (firstChar < '0' || firstChar > '9') {
            return CalcDimension(str);
        }
    }
    return Dimension::FromString(str);
}

template<>
CalcDimension Convert(const Ark_Number& src)
{
    return Convert<Dimension>(src);
}

template<>
std::pair<Dimension, Dimension> Convert(const Ark_Tuple_Dimension_Dimension& src)
{
    return { Converter::Convert<Dimension>(src.value0), Converter::Convert<Dimension>(src.value1) };
}

template<>
Dimension Convert(const Ark_Number& src)
{
    return Dimension(Converter::Convert<float>(src), DimensionUnit::VP);
}

template<>
int Convert(const Ark_IlluminatedType& src)
{
    return static_cast<int>(src);
}

template<>
StringArray Convert(const Ark_CustomObject& src)
{
    LOGE("Convert [Ark_CustomObject] to [StringArray] is not supported");
    return StringArray();
}

template<>
Color Convert(const Ark_Number& src)
{
    uint32_t value = static_cast<uint32_t>(Convert<int>(src));
    return Color((value <= 0xFFFFFF && value > 0) ? value + 0xFF000000U : value);
}

template<>
Color Convert(const Ark_String& src)
{
    return Color::FromString(src.chars);
}

template<>
std::tuple<Ark_Float32, Ark_Int32> Convert(const Ark_String& src)
{
    auto str = Convert<std::string>(src);
    auto dimension = Dimension::FromString(str);
    return std::make_tuple(dimension.Value(), static_cast<Ark_Int32>(dimension.Unit()));
}

template<>
Ark_CharPtr Convert(const Ark_Undefined& src)
{
    return "";
}

template<>
Ark_CharPtr Convert(const Ark_Function& src)
{
    LOGE("Convert [Ark_Function/CustomBuilder] to [Ark_CharPtr] is not valid.");
    return "";
}

template<>
Ark_CharPtr Convert(const Ark_CustomObject& src)
{
    LOGE("Convert [Ark_CustomObject] to [Ark_CharPtr] is not valid.");
    return "";
}

template<>
int Convert(const Ark_String& src)
{
    float value = std::atoi(src.chars);
    return value;
}

template<>
float Convert(const Ark_String& src)
{
    char *end = nullptr;
    float value = std::strtof(src.chars, &end);
    return value;
}

template<>
float Convert(const Ark_Float32& src)
{
    return src;
}

template<>
Shadow Convert(const Ark_Int32& src)
{
    Shadow shadow;
    shadow.SetBlurRadius(src);
    return shadow;
}

template<>
EdgesParam Convert(const Ark_Edges& src)
{
    EdgesParam edges;
    edges.left = OptConvert<Dimension>(src.left);
    edges.top = OptConvert<Dimension>(src.top);
    edges.right = OptConvert<Dimension>(src.right);
    edges.bottom = OptConvert<Dimension>(src.bottom);
    return edges;
}

template<>
PaddingProperty Convert(const Ark_Length& src)
{
    auto value = OptConvert<CalcLength>(src);
    return { .left = value, .right = value, .top = value, .bottom = value
    };
}

template<>
RadioStyle Convert(const Ark_RadioStyle& src)
{
    return { .checkedBackgroundColor = Converter::OptConvert<Color>(src.checkedBackgroundColor),
        .uncheckedBorderColor = Converter::OptConvert<Color>(src.uncheckedBorderColor),
        .indicatorColor = Converter::OptConvert<Color>(src.indicatorColor)
    };
}

template<>
BorderRadiusProperty Convert(const Ark_LocalizedBorderRadiuses& src)
{
    LOGE("Convert [Ark_LocalizedPadding] to [PaddingProperty] is not supported.");
    BorderRadiusProperty property;
    return property;
}

template<>
BorderStyleProperty Convert(const Ark_BorderStyle& src)
{
    BorderStyleProperty property;
    auto style = OptConvert<BorderStyle>(src);
    if (style) {
        property.SetBorderStyle(style.value());
    }
    return property;
}

template<>
Dimension Convert(const Ark_CustomObject& src)
{
    LOGE("Convert [Ark_CustomObject] to [Dimension] is not supported");
    return Dimension();
}

template<>
DimensionOffset Convert(const Ark_Offset& src)
{
    return DimensionOffset(Convert<Dimension>(src.dx), Convert<Dimension>(src.dy));
}

template<>
FontMetaData Convert(const Ark_Font& src)
{
    return { OptConvert<Dimension>(src.size), OptConvert<FontWeight>(src.weight) };
}

template<>
Ark_NativePointer Convert(const Ark_Materialized& src)
{
    return src.ptr;
}

template<>
ShadowColorStrategy Convert(const Ark_Color& src)
{
    return ShadowColorStrategy::NONE;
}

template<>
ShadowColorStrategy Convert(const Ark_String& src)
{
    return ShadowColorStrategy::NONE;
}

template<>
ShadowColorStrategy Convert(const Ark_Resource& src)
{
    return ShadowColorStrategy::NONE;
}

template<>
FontFamilies Convert(const Ark_String& src)
{
    auto familiesStr = Convert<std::string>(src);
    FontFamilies dst;
    dst.families = Framework::ConvertStrToFontFamilies(familiesStr);
    return dst;
}

template<>
Font Convert(const Ark_Font& src)
{
    Font font;
    if (auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>(src.family); fontfamiliesOpt) {
        font.fontFamilies = fontfamiliesOpt->families;
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
Gradient Convert(const Ark_LinearGradient& value)
{
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);

    // angle
    auto linearGradient = gradient.GetLinearGradient();
    linearGradient->angle = Converter::OptConvert<Dimension>(value.angle);

    // direction
    auto directionOpt = Converter::OptConvert<GradientDirection>(value.direction);
    if (directionOpt) {
        gradient.SetDirection(directionOpt.value());
    }

    // repeating
    auto repeatingOpt = Converter::OptConvert<bool>(value.repeating);
    if (repeatingOpt) {
        gradient.SetRepeat(repeatingOpt.value());
    }

    auto gradientColors = Converter::Convert<std::vector<std::pair<Color, Dimension>>>(value.colors);

    if (gradientColors.size() == 1) {
        auto item = gradientColors.front();
        GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(item.first));
        gradientColor.SetDimension(item.second);
        gradient.AddColor(gradientColor);
        gradient.AddColor(gradientColor);
    } else {
        for (auto item : gradientColors) {
            GradientColor gradientColor;
            gradientColor.SetLinearColor(LinearColor(item.first));
            gradientColor.SetDimension(item.second);
            gradient.AddColor(gradientColor);
        }
    }

    return gradient;
}

template<>
GradientColor Convert(const Ark_Tuple_ResourceColor_Number& src)
{
    GradientColor gradientColor;
    gradientColor.SetHasValue(false);

    // color
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(src.value0);
    if (colorOpt) {
        gradientColor.SetColor(colorOpt.value());
        gradientColor.SetHasValue(true);
    }

    // stop value
    float value = Converter::Convert<float>(src.value1);
    value = std::clamp(value, 0.0f, 1.0f);
    //  [0, 1] -> [0, 100.0];
    gradientColor.SetDimension(CalcDimension(value * Converter::PERCENT_100, DimensionUnit::PERCENT));

    return gradientColor;
}

template<>
Header Convert(const Ark_Header& src)
{
    Header header;
    header.headerKey = Converter::Convert<std::string>(src.headerKey);
    header.headerValue = Converter::Convert<std::string>(src.headerValue);
    return header;
}

template<>
std::pair<Color, Dimension> Convert(const Ark_Tuple_ResourceColor_Number& src)
{
    std::pair<Color, Dimension> gradientColor;
    // color
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(src.value0);
    if (colorOpt) {
        gradientColor.first = colorOpt.value();
    }
    // stop value
    float value = Converter::Convert<float>(src.value1);
    value = std::clamp(value, 0.0f, 1.0f);
    gradientColor.second = Dimension(value, DimensionUnit::VP);
    return gradientColor;
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
bool Convert(const Ark_EdgeEffectOptions& src)
{
    return static_cast<bool>(src.alwaysEnabled);
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
NestedScrollOptions Convert(const Ark_NestedScrollOptions& src)
{
    NestedScrollOptions nestedScrollOptions = {
        .forward = OptConvert<NestedScrollMode>(src.scrollForward).value_or(NestedScrollMode::SELF_ONLY),
        .backward = OptConvert<NestedScrollMode>(src.scrollBackward).value_or(NestedScrollMode::SELF_ONLY),
    };
    return nestedScrollOptions;
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
void AssignCast(std::optional<std::u16string>& dst, const Ark_Resource& src)
{
    auto str8 = OptConvert<std::string>(src);
    if (str8) {
        dst = UtfUtils::Str8ToStr16(str8.value());
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
BorderStyleProperty Convert(const Ark_EdgeStyles& src)
{
    BorderStyleProperty property;
    property.styleLeft = OptConvert<BorderStyle>(src.left);
    property.styleTop = OptConvert<BorderStyle>(src.top);
    property.styleRight = OptConvert<BorderStyle>(src.right);
    property.styleBottom = OptConvert<BorderStyle>(src.bottom);
    property.multiValued = true;
    return property;
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
void AssignCast(std::optional<FontFamilies>& dst, const Ark_Resource& value)
{
    dst = std::nullopt;
    ResourceConverter converter(value);
    auto families = converter.ToFontFamilies();
    if (families) {
        FontFamilies temp;
        temp.families = families.value();
        dst = temp;
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

template<>
PickerValueType Convert(const Ark_String& src)
{
    auto str = Converter::Convert<std::string>(src);
    return str;
}

template<>
PickerValueType Convert(const Array_String& src)
{
    return Converter::Convert<std::vector<std::string>>(src);
}

template<>
PickerSelectedType Convert(const Ark_Number& src)
{
    auto selected = Converter::Convert<int32_t>(src);
    if (selected < 0) {
        selected = 0;
    }
    return static_cast<uint32_t>(selected);
}

template<>
PickerSelectedType Convert(const Array_Number& src)
{
    std::vector<uint32_t> dst;
    std::vector<int32_t> tmp = Converter::Convert<std::vector<int32_t>>(src);
    for (auto selected : tmp) {
        if (selected < 0) {
            selected = 0;
        }
        dst.push_back(static_cast<uint32_t>(selected));
    }
    return dst;
}

template<>
void AssignCast(std::optional<PickerDate>& dst, const Ark_Date& src)
{
    const auto DATE_MIN = PickerDate(1970, 1, 1);
    const auto DATE_MAX = PickerDate(2100, 12, 31);
    const auto SEC_TO_MILLISEC = 1000L;
    auto timestamp = reinterpret_cast<int64_t>(src);
    time_t time = static_cast<time_t>(timestamp / SEC_TO_MILLISEC);
    auto local = std::localtime(&time);
    // tm_year is years since 1900
    // tm_mon from 0 to 11
    dst = PickerDate(local->tm_year + STD_TM_START_YEAR, local->tm_mon + 1, local->tm_mday);
    auto maxDay = PickerDate::GetMaxDay(dst->GetYear(), dst->GetMonth());
    if (dst->GetYear() < DATE_MIN.GetYear() || dst->GetYear() > DATE_MAX.GetYear()) {
        dst = DATE_MIN;
    } else if (dst->GetMonth() < DATE_MIN.GetMonth() || dst->GetMonth() > DATE_MAX.GetMonth()) {
        dst = DATE_MIN;
    } else if (dst->GetDay() < DATE_MIN.GetDay() || dst->GetDay() > maxDay) {
        dst = DATE_MIN;
    }
}

template<>
LightSource Convert(const Ark_LightSource& src)
{
    LightSource lightSource;
    lightSource.x = Converter::OptConvert<CalcDimension>(src.positionX);
    lightSource.y = Converter::OptConvert<CalcDimension>(src.positionY);
    lightSource.z = Converter::OptConvert<CalcDimension>(src.positionZ);
    lightSource.intensity = Converter::OptConvert<float>(src.intensity);
    Validator::ValidateIntensity(lightSource.intensity);
    lightSource.lightColor = Converter::OptConvert<Color>(src.color);
    return lightSource;
}

template<>
PointLightStyle Convert(const Ark_PointLightStyle& src)
{
    PointLightStyle pointLightStyle;
    pointLightStyle.lightSource = Converter::OptConvert<LightSource>(src.lightSource);
    // this converter should be changed to support IlluminatedType
    auto arkIlluminatedType = Converter::OptConvert<Ark_IlluminatedType>(src.illuminated);
    pointLightStyle.illuminationType = EnumToInt(arkIlluminatedType);
    pointLightStyle.bloom = Converter::OptConvert<float>(src.bloom);
    Validator::ValidateBloom(pointLightStyle.bloom);
    return pointLightStyle;
}
} // namespace OHOS::Ace::NG::Converter
