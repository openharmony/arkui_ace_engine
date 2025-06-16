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
    if (options->tag != ARK_TAG_UNDEFINED) {
        auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
        CHECK_NULL_VOID(eventHub);

        auto name = Converter::OptConvert<Ark_CharPtr>(options->value.name);
        if (name) {
            eventHub->SetName(name.value());
        }

        auto group = Converter::OptConvert<Ark_CharPtr>(options->value.group);
        if (group) {
            eventHub->SetGroupName(group.value());
        }

        auto arkIndicatorBuilder = Converter::OptConvert<CustomNodeBuilder>(options->value.indicatorBuilder);
        if (arkIndicatorBuilder) {
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto customBuilder = [callback = CallbackHelper(arkIndicatorBuilder.value()), node,
                weakNode]() {
                PipelineContext::SetCallBackNode(weakNode);
                auto uiNode = callback.BuildSync(node);
                ViewStackProcessor::GetInstance()->Push(uiNode);
            };
            // CheckBoxModelNG::SetBuilder(frameNode, std::move(customBuilder));
        }
    }
}
} // CheckboxInterfaceModifier
namespace CheckboxAttributeModifier {
void SelectImpl(Ark_NativePointer node,
                Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, Converter::Convert<bool>(value));
}
void SelectedColorImpl(Ark_NativePointer node,
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
void ShapeImpl(Ark_NativePointer node,
               Ark_CheckBoxShape value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto checkBoxStyle = Converter::OptConvert<CheckBoxStyle>(value);
}
void UnselectedColorImpl(Ark_NativePointer node,
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
void MarkImpl(Ark_NativePointer node,
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
void OnChangeImpl(Ark_NativePointer node,
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
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CheckboxModelNG::SetContentModifier(frameNode, convValue);
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
}
} // CheckboxAttributeModifier
const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier()
{
    static const GENERATED_ArkUICheckboxModifier ArkUICheckboxModifierImpl {
        CheckboxModifier::ConstructImpl,
        CheckboxInterfaceModifier::SetCheckboxOptionsImpl,
        CheckboxAttributeModifier::SelectImpl,
        CheckboxAttributeModifier::SelectedColorImpl,
        CheckboxAttributeModifier::ShapeImpl,
        CheckboxAttributeModifier::UnselectedColorImpl,
        CheckboxAttributeModifier::MarkImpl,
        CheckboxAttributeModifier::OnChangeImpl,
        CheckboxAttributeModifier::ContentModifierImpl,
        CheckboxAttributeModifier::_onChangeEvent_selectImpl,
    };
    return &ArkUICheckboxModifierImpl;
}

}
