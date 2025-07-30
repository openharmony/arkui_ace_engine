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
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_static.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/pattern_lock_controller_accessor_peer_impl.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/base/view_abstract_model_static.h"

namespace OHOS::Ace::NG {
namespace {
struct CircleStyleOptions {
    std::optional<Color>color;
    std::optional<Dimension> radius;
    std::optional<bool> enableWaveEffect;
    std::optional<bool> enableForeground;
};
}
}

namespace OHOS::Ace::NG::Converter {
template<>
CircleStyleOptions Convert(const Ark_CircleStyleOptions& src)
{
    CircleStyleOptions style;
    style.color = OptConvert<Color>(src.color);
    style.radius = OptConvert<Dimension>(src.radius);
    style.enableWaveEffect = OptConvert<bool>(src.enableWaveEffect);
    style.enableForeground = OptConvert<bool>(src.enableForeground);
    return style;
}
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace PatternLockModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    // auto frameNode = PatternLockModelNG::CreateFrameNode(id);
    // CHECK_NULL_RETURN(frameNode, nullptr);
    // frameNode->IncRefCount();
    return {};
}
} // PatternLockModifier
namespace PatternLockInterfaceModifier {
void SetPatternLockOptionsImpl(Ark_NativePointer node,
                               const Opt_PatternLockController* controller)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(controller);

    // auto controllerPtr = Converter::OptConvert<Ark_PatternLockController>(*controller);
    // if (controllerPtr.has_value()) {
    //     auto internalController = PatternLockModelNG::GetController(frameNode);
    //     auto peerImplPtr = reinterpret_cast<PatternLockControllerPeerImpl *>(controllerPtr.value());
    //     CHECK_NULL_VOID(peerImplPtr);
    //     // pass the internal controller to external management
    //     peerImplPtr->SetHandler(internalController);
    // }
}
} // PatternLockInterfaceModifier
namespace PatternLockAttributeModifier {
void SideLengthImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    PatternLockModelStatic::SetSideLength(frameNode, convValue);
}
void CircleRadiusImpl(Ark_NativePointer node,
                      const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    PatternLockModelStatic::SetCircleRadius(frameNode, convValue);
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    ViewAbstractModelStatic::SetBackgroundColor(frameNode, convValue);
}
void RegularColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    PatternLockModelStatic::SetRegularColor(frameNode, convValue);
}
void SelectedColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    PatternLockModelStatic::SetSelectedColor(frameNode, convValue);
}
void ActiveColorImpl(Ark_NativePointer node,
                     const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    PatternLockModelStatic::SetActiveColor(frameNode, convValue);
}
void PathColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    PatternLockModelStatic::SetPathColor(frameNode, convValue);
}
void PathStrokeWidthImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    PatternLockModelStatic::SetStrokeWidth(frameNode, convValue);
}
void OnPatternCompleteImpl(Ark_NativePointer node,
                           const Opt_Callback_Array_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        std::function<void(const BaseEventInfo* info)> func;
        PatternLockModelNG::SetPatternComplete(frameNode, std::move(func));
        return;
    }
    auto call = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* info) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<V2::PatternCompleteEvent>(info);
        CHECK_NULL_VOID(eventInfo);
        Converter::ArkArrayHolder<Array_Number> arrayHolder(eventInfo->GetInput());
        arkCallback.Invoke(arrayHolder.ArkValue());
    };
    PatternLockModelNG::SetPatternComplete(frameNode, std::move(call));
}
void AutoResetImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    PatternLockModelStatic::SetAutoReset(frameNode, convValue);
}
void OnDotConnectImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        std::function<void(int32_t)> func;
        PatternLockModelNG::SetDotConnect(frameNode, std::move(func));
        return;
    }
    auto call = [arkCallback = CallbackHelper(*optValue)](int32_t index) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        arkCallback.Invoke(arkIndex);
    };
    PatternLockModelNG::SetDotConnect(frameNode, std::move(call));
}
void ActivateCircleStyleImpl(Ark_NativePointer node,
                             const Opt_CircleStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<CircleStyleOptions>(*value) : std::nullopt;
    if (convValue) {
        PatternLockModelStatic::SetActiveCircleColor(frameNode, convValue->color);
        PatternLockModelStatic::SetEnableWaveEffect(frameNode, convValue->enableWaveEffect);
        PatternLockModelStatic::SetActiveCircleRadius(frameNode, convValue->radius);
        if (convValue->enableForeground) {
            PatternLockModelNG::SetEnableForeground(frameNode, convValue->enableForeground.value());
        }
    }
}
void SkipUnselectedPointImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    PatternLockModelNG::SetSkipUnselectedPoint(frameNode, *convValue);
}
} // PatternLockAttributeModifier
const GENERATED_ArkUIPatternLockModifier* GetPatternLockModifier()
{
    static const GENERATED_ArkUIPatternLockModifier ArkUIPatternLockModifierImpl {
        PatternLockModifier::ConstructImpl,
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
        PatternLockAttributeModifier::SkipUnselectedPointImpl,
    };
    return &ArkUIPatternLockModifierImpl;
}

}
