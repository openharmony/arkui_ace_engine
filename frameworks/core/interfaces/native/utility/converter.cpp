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

#include <cerrno>
#include <cstdint>
#include "arkoala_api_generated.h"

#include "converter.h"

#include "base/utils/string_utils.h"
#include "bridge/common/utils/utils.h"
#include "core/common/card_scope.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/components/theme/shadow_theme.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/implementation/transition_effect_peer_impl.h"
#include "core/interfaces/native/implementation/i_curve_peer_impl.h"
#include "core/interfaces/native/implementation/length_metrics_peer.h"
#include "core/interfaces/native/implementation/linear_gradient_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/implementation/text_menu_item_id_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace {
    constexpr int32_t NUM_0 = 0;
    constexpr int32_t NUM_1 = 1;
    constexpr int32_t NUM_2 = 2;
    constexpr int32_t NUM_3 = 3;
    constexpr int32_t NUM_4 = 4;
    constexpr int32_t STD_TM_START_YEAR = 1900;
    constexpr uint32_t DEFAULT_DURATION = 1000; // ms
    constexpr double NUM_DOUBLE_0 = 0.;
    constexpr double NUM_DOUBLE_1 = 1.;
    constexpr double NUM_DOUBLE_100 = 100.;
    constexpr int32_t NUM_PERCENT_100 = 100;
    constexpr int32_t DEFAULT_MULTIPLE = 100;
    constexpr float GRADIENT_MIN_POSITION = 0.0f;
    constexpr float GRADIENT_DEFAULT_MIN_POSITION = 0.0f;
    int32_t ConvertToVariableFontWeight(OHOS::Ace::FontWeight fontWeight)
    {
        OHOS::Ace::FontWeight convertValue;
        switch (fontWeight) {
            case OHOS::Ace::FontWeight::W100:
            case OHOS::Ace::FontWeight::LIGHTER:
                convertValue = OHOS::Ace::FontWeight::W100;
                break;
            case OHOS::Ace::FontWeight::W200:
                convertValue = OHOS::Ace::FontWeight::W200;
                break;
            case OHOS::Ace::FontWeight::W300:
                convertValue = OHOS::Ace::FontWeight::W300;
                break;
            case OHOS::Ace::FontWeight::W400:
            case OHOS::Ace::FontWeight::NORMAL:
            case OHOS::Ace::FontWeight::REGULAR:
                convertValue = OHOS::Ace::FontWeight::W400;
                break;
            case OHOS::Ace::FontWeight::W500:
            case OHOS::Ace::FontWeight::MEDIUM:
                convertValue = OHOS::Ace::FontWeight::W500;
                break;
            case OHOS::Ace::FontWeight::W600:
                convertValue = OHOS::Ace::FontWeight::W600;
                break;
            case OHOS::Ace::FontWeight::W700:
            case OHOS::Ace::FontWeight::BOLD:
                convertValue = OHOS::Ace::FontWeight::W700;
                break;
            case OHOS::Ace::FontWeight::W800:
                convertValue = OHOS::Ace::FontWeight::W800;
                break;
            case OHOS::Ace::FontWeight::W900:
            case OHOS::Ace::FontWeight::BOLDER:
                convertValue = OHOS::Ace::FontWeight::W900;
                break;
            default:
                convertValue = OHOS::Ace::FontWeight::W400;
                break;
        }
        return (static_cast<int32_t>(convertValue) + 1) * DEFAULT_MULTIPLE;
    }
    static const int32_t MIN_FONT_WEIGHT = ConvertToVariableFontWeight(OHOS::Ace::FontWeight::W100);
    static const int32_t MAX_FONT_WEIGHT = ConvertToVariableFontWeight(OHOS::Ace::FontWeight::W900);
    const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);

    std::string GetReplaceContentStr(
        int32_t pos, const std::string& type, std::vector<std::string>& params, int32_t containCount)
    {
        auto index = pos + containCount;
        if (index < 0) {
            return std::string();
        }
        return params.at(index);
    }
    void ReplaceHolder(std::string& originStr, std::vector<std::string>& params, int32_t containCount)
    {
        auto size = static_cast<int32_t>(params.size());
        if (containCount == size) {
            return;
        }
        std::string::const_iterator start = originStr.begin();
        std::string::const_iterator end = originStr.end();
        std::smatch matches;
        bool shortHolderType = false;
        bool firstMatch = true;
        int searchTime = 0;
        while (std::regex_search(start, end, matches, RESOURCE_APP_STRING_PLACEHOLDER)) {
            std::string pos = matches[2];
            std::string type = matches[4];
            if (firstMatch) {
                firstMatch = false;
                shortHolderType = pos.length() == 0;
            } else {
                if (shortHolderType ^ (pos.length() == 0)) {
                    return;
                }
            }
    
            std::string replaceContentStr;
            if (shortHolderType) {
                replaceContentStr = GetReplaceContentStr(searchTime, type, params, containCount);
            } else {
                replaceContentStr =
                    GetReplaceContentStr(OHOS::Ace::Framework::StringToInt(pos) - 1, type, params, containCount);
            }
    
            originStr.replace(matches[0].first - originStr.begin(), matches[0].length(), replaceContentStr);
            start = originStr.begin() + matches.prefix().length() + replaceContentStr.length();
            end = originStr.end();
            searchTime++;
        }
    }
} // namespace

namespace OHOS::Ace::NG {
std::optional<double> FloatToDouble(const std::optional<float>& src)
{
    return src ? std::optional(static_cast<double>(src.value())) : std::nullopt;
}
}

namespace OHOS::Ace::NG::Converter {
struct DecorationStyleInterface {
    std::optional<TextDecoration> type;
    std::optional<Color> color;
    std::optional<TextDecorationStyle> style;
};

RefPtr<ThemeConstants> GetThemeConstants(Ark_NodeHandle node, Ark_CharPtr bundleName, Ark_CharPtr moduleName)
{
    auto cardId = CardScope::CurrentId();
    if (cardId != INVALID_CARD_ID) {
        auto container = Container::Current();
        auto weak = container->GetCardPipeline(cardId);
        auto cardPipelineContext = weak.Upgrade();
        CHECK_NULL_RETURN(cardPipelineContext, nullptr);
        auto cardThemeManager = cardPipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(cardThemeManager, nullptr);
        return cardThemeManager->GetThemeConstants(bundleName, moduleName);
    }

    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    if (!frameNode) {
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, nullptr);
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        auto themeManager = pipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(themeManager, nullptr);
        return themeManager->GetThemeConstants(bundleName, moduleName);
    }
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetThemeConstants(bundleName, moduleName);
}

void AssignGradientColors(Gradient *gradient,
    const Array_Tuple_ResourceColor_Number *colors)
{
    for (int32_t i = 0; i < colors->length; i++) {
        auto color = OptConvert<Color>(colors->array[i].value0);
        auto position = Convert<float>(colors->array[i].value1);
        if (LessOrEqual(position, GRADIENT_MIN_POSITION)) {
            position = GRADIENT_DEFAULT_MIN_POSITION;
        }
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
    if (resource.id.tag == INTEROP_TAG_INT32) {
        id_ = resource.id.i32;
        type_ = static_cast<ResourceType>(OptConvert<int>(resource.type).value_or(0));
        bundleName_ = Convert<std::string>(resource.bundleName);
        moduleName_ = Convert<std::string>(resource.moduleName);
        if (resource.params.tag != INTEROP_TAG_UNDEFINED) {
            for (int i = 0; i < resource.params.value.length; i++) {
                params_.emplace_back(resource.params.value.array[i].chars);
            }
        }
        themeConstants_ = GetThemeConstants(nullptr, bundleName_.c_str(), moduleName_.c_str());
        if (!themeConstants_) {
            auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
            auto themeManager = context->GetThemeManager();
            CHECK_NULL_VOID(themeManager);
            themeConstants_ = themeManager->GetThemeConstants(bundleName_.c_str(), moduleName_.c_str());
        }
    } else {
        LOGE("ResourceConverter illegal id tag: id.tag = %{public}d", resource.id.tag);
    }
}

std::optional<std::string> ResourceConverter::GetStringResource()
{
    std::optional<std::string> result;
    if (id_ != -1) {
        result = themeConstants_->GetString(id_);
        ReplaceHolder(result.value(), params_, 0);
    } else if (!params_.empty()) {
        result = themeConstants_->GetStringByName(params_.front());
        ReplaceHolder(result.value(), params_, 1);
    } else {
        LOGE("Unknown resource value OHOS::Ace::NG::Converter::ResourceConverter");
    }
    return result;
}

std::optional<std::string> ResourceConverter::GetRawfilePath()
{
    std::optional<std::string> result;
    if (!params_.empty()) {
        result = themeConstants_->GetRawfile(params_.front());
    }
    return result;
}

std::optional<std::string> ResourceConverter::GetMediaPath()
{
    std::optional<std::string> result;
    if (id_ != -1) {
        result = themeConstants_->GetMediaPath(id_);
    } else if (!params_.empty()) {
        result = themeConstants_->GetMediaPathByName(params_.front());
    }
    return result;
}

std::optional<std::string> ResourceConverter::GetPluralResource()
{
    std::optional<std::string> result;
    if (id_ != -1 && params_.size() == 2) {  // 2 means quantity and count in params_
        result = themeConstants_->GetPluralString(id_, StringUtils::StringToInt(params_[0]));
        ReplaceHolder(result.value(), params_, 1);
    } else if (params_.size() == 3) {  // 3 means resName, quantity and count in params_
        result = themeConstants_->GetPluralStringByName(params_[0], StringUtils::StringToInt(params_[1]));
        ReplaceHolder(result.value(), params_, 2);  // 2 means data get from params_[2]
    } else {
        LOGE("Invalid PLURAL resource OHOS::Ace::NG::Converter::ResourceConverter");
    }
    return result;
}

std::optional<int32_t> ResourceConverter::GetIntegerResource()
{
    std::optional<int32_t> result;
    if (id_ != -1) {
        result = themeConstants_->GetInt(id_);
    } else if (!params_.empty()) {
        result = themeConstants_->GetIntByName(params_.front());
    } else {
        LOGE("Unknown INTEGER value OHOS::Ace::NG::Converter::ResourceConverter");
    }
    return result;
}

std::optional<double> ResourceConverter::GetFloatResource()
{
    std::optional<double> result;
    if (id_ != -1) {
        result = themeConstants_->GetDouble(id_);
    } else if (!params_.empty()) {
        result = themeConstants_->GetDoubleByName(params_.front());
    } else {
        LOGE("Unknown FLOAT value OHOS::Ace::NG::Converter::ResourceConverter");
    }
    return result;
}

std::optional<std::string> ResourceConverter::ToString()
{
    std::optional<std::string> result;
    CHECK_NULL_RETURN(themeConstants_, result);

    if (type_ == ResourceType::STRING) {
        result = GetStringResource();
    } else if (type_ == ResourceType::RAWFILE) {
        result = GetRawfilePath();
    } else if (type_ == ResourceType::MEDIA) {
        result = GetMediaPath();
    } else if (type_ == ResourceType::PLURAL) {
        result = GetPluralResource();
    } else if (type_ == ResourceType::INTEGER) {
        auto intValue = GetIntegerResource();
        result = intValue.has_value() ? std::make_optional(std::to_string(intValue.value())) : std::nullopt;
    } else if (type_ == ResourceType::FLOAT) {
        auto floatValue = GetFloatResource();
        result = floatValue.has_value() ? std::make_optional(std::to_string(floatValue.value())) : std::nullopt;
    } else {
        LOGE("Unknown resource value OHOS::Ace::NG::Converter::ResourceConverter");
    }
    return result;
}

std::optional<StringArray> ResourceConverter::ToStringArray()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == ResourceType::STRARRAY) {
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
    if (type_ == ResourceType::STRING) {
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
    } else if (type_ == ResourceType::STRARRAY) {
        return ToStringArray();
    } else {
        LOGE("ResourceConverter::ToFontFamilies Resource type is not supported");
    }
    return std::nullopt;
}

std::optional<Dimension> ResourceConverter::ToDimension()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == ResourceType::INTEGER) {
        auto resource = ToInt();
        if (!resource) return std::nullopt;
        return Dimension(*resource, DimensionUnit::VP);
    } else if (type_ == ResourceType::FLOAT) {
        if (id_ == -1 && !params_.empty()) {
            return themeConstants_->GetDimensionByName(params_.front());
        } else if (id_ != -1) {
            return themeConstants_->GetDimension(id_);
        } else {
            LOGE("ResourceConverter::ToDimension Unknown resource value");
        }
    }
    return std::nullopt;
}

std::optional<CalcLength> ResourceConverter::ToCalcLength()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == ResourceType::STRING) {
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
    if (type_ == ResourceType::FLOAT) {
        if (id_ == -1 && params_.size() > 0) {
            optFloat = static_cast<float>(themeConstants_->GetDoubleByName(params_[0]));
        } else {
            optFloat = static_cast<float>(themeConstants_->GetDouble(id_));
        }
    } else if (type_ == ResourceType::INTEGER) {
        if (id_ == -1 && params_.size() > 0) {
            optFloat = static_cast<float>(themeConstants_->GetIntByName(params_[0]));
        } else {
            optFloat = static_cast<float>(themeConstants_->GetInt(id_));
        }
    } else if (type_ == ResourceType::STRING) {
        std::optional<std::string> result;
        if (id_ != -1) {
            result = themeConstants_->GetString(id_);
            ReplaceHolder(result.value(), params_, 0);
        } else if (!params_.empty()) {
            result = themeConstants_->GetStringByName(params_.front());
            ReplaceHolder(result.value(), params_, 1);
        }
        if (result.has_value()) {
            double floatVal;
            if (StringUtils::StringToDouble(result.value(), floatVal)) {
                optFloat = floatVal;
            }
        }
    }
    return optFloat;
}

std::optional<int32_t> ResourceConverter::ToInt()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == ResourceType::INTEGER) {
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
        case ResourceType::STRING: {
            Color color;
            if (Color::ParseColorString(themeConstants_->GetString(id_), color)) {
                result = color;
            }
            break;
        }

        case ResourceType::INTEGER:
            result = Color(ColorAlphaAdapt(themeConstants_->GetInt(id_)));
            break;

        case ResourceType::COLOR:
            result = themeConstants_->GetColor(id_);
            break;

        default:
            break;
    }

    return result;
}

std::optional<bool> ResourceConverter::ToBoolean()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == ResourceType::BOOLEAN) {
        return themeConstants_->GetBoolean(id_);
    }
    return std::nullopt;
}

template<>
ScaleOpt Convert(const Ark_ScaleOptions& src)
{
    ScaleOpt scaleOptions;
    scaleOptions.x = OptConvert<float>(src.x);
    scaleOptions.y = OptConvert<float>(src.y);
    scaleOptions.z = OptConvert<float>(src.z);
    scaleOptions.centerX = OptConvert<Dimension>(src.centerX);
    scaleOptions.centerY = OptConvert<Dimension>(src.centerY);
    return scaleOptions;
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
SheetHeight Convert(const Ark_SheetSize& src)
{
    SheetHeight detent;
    detent.sheetMode = OptConvert<SheetMode>(src);
    detent.height.reset();
    return detent;
}

template<>
SheetHeight Convert(const Ark_Length& src)
{
    SheetHeight detent;
    detent.sheetMode.reset();
    detent.height = Convert<Dimension>(src);
    Validator::ValidateNonNegative(detent.height);
    if (!detent.height.has_value()) {
        detent.sheetMode = NG::SheetMode::LARGE;
        detent.height.reset();
    }
    return detent;
}

template<>
std::u16string Convert(const Ark_String& src)
{
    auto str8 =  Converter::Convert<std::string>(src);
    return UtfUtils::Str8ToStr16(str8);
}

template<>
std::vector<ImageAnalyzerType> Convert(const Array_ImageAnalyzerType& src)
{
    std::vector<ImageAnalyzerType> dst;
    auto length = Converter::Convert<int>(src.length);
    for (int i = 0; i < length; i++) {
        auto opt = Converter::OptConvert<ImageAnalyzerType>(*(src.array + i));
        if (opt) {
            dst.push_back(*opt);
        }
    }
    return dst;
}

template<>
std::vector<Shadow> Convert(const Ark_ShadowOptions& src)
{
    return { Convert<Shadow>(src) };
}

template<>
std::vector<uint32_t> Convert(const Array_LayoutSafeAreaType& src)
{
    std::vector<uint32_t> dst;
    auto length = Converter::Convert<int>(src.length);
    for (int i = 0; i < length; i++) {
        auto value = Converter::Convert<uint32_t>(*(src.array + i));
        dst.push_back(value);
    }
    return dst;
}

template<>
std::vector<uint32_t> Convert(const Array_LayoutSafeAreaEdge& src)
{
    std::vector<uint32_t> dst;
    auto length = Converter::Convert<int>(src.length);
    for (int i = 0; i < length; i++) {
        auto value = Converter::Convert<uint32_t>(*(src.array + i));
        dst.push_back(value);
    }
    return dst;
}

template<>
std::vector<NG::BarItem> Convert(const Array_NavigationMenuItem& src)
{
    std::vector<NG::BarItem> dst;
    auto length = Converter::Convert<int>(src.length);
    for (int i = 0; i < length; i++) {
        auto menuItem = *(src.array + i);
        NG::BarItem item;
        item.text = Converter::OptConvert<std::string>(menuItem.value).value_or("");
        item.icon = Converter::OptConvert<std::string>(menuItem.icon);
        // iconSymbol is not dealed
        item.isEnabled = Converter::OptConvert<bool>(menuItem.isEnabled);
        if (menuItem.action.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto actionCallback = [changeCallback = CallbackHelper(menuItem.action.value), node = targetNode]() {
                PipelineContext::SetCallBackNode(node);
                changeCallback.Invoke();
            };
            item.action = actionCallback;
        }
        dst.push_back(item);
    }
    return dst;
}

template<>
std::vector<NG::BarItem> Convert(const Array_ToolbarItem& src)
{
    std::vector<NG::BarItem> dst;
    auto length = Converter::Convert<int>(src.length);
    for (int i = 0; i < length; i++) {
        auto toolbarItem = *(src.array + i);
        NG::BarItem item;
        item.text = Converter::OptConvert<std::string>(toolbarItem.value).value_or("");
        item.icon = Converter::OptConvert<std::string>(toolbarItem.icon);
        //item.iconSymbol = Converter::OptConvert<std::function<void(WeakPtr<NG::FrameNode>)>>(toolbarItem.symbolIcon);
        if (toolbarItem.action.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto actionCallback = [changeCallback = CallbackHelper(toolbarItem.action.value), node = targetNode]() {
                PipelineContext::SetCallBackNode(node);
                changeCallback.Invoke();
            };
            item.action = actionCallback;
        }
        item.status = Converter::Convert<NavToolbarItemStatus>(toolbarItem.status);
        item.activeIcon = Converter::OptConvert<std::string>(toolbarItem.activeIcon);
        //item.activeIconSymbol = Converter::OptConvert<std::function<void(WeakPtr<NG::FrameNode>)>>(toolbarItem.activeSymbolIcon);
        dst.push_back(item);
    }
    return dst;
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
CalcDimension Convert(const Ark_LengthMetrics& src)
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
EdgesParam Convert(const Ark_LocalizedEdges& src)
{
    EdgesParam edges;
    edges.start = OptConvert<Dimension>(src.start);
    edges.top = OptConvert<Dimension>(src.top);
    edges.end = OptConvert<Dimension>(src.end);
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
    BorderRadiusProperty property;
    CalcDimension topStart;
    auto topStartOpt = Converter::OptConvert<Dimension>(src.topStart);
    if (topStartOpt) {
        topStart = topStartOpt.value();
    }
    CalcDimension topEnd;
    auto topEndOpt = Converter::OptConvert<Dimension>(src.topEnd);
    if (topEndOpt) {
        topEnd = topEndOpt.value();
    }
    CalcDimension bottomStart;
    auto bottomStartOpt = Converter::OptConvert<Dimension>(src.bottomStart);
    if (bottomStartOpt) {
        bottomStart = bottomStartOpt.value();
    }
    CalcDimension bottomEnd;
    auto bottomEndOpt = Converter::OptConvert<Dimension>(src.bottomEnd);
    if (bottomEndOpt) {
        bottomEnd = bottomEndOpt.value();
    }
    bool hasSetBorderRadius = topStartOpt || topEndOpt || bottomStartOpt || bottomEndOpt;
    auto isRtl = hasSetBorderRadius && AceApplicationInfo::GetInstance().IsRightToLeft();
    property.radiusTopStart = isRtl ? topEnd : topStart;
    property.radiusTopEnd = isRtl ? topStart : topEnd;
    property.radiusBottomStart = isRtl ? bottomEnd : bottomStart;
    property.radiusBottomEnd = isRtl ? bottomStart : bottomEnd;
    property.multiValued = true;
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
DimensionOffset Convert(const Ark_Position& src)
{
    auto x = Converter::OptConvert<Dimension>(src.x);
    auto y = Converter::OptConvert<Dimension>(src.y);
    return DimensionOffset(x.has_value() ? x.value() : Dimension(), y.has_value() ? y.value() : Dimension());
}

template<>
FontMetaData Convert(const Ark_Font& src)
{
    return { OptConvert<Dimension>(src.size), OptConvert<FontWeight>(src.weight) };
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
        Validator::ValidateNonNegative(fontSize);
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
FontInfo Convert(const Ark_FontInfo& src)
{
    return {
        .path = Convert<std::string>(src.path),
        .postScriptName = Convert<std::string>(src.postScriptName),
        .fullName = Convert<std::string>(src.fullName),
        .family = Convert<std::string>(src.family),
        .subfamily = Convert<std::string>(src.subfamily),
        .weight = Convert<uint32_t>(src.weight),
        .width = Convert<uint32_t>(src.width),
        .italic = Convert<bool>(src.italic),
        .monoSpace = Convert<bool>(src.monoSpace),
        .symbolic = Convert<bool>(src.symbolic),
    };
}

template<>
FontWeightInt Convert(const Ark_FontWeight& src)
{
    FontWeightInt dst = {};
    dst.fixed = OptConvert<FontWeight>(src);
    if (dst.fixed.has_value()) {
        dst.variable = ConvertToVariableFontWeight(dst.fixed.value());
    }
    return dst;
}

template<>
FontWeightInt Convert(const Ark_Number& src)
{
    FontWeightInt dst = {};
    dst.fixed = OptConvert<FontWeight>(src);
    int32_t weight = Convert<int32_t>(src);
    if (weight >= MIN_FONT_WEIGHT && weight <= MAX_FONT_WEIGHT) {
        dst.variable = weight;
    }
    return dst;
}

template<>
FontWeightInt Convert(const Ark_String& src)
{
    FontWeightInt dst = {};
    dst.fixed = OptConvert<FontWeight>(src);

    char *endptr;
    errno = 0;
    long value = std::strtol(src.chars, &endptr, 10);
    if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN)) ||
        (errno != 0 && value == 0) || (endptr == src.chars) || (*endptr != '\0')) {
        if (dst.fixed.has_value()) {
            dst.variable = ConvertToVariableFontWeight(dst.fixed.value());
        }
    } else {
        int32_t intWeight = static_cast<int32_t>(value);
        if (intWeight >= MIN_FONT_WEIGHT && intWeight <= MAX_FONT_WEIGHT) {
            dst.variable = intWeight;
        }
    }
    return dst;
}

template<>
Gradient Convert(const Ark_LinearGradient& value)
{
    Gradient gradient;
    LOGE("Conversion for Ark_LinearGradient to Gradient is not yet implemented!");
    return gradient;
}

template<>
void AssignCast (std::optional<Gradient>& dst, const Ark_LinearGradient& src)
{
    Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    auto peer = reinterpret_cast<LinearGradientPeer*>(src);
    auto gradientColors = src->colorStops;

    if (gradientColors.size() == 1) {
        auto item = gradientColors.front();
        if (!item.first.has_value()) {
            return;
        }
        GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(item.first.value()));
        gradientColor.SetDimension(item.second);
        gradient.AddColor(gradientColor);
        gradient.AddColor(gradientColor);
    } else {
        for (auto item : gradientColors) {
            if (!item.first.has_value()) {
                return;
            }
            GradientColor gradientColor;
            gradientColor.SetLinearColor(LinearColor(item.first.value()));
            gradientColor.SetDimension(item.second);
            gradient.AddColor(gradientColor);
        }
    }
    dst = gradient;
}

template<>
std::pair<std::optional<Color>, Dimension> Convert(const Ark_ColorStop& src)
{
    auto color = Converter::OptConvert<Color>(src.color);
    auto offset = Converter::Convert<Dimension>(src.offset);
    // normalize the offset in a range [0.0 ... 1.0]
    if (offset.Unit() == DimensionUnit::PERCENT) {
        offset = Dimension(std::clamp(offset.Value(), NUM_DOUBLE_0, NUM_DOUBLE_100) / NUM_PERCENT_100);
    } else {
        offset = Dimension(std::clamp(offset.Value(), NUM_DOUBLE_0, NUM_DOUBLE_1));
    }
    return std::make_pair(color, offset);
}

template<>
Gradient Convert(const Ark_LinearGradient_common& value)
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
Header Convert(const Ark_WebHeader& src)
{
    Header header;
    header.headerKey = Converter::Convert<std::string>(src.headerKey);
    header.headerValue = Converter::Convert<std::string>(src.headerValue);
    return header;
}

template<>
std::map<std::string, std::string> Convert(const Map_String_String& src)
{
    Array_String arkKeys {
        .array = src.keys,
        .length = src.size
    };
    Array_String arkValues {
        .array = src.values,
        .length = src.size
    };

    std::vector<std::string> keys = Convert<std::vector<std::string>>(arkKeys);
    std::vector<std::string> values = Convert<std::vector<std::string>>(arkValues);

    std::map<std::string, std::string> m;
    for (size_t i = 0; i < values.size(); ++i) {
        m[keys[i]] = values[i];
    }
    return m;
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
CheckboxSettingData Convert(const Ark_LunarSwitchStyle& src)
{
    CheckboxSettingData data;
    data.selectedColor = OptConvert<Color>(src.selectedColor);
    data.unselectedColor = OptConvert<Color>(src.unselectedColor);
    data.strokeColor = OptConvert<Color>(src.strokeColor);
    return data;
}

template<>
void AssignCast(std::optional<DateTimeType>& dst, const Ark_DateTimeOptions& src)
{
    const std::string TIMEPICKER_OPTIONS_NUMERIC_VAL = "numeric";
    const std::string TIMEPICKER_OPTIONS_TWO_DIGIT_VAL = "2-digit";

    DateTimeType type {ZeroPrefixType::AUTO, ZeroPrefixType::AUTO, ZeroPrefixType::AUTO};
    auto hourStr = OptConvert<std::string>(src.hour);
    if (hourStr) {
        if (hourStr == TIMEPICKER_OPTIONS_TWO_DIGIT_VAL) {
            type.hourType = ZeroPrefixType::SHOW;
        } else if (hourStr == TIMEPICKER_OPTIONS_NUMERIC_VAL) {
            type.hourType = ZeroPrefixType::HIDE;
        }
    }
    auto minuteStr = OptConvert<std::string>(src.minute);
    if (minuteStr) {
        type.minuteType = ZeroPrefixType::SHOW;
        if (minuteStr == TIMEPICKER_OPTIONS_NUMERIC_VAL) {
            type.minuteType = ZeroPrefixType::HIDE;
        }
    }
    dst = type;
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
void AssignCast(std::optional<TextSpanType>& dst, const Ark_TextSpanType& src)
{
    switch (src) {
        case ARK_TEXT_SPAN_TYPE_TEXT: dst = TextSpanType::TEXT; break;
        case ARK_TEXT_SPAN_TYPE_IMAGE: dst = TextSpanType::IMAGE; break;
        case ARK_TEXT_SPAN_TYPE_MIXED: dst = TextSpanType::MIXED; break;
        case ARK_TEXT_SPAN_TYPE_DEFAULT: dst = TextSpanType::NONE; break;
        default:
            LOGE("Unexpected enum value in Ark_TextSpanType: %{public}d", src);
            dst = std::nullopt;
    }
}

template<>
void AssignCast(std::optional<TextResponseType>& dst, const Ark_TextResponseType& src)
{
    switch (src) {
        case ARK_TEXT_RESPONSE_TYPE_RIGHT_CLICK: dst = TextResponseType::RIGHT_CLICK; break;
        case ARK_TEXT_RESPONSE_TYPE_LONG_PRESS: dst = TextResponseType::LONG_PRESS; break;
        case ARK_TEXT_RESPONSE_TYPE_SELECT: dst = TextResponseType::SELECTED_BY_MOUSE; break;
        case ARK_TEXT_RESPONSE_TYPE_DEFAULT: dst = TextResponseType::NONE; break;
        default:
            LOGE("Unexpected enum value in Ark_TextResponseType: %{public}d", src);
            dst = std::nullopt;
    }
}

template<>
void AssignCast(std::optional<uint32_t>& dst, const Ark_Number& src)
{
    if (src.tag == INTEROP_TAG_FLOAT32) {
        if (src.f32 >= 0) {
            dst = static_cast<int>(src.f32);
        }
    } else if (src.i32 >= 0) {
        dst = src.i32;
    }
}

template<>
void AssignCast(std::optional<std::string>& dst, const Array_TextDataDetectorType& src)
{
    CHECK_NULL_VOID(src.array);
    std::string ret;
    for (int idx = 0; idx < src.length; idx++) {
        Ark_TextDataDetectorType type = src.array[idx];
        switch (type) {
            case ARK_TEXT_DATA_DETECTOR_TYPE_PHONE_NUMBER:
                ret += "phoneNum";
                break;
            case ARK_TEXT_DATA_DETECTOR_TYPE_URL:
                ret += "url";
                break;
            case ARK_TEXT_DATA_DETECTOR_TYPE_EMAIL:
                ret += "email";
                break;
            case ARK_TEXT_DATA_DETECTOR_TYPE_ADDRESS:
                ret += "location";
                break;
            case ARK_TEXT_DATA_DETECTOR_TYPE_DATE_TIME:
                ret += "datetime";
                break;
            default:
                break;
        }
        bool isLast = idx == (src.length - 1);
        if (!isLast) {
            ret += ",";
        }
    }
    dst = ret;
}

template<>
DecorationStyleInterface Convert(const Ark_DecorationStyleInterface& src)
{
    DecorationStyleInterface ret;
    ret.type = OptConvert<TextDecoration>(src.type);
    ret.color = OptConvert<Color>(src.color);
    ret.style = OptConvert<TextDecorationStyle>(src.style);
    return ret;
}

template<>
TextDetectConfig Convert(const Ark_TextDataDetectorConfig& src)
{
    TextDetectConfig ret;
    ret.types = OptConvert<std::string>(src.types).value_or("");
    auto onDetectResultUpdate = OptConvert<Callback_String_Void>(src.onDetectResultUpdate);
    if (onDetectResultUpdate) {
        auto callback = [arkCallback = CallbackHelper(*onDetectResultUpdate)](const std::string& arg) -> void {
            ConvContext ctx;
            auto arkArg = ArkValue<Ark_String>(arg, &ctx);
            arkCallback.InvokeSync(arkArg);
        };
        ret.onResult = callback;
    }
    if (auto color = OptConvert<Color>(src.color); color) {
        ret.entityColor = color.value();
    }
    auto decoration = OptConvert<DecorationStyleInterface>(src.decoration);
    if (decoration) {
        if (auto type = decoration->type) {
            ret.entityDecorationType = type.value();
        }
        if (auto color = decoration->color) {
            ret.entityDecorationColor = color.value();
        }
        if (auto style = decoration->style) {
            ret.entityDecorationStyle = style.value();
        }
    }
    return ret;
}

template<>
TranslateOptions Convert(const Ark_TranslateOptions& src)
{
    TranslateOptions translateOptions;
    auto coord = OptConvert<Dimension>(src.x);
    if (coord.has_value()) {
        translateOptions.x = coord.value();
    }
    coord = OptConvert<Dimension>(src.y);
    if (coord.has_value()) {
        translateOptions.y = coord.value();
    }
    coord = OptConvert<Dimension>(src.z);
    if (coord.has_value()) {
        translateOptions.z = coord.value();
    }
    return translateOptions;
}

template<>
bool Convert(const Ark_EdgeEffectOptions& src)
{
    return static_cast<bool>(src.alwaysEnabled);
}

template<>
uint32_t Convert(const Ark_LayoutSafeAreaEdge& src)
{
    return static_cast<uint32_t>(src);
}

template<>
uint32_t Convert(const Ark_LayoutSafeAreaType& src)
{
    return static_cast<uint32_t>(src);
}

template<>
NG::NavigationBackgroundOptions Convert(const Ark_MoreButtonOptions& src)
{
    NG::NavigationBackgroundOptions options;
    options.color.reset();
    options.blurStyleOption.reset();
    options.effectOption.reset();
    BlurStyleOption styleOptions;
    EffectOption effectOption;

    if (src.backgroundColor.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        options.color = Converter::OptConvert<Color>(src.backgroundColor.value);
    }

    if (src.backgroundBlurStyleOptions.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        styleOptions = Converter::Convert<BlurStyleOption>(src.backgroundBlurStyleOptions.value);
    }

    if (src.backgroundBlurStyle.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto blurStyle = static_cast<int32_t>(src.backgroundBlurStyle.value);
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            styleOptions.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }

    if (src.backgroundEffect.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        effectOption = Converter::Convert<EffectOption>(src.backgroundEffect.value);
    }
    options.blurStyleOption = styleOptions;
    options.effectOption = effectOption;
    return options;
}

template<>
NG::NavigationBackgroundOptions Convert(const Ark_NavigationToolbarOptions& src)
{
    NG::NavigationBackgroundOptions options;
    options.color.reset();
    options.blurStyleOption.reset();
    options.effectOption.reset();
    BlurStyleOption styleOptions;
    EffectOption effectOption;

    if (src.backgroundColor.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        options.color = Converter::OptConvert<Color>(src.backgroundColor.value);
    }

    if (src.backgroundBlurStyleOptions.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        styleOptions = Converter::Convert<BlurStyleOption>(src.backgroundBlurStyleOptions.value);
    }

    if (src.backgroundBlurStyle.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto blurStyle = static_cast<int32_t>(src.backgroundBlurStyle.value);
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            styleOptions.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }

    if (src.backgroundEffect.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        effectOption = Converter::Convert<EffectOption>(src.backgroundEffect.value);
    }
    options.blurStyleOption = styleOptions;
    options.effectOption = effectOption;
    return options;
}

template<>
NG::NavigationBarOptions Convert(const Ark_NavigationToolbarOptions& src)
{
    NG::NavigationBarOptions options;
    options.paddingStart.reset();
    options.paddingEnd.reset();
    options.barStyle.reset();
    if (src.barStyle.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto barStyle = static_cast<int32_t>(src.barStyle.value);
        if (barStyle >= static_cast<int32_t>(NG::BarStyle::STANDARD) &&
            barStyle <= static_cast<int32_t>(NG::BarStyle::SAFE_AREA_PADDING)) {
            options.barStyle = static_cast<NG::BarStyle>(barStyle);
        } else {
            options.barStyle = NG::BarStyle::STANDARD;
        }
    }
    return options;
}

template<>
NavToolbarItemStatus Convert(const Opt_ToolbarItemStatus& src)
{
    NavToolbarItemStatus status = NavToolbarItemStatus::NORMAL;
    if (src.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        status = static_cast<NavToolbarItemStatus>(src.value);
    }
    return status;
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
ListItemGroupIndex Convert(const Ark_VisibleListContentInfo& src)
{
    auto itemIndex = ListItemGroupIndex{.index = Convert<int32_t>(src.index)}; // a struct is initialized by default
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
Rect Convert(const Ark_RectResult& src)
{
    return Rect(
        Converter::Convert<float>(src.x),
        Converter::Convert<float>(src.x),
        Converter::Convert<float>(src.width),
        Converter::Convert<float>(src.height)
    );
}

template<>
ShapePoint Convert(const Ark_Point& src)
{
    return ShapePoint(Converter::Convert<Dimension>(src.x), Converter::Convert<Dimension>(src.y));
}

template<>
ShapePoint Convert(const Ark_ShapePoint& src)
{
    ShapePoint point = {0.0_vp, 0.0_vp};
    auto x = Converter::OptConvert<Dimension>(src.value0);
    auto y = Converter::OptConvert<Dimension>(src.value1);
    point.first = x.value_or(0.0_vp);
    point.second = y.value_or(0.0_vp);
    return point;
}

template<>
MenuOptionsParam Convert(const Ark_TextMenuItem& src)
{
    MenuOptionsParam param;
    param.content = OptConvert<std::string>(src.content);
    param.icon = OptConvert<std::string>(src.icon);
    param.labelInfo = OptConvert<std::string>(src.labelInfo);
    param.id = src.id->id.value_or(param.id);
    return param;
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
OptionParam Convert(const Ark_MenuElement& src)
{
    OptionParam param;
    param.value = Converter::OptConvert<std::string>(src.value).value_or(param.value);
    param.action = [arkCallback = CallbackHelper(src.action)]() {
        arkCallback.Invoke();
    };
    param.icon = Converter::OptConvert<std::string>(src.icon).value_or(param.icon);
    LOGE("Ark_MenuElement Converter: SymbolGlyphModifier is not supported yet");
    param.enabled = Converter::OptConvert<bool>(src.enabled).value_or(param.enabled);
    return param;
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
    auto intVal = src.tag == Ark_Tag::INTEROP_TAG_INT32 ? src.i32 : static_cast<int32_t>(src.f32);
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
RefPtr<BasicShape> Convert(const Ark_CircleShape& src)
{
    CHECK_NULL_RETURN(src, nullptr);
    return src->shape;
}

template<>
RefPtr<BasicShape> Convert(const Ark_EllipseShape& src)
{
    CHECK_NULL_RETURN(src, nullptr);
    return src->shape;
}

template<>
RefPtr<BasicShape> Convert(const Ark_PathShape& src)
{
    CHECK_NULL_RETURN(src, nullptr);
    return src->shape;
}

template<>
RefPtr<BasicShape> Convert(const Ark_RectShape& src)
{
    CHECK_NULL_RETURN(src, nullptr);
    return src->shape;
}

template<>
RefPtr<ChainedTransitionEffect> Convert(const Ark_TransitionEffect& src)
{
    auto effectPeer = src;
    if (effectPeer) {
        return effectPeer->handler;
    } else {
        return nullptr;
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
    return src ? src->handler : nullptr;
}

template<>
DragPreviewOption Convert(const Ark_DragPreviewOptions &src)
{
    DragPreviewOption previewOption;
    auto previewModeHandler = [&previewOption](DragPreviewMode mode) -> bool {
        switch (mode) {
            case DragPreviewMode::AUTO: previewOption.ResetDragPreviewMode(); return true;
            case DragPreviewMode::DISABLE_SCALE: previewOption.isScaleEnabled = false; break;
            case DragPreviewMode::ENABLE_DEFAULT_SHADOW: previewOption.isDefaultShadowEnabled = true; break;
            case DragPreviewMode::ENABLE_DEFAULT_RADIUS: previewOption.isDefaultRadiusEnabled = true; break;
            default: break;
        }
        return false;
    };
    Converter::VisitUnion(src.mode,
        [previewModeHandler](const Ark_DragPreviewMode& mode) {
            auto previewMode = Converter::OptConvert<DragPreviewMode>(mode);
            if (previewMode) {
                previewModeHandler(previewMode.value());
            }
        },
        [previewModeHandler](const Array_DragPreviewMode& modeArray) {
            auto previewModeArray = Converter::Convert<std::vector<Ark_DragPreviewMode>>(modeArray);
            for (auto mode : previewModeArray) {
                auto previewMode = Converter::OptConvert<DragPreviewMode>(mode);
                if (previewMode && previewModeHandler(previewMode.value())) {
                    break;
                }
            }
        },
        []() {});
    Converter::VisitUnion(src.numberBadge,
        [&previewOption](const Ark_Number& value) {
            previewOption.isNumber = true;
            previewOption.badgeNumber = Converter::Convert<int32_t>(value);
        },
        [&previewOption](const Ark_Boolean& value) {
            previewOption.isNumber = false;
            previewOption.isShowBadge = Converter::Convert<bool>(value);
        },
        [&previewOption]() {
            previewOption.isNumber = false;
            previewOption.isShowBadge = true;
        });
    return previewOption;
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
RefPtr<PixelMap> Convert(const Ark_PixelMap& src)
{
    return src ? src->pixelMap : nullptr;
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

Dimension ConvertFromString(const std::string& str, DimensionUnit unit)
{
    static const int32_t percentUnit = 100;
    static const std::unordered_map<std::string, DimensionUnit> uMap {
        { "px", DimensionUnit::PX },
        { "vp", DimensionUnit::VP },
        { "fp", DimensionUnit::FP },
        { "%", DimensionUnit::PERCENT },
        { "lpx", DimensionUnit::LPX },
        { "auto", DimensionUnit::AUTO },
    };

    double value = 0.0;

    if (str.empty()) {
        LOGE("UITree |ERROR| empty string");
        return Dimension(value, unit);
    }

    for (int32_t i = static_cast<int32_t>(str.length() - 1); i >= 0; --i) {
        if (str[i] >= '0' && str[i] <= '9') {
            value = StringUtils::StringToDouble(str.substr(0, i + 1));
            auto subStr = str.substr(i + 1);
            auto iter = uMap.find(subStr);
            if (iter != uMap.end()) {
                unit = iter->second;
            }
            value = unit == DimensionUnit::PERCENT ? value / percentUnit : value;
            break;
        }
    }
    return Dimension(value, unit);
}

std::optional<Dimension> OptConvertFromArkResource(const Ark_Resource& src, DimensionUnit defaultUnit)
{
    ResourceConverter converter(src);
    std::optional<Dimension> dimension;
    ResourceType type = static_cast<ResourceType>(OptConvert<int>(src.type).value_or(0));
    if (type == ResourceType::FLOAT) {
        dimension = converter.ToDimension();
    } else if (type == ResourceType::STRING) {
        std::optional<std::string> optStr = converter.ToString();
        if (optStr.has_value()) {
            dimension = ConvertFromString(optStr.value(), defaultUnit);
        }
    } else if (type == ResourceType::INTEGER) {
        std::optional<int32_t> intValue = converter.ToInt();
        if (intValue.has_value()) {
            dimension = Dimension(intValue.value(), defaultUnit);
        }
    } else {
        LOGE("Unexpected converter type: %{public}d\n", type);
    }
    return dimension;
}

std::optional<Dimension> OptConvertFromArkNumStrRes(const Ark_Union_Number_String_Resource& src,
    DimensionUnit defaultUnit)
{
    std::optional<Dimension> dimension;
    auto selector = src.selector;
    if (selector == NUM_0) {
        std::optional<float> optValue = Converter::OptConvert<float>(src.value0);
        if (optValue.has_value()) {
            dimension = Dimension(optValue.value(), defaultUnit);
        }
    } else if (selector == NUM_1) {
        std::optional<std::string> optStr = Converter::OptConvert<std::string>(src.value1);
        if (optStr.has_value()) {
            dimension = ConvertFromString(optStr.value(), defaultUnit);
        }
    } else if (selector == NUM_2) {
        dimension = OptConvertFromArkResource(src.value2, defaultUnit);
    } else {
        LOGE("Unexpected converter type: %{public}d\n", selector);
    }
    return dimension;
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
    if (src.type == Ark_Tag::INTEROP_TAG_RESOURCE || src.type == Ark_RuntimeType::INTEROP_RUNTIME_OBJECT) {
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
    CHECK_NULL_RETURN(src, {});
    return src->value;
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
EffectOption Convert(const Ark_BackgroundEffectOptions& src)
{
    EffectOption dst;
    auto radiusOpt = OptConvert<Dimension>(src.radius);
    Validator::ValidateNonNegative(radiusOpt);
    dst.radius = radiusOpt.value_or(dst.radius);
    auto saturationOpt = Converter::OptConvert<float>(src.saturation);
    Validator::ValidateNonNegative(saturationOpt);
    dst.saturation = saturationOpt.value_or(dst.saturation);
    auto brightnessOpt = Converter::OptConvert<float>(src.brightness);
    Validator::ValidateNonNegative(brightnessOpt);
    dst.brightness = brightnessOpt.value_or(dst.brightness);
    dst.color = OptConvert<Color>(src.color).value_or(dst.color);
    dst.adaptiveColor = OptConvert<AdaptiveColor>(src.adaptiveColor).value_or(dst.adaptiveColor);
    dst.blurOption = OptConvert<BlurOption>(src.blurOptions).value_or(dst.blurOption);
    dst.policy = OptConvert<BlurStyleActivePolicy>(src.policy).value_or(dst.policy);
    dst.inactiveColor = OptConvert<Color>(src.inactiveColor).value_or(dst.inactiveColor);
    LOGE("OHOS::Ace::NG::Converter::Convert -> EffectOption::BlurType is not supported");
    return dst;
}

template<>
FingerInfo Convert(const Ark_FingerInfo& src)
{
    FingerInfo dst;
    dst.fingerId_ = Converter::Convert<int32_t>(src.id);
    dst.globalLocation_.SetX(Converter::Convert<float>(src.globalX));
    dst.globalLocation_.SetY(Converter::Convert<float>(src.globalY));
    dst.localLocation_.SetX(Converter::Convert<float>(src.localX));
    dst.localLocation_.SetY(Converter::Convert<float>(src.localY));
    dst.screenLocation_.SetX(Converter::Convert<float>(src.displayX));
    dst.screenLocation_.SetY(Converter::Convert<float>(src.displayY));
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
    PaddingProperty dst;
    dst.start = OptConvert<CalcLength>(src.start);
    dst.top = OptConvert<CalcLength>(src.top);
    dst.end = OptConvert<CalcLength>(src.end);
    dst.bottom = OptConvert<CalcLength>(src.bottom);
    return dst;
}

template<>
PaddingProperty Convert(const Ark_LengthMetrics& src)
{
    PaddingProperty dst;
    if (auto padding = Converter::OptConvert<CalcLength>(src); padding.has_value()) {
        dst.SetEdges(padding.value());
    }
    return dst;
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
AnimationOption Convert(const Ark_AnimateParam& src)
{
    AnimationOption option;
    // If the attribute does not exist, the default value is used.
    auto duration = Converter::OptConvert<int32_t>(src.duration).value_or(DEFAULT_DURATION);
    auto delay = Converter::OptConvert<int32_t>(src.delay).value_or(0);
    auto iterations = Converter::OptConvert<int32_t>(src.iterations).value_or(1);
    auto tempo = static_cast<double>(Converter::OptConvert<float>(src.tempo).value_or(1.0f));
    if (SystemProperties::GetRosenBackendEnabled() && NearZero(tempo)) {
        // set duration to 0 to disable animation.
        duration = 0;
    }
    auto direction = Converter::OptConvert<AnimationDirection>(src.playMode).value_or(AnimationDirection::NORMAL);
    auto finishCallbackType = Converter::OptConvert<FinishCallbackType>(src.finishCallbackType)
        .value_or(FinishCallbackType::REMOVED);
    auto curve = Converter::OptConvert<RefPtr<Curve>>(src.curve).value_or(Curves::EASE_IN_OUT);
    auto frameRateRange = Converter::OptConvert<RefPtr<FrameRateRange>>(src.expectedFrameRateRange)
        .value_or(AceType::MakeRefPtr<FrameRateRange>(0, 0, 0));

    option.SetDuration(duration);
    option.SetDelay(delay);
    option.SetIteration(iterations);
    option.SetTempo(tempo);
    option.SetAnimationDirection(direction);
    option.SetFinishCallbackType(finishCallbackType);
    option.SetCurve(curve);
    option.SetFrameRateRange(frameRateRange);
    return option;
}

template<>
BlurOption Convert(const Ark_BlurOptions& src)
{
    auto value0 = Converter::Convert<int32_t>(src.grayscale.value0);
    auto value1 = Converter::Convert<int32_t>(src.grayscale.value1);
    constexpr int32_t GRAYSCALE_MAX = 127;
    constexpr int32_t GRAYSCALE_MIN = 0;
    value0 = (value0 < GRAYSCALE_MIN || value0 > GRAYSCALE_MAX) ? 0 : value0;
    value1 = (value1 < GRAYSCALE_MIN || value1 > GRAYSCALE_MAX) ? 0 : value1;
    return BlurOption {
        .grayscale = { value0, value1 }
    };
}

template<>
BlurStyleOption Convert(const Ark_BackgroundBlurStyleOptions& src)
{
    BlurStyleOption dst;
    dst.colorMode = OptConvert<ThemeColorMode>(src.colorMode).value_or(dst.colorMode);
    dst.adaptiveColor = OptConvert<AdaptiveColor>(src.adaptiveColor).value_or(dst.adaptiveColor);
    if (auto scaleOpt = OptConvert<float>(src.scale); scaleOpt) {
        dst.scale = static_cast<double>(*scaleOpt);
    }
    dst.blurOption = OptConvert<BlurOption>(src.blurOptions).value_or(dst.blurOption);
    dst.policy = OptConvert<BlurStyleActivePolicy>(src.policy).value_or(dst.policy);
    dst.inactiveColor = OptConvert<Color>(src.inactiveColor).value_or(dst.inactiveColor);
    return dst;
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
BorderColorProperty Convert(const Ark_LocalizedEdgeColors& src)
{
    BorderColorProperty dst;
    LOGE("Converter::AssignTo(std::optional<BorderColorProperty> &, const Ark_LocalizedEdgeColors&)"
        " handles invalid structure"
    );
    // the src.left/.right should be used instead .start/.end, interface_sdk-js/issues/IB0DVD
    dst.leftColor = OptConvert<Color>(src.start);
    dst.topColor = OptConvert<Color>(src.top);
    dst.rightColor = OptConvert<Color>(src.end);
    dst.bottomColor = OptConvert<Color>(src.bottom);
    dst.multiValued = true;
    return dst;
}

template<>
BorderColorProperty Convert(const Ark_ResourceColor& src)
{
    BorderColorProperty dst;
    if (auto borderColor = Converter::OptConvert<Color>(src); borderColor.has_value()) {
        dst.SetColor(borderColor.value());
    }
    return dst;
}

template<>
BorderColorProperty Convert(const Ark_EdgesNumber& src)
{
    BorderColorProperty dst;
    dst.leftColor = OptConvert<Color>(src.left.value);
    dst.topColor = OptConvert<Color>(src.top.value);
    dst.rightColor = OptConvert<Color>(src.right.value);
    dst.bottomColor = OptConvert<Color>(src.bottom.value);
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
BorderRadiusProperty Convert(const Ark_LengthMetrics& src)
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
    if (auto width = Converter::Convert<Dimension>(src); !width.IsNegative()) {
        dst.SetBorderWidth(width);
        dst.multiValued = false;
    }
    return dst;
}

template<>
BorderWidthProperty Convert(const Ark_LocalizedEdgeWidths& src)
{
    BorderWidthProperty widthProperty;
    widthProperty.topDimen = Converter::OptConvert<Dimension>(src.top);
    Validator::ValidateNonNegative(widthProperty.topDimen);
    widthProperty.leftDimen = Converter::OptConvert<Dimension>(src.start);
    Validator::ValidateNonNegative(widthProperty.leftDimen);
    widthProperty.bottomDimen = Converter::OptConvert<Dimension>(src.bottom);
    Validator::ValidateNonNegative(widthProperty.bottomDimen);
    widthProperty.rightDimen = Converter::OptConvert<Dimension>(src.end);
    Validator::ValidateNonNegative(widthProperty.rightDimen);
    widthProperty.multiValued = true;
    return widthProperty;
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
    if (src.type == Ark_Tag::INTEROP_TAG_RESOURCE) {
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
PickerTextStyle Convert(const Ark_TextPickerTextStyle& src)
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
    style.minFontSize = Converter::OptConvert<Dimension>(src.minFontSize);
    style.maxFontSize = Converter::OptConvert<Dimension>(src.maxFontSize);
    style.textOverflow = Converter::OptConvert<TextOverflow>(src.overflow);
    return style;
}

template<>
PickerTime Convert(const Ark_Date& src)
{
    auto milliseconds = static_cast<int64_t>(src);
    const auto SEC_TO_MILLISEC = 1000L;
    auto seconds = static_cast<time_t>(milliseconds / SEC_TO_MILLISEC);
    struct std::tm time_info;
#ifdef WINDOWS_PLATFORM
    errno_t err = localtime_s(&time_info, &seconds);
    if (err) {
        LOGE("Invalid argument to localtime_s.");
    }
#else
    localtime_r(&seconds, &time_info);
#endif
    return PickerTime(time_info.tm_hour, time_info.tm_min, time_info.tm_sec);
}

template<>
PickerTime Convert(const Ark_TimePickerResult& src)
{
    auto second = Converter::OptConvert<uint32_t>(src.second).value_or(0);
    auto minute = Converter::OptConvert<uint32_t>(src.minute).value_or(0);
    auto hour = Converter::OptConvert<uint32_t>(src.hour).value_or(0);
    return PickerTime(hour, minute, second);
}

template<>
ButtonInfo Convert(const Ark_PickerDialogButtonStyle& src)
{
    ButtonInfo info;
    info.type = OptConvert<ButtonType>(src.type);
    info.buttonStyle = OptConvert<ButtonStyleMode>(src.style);
    info.role = OptConvert<ButtonRole>(src.role);

    if (auto fontSize = OptConvert<Dimension>(src.fontSize); fontSize) {
        Validator::ValidatePositive(fontSize);
        Validator::ValidateNonPercent(fontSize);
        info.fontSize = fontSize;
    }
    info.fontColor = OptConvert<Color>(src.fontColor);
    if (auto fontfamiliesOpt = OptConvert<FontFamilies>(src.fontFamily); fontfamiliesOpt) {
        info.fontFamily = fontfamiliesOpt->families;
    }
    info.fontWeight = OptConvert<FontWeight>(src.fontWeight);

    info.backgroundColor = OptConvert<Color>(src.backgroundColor);
    info.borderRadius = OptConvert<BorderRadiusProperty>(src.borderRadius);
    if (auto isPrimary = OptConvert<bool>(src.primary); isPrimary) {
        info.isPrimary = isPrimary.value();
    }

    return info;
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
    auto context = AceType::DynamicCast<PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);

    dst = shadowTheme->GetShadow(shadowStyle, context->GetColorMode());
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
    return Converter::Convert<std::string>(src);
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

template<>
PickerRangeType Convert(const Array_String& src)
{
    std::pair<bool, std::vector<NG::RangeContent>> dst;
    std::vector<std::string> tmp;
    tmp = Converter::Convert<std::vector<std::string>>(src);
    for (const auto& str : tmp) {
        NG::RangeContent content;
        content.icon_ = "";
        content.text_ = str;
        dst.second.push_back(content);
    }
    dst.first = false;
    return dst;
}

template<>
PickerRangeType Convert(const Array_Array_String& src)
{
    std::pair<bool, std::vector<NG::TextCascadePickerOptions>> dst;
    std::vector<std::vector<std::string>> tmp;
    auto tmpVector = Converter::Convert<std::vector<std::vector<std::string>>>(src);
    for (const auto& strVector : tmpVector) {
        NG::TextCascadePickerOptions value;
        for (const auto& str : strVector) {
            value.rangeResult.push_back(str);
        }
        dst.second.push_back(value);
    }
    dst.first = false;
    return dst;
}

template<>
PickerRangeType Convert(const Ark_Resource& src)
{
    std::pair<bool, std::vector<NG::RangeContent>> dst;
    auto tmp = Converter::OptConvert<std::vector<std::string>>(src);
    if (tmp) {
        for (const auto& str : tmp.value()) {
            NG::RangeContent content;
            content.icon_ = "";
            content.text_ = str;
            dst.second.push_back(content);
        }
    }
    dst.first = false;
    return dst;
}

template<>
PickerRangeType Convert(const Array_TextPickerRangeContent& src)
{
    std::pair<bool, std::vector<NG::RangeContent>> dst;
    dst.second = Converter::Convert<std::vector<NG::RangeContent>>(src);
    dst.first = true;
    return dst;
}

template<>
PickerRangeType Convert(const Array_TextCascadePickerRangeContent& src)
{
    std::pair<bool, std::vector<NG::TextCascadePickerOptions>> dst;
    dst.second = Converter::Convert<std::vector<NG::TextCascadePickerOptions>>(src);
    dst.first = true;
    return dst;
}

template<>
RangeContent Convert(const Ark_TextPickerRangeContent& src)
{
    RangeContent dst;
    auto iconOpt = OptConvert<std::string>(src.icon);
    auto textOpt = OptConvert<std::string>(src.text);
    dst.icon_ = iconOpt.value_or("");
    dst.text_ = textOpt.value_or("");
    return dst;
}

template<>
TextCascadePickerOptions Convert(const Ark_TextCascadePickerRangeContent& src)
{
    TextCascadePickerOptions dst;
    auto textOpt = OptConvert<std::string>(src.text);
    dst.rangeResult.push_back(textOpt.value_or(""));
    auto optionsOpt = OptConvert<std::vector<TextCascadePickerOptions>>(src.children);
    std::vector<TextCascadePickerOptions> empty;
    dst.children = optionsOpt.value_or(empty);
    return dst;
}

template<>
KeyboardOptions Convert(const Ark_KeyboardOptions& src)
{
    KeyboardOptions keyboardOptions;
    auto supportAvoidance = Converter::OptConvert<bool>(src.supportAvoidance);
    keyboardOptions.supportAvoidance = supportAvoidance.has_value() ? supportAvoidance.value() : false;
    return keyboardOptions;
}

template<>
EventTarget Convert(const Ark_EventTarget& src)
{
    static const Dimension Zero = Dimension(0.f);
    auto width = Converter::Convert<Dimension>(src.area.width);
    auto height = Converter::Convert<Dimension>(src.area.height);
    auto offsetX = Converter::OptConvert<Dimension>(src.area.position.x);
    auto offsetY = Converter::OptConvert<Dimension>(src.area.position.y);
    DimensionRect area(width, height,
        DimensionOffset(offsetX.value_or(Zero), offsetY.value_or(Zero)));
    auto globX = Converter::OptConvert<Dimension>(src.area.globalPosition.x);
    auto globY = Converter::OptConvert<Dimension>(src.area.globalPosition.y);
    auto id = Converter::OptConvert<std::string>(src.id);
    return EventTarget { id.value_or(""), "", area,
        DimensionOffset(globX.value_or(Zero), globY.value_or(Zero)) };
}

template<>
ImageResizableSlice Convert(const Ark_EdgeWidths& src)
{
    ImageResizableSlice dst;
    dst.left = OptConvert<Dimension>(src.left).value_or(dst.left);
    dst.right = OptConvert<Dimension>(src.right).value_or(dst.right);
    dst.top = OptConvert<Dimension>(src.top).value_or(dst.top);
    dst.bottom = OptConvert<Dimension>(src.bottom).value_or(dst.bottom);
    return dst;
}

template<>
NG::PreviewMenuOptions Convert(const Ark_PreviewMenuOptions& src)
{
    NG::PreviewMenuOptions previewMenuOptions;
    auto feedbackMode = Converter::OptConvert<HapticFeedbackMode>(src.hapticFeedbackMode);
    if (feedbackMode.has_value()) {
        previewMenuOptions.hapticFeedbackMode = feedbackMode.value();
    }
    return previewMenuOptions;
}

template<>
SelectMenuParam Convert(const Ark_SelectionMenuOptions& src)
{
    SelectMenuParam selectMenuParam = {
        .onAppear = [](int32_t start, int32_t end) {}, .onDisappear = []() {},
        .onMenuShow = [](int32_t start, int32_t end) {}, .onMenuHide = [](int32_t start, int32_t end) {},
        .previewMenuOptions = NG::PreviewMenuOptions()
    };
    auto optOnAppear = Converter::OptConvert<MenuOnAppearCallback>(src.onAppear);
    if (optOnAppear.has_value()) {
        selectMenuParam.onAppear =
            [arkCallback = CallbackHelper(optOnAppear.value())](int32_t start, int32_t end) {
                arkCallback.InvokeSync(Converter::ArkValue<Ark_Number>(start), Converter::ArkValue<Ark_Number>(end));
        };
    }
    auto optOnDisappear = Converter::OptConvert<Callback_Void>(src.onDisappear);
    if (optOnDisappear.has_value()) {
        selectMenuParam.onDisappear =
            [arkCallback = CallbackHelper(optOnDisappear.value())]() {
                arkCallback.InvokeSync();
        };
    }
    auto optOnMenuShow = Converter::OptConvert<MenuCallback>(src.onMenuShow);
    if (optOnMenuShow.has_value()) {
        selectMenuParam.onMenuShow =
            [arkCallback = CallbackHelper(optOnMenuShow.value())](int32_t start, int32_t end) {
                arkCallback.InvokeSync(Converter::ArkValue<Ark_Number>(start), Converter::ArkValue<Ark_Number>(end));
        };
    }
    auto optOnMenuHide = Converter::OptConvert<MenuCallback>(src.onMenuHide);
    if (optOnMenuHide.has_value()) {
        selectMenuParam.onMenuHide =
            [arkCallback = CallbackHelper(optOnMenuHide.value())](int32_t start, int32_t end) {
                arkCallback.InvokeSync(Converter::ArkValue<Ark_Number>(start), Converter::ArkValue<Ark_Number>(end));
        };
    }
    auto previewMenuOptions = Converter::OptConvert<NG::PreviewMenuOptions>(src.previewMenuOptions);
    if (previewMenuOptions.has_value()) {
        selectMenuParam.previewMenuOptions = previewMenuOptions.value();
    }
    return selectMenuParam;
}

template<>
std::pair<Dimension, Dimension> Convert(const Ark_Position& src)
{
    auto x = Converter::OptConvert<Dimension>(src.x);
    auto y = Converter::OptConvert<Dimension>(src.y);
    return std::make_pair(x.has_value() ? x.value() : Dimension(), y.has_value() ? y.value() : Dimension());
}

template<>
std::vector<uint32_t> Convert(const Ark_Buffer& src)
{
    std::vector<uint32_t> dataArray;
    auto array = (src.data != nullptr) ? static_cast<uint32_t*>(src.data) : nullptr;
    auto size = src.length / sizeof(uint32_t);
    if (array && size > 0) {
        for (int64_t idx = 0; idx < size; idx++) {
            dataArray.push_back(array[idx]);
        }
    }
    return dataArray;
}

template<>
PathShapeOptions Convert(const Ark_PathShapeOptions& value)
{
    return {
        .commands = Converter::OptConvert<std::string>(value.commands),
    };
}

template<>
ImageSpanSize Convert(const Ark_SizeOptions& value)
{
    auto width = OptConvert<CalcDimension>(value.width);
    auto height = OptConvert<CalcDimension>(value.height);
    Validator::ValidateNonNegative(width);
    Validator::ValidateNonNegative(height);
    return {
        .width = width,
        .height = height,
    };
}

template<>
TextRange Convert(const Ark_TextRange& src)
{
    TextRange dst; // initialized by default
    auto start = Converter::OptConvert<int32_t>(src.start);
    auto end = Converter::OptConvert<int32_t>(src.end);
    if (start.has_value()) {
        dst.start = start.value();
    }
    if (end.has_value()) {
        dst.end = end.value();
    }
    return dst;
}

template<>
OHOS::Ace::TextMetrics Convert(const Ark_TextMetrics& src)
{
    OHOS::Ace::TextMetrics dst;
    dst.actualBoundingBoxAscent = static_cast<double>(Converter::Convert<float>(src.actualBoundingBoxAscent));
    dst.actualBoundingBoxDescent = static_cast<double>(Converter::Convert<float>(src.actualBoundingBoxDescent));
    dst.actualBoundingBoxLeft = static_cast<double>(Converter::Convert<float>(src.actualBoundingBoxLeft));
    dst.actualBoundingBoxRight = static_cast<double>(Converter::Convert<float>(src.actualBoundingBoxRight));
    dst.alphabeticBaseline = static_cast<double>(Converter::Convert<float>(src.alphabeticBaseline));
    dst.emHeightAscent = static_cast<double>(Converter::Convert<float>(src.emHeightAscent));
    dst.emHeightDescent = static_cast<double>(Converter::Convert<float>(src.emHeightDescent));
    dst.fontBoundingBoxAscent = static_cast<double>(Converter::Convert<float>(src.fontBoundingBoxAscent));
    dst.fontBoundingBoxDescent = static_cast<double>(Converter::Convert<float>(src.fontBoundingBoxDescent));
    dst.hangingBaseline = static_cast<double>(Converter::Convert<float>(src.hangingBaseline));
    dst.ideographicBaseline = static_cast<double>(Converter::Convert<float>(src.ideographicBaseline));
    dst.width = static_cast<double>(Converter::Convert<float>(src.width));
    dst.height = static_cast<double>(Converter::Convert<float>(src.height));
    return dst;
}

template<>
std::set<SourceTool> Convert(const Array_SourceTool& src)
{
    std::set<SourceTool> dst = {};
    auto length = Converter::Convert<int>(src.length);
    for (int i = 0; i < length; i++) {
        auto sourceToolItem = *(src.array + i);
        SourceTool item = Converter::Convert<std::optional<SourceTool>>(sourceToolItem).value_or(SourceTool::UNKNOWN);
        dst.insert(item);
    }
    return dst;
}
template<>
std::set<std::string> Convert(const Array_UniformDataType& src)
{
    std::set<std::string> dst = {};
    std::optional<std::string> convVal;
    auto tmp = Converter::OptConvert<std::vector<Ark_UniformDataType>>(src);
    if (!tmp.has_value()) return dst;
    for (Ark_UniformDataType arkVal : tmp.value()) {
        convVal = Converter::OptConvert<std::string>(arkVal);
        if (convVal.has_value()) {
            dst.insert(convVal.value());
        }
    }
    return dst;
}
template<>
RefPtr<ShapeRect> Convert(const Ark_Rect& src)
{
    auto dst = AceType::MakeRefPtr<ShapeRect>();
    float left = Converter::Convert<float>(src.left);
    float top = Converter::Convert<float>(src.top);
    float right = Converter::Convert<float>(src.right);
    float bottom = Converter::Convert<float>(src.bottom);
    auto width = Dimension(right - left);
    auto height = Dimension(bottom - top);
    auto deltaX = Dimension(left);
    auto deltaY = Dimension(top);
    auto position = DimensionOffset(deltaX, deltaY);
    dst->SetWidth(width);
    dst->SetHeight(height);
    dst->SetPosition(position);
    return dst;
}
template<>
Radius Convert(const Ark_Vector2& src)
{
    Radius dst;
    auto x = Converter::Convert<float>(src.x);
    auto y = Converter::Convert<float>(src.y);
    dst.SetX(Dimension(x));
    dst.SetY(Dimension(y));
    return dst;
}
template<>
Corner Convert(const Ark_CornerRadius& src)
{
    return Corner {
        .topLeftRadius = Converter::Convert<Radius>(src.topLeft),
        .topRightRadius = Converter::Convert<Radius>(src.topRight),
        .bottomLeftRadius = Converter::Convert<Radius>(src.bottomLeft),
        .bottomRightRadius = Converter::Convert<Radius>(src.bottomRight),
    };
}
template<>
RefPtr<ShapeRect> Convert(const Ark_RoundRect& src)
{
    auto dst = Converter::Convert<RefPtr<ShapeRect>>(src.rect);
    auto corners = Converter::Convert<Corner>(src.corners);
    dst->SetTopLeftRadius(corners.topLeftRadius);
    dst->SetTopRightRadius(corners.topRightRadius);
    dst->SetBottomLeftRadius(corners.bottomLeftRadius);
    dst->SetBottomRightRadius(corners.bottomRightRadius);
    return dst;
}
template<>
RefPtr<Circle> Convert(const Ark_Circle& src)
{
    auto dst = AceType::MakeRefPtr<Circle>();
    auto centerX = Converter::Convert<float>(src.centerX);
    auto centerY = Converter::Convert<float>(src.centerY);
    auto radius = Converter::Convert<float>(src.radius);
    auto position = DimensionOffset(Dimension(centerX), Dimension(centerY));
    dst->SetPosition(position);
    dst->SetRadius(Dimension(radius));
    return dst;
}
template<>
std::string Convert(const Ark_CommandPath& src)
{
    return Converter::Convert<std::string>(src.commands);
}

template<>
NavigationOptions Convert(const Ark_NavigationOptions& src)
{
    return {
        .animated = Converter::OptConvert<bool>(src.animated).value_or(true),
        .launchMode = Converter::OptConvert<LaunchMode>(src.launchMode).value_or(LaunchMode::STANDARD)
    };
}

template<>
void AssignCast(std::optional<NavigationTitlebarOptions>& dst, const Ark_NavigationTitleOptions& value)
{
    dst = NavigationTitlebarOptions();
    dst->bgOptions = Converter::Convert<NavigationBackgroundOptions>(value);
    dst->brOptions = Converter::Convert<NavigationBarOptions>(value);
}

template<>
NG::NavigationBackgroundOptions Convert(const Ark_NavigationTitleOptions& src)
{
    NG::NavigationBackgroundOptions options;
    options.color.reset();
    options.blurStyleOption.reset();
    options.effectOption.reset();
    BlurStyleOption styleOptions;
    EffectOption effectOption;

    if (src.backgroundColor.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        options.color = Converter::OptConvert<Color>(src.backgroundColor.value);
    }

    if (src.backgroundBlurStyleOptions.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        styleOptions = Converter::Convert<BlurStyleOption>(src.backgroundBlurStyleOptions.value);
    }

    if (src.backgroundBlurStyle.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto blurStyle = static_cast<int32_t>(src.backgroundBlurStyle.value);
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            styleOptions.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }

    if (src.backgroundEffect.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        effectOption = Converter::Convert<EffectOption>(src.backgroundEffect.value);
    }
    options.blurStyleOption = styleOptions;
    options.effectOption = effectOption;
    return options;
}

template<>
NG::NavigationBarOptions Convert(const Ark_NavigationTitleOptions& src)
{
    NG::NavigationBarOptions options;
    options.paddingStart.reset();
    options.paddingEnd.reset();
    options.barStyle.reset();
    if (src.barStyle.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto barStyle = static_cast<int32_t>(src.barStyle.value);
        if (barStyle >= static_cast<int32_t>(NG::BarStyle::STANDARD) &&
            barStyle <= static_cast<int32_t>(NG::BarStyle::SAFE_AREA_PADDING)) {
            options.barStyle = static_cast<NG::BarStyle>(barStyle);
        } else {
            options.barStyle = NG::BarStyle::STANDARD;
        }
    }
    if (src.paddingStart.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        options.paddingStart = Converter::Convert<CalcDimension>(src.paddingStart.value);
    }
    if (src.paddingEnd.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        options.paddingEnd = Converter::Convert<CalcDimension>(src.paddingEnd.value);
    }
    return options;
}

template<>
void AssignCast(std::optional<NG::NavigationTransition>& dst, const Opt_NavigationAnimatedTransition& src)
{
    NG::NavigationTransition transition;
    dst = transition;
    if (src.tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        dst->isValid = false;
        return;
    }
    dst->isValid = true;
    if (src.value.isInteractive.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        dst->interactive = Converter::Convert<bool>(src.value.isInteractive.value);
    } else {
        dst->interactive = false;
    }
    if (src.value.timeout.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        dst->timeout = Converter::Convert<int32_t>(src.value.timeout.value);
    }
    if (!dst->interactive) {
        dst->timeout = dst->timeout < 0 ? 1000 : dst->timeout;
    }
    if (src.value.onTransitionEnd.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto onTransitionEnd = [callback = CallbackHelper(src.value.onTransitionEnd.value)](bool success) {
            auto isSuccess = Converter::ArkValue<Ark_Boolean>(success);
            callback.Invoke(isSuccess);
        };
        dst->endCallback = std::move(onTransitionEnd);
    }
    auto transitionCallback = [callback = CallbackHelper(src.value.transition)](const RefPtr<NavigationTransitionProxy>& transitionProxy) {
        auto transition = Converter::ArkValue<Ark_NavigationTransitionProxy>(transitionProxy);
        callback.Invoke(transition);
    };
    dst->transition = std::move(transitionCallback);
}

template<>
void AssignCast(std::optional<ShapePoint>& dst, const Opt_ShapePoint& src)
{
    if (src.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        dst = Converter::Convert<ShapePoint>(src.value);
    }
}
} // namespace OHOS::Ace::NG::Converter
