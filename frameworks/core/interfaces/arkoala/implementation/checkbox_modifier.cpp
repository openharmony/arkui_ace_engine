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
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CheckboxInterfaceModifier {
void SetCheckboxOptionsImpl(Ark_NativePointer node,
                            const Opt_CheckboxOptions* options)
{
    CHECK_NULL_VOID(options);
    if (options->tag != ARK_TAG_UNDEFINED) {
        auto frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
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
    }
}
} // CheckboxInterfaceModifier
namespace CheckboxAttributeModifier {
void SelectImpl(Ark_NativePointer node,
                Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, static_cast<bool>(value));
}
void SelectedColorImpl(Ark_NativePointer node,
                       const ResourceColor* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvert<Color>(*value);
    if (color) {
        CheckBoxModelNG::SetSelectedColor(frameNode, color.value());
    }
}
void ShapeImpl(Ark_NativePointer node,
               enum Ark_CheckBoxShape value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckboxStyle(frameNode, static_cast<CheckBoxStyle>(value));
}
void UnselectedColorImpl(Ark_NativePointer node,
                         const ResourceColor* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvert<Color>(*value);
    if (color) {
        CheckBoxModelNG::SetUnSelectedColor(frameNode, color.value());
    }
}
void MarkImpl(Ark_NativePointer node,
              const Ark_MarkStyle* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

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
                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](const bool value) {
        GetFullAPI()->getEventsAPI()->getCheckboxEventsReceiver()->onChange(frameNode->GetId(), value);
    };

    CheckBoxModelNG::SetOnChange(frameNode, std::move(onEvent));
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* modifier)
{
}
} // CheckboxAttributeModifier
const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier()
{
    static const GENERATED_ArkUICheckboxModifier ArkUICheckboxModifierImpl {
        CheckboxInterfaceModifier::SetCheckboxOptionsImpl,
        CheckboxAttributeModifier::SelectImpl,
        CheckboxAttributeModifier::SelectedColorImpl,
        CheckboxAttributeModifier::ShapeImpl,
        CheckboxAttributeModifier::UnselectedColorImpl,
        CheckboxAttributeModifier::MarkImpl,
        CheckboxAttributeModifier::OnChangeImpl,
        CheckboxAttributeModifier::ContentModifierImpl,
    };
    return &ArkUICheckboxModifierImpl;
}
}
