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
    RefPtr<UnifiedData> Convert(const Ark_UnifiedData& data)
    {
        auto unifiedDataPeer = reinterpret_cast<UnifiedDataPeer*>(data.ptr);
        return (unifiedDataPeer && unifiedDataPeer->unifiedData) ? unifiedDataPeer->unifiedData : nullptr;
    }
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
    CHECK_NULL_RETURN(peer, 0);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, 0);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetScreenX());
    auto arkScreenX = Converter::ArkValue<Ark_Number>(value);
    LOGE("Arkoala method DragEventAccessor.GetDisplayXImpl return int32_t value, instead of %{public}f",
        arkScreenX.f32);
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(value));
}
Ark_Int32 GetDisplayYImpl(DragEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, 0);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetScreenY());
    auto arkScreenY = Converter::ArkValue<Ark_Number>(value);
    LOGE("Arkoala method DragEventAccessor.GetDisplayYImpl return int32_t value, instead of %{public}f",
        arkScreenY.f32);
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(value));
}
Ark_Int32 GetWindowXImpl(DragEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    CHECK_NULL_RETURN(peer->dragInfo, 0);
    LOGE("Arkoala method DragEventAccessor.GetWindowXImpl return int32_t value");
    return ArkValue<Ark_Int32>(static_cast<int32_t>(peer->dragInfo->GetX()));
}
Ark_Int32 GetWindowYImpl(DragEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    CHECK_NULL_RETURN(peer->dragInfo, 0);
    LOGE("Arkoala method DragEventAccessor.GetWindowYImpl return int32_t value");
    return ArkValue<Ark_Int32>(static_cast<int32_t>(peer->dragInfo->GetY()));
}
Ark_Int32 GetXImpl(DragEventPeer* peer)
{
    return GetWindowXImpl(peer);
}
Ark_Int32 GetYImpl(DragEventPeer* peer)
{
    return GetWindowYImpl(peer);
}
void SetDataImpl(DragEventPeer* peer,
                 const Ark_UnifiedData* unifiedData)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->dragInfo);
    CHECK_NULL_VOID(unifiedData);
    CHECK_NULL_VOID(unifiedData->ptr);
    peer->dragInfo->SetData(Convert<RefPtr<UnifiedData>>(*unifiedData));
}
Ark_NativePointer GetDataImpl(DragEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->dragInfo, nullptr);
    auto data = peer->dragInfo->GetData();
    CHECK_NULL_RETURN(data, nullptr);
    const auto unifiedPeer = reinterpret_cast<UnifiedDataPeer*>(GeneratedModifier::GetUnifiedDataAccessor()->ctor());
    unifiedPeer->unifiedData = data;
    return reinterpret_cast<Ark_NativePointer>(unifiedPeer);
}
Ark_NativePointer GetSummaryImpl(DragEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, nullptr);
    auto summary = info->GetSummary();
    LOGE("DragEventAccessor::GetSummaryImpl wrong return data");
    return {};
}
void SetResultImpl(DragEventPeer* peer,
                   Ark_DragResult dragResult)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->dragInfo);
    auto result = OptConvert<DragRet>(dragResult);
    if (result) {
        peer->dragInfo->SetResult(*result);
    }
}
Ark_NativePointer GetResultImpl(DragEventPeer* peer)
{
    LOGE("DragEventAccessor::GetResultImpl wrong return data");
    return {};
}
Ark_NativePointer GetPreviewRectImpl(DragEventPeer* peer)
{
    LOGE("DragEventAccessor::GetPreviewRectImpl wrong return data");
    return {};
}
Ark_Int32 GetVelocityXImpl(DragEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, 0);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetVelocity().GetVelocityX());
    auto arkVelocityX = Converter::ArkValue<Ark_Number>(value);
    LOGE("Arkoala method DragEventAccessor.GetVelocityXImpl return int32_t value, instead of %{public}f",
        arkVelocityX.f32);
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(value));
}
Ark_Int32 GetVelocityYImpl(DragEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, 0);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetVelocity().GetVelocityY());
    auto arkVelocityY = Converter::ArkValue<Ark_Number>(value);
    LOGE("Arkoala method DragEventAccessor.GetVelocityYImpl return int32_t value, instead of %{public}f",
        arkVelocityY.f32);
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(value));
}
Ark_Int32 GetVelocityImpl(DragEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, 0);
    const auto value = PipelineBase::Px2VpWithCurrentDensity(info->GetVelocity().GetVelocityValue());
    auto arkVelocity = Converter::ArkValue<Ark_Number>(value);
    LOGE("Arkoala method DragEventAccessor.GetVelocityImpl return int32_t value, instead of %{public}f",
        arkVelocity.f32);
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(value));
}
Ark_Boolean GetModifierKeyStateImpl(DragEventPeer* peer,
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
Ark_NativePointer GetDragBehaviorImpl(DragEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto info = peer->dragInfo;
    CHECK_NULL_RETURN(info, nullptr);
    auto dragBehavior = info->GetDragBehavior();
    auto behavior = Converter::ArkValue<Ark_DragBehavior>(dragBehavior);
    LOGE("DragEventAccessor::GetDragBehaviorImpl wrong return data");
    return nullptr;
}
void SetDragBehaviorImpl(DragEventPeer* peer,
                         Ark_DragBehavior dragBehavior)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->dragInfo;
    CHECK_NULL_VOID(info);
    auto behavior = Converter::OptConvert<DragBehavior>(dragBehavior);
    if (behavior.has_value()) {
        info->SetDragBehavior(behavior.value());
    }
}
Ark_Boolean GetUseCustomDropAnimationImpl(DragEventPeer* peer)
{
    auto invalid = ArkValue<Ark_Boolean>(false);
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->dragInfo, invalid);
    return ArkValue<Ark_Boolean>(peer->dragInfo->IsUseCustomAnimation());
}
void SetUseCustomDropAnimationImpl(DragEventPeer* peer,
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
        DragEventAccessor::GetDragBehaviorImpl,
        DragEventAccessor::SetDragBehaviorImpl,
        DragEventAccessor::GetUseCustomDropAnimationImpl,
        DragEventAccessor::SetUseCustomDropAnimationImpl,
    };
    return &DragEventAccessorImpl;
}
}
