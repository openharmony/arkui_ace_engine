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
#include "core/interfaces/native/utility/revserse_converter.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "core/interfaces/native/implementation/unified_data_peer.h"
#include "unified_data_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
    const GENERATED_ArkUIUnifiedDataAccessor* GetUnifiedDataAccessor();
}
namespace OHOS::Ace::NG::Converter {
    template<>
    RefPtr<UnifiedData> Convert(const Ark_UnifiedData& data)
    {
        auto unifiedDataPeer = reinterpret_cast<UnifiedDataPeer*>(data.ptr);
        return unifiedDataPeer ? unifiedDataPeer->unifiedData : nullptr;
    }

    void AssignArkValue(Ark_UnifiedData& arkData, const RefPtr<UnifiedData>& data)
    {
        const auto peer = reinterpret_cast<UnifiedDataPeer*>(NG::GeneratedModifier::GetUnifiedDataAccessor()->ctor());
        peer->unifiedData = data;
        arkData.ptr = peer;
    }
} // namespace Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DragEventAccessor {
using namespace Converter;
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
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->dragInfo);//const RefPtr<UnifiedData>& unifiedData
    peer->dragInfo->SetData(Convert<RefPtr<UnifiedData>>(*unifiedData)); // RefPtr<UnifiedData>
}
Ark_NativePointer GetDataImpl(DragEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    CHECK_NULL_RETURN(peer->dragInfo, 0);
    return ArkValue<Ark_NativePointer>(peer->dragInfo->GetData());
    return nullptr;
}
Ark_NativePointer GetSummaryImpl(DragEventPeer* peer)
{
    return nullptr;
}
void SetResultImpl(DragEventPeer* peer,
                   Ark_DragResult dragResult)
{
    // CHECK_NULL_RETURN(peer, 0);
    // CHECK_NULL_RETURN(peer->dragInfo, 0);
    // peer->dragInfo->SetResult(Convert<UnifiedData>(dragResult)); // DragRet
}
Ark_NativePointer GetResultImpl(DragEventPeer* peer)
{
    // CHECK_NULL_RETURN(peer, 0);
    // CHECK_NULL_RETURN(peer->dragInfo, 0);
    // return ArkValue<Ark_NativePointer>(peer->dragInfo->GetResult()); // fix it
    return nullptr;
}
Ark_NativePointer GetPreviewRectImpl(DragEventPeer* peer)
{
    // CHECK_NULL_RETURN(peer, 0);
    // CHECK_NULL_RETURN(peer->dragInfo, 0);
    // return ArkValue<Ark_NativePointer>(peer->dragInfo->GetPreviewRect()); // fix it
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
    return false;
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
