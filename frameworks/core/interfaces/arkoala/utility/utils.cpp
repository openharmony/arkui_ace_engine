/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "utils.h"

namespace OHOS::Ace::NG::Utils
{
constexpr int32_t CASE_0 = 0;
constexpr int32_t CASE_1 = 1;
constexpr int32_t CASE_2 = 2;

RefPtr<ThemeConstants> GetThemeConstants(FrameNode* node, Ark_CharPtr bundleName, Ark_CharPtr moduleName)
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
    
    auto pipelineContext = node->GetContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetThemeConstants(bundleName, moduleName);
}

std::string ResourceToString(FrameNode* node, const Ark_Resource& resource)
{
    std::string src;
    ImageResource image = Convert(resource);

    auto themeConstants = GetThemeConstants(node, image.bundleName.c_str(), image.moduleName.c_str());

    if (themeConstants) {
        if (image.type == static_cast<int32_t>(ResourceType::RAWFILE)) {
            if (image.params.size() > 0) {
                src = themeConstants->GetRawfile(image.params.at(0));
            }
        }
        if (image.type == static_cast<int32_t>(ResourceType::MEDIA)) {
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

ImageResource Convert(const Ark_Resource& value)
{
    ImageResource resource;
    resource.id = value.id.i32;
    resource.type = value.type.i32;
    resource.bundleName = std::string(value.bundleName.chars);
    resource.moduleName = std::string(value.moduleName.chars);
    if (value.params.tag != ARK_TAG_UNDEFINED) {
        for (int i = 0; i < value.params.value.length; i++) {
            resource.params[i] = std::string(value.params.value.array[i].chars);
        }
    }
    return resource;
}

ImageSourceInfo Convert(FrameNode* node, const Type_ImageInterface_setImageOptions_Arg0& value)
{
    ImageSourceInfo info;

    switch (value.selector) {
        case CASE_0: {// CustomObject
            // TODO: not implemented
            break;
        }
        case CASE_1: {
            switch (value.value1.selector) {
                case CASE_0: { // String
                    info = ImageSourceInfo(value.value1.value0.chars);
                    break;
                }
                case CASE_1: { // ArkResource
                    info = ImageSourceInfo(ResourceToString(node, value.value1.value1), value.value1.value1.bundleName.chars, value.value1.value1.moduleName.chars);
                    break;
                } 
                default:
                    LOGE("Unexpected src->selector: %{public}d\n", value.value1.selector);
            }
            break;
        }
        case CASE_2: { // CustomObject
            // TODO: not implemented
            break;
        }
        default:
            LOGE("Unexpected src->selector: %{public}d\n", value.selector);
            break;
    }

    return info;
}

ImageSourceInfo Convert(FrameNode* node, const Type_ImageAttribute_alt_Arg0& value)
{
    ImageSourceInfo info;

    switch (value.selector) {
        case CASE_0: { // String
            info = ImageSourceInfo(value.value0.chars);
            break;
        }
        case CASE_1: { // Resource
            info = ImageSourceInfo(ResourceToString(node, value.value1), value.value1.bundleName.chars, value.value1.moduleName.chars);
            break;
        }
        case CASE_2: { // CustomObject
            // TODO: not implemented
            break;
        }
        default:
            LOGE("Unexpected src->selector: %{public}d\n", value.selector);
            break;
    }

    return info;
}
}