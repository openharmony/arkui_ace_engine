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
#include "core/interfaces/native/implementation/permission_request_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PermissionRequestAccessor {
PermissionRequestPeer* CtorImpl()
{
    return new PermissionRequestPeer();
}
static void DestroyPeer(PermissionRequestPeer *peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(DestroyPeer);
}
void DenyImpl(PermissionRequestPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->Deny();
}
void GetOriginImpl(PermissionRequestPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetOrigin();
    // origin value need to be returned
    LOGE("PermissionRequestAccessor::GetOriginImpl - return value need to be supported");
}
void GetAccessibleResourceImpl(PermissionRequestPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetResources();
    // accessible resource value need to be returned
    LOGE("PermissionRequestAccessor::GetAccessibleResourceImpl - return value need to be supported");
}
void GrantImpl(PermissionRequestPeer* peer,
               const Array_String* resources)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(resources);
    auto res = Converter::Convert<std::vector<std::string>>(*resources);
    peer->handler->Grant(res);
}
} // PermissionRequestAccessor
const GENERATED_ArkUIPermissionRequestAccessor* GetPermissionRequestAccessor()
{
    static const GENERATED_ArkUIPermissionRequestAccessor PermissionRequestAccessorImpl {
        PermissionRequestAccessor::CtorImpl,
        PermissionRequestAccessor::GetFinalizerImpl,
        PermissionRequestAccessor::DenyImpl,
        PermissionRequestAccessor::GetOriginImpl,
        PermissionRequestAccessor::GetAccessibleResourceImpl,
        PermissionRequestAccessor::GrantImpl,
    };
    return &PermissionRequestAccessorImpl;
}

}
