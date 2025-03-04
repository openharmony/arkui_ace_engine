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
namespace DragEventAccessor {
void DestroyPeerImpl(Ark_DragEvent peer)
{
}
Ark_DragEvent CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetDisplayXImpl(Ark_DragEvent peer)
{
    return {};
}
Ark_Number GetDisplayYImpl(Ark_DragEvent peer)
{
    return {};
}
Ark_Number GetWindowXImpl(Ark_DragEvent peer)
{
    return {};
}
Ark_Number GetWindowYImpl(Ark_DragEvent peer)
{
    return {};
}
Ark_Number GetXImpl(Ark_DragEvent peer)
{
    return {};
}
Ark_Number GetYImpl(Ark_DragEvent peer)
{
    return {};
}
void SetDataImpl(Ark_DragEvent peer,
                 Ark_UnifiedData unifiedData)
{
}
Ark_UnifiedData GetDataImpl(Ark_VMContext vmContext,
                            Ark_DragEvent peer)
{
    return {};
}
Ark_Summary GetSummaryImpl(Ark_DragEvent peer)
{
    return {};
}
void SetResultImpl(Ark_DragEvent peer,
                   Ark_DragResult dragResult)
{
}
Ark_DragResult GetResultImpl(Ark_DragEvent peer)
{
    return {};
}
Ark_Rectangle GetPreviewRectImpl(Ark_DragEvent peer)
{
    return {};
}
Ark_Number GetVelocityXImpl(Ark_DragEvent peer)
{
    return {};
}
Ark_Number GetVelocityYImpl(Ark_DragEvent peer)
{
    return {};
}
Ark_Number GetVelocityImpl(Ark_DragEvent peer)
{
    return {};
}
Ark_Boolean GetModifierKeyStateImpl(Ark_VMContext vmContext,
                                    Ark_DragEvent peer,
                                    const Array_String* keys)
{
    return {};
}
void ExecuteDropAnimationImpl(Ark_DragEvent peer,
                              const Callback_Void* customDropAnimation)
{
}
Ark_String StartDataLoadingImpl(Ark_VMContext vmContext,
                                Ark_DragEvent peer,
                                const Ark_DataSyncOptions* options)
{
    return {};
}
Ark_DragBehavior GetDragBehaviorImpl(Ark_DragEvent peer)
{
    return {};
}
void SetDragBehaviorImpl(Ark_DragEvent peer,
                         Ark_DragBehavior dragBehavior)
{
}
Ark_Boolean GetUseCustomDropAnimationImpl(Ark_DragEvent peer)
{
    return {};
}
void SetUseCustomDropAnimationImpl(Ark_DragEvent peer,
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
        DragEventAccessor::ExecuteDropAnimationImpl,
        DragEventAccessor::StartDataLoadingImpl,
        DragEventAccessor::GetDragBehaviorImpl,
        DragEventAccessor::SetDragBehaviorImpl,
        DragEventAccessor::GetUseCustomDropAnimationImpl,
        DragEventAccessor::SetUseCustomDropAnimationImpl,
    };
    return &DragEventAccessorImpl;
}

}
