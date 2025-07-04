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
namespace TextFieldOpsAccessor {
Ark_NativePointer RegisterTextFieldValueCallbackImpl(Ark_NativePointer node,
                                                     const Ark_ResourceStr* value,
                                                     const TextFieldValueCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetRegisterTextFieldValueCallback(frameNode, convValue);
    return {};
}
Ark_NativePointer TextFieldOpsSetWidthImpl(Ark_NativePointer node,
                                           const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetTextFieldOpsSetWidth(frameNode, convValue);
    return {};
}
Ark_NativePointer TextFieldOpsSetHeightImpl(Ark_NativePointer node,
                                            const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetTextFieldOpsSetHeight(frameNode, convValue);
    return {};
}
Ark_NativePointer TextFieldOpsSetPaddingImpl(Ark_NativePointer node,
                                             const Opt_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetTextFieldOpsSetPadding(frameNode, convValue);
    return {};
}
Ark_NativePointer TextFieldOpsSetMarginImpl(Ark_NativePointer node,
                                            const Opt_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetTextFieldOpsSetMargin(frameNode, convValue);
    return {};
}
Ark_NativePointer TextFieldOpsSetBorderImpl(Ark_NativePointer node,
                                            const Opt_BorderOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetTextFieldOpsSetBorder(frameNode, convValue);
    return {};
}
Ark_NativePointer TextFieldOpsSetBorderWidthImpl(Ark_NativePointer node,
                                                 const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetTextFieldOpsSetBorderWidth(frameNode, convValue);
    return {};
}
Ark_NativePointer TextFieldOpsSetBorderColorImpl(Ark_NativePointer node,
                                                 const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetTextFieldOpsSetBorderColor(frameNode, convValue);
    return {};
}
Ark_NativePointer TextFieldOpsSetBorderStyleImpl(Ark_NativePointer node,
                                                 const Opt_Union_BorderStyle_EdgeStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetTextFieldOpsSetBorderStyle(frameNode, convValue);
    return {};
}
Ark_NativePointer TextFieldOpsSetBorderRadiusImpl(Ark_NativePointer node,
                                                  const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetTextFieldOpsSetBorderRadius(frameNode, convValue);
    return {};
}
Ark_NativePointer TextFieldOpsSetBackgroundColorImpl(Ark_NativePointer node,
                                                     const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::SetTextFieldOpsSetBackgroundColor(frameNode, convValue);
    return {};
}
} // TextFieldOpsAccessor
const GENERATED_ArkUITextFieldOpsAccessor* GetTextFieldOpsAccessor()
{
    static const GENERATED_ArkUITextFieldOpsAccessor TextFieldOpsAccessorImpl {
        TextFieldOpsAccessor::RegisterTextFieldValueCallbackImpl,
        TextFieldOpsAccessor::TextFieldOpsSetWidthImpl,
        TextFieldOpsAccessor::TextFieldOpsSetHeightImpl,
        TextFieldOpsAccessor::TextFieldOpsSetPaddingImpl,
        TextFieldOpsAccessor::TextFieldOpsSetMarginImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBorderImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBorderWidthImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBorderColorImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBorderStyleImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBorderRadiusImpl,
        TextFieldOpsAccessor::TextFieldOpsSetBackgroundColorImpl,
    };
    return &TextFieldOpsAccessorImpl;
}

}
