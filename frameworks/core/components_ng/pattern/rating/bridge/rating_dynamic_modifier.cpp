/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/interfaces/native/node/rating_modifier.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
RatingModel* GetRatingModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("rating");
    static RatingModel* instance = loader ? reinterpret_cast<RatingModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
constexpr int32_t STARS_DEFAULT = 5;
constexpr double STEPS_DEFAULT = 0.5;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void SetStars(ArkUINodeHandle node, int32_t value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetStars(frameNode, value);
}

void SetRatingStepSize(ArkUINodeHandle node, ArkUI_Float32 value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetStepSize(frameNode, value);
}

void SetStarStyle(ArkUINodeHandle node,
    const char* backgroundUri, const char* foregroundUri, const char* secondaryUri)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string backgroundUriStr = backgroundUri;
    if (backgroundUriStr.empty()) {
        RatingModelNG::SetBackgroundSrc(frameNode, "", true);
    } else {
        RatingModelNG::SetBackgroundSrc(frameNode, backgroundUriStr, false);
    }

    std::string foregroundUriStr = foregroundUri;
    if (foregroundUriStr.empty()) {
        RatingModelNG::SetForegroundSrc(frameNode, "", true);
    } else {
        RatingModelNG::SetForegroundSrc(frameNode, foregroundUriStr, false);
    }

    std::string secondaryUriStr = secondaryUri;
    if (!secondaryUriStr.empty()) {
        RatingModelNG::SetSecondarySrc(frameNode, secondaryUriStr, false);
    } else if (!backgroundUriStr.empty()) {
        RatingModelNG::SetSecondarySrc(frameNode, backgroundUriStr, false);
    } else {
        RatingModelNG::SetSecondarySrc(frameNode, "", true);
    }
}

void SetStarStylePtr(ArkUINodeHandle node, const char* backgroundUri,
    const char* foregroundUri, const char* secondaryUri, const ArkUIRatingStyleStruct& resObj)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SetStarStyle(node, backgroundUri, foregroundUri, secondaryUri);
    if (SystemProperties::ConfigChangePerform()) {
        FrameNode* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        if (resObj.backgroundResObj) {
            auto* backgroundObj = reinterpret_cast<ResourceObject*>(resObj.backgroundResObj);
            auto backgroundResObjPtr = AceType::Claim(backgroundObj);
            RatingModelNG::CreateWithMediaResourceObj(frameNode, backgroundResObjPtr, RatingUriType::BACKGROUND_URI);
        } else {
            RatingModelNG::CreateWithMediaResourceObj(frameNode, nullptr, RatingUriType::BACKGROUND_URI);
        }

        if (resObj.foregroundResObj) {
            auto* foregroundObj = reinterpret_cast<ResourceObject*>(resObj.foregroundResObj);
            auto foregroundResObjPtr = AceType::Claim(foregroundObj);
            RatingModelNG::CreateWithMediaResourceObj(frameNode, foregroundResObjPtr, RatingUriType::FOREGROUND_URI);
        } else {
            RatingModelNG::CreateWithMediaResourceObj(frameNode, nullptr, RatingUriType::FOREGROUND_URI);
        }

        if (resObj.secondaryResObj) {
            auto* secondaryObj = reinterpret_cast<ResourceObject*>(resObj.secondaryResObj);
            auto secondaryResObjPtr = AceType::Claim(secondaryObj);
            RatingModelNG::CreateWithMediaResourceObj(frameNode, secondaryResObjPtr, RatingUriType::SECONDARY_URI);
        } else {
            RatingModelNG::CreateWithMediaResourceObj(frameNode, nullptr, RatingUriType::SECONDARY_URI);
        }
    }
}

void SetOnChange(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        RatingModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        RatingModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetStars(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetStars(frameNode, STARS_DEFAULT);
}

void ResetRatingStepSize(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetStepSize(frameNode, STEPS_DEFAULT);
}

void ResetStarStyle(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetBackgroundSrc(frameNode, "", true);
    RatingModelNG::SetForegroundSrc(frameNode, "", true);
    RatingModelNG::SetSecondarySrc(frameNode, "", true);
    if (SystemProperties::ConfigChangePerform()) {
        RatingModelNG::CreateWithMediaResourceObj(frameNode, nullptr, RatingUriType::BACKGROUND_URI);
        RatingModelNG::CreateWithMediaResourceObj(frameNode, nullptr, RatingUriType::FOREGROUND_URI);
        RatingModelNG::CreateWithMediaResourceObj(frameNode, nullptr, RatingUriType::SECONDARY_URI);
    }
}

void SetRatingOptions(ArkUINodeHandle node, ArkUI_Float64 rating, ArkUI_Bool indicator)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetRatingOptions(frameNode, rating, static_cast<bool>(indicator));
}

void ResetOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetOnChange(frameNode, nullptr);
}

ArkUINodeHandle CreateFrameNode(int32_t nodeId)
{
    auto frameNode = RatingModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

void CreateRating(ArkUI_Float64 rating, ArkUI_Bool indicator)
{
    RatingModelNG::CreateRating(rating, static_cast<bool>(indicator));
}

void SetOnChangeEvent(void* callback)
{
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        FrameNode* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        RatingModelNG::SetOnChangeEvent(frameNode, std::move(*onChange));
    }
}

#ifndef CROSS_PLATFORM
void SetStarsImpl(ArkUINodeHandle node, int32_t value)
{
    GetRatingModelImpl()->SetStars(value);
}

void SetRatingStepSizeImpl(ArkUINodeHandle node, ArkUI_Float32 value)
{
    GetRatingModelImpl()->SetStepSize(value);
}

void SetStarStyleImpl(ArkUINodeHandle node,
    const char* backgroundUri, const char* foregroundUri, const char* secondaryUri)
{
    std::string backgroundUriStr = backgroundUri;
    if (backgroundUriStr.empty()) {
        GetRatingModelImpl()->SetBackgroundSrc("", true);
    } else {
        GetRatingModelImpl()->SetBackgroundSrc(backgroundUriStr, false);
    }

    std::string foregroundUriStr = foregroundUri;
    if (foregroundUriStr.empty()) {
        GetRatingModelImpl()->SetForegroundSrc("", true);
    } else {
        GetRatingModelImpl()->SetForegroundSrc(foregroundUriStr, false);
    }

    std::string secondaryUriStr = secondaryUri;
    if (!secondaryUriStr.empty()) {
        GetRatingModelImpl()->SetSecondarySrc(secondaryUriStr, false);
    } else if (!backgroundUriStr.empty()) {
        GetRatingModelImpl()->SetSecondarySrc(backgroundUriStr, false);
    } else {
        GetRatingModelImpl()->SetSecondarySrc("", true);
    }
}

void SetStarStylePtrImpl(ArkUINodeHandle node, const char* backgroundUri,
    const char* foregroundUri, const char* secondaryUri, const ArkUIRatingStyleStruct& resObj)
{
    SetStarStyleImpl(node, backgroundUri, foregroundUri, secondaryUri);
    if (SystemProperties::ConfigChangePerform()) {
        if (resObj.backgroundResObj) {
            auto* backgroundObj = reinterpret_cast<ResourceObject*>(resObj.backgroundResObj);
            auto backgroundResObjPtr = AceType::Claim(backgroundObj);
            GetRatingModelImpl()->CreateWithMediaResourceObj(backgroundResObjPtr, RatingUriType::BACKGROUND_URI);
        } else {
            GetRatingModelImpl()->CreateWithMediaResourceObj(nullptr, RatingUriType::BACKGROUND_URI);
        }

        if (resObj.foregroundResObj) {
            auto* foregroundObj = reinterpret_cast<ResourceObject*>(resObj.foregroundResObj);
            auto foregroundResObjPtr = AceType::Claim(foregroundObj);
            GetRatingModelImpl()->CreateWithMediaResourceObj(foregroundResObjPtr, RatingUriType::FOREGROUND_URI);
        } else {
            GetRatingModelImpl()->CreateWithMediaResourceObj(nullptr, RatingUriType::FOREGROUND_URI);
        }

        if (resObj.secondaryResObj) {
            auto* secondaryObj = reinterpret_cast<ResourceObject*>(resObj.secondaryResObj);
            auto secondaryResObjPtr = AceType::Claim(secondaryObj);
            GetRatingModelImpl()->CreateWithMediaResourceObj(secondaryResObjPtr, RatingUriType::SECONDARY_URI);
        } else {
            GetRatingModelImpl()->CreateWithMediaResourceObj(nullptr, RatingUriType::SECONDARY_URI);
        }
    }
}

void SetOnChangeImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetRatingModelImpl()->SetOnChange(std::move(*onChange));
    }
}

void ResetStarsImpl(ArkUINodeHandle node)
{
    GetRatingModelImpl()->SetStars(STARS_DEFAULT);
}

void ResetRatingStepSizeImpl(ArkUINodeHandle node)
{
    GetRatingModelImpl()->SetStepSize(STEPS_DEFAULT);
}

void ResetStarStyleImpl(ArkUINodeHandle node)
{
    GetRatingModelImpl()->SetBackgroundSrc("", true);
    GetRatingModelImpl()->SetForegroundSrc("", true);
    GetRatingModelImpl()->SetSecondarySrc("", true);
}

void SetRatingOptionsImpl(ArkUINodeHandle node, ArkUI_Float64 rating, ArkUI_Bool indicator) {}

void ResetOnChangeImpl(ArkUINodeHandle node) {}

ArkUINodeHandle CreateFrameNodeImpl(int32_t nodeId)
{
    return nullptr;
}

void CreateRatingImpl(ArkUI_Float64 rating, ArkUI_Bool indicator)
{
    GetRatingModelImpl()->Create(rating, static_cast<bool>(indicator));
}

void SetOnChangeEventImpl(void* callback)
{
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
        GetRatingModelImpl()->SetOnChangeEvent(std::move(*onChange));
    }
}
#endif

const ArkUIRatingModifier* GetRatingDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN();
        static const ArkUIRatingModifier modifier = {
            .setStars = SetStarsImpl,
            .setRatingStepSize = SetRatingStepSizeImpl,
            .setStarStyle = SetStarStyleImpl,
            .setOnChange = SetOnChangeImpl,
            .resetStars = ResetStarsImpl,
            .resetRatingStepSize = ResetRatingStepSizeImpl,
            .resetStarStyle = ResetStarStyleImpl,
            .setRatingOptions = SetRatingOptionsImpl,
            .resetOnChange = ResetOnChangeImpl,
            .setStarStylePtr = SetStarStylePtrImpl,
            .createFrameNode = CreateFrameNodeImpl,
            .createRating = CreateRatingImpl,
            .setOnChangeEvent = SetOnChangeEventImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUIRatingModifier modifier = {
        .setStars = SetStars,
        .setRatingStepSize = SetRatingStepSize,
        .setStarStyle = SetStarStyle,
        .setOnChange = SetOnChange,
        .resetStars = ResetStars,
        .resetRatingStepSize = ResetRatingStepSize,
        .resetStarStyle = ResetStarStyle,
        .setRatingOptions = SetRatingOptions,
        .resetOnChange = ResetOnChange,
        .setStarStylePtr = SetStarStylePtr,
        .createFrameNode = CreateFrameNode,
        .createRating = CreateRating,
        .setOnChangeEvent = SetOnChangeEvent,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}

const CJUIRatingModifier* GetCJUIRatingModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const CJUIRatingModifier modifier = {
        .setStars = SetStars,
        .setRatingStepSize = SetRatingStepSize,
        .setStarStyle = SetStarStyle,
        .resetStars = ResetStars,
        .resetRatingStepSize = ResetRatingStepSize,
        .resetStarStyle = ResetStarStyle,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}

}
