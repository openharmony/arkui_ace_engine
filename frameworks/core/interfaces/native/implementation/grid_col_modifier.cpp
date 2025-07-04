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
namespace GridColModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // GridColModifier
namespace GridColInterfaceModifier {
void SetGridColOptionsImpl(Ark_NativePointer node,
                           const Opt_GridColOptions* option)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = option ? Converter::OptConvert<type>(*option) : std::nullopt;
    //GridColModelNG::SetSetGridColOptions(frameNode, convValue);
}
} // GridColInterfaceModifier
namespace GridColAttributeModifier {
void SetSpanImpl(Ark_NativePointer node,
                 const Opt_Union_Number_GridColColumnOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridColModelNG::SetSetSpan(frameNode, convValue);
}
void SetGridColOffsetImpl(Ark_NativePointer node,
                          const Opt_Union_Number_GridColColumnOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridColModelNG::SetSetGridColOffset(frameNode, convValue);
}
void SetOrderImpl(Ark_NativePointer node,
                  const Opt_Union_Number_GridColColumnOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //GridColModelNG::SetSetOrder(frameNode, convValue);
}
} // GridColAttributeModifier
const GENERATED_ArkUIGridColModifier* GetGridColModifier()
{
    static const GENERATED_ArkUIGridColModifier ArkUIGridColModifierImpl {
        GridColModifier::ConstructImpl,
        GridColInterfaceModifier::SetGridColOptionsImpl,
        GridColAttributeModifier::SetSpanImpl,
        GridColAttributeModifier::SetGridColOffsetImpl,
        GridColAttributeModifier::SetOrderImpl,
    };
    return &ArkUIGridColModifierImpl;
}

}
