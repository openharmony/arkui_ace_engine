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
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG::Converter {
    template<>
    void AssignCast(std::optional<CheckBoxStyle>& dst, const Ark_CheckBoxShape& src)
    {
        switch (src) {
            case ARK_CHECK_BOX_SHAPE_CIRCLE: dst = CheckBoxStyle::CIRCULAR_STYLE; break;
            case ARK_CHECK_BOX_SHAPE_ROUNDED_SQUARE: dst = CheckBoxStyle::SQUARE_STYLE; break;
            default: LOGE("Unexpected enum value in Ark_CheckBoxShape: %{public}d", src);
        }
    }
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CheckboxModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = CheckBoxModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // CheckboxModifier
namespace CheckboxInterfaceModifier {
void SetCheckboxOptionsImpl(Ark_NativePointer node,
                            const Opt_CheckboxOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    Converter::WithOptional(*options, [frameNode, node](const Ark_CheckboxOptions& options) {
        auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
        CHECK_NULL_VOID(eventHub);

        auto name = Converter::OptConvert<std::string>(options.name);
        if (name) {
            eventHub->SetName(name.value());
        }

        auto group = Converter::OptConvert<std::string>(options.group);
        if (group) {
            eventHub->SetGroupName(group.value());
        }

        auto arkIndicatorBuilder = Converter::OptConvert<CustomNodeBuilder>(options.indicatorBuilder);
        if (arkIndicatorBuilder) {
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto customBuilder = [callback = CallbackHelper(arkIndicatorBuilder.value()), node,
                weakNode]() {
                PipelineContext::SetCallBackNode(weakNode);
                auto uiNode = callback.BuildSync(node);
                ViewStackProcessor::GetInstance()->Push(uiNode);
            };
            CheckBoxModelNG::SetBuilder(frameNode, std::move(customBuilder));
        }
    });
}
} // CheckboxInterfaceModifier
namespace CheckboxAttributeModifier {
void Select0Impl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, Converter::Convert<bool>(value));
}
void Select1Impl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetSelect1(frameNode, convValue);
}
void SelectedColor0Impl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = Converter::OptConvert<Color>(*value);
    if (color) {
        CheckBoxModelNG::SetSelectedColor(frameNode, color.value());
    }
}
void SelectedColor1Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetSelectedColor1(frameNode, convValue);
}
void Shape0Impl(Ark_NativePointer node,
                Ark_CheckBoxShape value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto checkBoxStyle = Converter::OptConvert<CheckBoxStyle>(value);
    CheckBoxModelNG::SetCheckboxStyle(frameNode, checkBoxStyle);
}
void Shape1Impl(Ark_NativePointer node,
                const Opt_CheckBoxShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetShape1(frameNode, convValue);
}
void UnselectedColor0Impl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = Converter::OptConvert<Color>(*value);
    if (color) {
        CheckBoxModelNG::SetUnSelectedColor(frameNode, color.value());
    }
}
void UnselectedColor1Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetUnselectedColor1(frameNode, convValue);
}
void Mark0Impl(Ark_NativePointer node,
               const Ark_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto color = Converter::OptConvert<Color>(value->strokeColor);
    if (color) {
        CheckBoxModelNG::SetCheckMarkColor(frameNode, color.value());
    }

    auto size = Converter::OptConvert<Dimension>(value->size);
    if (size) {
        CheckBoxModelNG::SetCheckMarkSize(frameNode, size.value());
    }

    auto width = Converter::OptConvert<Dimension>(value->strokeWidth);
    if (width) {
        CheckBoxModelNG::SetCheckMarkWidth(frameNode, width.value());
    }
}
void Mark1Impl(Ark_NativePointer node,
               const Opt_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetMark1(frameNode, convValue);
}
void OnChange0Impl(Ark_NativePointer node,
                   const OnCheckboxChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [arkCallback = CallbackHelper(*value)](const bool value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(value));
    };
    CheckBoxModelNG::SetOnChange(frameNode, std::move(onEvent));
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetOnChange1(frameNode, convValue);
}
void ContentModifier0Impl(Ark_NativePointer node,
                          const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CheckboxModelNG::SetContentModifier0(frameNode, convValue);
}
void ContentModifier1Impl(Ark_NativePointer node,
                          const Opt_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetContentModifier1(frameNode, convValue);
}
void _onChangeEvent_selectImpl(Ark_NativePointer node,
                               const Callback_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const bool value) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(value));
    };
    CheckBoxModelNG::SetChangeEvent(frameNode, std::move(onEvent));
}
} // CheckboxAttributeModifier
const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier()
{
    static const GENERATED_ArkUICheckboxModifier ArkUICheckboxModifierImpl {
        CheckboxModifier::ConstructImpl,
        CheckboxInterfaceModifier::SetCheckboxOptionsImpl,
        CheckboxAttributeModifier::Select0Impl,
        CheckboxAttributeModifier::Select1Impl,
        CheckboxAttributeModifier::SelectedColor0Impl,
        CheckboxAttributeModifier::SelectedColor1Impl,
        CheckboxAttributeModifier::Shape0Impl,
        CheckboxAttributeModifier::Shape1Impl,
        CheckboxAttributeModifier::UnselectedColor0Impl,
        CheckboxAttributeModifier::UnselectedColor1Impl,
        CheckboxAttributeModifier::Mark0Impl,
        CheckboxAttributeModifier::Mark1Impl,
        CheckboxAttributeModifier::OnChange0Impl,
        CheckboxAttributeModifier::OnChange1Impl,
        CheckboxAttributeModifier::ContentModifier0Impl,
        CheckboxAttributeModifier::ContentModifier1Impl,
        CheckboxAttributeModifier::_onChangeEvent_selectImpl,
    };
    return &ArkUICheckboxModifierImpl;
}

}
