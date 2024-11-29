/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GridColModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
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
void SpanImpl(Ark_NativePointer node,
              const Ark_Union_Number_GridColColumnOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GridColModelNG::SetSpan(frameNode, convValue);
}
void GridColOffsetImpl(Ark_NativePointer node,
                       const Ark_Union_Number_GridColColumnOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GridColModelNG::SetGridColOffset(frameNode, convValue);
}
void OrderImpl(Ark_NativePointer node,
               const Ark_Union_Number_GridColColumnOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GridColModelNG::SetOrder(frameNode, convValue);
}
} // GridColAttributeModifier
const GENERATED_ArkUIGridColModifier* GetGridColModifier()
{
    static const GENERATED_ArkUIGridColModifier ArkUIGridColModifierImpl {
        GridColModifier::ConstructImpl,
        GridColInterfaceModifier::SetGridColOptionsImpl,
        GridColAttributeModifier::SpanImpl,
        GridColAttributeModifier::GridColOffsetImpl,
        GridColAttributeModifier::OrderImpl,
    };
    return &ArkUIGridColModifierImpl;
}

}
