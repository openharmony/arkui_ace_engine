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
namespace LocationButtonModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // LocationButtonModifier
namespace LocationButtonInterfaceModifier {
void SetLocationButtonOptions0Impl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //LocationButtonModelNG::SetSetLocationButtonOptions0(frameNode, convValue);
}
void SetLocationButtonOptions1Impl(Ark_NativePointer node,
                                   const Ark_LocationButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //LocationButtonModelNG::SetSetLocationButtonOptions1(frameNode, convValue);
}
} // LocationButtonInterfaceModifier
namespace LocationButtonAttributeModifier {
void OnClickImpl(Ark_NativePointer node,
                 const Callback_ClickEvent_LocationButtonOnClickResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //LocationButtonModelNG::SetOnClick(frameNode, convValue);
}
} // LocationButtonAttributeModifier
const GENERATED_ArkUILocationButtonModifier* GetLocationButtonModifier()
{
    static const GENERATED_ArkUILocationButtonModifier ArkUILocationButtonModifierImpl {
        LocationButtonModifier::ConstructImpl,
        LocationButtonInterfaceModifier::SetLocationButtonOptions0Impl,
        LocationButtonInterfaceModifier::SetLocationButtonOptions1Impl,
        LocationButtonAttributeModifier::OnClickImpl,
    };
    return &ArkUILocationButtonModifierImpl;
}

}
