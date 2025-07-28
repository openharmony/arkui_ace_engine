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

#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_static.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter2.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CheckboxGroupModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = CheckBoxGroupModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // CheckboxGroupModifier
namespace CheckboxGroupInterfaceModifier {
void SetCheckboxGroupOptionsImpl(Ark_NativePointer node,
                                 const Opt_CheckboxGroupOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    Converter::WithOptional(*options, [frameNode](const Ark_CheckboxGroupOptions& options) {
        auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto group = Converter::OptConvert<std::string>(options.group);
        if (group) {
            eventHub->SetGroupName(group.value());
        }
    });
}
} // CheckboxGroupInterfaceModifier
namespace CheckboxGroupAttributeModifier {
void SelectAll0Impl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelStatic::SetSelectAll(frameNode, value ? Converter::OptConvert<bool>(*value) : std::nullopt);
}
void SelectAll1Impl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    SelectAll0Impl(node, value);
}
void SelectedColor0Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelStatic::SetSelectedColor(frameNode, value ? Converter::OptConvert<Color>(*value) : std::nullopt);
}
void SelectedColor1Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    SelectedColor0Impl(node, value);
}
void UnselectedColor0Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelStatic::SetUnSelectedColor(
        frameNode, value ? Converter::OptConvert<Color>(*value) : std::nullopt);
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
    if (auto color = Converter::OptConvert<Color>(optValue->strokeColor); color) {
        CheckBoxGroupModelStatic::SetCheckMarkColor(frameNode, color);
    }
    if (auto size = Converter::OptConvert<Dimension>(optValue->size); size) {
        CheckBoxGroupModelStatic::SetCheckMarkSize(frameNode, size);
    }
    if (auto strokeWidth = Converter::OptConvert<Dimension>(optValue->strokeWidth); strokeWidth) {
        CheckBoxGroupModelStatic::SetCheckMarkWidth(frameNode, strokeWidth);
    }
}
void Mark1Impl(Ark_NativePointer node,
               const Opt_MarkStyle* value)
{
    Mark0Impl(node, value);
}
void OnChange0Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxGroupChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        CHECK_NULL_VOID(eventInfo);
        Converter::ArkArrayHolder<Array_String> vecHolder(eventInfo->GetNameList());
        Ark_CheckboxGroupResult result {
            .name = vecHolder.ArkValue(),
            .status = Converter::ArkValue<Ark_SelectStatus>(eventInfo->GetStatus())
        };
        arkCallback.Invoke(result);
    };
    CheckBoxGroupModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxGroupChangeCallback* value)
{
    OnChange0Impl(node, value);
}
void CheckboxShape0Impl(Ark_NativePointer node,
                        const Opt_CheckBoxShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelStatic::SetCheckboxGroupStyle(frameNode,
        value ? Converter::OptConvert<OHOS::Ace::CheckBoxStyle>(*value) : std::nullopt);
}
void CheckboxShape1Impl(Ark_NativePointer node,
                        const Opt_CheckBoxShape* value)
{
    CheckboxShape0Impl(node, value);
}
void _onChangeEvent_selectAllImpl(Ark_NativePointer node,
                                  const Callback_Opt_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const BaseEventInfo* info) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        if (eventInfo) {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke(Converter::ArkValue<Opt_Boolean>(eventInfo->GetStatus() == 0));
        }
    };
    CheckBoxGroupModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
}
} // CheckboxGroupAttributeModifier
const GENERATED_ArkUICheckboxGroupModifier* GetCheckboxGroupModifier()
{
    static const GENERATED_ArkUICheckboxGroupModifier ArkUICheckboxGroupModifierImpl {
        CheckboxGroupModifier::ConstructImpl,
        CheckboxGroupInterfaceModifier::SetCheckboxGroupOptionsImpl,
        CheckboxGroupAttributeModifier::SelectAll0Impl,
        CheckboxGroupAttributeModifier::SelectAll1Impl,
        CheckboxGroupAttributeModifier::SelectedColor0Impl,
        CheckboxGroupAttributeModifier::SelectedColor1Impl,
        CheckboxGroupAttributeModifier::UnselectedColor0Impl,
        CheckboxGroupAttributeModifier::UnselectedColor1Impl,
        CheckboxGroupAttributeModifier::Mark0Impl,
        CheckboxGroupAttributeModifier::Mark1Impl,
        CheckboxGroupAttributeModifier::OnChange0Impl,
        CheckboxGroupAttributeModifier::OnChange1Impl,
        CheckboxGroupAttributeModifier::CheckboxShape0Impl,
        CheckboxGroupAttributeModifier::CheckboxShape1Impl,
        CheckboxGroupAttributeModifier::_onChangeEvent_selectAllImpl,
    };
    return &ArkUICheckboxGroupModifierImpl;
}

}
