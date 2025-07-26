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
#include "core/components_ng/pattern/checkbox/checkbox_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter2.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
void SetBuilder(Ark_NativePointer node, FrameNode* frameNode, CustomNodeBuilder& customNodeBuilder)
{
    CallbackHelper(customNodeBuilder).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) mutable {
        auto builder = [uiNode]() {
            ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        CheckBoxModelStatic::SetBuilder(frameNode, std::move(builder));
        }, node);
}
}
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
            SetBuilder(node, frameNode, arkIndicatorBuilder.value());
        }
    });
}
} // CheckboxInterfaceModifier
namespace CheckboxAttributeModifier {
void Select0Impl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelStatic::SetSelect(frameNode, value ? Converter::OptConvert<bool>(*value) : std::nullopt);
}
void Select1Impl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    Select0Impl(node, value);
}
void SelectedColor0Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelStatic::SetSelectedColor(frameNode, value ? Converter::OptConvert<Color>(*value) : std::nullopt);
}
void SelectedColor1Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    SelectedColor0Impl(node, value);
}
void Shape0Impl(Ark_NativePointer node, const Opt_CheckBoxShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelStatic::SetCheckboxStyle(
        frameNode, value ? Converter::OptConvert<CheckBoxStyle>(*value) : std::nullopt);
}
void Shape1Impl(Ark_NativePointer node, const Opt_CheckBoxShape* value)
{
    Shape0Impl(node, value);
}
void UnselectedColor0Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelStatic::SetUnSelectedColor(frameNode, value ? Converter::OptConvert<Color>(*value) : std::nullopt);
}
void UnselectedColor1Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    UnselectedColor0Impl(node, value);
}
void Mark0Impl(Ark_NativePointer node,
               const Opt_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto color = Converter::OptConvert<Color>(optValue->strokeColor);
    if (color) {
        CheckBoxModelStatic::SetCheckMarkColor(frameNode, color.value());
    }

    auto size = Converter::OptConvert<Dimension>(optValue->size);
    if (size) {
        CheckBoxModelStatic::SetCheckMarkSize(frameNode, size.value());
    }

    auto width = Converter::OptConvert<Dimension>(optValue->strokeWidth);
    if (width) {
        CheckBoxModelStatic::SetCheckMarkWidth(frameNode, width.value());
    }
}
void Mark1Impl(Ark_NativePointer node,
               const Opt_MarkStyle* value)
{
    Mark0Impl(node, value);
}
void OnChange0Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optCallback = Converter::OptConvert<OnCheckboxChangeCallback>(*value);
    CHECK_NULL_VOID(optCallback);
    auto onEvent = [arkCallback = CallbackHelper(*optCallback)](const bool value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(value));
    };
    CheckBoxModelNG::SetOnChange(frameNode, std::move(onEvent));
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxChangeCallback* value)
{
    OnChange0Impl(node, value);
}
void ContentModifier0Impl(Ark_NativePointer node,
                          const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void ContentModifier1Impl(Ark_NativePointer node,
                          const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void _onChangeEvent_selectImpl(Ark_NativePointer node,
                               const Callback_Opt_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const bool value) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Opt_Boolean>(value));
    };
    CheckBoxModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
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
