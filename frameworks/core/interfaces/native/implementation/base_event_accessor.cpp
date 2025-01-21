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
namespace BaseEventAccessor {
void DestroyPeerImpl(BaseEventPeer* peer)
{
}
Ark_NativePointer CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean GetModifierKeyStateImpl(BaseEventPeer* peer,
                                    const Array_String* keys)
{
    return 0;
}
void SetTargetImpl(BaseEventPeer* peer,
                   const Ark_EventTarget* target)
{
}
Ark_Int32 GetTimestampImpl(BaseEventPeer* peer)
{
    return 0;
}
void SetTimestampImpl(BaseEventPeer* peer,
                      const Ark_Number* timestamp)
{
}
Ark_NativePointer GetSourceImpl(BaseEventPeer* peer)
{
    return nullptr;
}
void SetSourceImpl(BaseEventPeer* peer,
                   Ark_SourceType source)
{
}
Ark_Int32 GetAxisHorizontalImpl(BaseEventPeer* peer)
{
    return 0;
}
void SetAxisHorizontalImpl(BaseEventPeer* peer,
                           const Ark_Number* axisHorizontal)
{
}
Ark_Int32 GetAxisVerticalImpl(BaseEventPeer* peer)
{
    return 0;
}
void SetAxisVerticalImpl(BaseEventPeer* peer,
                         const Ark_Number* axisVertical)
{
}
Ark_Int32 GetPressureImpl(BaseEventPeer* peer)
{
    return 0;
}
void SetPressureImpl(BaseEventPeer* peer,
                     const Ark_Number* pressure)
{
}
Ark_Int32 GetTiltXImpl(BaseEventPeer* peer)
{
    return 0;
}
void SetTiltXImpl(BaseEventPeer* peer,
                  const Ark_Number* tiltX)
{
}
Ark_Int32 GetTiltYImpl(BaseEventPeer* peer)
{
    return 0;
}
void SetTiltYImpl(BaseEventPeer* peer,
                  const Ark_Number* tiltY)
{
}
Ark_NativePointer GetSourceToolImpl(BaseEventPeer* peer)
{
    return nullptr;
}
void SetSourceToolImpl(BaseEventPeer* peer,
                       Ark_SourceTool sourceTool)
{
}
Ark_Int32 GetDeviceIdImpl(BaseEventPeer* peer)
{
    return 0;
}
void SetDeviceIdImpl(BaseEventPeer* peer,
                     const Ark_Number* deviceId)
{
}
} // BaseEventAccessor
const GENERATED_ArkUIBaseEventAccessor* GetBaseEventAccessor()
{
    static const GENERATED_ArkUIBaseEventAccessor BaseEventAccessorImpl {
        BaseEventAccessor::DestroyPeerImpl,
        BaseEventAccessor::CtorImpl,
        BaseEventAccessor::GetFinalizerImpl,
        BaseEventAccessor::GetModifierKeyStateImpl,
        BaseEventAccessor::SetTargetImpl,
        BaseEventAccessor::GetTimestampImpl,
        BaseEventAccessor::SetTimestampImpl,
        BaseEventAccessor::GetSourceImpl,
        BaseEventAccessor::SetSourceImpl,
        BaseEventAccessor::GetAxisHorizontalImpl,
        BaseEventAccessor::SetAxisHorizontalImpl,
        BaseEventAccessor::GetAxisVerticalImpl,
        BaseEventAccessor::SetAxisVerticalImpl,
        BaseEventAccessor::GetPressureImpl,
        BaseEventAccessor::SetPressureImpl,
        BaseEventAccessor::GetTiltXImpl,
        BaseEventAccessor::SetTiltXImpl,
        BaseEventAccessor::GetTiltYImpl,
        BaseEventAccessor::SetTiltYImpl,
        BaseEventAccessor::GetSourceToolImpl,
        BaseEventAccessor::SetSourceToolImpl,
        BaseEventAccessor::GetDeviceIdImpl,
        BaseEventAccessor::SetDeviceIdImpl,
    };
    return &BaseEventAccessorImpl;
}

struct BaseEventPeer {
    virtual ~BaseEventPeer() = default;
};
}
