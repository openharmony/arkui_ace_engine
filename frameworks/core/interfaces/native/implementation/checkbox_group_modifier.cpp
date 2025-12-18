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
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace {
std::optional<bool> ProcessBindableSelectAll(FrameNode* frameNode, const Opt_Union_Boolean_Bindable_Boolean *value)
{
    std::optional<bool> result;
    Converter::VisitUnionPtr(value,
        [&result](const Ark_Boolean& src) {
            result = Converter::OptConvert<bool>(src);
        },
        [&result, frameNode](const Ark_Bindable_Boolean& src) {
            result = Converter::OptConvert<bool>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const BaseEventInfo* info) {
                const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
                if (eventInfo) {
                    PipelineContext::SetCallBackNode(weakNode);
                    arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(eventInfo->GetStatus() == 0));
                }
            };
            CheckBoxGroupModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
        },
        [&result] {
            result = false;
        });
    return result;
}
} // namespace
} // namespace OHOS::Ace::NG

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
namespace {
constexpr float CHECK_BOX_GROUP_MARK_SIZE_INVALID_VALUE = -1.0f;
const Dimension CHECK_BOX_GROUP_MARK_WIDTH_DEFAULT_VALUE = 2.0_vp;
}
void SetSelectAllImpl(Ark_NativePointer node,
                      const Opt_Union_Boolean_Bindable_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelStatic::SetSelectAll(frameNode, ProcessBindableSelectAll(frameNode, value));
}
void SetSelectedColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelStatic::SetSelectedColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetUnselectedColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelStatic::SetUnSelectedColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetMarkImpl(Ark_NativePointer node,
                 const Opt_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    if (auto color = Converter::OptConvert<Color>(optValue->strokeColor); color) {
        CheckBoxGroupModelStatic::SetCheckMarkColor(frameNode, color);
    } else {
        CheckBoxGroupModelStatic::ResetCheckMarkColor(frameNode);
    }
    auto size = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(optValue->size, DimensionUnit::VP);
    if (!size.has_value() || (size.value().Unit() == DimensionUnit::PERCENT) || (size.value().IsNegative())) {
        size = Dimension(CHECK_BOX_GROUP_MARK_SIZE_INVALID_VALUE);
    }
    CheckBoxGroupModelStatic::SetCheckMarkSize(frameNode, size);
    auto strokeWidth =
        Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(optValue->strokeWidth, DimensionUnit::VP);
    if (!strokeWidth.has_value() || (strokeWidth.value().Unit() == DimensionUnit::PERCENT)
        || (strokeWidth.value().IsNegative())) {
        auto context = frameNode->GetContext();
        CHECK_NULL_VOID(context);
        auto theme = context->GetTheme<CheckboxTheme>();
        auto defaultStroke = theme ? theme->GetCheckStroke() : CHECK_BOX_GROUP_MARK_WIDTH_DEFAULT_VALUE;
        strokeWidth = defaultStroke;
    }
    CheckBoxGroupModelStatic::SetCheckMarkWidth(frameNode, strokeWidth);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_OnCheckboxGroupChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        CheckBoxGroupModelStatic::SetOnChange(frameNode, nullptr);
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
    CheckBoxGroupModelStatic::SetOnChange(frameNode, std::move(onEvent));
}
void SetCheckboxShapeImpl(Ark_NativePointer node,
                          const Opt_CheckBoxShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxGroupModelStatic::SetCheckboxGroupStyle(frameNode, Converter::OptConvertPtr<Ace::CheckBoxStyle>(value));
}
} // CheckboxGroupAttributeModifier
const GENERATED_ArkUICheckboxGroupModifier* GetCheckboxGroupModifier()
{
    static const GENERATED_ArkUICheckboxGroupModifier ArkUICheckboxGroupModifierImpl {
        CheckboxGroupModifier::ConstructImpl,
        CheckboxGroupInterfaceModifier::SetCheckboxGroupOptionsImpl,
        CheckboxGroupAttributeModifier::SetSelectAllImpl,
        CheckboxGroupAttributeModifier::SetSelectedColorImpl,
        CheckboxGroupAttributeModifier::SetUnselectedColorImpl,
        CheckboxGroupAttributeModifier::SetMarkImpl,
        CheckboxGroupAttributeModifier::SetOnChangeImpl,
        CheckboxGroupAttributeModifier::SetCheckboxShapeImpl,
    };
    return &ArkUICheckboxGroupModifierImpl;
}

}
