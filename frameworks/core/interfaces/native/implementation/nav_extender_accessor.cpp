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
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavExtenderAccessor {
void SetUpdateStackCallbackImpl(Ark_NavPathStack peer,
                                const NavExtender_OnUpdateStack* callback)
{
    auto stack = peer;
    CHECK_NULL_VOID(stack);
    auto navigationStack = stack->GetNavPathStack();
    CHECK_NULL_VOID(navigationStack);
    auto updater = [callback = CallbackHelper(*callback)]() {
        Converter::ConvContext ctx;
        auto name = Converter::ArkValue<Ark_String>("", &ctx);
        callback.Invoke(name);
    };
    navigationStack->SetOnStateChangedCallback(std::move(updater));
}
void SyncStackImpl(Ark_NavPathStack peer)
{
    CHECK_NULL_VOID(peer);
    auto stack = peer->GetNavPathStack();
    CHECK_NULL_VOID(stack);
    auto navigationNode = AceType::DynamicCast<FrameNode>(stack->GetNavigationNode().Upgrade());
    CHECK_NULL_VOID(navigationNode);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    stack->ClearNodeList();
}
Ark_Boolean CheckNeedCreateImpl(Ark_NativePointer navigation,
                                Ark_Int32 index)
{
    auto invalidVal = Converter::ArkValue<Ark_Boolean>(false);
    auto navigationNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_RETURN(navigationNode, invalidVal);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(pattern, invalidVal);
    // need check
    return Converter::ArkValue<Ark_Boolean>(true);
}
Ark_NativePointer NavigationCreateImpl(Ark_Int32 peer,
                                       Ark_Int32 flag)
{
    auto frameNode = NavigationModelNG::CreateFrameNode(peer);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
void SetNavigationOptionsImpl(Ark_NativePointer navigation,
                              Ark_NavPathStack stack)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(stack);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    auto navigationStack = stack->GetNavPathStack();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationStack->SetOnStateChangedCallback(nullptr);
}
void SetNavDestinationNodeImpl(Ark_NavPathStack peer,
                               Ark_Int32 index,
                               Ark_NativePointer node)
{
    CHECK_NULL_VOID(peer);
    auto stack = peer->GetNavPathStack();
    CHECK_NULL_VOID(stack);
    int32_t curIndex = Converter::Convert<int32_t>(index);
    stack->AddCustomNode(curIndex, Referenced::Claim(reinterpret_cast<UINode*>(node)));
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
