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
    if (src.fromStart.value) {
        options.direction = MarqueeDirection::LEFT;
    } else {
        options.direction = MarqueeDirection::RIGHT;
    }
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
        MarqueeModelNG::SetScrollAmount(frameNode, marqueeOptions.step);
    }
    if (marqueeOptions.loop) {
        MarqueeModelNG::SetLoop(frameNode, marqueeOptions.loop);
    }
    if (marqueeOptions.src) {
        MarqueeModelNG::SetValue(frameNode, marqueeOptions.src);
    }
    if (marqueeOptions.start) {
        MarqueeModelNG::SetPlayerStatus(frameNode, marqueeOptions.start);
    }
    if (marqueeOptions.direction) {
        MarqueeModelNG::SetDirection(frameNode, marqueeOptions.direction);
    }
}
} // MarqueeInterfaceModifier

namespace MarqueeAttributeModifier {
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    MarqueeModelNG::SetTextColor(frameNode, convValue);
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    MarqueeModelNG::SetFontSize(frameNode, convValue);
}
void AllowScaleImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    MarqueeModelNG::SetAllowScale(frameNode, convValue);
}
void FontWeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Ace::FontWeight>(*value);
    MarqueeModelNG::SetFontWeight(frameNode, convValue);
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Ark_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>(*value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    MarqueeModelNG::SetFontFamily(frameNode, families);
}
void MarqueeUpdateStrategyImpl(Ark_NativePointer node,
                               Ark_MarqueeUpdateStrategy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<MarqueeUpdateStrategy>(value);
    MarqueeModelNG::SetMarqueeUpdateStrategy(frameNode, convValue);
}
void OnStartImpl(Ark_NativePointer node,
                 const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onStart = [arkCallback = CallbackHelper(*value)]() -> void {
        arkCallback.Invoke();
    };
    MarqueeModelNG::SetOnStart(frameNode, std::move(onStart));
}
void OnBounceImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onBounce = [arkCallback = CallbackHelper(*value)]() -> void {
        arkCallback.Invoke();
    };
    MarqueeModelNG::SetOnBounce(frameNode, onBounce);
}
void OnFinishImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onFinish = [arkCallback = CallbackHelper(*value)]() -> void {
        arkCallback.Invoke();
    };
    MarqueeModelNG::SetOnFinish(frameNode, onFinish);
}
} // MarqueeAttributeModifier
const GENERATED_ArkUIMarqueeModifier* GetMarqueeModifier()
{
    static const GENERATED_ArkUIMarqueeModifier ArkUIMarqueeModifierImpl {
        MarqueeModifier::ConstructImpl,
        MarqueeInterfaceModifier::SetMarqueeOptionsImpl,
        MarqueeAttributeModifier::FontColorImpl,
        MarqueeAttributeModifier::FontSizeImpl,
        MarqueeAttributeModifier::AllowScaleImpl,
        MarqueeAttributeModifier::FontWeightImpl,
        MarqueeAttributeModifier::FontFamilyImpl,
        MarqueeAttributeModifier::MarqueeUpdateStrategyImpl,
        MarqueeAttributeModifier::OnStartImpl,
        MarqueeAttributeModifier::OnBounceImpl,
        MarqueeAttributeModifier::OnFinishImpl,
    };
    return &ArkUIMarqueeModifierImpl;
}

}
