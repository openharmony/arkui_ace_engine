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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"
#include "core/components_ng/pattern/marquee/marquee_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
struct MarqueeOptions {
    std::optional<double> step;
    std::optional<int32_t> loop;
    std::optional<std::string> src;
    std::optional<bool> start;
    std::optional<MarqueeDirection> direction;
};
} // OHOS::Ace::NG

namespace OHOS::Ace::NG {
namespace Converter {
template<>
void AssignCast(std::optional<MarqueeUpdateStrategy>& dst, const Ark_MarqueeUpdateStrategy& src)
{
    switch (src) {
        case ARK_MARQUEE_UPDATE_STRATEGY_DEFAULT: dst = MarqueeUpdateStrategy::DEFAULT; break;
        case ARK_MARQUEE_UPDATE_STRATEGY_PRESERVE_POSITION: dst = MarqueeUpdateStrategy::PRESERVE_POSITION; break;
        default: LOGE("Unexpected enum value in Ark_MarqueeUpdateStrategy: %{public}d", src);
    }
}

template<>
MarqueeOptions Convert(const Ark_MarqueeOptions& src)
{
    MarqueeOptions options;
    options.step = OptConvert<float>(src.step);
    options.loop = OptConvert<int>(src.loop);
    options.src = OptConvert<std::string>(src.src);
    options.start = OptConvert<bool>(src.start);
    auto fromStart = OptConvert<bool>(src.fromStart);
    options.direction = fromStart.value_or(true) ? MarqueeDirection::LEFT : MarqueeDirection::RIGHT;
    return options;
}

} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MarqueeModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = MarqueeModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // MarqueeModifier
namespace MarqueeInterfaceModifier {
void SetMarqueeOptionsImpl(Ark_NativePointer node,
                           const Ark_MarqueeOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto marqueeOptions = Converter::Convert<MarqueeOptions>(*options);
    if (marqueeOptions.step) {
        auto getStep = marqueeOptions.step;
        std::optional<double> stepOpt;
        if (getStep.has_value()) {
            auto step = getStep.value();
            if (GreatNotEqual(step, 0.0)) {
                stepOpt = Dimension(step, DimensionUnit::VP).ConvertToPx();
            }
        }
        MarqueeModelStatic::SetScrollAmount(frameNode, stepOpt);
    }
    if (marqueeOptions.loop) {
        std::optional<int32_t> loopOpt;
        int32_t loop = marqueeOptions.loop.value();
        if (loop == std::numeric_limits<int32_t>::max() || loop < 1) {
            loop = -1;
        }
        loopOpt = loop;
        MarqueeModelNG::SetLoop(frameNode, loopOpt);
    }
    MarqueeModelNG::SetValue(frameNode, marqueeOptions.src.value_or(""));
    MarqueeModelNG::SetPlayerStatus(frameNode, marqueeOptions.start.value_or(false));
    if (marqueeOptions.direction) {
        MarqueeModelNG::SetDirection(frameNode, marqueeOptions.direction);
    }
}
} // MarqueeInterfaceModifier
namespace MarqueeAttributeModifier {
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    MarqueeModelNG::SetTextColor(frameNode, convValue);
}
void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> convValue = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        convValue = Converter::OptConvertFromArkNumStrRes<Ark_Length, Ark_Float64>(value->value, DimensionUnit::FP);
    }
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    MarqueeModelNG::SetFontSize(frameNode, convValue);
}
void SetAllowScaleImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        // Implement Reset value
        MarqueeModelNG::SetAllowScale(frameNode, false);
        return;
    }
    MarqueeModelNG::SetAllowScale(frameNode, *convValue);
}
void SetFontWeightImpl(Ark_NativePointer node,
                       const Opt_Union_I32_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Ace::FontWeight>(value);
    MarqueeModelNG::SetFontWeight(frameNode, convValue);
}
void SetFontFamilyImpl(Ark_NativePointer node,
                       const Opt_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvertPtr<Converter::FontFamilies>(value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    MarqueeModelNG::SetFontFamily(frameNode, families);
}
void SetMarqueeUpdateStrategyImpl(Ark_NativePointer node,
                                  const Opt_MarqueeUpdateStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<MarqueeUpdateStrategy>(value);
    MarqueeModelNG::SetMarqueeUpdateStrategy(frameNode, convValue);
}
void SetOnStartImpl(Ark_NativePointer node,
                    const Opt_synthetic_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        MarqueeModelNG::SetOnStart(frameNode, nullptr);
        return;
    }
    auto onStart = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.InvokeSync();
    };
    MarqueeModelNG::SetOnStart(frameNode, std::move(onStart));
}
void SetOnBounceImpl(Ark_NativePointer node,
                     const Opt_synthetic_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        MarqueeModelNG::SetOnBounce(frameNode, nullptr);
        return;
    }
    auto onBounce = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.InvokeSync();
    };
    MarqueeModelNG::SetOnBounce(frameNode, onBounce);
}
void SetOnFinishImpl(Ark_NativePointer node,
                     const Opt_synthetic_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        MarqueeModelNG::SetOnFinish(frameNode, nullptr);
        return;
    }
    auto onFinish = [arkCallback = CallbackHelper(*optValue)]() -> void {
        arkCallback.InvokeSync();
    };
    MarqueeModelNG::SetOnFinish(frameNode, onFinish);
}
} // MarqueeAttributeModifier
const GENERATED_ArkUIMarqueeModifier* GetMarqueeModifier()
{
    static const GENERATED_ArkUIMarqueeModifier ArkUIMarqueeModifierImpl {
        MarqueeModifier::ConstructImpl,
        MarqueeInterfaceModifier::SetMarqueeOptionsImpl,
        MarqueeAttributeModifier::SetFontColorImpl,
        MarqueeAttributeModifier::SetFontSizeImpl,
        MarqueeAttributeModifier::SetAllowScaleImpl,
        MarqueeAttributeModifier::SetFontWeightImpl,
        MarqueeAttributeModifier::SetFontFamilyImpl,
        MarqueeAttributeModifier::SetMarqueeUpdateStrategyImpl,
        MarqueeAttributeModifier::SetOnStartImpl,
        MarqueeAttributeModifier::SetOnBounceImpl,
        MarqueeAttributeModifier::SetOnFinishImpl,
    };
    return &ArkUIMarqueeModifierImpl;
}

}
