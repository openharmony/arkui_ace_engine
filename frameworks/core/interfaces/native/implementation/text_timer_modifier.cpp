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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_static.h"
#include "core/interfaces/native/implementation/text_timer_controller_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
struct TextTimerOptions {
    std::optional<bool> isCountDown;
    std::optional<double> count;
    std::optional<Ark_TextTimerController> controller;
};

namespace Converter {
template<>
TextTimerOptions Convert(const Ark_TextTimerOptions& src)
{
    TextTimerOptions dst;
    dst.isCountDown = Converter::OptConvert<bool>(src.isCountDown);
#ifdef WRONG_GEN
    dst.count = Converter::OptConvert<float>(src.count);
#endif
    dst.controller = Converter::OptConvert<Ark_TextTimerController>(src.controller);
    return dst;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextTimerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TextTimerModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // TextTimerModifier
namespace TextTimerInterfaceModifier {
void SetTextTimerOptionsImpl(Ark_NativePointer node,
                             const Opt_TextTimerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto opts = Converter::OptConvertPtr<TextTimerOptions>(options);
    TextTimerModelStatic::SetIsCountDown(frameNode, opts->isCountDown);
    if (!opts->isCountDown.value_or(false)) {
        opts->count.reset();
    }
    TextTimerModelStatic::SetInputCount(frameNode, opts->count);

    CHECK_NULL_VOID(opts->controller);
    auto textTimerController = TextTimerModelNG::InitTextController(frameNode);
    CHECK_NULL_VOID(textTimerController);
    TextTimerControllerPeer* peerPtr = opts->controller.value();
    CHECK_NULL_VOID(peerPtr);
    peerPtr->SetController(textTimerController);
}
} // TextTimerInterfaceModifier
namespace TextTimerAttributeModifier {
void SetFormatImpl(Ark_NativePointer node,
                   const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto format = Converter::OptConvertPtr<std::string>(value);

    if (format) {
        std::smatch result;
        std::regex pattern("(([YyMdD]+))");
        if (std::regex_search(format.value(), result, pattern)) {
            if (!result.empty()) {
                format.reset();
            }
        }

        std::string target = "HmsS:.";
        for (auto ch : *format) {
            if (target.find(ch) == std::string::npos) {
                format.reset();
            }
        }

        auto pos = format->find("hh");
        if (pos != std::string::npos) {
            format->replace(pos, sizeof("hh") - 1, "HH");
        }
    }
    TextTimerModelStatic::SetFormat(frameNode, format);
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvertPtr<Color>(value);
    TextTimerModelStatic::SetFontColor(frameNode, color);
}
void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto size = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(size);
    Validator::ValidateNonPercent(size);
    TextTimerModelStatic::SetFontSize(frameNode, size);
}
void SetFontStyleImpl(Ark_NativePointer node,
                      const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto style = Converter::OptConvertPtr<Ace::FontStyle>(value);
    TextTimerModelStatic::SetFontStyle(frameNode, style);
}
void SetFontWeightImpl(Ark_NativePointer node,
                       const Opt_Union_Number_FontWeight_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto weight = Converter::OptConvertPtr<Ace::FontWeight>(value);
    TextTimerModelStatic::SetFontWeight(frameNode, weight);
}
void SetFontFamilyImpl(Ark_NativePointer node,
                       const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvertPtr<Converter::FontFamilies>(value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    TextTimerModelStatic::SetFontFamily(frameNode, families);
}
// fix Opt_Callback_Number_Number_Void > Opt_Callback_Int64_Int64_Void this is time so int64 is required
void SetOnTimerImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue), node = AceType::WeakClaim(frameNode)](
        int64_t utc, int64_t elapsedTime) {
#ifdef WRONG_GEN
        PipelineContext::SetCallBackNode(node);
        auto utcResult = Converter::ArkValue<Ark_Int64>(utc);
        auto elapsedTimeResult = Converter::ArkValue<Ark_Int64>(elapsedTime);
        arkCallback.Invoke(utcResult, elapsedTimeResult);
#endif
    };
    TextTimerModelNG::SetOnTimer(frameNode, std::move(onChange));
}
void SetTextShadowImpl(Ark_NativePointer node,
                       const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto shadowList = Converter::OptConvert<std::vector<Shadow>>(*value);
    TextTimerModelStatic::SetTextShadow(frameNode, shadowList);
}
} // TextTimerAttributeModifier
const GENERATED_ArkUITextTimerModifier* GetTextTimerModifier()
{
    static const GENERATED_ArkUITextTimerModifier ArkUITextTimerModifierImpl {
        TextTimerModifier::ConstructImpl,
        TextTimerInterfaceModifier::SetTextTimerOptionsImpl,
        TextTimerAttributeModifier::SetFormatImpl,
        TextTimerAttributeModifier::SetFontColorImpl,
        TextTimerAttributeModifier::SetFontSizeImpl,
        TextTimerAttributeModifier::SetFontStyleImpl,
        TextTimerAttributeModifier::SetFontWeightImpl,
        TextTimerAttributeModifier::SetFontFamilyImpl,
        TextTimerAttributeModifier::SetOnTimerImpl,
        TextTimerAttributeModifier::SetTextShadowImpl,
    };
    return &ArkUITextTimerModifierImpl;
}
}
