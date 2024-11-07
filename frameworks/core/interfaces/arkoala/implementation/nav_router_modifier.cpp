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
namespace NavRouterInterfaceModifier {
void SetNavRouterOptions0Impl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //NavRouterModelNG::SetSetNavRouterOptions0(frameNode, convValue);
}
void SetNavRouterOptions1Impl(Ark_NativePointer node,
                              const Ark_RouteInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavRouterModelNG::SetSetNavRouterOptions1(frameNode, convValue);
}
} // NavRouterInterfaceModifier
namespace NavRouterAttributeModifier {
void OnStateChangeImpl(Ark_NativePointer node,
                       const Ark_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //NavRouterModelNG::SetOnStateChange(frameNode, convValue);
}
void ModeImpl(Ark_NativePointer node,
              Ark_NavRouteMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //NavRouterModelNG::SetMode(frameNode, convValue);
}
} // NavRouterAttributeModifier
const GENERATED_ArkUINavRouterModifier* GetNavRouterModifier()
{
    static const GENERATED_ArkUINavRouterModifier ArkUINavRouterModifierImpl {
        NavRouterInterfaceModifier::SetNavRouterOptions0Impl,
        NavRouterInterfaceModifier::SetNavRouterOptions1Impl,
        NavRouterAttributeModifier::OnStateChangeImpl,
        NavRouterAttributeModifier::ModeImpl,
    };
    return &ArkUINavRouterModifierImpl;
}

}
