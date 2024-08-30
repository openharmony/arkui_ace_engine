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

constexpr int32_t OFFSET_0 = 0;
constexpr int32_t OFFSET_1 = 1;
constexpr int32_t OFFSET_2 = 2;

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

bool ParseColorFromArkResource(const Ark_Resource &res, Color &result)
{
    constexpr int32_t ERROR_COLOR_ID = -1;

    auto themeConstants = NodeModifier::GetThemeConstants(0, res.bundleName.chars, res.moduleName.chars);
    CHECK_NULL_RETURN(themeConstants, false);

    CHECK_NULL_RETURN(res.id.tag == ARK_TAG_INT32, false);
    auto resId = res.id.i32;
    if (resId == ERROR_COLOR_ID) {
        CHECK_NULL_RETURN(res.params.value.array, false);
        std::string colorName = res.params.value.array[0].chars;
        result = themeConstants->GetColorByName(colorName);
        return true;
    }

    CHECK_NULL_RETURN(res.type.tag == ARK_TAG_INT32, false);
    auto type = res.type.i32;
    if (type == static_cast<int32_t>(NodeModifier::ResourceType::STRING)) {
        auto value = themeConstants->GetString(resId);
        return Color::ParseColorString(value, result);
    }
    if (type == static_cast<int32_t>(NodeModifier::ResourceType::INTEGER)) {
        auto value = themeConstants->GetInt(resId);
        result = Color(ColorAlphaAdapt(value));
        return true;
    }
    if (type == static_cast<int32_t>(NodeModifier::ResourceType::COLOR)) {
        result = themeConstants->GetColor(resId);
        return true;
    }
    return false;
}

static std::string ResourceToString(Ark_NativePointer node, const Ark_Resource& resource)
{
    std::string src;
    ImageResource image = Convert(resource);

    auto themeConstants = NodeModifier::GetThemeConstants(reinterpret_cast<Ark_NodeHandle>(node),
                                                          image.bundleName.c_str(), image.moduleName.c_str());

    if (themeConstants) {
        if (image.type == static_cast<int32_t>(NodeModifier::ResourceType::RAWFILE)) {
            if (image.params.size() > 0) {
                src = themeConstants->GetRawfile(image.params.at(0));
            }
        }
        if (image.type == static_cast<int32_t>(NodeModifier::ResourceType::MEDIA)) {
            if (image.id == -1) {
                if (image.params.size() > 0) {
                    src = themeConstants->GetMediaPathByName(image.params.at(0));
                }
            } else {
                src = themeConstants->GetMediaPath(image.id);
            }
        }
    }
    return src;
}

template<>
std::string Convert(const Ark_Resource& resource)
{
    return ResourceToString(nullptr, resource);
}

ImageResource Convert(const Ark_Resource& value)
{
    ImageResource resource;
    resource.id = value.id.i32;
    resource.type = value.type.i32;
    resource.bundleName = std::string(value.bundleName.chars);
    resource.moduleName = std::string(value.moduleName.chars);
    if (value.params.tag != ARK_TAG_UNDEFINED && value.params.value.length > 0) {
        resource.params.reserve(value.params.value.length);
        for (int i = 0; i < value.params.value.length; i++) {
            resource.params.push_back(value.params.value.array[i].chars);
        }
    }
    return resource;
}

ImageSourceInfo Convert(Ark_NativePointer node, const Type_ImageInterface_setImageOptions_Arg0& value)
{
    ImageSourceInfo info;

    switch (value.selector) {
        case OFFSET_0: { // CustomObject
            break;
        }
        case OFFSET_1: {
            switch (value.value1.selector) {
                case OFFSET_0: { // String
                    info = ImageSourceInfo(value.value1.value0.chars);
                    break;
                }
                case OFFSET_1: { // ArkResource
                    info = ImageSourceInfo(ResourceToString(node, value.value1.value1),
                                           value.value1.value1.bundleName.chars,
                                           value.value1.value1.moduleName.chars);
                    break;
                }
                default:
                    LOGE("Unexpected src->selector: %{public}d\n", value.value1.selector);
            }
            break;
        }
        case OFFSET_2: { // CustomObject
            break;
        }
        default:
            LOGE("Unexpected src->selector: %{public}d\n", value.selector);
            break;
    }

    return info;
}

ImageSourceInfo Convert(Ark_NativePointer node, const Type_ImageAttribute_alt_Arg0& value)
{
    ImageSourceInfo info;

    switch (value.selector) {
        case OFFSET_0: { // String
            info = ImageSourceInfo(value.value0.chars);
            break;
        }
        case OFFSET_1: { // Resource
            info = ImageSourceInfo(ResourceToString(node, value.value1),
                                   value.value1.bundleName.chars,
                                   value.value1.moduleName.chars);
            break;
        }
        case OFFSET_2: { // CustomObject
            break;
        }
        default:
            LOGE("Unexpected src->selector: %{public}d\n", value.selector);
            break;
    }

    return info;
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
            auto srcArkStr = std::get_if<Ark_String>(&familiesResStr.value());
            if (srcArkStr != nullptr) {
                auto srcStr = Converter::Convert<std::string>(*srcArkStr);
                if (!srcStr.empty()) {
                    familiesStr = srcStr;
                } else {
                    LOGE("ARKOALA SearchAttributeModifier.FonFamilyResource not implemented.");
                }
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
} // namespace OHOS::Ace::NG::Converter
