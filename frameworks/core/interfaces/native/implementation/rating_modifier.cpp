/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RatingModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = RatingModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // RatingModifier
namespace RatingInterfaceModifier {
void SetRatingOptionsImpl(Ark_NativePointer node,
                          const Opt_RatingOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<float> rating {std::nullopt};
    std::optional<double> dRating {std::nullopt};
    std::optional<bool> indicator {std::nullopt};
    if (!options) {
        // need check
        // RatingModelNG::SetRatingOptions(frameNode, dRating, indicator);
        return;
    }
    auto optOptions = Converter::OptConvert<Ark_RatingOptions>(*options);
    if (!optOptions.has_value()) {
        // need check
        // RatingModelNG::SetRatingOptions(frameNode, dRating, indicator);
        return;
    }
    auto arkOptions = optOptions.value();
    rating = Converter::Convert<float>(arkOptions.rating);
    indicator = Converter::OptConvert<bool>(arkOptions.indicator);
    Validator::ValidateNonNegative(rating);
    dRating = FloatToDouble(rating);
    // need check
    // RatingModelNG::SetRatingOptions(frameNode, dRating, indicator);
}
} // RatingInterfaceModifier
namespace RatingAttributeModifier {
void StarsImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optVal = Converter::OptConvert<float>(*value);
    Validator::ValidateNonNegative(optVal);
    auto optdVal = FloatToDouble(optVal);
    // need check
    // RatingModelNG::SetStars(frameNode,  optdVal);
}
void StepSizeImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optVal = Converter::OptConvert<float>(*value);
    static const float stepSizeMin = 0.1;
    Validator::ValidateGreatOrEqual(optVal, stepSizeMin);
    auto optdVal = FloatToDouble(optVal);
    // need check
    // RatingModelNG::SetStepSize(frameNode,  optdVal);
}
void StarStyleImpl(Ark_NativePointer node,
                   const Ark_StarStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string backgroundUri = Converter::Convert<std::string>(value->backgroundUri);
    RatingModelNG::SetBackgroundSrc(frameNode, backgroundUri,  backgroundUri.empty());
    std::string foregroundUri = Converter::Convert<std::string>(value->foregroundUri);
    RatingModelNG::SetForegroundSrc(frameNode, foregroundUri, foregroundUri.empty());
    auto optSecondaryUri = Converter::OptConvert<std::string>(value->secondaryUri);
    std::string secondaryUri;
    if (optSecondaryUri.has_value()) {
        secondaryUri = optSecondaryUri.value();
        RatingModelNG::SetSecondarySrc(frameNode, secondaryUri, false);
    } else {
        RatingModelNG::SetSecondarySrc(frameNode, "", true);
    }
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [arkCallback = CallbackHelper(*value)](const std::string& value) {
        Ark_Number convValue = Converter::ArkValue<Ark_Number>(std::stof(value));
        arkCallback.Invoke(convValue);
    };
    RatingModelNG::SetOnChange(frameNode, onChange);
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA RatingInterfaceModifier::ContentModifier is not implemented.");
}
void _onChangeEvent_ratingImpl(Ark_NativePointer node,
                               const Callback_Number_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const std::string& value) {
        Ark_Number nValue = Converter::ArkValue<Ark_Number>(std::stof(value));
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(nValue);
    };
    // need check
    // RatingModelNG::SetOnChangeEvent(frameNode, std::move(onEvent));
}
} // RatingAttributeModifier
const GENERATED_ArkUIRatingModifier* GetRatingModifier()
{
    static const GENERATED_ArkUIRatingModifier ArkUIRatingModifierImpl {
        RatingModifier::ConstructImpl,
        RatingInterfaceModifier::SetRatingOptionsImpl,
        RatingAttributeModifier::StarsImpl,
        RatingAttributeModifier::StepSizeImpl,
        RatingAttributeModifier::StarStyleImpl,
        RatingAttributeModifier::OnChangeImpl,
        RatingAttributeModifier::ContentModifierImpl,
        RatingAttributeModifier::_onChangeEvent_ratingImpl,
    };
    return &ArkUIRatingModifierImpl;
}

}
