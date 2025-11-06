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
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace {
std::optional<bool> ProcessBindableSelect(FrameNode* frameNode, const Opt_Union_Boolean_Bindable *value)
{
    std::optional<bool> result;
    Converter::VisitUnionPtr(value,
        [&result](const Ark_Boolean& src) {
            result = Converter::OptConvert<bool>(src);
        },
        [&result, frameNode](const Ark_Bindable_Boolean& src) {
            result = Converter::OptConvert<bool>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const bool value) {
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(value));
            };
            CheckBoxModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
} // namespace OHOS::Ace::NG

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
namespace {
constexpr float CHECK_BOX_MARK_SIZE_INVALID_VALUE = -1.0f;
const Dimension CHECK_BOX_MARK_WIDTH_DEFAULT_VALUE = 2.0_vp;
}
void SetSelectImpl(Ark_NativePointer node,
                   const Opt_Union_Boolean_Bindable* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelStatic::SetSelect(frameNode, ProcessBindableSelect(frameNode, value));
}
void SetSelectedColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelStatic::SetSelectedColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetShapeImpl(Ark_NativePointer node,
                  const Opt_CheckBoxShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvertPtr<CheckBoxStyle>(value);
    if (!optValue) {
        CheckBoxModelStatic::SetCheckboxStyle(frameNode, CheckBoxStyle::CIRCULAR_STYLE);
        return;
    }
    CheckBoxModelStatic::SetCheckboxStyle(frameNode, *optValue);
}
void SetUnselectedColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelStatic::SetUnSelectedColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetMarkImpl(Ark_NativePointer node,
                 const Opt_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        CheckBoxModelStatic::SetCheckMarkColor(frameNode, std::nullopt);
        CheckBoxModelStatic::SetCheckMarkSize(frameNode, std::nullopt);
        CheckBoxModelStatic::SetCheckMarkWidth(frameNode, std::nullopt);
        return;
    }
    auto color = Converter::OptConvert<Color>(optValue->strokeColor);
    if (color) {
        CheckBoxModelStatic::SetCheckMarkColor(frameNode, color.value());
    }

    auto size = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(optValue->size, DimensionUnit::VP);
    if (!size.has_value() || (size.value().Unit() == DimensionUnit::PERCENT) || (size.value().IsNegative())) {
        size = Dimension(CHECK_BOX_MARK_SIZE_INVALID_VALUE);
    }
    CheckBoxModelStatic::SetCheckMarkSize(frameNode, size);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<CheckboxTheme>();
    auto defaultStroke = theme ? theme->GetCheckStroke() : CHECK_BOX_MARK_WIDTH_DEFAULT_VALUE;
    auto width = optValue->strokeWidth.tag == INTEROP_TAG_UNDEFINED
        ? defaultStroke
        : Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Float64>(optValue->strokeWidth, DimensionUnit::VP);
    if (!width.has_value() || (width.value().Unit() == DimensionUnit::PERCENT) || (width.value().IsNegative())) {
        width = defaultStroke;
    }
    CheckBoxModelStatic::SetCheckMarkWidth(frameNode, width);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_OnCheckboxChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optCallback = Converter::GetOptPtr(value);
    CHECK_NULL_VOID(optCallback);
    auto onEvent = [arkCallback = CallbackHelper(*optCallback)](const bool value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(value));
    };
    CheckBoxModelNG::SetOnChange(frameNode, std::move(onEvent));
}
} // CheckboxAttributeModifier
const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier()
{
    static const GENERATED_ArkUICheckboxModifier ArkUICheckboxModifierImpl {
        CheckboxModifier::ConstructImpl,
        CheckboxInterfaceModifier::SetCheckboxOptionsImpl,
        CheckboxAttributeModifier::SetSelectImpl,
        CheckboxAttributeModifier::SetSelectedColorImpl,
        CheckboxAttributeModifier::SetShapeImpl,
        CheckboxAttributeModifier::SetUnselectedColorImpl,
        CheckboxAttributeModifier::SetMarkImpl,
        CheckboxAttributeModifier::SetOnChangeImpl,
    };
    return &ArkUICheckboxModifierImpl;
}

}
