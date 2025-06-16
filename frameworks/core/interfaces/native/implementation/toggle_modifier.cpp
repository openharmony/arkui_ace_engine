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
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter2.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::Converter {
struct ToggleOptions {
    std::optional<ToggleType> type;
    std::optional<bool> isOn;
};

template<>
ToggleOptions Convert(const Ark_ToggleOptions& src)
{
    return {
        .type = Converter::OptConvert<ToggleType>(src.type),
        .isOn = Converter::OptConvert<bool>(src.isOn)
    };
}

struct SwitchStyle {
    std::optional<Dimension> pointRadius;
    std::optional<Color> unselectedColor;
    std::optional<Color> pointColor;
    std::optional<Dimension> trackBorderRadius;
};

template<>
SwitchStyle Convert(const Ark_SwitchStyle& src)
{
    return {
        .pointRadius = Converter::OptConvert<Dimension>(src.pointRadius),
        .unselectedColor = Converter::OptConvert<Color>(src.unselectedColor),
        .pointColor = Converter::OptConvert<Color>(src.pointColor),
        .trackBorderRadius = Converter::OptConvert<Dimension>(src.trackBorderRadius)
    };
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ToggleModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = ToggleModelNG::CreateFrameNode(id, NG::ToggleType::SWITCH, false);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace ToggleModifier
namespace ToggleInterfaceModifier {
void SetToggleOptionsImpl(Ark_NativePointer node, const Ark_ToggleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto convValue = Converter::Convert<Converter::ToggleOptions>(*options);
    if (convValue.isOn.has_value()) {
        ToggleModelNG::SetToggleState(frameNode, convValue.isOn.value());
    }
    LOGE("ToggleModifier::SetToggleOptionsImpl. Set ToggleType is not supported!");
}
} // namespace ToggleInterfaceModifier
namespace ToggleAttributeModifier {
void OnChangeImpl(Ark_NativePointer node, const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [arkCallback = CallbackHelper(*value)](const bool isOn) {
        auto arkValue = Converter::ArkValue<Ark_Boolean>(isOn);
        arkCallback.Invoke(arkValue);
    };
    ToggleModelNG::OnChange(frameNode, std::move(onChange));
}
void ContentModifierImpl(Ark_NativePointer node, const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    // auto convValue = Converter::OptConvert<type_name>(*value);
    // ToggleModelNG::SetContentModifier(frameNode, convValue);
    LOGE("ToggleModifier::ContentModifierImpl is not implemented, Ark_CustomObject is not supported!");
}
void SelectedColorImpl(Ark_NativePointer node, const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    ToggleModelNG::SetSelectedColor(frameNode, convValue);
}
void SwitchPointColorImpl(Ark_NativePointer node, const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    ToggleModelNG::SetSwitchPointColor(frameNode, convValue);
}
void SwitchStyleImpl(Ark_NativePointer node, const Ark_SwitchStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<Converter::SwitchStyle>(*value);
    Validator::ValidateNonNegative(convValue.pointRadius);
    Validator::ValidateNonPercent(convValue.pointRadius);
    ToggleModelNG::SetSwitchPointColor(frameNode, convValue.pointColor);
    Validator::ValidateNonNegative(convValue.trackBorderRadius);
    Validator::ValidateNonPercent(convValue.trackBorderRadius);
}
void _onChangeEvent_isOnImpl(Ark_NativePointer node, const Callback_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](bool isOn) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(isOn));
    };
}
} // namespace ToggleAttributeModifier
const GENERATED_ArkUIToggleModifier* GetToggleModifier()
{
    static const GENERATED_ArkUIToggleModifier ArkUIToggleModifierImpl {
        ToggleModifier::ConstructImpl,
        ToggleInterfaceModifier::SetToggleOptionsImpl,
        ToggleAttributeModifier::OnChangeImpl,
        ToggleAttributeModifier::ContentModifierImpl,
        ToggleAttributeModifier::SelectedColorImpl,
        ToggleAttributeModifier::SwitchPointColorImpl,
        ToggleAttributeModifier::SwitchStyleImpl,
        ToggleAttributeModifier::_onChangeEvent_isOnImpl,
    };
    return &ArkUIToggleModifierImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
