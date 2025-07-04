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
namespace HoverEventAccessor {
void DestroyPeerImpl(Ark_HoverEvent peer)
{
    auto peerImpl = reinterpret_cast<HoverEventPeerImpl *>(peer);
    if (peerImpl) {
        delete peerImpl;
    }
}
Ark_HoverEvent ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_Number GetXImpl(Ark_HoverEvent peer)
{
    return {};
}
void SetXImpl(Ark_HoverEvent peer,
              const Opt_Number* x)
{
}
Opt_Number GetYImpl(Ark_HoverEvent peer)
{
    return {};
}
void SetYImpl(Ark_HoverEvent peer,
              const Opt_Number* y)
{
}
Opt_Number GetWindowXImpl(Ark_HoverEvent peer)
{
    return {};
}
void SetWindowXImpl(Ark_HoverEvent peer,
                    const Opt_Number* windowX)
{
}
Opt_Number GetWindowYImpl(Ark_HoverEvent peer)
{
    return {};
}
void SetWindowYImpl(Ark_HoverEvent peer,
                    const Opt_Number* windowY)
{
}
Opt_Number GetDisplayXImpl(Ark_HoverEvent peer)
{
    return {};
}
void SetDisplayXImpl(Ark_HoverEvent peer,
                     const Opt_Number* displayX)
{
}
Opt_Number GetDisplayYImpl(Ark_HoverEvent peer)
{
    return {};
}
void SetDisplayYImpl(Ark_HoverEvent peer,
                     const Opt_Number* displayY)
{
}
Callback_Void GetStopPropagationImpl(Ark_HoverEvent peer)
{
    return {};
}
void SetStopPropagationImpl(Ark_HoverEvent peer,
                            const Callback_Void* stopPropagation)
{
}
} // HoverEventAccessor
const GENERATED_ArkUIHoverEventAccessor* GetHoverEventAccessor()
{
    static const GENERATED_ArkUIHoverEventAccessor HoverEventAccessorImpl {
        HoverEventAccessor::DestroyPeerImpl,
        HoverEventAccessor::ConstructImpl,
        HoverEventAccessor::GetFinalizerImpl,
        HoverEventAccessor::GetXImpl,
        HoverEventAccessor::SetXImpl,
        HoverEventAccessor::GetYImpl,
        HoverEventAccessor::SetYImpl,
        HoverEventAccessor::GetWindowXImpl,
        HoverEventAccessor::SetWindowXImpl,
        HoverEventAccessor::GetWindowYImpl,
        HoverEventAccessor::SetWindowYImpl,
        HoverEventAccessor::GetDisplayXImpl,
        HoverEventAccessor::SetDisplayXImpl,
        HoverEventAccessor::GetDisplayYImpl,
        HoverEventAccessor::SetDisplayYImpl,
        HoverEventAccessor::GetStopPropagationImpl,
        HoverEventAccessor::SetStopPropagationImpl,
    };
    return &HoverEventAccessorImpl;
}

struct HoverEventPeer {
    virtual ~HoverEventPeer() = default;
};
}
