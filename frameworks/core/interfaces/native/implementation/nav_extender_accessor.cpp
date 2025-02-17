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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "core/interfaces/native/implementation/nav_extender_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavExtenderAccessor {
void DestroyPeerImpl(Ark_NavExtender peer)
{
    if (peer) {
        delete peer;
    }
}
Ark_NavExtender CtorImpl()
{
    return new NavExtenderPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetUpdateStackCallbackImpl(Ark_NavPathStack peer,
                                const NavExtender_OnUpdateStack* callback)
{
    auto stack = peer;
    CHECK_NULL_VOID(stack);
    auto updater = [callback = CallbackHelper(*callback)](const std::string& value) {
        auto stringValue = Converter::ArkValue<Ark_String>(value);
        callback.Invoke(stringValue);
    };
    stack->SetUpdateCallback(std::move(updater));
}
} // NavExtenderAccessor
const GENERATED_ArkUINavExtenderAccessor* GetNavExtenderAccessor()
{
    static const GENERATED_ArkUINavExtenderAccessor NavExtenderAccessorImpl {
        NavExtenderAccessor::DestroyPeerImpl,
        NavExtenderAccessor::CtorImpl,
        NavExtenderAccessor::GetFinalizerImpl,
        NavExtenderAccessor::SetUpdateStackCallbackImpl,
    };
    return &NavExtenderAccessorImpl;
}

}
