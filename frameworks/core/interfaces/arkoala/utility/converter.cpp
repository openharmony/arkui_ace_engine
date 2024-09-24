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

#include "core/interfaces/native/node/node_api.h"
#include "converter.h"

namespace OHOS::Ace::NG::Converter {
Ark_TouchObject ConvertTouchInfo(OHOS::Ace::TouchLocationInfo& info)
{
    Ark_TouchObject touch;
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

    return touch;
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
    if (resource.id.tag == ARK_TAG_INT32 && resource.type.tag == ARK_TAG_INT32) {
        id_ = resource.id.i32;
        type_ = static_cast<NodeModifier::ResourceType>(resource.type.i32);
        bundleName_ = std::string(resource.bundleName.chars);
        moduleName_ = std::string(resource.moduleName.chars);
        if (resource.params.tag != ARK_TAG_UNDEFINED) {
            for (int i = 0; i < resource.params.value.length; i++) {
                params_.emplace_back(resource.params.value.array[i].chars);
            }
        }

        themeConstants_ = NodeModifier::GetThemeConstants(nullptr, bundleName_.c_str(), moduleName_.c_str());
    } else {
        LOGE("ResourceConverter illegal id/type tag: id.tag = %{public}d, type.tag = %{public}d",
             resource.id.tag, resource.type.tag);
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
            } else if (params_.size() > 0) {
                result = themeConstants_->GetStringByName(params_.at(0));
            } else {
                LOGE("Unknown resource value");
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
        return themeConstants_->GetStringArray(id_);
    }
    return std::nullopt;
}

std::optional<Dimension> ResourceConverter::ToDimension()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == NodeModifier::ResourceType::STRING) {
        return themeConstants_->GetDimension(id_);
    }
    return std::nullopt;
}

std::optional<float> ResourceConverter::ToFloat()
{
    CHECK_NULL_RETURN(themeConstants_, std::nullopt);
    if (type_ == NodeModifier::ResourceType::FLOAT) {
        return static_cast<float>(themeConstants_->GetDouble(id_));
    }
    return std::nullopt;
}

std::optional<Color> ResourceConverter::ToColor()
{
    std::optional<Color> result;
    if (id_ == -1 && params_.size() > 0) {
        CHECK_NULL_RETURN(themeConstants_, result);
        result = themeConstants_->GetColorByName(params_[0]);
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

Shadow ToShadow(const Ark_ShadowOptions& src)
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
Font Convert(const Ark_Font& src)
{
        Font font;
        // cannot be moved to the ace_engine_types
        using UnionStringResource = std::variant<Ark_String, Ark_Resource>;
        auto familiesResStr = OptConvert<UnionStringResource>(src.family);
        std::string familiesStr;
        if (familiesResStr) {
            if (auto srcArkStr = std::get_if<Ark_String>(&familiesResStr.value());
                srcArkStr != nullptr) {
                familiesStr = Converter::Convert<std::string>(*srcArkStr);
            } else {
                LOGE("ARKOALA SearchAttributeModifier.FonFamilyResource not implemented.");
            }
        }
        std::istringstream families(familiesStr);
        std::vector<std::string> fontFamilies;
        for (std::string family; std::getline(families, family, ',');) {
            StringUtils::TrimStr(family);
            fontFamilies.push_back(family);
        }
        font.fontFamilies = fontFamilies;
        auto fontSize = OptConvert<Dimension>(src.size);
        if (fontSize) {
            if (fontSize->IsNegative()) fontSize.reset();
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
} // namespace OHOS::Ace::NG::Converter
