/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/common_view/common_view_model_ng.h"
#include "core/components_ng/pattern/rating/bridge/rating_content_modifier_helper.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/rating/rating_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/object_keeper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace {
struct StarStyleOptions {
    std::string backgroundUri = {};
    std::string foregroundUri = {};
    std::string secondaryUri = {};
};
std::optional<float> ProcessBindableRating(FrameNode* frameNode, const Opt_Union_F64_Bindable& value)
{
    std::optional<float> result;
    Converter::VisitUnion(value,
        [&result](const Ark_Float64& src) {
            result = Converter::Convert<float>(src);
        },
        [&result, frameNode](const Ark_Bindable_F64& src) {
            result = Converter::Convert<float>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const std::string& value) {
                auto nValue = Converter::ArkValue<Ark_Float64>(StringUtils::StringToFloat(value));
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(nValue);
            };
            RatingModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace

namespace Converter {
template<>
StarStyleOptions Convert(const Ark_StarStyleOptions& value)
{
    StarStyleOptions options;
    options.backgroundUri = Converter::OptConvert<std::string>(value.backgroundUri).value_or(std::string());
    options.foregroundUri = Converter::OptConvert<std::string>(value.foregroundUri).value_or(std::string());
    options.secondaryUri = Converter::OptConvert<std::string>(value.secondaryUri).value_or(std::string());
    return options;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RatingAttributeModifier {
    void Stars1Impl(Ark_NativePointer node, const Opt_Int32* value);
    void StepSize1Impl(Ark_NativePointer node, const Opt_Float64* value);
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
    auto optOptions = Converter::GetOptPtr(options);
    auto rating = optOptions ? ProcessBindableRating(frameNode, optOptions->rating) : std::nullopt;
    auto indicator = OPT_CONVERT_FIELD(bool, optOptions, indicator);
    Validator::ValidateNonNegative(rating);
    auto dRating = FloatToDouble(rating);
    RatingModelStatic::SetRatingOptions(frameNode, dRating.value_or(0), indicator);
}
} // RatingInterfaceModifier
namespace RatingAttributeModifier {
void SetStarsImpl(Ark_NativePointer node,
                  const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convVal = Converter::OptConvertPtr<float>(value);
    Validator::ValidateNonNegative(convVal);
    auto optdVal = FloatToDouble(convVal);
    RatingModelStatic::SetStars(frameNode,  optdVal);
}
void SetStepSizeImpl(Ark_NativePointer node,
                     const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convVal = Converter::OptConvertPtr<float>(value);
    static const float stepSizeMin = 0.1;
    Validator::ValidateGreatOrEqual(convVal, stepSizeMin);
    auto optdVal = FloatToDouble(convVal);
    RatingModelStatic::SetStepSize(frameNode,  optdVal);
}
void SetStarStyleImpl(Ark_NativePointer node,
                      const Opt_StarStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = Converter::OptConvertPtr<StarStyleOptions>(value).value_or(StarStyleOptions());
    RatingModelNG::SetBackgroundSrc(frameNode, options.backgroundUri,  options.backgroundUri.empty());
    RatingModelNG::SetForegroundSrc(frameNode, options.foregroundUri, options.foregroundUri.empty());
    if (options.secondaryUri.empty()) {
        RatingModelNG::SetSecondarySrc(frameNode, options.backgroundUri, options.backgroundUri.empty());
    } else {
        RatingModelNG::SetSecondarySrc(frameNode, options.secondaryUri, false);
    }
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_OnRatingChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    RatingChangeEvent onChange = {};
    if (optValue) {
        onChange = [arkCallback = CallbackHelper(*optValue)](const std::string& value) {
            Ark_Float64 convValue = Converter::ArkValue<Ark_Float64>(StringUtils::StringToFloat(value));
            arkCallback.Invoke(convValue);
        };
    }
    RatingModelStatic::SetOnChange(frameNode, std::move(onChange));
}

void ContentModifierRatingImpl(Ark_NativePointer node,
                               const Ark_Object* contentModifier,
                               const RatingModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
    RatingConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_RatingConfiguration arkConfig;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.contentModifier = contentModifier;
        arkConfig.rating = Converter::ArkValue<Ark_Float64>(config.rating_);
        arkConfig.indicator = Converter::ArkValue<Ark_Boolean>(config.isIndicator_);
        arkConfig.stars = Converter::ArkValue<Ark_Int32>(config.starNum_);
        arkConfig.stepSize = Converter::ArkValue<Ark_Float64>(config.stepSize_);
        auto handler = [frameNode](Ark_Float64 retValue) {
            RatingModelStatic::TriggerChange(frameNode, Converter::Convert<double>(retValue));
        };
        auto triggerCallback = CallbackKeeper::Claim<Callback_F64_Void>(handler);
        arkConfig.triggerChange = triggerCallback.ArkValue();
        auto boxNode = CommonViewModelNG::CreateFrameNode(ViewStackProcessor::GetInstance()->ClaimNodeId());
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    RatingModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}

void ResetContentModifierRatingImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RatingModelNG::SetBuilderFunc(frameNode, nullptr);
}

} // RatingAttributeModifier
const GENERATED_ArkUIRatingModifier* GetRatingStaticModifier()
{
    static const GENERATED_ArkUIRatingModifier ArkUIRatingModifierImpl {
        RatingModifier::ConstructImpl,
        RatingInterfaceModifier::SetRatingOptionsImpl,
        RatingAttributeModifier::SetStarsImpl,
        RatingAttributeModifier::SetStepSizeImpl,
        RatingAttributeModifier::SetStarStyleImpl,
        RatingAttributeModifier::SetOnChangeImpl,
    };
    return &ArkUIRatingModifierImpl;
}

const GENERATED_ArkUIRatingContentModifier* GetRatingStaticContentModifier()
{
    static const GENERATED_ArkUIRatingContentModifier ArkUIRatingStaticContentModifierImpl {
        RatingAttributeModifier::ContentModifierRatingImpl,
        RatingAttributeModifier::ResetContentModifierRatingImpl,
    };
    return &ArkUIRatingStaticContentModifierImpl;
}

}
