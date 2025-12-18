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
#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_static.h"
#include "core/interfaces/native/implementation/indicator_component_controller_peer.h"
#include "core/interfaces/native/implementation/dot_indicator_peer_impl.h"
#include "core/interfaces/native/implementation/digit_indicator_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::SwiperAttributeModifierInternal {
bool CheckSwiperParameters(SwiperParameters& p);
void CheckSwiperDigitalParameters(SwiperDigitalParameters& p);
} // namespace OHOS::Ace::NG::SwiperAttributeModifierInternal

namespace OHOS::Ace::NG::GeneratedModifier {
namespace IndicatorComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = IndicatorModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return Referenced::RawPtr(frameNode);
}
} // IndicatorComponentModifier
namespace IndicatorComponentInterfaceModifier {
void SetIndicatorComponentOptionsImpl(Ark_NativePointer node,
                                      const Opt_IndicatorComponentController* controller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    // obtain the peer of external IndicatorController
    Ark_IndicatorComponentController peerImplPtr{};
    if (auto opt = Converter::OptConvertPtr<Ark_IndicatorComponentController>(controller); opt) {
        peerImplPtr = *opt;
    }
    CHECK_NULL_VOID(peerImplPtr);

    // obtain the internal IndicatorController
    auto internalController = IndicatorModelStatic::InitIndicatorController(frameNode);

    // pass the internal controller to external management
    auto indicatorNode = AceType::Claim<NG::FrameNode>(frameNode);
    peerImplPtr->SetController(internalController, indicatorNode);
}
} // IndicatorComponentInterfaceModifier
namespace IndicatorComponentAttributeModifier {
void SetInitialIndexImpl(Ark_NativePointer node,
                         const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::OptConvertPtr<int32_t>(value);
    Validator::ValidateNonNegative(aceVal);
    IndicatorModelStatic::SetInitialIndex(frameNode, aceVal);
}
void SetCountImpl(Ark_NativePointer node,
                  const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::OptConvertPtr<int32_t>(value);
    Validator::ValidateNonNegative(aceVal);
    IndicatorModelStatic::SetCount(frameNode, aceVal);
}
void SetStyleImpl(Ark_NativePointer node,
                  const Opt_Union_DotIndicator_DigitIndicator* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Converter::VisitUnion(*value,
        [frameNode](const Ark_DotIndicator& value) {
            CHECK_NULL_VOID(frameNode);
            auto peerDotIndicator = value;
            CHECK_NULL_VOID(peerDotIndicator);
            auto dotParam = peerDotIndicator->GetDotParameters();
            auto isCustomSize = SwiperAttributeModifierInternal::CheckSwiperParameters(dotParam);
            IndicatorModelStatic::SetDotIndicatorStyle(frameNode, dotParam);
            IndicatorModelStatic::SetIsIndicatorCustomSize(frameNode, isCustomSize);
            IndicatorModelStatic::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
            IndicatorModelStatic::SetShowIndicator(frameNode, true);
        },
        [frameNode](const Ark_DigitIndicator& value) {
            CHECK_NULL_VOID(frameNode);
            auto peerDigitIndicator = value;
            CHECK_NULL_VOID(peerDigitIndicator);
            auto digitParam = peerDigitIndicator->GetDigitParameters();
            SwiperAttributeModifierInternal::CheckSwiperDigitalParameters(digitParam);
            IndicatorModelStatic::SetDigitIndicatorStyle(frameNode, digitParam);
            IndicatorModelStatic::SetIsIndicatorCustomSize(frameNode, false);
            IndicatorModelStatic::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
            IndicatorModelStatic::SetShowIndicator(frameNode, true);
        },
        [frameNode]() {
            SwiperParameters dotParam;
            auto isCustomSize = SwiperAttributeModifierInternal::CheckSwiperParameters(dotParam);
            IndicatorModelStatic::SetDotIndicatorStyle(frameNode, dotParam);
            IndicatorModelStatic::SetIsIndicatorCustomSize(frameNode, isCustomSize);
            IndicatorModelStatic::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
            IndicatorModelStatic::SetShowIndicator(frameNode, false);
        });
}
void SetLoopImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value).value_or(true);
    IndicatorModelStatic::SetLoop(frameNode, convValue);
}
void SetVerticalImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value).value_or(false);
    IndicatorModelStatic::SetDirection(frameNode, convValue ? Axis::VERTICAL : Axis::HORIZONTAL);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_arkui_component_common_Callback_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        IndicatorModelStatic::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](int32_t index) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(index));
    };
    IndicatorModelStatic::SetOnChange(frameNode, onEvent);
}
} // IndicatorComponentAttributeModifier
const GENERATED_ArkUIIndicatorComponentModifier* GetIndicatorComponentModifier()
{
    static const GENERATED_ArkUIIndicatorComponentModifier ArkUIIndicatorComponentModifierImpl {
        IndicatorComponentModifier::ConstructImpl,
        IndicatorComponentInterfaceModifier::SetIndicatorComponentOptionsImpl,
        IndicatorComponentAttributeModifier::SetInitialIndexImpl,
        IndicatorComponentAttributeModifier::SetCountImpl,
        IndicatorComponentAttributeModifier::SetStyleImpl,
        IndicatorComponentAttributeModifier::SetLoopImpl,
        IndicatorComponentAttributeModifier::SetVerticalImpl,
        IndicatorComponentAttributeModifier::SetOnChangeImpl,
    };
    return &ArkUIIndicatorComponentModifierImpl;
}

}
