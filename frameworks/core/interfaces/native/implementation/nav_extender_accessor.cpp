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
namespace NavExtenderAccessor {
void SetUpdateStackCallbackImpl(Ark_NavPathStack peer,
                                const NavExtender_OnUpdateStack* callback)
{
}
void SyncStackImpl(Ark_NavPathStack peer)
{
}
Ark_Boolean CheckNeedCreateImpl(Ark_NativePointer navigation,
                                Ark_Int32 index)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(navigation);
    //auto convValue = Converter::OptConvert<type>(navigation); // for enums
    //undefinedModelNG::SetCheckNeedCreate(frameNode, convValue);
    return {};
}
Ark_NativePointer NavigationCreateImpl(Ark_Int32 peer,
                                       Ark_Int32 flag)
{
    return {};
}
void SetNavigationOptionsImpl(Ark_NativePointer navigation,
                              Ark_NavPathStack stack)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(navigation);
    //auto convValue = Converter::OptConvert<type>(navigation); // for enums
    //undefinedModelNG::SetSetNavigationOptions(frameNode, convValue);
}
void SetNavDestinationNodeImpl(Ark_NavPathStack peer,
                               Ark_Int32 index,
                               Ark_NativePointer node)
{
}
} // NavExtenderAccessor
const GENERATED_ArkUINavExtenderAccessor* GetNavExtenderAccessor()
{
    static const GENERATED_ArkUINavExtenderAccessor NavExtenderAccessorImpl {
        NavExtenderAccessor::SetUpdateStackCallbackImpl,
        NavExtenderAccessor::SyncStackImpl,
        NavExtenderAccessor::CheckNeedCreateImpl,
        NavExtenderAccessor::NavigationCreateImpl,
        NavExtenderAccessor::SetNavigationOptionsImpl,
        NavExtenderAccessor::SetNavDestinationNodeImpl,
    };
    return &NavExtenderAccessorImpl;
}

}
