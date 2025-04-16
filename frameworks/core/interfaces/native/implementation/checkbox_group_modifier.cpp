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
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_SelectStatus& dst, const int32_t& src)
{
    switch (src) {
        case static_cast<int32_t>(ARK_SELECT_STATUS_ALL): dst = ARK_SELECT_STATUS_ALL; break;
        case static_cast<int32_t>(ARK_SELECT_STATUS_PART): dst = ARK_SELECT_STATUS_PART; break;
        case static_cast<int32_t>(ARK_SELECT_STATUS_NONE): dst = ARK_SELECT_STATUS_NONE; break;
        default: dst = static_cast<Ark_SelectStatus>(-1);
            LOGE("Unexpected enum value in SelectStatus: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter

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
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetSelectAll(frameNode, static_cast<bool>(value));
}
void SelectAll1Impl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetSelectAll1(frameNode, convValue);
}
void SelectedColor0Impl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (auto color = Converter::OptConvert<Color>(*value); color) {
        CheckBoxGroupModelNG::SetSelectedColor(frameNode, color.value());
    }
}
void SelectedColor1Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetSelectedColor1(frameNode, convValue);
}
void UnselectedColor0Impl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (auto color = Converter::OptConvert<Color>(*value); color) {
        CheckBoxGroupModelNG::SetUnSelectedColor(frameNode, color.value());
    }
}
void UnselectedColor1Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetUnselectedColor1(frameNode, convValue);
}
void Mark0Impl(Ark_NativePointer node,
               const Ark_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (auto color = Converter::OptConvert<Color>(value->strokeColor); color) {
        CheckBoxGroupModelNG::SetCheckMarkColor(frameNode, color.value());
    }
    if (auto size = Converter::OptConvert<Dimension>(value->size); size) {
        CheckBoxGroupModelNG::SetCheckMarkSize(frameNode, size.value());
    }
    if (auto strokeWidth = Converter::OptConvert<Dimension>(value->strokeWidth); strokeWidth) {
        CheckBoxGroupModelNG::SetCheckMarkWidth(frameNode, strokeWidth.value());
    }
}
void Mark1Impl(Ark_NativePointer node,
               const Opt_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetMark1(frameNode, convValue);
}
void OnChange0Impl(Ark_NativePointer node,
                   const OnCheckboxGroupChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [arkCallback = CallbackHelper(*value)](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        CHECK_NULL_VOID(eventInfo);
        Converter::ArkArrayHolder<Array_String> vecHolder(eventInfo->GetNameList());
        Ark_CheckboxGroupResult result {
            .name = vecHolder.ArkValue(),
            .status = Converter::ArkValue<Ark_SelectStatus>(eventInfo->GetStatus())
        };
        arkCallback.Invoke(result);
    };
    CheckBoxGroupModelNG::SetChangeEvent(frameNode, std::move(onEvent));
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxGroupChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetOnChange1(frameNode, convValue);
}
void CheckboxShape0Impl(Ark_NativePointer node,
                        Ark_CheckBoxShape value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelNG::SetCheckboxGroupStyle(frameNode, static_cast<CheckBoxStyle>(value));
}
void CheckboxShape1Impl(Ark_NativePointer node,
                        const Opt_CheckBoxShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxGroupModelNG::SetCheckboxShape1(frameNode, convValue);
}
void _onChangeEvent_selectAllImpl(Ark_NativePointer node,
                                  const Callback_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const BaseEventInfo* info) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        if (eventInfo) {
            PipelineContext::SetCallBackNode(weakNode);
            arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(eventInfo->GetStatus() == 0));
        }
    };
    CheckBoxGroupModelNG::SetChangeEvent(frameNode, std::move(onEvent));
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
