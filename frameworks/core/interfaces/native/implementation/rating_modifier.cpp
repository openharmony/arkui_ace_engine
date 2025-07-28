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
#include "core/components_ng/pattern/rating/rating_model_static.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace {
struct StarStyleOptions {
    std::string backgroundUri = {};
    std::string foregroundUri = {};
    std::string secondaryUri = {};
};
}

namespace Converter {
template<>
StarStyleOptions Convert(const Ark_StarStyleOptions& value)
{
    StarStyleOptions options;
    options.backgroundUri = Converter::Convert<std::string>(value.backgroundUri);
    options.foregroundUri = Converter::Convert<std::string>(value.foregroundUri);
    auto optStr = Converter::OptConvert<std::string>(value.secondaryUri);
    options.secondaryUri = optStr.value_or(std::string());
    return options;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RatingAttributeModifier {
    void Stars1Impl(Ark_NativePointer node, const Opt_Number* value);
    void StepSize1Impl(Ark_NativePointer node, const Opt_Number* value);
    void StarStyle1Impl(Ark_NativePointer node, const Opt_StarStyleOptions* value);
}
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
        RatingModelStatic::SetRatingOptions(frameNode, dRating, indicator);
        return;
    }
    auto optOptions = Converter::OptConvert<Ark_RatingOptions>(*options);
    if (!optOptions.has_value()) {
        RatingModelStatic::SetRatingOptions(frameNode, dRating, indicator);
        return;
    }
    auto arkOptions = optOptions.value();
    rating = Converter::Convert<float>(arkOptions.rating);
    indicator = Converter::OptConvert<bool>(arkOptions.indicator);
    Validator::ValidateNonNegative(rating);
    dRating = FloatToDouble(rating);
    RatingModelStatic::SetRatingOptions(frameNode, dRating, indicator);
}
} // RatingInterfaceModifier
namespace RatingAttributeModifier {
void Stars0Impl(Ark_NativePointer node,
                const Opt_Number* value)
{
    Stars1Impl(node, value);
}
void Stars1Impl(Ark_NativePointer node,
                const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkVal = value ? Converter::GetOpt(*value) : std::nullopt;
    auto convVal = arkVal.has_value() ? Converter::OptConvert<float>(arkVal.value()) : std::nullopt;
    Validator::ValidateNonNegative(convVal);
    auto optdVal = FloatToDouble(convVal);
    RatingModelStatic::SetStars(frameNode,  optdVal);
}
void StepSize0Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    StepSize1Impl(node, value);
}
void StepSize1Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkVal = value ? Converter::GetOpt(*value) : std::nullopt;
    auto convVal = arkVal.has_value() ? Converter::OptConvert<float>(arkVal.value()) : std::nullopt;
    static const float stepSizeMin = 0.1;
    Validator::ValidateGreatOrEqual(convVal, stepSizeMin);
    auto optdVal = FloatToDouble(convVal);
    RatingModelStatic::SetStepSize(frameNode,  optdVal);
}
void StarStyle0Impl(Ark_NativePointer node,
                    const Opt_StarStyleOptions* value)
{
    StarStyle1Impl(node, value);
}
void StarStyle1Impl(Ark_NativePointer node,
                    const Opt_StarStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkVal = value ? Converter::GetOpt(*value) : std::nullopt;
    StarStyleOptions options = {};
    if (arkVal.has_value()) {
        options = Converter::Convert<StarStyleOptions>(arkVal.value());
    }
    RatingModelNG::SetBackgroundSrc(frameNode, options.backgroundUri,  options.backgroundUri.empty());
    RatingModelNG::SetForegroundSrc(frameNode, options.foregroundUri, options.foregroundUri.empty());
    RatingModelNG::SetSecondarySrc(frameNode, options.secondaryUri, options.secondaryUri.empty());
}
void OnChange0Impl(Ark_NativePointer node,
                   const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RatingChangeEvent onChange = {};
    auto optValue = Converter::GetOptPtr(value);
    if (optValue) {
        onChange = [arkCallback = CallbackHelper(*optValue)](const std::string& value) {
            Ark_Number convValue = Converter::ArkValue<Ark_Number>(std::stof(value));
            arkCallback.Invoke(convValue);
        };
    }
    RatingModelStatic::SetOnChange(frameNode, std::move(onChange));
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnRatingChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    RatingChangeEvent onChange = {};
    if (optValue) {
        onChange = [arkCallback = CallbackHelper(*optValue)](const std::string& value) {
            Ark_Number convValue = Converter::ArkValue<Ark_Number>(std::stof(value));
            arkCallback.Invoke(convValue);
        };
    }
    RatingModelStatic::SetOnChange(frameNode, std::move(onChange));
}
void ContentModifier0Impl(Ark_NativePointer node,
                          const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA RatingInterfaceModifier::ContentModifier is not implemented.");
}
void ContentModifier1Impl(Ark_NativePointer node,
                          const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
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
    RatingModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
}
} // RatingAttributeModifier
const GENERATED_ArkUIRatingModifier* GetRatingModifier()
{
    static const GENERATED_ArkUIRatingModifier ArkUIRatingModifierImpl {
        RatingModifier::ConstructImpl,
        RatingInterfaceModifier::SetRatingOptionsImpl,
        RatingAttributeModifier::Stars0Impl,
        RatingAttributeModifier::Stars1Impl,
        RatingAttributeModifier::StepSize0Impl,
        RatingAttributeModifier::StepSize1Impl,
        RatingAttributeModifier::StarStyle0Impl,
        RatingAttributeModifier::StarStyle1Impl,
        RatingAttributeModifier::OnChange0Impl,
        RatingAttributeModifier::OnChange1Impl,
        RatingAttributeModifier::ContentModifier0Impl,
        RatingAttributeModifier::ContentModifier1Impl,
        RatingAttributeModifier::_onChangeEvent_ratingImpl,
    };
    return &ArkUIRatingModifierImpl;
}

}
