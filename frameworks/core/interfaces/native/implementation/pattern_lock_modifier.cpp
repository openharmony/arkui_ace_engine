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
    auto frameNode = PatternLockModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // PatternLockModifier
namespace PatternLockInterfaceModifier {
std::mutex controllerMutex;
void SetPatternLockOptionsImpl(Ark_NativePointer node,
                               const Opt_PatternLockController* controller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    auto controllerPtr = Converter::OptConvertPtr<Ark_PatternLockController>(controller);
    if (controllerPtr.has_value()) {
        std::lock_guard<std::mutex> lock(controllerMutex);
        auto internalController = PatternLockModelStatic::GetController(frameNode);
        auto peerImplPtr = reinterpret_cast<PatternLockControllerPeerImpl *>(controllerPtr.value());
        CHECK_NULL_VOID(peerImplPtr);
        // pass the internal controller to external management
        peerImplPtr->SetHandler(internalController);
    }
}
} // PatternLockInterfaceModifier
namespace PatternLockAttributeModifier {
void SetSideLengthImpl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    PatternLockModelStatic::SetSideLength(frameNode, convValue);
}
void SetCircleRadiusImpl(Ark_NativePointer node,
                         const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    PatternLockModelStatic::SetCircleRadius(frameNode, convValue);
}
void SetBackgroundColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    ViewAbstractModelStatic::SetBackgroundColor(frameNode, convValue);
}
void SetRegularColorImpl(Ark_NativePointer node,
                         const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    PatternLockModelStatic::SetRegularColor(frameNode, convValue);
}
void SetSelectedColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    PatternLockModelStatic::SetSelectedColor(frameNode, convValue);
}
void SetActiveColorImpl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    PatternLockModelStatic::SetActiveColor(frameNode, convValue);
}
void SetPathColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    PatternLockModelStatic::SetPathColor(frameNode, convValue);
}
void SetPathStrokeWidthImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    PatternLockModelStatic::SetStrokeWidth(frameNode, convValue);
}
void SetOnPatternCompleteImpl(Ark_NativePointer node,
                              const Opt_Callback_Array_I32_Void* value)
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
        Converter::ArkArrayHolder<Array_Int32> arrayHolder(eventInfo->GetInput());
        arkCallback.Invoke(arrayHolder.ArkValue());
    };
    PatternLockModelNG::SetPatternComplete(frameNode, std::move(call));
}
void SetAutoResetImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        PatternLockModelStatic::SetAutoReset(frameNode, true);
        return;
    }
    PatternLockModelStatic::SetAutoReset(frameNode, convValue);
}
void SetOnDotConnectImpl(Ark_NativePointer node,
                         const Opt_Callback_I32_Void* value)
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
        auto arkIndex = Converter::ArkValue<Ark_Int32>(index);
        arkCallback.Invoke(arkIndex);
    };
    PatternLockModelNG::SetDotConnect(frameNode, std::move(call));
}
void SetActivateCircleStyleImpl(Ark_NativePointer node,
                                const Opt_CircleStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<CircleStyleOptions>(value);
    if (convValue) {
        PatternLockModelStatic::SetActiveCircleColor(frameNode, convValue->color);
        PatternLockModelStatic::SetEnableWaveEffect(frameNode, convValue->enableWaveEffect);
        PatternLockModelStatic::SetActiveCircleRadius(frameNode, convValue->radius);
        if (convValue->enableForeground) {
            PatternLockModelStatic::SetEnableForeground(frameNode, convValue->enableForeground.value());
        }
    } else {
        PatternLockModelStatic::SetActiveCircleColor(frameNode, std::nullopt);
        PatternLockModelStatic::SetEnableWaveEffect(frameNode, std::nullopt);
        PatternLockModelStatic::SetActiveCircleRadius(frameNode, std::nullopt);
        PatternLockModelStatic::SetEnableForeground(frameNode, std::nullopt);
    }
}
void SetSkipUnselectedPointImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    PatternLockModelNG::SetSkipUnselectedPoint(frameNode, *convValue);
}
} // PatternLockAttributeModifier
const GENERATED_ArkUIPatternLockModifier* GetPatternLockModifier()
{
    static const GENERATED_ArkUIPatternLockModifier ArkUIPatternLockModifierImpl {
        PatternLockModifier::ConstructImpl,
        PatternLockInterfaceModifier::SetPatternLockOptionsImpl,
        PatternLockAttributeModifier::SetSideLengthImpl,
        PatternLockAttributeModifier::SetCircleRadiusImpl,
        PatternLockAttributeModifier::SetBackgroundColorImpl,
        PatternLockAttributeModifier::SetRegularColorImpl,
        PatternLockAttributeModifier::SetSelectedColorImpl,
        PatternLockAttributeModifier::SetActiveColorImpl,
        PatternLockAttributeModifier::SetPathColorImpl,
        PatternLockAttributeModifier::SetPathStrokeWidthImpl,
        PatternLockAttributeModifier::SetOnPatternCompleteImpl,
        PatternLockAttributeModifier::SetAutoResetImpl,
        PatternLockAttributeModifier::SetOnDotConnectImpl,
        PatternLockAttributeModifier::SetActivateCircleStyleImpl,
        PatternLockAttributeModifier::SetSkipUnselectedPointImpl,
    };
    return &ArkUIPatternLockModifierImpl;
}

}
