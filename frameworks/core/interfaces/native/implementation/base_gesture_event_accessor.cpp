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
#include "core/interfaces/native/implementation/base_gesture_event_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
    void AssignArkValue(Ark_FingerInfo& dst, const FingerInfo& src)
    {
        dst.id = Converter::ArkValue<Ark_Number>(src.fingerId_);
        dst.globalX = Converter::ArkValue<Ark_Number>(src.globalLocation_.GetX());
        dst.globalY = Converter::ArkValue<Ark_Number>(src.globalLocation_.GetY());
        dst.localX = Converter::ArkValue<Ark_Number>(src.localLocation_.GetX());
        dst.localY = Converter::ArkValue<Ark_Number>(src.localLocation_.GetY());
        dst.displayX = Converter::ArkValue<Ark_Number>(src.screenLocation_.GetX());
        dst.displayY = Converter::ArkValue<Ark_Number>(src.screenLocation_.GetY());
    }
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace BaseGestureEventAccessor {
void DestroyPeerImpl(Ark_BaseGestureEvent peer)
{
    delete peer;
}
Ark_BaseGestureEvent CtorImpl()
{
    return new BaseGestureEventPeerImpl();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Array_FingerInfo GetFingerListImpl(Ark_BaseGestureEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto info = peer->GetBaseGestureInfo();
    CHECK_NULL_RETURN(info, {});
    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    return Converter::ArkValue<Array_FingerInfo>(fingerList, Converter::FC);
}
void SetFingerListImpl(Ark_BaseGestureEvent peer,
                       const Array_FingerInfo* fingerList)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(fingerList);
    auto eventInfo = peer->GetBaseGestureInfo();
    CHECK_NULL_VOID(eventInfo);
    std::list<FingerInfo> list = Converter::Convert<std::list<FingerInfo>>(*fingerList);
    eventInfo->SetFingerList(list);
}
} // BaseGestureEventAccessor
const GENERATED_ArkUIBaseGestureEventAccessor* GetBaseGestureEventAccessor()
{
    static const GENERATED_ArkUIBaseGestureEventAccessor BaseGestureEventAccessorImpl {
        BaseGestureEventAccessor::DestroyPeerImpl,
        BaseGestureEventAccessor::CtorImpl,
        BaseGestureEventAccessor::GetFinalizerImpl,
        BaseGestureEventAccessor::GetFingerListImpl,
        BaseGestureEventAccessor::SetFingerListImpl,
    };
    return &BaseGestureEventAccessorImpl;
}
}
