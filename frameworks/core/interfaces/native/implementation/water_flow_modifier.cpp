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
namespace WaterFlowModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // WaterFlowModifier
namespace WaterFlowInterfaceModifier {
void SetWaterFlowOptionsImpl(Ark_NativePointer node,
                             const Opt_WaterFlowOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //WaterFlowModelNG::SetSetWaterFlowOptions(frameNode, convValue);
}
} // WaterFlowInterfaceModifier
namespace WaterFlowAttributeModifier {
void SetColumnsTemplateImpl(Ark_NativePointer node,
                            const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WaterFlowModelNG::SetSetColumnsTemplate(frameNode, convValue);
}
void SetItemConstraintSizeImpl(Ark_NativePointer node,
                               const Opt_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WaterFlowModelNG::SetSetItemConstraintSize(frameNode, convValue);
}
void SetRowsTemplateImpl(Ark_NativePointer node,
                         const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WaterFlowModelNG::SetSetRowsTemplate(frameNode, convValue);
}
void SetColumnsGapImpl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WaterFlowModelNG::SetSetColumnsGap(frameNode, convValue);
}
void SetRowsGapImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WaterFlowModelNG::SetSetRowsGap(frameNode, convValue);
}
void SetLayoutDirectionImpl(Ark_NativePointer node,
                            const Opt_FlexDirection* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WaterFlowModelNG::SetSetLayoutDirection(frameNode, convValue);
}
void SetCachedCount0Impl(Ark_NativePointer node,
                         const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WaterFlowModelNG::SetSetCachedCount0(frameNode, convValue);
}
void SetOnScrollFrameBeginImpl(Ark_NativePointer node,
                               const Opt_OnScrollFrameBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WaterFlowModelNG::SetSetOnScrollFrameBegin(frameNode, convValue);
}
void SetOnScrollIndexImpl(Ark_NativePointer node,
                          const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WaterFlowModelNG::SetSetOnScrollIndex(frameNode, convValue);
}
void SetOnWillScrollImpl(Ark_NativePointer node,
                         const Opt_OnWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WaterFlowModelNG::SetSetOnWillScroll(frameNode, convValue);
}
void SetOnDidScrollImpl(Ark_NativePointer node,
                        const Opt_OnScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //WaterFlowModelNG::SetSetOnDidScroll(frameNode, convValue);
}
void SetCachedCount1Impl(Ark_NativePointer node,
                         const Opt_Number* count,
                         const Opt_Boolean* show)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(count);
    //auto convValue = Converter::OptConvert<type>(count); // for enums
    //WaterFlowModelNG::SetSetCachedCount1(frameNode, convValue);
}
} // WaterFlowAttributeModifier
const GENERATED_ArkUIWaterFlowModifier* GetWaterFlowModifier()
{
    static const GENERATED_ArkUIWaterFlowModifier ArkUIWaterFlowModifierImpl {
        WaterFlowModifier::ConstructImpl,
        WaterFlowInterfaceModifier::SetWaterFlowOptionsImpl,
        WaterFlowAttributeModifier::SetColumnsTemplateImpl,
        WaterFlowAttributeModifier::SetItemConstraintSizeImpl,
        WaterFlowAttributeModifier::SetRowsTemplateImpl,
        WaterFlowAttributeModifier::SetColumnsGapImpl,
        WaterFlowAttributeModifier::SetRowsGapImpl,
        WaterFlowAttributeModifier::SetLayoutDirectionImpl,
        WaterFlowAttributeModifier::SetCachedCount0Impl,
        WaterFlowAttributeModifier::SetOnScrollFrameBeginImpl,
        WaterFlowAttributeModifier::SetOnScrollIndexImpl,
        WaterFlowAttributeModifier::SetOnWillScrollImpl,
        WaterFlowAttributeModifier::SetOnDidScrollImpl,
        WaterFlowAttributeModifier::SetCachedCount1Impl,
    };
    return &ArkUIWaterFlowModifierImpl;
}

}
