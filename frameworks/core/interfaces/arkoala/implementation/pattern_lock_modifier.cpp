/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/interfaces/arkoala/implementation/pattern_lock_controller_accessor_peer_impl.h"
#include "core/interfaces/arkoala/utility/validators.h"


namespace OHOS::Ace::NG {
namespace {
struct CircleStyleOptions {
    std::optional<Color>color;
    std::optional<Dimension> radius;
    std::optional<bool> enableWaveEffect;
};
}
}

namespace OHOS::Ace::NG::Converter {
template<>
CircleStyleOptions Convert(const Ark_CircleStyleOptions& src)
{
    CircleStyleOptions style;
    style.color = OptConvert<Color>(src.color);
    style.enableWaveEffect = OptConvert<bool>(src.enableWaveEffect);
    LOGE("PatternLockInterfaceModifier::converter Ark_CircleStyleOptions -> CircleStyleOptions  is not fully"
        "implemented. Need get style.radius");
    return style;
}
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace PatternLockInterfaceModifier {
void SetPatternLockOptionsImpl(Ark_NativePointer node,
                               const Opt_PatternLockController* controller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(controller);

    auto controllerPtr = Converter::OptConvert<Ark_NativePointer>(*controller);
    if (controllerPtr.has_value()) {
        auto internalController = PatternLockModelNG::GetController(frameNode);
        auto peerImplPtr = reinterpret_cast<GeneratedModifier::PatternLockControllerPeerImpl *>(
        controllerPtr.value());
        CHECK_NULL_VOID(peerImplPtr);
        // pass the internal controller to external management
        peerImplPtr->SetHandler(internalController);
    }
}
} // PatternLockInterfaceModifier
namespace PatternLockAttributeModifier {
void SideLengthImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    PatternLockModelNG::SetSideLength(frameNode, convValue);
}
void CircleRadiusImpl(Ark_NativePointer node,
                      const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    PatternLockModelNG::SetCircleRadius(frameNode, convValue);
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    ViewAbstract::SetBackgroundColor(frameNode, convValue);
}
void RegularColorImpl(Ark_NativePointer node,
                      const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    PatternLockModelNG::SetRegularColor(frameNode, convValue);
}
void SelectedColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    PatternLockModelNG::SetSelectedColor(frameNode, convValue);
}
void ActiveColorImpl(Ark_NativePointer node,
                     const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    PatternLockModelNG::SetActiveColor(frameNode, convValue);
}
void PathColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    PatternLockModelNG::SetPathColor(frameNode, convValue);
}
void PathStrokeWidthImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    PatternLockModelNG::SetStrokeWidth(frameNode, convValue);
}
void OnPatternCompleteImpl(Ark_NativePointer node,
                           const Callback_Array_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //PatternLockModelNG::SetOnPatternComplete(frameNode, convValue);
    LOGE("PatternLockInterfaceModifier::OnPatternCompleteImpl -> Method be "
        "implemented later.");
}
void AutoResetImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    PatternLockModelNG::SetAutoReset(frameNode, convValue);
}
void OnDotConnectImpl(Ark_NativePointer node,
                      const Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //PatternLockModelNG::SetOnDotConnect(frameNode, convValue);
    LOGE("PatternLockInterfaceModifier::OnDotConnectImpl -> Method be "
        "implemented later.");
}
void ActivateCircleStyleImpl(Ark_NativePointer node,
                             const Ark_Union_CircleStyleOptions_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<CircleStyleOptions>(*value) : std::nullopt;
    if (convValue) {
        PatternLockModelNG::SetActiveCircleColor(frameNode, convValue->color);
        PatternLockModelNG::SetEnableWaveEffect(frameNode, convValue->enableWaveEffect);
        LOGE("PatternLockInterfaceModifier::ActivateCircleStyleImpl -> Method is not fully"
            "implemented. Need add PatternLockModelNG::SetActiveCircleRadius");
    }
}
} // PatternLockAttributeModifier
const GENERATED_ArkUIPatternLockModifier* GetPatternLockModifier()
{
    static const GENERATED_ArkUIPatternLockModifier ArkUIPatternLockModifierImpl {
        PatternLockInterfaceModifier::SetPatternLockOptionsImpl,
        PatternLockAttributeModifier::SideLengthImpl,
        PatternLockAttributeModifier::CircleRadiusImpl,
        PatternLockAttributeModifier::BackgroundColorImpl,
        PatternLockAttributeModifier::RegularColorImpl,
        PatternLockAttributeModifier::SelectedColorImpl,
        PatternLockAttributeModifier::ActiveColorImpl,
        PatternLockAttributeModifier::PathColorImpl,
        PatternLockAttributeModifier::PathStrokeWidthImpl,
        PatternLockAttributeModifier::OnPatternCompleteImpl,
        PatternLockAttributeModifier::AutoResetImpl,
        PatternLockAttributeModifier::OnDotConnectImpl,
        PatternLockAttributeModifier::ActivateCircleStyleImpl,
    };
    return &ArkUIPatternLockModifierImpl;
}

}
