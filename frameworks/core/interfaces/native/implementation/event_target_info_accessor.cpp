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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

#include "core/interfaces/native/implementation/event_target_info_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace EventTargetInfoAccessor {
void DestroyPeerImpl(EventTargetInfoPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new EventTargetInfoPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void GetIdImpl(EventTargetInfoPeer* peer)
{
    CHECK_NULL_VOID(peer); // Use CHECK_NULL_VOID_RETURN with an empty string if it is possible.
    const auto result = Converter::ArkValue<Ark_String>(peer->id); // Return result if it is possible.
    LOGE("EventTargetInfoAccessor: GetIdImpl (blocked) result: %{public}s",
        Converter::Convert<std::string>(result).c_str());
}
} // EventTargetInfoAccessor
const GENERATED_ArkUIEventTargetInfoAccessor* GetEventTargetInfoAccessor()
{
    static const GENERATED_ArkUIEventTargetInfoAccessor EventTargetInfoAccessorImpl {
        EventTargetInfoAccessor::DestroyPeerImpl,
        EventTargetInfoAccessor::CtorImpl,
        EventTargetInfoAccessor::GetFinalizerImpl,
        EventTargetInfoAccessor::GetIdImpl,
    };
    return &EventTargetInfoAccessorImpl;
}

struct EventTargetInfoPeer {
    virtual ~EventTargetInfoPeer() = default;
};
}
