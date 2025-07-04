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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

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
    return {};
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
void SetSelectImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetSetSelect(frameNode, convValue);
}
void SetSelectedColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetSetSelectedColor(frameNode, convValue);
}
void SetShapeImpl(Ark_NativePointer node,
                  const Opt_CheckBoxShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetSetShape(frameNode, convValue);
}
void SetUnselectedColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetSetUnselectedColor(frameNode, convValue);
}
void SetMarkImpl(Ark_NativePointer node,
                 const Opt_MarkStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetSetMark(frameNode, convValue);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_OnCheckboxChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetSetOnChange(frameNode, convValue);
}
void SetContentModifierImpl(Ark_NativePointer node,
                            const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CheckboxModelNG::SetSetContentModifier(frameNode, convValue);
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
        CheckboxAttributeModifier::SetContentModifierImpl,
    };
    return &ArkUICheckboxModifierImpl;
}

}
