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
#include "core/interfaces/native/utility/accessor_utils.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "core/interfaces/native/implementation/unified_data_peer.h"
#include "unified_data_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
    const GENERATED_ArkUIUnifiedDataAccessor* GetUnifiedDataAccessor();
}
namespace OHOS::Ace::NG::Converter {
    template<>
    void AssignCast(std::optional<DragRet>& dst, const Ark_DragResult& src)
    {
        switch (src) {
            case ARK_DRAG_RESULT_DRAG_SUCCESSFUL: dst = DragRet::DRAG_SUCCESS; break;
            case ARK_DRAG_RESULT_DRAG_FAILED: dst = DragRet::DRAG_FAIL; break;
            case ARK_DRAG_RESULT_DRAG_CANCELED: dst = DragRet::DRAG_CANCEL; break;
            case ARK_DRAG_RESULT_DROP_ENABLED: dst = DragRet::ENABLE_DROP; break;
            case ARK_DRAG_RESULT_DROP_DISABLED: dst = DragRet::DISABLE_DROP; break;
            default: LOGE("Unexpected enum value in DragRet: %{public}d", src);
        }
    }

    void AssignArkValue(Ark_DragResult& dst, const DragRet& src)
    {
        switch (src) {
            case DragRet::DRAG_SUCCESS: dst = ARK_DRAG_RESULT_DRAG_SUCCESSFUL; break;
            case DragRet::DRAG_FAIL: dst = ARK_DRAG_RESULT_DRAG_FAILED; break;
            case DragRet::DRAG_CANCEL: dst = ARK_DRAG_RESULT_DRAG_CANCELED; break;\
            case DragRet::ENABLE_DROP: dst = ARK_DRAG_RESULT_DROP_ENABLED; break;
            case DragRet::DISABLE_DROP: dst = ARK_DRAG_RESULT_DROP_DISABLED; break;
            default:
                dst = static_cast<Ark_DragResult>(-1);
                LOGE("Unexpected enum value in Ark_DragResult: %{public}d", src);
        }
    }

    void AssignArkValue(Ark_Rectangle& dst, const Rect& src)
    {
        dst.x = ArkValue<Opt_Length>(src.Left());
        dst.y = ArkValue<Opt_Length>(src.Top());
        dst.width = ArkValue<Opt_Length>(src.Width());
        dst.height = ArkValue<Opt_Length>(src.Height());
    }
} // namespace Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DragEventAccessor {
using namespace Converter;
void DestroyPeerImpl(Ark_DragEvent peer)
{
    delete peer;
}
Ark_DragEvent CtorImpl()
{
    return new DragEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetDisplayXImpl(Ark_DragEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, errValue);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetScreenX());
    return Converter::ArkValue<Ark_Number>(value);
}
Ark_Number GetDisplayYImpl(Ark_DragEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, errValue);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetScreenY());
    return Converter::ArkValue<Ark_Number>(value);
}
Ark_Number GetWindowXImpl(Ark_DragEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    CHECK_NULL_RETURN(peer->dragInfo, errValue);
    return ArkValue<Ark_Number>(peer->dragInfo->GetX());
}
Ark_Number GetWindowYImpl(Ark_DragEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    CHECK_NULL_RETURN(peer->dragInfo, errValue);
    return ArkValue<Ark_Number>(peer->dragInfo->GetY());
}
Ark_Number GetXImpl(Ark_DragEvent peer)
{
    return GetWindowXImpl(peer);
}
Ark_Number GetYImpl(Ark_DragEvent peer)
{
    return GetWindowYImpl(peer);
}
void SetDataImpl(Ark_DragEvent peer,
                 Ark_UnifiedData unifiedData)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->dragInfo);
    CHECK_NULL_VOID(unifiedData);
    peer->dragInfo->SetData(unifiedData->unifiedData);
}
Ark_UnifiedData GetDataImpl(Ark_VMContext vmContext,
                            Ark_DragEvent peer)
{
    const auto unifiedPeer = GeneratedModifier::GetUnifiedDataAccessor()->ctor();
    CHECK_NULL_RETURN(peer, unifiedPeer);
    CHECK_NULL_RETURN(peer->dragInfo, unifiedPeer);
    auto data = peer->dragInfo->GetData();
    CHECK_NULL_RETURN(data, unifiedPeer);
    unifiedPeer->unifiedData = data;
    return unifiedPeer;
}
Ark_Summary GetSummaryImpl(Ark_DragEvent peer)
{
    Ark_Summary arkValue = { .summary = {}, .totalSize = 0 };
    CHECK_NULL_RETURN(peer, arkValue);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, arkValue);
    auto summary = info->GetSummary();
    arkValue.summary = Converter::ArkValue<Map_String_Int64>(summary, Converter::FC);
    for (const auto &item: summary) {
        arkValue.totalSize += ArkValue<Ark_Int64>(item.second);
    }
    return arkValue;
}
void SetResultImpl(Ark_DragEvent peer,
                   Ark_DragResult dragResult)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->dragInfo);
    auto result = OptConvert<DragRet>(dragResult);
    if (result) {
        peer->dragInfo->SetResult(*result);
    }
}
Ark_DragResult GetResultImpl(Ark_DragEvent peer)
{
    auto defaultReturn = ArkValue<Ark_DragResult>(DragRet::DRAG_DEFAULT); // DRAG_DEFAULT = -1
    CHECK_NULL_RETURN(peer, defaultReturn);
    CHECK_NULL_RETURN(peer->dragInfo, defaultReturn);
    return ArkValue<Ark_DragResult>(peer->dragInfo->GetResult());
}
Ark_Rectangle GetPreviewRectImpl(Ark_DragEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, {});
    return ArkValue<Ark_Rectangle>(info->GetPreviewRect());
}
Ark_Number GetVelocityXImpl(Ark_DragEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, errValue);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetVelocity().GetVelocityX());
    return Converter::ArkValue<Ark_Number>(value);
}
Ark_Number GetVelocityYImpl(Ark_DragEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, errValue);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetVelocity().GetVelocityY());
    return Converter::ArkValue<Ark_Number>(value);
}
Ark_Number GetVelocityImpl(Ark_DragEvent peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, errValue);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetVelocity().GetVelocityValue());
    return Converter::ArkValue<Ark_Number>(value);
}
Ark_Boolean GetModifierKeyStateImpl(Ark_VMContext vmContext,
                                    Ark_DragEvent peer,
                                    const Array_String* keys)
{
    auto defaultValue = ArkValue<Ark_Boolean>(false);
    CHECK_NULL_RETURN(peer, defaultValue);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, defaultValue);
    auto eventKeys = info->GetPressedKeyCodes();
    auto keysStr = Converter::Convert<std::vector<std::string>>(*keys);
    return Converter::ArkValue<Ark_Boolean>(AccessorUtils::CheckKeysPressed(keysStr, eventKeys));
}
void ExecuteDropAnimationImpl(Ark_DragEvent peer,
                              const Callback_Void* customDropAnimation)
{
    CHECK_NULL_VOID(customDropAnimation);
    CHECK_NULL_VOID(peer);
    auto info = peer->dragInfo;
    CHECK_NULL_VOID(info);
    auto customDropAnimationCallback = [callback = CallbackHelper(*customDropAnimation)]() {
        callback.InvokeSync();
    };
    info->SetDropAnimation(std::move(customDropAnimationCallback));
}
Ark_String StartDataLoadingImpl(Ark_VMContext vmContext,
                                Ark_DragEvent peer,
                                const Ark_DataSyncOptions* options)
{
    return {};
}
Ark_DragBehavior GetDragBehaviorImpl(Ark_DragEvent peer)
{
    auto defaultReturn = ArkValue<Ark_DragBehavior>(DragBehavior::MOVE);
    CHECK_NULL_RETURN(peer, defaultReturn);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, defaultReturn);
    auto dragBehavior = info->GetDragBehavior();
    return Converter::ArkValue<Ark_DragBehavior>(dragBehavior);
}
void SetDragBehaviorImpl(Ark_DragEvent peer,
                         Ark_DragBehavior dragBehavior)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->dragInfo;
    CHECK_NULL_VOID(info);
    auto behavior = Converter::OptConvert<DragBehavior>(dragBehavior);
    if (behavior) {
        info->SetDragBehavior(*behavior);
    }
}
Ark_Boolean GetUseCustomDropAnimationImpl(Ark_DragEvent peer)
{
    auto invalid = ArkValue<Ark_Boolean>(false);
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->dragInfo, invalid);
    return ArkValue<Ark_Boolean>(peer->dragInfo->IsUseCustomAnimation());
}
void SetUseCustomDropAnimationImpl(Ark_DragEvent peer,
                                   Ark_Boolean useCustomDropAnimation)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->dragInfo);
    peer->dragInfo->UseCustomAnimation(Convert<bool>(useCustomDropAnimation));
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
