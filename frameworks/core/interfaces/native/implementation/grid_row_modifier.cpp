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
namespace GridRowModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // GridRowModifier
namespace GridRowInterfaceModifier {
void SetGridRowOptionsImpl(Ark_NativePointer node,
                           const Opt_GridRowOptions* option)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = option ? Converter::OptConvert<type>(*option) : std::nullopt;
    //GridRowModelNG::SetSetGridRowOptions(frameNode, convValue);
}
} // GridRowInterfaceModifier
namespace GridRowAttributeModifier {
void OnBreakpointChangeImpl(Ark_NativePointer node,
                            const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //GridRowModelNG::SetOnBreakpointChange(frameNode, convValue);
}
void AlignItemsImpl(Ark_NativePointer node,
                    Ark_ItemAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //GridRowModelNG::SetAlignItems(frameNode, convValue);
}
} // GridRowAttributeModifier
const GENERATED_ArkUIGridRowModifier* GetGridRowModifier()
{
    static const GENERATED_ArkUIGridRowModifier ArkUIGridRowModifierImpl {
        GridRowModifier::ConstructImpl,
        GridRowInterfaceModifier::SetGridRowOptionsImpl,
        GridRowAttributeModifier::OnBreakpointChangeImpl,
        GridRowAttributeModifier::AlignItemsImpl,
    };
    return &ArkUIGridRowModifierImpl;
}

}
