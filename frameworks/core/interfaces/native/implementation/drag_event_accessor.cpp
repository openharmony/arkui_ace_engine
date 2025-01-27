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
#include "core/interfaces/native/implementation/drag_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DragEventAccessor {
void DestroyPeerImpl(DragEventPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new DragEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Int32 GetDisplayXImpl(DragEventPeer* peer)
{
    return 0;
}
Ark_Int32 GetDisplayYImpl(DragEventPeer* peer)
{
    return 0;
}
Ark_Int32 GetWindowXImpl(DragEventPeer* peer)
{
    return 0;
}
Ark_Int32 GetWindowYImpl(DragEventPeer* peer)
{
    return 0;
}
Ark_Int32 GetXImpl(DragEventPeer* peer)
{
    return 0;
}
Ark_Int32 GetYImpl(DragEventPeer* peer)
{
    return 0;
}
void SetDataImpl(DragEventPeer* peer,
                 const Ark_UnifiedData* unifiedData)
{
}
Ark_NativePointer GetDataImpl(DragEventPeer* peer)
{
    return nullptr;
}
Ark_NativePointer GetSummaryImpl(DragEventPeer* peer)
{
    return nullptr;
}
void SetResultImpl(DragEventPeer* peer,
                   Ark_DragResult dragResult)
{
}
Ark_NativePointer GetResultImpl(DragEventPeer* peer)
{
    return nullptr;
}
Ark_NativePointer GetPreviewRectImpl(DragEventPeer* peer)
{
    return nullptr;
}
Ark_Int32 GetVelocityXImpl(DragEventPeer* peer)
{
    return 0;
}
Ark_Int32 GetVelocityYImpl(DragEventPeer* peer)
{
    return 0;
}
Ark_Int32 GetVelocityImpl(DragEventPeer* peer)
{
    return 0;
}
Ark_Boolean GetModifierKeyStateImpl(DragEventPeer* peer,
                                    const Array_String* keys)
{
    return 0;
}
Ark_NativePointer GetDragBehaviorImpl(DragEventPeer* peer)
{
    return nullptr;
}
void SetDragBehaviorImpl(DragEventPeer* peer,
                         Ark_DragBehavior dragBehavior)
{
}
Ark_Boolean GetUseCustomDropAnimationImpl(DragEventPeer* peer)
{
    return 0;
}
void SetUseCustomDropAnimationImpl(DragEventPeer* peer,
                                   Ark_Boolean useCustomDropAnimation)
{
}
} // DragEventAccessor
const GENERATED_ArkUIDragEventAccessor* GetDragEventAccessor()
{
    static const GENERATED_ArkUIDragEventAccessor DragEventAccessorImpl {
        DragEventAccessor::DestroyPeerImpl,
        DragEventAccessor::CtorImpl,
        DragEventAccessor::GetFinalizerImpl,
        DragEventAccessor::GetDisplayXImpl,
        DragEventAccessor::GetDisplayYImpl,
        DragEventAccessor::GetWindowXImpl,
        DragEventAccessor::GetWindowYImpl,
        DragEventAccessor::GetXImpl,
        DragEventAccessor::GetYImpl,
        DragEventAccessor::SetDataImpl,
        DragEventAccessor::GetDataImpl,
        DragEventAccessor::GetSummaryImpl,
        DragEventAccessor::SetResultImpl,
        DragEventAccessor::GetResultImpl,
        DragEventAccessor::GetPreviewRectImpl,
        DragEventAccessor::GetVelocityXImpl,
        DragEventAccessor::GetVelocityYImpl,
        DragEventAccessor::GetVelocityImpl,
        DragEventAccessor::GetModifierKeyStateImpl,
        DragEventAccessor::GetDragBehaviorImpl,
        DragEventAccessor::SetDragBehaviorImpl,
        DragEventAccessor::GetUseCustomDropAnimationImpl,
        DragEventAccessor::SetUseCustomDropAnimationImpl,
    };
    return &DragEventAccessorImpl;
}

}
