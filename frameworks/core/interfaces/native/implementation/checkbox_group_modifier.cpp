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
void SelectAll1Impl(Ark_NativePointer node, const Opt_Boolean* value);
void SelectedColor1Impl(Ark_NativePointer node, const Opt_ResourceColor* value);
void UnselectedColor1Impl(Ark_NativePointer node, const Opt_ResourceColor* value);
void Mark1Impl(Ark_NativePointer node, const Opt_MarkStyle* value);
void OnChange1Impl(Ark_NativePointer node, const Opt_OnCheckboxGroupChangeCallback* value);
void CheckboxShape1Impl(Ark_NativePointer node, const Opt_CheckBoxShape* value);

void SelectAll0Impl(Ark_NativePointer node,
                    Ark_Boolean value)
{
   const auto optValue = Converter::ArkValue<Opt_Boolean, Ark_Boolean>(value);
   SelectAll1Impl(node, &optValue);
}
void SelectAll1Impl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{    
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    const auto value1 = Converter::Convert<bool>(*value);
 //   CheckBoxGroupModelNG::SetSelectAll(frameNode, *optValue);
    bool b = true;
    CheckBoxGroupModelNG::SetSelectAll(value1);
}
void SelectedColor0Impl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
{
    const auto optValue = Converter::ArkValue<Opt_ResourceColor, Ark_ResourceColor>(*value);
    SelectedColor1Impl(node, &optValue);
}
void SelectedColor1Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (auto color = Converter::OptConvert<Color>(*value); color) {
//        CheckBoxGroupModelNG::SetSelectedColor(frameNode, color.value());
    }
}
void UnselectedColor0Impl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    const auto optValue = Converter::ArkValue<Opt_ResourceColor, Ark_ResourceColor>(*value);
    UnselectedColor1Impl(node, &optValue);
}
void UnselectedColor1Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (auto color = Converter::OptConvert<Color>(*value); color) {
//        CheckBoxGroupModelNG::SetUnSelectedColor(frameNode, color.value());
    }
}
void Mark0Impl(Ark_NativePointer node,
               const Ark_MarkStyle* value)
{
    const auto optValue = Converter::ArkValue<Opt_MarkStyle, Ark_MarkStyle>(*value);
    Mark1Impl(node, &optValue);
}
void Mark1Impl(Ark_NativePointer node,
               const Opt_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto arkValue = (*value).value;

    if (auto color = Converter::OptConvert<Color>(arkValue.strokeColor); color) {
//        CheckBoxGroupModelNG::SetCheckMarkColor(frameNode, color);
    }
    if (auto size = Converter::OptConvert<Dimension>(arkValue.size); size) {
//        CheckBoxGroupModelNG::SetCheckMarkSize(frameNode, size);
    }
    if (auto strokeWidth = Converter::OptConvert<Dimension>(arkValue.strokeWidth); strokeWidth) {
//        CheckBoxGroupModelNG::SetCheckMarkWidth(frameNode, strokeWidth);
    }
}
void OnChange0Impl(Ark_NativePointer node,
                   const OnCheckboxGroupChangeCallback* value)
{
    const auto opt = Converter::ArkValue<Opt_OnCheckboxGroupChangeCallback, OnCheckboxGroupChangeCallback>(*value);
    OnChange1Impl(node, &opt);
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnCheckboxGroupChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [frameNode](const BaseEventInfo* info) {
        Ark_CheckboxGroupResult result;
//        GetFullAPI()->getEventsAPI()->getCheckboxGroupEventsReceiver()->onChange0(frameNode->GetId(), result);
    };
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onEvent));
}
void CheckboxShape0Impl(Ark_NativePointer node,
                        Ark_CheckBoxShape value)
{
    const auto optValue = Converter::ArkValue<Opt_CheckBoxShape, Ark_CheckBoxShape>(value);
    CheckboxShape1Impl(node, &optValue);
}
void CheckboxShape1Impl(Ark_NativePointer node,
                        const Opt_CheckBoxShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
 //   auto style = Converter::OptConvert<CheckBoxStyle>(*value);
 //   CheckBoxGroupModelNG::SetCheckboxGroupStyle(frameNode, style);
}
void __onChangeEvent_selectAllImpl(Ark_NativePointer node,
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
        CheckboxGroupAttributeModifier::__onChangeEvent_selectAllImpl,
    };
    return &ArkUICheckboxGroupModifierImpl;
}
}
/*template<>
void AssignCast(std::optional<OHOS::Ace::CheckBoxStyle>& dst, const Ark_CheckBoxShape& src)
{
    switch (src) {
        case ARK_CHECK_BOX_SHAPE_CIRCLE: dst = OHOS::Ace::CheckBoxStyle::CIRCULAR_STYLE; break;
        case ARK_CHECK_BOX_SHAPE_ROUNDED_SQUARE: dst = OHOS::Ace::CheckBoxStyle::SQUARE_STYLE; break;
        default: {
            LOGE("Unexpected enum value in Ark_CheckBoxShape: %{public}d", src);
        }
    }
}*/


/*void AssignArkValue(Ark_CheckBoxShape& dst, const OHOS::Ace::CheckBoxStyle& src)
{
    switch (src) {
        case OHOS::Ace::CheckBoxStyle::CIRCULAR_STYLE: dst = ARK_CHECK_BOX_SHAPE_CIRCLE; break;
        case OHOS::Ace::CheckBoxStyle::SQUARE_STYLE: dst = ARK_CHECK_BOX_SHAPE_ROUNDED_SQUARE; break;
         default:
            dst = static_cast<Ark_CheckBoxShape>(-1);
            LOGE("Unexpected enum value in CheckBoxStyle: %{public}d", src);
    }
}*/